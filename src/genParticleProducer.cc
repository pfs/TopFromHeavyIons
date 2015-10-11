//
// producer of generated particles
//

#include "UserCode/TopFromHeavyIons/interface/genParticleProducer.h"
#include "UserCode/TopFromHeavyIons/interface/genParticle.h"

ClassImp(genParticleProducer)

//__________________________________________________________
genParticleProducer::genParticleProducer() :
inputBase("genParticleProducer"),
  fGenParticlesName("genParticles"),
  fGenParticles(0x0),
  fFGenParts(),
  fStatus(1),
  fSube(0)
{
  //default constructor
}

//__________________________________________________________
genParticleProducer::genParticleProducer(const char *name) :
  inputBase(name),
  fGenParticlesName("genParticles"),
  fGenParticles(0x0),
  fFGenParts(),
  fStatus(1),
  fSube(0)
{
  //standard constructor
}

//__________________________________________________________
Bool_t genParticleProducer::Init() {

  if(!inputBase::Init()) return kFALSE;

  if(fInputMode==hiForest) {
    // Set branch addresses and branch pointers
    if (fChain->GetBranch("event")) fChain->SetBranchAddress("event", &fFGenParts.event, &fFGenParts.b_event);
    if (fChain->GetBranch("b")) fChain->SetBranchAddress("b", &fFGenParts.b, &fFGenParts.b_b);
    if (fChain->GetBranch("npart")) fChain->SetBranchAddress("npart", &fFGenParts.npart, &fFGenParts.b_npart);
    if (fChain->GetBranch("ncoll")) fChain->SetBranchAddress("ncoll", &fFGenParts.ncoll, &fFGenParts.b_ncoll);
    if (fChain->GetBranch("nhard")) fChain->SetBranchAddress("nhard", &fFGenParts.nhard, &fFGenParts.b_nhard);
    if (fChain->GetBranch("phi0")) fChain->SetBranchAddress("phi0", &fFGenParts.phi0, &fFGenParts.b_phi0);
    if (fChain->GetBranch("scale")) fChain->SetBranchAddress("scale", &fFGenParts.scale, &fFGenParts.b_scale);
    if (fChain->GetBranch("n")) fChain->SetBranchAddress("n", fFGenParts.n, &fFGenParts.b_n);
    if (fChain->GetBranch("ptav")) fChain->SetBranchAddress("ptav", fFGenParts.ptav, &fFGenParts.b_ptav);
    if (fChain->GetBranch("mult")) fChain->SetBranchAddress("mult", &fFGenParts.mult, &fFGenParts.b_mult);
    if (fChain->GetBranch("pt")) fChain->SetBranchAddress("pt", fFGenParts.pt, &fFGenParts.b_pt);
    if (fChain->GetBranch("eta")) fChain->SetBranchAddress("eta", fFGenParts.eta, &fFGenParts.b_eta);
    if (fChain->GetBranch("phi")) fChain->SetBranchAddress("phi", fFGenParts.phi, &fFGenParts.b_phi);
    if (fChain->GetBranch("pdg")) fChain->SetBranchAddress("pdg", fFGenParts.pdg, &fFGenParts.b_pdg);
    if (fChain->GetBranch("chg")) fChain->SetBranchAddress("chg", fFGenParts.chg, &fFGenParts.b_chg);
    if (fChain->GetBranch("sta")) fChain->SetBranchAddress("sta", fFGenParts.sta, &fFGenParts.b_sta);
    if (fChain->GetBranch("sube")) fChain->SetBranchAddress("sube", fFGenParts.sube, &fFGenParts.b_sube);
    if (fChain->GetBranch("vx")) fChain->SetBranchAddress("vx", &fFGenParts.vx, &fFGenParts.b_vx);
    if (fChain->GetBranch("vy")) fChain->SetBranchAddress("vy", &fFGenParts.vy, &fFGenParts.b_vy);
    if (fChain->GetBranch("vz")) fChain->SetBranchAddress("vz", &fFGenParts.vz, &fFGenParts.b_vz);
    if (fChain->GetBranch("vr")) fChain->SetBranchAddress("vr", &fFGenParts.vr, &fFGenParts.b_vr);

    fInit = kTRUE;
  }
  return kTRUE;
}

//__________________________________________________________
Bool_t genParticleProducer::InitEventObjects() {

  //Create event objects
  if(!fEventObjects) {
    Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
    return kFALSE;
  } else {
    if(!fEventObjects->FindObject(fGenParticlesName)) {
      fGenParticles = new TClonesArray("genParticle");
      fGenParticles->SetName(fGenParticlesName);
      fEventObjects->Add(fGenParticles);
    }
  }
  
  return kTRUE;
}

//__________________________________________________________
Bool_t genParticleProducer::Run(Long64_t entry) {

  //overloaded run funtion
  Long64_t centry = LoadTree(entry);
  if(centry<0) return kFALSE;

  if(!InitEventObjects()) return kFALSE;
  
  //clear arrays
  fGenParticles->Delete();

  //generated particles
  int ngen = 0;
  for(Int_t i = 0; i<fFGenParts.mult; i++) {
    if(!AcceptParticle(i)) continue;
    genParticle *gp = new genParticle(fFGenParts.pt[i],
                                      fFGenParts.eta[i],
                                      fFGenParts.phi[i],
                                      0,
                                      i);
    gp->SetCharge(fFGenParts.pdg[i]/abs(fFGenParts.pdg[i]));
    gp->SetPID(fFGenParts.pdg[i]);
    gp->SetPIDMom(0);
    (*fGenParticles)[ngen] = gp;
    ++ngen;
  }
  
  return kTRUE;
}

//__________________________________________________________
Bool_t genParticleProducer::AcceptParticle(Int_t i) {

  //gen particle selection

  if(fFGenParts.sta[i]!=fStatus)                  return kFALSE;
  if(fFGenParts.sube[i]!=fSube)                   return kFALSE;
  
  else return kTRUE;
}

//__________________________________________________________
Long64_t genParticleProducer::LoadTree(Long64_t entry) {

  //overloaded LoadTree function 
  if(!fChain) {
    Printf("fChain doesn't exist");
    return -5;
  }
  
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Init();
  }

  //  fChain->SetMakeClass(1);
 
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) {
    Printf("genParticleProducer: centry smaller than 0");
    return centry;  
  }
  
  fChain->GetEntry(entry);

  return centry;
}
