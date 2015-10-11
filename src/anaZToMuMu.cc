#include "UserCode/TopFromHeavyIons/interface/anaZToMuMu.h"
#include "UserCode/TopFromHeavyIons/interface/genParticle.h"

#include "TLorentzVector.h"

#include "TClass.h"

ClassImp(anaZToMuMu)
   
anaZToMuMu::anaZToMuMu(const char *name, const char *title) 
:anaBaseTask(name,title),
  fEvtName(""),
  fHiEvent(),
  fMuonsName(""),
  fMuons(0x0),
  fCheckPid(kFALSE),
  fh1NMuons(),
  fh3CentPtInvMass()
{

}

//----------------------------------------------------------
void anaZToMuMu::Exec(Option_t * /*option*/)
{
   //printf("anaZToMuMu executing\n");
   if(!fInitOutput) CreateOutputObjects();

   //Get event properties
   if(!fHiEvent && !fEvtName.IsNull())
     fHiEvent = dynamic_cast<hiEventContainer*>(fEventObjects->FindObject(fEvtName.Data()));
   if(!fHiEvent) return;

   //Get particles from which MET will be calculated
   if(!fMuons && !fMuonsName.IsNull()) {
     fMuons = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fMuonsName.Data()));
   }
   
   if(!fMuons) return;

   Double_t cent = fHiEvent->GetCentrality();

   Int_t nmuons = fMuons->GetEntriesFast();
   fh1NMuons->Fill(nmuons);
   if(nmuons<2) return;
   
   for (int i = 0; i < fMuons->GetEntriesFast()-1; i++) {
     particleBase *mu1 = static_cast<particleBase*>(fMuons->At(i));
     if(!mu1) {
       Printf("%s ERROR: couldn't get muon",GetName());
       continue;
     }
     if(fCheckPid)
       if(!CheckPid(mu1)) continue;
     
     for (int j = i+1; j < fMuons->GetEntriesFast(); j++) {
       particleBase *mu2 = static_cast<particleBase*>(fMuons->At(j));
       if(!mu2) {
         Printf("%s ERROR: couldn't get muon",GetName());
         continue;
       }
       if(mu1->GetCharge()*mu2->GetCharge()>0) //muons should be of opposite sign
         continue;
       if(fCheckPid)
         if(!CheckPid(mu2)) continue;
   
       
       TLorentzVector l1 = mu1->GetLorentzVector();
       TLorentzVector l2 = mu2->GetLorentzVector();
       TLorentzVector dimu = l1 + l2;

       fh3CentPtInvMass->Fill(cent,dimu.Pt(),dimu.M());

     }//muon 2 loop
   }//muon 1 loop

}

//----------------------------------------------------------
Bool_t anaZToMuMu::CheckPid(particleBase *p) {
  //check if generated particle is muon
  genParticle *gp = dynamic_cast<genParticle*>(p);
  if(!gp) return kFALSE;
  if(abs(gp->GetPID())==13) return kTRUE;
  return kFALSE;
}

//----------------------------------------------------------
void anaZToMuMu::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaZToMuMu: fOutput not present");
    return;
  }

  fh1NMuons = new TH1F("fh1NMuons","fh1NMuons;#it{N}_{muons}",100,0,100.);
  fOutput->Add(fh1NMuons);
  
  fh3CentPtInvMass = new TH3F("fh3CentPtInvMass","fh3CentPtInvMass;centrality;#it{p}_{T};#it{M}_{inv}",100,0,100,200,0,200.,200,0.,200.);
  fOutput->Add(fh3CentPtInvMass);

}
