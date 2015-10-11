#include "UserCode/TopFromHeavyIons/interface/anaJetQA.h"

#include "UserCode/TopFromHeavyIons/interface/lwJet.h"

ClassImp(anaJetQA)
   
anaJetQA::anaJetQA(const char *name, const char *title) 
:anaBaseTask(name,title),
  fJetsName(""),
  fJetsCont(),
  fh3PtEtaPhi(),
  fh3PtEtaArea()
{

}

//----------------------------------------------------------
void anaJetQA::Exec(Option_t * /*option*/)
{
   //printf("anaJetQA executing\n");
  if(!fInitOutput) CreateOutputObjects();

   if(!fJetsCont && !fJetsName.IsNull())
     fJetsCont = dynamic_cast<lwJetContainer*>(fEventObjects->FindObject(fJetsName.Data()));
   if(!fJetsCont) return;

   TClonesArray *jets = fJetsCont->GetJets();

   Double_t maxPt = 0.;
   Int_t njets = 0;
   for (int i = 0; i < fJetsCont->GetNJets(); i++) {
     lwJet *jet = static_cast<lwJet*>(jets->At(i));
     Double_t pt = jet->Pt();
     Double_t phi = jet->Phi();
     Double_t eta = jet->Eta();
     //      Double_t m = jet->M();
     if(fabs(pt-0.)<1e-6) continue; //remove ghosts
     fh3PtEtaPhi->Fill(pt,eta,phi);
     fh3PtEtaArea->Fill(pt,eta,jet->GetArea());
     if(pt>maxPt) maxPt = pt;
     njets++;
   }
   fh1NJets->Fill(njets);
}

//----------------------------------------------------------
void anaJetQA::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaJetQA: fOutput not present");
    return;
  }

  fh1NJets = new TH1F("fh1NJets","fh1NJets;N_{jets}",500,0,500);
  fOutput->Add(fh1NJets);
  
  fh3PtEtaPhi = new TH3F("fh3PtEtaPhi","fh3PtEtaPhi;pt;eta;phi",500,0,500,100,-5,5,72,-TMath::Pi(),TMath::Pi());
  fOutput->Add(fh3PtEtaPhi);

  fh3PtEtaArea = new TH3F("fh3PtEtaArea","fh3PtEtaArea;pt;eta;A",500,0,500,100,-5,5,100,0,1);
  fOutput->Add(fh3PtEtaArea);
}
