#include "UserCode/TopFromHeavyIons/interface/anaMET.h"

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"

#include "TLorentzVector.h"

#include "TClass.h"

ClassImp(anaMET)
   
anaMET::anaMET(const char *name, const char *title) 
:anaBaseTask(name,title),
  fEvtName(""),
  fHiEvent(),
  fParticlesName(""),
  fParticles(0x0),
  fMetType(kGen),
  fh2MetCent(),
  fh2SumEtCent(),
  fh3PtEtaPhi()
{

}

//----------------------------------------------------------
void anaMET::Exec(Option_t * /*option*/)
{
   //printf("anaMET executing\n");
   if(!fInitOutput) CreateOutputObjects();

   //Get event properties
   if(!fHiEvent && !fEvtName.IsNull())
     fHiEvent = dynamic_cast<hiEventContainer*>(fEventObjects->FindObject(fEvtName.Data()));
   if(!fHiEvent) return;

   //Get particles from which MET will be calculated
   if(!fParticles && !fParticlesName.IsNull()) {
     fParticles = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fParticlesName.Data()));
     //inheritance check gives crash. Don't know why. Skipping for now. Dangerous
     //     if(fParticles)
     //  if(!CheckInheritance(fParticles,"particleBase")) return;
   }
   
   if(!fParticles) return;

   Double_t cent = fHiEvent->GetCentrality();
   
   TLorentzVector p4(0.,0.,0.,0.);
   Double_t sumEt = 0.;
   for (int i = 0; i < fParticles->GetEntriesFast(); i++) {
     particleBase *p = static_cast<particleBase*>(fParticles->At(i));
     if(!p) {
       Printf("%s ERROR: couldn't get particle",GetName());
       continue;
     }
       
     if(fMetType==kGen || fMetType==kPFRaw) {
       TLorentzVector l = p->GetLorentzVector();
       fh3PtEtaPhi->Fill(l.Pt(),l.Eta(),l.Phi());
       p4+=l;
       sumEt+=l.Et();
     }
     else if(fMetType==kVS) {
       pfParticle *pf = dynamic_cast<pfParticle*>(p);
       if(!pf) {
         Printf("%s ERROR: couldn't cast particle to pfParticle",GetName());
         return;
       }
       TLorentzVector l;
       l.SetPtEtaPhiM(pf->PtVS(),pf->Eta(),pf->Phi(),pf->M());
       fh3PtEtaPhi->Fill(l.Pt(),l.Eta(),l.Phi());
       p4+=l;
       sumEt+=l.Et();
     }
     else if(fMetType==kPuppi) {
       pfParticle *pf = dynamic_cast<pfParticle*>(p);
       if(!pf) {
         Printf("%s ERROR: couldn't cast particle to pfParticle",GetName());
         return;
       }
       TLorentzVector l = pf->GetPuppiWeight()*p->GetLorentzVector();
       fh3PtEtaPhi->Fill(l.Pt(),l.Eta(),l.Phi());
       p4+=l;
       sumEt+=l.Et();
     }
     
   }

   TLorentzVector met = -p4;
   fh2MetCent->Fill(cent,met.Pt());
   fh2SumEtCent->Fill(cent,sumEt);

}

//----------------------------------------------------------
void anaMET::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaMET: fOutput not present");
    return;
  }

  fh2MetCent = new TH2F("fh2MetCent","fh2MetCent;centrality;MET",100,0,100,500,0,500.);
  fOutput->Add(fh2MetCent);

  fh2SumEtCent = new TH2F("fh2SumEtCent","fh2SumEtCent;centrality;sumET",100,0,100,500,0,10000.);
  fOutput->Add(fh2SumEtCent);

  fh3PtEtaPhi = new TH3F("fh3PtEtaPhi","fh3PtEtaPhi;pt;eta;phi",500,0,500,100,-5,5,72,-TMath::Pi(),TMath::Pi());
  fOutput->Add(fh3PtEtaPhi);
  
}
