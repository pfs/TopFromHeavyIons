#ifndef FJJetShape_H
#define FJJetShape_H

// jet shape definitions

#include <vector>
#include <TString.h>
#include "fastjet/config.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/FunctionOfPseudoJet.hh"

#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TVector3.h"
#include "TVector2.h"
using namespace std;

#ifdef FASTJET_VERSION
//________________________________________________________________________
class FJJetShapeMass : public fastjet::FunctionOfPseudoJet<Double32_t>
{
 public:
  virtual std::string description() const{return "jet mass";}
  Double32_t result(const fastjet::PseudoJet &jet) const{ return jet.m();}
};

//________________________________________________________________________
class FJJetShapeGRNum : public fastjet::FunctionOfPseudoJet<Double32_t>
{
 public:
  // default ctor
  FJJetShapeGRNum(Double_t r = 0.2, Double_t wr = 0.04) : fR(r),fDRStep(wr){}
  virtual std::string description() const{return "Numerator angular structure function";}
  //  static Int_t GetBin(Double_t x) {Int_t bin = TMath::FloorNint((x-kxmin)/mdx); return bin;}
  Double32_t result(const fastjet::PseudoJet &jet) const;

 protected:
  Double_t fR;
  Double_t fDRStep;
};

//________________________________________________________________________
class FJJetShapeGRDen : public fastjet::FunctionOfPseudoJet<Double32_t>
{
 public:
  // default ctor
  FJJetShapeGRDen(Double_t r = 0.2, Double_t wr = 0.04) : fR(r),fDRStep(wr){}
  virtual std::string description() const{return "Denominator angular structure function";}
  Double32_t result(const fastjet::PseudoJet &jet) const;

 protected:
  Double_t fR;
  Double_t fDRStep;
};

//________________________________________________________________________
class FJJetShapeAngularity : public fastjet::FunctionOfPseudoJet<Double32_t>{
public:
  virtual std::string description() const{return "Angularity:radial moment";}
  Double32_t result(const fastjet::PseudoJet &jet) const;
};

//________________________________________________________________________
class FJJetShapepTD : public fastjet::FunctionOfPseudoJet<Double32_t>{
 public:
  virtual std::string description() const{return "pTD";}
  Double32_t result(const fastjet::PseudoJet &jet) const;
};

class FJJetShapeConstituent : public fastjet::FunctionOfPseudoJet<Double32_t>{
 public:
  virtual std::string description() const{return "constituents";}
  Double_t result(const fastjet::PseudoJet &jet) const {
    if (!jet.has_constituents())
      return 0; 
    Double_t num = 0.;
    std::vector<fastjet::PseudoJet> constits = jet.constituents();
    num=1.*constits.size();  
    return num;
  }
};

//________________________________________________________________________
class FJJetShapeCircularity : public fastjet::FunctionOfPseudoJet<Double32_t>{
 public:
  virtual std::string description() const{return "circularity denominator";}
  Double32_t result(const fastjet::PseudoJet &jet) const;
};

//________________________________________________________________________
class FJJetShapeSigma2 : public fastjet::FunctionOfPseudoJet<Double32_t>{
 public:
  virtual std::string description() const{return "cms sigma2";}
  Double32_t result(const fastjet::PseudoJet &jet) const;
};

//________________________________________________________________________
class FJJetShapeLeSub : public fastjet::FunctionOfPseudoJet<Double32_t>{
 public:
  virtual std::string description() const{return "leading mins subleading";}
  Double32_t result(const fastjet::PseudoJet &jet) const {
    if (!jet.has_constituents())
      return 0;
    std::vector<fastjet::PseudoJet> constits = jet.constituents();
    std::vector<fastjet::PseudoJet> sortedconstits=sorted_by_pt(constits); 
    if(sortedconstits.size()<2) return 0;
    Double_t num=TMath::Abs(sortedconstits[0].perp()-sortedconstits[1].perp());
    return num;
  }
};

#endif
#endif

