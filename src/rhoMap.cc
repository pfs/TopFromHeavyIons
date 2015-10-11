//
// container with rho/rhom mapping vs eta
//

#include "UserCode/TopFromHeavyIons/interface/rhoMap.h"

using ival = icl::interval<double>;

ClassImp(rhoMap)

//__________________________________________________________
rhoMap::rhoMap() :
TNamed("rhoMap","rhoMap"),
  fMapToIndex(),
  fMapToVal()
{
  //default constructor
}

//__________________________________________________________
rhoMap::rhoMap(const char *name) :
  TNamed(name,name),
  fMapToIndex(),
  fMapToVal()
{
  //standard constructor
}

//__________________________________________________________
double rhoMap::GetValue(double e) const {

  int index = GetIndex(e);
  if(index>0 && index <= (int)fMapToVal.size()) return fMapToVal.at(index);
  else                                          return -1.;
}

//__________________________________________________________
void rhoMap::AddEtaRange(double etaMin, double etaMax, int index, double val) {

  fMapToIndex.add({ival::open(etaMin, etaMax), index}); //create interval
  fMapToIndex.add({etaMin,index}); //include lower border to interval

  fMapToVal[index]=val;            //assign value to interval
}

//__________________________________________________________
void rhoMap::SetValue(int index, double val) {
  if(index>0 && index <= (int)fMapToVal.size())
    fMapToVal[index]=val;
  else
    Printf("WARNING: index does not exist");
}



