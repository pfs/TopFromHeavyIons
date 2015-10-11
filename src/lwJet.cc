//
// light-weight reconstructed jet
//

#include "UserCode/TopFromHeavyIons/interface/lwJet.h"

ClassImp(lwJet)

//__________________________________________________________
lwJet::lwJet() :
particleBase(),
  fArea(-1),
  fConstIds(),
  fRefParton(-1),
  fRefPartonForB(-1)
{
  //default constructor
}

//__________________________________________________________
lwJet::lwJet(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id, Int_t c) :
  particleBase(pt,eta,phi,m,id,c),
  fArea(-1),
  fConstIds(),
  fRefParton(-1),
  fRefPartonForB(-1)
{
  //standard constructor
}

//__________________________________________________________
lwJet::lwJet(const lwJet &obj) :
  particleBase(obj),
  fArea(obj.fArea),
  fConstIds(obj.fConstIds),
  fRefParton(obj.fRefParton),
  fRefPartonForB(obj.fRefPartonForB)
{
  //copy constructor
}

//__________________________________________________________
lwJet &lwJet::operator=(const lwJet &other)
{
  //assignment operator

  if(this!=&other) {
    lwJet::operator=(other);
    fArea          = other.fArea;
    fConstIds      = other.fConstIds;
    fRefParton     = other.fRefParton;
    fRefPartonForB = other.fRefPartonForB; 
  }
  return *this;
}

