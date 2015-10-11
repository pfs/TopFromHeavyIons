#ifndef anaPuppiProducer_h
#define anaPuppiProducer_h

#include <map>

#include "TString.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TClonesArray.h"
#include "TRandom3.h"

#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"
#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"
#include "UserCode/TopFromHeavyIons/interface/pfParticle.h"
#include "UserCode/TopFromHeavyIons/interface/lwJetContainer.h"

//
// muon isolation with different methods
//

class anaPuppiProducer : public anaBaseTask {
   
public:
   anaPuppiProducer() {;}
   anaPuppiProducer(const char *name, const char *title);
   virtual ~anaPuppiProducer();// {;}

   void Exec(Option_t *option="");
   void CreateOutputObjects();

   void SetHiEvtName(TString name)    { fEvtName  = name ; }
   void SetPFPartName(TString name)   { fPFParticlesName = name ; }
   void SetJetsName(TString name)     { fJetsName = name ; }

   void SetConeRadius(Double_t r)          { fConeRadius = r; }
   void SetNExLJ(Int_t i)                  { fNExLJ      = i; }
   void SetPtMinExLJ(Double_t m)           { fMinPtExLJ  = m; }
   void SetMinDistToSigJet(Double_t d)     { fdRMaxJet   = d; }
   void SetEtaLimit(Int_t i, Double_t eta) {fMapEtaRanges[i]=eta;}

 protected:
   Double_t          fConeRadius;       //cone radius for isolation
   Int_t             fCentBin;          //centrality bin
   Int_t             fNExLJ;            //maximum number of signal jets
   Double_t          fMinPtExLJ;        //pt min to qualify as signal jet
   Double_t          fdRMaxJet;         //minimum distance to signal jet
   TString           fEvtName;          //name of hi event container
   hiEventContainer *fHiEvent;          //!event container
   TString           fPFParticlesName;  //name of array with pf candidates
   TClonesArray     *fPFParticles;      //!pf candidates array
   TString           fJetsName;         //name of jet array
   lwJetContainer   *fJetsCont;         //!jet container
   std::map<int,double> fMapEtaRanges;  //eta ranges

   TH2F             *fh2CentMedianAlpha; //!centrality vs median alpha
   TH2F             *fh2CentRMSAlpha;    //!centrality vs median alpha
   
   ClassDef(anaPuppiProducer,1)
};
#endif
