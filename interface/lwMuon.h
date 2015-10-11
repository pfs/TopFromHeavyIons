#ifndef lwMuon_h
#define lwMuon_h

//
// light-weight muon candidate
//

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

class lwMuon : public particleBase {
 public:
  lwMuon();
  lwMuon(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id = -1);
  virtual ~lwMuon() {;}
  lwMuon(const lwMuon& obj); // copy constructor
  lwMuon& operator=(const lwMuon& other); // assignment

  void     SetClosestGen(Int_t i)      { fMatchId1 = i; }
  void     SetClosestPF(Int_t i)       { fMatchId2  = i; }

  Int_t    GetClosestGen()   const     { return fMatchId1; }
  Int_t    GetClosestPF()    const     { return fMatchId2; }
  
 protected:
  
  ClassDef(lwMuon,1)
};
#endif
