//
// producer of particle flow candidates
//

#include "UserCode/TopFromHeavyIons/interface/lwJetFromForestProducer.h"
#include "UserCode/TopFromHeavyIons/interface/lwJet.h"

ClassImp(lwJetFromForestProducer)

//__________________________________________________________
lwJetFromForestProducer::lwJetFromForestProducer() :
inputBase("lwJetFromForestProducer"),
  flwJetContName("flwJetCont"),
  flwJetContainer(0x0),
  fForestJets(),
  fRadius(-1.)
{
  //default constructor
}

//__________________________________________________________
lwJetFromForestProducer::lwJetFromForestProducer(const char *name) :
  inputBase(name),
  flwJetContName("flwJetCont"),
  flwJetContainer(0x0),
  fForestJets(),
  fRadius(-1.)
{
  //standard constructor
}

//__________________________________________________________
Bool_t lwJetFromForestProducer::Init() {

  if(!inputBase::Init()) return kFALSE;
  
  if(fInputMode==hiForest) {
    if (fChain->GetBranch("nref"))
      fChain->SetBranchAddress("nref", &fForestJets.nref, &fForestJets.b_nref);
    if (fChain->GetBranch("rawpt"))
      fChain->SetBranchAddress("rawpt", fForestJets.rawpt, &fForestJets.b_rawpt);
    if (fChain->GetBranch("jtpt"))
      fChain->SetBranchAddress("jtpt", fForestJets.jtpt, &fForestJets.b_jtpt);
    if (fChain->GetBranch("jteta"))
      fChain->SetBranchAddress("jteta", fForestJets.jteta, &fForestJets.b_jteta);
    if (fChain->GetBranch("jty"))
      fChain->SetBranchAddress("jty", fForestJets.jty, &fForestJets.b_jty);
    if (fChain->GetBranch("jtphi"))
      fChain->SetBranchAddress("jtphi", fForestJets.jtphi, &fForestJets.b_jtphi);
    if (fChain->GetBranch("jtpu"))
      fChain->SetBranchAddress("jtpu", fForestJets.jtpu, &fForestJets.b_jtpu);
    if (fChain->GetBranch("jtm"))
      fChain->SetBranchAddress("jtm", fForestJets.jtm, &fForestJets.b_jtm);
    if (fChain->GetBranch("refparton_flavor"))
      fChain->SetBranchAddress("refparton_flavor", fForestJets.refparton_flavor, &fForestJets.b_refparton_flavor);
    if (fChain->GetBranch("refparton_flavorForB"))
      fChain->SetBranchAddress("refparton_flavorForB", fForestJets.refparton_flavorForB, &fForestJets.b_refparton_flavorForB);
    
    fInit = kTRUE;
  }
  return kTRUE;
}

//__________________________________________________________
Bool_t lwJetFromForestProducer::InitEventObjects() {
  //Create event objects
  if(!fEventObjects) {
    Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
    return kFALSE;
  } else {
    if(!fEventObjects->FindObject(flwJetContName)) {
      flwJetContainer = new lwJetContainer(flwJetContName);
      flwJetContainer->Init();
      flwJetContainer->SetJetRadius(fRadius);
      fEventObjects->Add(flwJetContainer);
    }
  }

  return kTRUE;
}

//__________________________________________________________
Bool_t lwJetFromForestProducer::Run(Long64_t entry) {

  //run analysis
  Long64_t centry = LoadTree(entry);
  if(centry<0) return kFALSE;

  if(!InitEventObjects()) return kFALSE;
 
  //clear array
  flwJetContainer->ClearVec();
  
  //put particles of this event in array
  Int_t jetCount = 0;
  for(Int_t i = 0; i<fForestJets.nref; i++) {
    lwJet *jet = new lwJet(fForestJets.jtpt[i],
                           fForestJets.jteta[i],
                           fForestJets.jtphi[i],
                           fForestJets.jtm[i]);
    jet->SetRefToParton(fForestJets.refparton_flavor[i]);
    jet->SetRefToPartonForB(fForestJets.refparton_flavorForB[i]);
    flwJetContainer->AddJet(jet,jetCount);
    ++jetCount;
  }
  return kTRUE;
}

//__________________________________________________________
Long64_t lwJetFromForestProducer::LoadTree(Long64_t entry) {

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
    Printf("lwJetFromForestProducer: centry smaller than 0");
    return centry;  
  } 

  fChain->GetEntry(entry);
  
  return centry;
}
