#ifndef ForestPFs_h
#define ForestPFs_h

#define maxPF 40000

class ForestPFs {
public :
   ForestPFs(){};
   ~ForestPFs(){};

   // Declaration of leaf types
   Int_t           nPFpart;
   Int_t           pfId[maxPF];   //[nPFpart]
   Float_t         pfPt[maxPF];   //[nPFpart]
   Float_t         pfVsPt[maxPF]; //[nPFpart]
   Float_t         pfEta[maxPF];  //[nPFpart]
   Float_t         pfPhi[maxPF];  //[nPFpart]
   Float_t         vn[5][15];
   Float_t         psin[5][15];
   Float_t         sumpt[15];

   // List of branches
   TBranch        *b_nPFpart; //!
   TBranch        *b_pfId;    //!
   TBranch        *b_pfPt;    //!
   TBranch        *b_pfVsPt;  //!
   TBranch        *b_pfEta;   //!
   TBranch        *b_pfPhi;   //!
   TBranch        *b_vn;
   TBranch        *b_psin;
   TBranch        *b_sumpt;
};
#endif
