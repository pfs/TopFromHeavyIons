#include "UserCode/TopFromHeavyIons/interface/hiEvt.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

ClassImp(hiEvt)

//__________________________________________________________
hiEvt::hiEvt() : fFileOut(0),
  fOutput(0), 
  fChain(0)
{
  //Default constructor
}

//__________________________________________________________
hiEvt::hiEvt(std::vector<std::string> &infnames) : fFileOut(0),
						   fOutput(0), 
						   fChain(0) 
{
  //add files to chain
  fChain = new TChain("hiEvtAnalyzer/HiTree");
  for(size_t i=0; i<infnames.size(); i++) fChain->Add(infnames[i].c_str());
}

//__________________________________________________________
hiEvt::~hiEvt()
{
  //Destructor
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

//__________________________________________________________
Int_t hiEvt::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

//__________________________________________________________
Long64_t hiEvt::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

//__________________________________________________________
void hiEvt::Run(const char *outname)
{
  //run
  Init(fChain);
  CreateOutputObjects(outname);
  Loop();

  fFileOut->Write();
  fFileOut->Close();
}

//__________________________________________________________
void hiEvt::Loop()
{
  //Do analysis here
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      // if (Cut(ientry) < 0) continue;
   }
}

//__________________________________________________________
void hiEvt::Init(TChain *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("run", &run);
  fChain->SetBranchAddress("evt", &evt);
  fChain->SetBranchAddress("lumi", &lumi);
  fChain->SetBranchAddress("vx", &vx);
  fChain->SetBranchAddress("vy", &vy);
  fChain->SetBranchAddress("vz", &vz);
  fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
  fChain->SetBranchAddress("hiHF", &hiHF, &b_hiHF);
  fChain->SetBranchAddress("hiHFplus", &hiHFplus, &b_hiHFplus);
  fChain->SetBranchAddress("hiHFminus", &hiHFminus, &b_hiHFminus);
  fChain->SetBranchAddress("hiHFplusEta4", &hiHFplusEta4, &b_hiHFplusEta4);
  fChain->SetBranchAddress("hiHFminusEta4", &hiHFminusEta4, &b_hiHFminusEta4);
  fChain->SetBranchAddress("hiZDC", &hiZDC, &b_hiZDC);
  fChain->SetBranchAddress("hiZDCplus", &hiZDCplus, &b_hiZDCplus);
  fChain->SetBranchAddress("hiZDCminus", &hiZDCminus, &b_hiZDCminus);
  fChain->SetBranchAddress("hiHFhit", &hiHFhit, &b_hiHFhit);
  fChain->SetBranchAddress("hiHFhitPlus", &hiHFhitPlus, &b_hiHFhitPlus);
  fChain->SetBranchAddress("hiHFhitMinus", &hiHFhitMinus, &b_hiHFhitMinus);
  fChain->SetBranchAddress("hiET", &hiET, &b_hiET);
  fChain->SetBranchAddress("hiEE", &hiEE, &b_hiEE);
  fChain->SetBranchAddress("hiEB", &hiEB, &b_hiEB);
  fChain->SetBranchAddress("hiEEplus", &hiEEplus, &b_hiEEplus);
  fChain->SetBranchAddress("hiEEminus", &hiEEminus, &b_hiEEminus);
  fChain->SetBranchAddress("hiNpix", &hiNpix, &b_hiNpix);
  fChain->SetBranchAddress("hiNpixelTracks", &hiNpixelTracks, &b_hiNpixelTracks);
  fChain->SetBranchAddress("hiNtracks", &hiNtracks, &b_hiNtracks);
  fChain->SetBranchAddress("hiNtracksPtCut", &hiNtracksPtCut, &b_hiNtracksPtCut);
  fChain->SetBranchAddress("hiNtracksEtaCut", &hiNtracksEtaCut, &b_hiNtracksEtaCut);
  fChain->SetBranchAddress("hiNtracksEtaPtCut", &hiNtracksEtaPtCut, &b_hiNtracksEtaPtCut);
  fChain->SetBranchAddress("hiNevtPlane", &hiNevtPlane, &b_hiNevtPlane);
  fChain->SetBranchAddress("hiEvtPlanes", hiEvtPlanes, &b_hiEvtPlanes);
  Notify();
}

//__________________________________________________________
Bool_t hiEvt::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TChain in a TChain or when when a new TChain
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

//__________________________________________________________
void hiEvt::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

//__________________________________________________________
Int_t hiEvt::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

//__________________________________________________________
void hiEvt::CreateOutputObjects(const char* outname) {
  //create output objects
  if(!fFileOut) fFileOut = new TFile(outname,"RECREATE");
  if(!fOutput) fOutput = new TList();
}
