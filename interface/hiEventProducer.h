#ifndef hiEventProducer_h
#define hiEventProducer_h

//
// heavy-ion event container producer
//

#include <TNamed.h>
#include <TChain.h>
#include <TString.h>
#include <TBranch.h>

#include "UserCode/TopFromHeavyIons/interface/inputBase.h"
#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"

class hiEventProducer : public inputBase {
 public:
  hiEventProducer();
  hiEventProducer(const char *name);
  virtual ~hiEventProducer() {;}

  void     SetInput(TChain *chain);
  Bool_t   Init();
  Long64_t LoadTree(Long64_t entry);
  Bool_t   InitEventObjects();
  Bool_t   Run(Long64_t entry);
  
  void     SetHIEventContName(TString n) { fhiEventContName = n; }

  const char* GetHIEventContName() const { return fhiEventContName.Data() ; }
  
 protected:
  TString                      fhiEventContName;  // name of HI event container
  hiEventContainer            *fhiEventContainer; //!HI event properties
  Int_t                        fRun;     //!
  Int_t                        fEvt;     //!
  Int_t                        fLumi;    //!
  Float_t                      fVx;      //!
  Float_t                      fVy;      //!
  Float_t                      fVz;      //!
  Int_t                        fHiBin;   //!

  TBranch        *b_run;    //!
  TBranch        *b_evt;    //!
  TBranch        *b_lumi;   //!
  TBranch        *b_vx;     //!
  TBranch        *b_vy;     //!
  TBranch        *b_vz;     //!
  TBranch        *b_hiBin;  //!
  
 private:
  hiEventProducer(const hiEventProducer& obj); // copy constructor
  hiEventProducer& operator=(const hiEventProducer& other); // assignment
  
  ClassDef(hiEventProducer,1)
};
#endif
