//
// light-weight generated particle
//

#include "UserCode/TopFromHeavyIons/interface/genParticle.h"

ClassImp(genParticle)

//__________________________________________________________
genParticle::genParticle() :
particleBase(),
  fPid(-1),
  fMomPid(-1)
{
  //default constructor
}

//__________________________________________________________
genParticle::genParticle(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id, Int_t c) :
  particleBase(pt,eta,phi,m,id,c),
  fPid(-1),
  fMomPid(-1)
{
  //standard constructor
}

//__________________________________________________________
genParticle::genParticle(const genParticle &obj) :
  particleBase(obj),
  fPid(obj.fPid),
  fMomPid(obj.fMomPid)
{
  //copy constructor
}

//__________________________________________________________
genParticle &genParticle::operator=(const genParticle &other)
{
  //assignment operator

  if(this!=&other) {
    genParticle::operator=(other);
    fPid     = other.fPid;
    fMomPid  = other.fMomPid;
  }
  return *this;
}

