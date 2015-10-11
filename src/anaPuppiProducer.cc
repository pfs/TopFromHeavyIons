#include "UserCode/TopFromHeavyIons/interface/anaPuppiProducer.h"

#include "UserCode/TopFromHeavyIons/interface/lwJet.h"
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"

#include "Math/QuantFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"
#include "Math/ProbFunc.h"
#include "TClass.h"
#include "TMath.h"

ClassImp(anaPuppiProducer)
   
anaPuppiProducer::anaPuppiProducer(const char *name, const char *title) 
:anaBaseTask(name,title),
  fConeRadius(0.3),
  fCentBin(-1),
  fNExLJ(2),
  fMinPtExLJ(20.),
  fdRMaxJet(0.4),
  fEvtName(""),
  fHiEvent(),
  fPFParticlesName(""),
  fPFParticles(0x0),
  fJetsName(""),
  fJetsCont(0x0),
  fMapEtaRanges(),
  fh2CentMedianAlpha(),
  fh2CentRMSAlpha()
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

//________________________________________________________________________
anaPuppiProducer::~anaPuppiProducer() {
  // Destructor
 
}

//----------------------------------------------------------
void anaPuppiProducer::Exec(Option_t * /*option*/)
{
  // printf("anaPuppiProducer executing\n");
   if(!fInitOutput) CreateOutputObjects();

   if(!fEventObjects) {
     Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
     return;
   }
   
   //Get event properties
   if(!fHiEvent && !fEvtName.IsNull())
     fHiEvent = dynamic_cast<hiEventContainer*>(fEventObjects->FindObject(fEvtName.Data()));
   if(!fHiEvent) return;
   
   //Get jet container
   if(!fJetsCont && !fJetsName.IsNull())
     fJetsCont = dynamic_cast<lwJetContainer*>(fEventObjects->FindObject(fJetsName.Data()));
   if(!fJetsCont) return;
   TClonesArray *jets = fJetsCont->GetJets();
   if(!jets) return;
      
   //Get pf particles
   if(!fPFParticles && !fPFParticlesName.IsNull()) {
     fPFParticles = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fPFParticlesName.Data()));
   }
   if(!fPFParticles) return;

   //Determine centrality bin
   Double_t cent = fHiEvent->GetCentrality();
   if(cent>=0. && cent<10.)       fCentBin = 0;
   else if(cent>=10. && cent<30.) fCentBin = 1;
   else if(cent>=30. && cent<50.) fCentBin = 2;
   else if(cent>=50. && cent<80.) fCentBin = 3;
   else fCentBin = -1;

   //Find signal jets at detector level
   Int_t nSignalJetsDet = 0;
   // Int_t sigDetIds[999];
   Double_t sigDetPhi[999];
   Double_t sigDetEta[999];
   Int_t nj = TMath::Min(fNExLJ,fJetsCont->GetNJets());
   for(Int_t ij = 0; ij<nj; ij++) {
     lwJet *jet = static_cast<lwJet*>(jets->At(ij));
     if(jet->Pt()>fMinPtExLJ) {
       // sigDetIds[nSignalJetsDet] = ij;
       sigDetPhi[nSignalJetsDet] = jet->Phi();
       sigDetEta[nSignalJetsDet] = jet->Eta();
       nSignalJetsDet++;
     }
   }
   
   //pf candidate loop to calculate alpha for each particle
   for (int i = 0; i < fPFParticles->GetEntriesFast(); i++) {
     pfParticle *p1 = static_cast<pfParticle*>(fPFParticles->At(i));
     Double_t var = 0.;
     for (int j = 0; j < fPFParticles->GetEntriesFast(); j++) {
       if(i==j) continue;
       pfParticle *p2 = static_cast<pfParticle*>(fPFParticles->At(j));
       Double_t dr = p1->DeltaR(p2);
       if(dr>fConeRadius) continue;
       var += p2->Pt() /dr/dr;
     }
     if(var!=0.) var = log(var);
     p1->SetPuppiAlpha(var);
   }//particles loop

   //calculation of median and RMS alpha in eta ranges
   std::map<int,double> fMapMedianAlpha; //median alpha in eta regions
   std::map<int,double> fMapRmsAlpha;    //rms alpha in eta regions
   Int_t neta = (Int_t)fMapEtaRanges.size();
   for(Int_t ieta = 1; ieta<neta; ieta++) {
     static Double_t alphaArrExLJ[9999] = {0.};
     Int_t count = 0;

     Double_t etaMin = fMapEtaRanges.at(ieta)+fConeRadius;
     Double_t etaMax = fMapEtaRanges.at(ieta+1)-fConeRadius;
     
     for (int i = 0; i < fPFParticles->GetEntriesFast(); i++) {
       pfParticle *p1 = static_cast<pfParticle*>(fPFParticles->At(i));
       if(!p1) continue;
       
       if(p1->Eta()>=etaMin && p1->Eta()<etaMax) {       
         //check distance to closest signal jet
         Double_t drDet = 999.;
         for(Int_t is = 0; is<nSignalJetsDet; is++) {
           Double_t dPhi = p1->Phi() - sigDetPhi[is];
           Double_t dEta = p1->Eta() - sigDetEta[is];
           dPhi = TVector2::Phi_mpi_pi(dPhi);
           Double_t dr2tmp = dPhi * dPhi + dEta * dEta;
           Double_t drtmp = 0.;
           if(dr2tmp>0.) drtmp = TMath::Sqrt(dr2tmp);
           if(drtmp<drDet) {
             drDet = drtmp;
           }
         }//signal jets

         //Excluding regions close to leading detector-level jet
         if(drDet>fdRMaxJet) {
           alphaArrExLJ[count] = p1->GetPuppiAlpha();//var;
           count++;
         }
       }//eta selection
     }//particles loop
     
     static Int_t indexes[9999] = {-1};//indexes for sorting
     TMath::Sort(count,alphaArrExLJ,indexes);
     Double_t medAlpha = TMath::Median(count,alphaArrExLJ);

     //Calculate LHS RMS. LHS defined as all entries up to median
     Int_t nias = TMath::FloorNint((Double_t)count/2.);
     Double_t rmsAlpha = 0.;
     for(Int_t ia = nias; ia<count; ia++) { //taking entries starting from nias since sorted from high to low
       Double_t alph = alphaArrExLJ[indexes[ia]];
       if(alph>medAlpha) Printf("WARNING: alph (%f) larger than medAlpha (%f)",alph,medAlpha);
       rmsAlpha += (alph - medAlpha)*(alph - medAlpha);
     }
     if(rmsAlpha>0.) rmsAlpha = TMath::Sqrt(rmsAlpha/((double)nias));

     //Fill histograms
     fh2CentMedianAlpha->Fill(cent,medAlpha);
     fh2CentRMSAlpha->Fill(cent,rmsAlpha);

     fMapMedianAlpha[ieta] = medAlpha;
     fMapRmsAlpha[ieta] = rmsAlpha;
     
   }//eta bins
     
   //Set puppi weight for each particle
   for (int i = 0; i < fPFParticles->GetEntriesFast(); i++) {
     pfParticle *p1 = static_cast<pfParticle*>(fPFParticles->At(i));
     Double_t prob = 1.;
     Int_t etaBin = -1;
     for(Int_t ieta = 1; ieta<neta; ++ieta) {
       Double_t etaMin = fMapEtaRanges.at(ieta);
       Double_t etaMax = fMapEtaRanges.at(ieta+1);
       if(p1->Eta()>=etaMin && p1->Eta()<etaMax)
         etaBin = ieta;
     }
     Double_t medAlpha = fMapMedianAlpha[etaBin];
     Double_t rmsAlpha = fMapRmsAlpha[etaBin];
     if(rmsAlpha>0.) {
       Double_t chii = (p1->GetPuppiAlpha() - medAlpha) * fabs(p1->GetPuppiAlpha() - medAlpha) / rmsAlpha / rmsAlpha;
       prob = ROOT::Math::chisquared_cdf(chii,1.);
     }
     p1->SetPuppiWeight(prob);
   }
}

//----------------------------------------------------------
void anaPuppiProducer::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaPuppiProducer: fOutput not present");
    return;
  }

  fh2CentMedianAlpha = new TH2F("fh2CentMedianAlpha","fh2CentMedianAlpha;centrality (%);med{#alpha}",10,0,100,40,0,20);
  fOutput->Add(fh2CentMedianAlpha);

  fh2CentRMSAlpha = new TH2F("fh2CentRMSAlpha","fh2CentRMSAlpha;centrality (%);RMS{#alpha}",10,0,100,40,0,4);
  fOutput->Add(fh2CentRMSAlpha);
}
