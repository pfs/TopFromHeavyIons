//
// producer of particle flow candidates
//

#include "UserCode/TopFromHeavyIons/interface/pfParticleProducer.h"

ClassImp(pfParticleProducer)

//__________________________________________________________
pfParticleProducer::pfParticleProducer() :
inputBase("pfParticleProducer"),
  fpfParticlesName("pfParticles"),
  fpfParticles(0x0),
  fPFs()
{
  //default constructor
}

//__________________________________________________________
pfParticleProducer::pfParticleProducer(const char *name) :
  inputBase(name),
  fpfParticlesName("pfParticles"),
  fpfParticles(0x0),
  fPFs()
{
  //standard constructor
}

//__________________________________________________________
Bool_t pfParticleProducer::Init() {

  if(!inputBase::Init()) return kFALSE;
  
  if(fInputMode==hiForest) {
    if (fChain->GetBranch("nPFpart"))
      fChain->SetBranchAddress("nPFpart", &fPFs.nPFpart, &fPFs.b_nPFpart);
    if (fChain->GetBranch("pfId"))
      fChain->SetBranchAddress("pfId", fPFs.pfId, &fPFs.b_pfId);
    if (fChain->GetBranch("pfPt"))
      fChain->SetBranchAddress("pfPt", fPFs.pfPt, &fPFs.b_pfPt);
    if (fChain->GetBranch("pfVsPt"))
      fChain->SetBranchAddress("pfVsPt", fPFs.pfVsPt, &fPFs.b_pfVsPt);
    if (fChain->GetBranch("pfEta"))
      fChain->SetBranchAddress("pfEta", fPFs.pfEta, &fPFs.b_pfEta);
    if (fChain->GetBranch("pfPhi"))
      fChain->SetBranchAddress("pfPhi", fPFs.pfPhi, &fPFs.b_pfPhi);
    fInit = kTRUE;
  }
  return kTRUE;
}

//__________________________________________________________
Bool_t pfParticleProducer::InitEventObjects() {
  //Create event objects
  if(!fEventObjects) {
    Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
    return kFALSE;
  } else {
    if(!fEventObjects->FindObject(fpfParticlesName)) {
      fpfParticles = new TClonesArray("pfParticle");
      fpfParticles->SetName(fpfParticlesName);
      fEventObjects->Add(fpfParticles);
    }
  }
  return kTRUE;
}

//__________________________________________________________
Bool_t pfParticleProducer::Run(Long64_t entry) {

  //run analysis
  Long64_t centry = LoadTree(entry);
  if(centry<0) return kFALSE;

  if(!InitEventObjects()) return kFALSE;
 
  //clear array
  fpfParticles->Delete();
  
  //put particles of this event in array
  Int_t pfCount = 0;
  for(Int_t i = 0; i<fPFs.nPFpart; i++) {
    Double_t mass = 0.;
    Int_t charge = 0;
    if(fPFs.pfId[i]==1) { //charged hadron, assume pion mass
      mass   = 0.13957;
      charge = 1;
    }

    pfParticle *pPart = new ((*fpfParticles)[pfCount])
      pfParticle(fPFs.pfPt[i],
                 fPFs.pfEta[i],
                 fPFs.pfPhi[i],
                 mass,
                 fPFs.pfId[i]);
    pPart->SetCharge(charge);
    pPart->SetPtVS(fPFs.pfVsPt[i]);
    ++pfCount;
  }
  return kTRUE;
}

//__________________________________________________________
Long64_t pfParticleProducer::LoadTree(Long64_t entry) {

  //overloaded LoadTree function 
  if(!fChain) {
    Printf("fChain doesn't exist");
    return -5;
  }
  
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Init();
    //  Printf("%lld fCurrent: %d",entry,fCurrent);
  }

  // fChain->SetMakeClass(1);
 
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) {
    Printf("pfParticleProducer: centry smaller than 0");
    return centry;  
  } 

  fChain->GetEntry(entry);
  
  return centry;
}
