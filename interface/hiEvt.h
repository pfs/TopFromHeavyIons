//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 22 17:46:40 2015 by ROOT version 5.34/09
// from TTree HiTree/
// found on file: /data/wrk/cms/top/data/PythiaTTbar/HIForest_pythiaTTbar_2.root
//////////////////////////////////////////////////////////

#ifndef hiEvt_h
#define hiEvt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class hiEvt {
 public :
  hiEvt();
  hiEvt(std::vector<std::string> &infnames);
  hiEvt(TChain *tree);
  virtual ~hiEvt();

  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TChain *tree);
  virtual void     CreateOutputObjects(const char* outname);
  virtual void     Run();
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

 protected:
  TFile          *fFileOut; //!output file
  TList          *fOutput;  //!output list
  TChain          *fChain;   //!pointer to the analyzed TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Int_t           run;
  Int_t           evt;
  Int_t           lumi;
  Float_t         vx;
  Float_t         vy;
  Float_t         vz;
  Int_t           hiBin;
  Float_t         hiHF;
  Float_t         hiHFplus;
  Float_t         hiHFminus;
  Float_t         hiHFplusEta4;
  Float_t         hiHFminusEta4;
  Float_t         hiZDC;
  Float_t         hiZDCplus;
  Float_t         hiZDCminus;
  Float_t         hiHFhit;
  Float_t         hiHFhitPlus;
  Float_t         hiHFhitMinus;
  Float_t         hiET;
  Float_t         hiEE;
  Float_t         hiEB;
  Float_t         hiEEplus;
  Float_t         hiEEminus;
  Int_t           hiNpix;
  Int_t           hiNpixelTracks;
  Int_t           hiNtracks;
  Int_t           hiNtracksPtCut;
  Int_t           hiNtracksEtaCut;
  Int_t           hiNtracksEtaPtCut;
  Int_t           hiNevtPlane;
  Float_t         hiEvtPlanes[29];   //[hiNevtPlane]

  // List of branches
  TBranch        *b_run;   //!
  TBranch        *b_evt;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_vx;   //!
  TBranch        *b_vy;   //!
  TBranch        *b_vz;   //!
  TBranch        *b_hiBin;   //!
  TBranch        *b_hiHF;   //!
  TBranch        *b_hiHFplus;   //!
  TBranch        *b_hiHFminus;   //!
  TBranch        *b_hiHFplusEta4;   //!
  TBranch        *b_hiHFminusEta4;   //!
  TBranch        *b_hiZDC;   //!
  TBranch        *b_hiZDCplus;   //!
  TBranch        *b_hiZDCminus;   //!
  TBranch        *b_hiHFhit;   //!
  TBranch        *b_hiHFhitPlus;   //!
  TBranch        *b_hiHFhitMinus;   //!
  TBranch        *b_hiET;   //!
  TBranch        *b_hiEE;   //!
  TBranch        *b_hiEB;   //!
  TBranch        *b_hiEEplus;   //!
  TBranch        *b_hiEEminus;   //!
  TBranch        *b_hiNpix;   //!
  TBranch        *b_hiNpixelTracks;   //!
  TBranch        *b_hiNtracks;   //!
  TBranch        *b_hiNtracksPtCut;   //!
  TBranch        *b_hiNtracksEtaCut;   //!
  TBranch        *b_hiNtracksEtaPtCut;   //!
  TBranch        *b_hiNevtPlane;   //!
  TBranch        *b_hiEvtPlanes;   //!

  ClassDef(hiEvt,1)
};

#endif

