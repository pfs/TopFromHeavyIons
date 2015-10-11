#ifndef ForestMuons_h
#define ForestMuons_h

#define maxForestMuons 10

class ForestMuons {
public :
   ForestMuons(){};
   ~ForestMuons(){};

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Lumi;
   Int_t           CentBin;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           Gen_nptl;
   Int_t           Gen_pid[maxForestMuons];   //[Gen_nptl]
   Int_t           Gen_mom[maxForestMuons];   //[Gen_nptl] pid mother
   Int_t           Gen_status[maxForestMuons];   //[Gen_nptl]
   Float_t         Gen_p[maxForestMuons];   //[Gen_nptl]
   Float_t         Gen_pt[maxForestMuons];   //[Gen_nptl]
   Float_t         Gen_eta[maxForestMuons];   //[Gen_nptl]
   Float_t         Gen_phi[maxForestMuons];   //[Gen_nptl]
   Int_t           Glb_nptl;
   Int_t           Glb_charge[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_p[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_pt[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_eta[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_phi[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_dxy[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_dz[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_nValMuHits[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_nValTrkHits[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_nValPixHits[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_trkLayerWMeas[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_nMatchedStations[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_nTrkFound[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_glbChi2_ndof[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_trkChi2_ndof[maxForestMuons];   //[Glb_nptl]
   Int_t           Glb_pixLayerWMeas[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_trkDxy[maxForestMuons];   //[Glb_nptl]
   Float_t         Glb_trkDz[maxForestMuons];   //[Glb_nptl]
   Int_t           Sta_nptl;
   Int_t           Sta_charge[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_p[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_pt[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_eta[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_phi[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_dxy[maxForestMuons];   //[Sta_nptl]
   Float_t         Sta_dz[maxForestMuons];   //[Sta_nptl]
   Int_t           Glb_isArbitrated[maxForestMuons];   //[Glb_nptl]
   Int_t           Di_npair;
   Float_t         Di_vProb[maxForestMuons];   //[Di_npair]
   Float_t         Di_mass[maxForestMuons];   //[Di_npair]
   Float_t         Di_e[maxForestMuons];   //[Di_npair]
   Float_t         Di_pt[maxForestMuons];   //[Di_npair]
   Float_t         Di_pt1[maxForestMuons];   //[Di_npair]
   Float_t         Di_pt2[maxForestMuons];   //[Di_npair]
   Float_t         Di_eta[maxForestMuons];   //[Di_npair]
   Float_t         Di_eta1[maxForestMuons];   //[Di_npair]
   Float_t         Di_eta2[maxForestMuons];   //[Di_npair]
   Float_t         Di_phi[maxForestMuons];   //[Di_npair]
   Float_t         Di_phi1[maxForestMuons];   //[Di_npair]
   Float_t         Di_phi2[maxForestMuons];   //[Di_npair]
   Int_t           Di_charge1[maxForestMuons];   //[Di_npair]
   Int_t           Di_charge2[maxForestMuons];   //[Di_npair]
   Int_t           Di_isArb1[maxForestMuons];   //[Di_npair]
   Int_t           Di_isArb2[maxForestMuons];   //[Di_npair]
   Float_t         Di_nTrkHit1[maxForestMuons];   //[Di_npair]
   Float_t         Di_nTrkHit2[maxForestMuons];   //[Di_npair]
   Float_t         Di_trkChi2_1[maxForestMuons];   //[Di_npair]
   Float_t         Di_trkChi2_2[maxForestMuons];   //[Di_npair]
   Float_t         Di_glbChi2_1[maxForestMuons];   //[Di_npair]
   Float_t         Di_glbChi2_2[maxForestMuons];   //[Di_npair]
   Float_t         Di_dxy1[maxForestMuons];   //[Di_npair]
   Float_t         Di_dxy2[maxForestMuons];   //[Di_npair]
   Float_t         Di_dz1[maxForestMuons];   //[Di_npair]
   Float_t         Di_dz2[maxForestMuons];   //[Di_npair]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_cbin;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_Gen_nptl;   //!
   TBranch        *b_Gen_pid;   //!
   TBranch        *b_Gen_mom;   //!
   TBranch        *b_Gen_status;   //!
   TBranch        *b_Gen_p;   //!
   TBranch        *b_Gen_pt;   //!
   TBranch        *b_Gen_eta;   //!
   TBranch        *b_Gen_phi;   //!
   TBranch        *b_Glb_nptl;   //!
   TBranch        *b_Glb_charge;   //!
   TBranch        *b_Glb_p;   //!
   TBranch        *b_Glb_pt;   //!
   TBranch        *b_Glb_eta;   //!
   TBranch        *b_Glb_phi;   //!
   TBranch        *b_Glb_dxy;   //!
   TBranch        *b_Glb_dz;   //!
   TBranch        *b_Glb_nValMuHits;   //!
   TBranch        *b_Glb_nValTrkHits;   //!
   TBranch        *b_Glb_nValPixHits;   //!
   TBranch        *b_Glb_trkLayerWMeas;   //!
   TBranch        *b_Glb_nMatchedStations;   //!
   TBranch        *b_Glb_nTrkFound;   //!
   TBranch        *b_Glb_glbChi2_ndof;   //!
   TBranch        *b_Glb_trkChi2_ndof;   //!
   TBranch        *b_Glb_pixLayerWMeas;   //!
   TBranch        *b_Glb_trkDxy;   //!
   TBranch        *b_Glb_trkDz;   //!
   TBranch        *b_Sta_nptl;   //!
   TBranch        *b_Sta_charge;   //!
   TBranch        *b_Sta_p;   //!
   TBranch        *b_Sta_pt;   //!
   TBranch        *b_Sta_eta;   //!
   TBranch        *b_Sta_phi;   //!
   TBranch        *b_Sta_dxy;   //!
   TBranch        *b_Sta_dz;   //!
   TBranch        *b_Glb_isArbitrated;   //!
   TBranch        *b_Di_npair;   //!
   TBranch        *b_Di_vProb;   //!
   TBranch        *b_Di_mass;   //!
   TBranch        *b_Di_e;   //!
   TBranch        *b_Di_pt;   //!
   TBranch        *b_Di_pt1;   //!
   TBranch        *b_Di_pt2;   //!
   TBranch        *b_Di_eta;   //!
   TBranch        *b_Di_eta1;   //!
   TBranch        *b_Di_eta2;   //!
   TBranch        *b_Di_phi;   //!
   TBranch        *b_Di_phi1;   //!
   TBranch        *b_Di_phi2;   //!
   TBranch        *b_Di_charge1;   //!
   TBranch        *b_Di_charge2;   //!
   TBranch        *b_Di_isArb1;   //!
   TBranch        *b_Di_isArb2;   //!
   TBranch        *b_Di_nTrkHit1;   //!
   TBranch        *b_Di_nTrkHit2;   //!
   TBranch        *b_Di_trkChi2_1;   //!
   TBranch        *b_Di_trkChi2_2;   //!
   TBranch        *b_Di_glbChi2_1;   //!
   TBranch        *b_Di_glbChi2_2;   //!
   TBranch        *b_Di_dxy1;   //!
   TBranch        *b_Di_dxy2;   //!
   TBranch        *b_Di_dz1;   //!
   TBranch        *b_Di_dz2;   //!
};
#endif
