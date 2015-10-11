#include "UserCode/TopFromHeavyIons/interface/anaRhoProducer.h"

#include "UserCode/TopFromHeavyIons/interface/lwJet.h"

ClassImp(anaRhoProducer)
   
anaRhoProducer::anaRhoProducer(const char *name, const char *title) 
:anaBaseTask(name,title),
  fRhoName("rhoMap"),
  fRhoMap(0x0),
  fRhoMName("rhoMMap"),
  fRhoMMap(0x0),
  fJetsName(""),
  fJetsCont(),
  fEvtName(""),
  fHiEvent(),
  fNExcl(2),
  fMinEta(-5.),
  fMaxEta(5.),
  fMapEtaRanges(),
  fh3PtEtaPhi(),
  fh3PtEtaArea(),
  fh2RhoCent(),
  fh2RhoMCent(),
  fh3RhoCentEtaJet()
{

  //Set default eta ranges
  //[-5,-3,-2.1,2.1,3,5] -> 5 intervals
  fMapEtaRanges[1] = -5.;
  fMapEtaRanges[2] = -3.;
  fMapEtaRanges[3] = -2.1;
  fMapEtaRanges[4] =  2.1;
  fMapEtaRanges[5] =  3.;
  fMapEtaRanges[6] =  5.;
}

//----------------------------------------------------------
void anaRhoProducer::Exec(Option_t * /*option*/)
{
   //printf("anaRhoProducer executing\n");
   if(!fInitOutput) CreateOutputObjects();

   //create maps
   if(!fRhoMap && !fRhoName.IsNull()) {
     fRhoMap = new rhoMap(fRhoName.Data());
     for(Int_t ieta = 1; ieta<(Int_t)fMapEtaRanges.size(); ieta++)
       fRhoMap->AddEtaRange(fMapEtaRanges.at(ieta),fMapEtaRanges.at(ieta+1),ieta,0.);   
     fEventObjects->Add(fRhoMap);
   }
   if(!fRhoMMap && !fRhoMName.IsNull()) {
     fRhoMMap = new rhoMap(fRhoMName.Data());
     for(Int_t ieta = 1; ieta<(Int_t)fMapEtaRanges.size(); ieta++)
       fRhoMMap->AddEtaRange(fMapEtaRanges.at(ieta),fMapEtaRanges.at(ieta+1),ieta,0.);
     fEventObjects->Add(fRhoMMap);
   }

   //Get event properties
   if(!fHiEvent && !fEvtName.IsNull())
     fHiEvent = dynamic_cast<hiEventContainer*>(fEventObjects->FindObject(fEvtName.Data()));
   if(!fHiEvent) return;
   
   if(!fJetsCont && !fJetsName.IsNull())
     fJetsCont = dynamic_cast<lwJetContainer*>(fEventObjects->FindObject(fJetsName.Data()));
   if(!fJetsCont) return;

   Double_t radius = fJetsCont->GetJetRadius();
   TClonesArray *jets = fJetsCont->GetJets();

   static Double_t rhoVec[999];
   static Double_t rhomVec[999];
   static Double_t etaVec[999];

   Int_t nacc = 0;
   Int_t iexcl = 0;
   for (int i = 0; i < fJetsCont->GetNJets(); i++) {
     lwJet *jet = static_cast<lwJet*>(jets->At(i));
     if(fabs(jet->Pt()-0.)<1e-6) continue; //remove ghosts
     Double_t pt = jet->Pt();
     Double_t eta = jet->Eta();
     Double_t phi = jet->Phi();
     Double_t area = jet->GetArea();
     
     fh3PtEtaPhi->Fill(pt,eta,phi);
     fh3PtEtaArea->Fill(pt,eta,area);

     if(eta<fMinEta || eta>fMaxEta) continue;
     if(iexcl<fNExcl) { iexcl++; continue; }
     
     if(area>0.) {
       rhoVec[nacc] = pt/area;
       Double_t md = calcMd(jet);
       rhomVec[nacc] = md/area;
       etaVec[nacc] = eta;
       ++nacc;

       fh3RhoCentEtaJet->Fill(fHiEvent->GetCentrality(),pt/area,eta);
    }
   }
   fh1NJets->Fill(nacc);

   //calculate rho and rhom
   Double_t rho = 0.;
   Double_t rhom = 0.;
   if(nacc>0) {
     rho = TMath::Median(nacc, rhoVec);
     rhom = TMath::Median(nacc, rhomVec);
   }
   fh2RhoCent->Fill(fHiEvent->GetCentrality(),rho);
   fh2RhoMCent->Fill(fHiEvent->GetCentrality(),rhom);

   //calculate rho and rhom in eta ranges
   Int_t neta = (Int_t)fMapEtaRanges.size();
   for(Int_t ieta = 1; ieta<neta; ieta++) {
     static Double_t rhoVecCur[999] = {0.};
     static Double_t rhomVecCur[999]= {0.};

     Double_t etaMin = fMapEtaRanges.at(ieta)+radius;
     Double_t etaMax = fMapEtaRanges.at(ieta+1)-radius;

     Int_t naccCur = 0;
     for(Int_t i = 0; i<nacc; i++) {
       if(etaVec[i]>=etaMin && etaVec[i]<etaMax) {
         rhoVecCur[naccCur] = rhoVec[i];
         rhomVecCur[naccCur] = rhomVec[i];
         ++naccCur;
       }//eta selection
     }//accepted jet loop
     Double_t rhoCur = TMath::Median(naccCur, rhoVecCur);
     Double_t rhomCur = TMath::Median(naccCur, rhomVecCur);
     fRhoMap->SetValue(ieta,rhoCur);
     fRhoMMap->SetValue(ieta,rhomCur);

     fh3RhoCentEtaBin->Fill(fHiEvent->GetCentrality(),rhoCur,etaMin + 0.5*(etaMax-etaMin));
     fh3RhoMCentEtaBin->Fill(fHiEvent->GetCentrality(),rhomCur,etaMin + 0.5*(etaMax-etaMin));
   }//eta ranges
   
}

//----------------------------------------------------------
void anaRhoProducer::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaRhoProducer: fOutput not present");
    return;
  }

  fh1NJets = new TH1F("fh1NJets","fh1NJets;N_{jets}",500,0,500);
  fOutput->Add(fh1NJets);
  
  fh3PtEtaPhi = new TH3F("fh3PtEtaPhi","fh3PtEtaPhi;pt;eta;phi",500,0,500,100,-5,5,72,-TMath::Pi(),TMath::Pi());
  fOutput->Add(fh3PtEtaPhi);

  fh3PtEtaArea = new TH3F("fh3PtEtaArea","fh3PtEtaArea;pt;eta;A",500,0,500,100,-5,5,100,0,1);
  fOutput->Add(fh3PtEtaArea);

  fh2RhoCent = new TH2F("fh2RhoCent","fh2RhoCent;centrality;#rho",100,0,100,400,0,400);
  fOutput->Add(fh2RhoCent);

  fh2RhoMCent = new TH2F("fh2RhoMCent","fh2RhoMCent;centrality;#rho_{m}",100,0,100,500,0,5);
  fOutput->Add(fh2RhoMCent);

  fh3RhoCentEtaJet = new TH3F("fh3RhoCentEtaJet","fh3RhoCentEtaJet;centrality;#rho_{jet};#eta_{jet}",100,0,100,400,0,400,100,-5.,5.);
  fOutput->Add(fh3RhoCentEtaJet);

  Int_t fgkNCentBins = 100;
  Float_t kMinCent   = 0.;
  Float_t kMaxCent   = 100;
  Double_t *binsCent = new Double_t[fgkNCentBins+1];
  for(Int_t i=0; i<=fgkNCentBins; i++) binsCent[i]=(Double_t)kMinCent + (kMaxCent-kMinCent)/fgkNCentBins*(Double_t)i ;

  Int_t fgkNRhoBins = 500;
  Float_t kMinRho   = 0.;
  Float_t kMaxRho   = 500;
  Double_t *binsRho = new Double_t[fgkNRhoBins+1];
  for(Int_t i=0; i<=fgkNRhoBins; i++) binsRho[i]=(Double_t)kMinRho + (kMaxRho-kMinRho)/fgkNRhoBins*(Double_t)i ;

  Int_t fgkNRhoMBins = 500;
  Float_t kMinRhoM   = 0.;
  Float_t kMaxRhoM   = 5;
  Double_t *binsRhoM = new Double_t[fgkNRhoMBins+1];
  for(Int_t i=0; i<=fgkNRhoMBins; i++) binsRhoM[i]=(Double_t)kMinRhoM + (kMaxRhoM-kMinRhoM)/fgkNRhoMBins*(Double_t)i ;
  
  Int_t fgkNEtaBins = (Int_t)fMapEtaRanges.size()-1;
  Double_t *binsEta = new Double_t[fgkNEtaBins+1];
  for(Int_t i=0; i<=fgkNEtaBins; i++)
    binsEta[i]=fMapEtaRanges.at(i+1);
  
  fh3RhoCentEtaBin = new TH3F("fh3RhoCentEtaBin","fh3RhoCentEtaBin;centrality;#rho;#eta",fgkNCentBins,binsCent,fgkNRhoBins,binsRho,fgkNEtaBins,binsEta);
  fOutput->Add(fh3RhoCentEtaBin);

  fh3RhoMCentEtaBin = new TH3F("fh3RhoMCentEtaBin","fh3RhoMCentEtaBin;centrality;#rho;#eta",fgkNCentBins,binsCent,fgkNRhoMBins,binsRhoM,fgkNEtaBins,binsEta);
  fOutput->Add(fh3RhoMCentEtaBin);

  delete [] binsCent;
  delete [] binsRho;
  delete [] binsRhoM;
  delete [] binsEta;
  
}

//----------------------------------------------------------
Double_t anaRhoProducer::calcMd(const lwJet *jet) {
  //
  //get md as defined in http://arxiv.org/pdf/1211.2811.pdf
  //

  //Loop over the jet constituents
  Double_t sum = 0.;
  Double_t sumPt = 0.;
  for(Int_t i = 0; i<jet->GetNConstituents(); ++i) {
    pfParticle *p = jet->GetConstituent(i,fJetsCont->GetConstituents());
    if(p->Pt()<1e-6) continue; //remove ghosts
    sum += TMath::Sqrt(p->M()*p->M() + p->Pt()*p->Pt()) - p->Pt();
    sumPt+=p->Pt();
  }
  return sum;
}
