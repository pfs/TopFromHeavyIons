#ifndef particleBase_h
#define particleBase_h

#include <TLorentzVector.h>
#include <TObject.h>

class particleBase : public TObject {
 public:
  particleBase();
  particleBase(Double_t pt, Double_t eta, Double_t phi, Double_t m, Int_t id = -1, Int_t c = 0);
  virtual ~particleBase() {;}
  particleBase(const particleBase& obj); // copy constructor
  particleBase& operator=(const particleBase& other); // assignment
  
  void           SetLorentzVector(TLorentzVector pv) { fLorentzVector = pv; }
  void           SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m) { fLorentzVector.SetPtEtaPhiM(pt,eta,phi,m); }
  void           SetId(Int_t id)                     { fId     = id; }
  void           SetCharge(Int_t c)                  { fCharge = c;  }
  void           SetMatchId1(Int_t id)               { fMatchId1 = id; }
  void           SetMatchId2(Int_t id)               { fMatchId2 = id; }

  Double_t       Pt()               const { return fLorentzVector.Pt(); }
  Double_t       Phi()              const { return fLorentzVector.Phi(); }
  Double_t       Eta()              const { return fLorentzVector.Eta(); }
  Double_t       M()                const { return fLorentzVector.M(); }
  TLorentzVector GetLorentzVector() const { return fLorentzVector; }
  Int_t          GetId()            const { return fId; }
  Int_t          GetCharge()        const { return fCharge; }
  Int_t          GetMatchId1()      const { return fMatchId1; }
  Int_t          GetMatchId2()      const { return fMatchId2; }

  Double_t       DeltaR(const particleBase* part) const;
  Double_t       DeltaRSquared(const particleBase* part) const;
  Double_t       DeltaRSquared(const particleBase part) const;
  
 protected:
    TLorentzVector fLorentzVector;
    Int_t          fId;
    Int_t          fCharge;
    Int_t          fMatchId1;
    Int_t          fMatchId2;

    ClassDef(particleBase,1)
};
#endif
