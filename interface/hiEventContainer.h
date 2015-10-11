#ifndef hiEventContainer_h
#define hiEventContainer_h

//
// heavy-ion event container: hi event properties
//

#include <TNamed.h>
#include <TChain.h>

class hiEventContainer : public TNamed {
 public:
  hiEventContainer();
  hiEventContainer(const char *name);
  virtual ~hiEventContainer() {;}

  void     SetRun(Int_t r)                     { fRun   = r  ; }
  void     SetEvent(Int_t e)                   { fEvt   = e  ; }
  void     SetLumi(Int_t l)                    { fLumi  = l  ; }
  void     SetVx(Float_t vx)                   { fVx    = vx ; }
  void     SetVy(Float_t vy)                   { fVy    = vy ; }
  void     SetVz(Float_t vz)                   { fVz    = vz ; }
  void     SetHiBin(Int_t b)                   { fHiBin = b  ; fCent = (Double_t)fHiBin/2.;}

  Int_t    GetRun()        const               { return fRun;  }
  Int_t    GetEvent()      const               { return fEvt;  }
  Int_t    GetLumi()       const               { return fLumi; }
  Float_t  GetVx()         const               { return fVx;   }
  Float_t  GetVy()         const               { return fVy;   }
  Float_t  GetVz()         const               { return fVz;   }
  Int_t    GetHiBin()      const               { return fHiBin;}
  Double_t GetCentrality() const               { return fCent; }
    
 
 protected:
  Int_t                        fRun;     //!
  Int_t                        fEvt;     //!
  Int_t                        fLumi;    //!
  Float_t                      fVx;      //!
  Float_t                      fVy;      //!
  Float_t                      fVz;      //!
  Int_t                        fHiBin;   //!
  Double_t                     fCent;

 private:
  hiEventContainer(const hiEventContainer& obj); // copy constructor
  hiEventContainer& operator=(const hiEventContainer& other); // assignment
  
  ClassDef(hiEventContainer,1)
};
#endif
