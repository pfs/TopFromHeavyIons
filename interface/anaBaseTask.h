#ifndef anaBaseTask_h
#define anaBaseTask_h

#include "TTask.h"
#include "TList.h"
#include "TClonesArray.h"
#include "TDirectory.h"

class anaBaseTask : public TTask {
   
public:
   anaBaseTask() {;}
   anaBaseTask(const char *name, const char *title);
   virtual ~anaBaseTask() {;}
   void Exec(Option_t *option="");

   void ConnectEventObject(TList *l)   {fEventObjects = l; }
   void ConnectOutput(TList *l)        {fOutput       = l; }

   virtual void CreateOutputObjects();
   
   TList *GetOutput()           const  { return fOutput; }

 protected:
   Bool_t CheckInheritance(TClonesArray *c, TString clsName);
   TList      *fEventObjects;                   //!list with event objects
   Bool_t      fInitOutput;                     //output objects created
   TDirectory *fDir;                            //!output directory
   TList      *fOutput;                         //!list with output objects
   
   ClassDef(anaBaseTask,1)
};
#endif
