//
// base particle object
//

#include "TObject.h"
#include "TMath.h"
#include "TVector2.h"

#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

ClassImp(particleBase)

//__________________________________________________________
particleBase::particleBase() :
TObject(),
  fLorentzVector(),
  fId(-1),
  fCharge(0),
  fMatchId1(-1),
  fMatchId2(-1)
{
  //default constructor
}

//__________________________________________________________
particleBase::particleBase(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id, Int_t c) :
  TObject(),
  fLorentzVector(),
  fId(-1),
  fCharge(0),
  fMatchId1(-1),
  fMatchId2(-1)
{
  //standard constructor
  SetPtEtaPhiM(pt,eta,phi,m);
  SetId(id);
  SetCharge(c);
}

//__________________________________________________________
particleBase::particleBase(const particleBase &obj) :
  TObject(obj),
  fLorentzVector(obj.fLorentzVector),
  fId(obj.fId),
  fCharge(obj.fCharge),
  fMatchId1(obj.fMatchId1),
  fMatchId2(obj.fMatchId2)
{
  //copy constructor
}

//__________________________________________________________
particleBase &particleBase::operator=(const particleBase &other)
{
  //assignment operator

  if(this!=&other) {
    TObject::operator=(other);
    fLorentzVector = other.fLorentzVector;
    fId            = other.fId;
    fCharge        = other.fCharge;
    fMatchId1      = other.fMatchId1;
    fMatchId2      = other.fMatchId2;
  }
  return *this;
}

//______________________________________________________________________________
Double_t particleBase::DeltaR(const particleBase* part) const
{
  // Helper function to calculate the distance between two particleBase objects
  Double_t sq = this->DeltaRSquared(part);
  if(sq>0.) return TMath::Sqrt(sq);
  else      return -1.;
}

//______________________________________________________________________________
Double_t particleBase::DeltaRSquared(const particleBase* part) const
{
  // Helper function to calculate the squared distance between two particleBase objects
  Double_t dPhi = Phi() - part->Phi();
  Double_t dEta = Eta() - part->Eta();
  dPhi = TVector2::Phi_mpi_pi(dPhi);
  return dPhi * dPhi + dEta * dEta;
}

//______________________________________________________________________________
Double_t particleBase::DeltaRSquared(const particleBase part) const
{
  // Helper function to calculate the squared distance between two particleBase objects
  Double_t dPhi = Phi() - part.Phi();
  Double_t dEta = Eta() - part.Eta();
  dPhi = TVector2::Phi_mpi_pi(dPhi);
  return dPhi * dPhi + dEta * dEta;
}
