#include "UserCode/TopFromHeavyIons/interface/anaMuonIsolation.h"

#include "UserCode/TopFromHeavyIons/interface/lwMuon.h"
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"
#include "UserCode/TopFromHeavyIons/interface/genParticle.h"

#include "TClass.h"
#include "TMath.h"

ClassImp(anaMuonIsolation)
   
anaMuonIsolation::anaMuonIsolation(const char *name, const char *title) 
:anaBaseTask(name,title),
  fIsolationType(kRaw),
  fConeRadius(0.3),
  fOffset(0.05),
  fRandom(new TRandom3(0)),
  fCentBin(-1),
  fEvtName(""),
  fHiEvent(),
  fMuonsName(""),
  fMuons(0x0),
  fPFParticlesName(""),
  fPFParticles(0x0),
  fRhoMapName(""),
  fRhoMap(),
  fRhoMMapName(""),
  fRhoMMap(),
  fMuonsGenName(""),
  fMuonsGen(0x0),
  fh2CentIso(),
  fh2IsoZCone(),
  fh2PtRecoIso(),
  fh2PtGenIso()
{

  fh2IsoZCone = new TH2F*[4];
  fh2PtRecoIso = new TH2F*[4];
  fh2PtGenIso = new TH2F*[4];
  for(Int_t i = 0; i<4; i++) {
    fh2IsoZCone[i] = 0;
    fh2PtRecoIso[i] = 0;
    fh2PtGenIso[i] = 0;
  }

}

//________________________________________________________________________
anaMuonIsolation::~anaMuonIsolation() {
  // Destructor
  delete fRandom;
}

//----------------------------------------------------------
void anaMuonIsolation::Exec(Option_t * /*option*/)
{
   //printf("anaMuonIsolation executing\n");
   if(!fInitOutput) CreateOutputObjects();

   //Get event properties
   if(!fHiEvent && !fEvtName.IsNull())
     fHiEvent = dynamic_cast<hiEventContainer*>(fEventObjects->FindObject(fEvtName.Data()));
   if(!fHiEvent) return;

   if(!fRhoMap && !fRhoMapName.IsNull())
     fRhoMap = dynamic_cast<rhoMap*>(fEventObjects->FindObject(fRhoMapName.Data()));

   if(!fRhoMMap && !fRhoMMapName.IsNull())
     fRhoMMap = dynamic_cast<rhoMap*>(fEventObjects->FindObject(fRhoMMapName.Data()));
   
   //Get muons
   if(!fMuons && !fMuonsName.IsNull()) {
     fMuons = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fMuonsName.Data()));
     //inheritance check gives crash. Don't know why. Skipping for now. Dangerous
     //     if(fMuons)
     //  if(!CheckInheritance(fMuons,"lwMuon")) return;
   }
   if(!fMuons) return;

   //get generated muons
   if(!fMuonsGen && !fMuonsGenName.IsNull()) {
     fMuonsGen = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fMuonsGenName.Data()));
   }

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

   std::vector<pfParticle> partInCone;
   for (int i = 0; i < fMuons->GetEntriesFast(); i++) {
     lwMuon *muon = static_cast<lwMuon*>(fMuons->At(i));
     partInCone.clear();
     Double_t conePt = 0.;
     Double_t ptlead = -1;
     for (int j = 0; j < fPFParticles->GetEntriesFast(); j++) {
       if(muon->GetClosestPF()==j) continue; //exclude itself
       
       pfParticle *pfp = static_cast<pfParticle*>(fPFParticles->At(j));
       Double_t dr = muon->DeltaR(pfp);
       if(fIsolationType==kCS && dr<(fConeRadius+fOffset)) { //collect particles in cone
         partInCone.push_back(*pfp);
       }
       if(dr>fConeRadius) continue;
       if(fIsolationType==kRaw || fIsolationType==kArea) {
         conePt+=pfp->Pt();
         if(pfp->Pt()>ptlead) ptlead = pfp->Pt();
       }
       else if(fIsolationType==kVS)  {
         conePt+=pfp->PtVS();
         if(pfp->PtVS()>ptlead) ptlead = pfp->PtVS();
       }
       else if(fIsolationType==kPuppi)  {
         Double_t pt = pfp->Pt()*pfp->GetPuppiWeight();
         conePt+=pt;
         if(pt>ptlead) ptlead = pt;
       }
       // else if(fIsolationType==kCS) { //collect particles in cone
       //   partInCone.push_back(*pfp);
       // }
     }//pfParticle loop

     if(fIsolationType==kArea) {
       if(fRhoMap)
         conePt-=fRhoMap->GetValue(muon->Eta())*TMath::Pi()*fConeRadius*fConeRadius;
       else
         conePt = 999.;
     }

     if(fIsolationType==kCS) {
       conePt = DoConstituentSubtraction(partInCone,muon->Eta(),muon->Phi(),ptlead);
       //   Printf("conePt: %f  ptlead: %f",conePt,ptlead);
     }
     Double_t iso = 999.;
     if(muon->Pt()>0.) iso = conePt/muon->Pt();
     fh2CentIso->Fill(fHiEvent->GetCentrality(),iso);
     if(fCentBin>=0) {
       Double_t zlead = ptlead/conePt;
       fh2IsoZCone[fCentBin]->Fill(iso,zlead);
       fh2PtRecoIso[fCentBin]->Fill(muon->Pt(),iso);
       if(fMuonsGen) {
         Int_t genid = muon->GetClosestGen();
         if(genid>=0 && genid<fMuonsGen->GetEntriesFast()) {
           genParticle *gen = static_cast<genParticle*>(fMuonsGen->At(genid));
           if(gen) {
             // Double_t dr = muon->DeltaR(gen);
             // Printf("deltaR muon,gen: %f",dr);
             fh2PtGenIso[fCentBin]->Fill(gen->Pt(),iso);
           }
         }
       }
     }
   }//reco muon loop
}

//----------------------------------------------------------
Double_t anaMuonIsolation::DoConstituentSubtraction(std::vector<pfParticle> particles, const Double_t muEta, const Double_t muPhi, Double_t &ptlead) {

  //apply constituent subtraction on particles in cone around muon
  //Code copied and adjusted from ConstituentSubtractor of fastjet contrib package
  if(!fRandom) fRandom = new TRandom3(0); //should already exist

  //--------------------------------------------------
  //construct vector with ghosts in grid around muon axis in eta-phi plane
  //grid size: fConeRadius vs fConeRadius + some extra room (fIOffset)
  Double_t ghostArea = 0.005;
  std::vector<pfParticle> ghosts;
  Double_t gridLength = 2.*(fConeRadius+fOffset);
  Int_t nEta = TMath::FloorNint(gridLength/ghostArea);
  Int_t nPhi = nEta;
  ghostArea = 0.005*0.005;

  Double_t etaMin = muEta - gridLength/2.;
  Double_t phiMin = muPhi - gridLength/2.;
  Double_t etaWidth = gridLength/(Double_t)nEta;
  Double_t phiWidth = gridLength/(Double_t)nPhi;

  Double_t rho = 1e-9;
  if(fRhoMap) rho = fRhoMap->GetValue(muEta);
  Double_t rhom = 0.;
  if(fRhoMMap) rhom = fRhoMMap->GetValue(muEta);

  //create ghost particles (only with fConeRadius from muon position)
  for(Int_t ieta= 0; ieta<nEta; ++ieta) {
    for(Int_t iphi= 0; iphi<nPhi; ++iphi) {
      //pick random eta and phi within grid cell
      Double_t geta = etaMin + (Double_t)ieta*etaWidth + fRandom->Uniform(1.)*etaWidth;
      Double_t gphi = phiMin + (Double_t)iphi*phiWidth + fRandom->Uniform(1.)*phiWidth;

      Double_t dPhi = muPhi - gphi;
      Double_t dEta = muEta - geta;
      dPhi = TVector2::Phi_mpi_pi(dPhi);
      Double_t dr2 = dPhi * dPhi + dEta * dEta;
      Double_t r = TMath::Sqrt(dr2);
      if(r>(fConeRadius+fOffset)) continue;
      
      pfParticle ghost(rho*ghostArea,geta,gphi,rhom*ghostArea);
      ghosts.push_back(ghost);
    }
  }

  //--------------------------------------------------
  // computing and sorting the distances, deltaR
  Double_t alpha = 0.;
  Double_t alpha_times_two=alpha*2.;
  Double_t maxDeltaR = -1.;
  bool use_max_deltaR=false;
  if (maxDeltaR>0.) use_max_deltaR=true;
  Double_t maxDeltaR_squared=pow(maxDeltaR,2);
    
  std::vector<std::pair<double,int> > deltaRs;  // the first element is deltaR, the second element is only the index in the vector used for sorting
  std::vector<int> particle_indices_unsorted;
  std::vector<int> ghost_indices_unsorted;

  for (unsigned int i=0;i<particles.size(); i++) {
    double pt_factor=1.;
    if (fabs(alpha_times_two)>1e-5) pt_factor=pow(particles[i].Pt(),alpha_times_two);
  
    for (unsigned int j=0;j<ghosts.size(); j++) {
      double deltaR_squared = ghosts[j].DeltaRSquared(particles[i])*pt_factor;
      if (!use_max_deltaR || deltaR_squared<=maxDeltaR_squared) {
        particle_indices_unsorted.push_back(i);
        ghost_indices_unsorted.push_back(j);
        int deltaRs_size=deltaRs.size();  // current position
        deltaRs.push_back(std::make_pair(deltaR_squared,deltaRs_size));
      }
    }
  }
  std::sort(deltaRs.begin(),deltaRs.end(),anaMuonIsolation::SortingFunction);
  unsigned long nStoredPairs=deltaRs.size();
  
  //--------------------------------------------------
  // the iterative process. Here, only finding the fractions of pt to be corrected.
  // The actual correction of particles is done later.
  std::vector<double> ghosts_fraction_of_pt(ghosts.size(),1.);
  std::vector<double> particles_fraction_of_pt(particles.size(),1.);
  for (unsigned long iindices=0;iindices<nStoredPairs;++iindices) {
    int particle_index=particle_indices_unsorted[deltaRs[iindices].second];
    int ghost_index=ghost_indices_unsorted[deltaRs[iindices].second];
    
    if (ghosts_fraction_of_pt[ghost_index]>0 && particles_fraction_of_pt[particle_index]>0) {
      double ratio_pt = particles[particle_index].Pt()*particles_fraction_of_pt[particle_index]/ghosts[ghost_index].Pt()/ghosts_fraction_of_pt[ghost_index];
      if (ratio_pt>1) {
        particles_fraction_of_pt[particle_index]*=1-1./ratio_pt;
        ghosts_fraction_of_pt[ghost_index]=-1;
      }
      else {
        ghosts_fraction_of_pt[ghost_index]*=1-ratio_pt;
        particles_fraction_of_pt[particle_index]=-1;
      }
    }
  }

  //--------------------------------------------------
  //Subtract particles and return sum pt
  std::vector<pfParticle> subtracted_particles;
  Double_t sumPt = 0.;
  for (unsigned int i=0;i<particles_fraction_of_pt.size(); i++) {
    if (particles_fraction_of_pt[i]<=0) continue;  // particles with zero pt are not used
    double subtracted_pt=0;
    if (particles_fraction_of_pt[i]>0) subtracted_pt=particles[i].Pt()*particles_fraction_of_pt[i];

    //only take particles in cone (excluding offset)
    Double_t dPhi = muPhi - particles[i].Phi();
    Double_t dEta = muEta - particles[i].Eta();
    dPhi = TVector2::Phi_mpi_pi(dPhi);
    Double_t dr2 = dPhi * dPhi + dEta * dEta;
    if(dr2<(fConeRadius*fConeRadius)) {
      if(subtracted_pt>ptlead) ptlead = subtracted_pt;
      sumPt+=subtracted_pt;
    }
  }
  return sumPt;
}

//----------------------------------------------------------
Bool_t anaMuonIsolation::SortingFunction(std::pair<double,int> i,std::pair<double, int> j){
    return (i.first < j.first);
  }

//----------------------------------------------------------
void anaMuonIsolation::CreateOutputObjects() {

  anaBaseTask::CreateOutputObjects();

  if(!fOutput) {
    Printf("anaMuonIsolation: fOutput not present");
    return;
  }

  fh2CentIso = new TH2F("fh2CentIso","fh2CentIso;centrality (%);p_{T,cone}/p_{T,muon}",100,0,100,600,-1.,5.);
  fOutput->Add(fh2CentIso);

  TString histName = "";
  TString histTitle = "";
  for(Int_t i = 0; i<4; i++) {
    histName = Form("fh2IsoZCone_%d",i);
    histTitle = Form("%s;p_{T,cone}/p_{T,muon};z_{lead,cone}",histName.Data());
    fh2IsoZCone[i] = new TH2F(histName.Data(),histTitle.Data(),600,-1,5,100,0,1.);
    fOutput->Add(fh2IsoZCone[i]);

    histName = Form("fh2PtRecoIso_%d",i);
    histTitle = Form("%s;p_{T,muon,reco};iso",histName.Data());
    fh2PtRecoIso[i] = new TH2F(histName.Data(),histTitle.Data(),100,0.,100.,600,-1,5);
    fOutput->Add(fh2PtRecoIso[i]);

    histName = Form("fh2PtGenIso_%d",i);
    histTitle = Form("%s;p_{T,muon,gen};iso",histName.Data());
    fh2PtGenIso[i] = new TH2F(histName.Data(),histTitle.Data(),100,0.,100.,600,-1,5);
    fOutput->Add(fh2PtGenIso[i]);
  }

}
