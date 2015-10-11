//
// light-weight particle flow candidate
//

#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"

ClassImp(pfParticle)

//__________________________________________________________
pfParticle::pfParticle() :
particleBase(),
  fPupId(-1),
  fPupAlpha(0),
  fPupWeight(0),
  fPtVS(0.)
{
  //default constructor
}

//__________________________________________________________
pfParticle::pfParticle(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id, Int_t c) :
  particleBase(pt,eta,phi,m,id,c),
  fPupId(-1),
  fPupAlpha(0),
  fPupWeight(0),
  fPtVS(0.)
{
  //standard constructor
}

//__________________________________________________________
pfParticle::pfParticle(const pfParticle &obj) :
  particleBase(obj),
  fPupId(obj.fPupId),
  fPupAlpha(obj.fPupAlpha),
  fPupWeight(obj.fPupWeight),
  fPtVS(obj.fPtVS)
{
  //copy constructor
}

//__________________________________________________________
pfParticle &pfParticle::operator=(const pfParticle &other)
{
  //assignment operator

  if(this!=&other) {
    pfParticle::operator=(other);
    fPupId     = other.fPupId;
    fPupAlpha  = other.fPupAlpha;
    fPupWeight = other.fPupWeight;
    fPtVS      = other.fPtVS;
  }
  return *this;
}
  
  


