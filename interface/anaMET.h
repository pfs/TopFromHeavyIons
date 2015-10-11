#ifndef anaMET_h
#define anaMET_h

#include "TString.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TClonesArray.h"

#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"

#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"

//
// geometrical matching of muons to other pfParticleBase object in fMatch
// match info is stored in muons (fMuons)
//

class anaMET : public anaBaseTask {
   
public:
  enum metType {
    kGen   = 0,
    kGenEm = 1,
    kPFRaw = 2,
    kVS    = 3,
    kPuppi = 4,
    kCS    = 5
  };
  
   anaMET() {;}
   anaMET(const char *name, const char *title);
   virtual ~anaMET() {;}
   void Exec(Option_t *option="");
   void CreateOutputObjects();

   void SetHiEvtName(TString name)     { fEvtName  = name ; }
   void SetParticlesName(TString name) { fParticlesName = name ; }
   void SetMetType(metType t)          { fMetType = t; }
   
 protected:
   TString           fEvtName;              //name of hi event container
   hiEventContainer *fHiEvent;              //!event container
   TString           fParticlesName;        //name of particles
   TClonesArray     *fParticles;            //!muon array
   metType           fMetType;              //matching type (defines where to store)

   
   TH2F            *fh2MetCent;            //!MET vs centrality
   TH2F            *fh2SumEtCent;          //!SumEt vs centrality
   TH3F            *fh3PtEtaPhi;          //!particle pt vs eta vs phi

   ClassDef(anaMET,1)
};
#endif
