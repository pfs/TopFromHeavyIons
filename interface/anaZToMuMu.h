#ifndef anaZToMuMu_h
#define anaZToMuMu_h

#include "TString.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TClonesArray.h"

#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"
#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"
#include "UserCode/TopFromHeavyIons/interface/particleBase.h"

//
// Z->mu+mu- analysis
//

class anaZToMuMu : public anaBaseTask {
   
public:
   anaZToMuMu() {;}
   anaZToMuMu(const char *name, const char *title);
   virtual ~anaZToMuMu() {;}
   void Exec(Option_t *option="");
   void CreateOutputObjects();

   void SetHiEvtName(TString name)     { fEvtName  = name ; }
   void SetMuonsName(TString name)     { fMuonsName = name ; }
   void SetCheckPid(Bool_t b)          { fCheckPid = b; }
   
 protected:
   Bool_t            CheckPid(particleBase *p);
   
   TString           fEvtName;              //name of hi event container
   hiEventContainer *fHiEvent;              //!event container
   TString           fMuonsName;            //name of particles
   TClonesArray     *fMuons;                //!muon array
   Bool_t            fCheckPid;             //check if candidates are really muons (for simulation)
   TH1F             *fh1NMuons;             //!# selected muons in event
   TH3F             *fh3CentPtInvMass;      //!centrality vs Pt vs inv mass
   
   ClassDef(anaZToMuMu,1)
};
#endif
