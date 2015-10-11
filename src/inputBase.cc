//
// base container
//

#include "UserCode/TopFromHeavyIons/interface/inputBase.h"

ClassImp(inputBase)

//__________________________________________________________
inputBase::inputBase() :
TNamed("inputBase","inputBase"),
  fInit(0),
  fInputMode(hiForest),
  fChain(),
  fCurrent(-1),
  fEventObjects(0x0)
 {
  //default constructor
}

//__________________________________________________________
inputBase::inputBase(const char *name) :
  TNamed(name,name),
  fInit(0),
  fInputMode(hiForest),
  fChain(),
  fEventObjects(0x0)
{
  //standard constructor
}

//__________________________________________________________
inputBase::inputBase(const inputBase &obj) :
  TNamed(obj),
  fInit(obj.fInit),
  fInputMode(obj.fInputMode),
  fChain(obj.fChain)
{
  //copy constructor
}

//__________________________________________________________
inputBase &inputBase::operator=(const inputBase &other)
{
  //assignment operator

  if(this!=&other) {
    TNamed::operator=(other);
    fInit      = other.fInit;
    fInputMode = other.fInputMode;
    fChain     = other.fChain;
  }
  return *this;
}

//__________________________________________________________
Bool_t inputBase::Init() {

  if(!fChain) return kFALSE;
  // fChain->SetMakeClass(1);

  return kTRUE;
}

//__________________________________________________________
Bool_t inputBase::Run(Long64_t entry) {

  if(!fInit) {
    fInit = Init();
    if(!fInit) {
      Printf("%s: inputBase::Init failed",GetName());
      return kFALSE;
    }
  }

  LoadTree(entry);

  return kTRUE;
}

//__________________________________________________________
Long64_t inputBase::LoadTree(Long64_t entry) {

  // Set the environment to read one entry
  if(!fChain) return 0;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) {
    Printf("centry smaller than 0");
    return centry;
  }
  return centry;
}
