#ifndef inputBase_h
#define inputBase_h

//
// base container
//

#include <TNamed.h>
#include <TChain.h>
#include <TList.h>

class inputBase : public TNamed {
 public:
  enum InputMode {
    hiForest = 0
  };
  
  inputBase();
  inputBase(const char *name);
  virtual ~inputBase() {;}
  inputBase(const inputBase& obj); // copy constructor
  inputBase& operator=(const inputBase& other); // assignment
  
  virtual void     SetInput(TChain *chain)             { fChain = chain; }
  void     SetInputMode(InputMode m)           { fInputMode = m; }
  void     SetEventObjects(TList *l)           { fEventObjects = l; }
  
  virtual Bool_t   Init();
  virtual Bool_t   Run(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual Bool_t   InitEventObjects() {return kTRUE;}
  virtual void     CreateEventObjects() {;}
  
 protected:
  Bool_t                       fInit;           // init
  InputMode                    fInputMode;      // input source
  TChain                      *fChain;          //! pointer to the input chain
  Int_t                        fCurrent;        //  current file
  TList                       *fEventObjects;   //! pointer to event objects
  
 private:
  
  ClassDef(inputBase,1)
};
#endif
