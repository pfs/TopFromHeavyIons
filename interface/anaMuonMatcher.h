#ifndef anaMuonMatcher_h
#define anaMuonMatcher_h

#include "TString.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TClonesArray.h"

#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"

//
// geometrical matching of muons to other pfParticleBase object in fMatch
// match info is stored in muons (fMuons)
//

class anaMuonMatcher : public anaBaseTask {
   
public:
  enum matchType {
    kGen = 0,
    kPF  = 1
  };
  
   anaMuonMatcher() {;}
   anaMuonMatcher(const char *name, const char *title);
   virtual ~anaMuonMatcher() {;}
   void Exec(Option_t *option="");
   void CreateOutputObjects();
   
   void SetMuonsName(TString name) { fMuonsName = name ; }
   void SetMatchName(TString name) { fMatchName = name ; }
   void SetMatchType(matchType t)  { fMatchType = t; }
   
 protected:
   TString          fMuonsName;        //name of reconstructed muon array
   TClonesArray    *fMuons;            //!muon array
   TString          fMatchName;        //name of array with objects to match
   TClonesArray    *fMatch;            //!match array
   matchType        fMatchType;        //matching type (defines where to store)
   TH1F            *fh1PtNoMatch;      //!no match
   TH2F            *fh2MuPtDeltaR;     //!muon pt vs deltaR
   TH2F            *fh2MuPtDeltaRPF;   //!muon pt vs deltaR, match to muon pf id
   TH2F            *fh2MuPtFracDeltaR; //!muon pt/match pt vs deltaR
   TH2F            *fh2MuPtFracDeltaRPF; //!muon pt/match pt vs deltaR, match to mu pf id
   TH1F            *fh1MuPtGen;        //!all generated muons
   TH1F            *fh1MuPtGenMatch;   //!reconstructed generated muons
   
   ClassDef(anaMuonMatcher,1)
};
#endif
