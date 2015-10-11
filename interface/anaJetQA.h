#ifndef anaJetQA_h
#define anaJetQA_h

#include "TString.h"
#include "TH3F.h"

#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"
#include "UserCode/TopFromHeavyIons/interface/lwJetContainer.h"

class anaJetQA : public anaBaseTask {
   
public:
   anaJetQA() {;}
   anaJetQA(const char *name, const char *title);
   virtual ~anaJetQA() {;}
   void Exec(Option_t *option="");
   void CreateOutputObjects();
   
   void SetJetsName(TString name) { fJetsName = name ; } 
   
 protected:
   TString          fJetsName;    //name of jet container
   lwJetContainer  *fJetsCont;    //!jet container
   TH1F            *fh1NJets;     //!number of jets in event
   TH3F            *fh3PtEtaPhi;  //!jet pt vs eta vs phi
   TH3F            *fh3PtEtaArea; //!jet pt vs eta vs area
   
   ClassDef(anaJetQA,1)
};
#endif
