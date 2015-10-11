#ifndef lwJetContainer_h
#define lwJetContainer_h

//
// container with reconstructed jets
//

#include <TNamed.h>
#include <TChain.h>
#include <TClonesArray.h>

#include <UserCode/TopFromHeavyIons/interface/lwJet.h>
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"

class lwJetContainer : public TNamed {
 public:
  lwJetContainer();
  lwJetContainer(const char *name);
  virtual ~lwJetContainer() {;}

  Int_t         GetNJets()                 const { return fJets->GetEntriesFast();}
  TClonesArray* GetJets()                  const { return fJets; }
  TClonesArray* GetConstituents()          const { return fConst;}
  pfParticle*   GetConstituentAt(Int_t i)  const { return static_cast<pfParticle*>(fConst->At(i));}
  const char *  GetJetsName()              const { return fJetsName.Data(); }
  Double_t      GetJetRadius()             const { return fRadius;}
  
  void          SetJetsName(TString n)     { fJetsName = n; }
  void          SetJetRadius(Double_t r)   { fRadius   = r; }
  
  Bool_t   Init();
  void     AddJet(lwJet *jet, Int_t pos);
  void     ClearVec()                           { fJets->Delete(); }
  void     ConnectConstituents(TClonesArray *c) { fConst = c;    }
  
 protected:
  TClonesArray          *fJets;     //  container with jets
  TClonesArray          *fConst;    //! container with jet constituents
  TString                fJetsName; //name of jet array
  Double_t               fRadius;   //jet resolution parameter
  
 private:
  lwJetContainer(const lwJetContainer& obj); // copy constructor
  lwJetContainer& operator=(const lwJetContainer& other); // assignment
  
  ClassDef(lwJetContainer,1)
};
#endif
