#ifndef rhoMap_h
#define rhoMap_h

//
// container with rho/rhom mapping vs eta
//

#include <map>
#include <boost/icl/interval_map.hpp>

#include <TNamed.h>

namespace icl = boost::icl;

class rhoMap : public TNamed {
 public:
  rhoMap();
  rhoMap(const char *name);
  virtual ~rhoMap() {;}

  Int_t    GetIndex(double e) const {return fMapToIndex(e);}
  Double_t GetValue(double e) const;// {return fMapToVal.at(fMapToIndex(e));}
  
  icl::interval_map<double,int> GetMapToIndex() const {return fMapToIndex;}
  std::map<int,double>          GetMapToValue() const {return fMapToVal;}

  void     SetValue(int index, double val);
  void     AddEtaRange(double etaMin, double etaMax, int index, double val);
  
 protected:
  icl::interval_map<double, int> fMapToIndex;
  std::map<int,double>           fMapToVal;

 private:
  rhoMap(const rhoMap& obj); // copy constructor
  rhoMap& operator=(const rhoMap& other); // assignment

  ClassDef(rhoMap,1)
};
#endif
