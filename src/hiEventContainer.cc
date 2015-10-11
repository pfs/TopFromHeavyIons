//
// container with heavy-ion event properties
//

#include "UserCode/TopFromHeavyIons/interface/hiEventContainer.h"

ClassImp(hiEventContainer)

//__________________________________________________________
hiEventContainer::hiEventContainer() :
TNamed("hiEventContainer","hiEventContainer"),
  fRun(-1),
  fEvt(-1),
  fLumi(-1),
  fVx(0.),
  fVy(0.),
  fVz(0.),
  fHiBin(0),
  fCent(0.)
{
  //default constructor
}

//__________________________________________________________
hiEventContainer::hiEventContainer(const char *name) :
  TNamed(name,name),
  fRun(-1),
  fEvt(-1),
  fLumi(-1),
  fVx(0.),
  fVy(0.),
  fVz(0.),
  fHiBin(0),
  fCent(0.)
{
  //standard constructor
}
