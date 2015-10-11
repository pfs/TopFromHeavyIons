#ifndef ForestJets_h
#define ForestJets_h

#define maxJets 20000
#define maxGenJets 20000

class ForestJets {
public :
   ForestJets(){};
   ~ForestJets(){};

   // Declaration of leaf types
   Int_t           evt;
   Float_t         b;
   Int_t           nref;
   Float_t         rawpt[maxJets];   //[nref]
   Float_t         jtpt[maxJets];   //[nref]
   Float_t         jteta[maxJets];   //[nref]
   Float_t         jty[maxJets];   //[nref]
   Float_t         jtphi[maxJets];   //[nref]
   Float_t         jtpu[maxJets];   //[nref]
   Float_t         jtm[maxJets];   //[nref]
   Float_t         discr_fr01[maxJets];   //[nref]
   Float_t         trackMax[maxJets];   //[nref]
   Float_t         trackSum[maxJets];   //[nref]
   Int_t           trackN[maxJets];   //[nref]
   Float_t         trackHardSum[maxJets];   //[nref]
   Int_t           trackHardN[maxJets];   //[nref]
   Float_t         chargedMax[maxJets];   //[nref]
   Float_t         chargedSum[maxJets];   //[nref]
   Int_t           chargedN[maxJets];   //[nref]
   Float_t         chargedHardSum[maxJets];   //[nref]
   Int_t           chargedHardN[maxJets];   //[nref]
   Float_t         photonMax[maxJets];   //[nref]
   Float_t         photonSum[maxJets];   //[nref]
   Int_t           photonN[maxJets];   //[nref]
   Float_t         photonHardSum[maxJets];   //[nref]
   Int_t           photonHardN[maxJets];   //[nref]
   Float_t         neutralMax[maxJets];   //[nref]
   Float_t         neutralSum[maxJets];   //[nref]
   Int_t           neutralN[maxJets];   //[nref]

   Float_t         hcalSum[maxJets];   //[nref]
   Float_t         ecalSum[maxJets];   //[nref]

   Float_t         eMax[maxJets];   //[nref]
   Float_t         eSum[maxJets];   //[nref]
   Int_t           eN[maxJets];   //[nref]
   Float_t         muMax[maxJets];   //[nref]
   Float_t         muSum[maxJets];   //[nref]
   Int_t           muN[maxJets];   //[nref]
   Float_t         matchedPt[maxJets];   //[nref]
   Float_t         matchedR[maxJets];   //[nref]
   Int_t           beamId1;
   Int_t           beamId2;
   Float_t         pthat;
   Float_t         refpt[maxJets];   //[nref]
   Float_t         refeta[maxJets];   //[nref]
   Float_t         refy[maxJets];   //[nref]
   Float_t         refphi[maxJets];   //[nref]
   Float_t         refdphijt[maxJets];   //[nref]
   Float_t         refdrjt[maxJets];   //[nref]
   Float_t         refparton_pt[maxJets];   //[nref]
   Int_t           refparton_flavor[maxJets];   //[nref]
   Int_t           refparton_flavorForB[maxJets];   //[nref]

   Float_t         genChargedSum[maxJets];   //[nref]
   Float_t         genHardSum[maxJets];   //[nref]

   Float_t         signalChargedSum[maxJets];   //[nref]
   Float_t         signalHardSum[maxJets];   //[nref]

   Int_t           subid[maxJets];   //[nref]

   Int_t           ngen;
   Int_t           genmatchindex[maxGenJets];   //[ngen]
   Float_t         genpt[maxGenJets];   //[ngen]
   Float_t         geneta[maxGenJets];   //[ngen]
   Float_t         geny[maxGenJets];   //[ngen]
   Float_t         genphi[maxGenJets];   //[ngen]
   Float_t         gendphijt[maxGenJets];   //[ngen]
   Float_t         gendrjt[maxGenJets];   //[ngen]
   Int_t           gensubid[maxGenJets];   //[ngen]

   Float_t         smpt[maxJets];   //[nref]
   Float_t         fr01Chg[maxJets];   //[nref]
   Float_t         fr01EM[maxJets];   //[nref]
   Float_t         fr01[maxJets];   //[nref]

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
   TBranch        *b_matchedPt;   //!
   TBranch        *b_matchedR;   //!
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
   TBranch        *b_subid;   //!

   TBranch        *b_ngen;   //!
   TBranch        *b_genmatchindex;   //!
   TBranch        *b_genpt;   //!
   TBranch        *b_geneta;   //!
   TBranch        *b_geny;   //!
   TBranch        *b_genphi;   //!
   TBranch        *b_gendphijt;   //!
   TBranch        *b_gendrjt;   //!
   TBranch        *b_gensubid;   //!
   TBranch        *b_smpt;   //!
   TBranch        *b_fr01Chg;   //!
   TBranch        *b_fr01EM;   //!
   TBranch        *b_fr01;   //!

};
#endif
