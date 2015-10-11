//
// producer of muon candidates
//

#include "UserCode/TopFromHeavyIons/interface/lwMuonProducer.h"
#include "UserCode/TopFromHeavyIons/interface/genParticle.h"
#include "UserCode/TopFromHeavyIons/interface/lwMuon.h"

ClassImp(lwMuonProducer)

//__________________________________________________________
lwMuonProducer::lwMuonProducer() :
inputBase("lwMuonProducer"),
  flwMuonsRecoName("lwMuonsReco"),
  flwMuonsReco(0x0),
  flwMuonsGeneName("lwMuonsGene"),
  flwMuonsGene(0x0),
  fMuons(),
  fPtMin(16.),
  fMaxEtaAbs(2.1),
  fMaxTrkChi2(4.),
  fMaxGlbChi2(10.),
  fMinNMuHits(1),
  fMinMS(2),
  fMaxDxy(3.),
  fMaxDz(15.),
  fMinNPixHits(1),
  fMinTrkLWM(6)
{
  //default constructor
}

//__________________________________________________________
lwMuonProducer::lwMuonProducer(const char *name) :
  inputBase(name),
  flwMuonsRecoName("lwMuonsReco"),
  flwMuonsReco(0x0),
  flwMuonsGeneName("lwMuonsGene"),
  flwMuonsGene(0x0),
  fMuons(),
  fPtMin(16.),
  fMaxEtaAbs(2.1),
  fMaxTrkChi2(4.),
  fMaxGlbChi2(10.),
  fMinNMuHits(1),
  fMinMS(2),
  fMaxDxy(3.),
  fMaxDz(15.),
  fMinNPixHits(1),
  fMinTrkLWM(6)
{
  //standard constructor
}

//__________________________________________________________
Bool_t lwMuonProducer::Init() {

  if(!inputBase::Init()) return kFALSE;
  
  if(fInputMode==hiForest) {
    if (fChain->GetBranch("Gen_nptl"))
      fChain->SetBranchAddress("Gen_nptl", &fMuons.Gen_nptl, &fMuons.b_Gen_nptl);
    if (fChain->GetBranch("Gen_pid"))
      fChain->SetBranchAddress("Gen_pid", &fMuons.Gen_pid, &fMuons.b_Gen_pid);
    if (fChain->GetBranch("Gen_mom"))
      fChain->SetBranchAddress("Gen_mom", &fMuons.Gen_mom, &fMuons.b_Gen_mom);
    if (fChain->GetBranch("Gen_pt"))
      fChain->SetBranchAddress("Gen_pt", &fMuons.Gen_pt, &fMuons.b_Gen_pt);
    if (fChain->GetBranch("Gen_eta"))
      fChain->SetBranchAddress("Gen_eta", &fMuons.Gen_eta, &fMuons.b_Gen_eta);
    if (fChain->GetBranch("Gen_phi"))
      fChain->SetBranchAddress("Gen_phi", &fMuons.Gen_phi, &fMuons.b_Gen_phi);
    if (fChain->GetBranch("Glb_nptl"))
      fChain->SetBranchAddress("Glb_nptl", &fMuons.Glb_nptl, &fMuons.b_Glb_nptl);
    if (fChain->GetBranch("Glb_charge"))
      fChain->SetBranchAddress("Glb_charge", &fMuons.Glb_charge, &fMuons.b_Glb_charge);
    if (fChain->GetBranch("Glb_pt"))
      fChain->SetBranchAddress("Glb_pt", &fMuons.Glb_pt, &fMuons.b_Glb_pt);
    if (fChain->GetBranch("Glb_eta"))
      fChain->SetBranchAddress("Glb_eta", &fMuons.Glb_eta, &fMuons.b_Glb_eta);
    if (fChain->GetBranch("Glb_phi"))
      fChain->SetBranchAddress("Glb_phi", &fMuons.Glb_phi, &fMuons.b_Glb_phi);
    if (fChain->GetBranch("Glb_dxy"))
      fChain->SetBranchAddress("Glb_dxy", &fMuons.Glb_dxy, &fMuons.b_Glb_dxy);
    if (fChain->GetBranch("Glb_nValMuHits"))
      fChain->SetBranchAddress("Glb_nValMuHits", &fMuons.Glb_nValMuHits, &fMuons.b_Glb_nValMuHits);
    if (fChain->GetBranch("Glb_nValTrkHits"))
      fChain->SetBranchAddress("Glb_nValTrkHits", &fMuons.Glb_nValTrkHits, &fMuons.b_Glb_nValTrkHits);
    if (fChain->GetBranch("Glb_nValPixHits"))
      fChain->SetBranchAddress("Glb_nValPixHits", &fMuons.Glb_nValPixHits, &fMuons.b_Glb_nValPixHits);
    if (fChain->GetBranch("Glb_trkChi2_ndof"))
      fChain->SetBranchAddress("Glb_trkChi2_ndof", &fMuons.Glb_trkChi2_ndof, &fMuons.b_Glb_trkChi2_ndof);
    if (fChain->GetBranch("Glb_nMatchedStations"))
      fChain->SetBranchAddress("Glb_nMatchedStations", &fMuons.Glb_nMatchedStations, &fMuons.b_Glb_nMatchedStations);
    if (fChain->GetBranch("Glb_trkDz"))
      fChain->SetBranchAddress("Glb_trkDz", &fMuons.Glb_trkDz, &fMuons.b_Glb_trkDz);
    if (fChain->GetBranch("Glb_trkLayerWMeas"))
      fChain->SetBranchAddress("Glb_trkLayerWMeas", &fMuons.Glb_trkLayerWMeas, &fMuons.b_Glb_trkLayerWMeas);

    fInit = kTRUE;
  }
  return kTRUE;
}

//__________________________________________________________
Bool_t lwMuonProducer::InitEventObjects() {

  //Create event objects
  if(!fEventObjects) {
    Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
    return kFALSE;
  } else {
    if(!fEventObjects->FindObject(flwMuonsRecoName)) {
      flwMuonsReco = new TClonesArray("lwMuon");
      flwMuonsReco->SetName(flwMuonsRecoName);
      fEventObjects->Add(flwMuonsReco);
    }
    if(!fEventObjects->FindObject(flwMuonsGeneName)) {
      flwMuonsGene = new TClonesArray("genParticle");
      flwMuonsGene->SetName(flwMuonsGeneName);
      fEventObjects->Add(flwMuonsGene);
    }
  }
  
  return kTRUE;
}

//__________________________________________________________
Bool_t lwMuonProducer::Run(Long64_t entry) {

  //overloaded run funtion
  Long64_t centry = LoadTree(entry);
  if(centry<0) return kFALSE;

  if(!InitEventObjects()) return kFALSE;
  
  //clear arrays
  flwMuonsReco->Delete();
  flwMuonsGene->Delete();

  //reconstructed muons
  Int_t muCount = 0;
  for(Int_t i = 0; i<fMuons.Glb_nptl; i++) {
    if(!AcceptMuon(i)) continue;
    lwMuon *mu = new lwMuon(fMuons.Glb_pt[i],
                            fMuons.Glb_eta[i],
                            fMuons.Glb_phi[i],
                            0,
                            i);
    mu->SetCharge(fMuons.Glb_charge[i]);
    (*flwMuonsReco)[muCount] = mu;
    ++muCount;
  }
  //Printf("%d reconstructed muons",muCount);

  //generated muons
  muCount = 0;
  for(Int_t i = 0; i<fMuons.Gen_nptl; i++) {
    genParticle *mu = new genParticle(fMuons.Gen_pt[i],
                                      fMuons.Gen_eta[i],
                                      fMuons.Gen_phi[i],
                                      0,
                                      i);
    mu->SetCharge(fMuons.Gen_pid[i]/abs(fMuons.Gen_pid[i]));
    mu->SetPID(fMuons.Gen_pid[i]);
    mu->SetPIDMom(fMuons.Gen_mom[i]);
    (*flwMuonsGene)[muCount] = mu;
    ++muCount;
  }
  //Printf("%d generated muons",muCount);
  
  return kTRUE;
}

//__________________________________________________________
Bool_t lwMuonProducer::AcceptMuon(Int_t i) {

  //muon quality selection

  if(fMuons.Glb_pt[i]<fPtMin)                     return kFALSE;
  else if(fabs(fMuons.Glb_eta[i])>fMaxEtaAbs)     return kFALSE;
  else if(fMuons.Glb_trkChi2_ndof[i]>fMaxTrkChi2) return kFALSE;
  else if(fMuons.Glb_glbChi2_ndof[i]>fMaxGlbChi2) return kFALSE;
  else if(fMuons.Glb_nValMuHits[i]<fMinNMuHits)   return kFALSE;
  else if(fMuons.Glb_nMatchedStations[i]<fMinMS)  return kFALSE;
  else if(fMuons.Glb_dxy[i]>fMaxDxy)              return kFALSE;
  else if(fMuons.Glb_dz[i]>fMaxDz)                return kFALSE;
  else if(fMuons.Glb_nValPixHits[i]<fMinNPixHits) return kFALSE;
  else if(fMuons.Glb_trkLayerWMeas[i]<fMinTrkLWM) return kFALSE;
  else return kTRUE;
}

//__________________________________________________________
Long64_t lwMuonProducer::LoadTree(Long64_t entry) {

  //overloaded LoadTree function 
  if(!fChain) {
    Printf("fChain doesn't exist");
    return -5;
  }
  
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Init();
    Printf("%lld fCurrent: %d",entry,fCurrent);
  }

  //  fChain->SetMakeClass(1);
 
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) {
    Printf("hiEventProducer: centry smaller than 0");
    return centry;  
  }
  
  fChain->GetEntry(entry);

  return centry;
}
