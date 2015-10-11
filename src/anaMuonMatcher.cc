#include "UserCode/TopFromHeavyIons/interface/anaMuonMatcher.h"

#include "UserCode/TopFromHeavyIons/interface/lwMuon.h"
#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

#include "TClass.h"

ClassImp(anaMuonMatcher)
   
anaMuonMatcher::anaMuonMatcher(const char *name, const char *title) 
:anaBaseTask(name,title),
  fMuonsName(""),
  fMuons(0x0),
  fMatchName(""),
  fMatch(0x0),
  fMatchType(kGen),
  fh1PtNoMatch(),
  fh2MuPtDeltaR(),
  fh2MuPtDeltaRPF(),
  fh2MuPtFracDeltaR(),
  fh2MuPtFracDeltaRPF(),
  fh1MuPtGen(),
  fh1MuPtGenMatch()
{

}

//----------------------------------------------------------
void anaMuonMatcher::Exec(Option_t * /*option*/)
{
   //printf("anaMuonMatcher executing\n");
   if(!fInitOutput) CreateOutputObjects();

   if(!fMuons && !fMuonsName.IsNull()) {
     fMuons = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fMuonsName.Data()));
     //inheritance check gives crash. Don't know why. Skipping for now. Dangerous
     //     if(fMuons)
     //  if(!CheckInheritance(fMuons,"lwMuon")) return;
   }
   
   if(!fMuons) return;

   if(!fMatch && !fMatchName.IsNull()) {
     fMatch = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fMatchName.Data()));
     //inheritance check gives crash. Don't know why. Skipping for now. Dangerous
     //if(fMatch)
       // if(!CheckInheritance(fMatch,"particleBase")) return;
   }
   if(!fMatch) return;

   //Printf("reco muons: %d  gene muons: %d",fMuons->GetEntriesFast(),fMatch->GetEntriesFast());
   
   for (int i = 0; i < fMuons->GetEntriesFast(); i++) {
     lwMuon *muon = static_cast<lwMuon*>(fMuons->At(i));
  
     Double_t drMin = 999.;
     Int_t closest  = -1;
     particleBase *matched;
     for (int j = 0; j < fMatch->GetEntriesFast(); j++) {
       particleBase *match = static_cast<particleBase*>(fMatch->At(j));
       Double_t dr = muon->DeltaR(match);
       if(dr<drMin) {
         drMin = dr;
         closest = j;
         matched=match;
       }
     }
     //  Printf("match found for muon %d to %d with dr=%f",i,closest,drMin);
     if(closest>-1) {
       fh2MuPtDeltaR->Fill(muon->Pt(),drMin);
       fh2MuPtFracDeltaR->Fill(muon->Pt()/matched->Pt(),drMin);
       if(fMatchType==kPF && fabs(muon->GetId())==5) {
         fh2MuPtDeltaRPF->Fill(muon->Pt(),drMin);
         fh2MuPtFracDeltaRPF->Fill(muon->Pt()/matched->Pt(),drMin);
       }

       particleBase *match = static_cast<particleBase*>(fMatch->At(closest));
       if(fMatchType==kGen)  {
         muon->SetClosestGen(closest);
         match->SetMatchId1(i);
       }
       if(fMatchType==kPF) {
         muon->SetClosestPF(closest);
         match->SetMatchId2(i);
       }
       
     } else {
       fh1PtNoMatch->Fill(muon->Pt());
     }

   }

   if(fMatchType==kGen) {
     for (int j = 0; j < fMatch->GetEntriesFast(); j++) {
       particleBase *match = static_cast<particleBase*>(fMatch->At(j));
       fh1MuPtGen->Fill(match->Pt());
       if(match->GetMatchId1()>-1) fh1MuPtGenMatch->Fill(match->Pt());
     }
   }
}

//----------------------------------------------------------
void anaMuonMatcher::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaMuonMatcher: fOutput not present");
    return;
  }

  fh1PtNoMatch = new TH1F("fh1PtNoMatch","fh1PtNoMatch;reco muon p_{T};",100,0,100);
  fOutput->Add(fh1PtNoMatch);

  fh2MuPtDeltaR = new TH2F("fh2MuPtDeltaR","fh2MuPtDeltaR;muon p_{T};#Delta r",100,0,100,200,0,0.005);
  fOutput->Add(fh2MuPtDeltaR);

  fh2MuPtDeltaRPF = new TH2F("fh2MuPtDeltaRPF","fh2MuPtDeltaRPF;muon p_{T};#Delta r",100,0,100,200,0,0.005);
  fOutput->Add(fh2MuPtDeltaRPF);

  fh2MuPtFracDeltaR = new TH2F("fh2MuPtFracDeltaR","fh2MuPtFracDeltaR;muon p_{T};#Delta r",200,0,2,200,0,0.005);
  fOutput->Add(fh2MuPtFracDeltaR);

  fh2MuPtFracDeltaRPF = new TH2F("fh2MuPtFracDeltaRPF","fh2MuPtFracDeltaRPF;muon p_{T};#Delta r",200,0,2,200,0,0.005);
  fOutput->Add(fh2MuPtFracDeltaRPF);
  
  fh1MuPtGen = new TH1F("fh1MuPtGen","fh1MuPtGen;gen muon p_{T};",100,0,100);
  fOutput->Add(fh1MuPtGen);

  fh1MuPtGenMatch = new TH1F("fh1MuPtGenMatch","fh1MuPtGenMatch;gen muon p_{T};",100,0,100);
  fOutput->Add(fh1MuPtGenMatch);
}
