#ifndef genParticle_h
#define genParticle_h

//
// light-weight generated particle
//

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

class genParticle : public particleBase {
 public:
  genParticle();
  genParticle(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id = -1, Int_t c = 0);
  virtual ~genParticle() {;}
  genParticle(const genParticle& obj); // copy constructor
  genParticle& operator=(const genParticle& other); // assignment
  
  
  void           SetPID(Int_t id)         { fPid    = id;    }
  void           SetPIDMom(Int_t id)      { fMomPid = id;    }
  
  Int_t          GetPID() const      { return fPid; }
  Int_t          GetPIDMom() const      { return fMomPid; }

 protected:
  Int_t          fPid;       //pid
  Int_t          fMomPid;    //pid mother
  Int_t          fStatus;    //status
  
  ClassDef(genParticle,1)
};
#endif
