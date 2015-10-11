#ifndef ForestGenParticles_h
#define ForestGenParticles_h

#define maxGenParticles 20000

class ForestGenParticles {
public :
   ForestGenParticles(){};
   ~ForestGenParticles(){};

   // Declaration of leaf types
   Int_t           event;
   Float_t         b;
   Float_t         npart;
   Float_t         ncoll;
   Float_t         nhard;
   Float_t         phi0;
   Float_t         scale;
   Int_t           n[3];
   Float_t         ptav[3];
   Int_t           mult;
   Float_t         pt[maxGenParticles];   //[mult]
   Float_t         eta[maxGenParticles];   //[mult]
   Float_t         phi[maxGenParticles];   //[mult]
   Int_t           pdg[maxGenParticles];   //[mult]
   Int_t           chg[maxGenParticles];   //[mult]
   Int_t           sta[maxGenParticles];   //[mult]
   Int_t           sube[maxGenParticles];   //[mult]
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         vr;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_b;   //!
   TBranch        *b_npart;   //!
   TBranch        *b_ncoll;   //!
   TBranch        *b_nhard;   //!
   TBranch        *b_phi0;   //!
   TBranch        *b_scale;   //!
   TBranch        *b_n;   //!
   TBranch        *b_ptav;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_chg;   //!
   TBranch        *b_sta;   //!
   TBranch        *b_sube;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_vr;   //!

};
#endif
