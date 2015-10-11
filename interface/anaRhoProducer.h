#ifndef anaRhoProducer_h
#define anaRhoProducer_h

#include "TString.h"
#include "TH2F.h"
#include "TH3F.h"

#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"
#include "UserCode/TopFromHeavyIons/interface/lwJetContainer.h"
#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"
#include "UserCode/TopFromHeavyIons/interface/rhoMap.h"

#include <map>

class anaRhoProducer : public anaBaseTask {
   
public:
   anaRhoProducer() {;}
   anaRhoProducer(const char *name, const char *title);
   virtual ~anaRhoProducer() {;}
   void Exec(Option_t *option="");
   void CreateOutputObjects();

   void SetRhoName(TString name)   { fRhoName  = name ; }
   void SetRhoMName(TString name)  { fRhoMName = name ; }
   void SetJetsName(TString name)  { fJetsName = name ; }
   void SetHiEvtName(TString name) { fEvtName  = name ; }
   void SetNExcl(Int_t n)          { fNExcl    = n    ; }
   void SetEtaRangeAll(Double_t min, Double_t max) {fMinEta = min; fMaxEta = max;}
   void SetEtaLimit(Int_t i, Double_t eta) {fMapEtaRanges[i]=eta;}
   
   
 protected:
   Double_t          calcMd(const lwJet *jet);

   //produces
   TString           fRhoName;           //name of rho mapping
   rhoMap           *fRhoMap;            //!rho mapping
   TString           fRhoMName;          //name of rhom mapping
   rhoMap           *fRhoMMap;           //!rhom mapping
   //consumes
   TString           fJetsName;          //name of jet container
   lwJetContainer   *fJetsCont;          //!jet container
   TString           fEvtName;           //name of hi event container
   hiEventContainer *fHiEvent;           //!event container
   //members
   Int_t             fNExcl;             //exclude N leading jets
   Double_t          fMinEta;            //min eta
   Double_t          fMaxEta;            //max eta
   std::map<int,double> fMapEtaRanges;   //eta ranges
    
   TH1F             *fh1NJets;           //!number of jets in event
   TH3F             *fh3PtEtaPhi;        //!jet pt vs eta vs phi
   TH3F             *fh3PtEtaArea;       //!jet pt vs eta vs area
   TH2F             *fh2RhoCent;         //!rho vs cent
   TH2F             *fh2RhoMCent;        //!rhom vs cent
   TH3F             *fh3RhoCentEtaJet;   //!rho vs cent vs eta per jet
   TH3F             *fh3RhoCentEtaBin;   //!rho vs cent vs eta bin
   TH3F             *fh3RhoMCentEtaBin;  //!rho vs cent vs eta bin
   
   ClassDef(anaRhoProducer,1)
};
#endif
