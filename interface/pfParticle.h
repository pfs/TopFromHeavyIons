#ifndef pfParticle_h
#define pfParticle_h

//
// light-weight particle flow candidate
//

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

class pfParticle : public particleBase {
 public:
  pfParticle();
  pfParticle(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id = -1, Int_t c = 0);
  virtual ~pfParticle() {;}
  pfParticle(const pfParticle& obj); // copy constructor
  pfParticle& operator=(const pfParticle& other); // assignment
  
  
  void           SetPuppiId(Int_t id)         { fPupId = id;    }
  void           SetPuppiAlpha(Double_t a)    { fPupAlpha = a;  }
  void           SetPuppiWeight(Double_t w)   { fPupWeight = w; }
  void           SetPtVS(Double_t pt)         { fPtVS  = pt;    }
  
  Int_t          GetPuppiId() const      { return fPupId; }
  Double_t       GetPuppiAlpha() const   { return fPupAlpha; }
  Double_t       GetPuppiWeight() const  { return fPupWeight;}
  Double_t       PtVS()       const      { return fPtVS;  } 

 protected:
  Int_t          fPupId;     //puppi id
  Double_t       fPupAlpha;  //puppi alpha
  Double_t       fPupWeight; //puppi weight
  Double_t       fPtVS;      //subtracted pt from HF-Voronoi algo
  
  ClassDef(pfParticle,1)
};
#endif
