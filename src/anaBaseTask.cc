#include "UserCode/TopFromHeavyIons/interface/anaBaseTask.h"

#include "TClass.h"
#include "TDirectory.h"

ClassImp(anaBaseTask)
   
anaBaseTask::anaBaseTask(const char *name, const char *title) 
:TTask(name,title),
  fEventObjects(0),
  fInitOutput(0),
  fDir(0x0),
  fOutput(0)
{

}

//----------------------------------------------------------
void anaBaseTask::Exec(Option_t * /*option*/)
{
  if(!fInitOutput) CreateOutputObjects();
}

//----------------------------------------------------------
void anaBaseTask::CreateOutputObjects() {

  if(!fDir) {
    TString dirName = GetName();
    fDir = new TDirectory(dirName.Data(),dirName.Data());
  }
  fDir->cd();
  if(!fOutput) fOutput = new TList();
  if(!fOutput) {
    Printf("%s: There is a problem. fOutput does not exist",GetName());
    return;
  }
  fOutput->SetName(GetName());
  
  fInitOutput = kTRUE;
}

//----------------------------------------------------------
Bool_t anaBaseTask::CheckInheritance(TClonesArray *c, TString clsName) {

  //check if inheritance is to expected type
  TString objname(c->GetClass()->GetName());
  TClass cls(objname);
  if (!cls.InheritsFrom(clsName)) {
    Printf("%s: Objects of type %s are not inherited from %s!", 
           GetName(), cls.GetName(), clsName.Data()); 
    return kFALSE;
  }
  return kTRUE;
}
