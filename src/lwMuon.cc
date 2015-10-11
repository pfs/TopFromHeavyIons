//
// light-weight muon candidate
//

#include "UserCode/TopFromHeavyIons/interface/lwMuon.h"

ClassImp(lwMuon)

//__________________________________________________________
lwMuon::lwMuon() :
particleBase()
{
  //default constructor
}

//__________________________________________________________
lwMuon::lwMuon(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id) :
  particleBase(pt,eta,phi,m,id,0)
{
  //standard constructor
}

//__________________________________________________________
lwMuon::lwMuon(const lwMuon &obj) :
  particleBase(obj)
{
  //copy constructor
}

//__________________________________________________________
lwMuon &lwMuon::operator=(const lwMuon &other)
{
  //assignment operator

  if(this!=&other) {
    lwMuon::operator=(other);
  }
  return *this;
}
  
  


