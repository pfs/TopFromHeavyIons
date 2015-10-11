#ifndef lwJet_h
#define lwJet_h

//
// light-weight reconstructed jet
//

#include "TClonesArray.h"

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"

class lwJet : public particleBase {
 public:
  
  lwJet();
  lwJet(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id = -1, Int_t c = 0);
  virtual ~lwJet() {;}
  lwJet(const lwJet& obj); // copy constructor
  lwJet& operator=(const lwJet& other); // assignment

  Double_t    GetArea()                 const { return fArea           ; }
  Int_t       GetNConstituents()        const { return fConstIds.size(); }
  Int_t       GetConstituentId(Int_t i) const { return fConstIds[i]    ; }
  pfParticle *GetConstituent(Int_t i, TClonesArray *c) const { if(!c) return 0; return dynamic_cast<pfParticle*>(c->At(fConstIds[i])); }
  
  void        SetArea(Double_t a)         { fArea = a; }
  void        AddConstituent(Int_t i )    { fConstIds.push_back(i); }
  void        SetRefToParton(Int_t i)     { fRefParton = i;}
  void        SetRefToPartonForB(Int_t i) { fRefPartonForB = i; }  

 protected:
  Double_t          fArea;          //jet area
  std::vector<int>  fConstIds;      //ids of constituents
  Int_t             fRefParton;     //ref to parton
  Int_t             fRefPartonForB; //ref to parton for b
    
  ClassDef(lwJet,1)
};
#endif
