#ifndef topEvt_h
#define topEvt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>

#include "UserCode/TopFromHeavyIons/interface/hiEvt.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class topEvt : public hiEvt {
 public :
  topEvt();
  topEvt(std::vector<std::string> &infnames,int maxEvts=-1,int minCentrality=0, int maxCentrality=200);
  topEvt(TChain *chain);
  virtual ~topEvt();
  
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TChain *tree);
  virtual void     CreateOutputObjects(const char* outname);
  virtual void     Run(const char *outname);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
 protected:
  Int_t maxEvts_;

  Int_t minCentrality_,maxCentrality_;

  //output histos
  TH1F *fPtHat;      
  TH1F *fEventSelection; 

  //muon histos
  TH1F *hist_gen_pt_signal;
  TH1F *hist_gen_pt_bg;
  TH1F *hist_R;
  TH1F *hist_glb_pt_signal;
  TH1F *hist_glb_eta_signal;
  TH1F *hist_glb_pt_signal_pass;
  TH1F *hist_glb_pt_bg;
  TH1F *hist_glb_eta_bg;
  TH1F *hist_glb_pt_bg_pass;
  TGraphAsymmErrors *hist_eff_pt_signal,*hist_eff_pt_bg;
  TH1F *hist_glb_dxy_signal;
  TH1F *hist_glb_dxy_bg;
  TH1F *hist_nmhits_signal;
  TH1F *hist_nmhits_bg;
  TH1F *hist_nthits_signal;
  TH1F *hist_nthits_bg;
  TH1F *hist_nphits_signal;
  TH1F *hist_nphits_bg;
  TH1F *hist_chi_signal;
  TH1F *hist_chi_bg;  
  TH1F *hist_nMS_signal;
  TH1F *hist_nMS_bg;
  TH1F *hist_glb_dz_signal;
  TH1F *hist_glb_dz_bg;
  TH1F *hist_tLWM_signal;
  TH1F *hist_tLWM_bg;
  TH1F *hist_hiBin_signal;
  TH1F *hist_sumchpt;
  TH1F *invariant_mass_histogram; 


  TH1F *fPtJet;       //!
  TH2F *fPtResponse;  //!
  TH1F *fNJets15, *fNJets30, *fNJets40;
  TH1F *fDiscrCSVSimple[2];
  TGraphErrors *csveffgraph[2];
  TGraphErrors *csvpurgraph;

  // Declaration of leaf types
  Int_t           evt;
  Float_t         b;
  Int_t           nref;
  Float_t         rawpt[90];   //[nref]
  Float_t         jtpt[90];   //[nref]
  Float_t         jteta[90];   //[nref]
  Float_t         jty[90];   //[nref]
  Float_t         jtphi[90];   //[nref]
  Float_t         jtpu[90];   //[nref]
  Float_t         jtm[90];   //[nref]
  Float_t         discr_fr01[90];   //[nref]
  Float_t         trackMax[90];   //[nref]
  Float_t         trackSum[90];   //[nref]
  Int_t           trackN[90];   //[nref]
  Float_t         trackHardSum[90];   //[nref]
  Int_t           trackHardN[90];   //[nref]
  Float_t         chargedMax[90];   //[nref]
  Float_t         chargedSum[90];   //[nref]
  Int_t           chargedN[90];   //[nref]
  Float_t         chargedHardSum[90];   //[nref]
  Int_t           chargedHardN[90];   //[nref]
  Float_t         photonMax[90];   //[nref]
  Float_t         photonSum[90];   //[nref]
  Int_t           photonN[90];   //[nref]
  Float_t         photonHardSum[90];   //[nref]
  Int_t           photonHardN[90];   //[nref]
  Float_t         neutralMax[90];   //[nref]
  Float_t         neutralSum[90];   //[nref]
  Int_t           neutralN[90];   //[nref]
  Float_t         hcalSum[90];   //[nref]
  Float_t         ecalSum[90];   //[nref]
  Float_t         eMax[90];   //[nref]
  Float_t         eSum[90];   //[nref]
  Int_t           eN[90];   //[nref]
  Float_t         muMax[90];   //[nref]
  Float_t         muSum[90];   //[nref]
  Int_t           muN[90];   //[nref]
  Float_t         discr_ssvHighEff[90];   //[nref]
  Float_t         discr_ssvHighPur[90];   //[nref]
  Float_t         discr_csvMva[90];   //[nref]
  Float_t         discr_csvSimple[90];   //[nref]
  Float_t         discr_muByIp3[90];   //[nref]
  Float_t         discr_muByPt[90];   //[nref]
  Float_t         discr_prob[90];   //[nref]
  Float_t         discr_probb[90];   //[nref]
  Float_t         discr_tcHighEff[90];   //[nref]
  Float_t         discr_tcHighPur[90];   //[nref]
  Float_t         ndiscr_ssvHighEff[90];   //[nref]
  Float_t         ndiscr_ssvHighPur[90];   //[nref]
  Float_t         ndiscr_csvSimple[90];   //[nref]
  Float_t         ndiscr_muByPt[90];   //[nref]
  Float_t         ndiscr_prob[90];   //[nref]
  Float_t         ndiscr_probb[90];   //[nref]
  Float_t         ndiscr_tcHighEff[90];   //[nref]
  Float_t         ndiscr_tcHighPur[90];   //[nref]
  Float_t         pdiscr_csvSimple[90];   //[nref]
  Float_t         pdiscr_prob[90];   //[nref]
  Float_t         pdiscr_probb[90];   //[nref]
  Int_t           nsvtx[90];   //[nref]
  Int_t           svtxntrk[90];   //[nref]  //number of tracks associated to secondary vertex
  Float_t         svtxdl[90];   //[nref]   //transverse flight distance
  Float_t         svtxdls[90];   //[nref]  //transverse flight distance significance
  Float_t         svtxm[90];   //[nref]    //SV mass
  Float_t         svtxpt[90];   //[nref]
  Int_t           nIPtrk[90];   //[nref]
  Int_t           nselIPtrk[90];   //[nref]
  Int_t           nIP;
  Int_t           ipJetIndex[5593];   //[nIP]
  Float_t         ipPt[5593];   //[nIP]
  Float_t         ipProb0[5593];   //[nIP]
  Float_t         ipProb1[5593];   //[nIP]
  Float_t         ip2d[5593];   //[nIP]
  Float_t         ip2dSig[5593];   //[nIP]
  Float_t         ip3d[5593];   //[nIP]
  Float_t         ip3dSig[5593];   //[nIP]
  Float_t         ipDist2Jet[5593];   //[nIP]
  Float_t         ipDist2JetSig[5593];   //[nIP]
  Float_t         ipClosest2Jet[5593];   //[nIP]
  Float_t         mue[90];   //[nref]
  Float_t         mupt[90];   //[nref]
  Float_t         mueta[90];   //[nref]
  Float_t         muphi[90];   //[nref]
  Float_t         mudr[90];   //[nref]
  Float_t         muptrel[90];   //[nref]
  Int_t           muchg[90];   //[nref]
  Int_t           beamId1;
  Int_t           beamId2;
  Float_t         pthat;
  Float_t         refpt[90];   //[nref]
  Float_t         refeta[90];   //[nref]
  Float_t         refy[90];   //[nref]
  Float_t         refphi[90];   //[nref]
  Float_t         refdphijt[90];   //[nref]
  Float_t         refdrjt[90];   //[nref]
  Float_t         refparton_pt[90];   //[nref]
  Int_t           refparton_flavor[90];   //[nref]
  Int_t           refparton_flavorForB[90];   //[nref]
  Float_t         genChargedSum[90];   //[nref]
  Float_t         genHardSum[90];   //[nref]
  Float_t         signalChargedSum[90];   //[nref]
  Float_t         signalHardSum[90];   //[nref]
  Int_t           ngen;
  Int_t           genmatchindex[7];   //[ngen]
  Float_t         genpt[7];   //[ngen]
  Float_t         geneta[7];   //[ngen]
  Float_t         geny[7];   //[ngen]
  Float_t         genphi[7];   //[ngen]
  Float_t         gendphijt[7];   //[ngen]
  Float_t         gendrjt[7];   //[ngen]

  Int_t n_gen;
  Int_t n_glb;
	Float_t gen_pt[10];
	Float_t gen_eta[10];
	Float_t gen_phi[10];
	Float_t glb_pt[10];
	Float_t glb_eta[10];
	Float_t glb_phi[10];
	Int_t gen_mom[10];

	Float_t glb_dxy[10];
	Float_t glb_dz[10];

	Int_t nmhits[10];
	Int_t nthits[10];
	Int_t nphits[10];
	
	Float_t chi[10];
	
	Int_t nMS[10];
	Int_t tLWM[10];

	//Int_t pfId;
	Int_t nPFpart;
	Float_t pfPt[3000];
	Float_t pfEta[9000];
	Float_t pfPhi[9000];


	Float_t trr[4] = {0.6,0.7,0.8,0.9};
	Double_t efficiency[4];
	Double_t purity[4];
	Float_t sumPt=0;
	


  // List of branches
  TBranch        *b_evt;   //!
  TBranch        *b_b;   //!
  TBranch        *b_nref;   //!
  TBranch        *b_rawpt;   //!
  TBranch        *b_jtpt;   //!
  TBranch        *b_jteta;   //!
  TBranch        *b_jty;   //!
  TBranch        *b_jtphi;   //!
  TBranch        *b_jtpu;   //!
  TBranch        *b_jtm;   //!
  TBranch        *b_discr_fr01;   //!
  TBranch        *b_trackMax;   //!
  TBranch        *b_trackSum;   //!
  TBranch        *b_trackN;   //!
  TBranch        *b_trackHardSum;   //!
  TBranch        *b_trackHardN;   //!
  TBranch        *b_chargedMax;   //!
  TBranch        *b_chargedSum;   //!
  TBranch        *b_chargedN;   //!
  TBranch        *b_chargedHardSum;   //!
  TBranch        *b_chargedHardN;   //!
  TBranch        *b_photonMax;   //!
  TBranch        *b_photonSum;   //!
  TBranch        *b_photonN;   //!
  TBranch        *b_photonHardSum;   //!
  TBranch        *b_photonHardN;   //!
  TBranch        *b_neutralMax;   //!
  TBranch        *b_neutralSum;   //!
  TBranch        *b_neutralN;   //!
  TBranch        *b_hcalSum;   //!
  TBranch        *b_ecalSum;   //!
  TBranch        *b_eMax;   //!
  TBranch        *b_eSum;   //!
  TBranch        *b_eN;   //!
  TBranch        *b_muMax;   //!
  TBranch        *b_muSum;   //!
  TBranch        *b_muN;   //!
  TBranch        *b_discr_ssvHighEff;   //!
  TBranch        *b_discr_ssvHighPur;   //!
  TBranch        *b_discr_csvMva;   //!
  TBranch        *b_discr_csvSimple;   //!
  TBranch        *b_discr_muByIp3;   //!
  TBranch        *b_discr_muByPt;   //!
  TBranch        *b_discr_prob;   //!
  TBranch        *b_discr_probb;   //!
  TBranch        *b_discr_tcHighEff;   //!
  TBranch        *b_discr_tcHighPur;   //!
  TBranch        *b_ndiscr_ssvHighEff;   //!
  TBranch        *b_ndiscr_ssvHighPur;   //!
  TBranch        *b_ndiscr_csvSimple;   //!
  TBranch        *b_ndiscr_muByPt;   //!
  TBranch        *b_ndiscr_prob;   //!
  TBranch        *b_ndiscr_probb;   //!
  TBranch        *b_ndiscr_tcHighEff;   //!
  TBranch        *b_ndiscr_tcHighPur;   //!
  TBranch        *b_pdiscr_csvSimple;   //!
  TBranch        *b_pdiscr_prob;   //!
  TBranch        *b_pdiscr_probb;   //!
  TBranch        *b_nsvtx;   //!
  TBranch        *b_svtxntrk;   //!
  TBranch        *b_svtxdl;   //!
  TBranch        *b_svtxdls;   //!
  TBranch        *b_svtxm;   //!
  TBranch        *b_svtxpt;   //!
  TBranch        *b_nIPtrk;   //!
  TBranch        *b_nselIPtrk;   //!
  TBranch        *b_nIP;   //!
  TBranch        *b_ipJetIndex;   //!
  TBranch        *b_ipPt;   //!
  TBranch        *b_ipProb0;   //!
  TBranch        *b_ipProb1;   //!
  TBranch        *b_ip2d;   //!
  TBranch        *b_ip2dSig;   //!
  TBranch        *b_ip3d;   //!
  TBranch        *b_ip3dSig;   //!
  TBranch        *b_ipDist2Jet;   //!
  TBranch        *b_ipDist2JetSig;   //!
  TBranch        *b_ipClosest2Jet;   //!
  TBranch        *b_mue;   //!
  TBranch        *b_mupt;   //!
  TBranch        *b_mueta;   //!
  TBranch        *b_muphi;   //!
  TBranch        *b_mudr;   //!
  TBranch        *b_muptrel;   //!
  TBranch        *b_muchg;   //!
  TBranch        *b_beamId1;   //!
  TBranch        *b_beamId2;   //!
  TBranch        *b_pthat;   //!
  TBranch        *b_refpt;   //!
  TBranch        *b_refeta;   //!
  TBranch        *b_refy;   //!
  TBranch        *b_refphi;   //!
  TBranch        *b_refdphijt;   //!
  TBranch        *b_refdrjt;   //!
  TBranch        *b_refparton_pt;   //!
  TBranch        *b_refparton_flavor;   //!
  TBranch        *b_refparton_flavorForB;   //!
  TBranch        *b_genChargedSum;   //!
  TBranch        *b_genHardSum;   //!
  TBranch        *b_signalChargedSum;   //!
  TBranch        *b_signalHardSum;   //!
  TBranch        *b_ngen;   //!
  TBranch        *b_genmatchindex;   //!
  TBranch        *b_genpt;   //!
  TBranch        *b_geneta;   //!
  TBranch        *b_geny;   //!
  TBranch        *b_genphi;   //!
  TBranch        *b_gendphijt;   //!
  TBranch        *b_gendrjt;   //!

  TBranch	  *b_n_gen;
  TBranch 	  *b_n_glb;
  TBranch	   *b_gen_pt;
	TBranch 	*b_gen_eta;
	TBranch 	*b_gen_phi;
	TBranch		*b_glb_pt;
	TBranch 	*b_glb_eta;
	TBranch 	*b_glb_phi;
	TBranch		*b_gen_mom;
	TBranch 	*b_glb_dxy;
	TBranch 	*b_glb_dz;
	TBranch 	*b_nmhits;
	TBranch 	*b_nthits;
	TBranch 	*b_nphits;
	TBranch 	*b_chi;
	TBranch 	*b_nMS;
	TBranch 	*b_tLWM;
	
	//TBranch 	*b_pfId;
	TBranch 	*b_nPFpart;
	TBranch		*b_pfPt;
	TBranch 	*b_pfEta;
	TBranch 	*b_pfPhi;

  ClassDef(topEvt,1)
};

#endif

