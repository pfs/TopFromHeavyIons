#ifndef genParticleProducer_h
#define genParticleProducer_h

//
// generated particles producer
//

#include <TNamed.h>
#include <TChain.h>
#include <TString.h>
#include <TClonesArray.h>

#include "UserCode/TopFromHeavyIons/interface/inputBase.h"
#include <UserCode/TopFromHeavyIons/interface/ForestGenParticles.h>

class genParticleProducer : public inputBase {
 public:
  genParticleProducer();
  genParticleProducer(const char *name);
  virtual ~genParticleProducer() {;}

  Bool_t   Init();
  Long64_t LoadTree(Long64_t entry);
  Bool_t   InitEventObjects();
  Bool_t   Run(Long64_t entry);
  
  void     SetGenParticlesName(TString n) { fGenParticlesName = n; }
  void     SetStatus(Int_t i )            { fStatus = i;           }
  void     SetSubevent(Int_t i )          { fSube   = i;           }
  
  const char* GetGenParticlesName() const { return fGenParticlesName.Data() ; }
  
 protected:
  Bool_t   AcceptParticle(Int_t i);
  
  TString                      fGenParticlesName;// name of generated particles branch
  TClonesArray                *fGenParticles;    //!generated particles
  ForestGenParticles           fFGenParts;       //! generated particles in forest tree
  Int_t                        fStatus;          // required status
  Int_t                        fSube;            // required subevent
  
 private:
  genParticleProducer(const genParticleProducer& obj); // copy constructor
  genParticleProducer& operator=(const genParticleProducer& other); // assignment
  
  ClassDef(genParticleProducer,1)
};
#endif
