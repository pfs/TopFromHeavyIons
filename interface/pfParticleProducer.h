#ifndef pfParticleProducer_h
#define pfParticleProducer_h

//
// particle flow candidate producer
//

#include <TNamed.h>
#include <TChain.h>
#include <TString.h>
#include <TClonesArray.h>

#include "UserCode/TopFromHeavyIons/interface/inputBase.h"
#include <UserCode/TopFromHeavyIons/interface/pfParticle.h>
#include <UserCode/TopFromHeavyIons/interface/ForestPFs.h>

class pfParticleProducer : public inputBase {
 public:
  pfParticleProducer();
  pfParticleProducer(const char *name);
  virtual ~pfParticleProducer() {;}

  Bool_t   Init();
  Long64_t LoadTree(Long64_t entry);
  Bool_t   InitEventObjects();
  Bool_t   Run(Long64_t entry);
  
  void     SetpfParticlesName(TString n) { fpfParticlesName = n; }

  const char* GetpfParticlesName() const { return fpfParticlesName.Data() ; }
  
 protected:
  TString                      fpfParticlesName;  // name of HI event container
  TClonesArray                *fpfParticles;      //!HI event properties
  ForestPFs                    fPFs;              //!PFs in tree

 private:
  pfParticleProducer(const pfParticleProducer& obj); // copy constructor
  pfParticleProducer& operator=(const pfParticleProducer& other); // assignment
  
  ClassDef(pfParticleProducer,1)
};
#endif
