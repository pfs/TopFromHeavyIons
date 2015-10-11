#ifndef lwJetFromForestProducer_h
#define lwJetFromForestProducer_h

//
// jet candidates from HI forest producer
//

#include <TNamed.h>
#include <TChain.h>
#include <TString.h>
#include <TClonesArray.h>

#include "UserCode/TopFromHeavyIons/interface/inputBase.h"
#include <UserCode/TopFromHeavyIons/interface/lwJetContainer.h>
#include <UserCode/TopFromHeavyIons/interface/ForestJets.h>

class lwJetFromForestProducer : public inputBase {
 public:
  lwJetFromForestProducer();
  lwJetFromForestProducer(const char *name);
  virtual ~lwJetFromForestProducer() {;}

  Bool_t   Init();
  Long64_t LoadTree(Long64_t entry);
  Bool_t   InitEventObjects();
  Bool_t   Run(Long64_t entry);

  void        SetJetContName(TString n)   { flwJetContName = n ; }
  void        SetRadius(Double_t r)       { fRadius        = r ; }

  const char* GetJetContName() const { return flwJetContName.Data() ; }
  Double_t    GetRadius()      const { return fRadius               ; }
  
 protected:
  TString                      flwJetContName;   // name of jet container
  lwJetContainer              *flwJetContainer;  //!lwJetContainer
  ForestJets                   fForestJets;      //!jets in forest tree
  Double_t                     fRadius;          // the R parameter to use

 private:
  lwJetFromForestProducer(const lwJetFromForestProducer& obj); // copy constructor
  lwJetFromForestProducer& operator=(const lwJetFromForestProducer& other); // assignment
  
  ClassDef(lwJetFromForestProducer,1)
};
#endif
