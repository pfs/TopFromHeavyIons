#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>

#include "UserCode/TopFromHeavyIons/interface/FJWrapper.h"
#include "UserCode/TopFromHeavyIons/interface/LWJetProducer.h"
#include <UserCode/TopFromHeavyIons/interface/lwJetContainer.h>
#include <UserCode/TopFromHeavyIons/interface/lwJet.h>

using namespace std;

ClassImp(LWJetProducer)

//__________________________________________________________
LWJetProducer::LWJetProducer() :
inputBase("LWJetProducer"),
  fJetType(kAKT),
  fRadius(0.3),
  fRecombScheme(fastjet::E_scheme),
  fGhostArea(0.005),
  fPtMinConst(0.),
  fjInputs(),
  fjJets(),
  fIsInit(0),
  fConst(),
  fConstName(""),
  flwJetContainer(),
  flwJetContName("jetContainer"),
  fFastJetWrapper("LWJetProducer","LWJetProducer")
{
  //default constructor
}

//__________________________________________________________
LWJetProducer::LWJetProducer(const char *name) :
  inputBase(name),
  fJetType(kAKT),
  fRadius(0.3),
  fRecombScheme(fastjet::E_scheme),
  fGhostArea(0.005),
  fPtMinConst(0.),
  fjInputs(),
  fjJets(),
  fIsInit(0),
  fConst(),
  fConstName(""),
  flwJetContainer(),
  flwJetContName("jetContainer"),
  fFastJetWrapper(name,name)
{
  //standard constructor
}

//__________________________________________________________
Bool_t LWJetProducer::Init() {

  TString name("kt");
  fastjet::JetAlgorithm jalgo(fastjet::kt_algorithm);
  if ((fJetType & kAKT) != 0) {
    name  = "antikt";
    jalgo = fastjet::antikt_algorithm;
  }
  //Printf("Running %s jet finder",name.Data());
    
  // setup fj wrapper
  fFastJetWrapper.SetName(name);
  fFastJetWrapper.SetTitle(name);
  fFastJetWrapper.SetAreaType(fastjet::active_area_explicit_ghosts);
  fFastJetWrapper.SetGhostArea(fGhostArea);
  fFastJetWrapper.SetR(fRadius);
  fFastJetWrapper.SetAlgorithm(jalgo);
  fFastJetWrapper.SetRecombScheme(static_cast<fastjet::RecombinationScheme>(fRecombScheme));

  if(!fEventObjects) {
    Printf("%s: fEventObjects does not exist. Cannot store output",GetName());
    return kFALSE;
  }
  
  //Retrieve event objects
  if(!fConst && !fConstName.IsNull()) {
    fConst = dynamic_cast<TClonesArray*>(fEventObjects->FindObject(fConstName));
    if(!fConst) {
      Printf("%s: couldn't find constituents %s",GetName(),fConstName.Data());
      return kFALSE;
    }
  }

  //Create event objects
  if(!fEventObjects->FindObject(flwJetContName)) {
    flwJetContainer = new lwJetContainer(flwJetContName);
    flwJetContainer->Init();
    flwJetContainer->SetJetRadius(fRadius);
    fEventObjects->Add(flwJetContainer);
  } else {
    Printf("%s: Object with name %s already in event! Returning",GetName(),flwJetContName.Data());
    return kFALSE;
  }

  fIsInit = kTRUE;
  return kTRUE;
}

//__________________________________________________________
Int_t LWJetProducer::FindJets() {

  if(!fIsInit) {
    if(!Init()) return -1;
  }

  //clear
  fFastJetWrapper.Clear();
  fjInputs.clear();
  flwJetContainer->ClearVec();

  flwJetContainer->ConnectConstituents(fConst);

  //collect input particles and pass to fj wrapper
  Int_t npart = fConst->GetEntriesFast();
  fjInputs.reserve(npart);
  
  for (int i = 0; i < npart; i++) {
    pfParticle *fRecoParticle = static_cast<pfParticle*>(fConst->At(i));
    if(fRecoParticle->GetLorentzVector().Pt()<fPtMinConst) continue;

    fFastJetWrapper.AddInputVector(fRecoParticle->GetLorentzVector().Px(),
                                   fRecoParticle->GetLorentzVector().Py(),
                                   fRecoParticle->GetLorentzVector().Pz(),
                                   fRecoParticle->GetLorentzVector().E(),
                                   i);
  }

  if (fFastJetWrapper.GetInputVectors().size() == 0) return 0;

  // run jet finder
  fFastJetWrapper.Run();

  // retrieve fastjet jets and sort according to jet pt
  std::vector<fastjet::PseudoJet> jets_incl = fFastJetWrapper.GetInclusiveJets();
  static Int_t indexes[9999] = {-1};
  GetSortedArray(indexes, jets_incl);

  //loop over jets and store in jet container
  Int_t jetCount = 0;
  for (UInt_t ijet = 0; ijet < jets_incl.size(); ++ijet) {
    Int_t ij = indexes[ijet];
    if(fabs(jets_incl[ij].perp()<1e-6)) continue; //remove pure ghost jets
    lwJet *jet = new lwJet(jets_incl[ij].perp(), jets_incl[ij].eta(), jets_incl[ij].phi(), jets_incl[ij].m());
    jet->SetArea(fFastJetWrapper.GetJetArea(ij));

    // Fill constituent info
    std::vector<fastjet::PseudoJet> constituents(fFastJetWrapper.GetJetConstituents(ij));
    Int_t nc = 0;
    for (UInt_t ic = 0; ic < constituents.size(); ++ic) {
      Int_t uid = constituents[ic].user_index();
      if (uid == -1) continue; //ghost particle
      else {
        jet->AddConstituent(uid);
        nc++;
      }
    }

    if(nc>0) { //only store if not pure ghost jet
      flwJetContainer->AddJet(jet,jetCount);
      ++jetCount;
    }
  }
  //  Printf("Event had %d jets  %d",jetCount,(Int_t)fFastJetWrapper.GetInclusiveJets().size());

  return fFastJetWrapper.GetInclusiveJets().size();
  
}

//_______________________________________________________________
Bool_t LWJetProducer::GetSortedArray(Int_t indexes[], std::vector<fastjet::PseudoJet> array) const
{
  // Get the leading jets.

  static Float_t pt[9999] = {0};

  const Int_t n = (Int_t)array.size();

  if (n < 1)
    return kFALSE;

  for (Int_t i = 0; i < n; i++)
    pt[i] = array[i].perp();

  TMath::Sort(n, pt, indexes);

  return kTRUE;
}
