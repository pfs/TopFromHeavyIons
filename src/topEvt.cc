#include "UserCode/TopFromHeavyIons/interface/topEvt.h"

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TChain.h>

ClassImp(topEvt)

//__________________________________________________________
topEvt::topEvt() : 
  hiEvt()
{
  //Default constructor
}

//__________________________________________________________
topEvt::topEvt(std::vector<std::string> &infnames) :
  hiEvt(infnames)
{
  TChain *jetTree = new TChain("akPu3PFJetAnalyzer/t");
  for(size_t i=0; i<infnames.size(); i++) jetTree->Add(infnames[i].c_str());

  fChain->AddFriend(jetTree);

  Init(fChain);
}


//__________________________________________________________
topEvt::~topEvt()
{
  //Destructor
}

//__________________________________________________________
Int_t topEvt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

//__________________________________________________________
Long64_t topEvt::LoadTree(Long64_t entry)
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
void topEvt::Run(const char *outname)
{
  //run
  CreateOutputObjects(outname);
  Loop();

  fFileOut->Write();
  fFileOut->Close();
}

//__________________________________________________________
void topEvt::Loop()
{
  //Do your analysis here
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;

    fPtHat->Fill(pthat);

    //loop over jets
    for(Int_t j = 0; j < nref; ++j) {
      if(rawpt[j] < 15.) continue; //remove low pT jets
      if(TMath::Abs(jteta[j]) > 2. ) continue;

      Float_t ptsub = jtpt[j]; //jet pT after subtracting background
      fPtJet->Fill(ptsub);

      //discriminator from b-tagger
      fDiscrSSVHighEff[0]->Fill(discr_ssvHighEff[j]);
      fDiscrSSVHighPur[0]->Fill(discr_ssvHighPur[j]);
      fDiscrCSVMVA[0]->Fill(discr_csvMva[j]);
      fDiscrCSVSimple[0]->Fill(discr_csvSimple[j]);
      fSVMass[0]->Fill(svtxm[j]);
      fJetMass[0]->Fill(jtm[j]);

      if(TMath::Abs(refparton_flavorForB[j])==5) {
        Printf("Found b-jet pf: %d pt = %.2f ptgen: %f svtxm: %.1f",refparton_flavorForB[j],jtpt[j],refpt[j],svtxm[j]);

        //discriminator from b-tagger
        fDiscrSSVHighEff[1]->Fill(discr_ssvHighEff[j]);
        fDiscrSSVHighPur[1]->Fill(discr_ssvHighPur[j]);
        fDiscrCSVMVA[1]->Fill(discr_csvMva[j]);
        fDiscrCSVSimple[1]->Fill(discr_csvSimple[j]);
        fSVMass[1]->Fill(svtxm[j]);
        fJetMass[1]->Fill(jtm[j]);
      }

      //Find corresponding particle-level jet
      if(refdrjt[j]<0.05 && refpt[j]>0.) { //cut on deltaR needs to be optimized: ask HI jet expert
        Float_t ptgen = refpt[j];
        fPtResponse->Fill(ptgen,ptsub);
      }


    }//jet loop

    
  }
}

//__________________________________________________________
void topEvt::CreateOutputObjects(const char* outname) {

  hiEvt::CreateOutputObjects(outname);

  fPtHat = new TH1F("fPtHat","fPtHat;p_{T} (GeV/c);counts",500,0,500);
  fOutput->Add(fPtHat);
  fPtJet = new TH1F("fPtJet","fPtJet;p_{T} (GeV/c);counts",300,0,300);
  fOutput->Add(fPtJet);

  fPtResponse = new TH2F("fPtResponse","fPtResponse;p_{T,part} (GeV/c);p_{T,det} (GeV/c)",300,0,300,300,0,300);
  fOutput->Add(fPtResponse);

  TString strTypes[2] = {"AllJets","BJets"};

  for(Int_t i = 0; i<2; i++) {
    fDiscrSSVHighEff[i] = new TH1F(Form("fDiscrSSVHighEff%s",strTypes[i].Data()),Form("fDiscrSSVHighEff%s;discriminator",strTypes[i].Data()),100,0,10);
    fOutput->Add(fDiscrSSVHighEff[i]);

    fDiscrSSVHighPur[i] = new TH1F(Form("fDiscrSSVHighPur%s",strTypes[i].Data()),Form("fDiscrSSVHighPur%s;discriminator",strTypes[i].Data()),100,0,10);
    fOutput->Add(fDiscrSSVHighPur[i]);

    fDiscrCSVSimple[i] = new TH1F(Form("fDiscrCSVSimple%s",strTypes[i].Data()),Form("fDiscrCSVSimple%s;discriminator",strTypes[i].Data()),100,0,10);
    fOutput->Add(fDiscrCSVSimple[i]);

    fDiscrCSVMVA[i] = new TH1F(Form("fDiscrCSVMVA%s",strTypes[i].Data()),Form("fDiscrCSVMVA%s;discriminator",strTypes[i].Data()),100,0,10);
    fOutput->Add(fDiscrCSVMVA[i]);

    fSVMass[i] = new TH1F(Form("fSVMass%s",strTypes[i].Data()),Form("fSVMass%s;SV mass",strTypes[i].Data()),100,0,10);
    fOutput->Add(fSVMass[i]);

    fJetMass[i] = new TH1F(Form("fJetMass%s",strTypes[i].Data()),Form("fJetMass%s;M_{jet}",strTypes[i].Data()),100,0,10);
    fOutput->Add(fJetMass[i]);

  }

}


//__________________________________________________________
void topEvt::Init(TChain *tree)
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
  hiEvt::Init(tree);

  fChain->SetBranchAddress("evt", &evt, &b_evt);
  fChain->SetBranchAddress("b", &b, &b_b);
  fChain->SetBranchAddress("nref", &nref, &b_nref);
  fChain->SetBranchAddress("rawpt", rawpt, &b_rawpt);
  fChain->SetBranchAddress("jtpt", jtpt, &b_jtpt);
  fChain->SetBranchAddress("jteta", jteta, &b_jteta);
  fChain->SetBranchAddress("jty", jty, &b_jty);
  fChain->SetBranchAddress("jtphi", jtphi, &b_jtphi);
  fChain->SetBranchAddress("jtpu", jtpu, &b_jtpu);
  fChain->SetBranchAddress("jtm", jtm, &b_jtm);
  fChain->SetBranchAddress("discr_fr01", discr_fr01, &b_discr_fr01);
  fChain->SetBranchAddress("trackMax", trackMax, &b_trackMax);
  fChain->SetBranchAddress("trackSum", trackSum, &b_trackSum);
  fChain->SetBranchAddress("trackN", trackN, &b_trackN);
  fChain->SetBranchAddress("trackHardSum", trackHardSum, &b_trackHardSum);
  fChain->SetBranchAddress("trackHardN", trackHardN, &b_trackHardN);
  fChain->SetBranchAddress("chargedMax", chargedMax, &b_chargedMax);
  fChain->SetBranchAddress("chargedSum", chargedSum, &b_chargedSum);
  fChain->SetBranchAddress("chargedN", chargedN, &b_chargedN);
  fChain->SetBranchAddress("chargedHardSum", chargedHardSum, &b_chargedHardSum);
  fChain->SetBranchAddress("chargedHardN", chargedHardN, &b_chargedHardN);
  fChain->SetBranchAddress("photonMax", photonMax, &b_photonMax);
  fChain->SetBranchAddress("photonSum", photonSum, &b_photonSum);
  fChain->SetBranchAddress("photonN", photonN, &b_photonN);
  fChain->SetBranchAddress("photonHardSum", photonHardSum, &b_photonHardSum);
  fChain->SetBranchAddress("photonHardN", photonHardN, &b_photonHardN);
  fChain->SetBranchAddress("neutralMax", neutralMax, &b_neutralMax);
  fChain->SetBranchAddress("neutralSum", neutralSum, &b_neutralSum);
  fChain->SetBranchAddress("neutralN", neutralN, &b_neutralN);
  fChain->SetBranchAddress("hcalSum", hcalSum, &b_hcalSum);
  fChain->SetBranchAddress("ecalSum", ecalSum, &b_ecalSum);
  fChain->SetBranchAddress("eMax", eMax, &b_eMax);
  fChain->SetBranchAddress("eSum", eSum, &b_eSum);
  fChain->SetBranchAddress("eN", eN, &b_eN);
  fChain->SetBranchAddress("muMax", muMax, &b_muMax);
  fChain->SetBranchAddress("muSum", muSum, &b_muSum);
  fChain->SetBranchAddress("muN", muN, &b_muN);
  fChain->SetBranchAddress("discr_ssvHighEff", discr_ssvHighEff, &b_discr_ssvHighEff);
  fChain->SetBranchAddress("discr_ssvHighPur", discr_ssvHighPur, &b_discr_ssvHighPur);
  fChain->SetBranchAddress("discr_csvMva", discr_csvMva, &b_discr_csvMva);
  fChain->SetBranchAddress("discr_csvSimple", discr_csvSimple, &b_discr_csvSimple);
  fChain->SetBranchAddress("discr_muByIp3", discr_muByIp3, &b_discr_muByIp3);
  fChain->SetBranchAddress("discr_muByPt", discr_muByPt, &b_discr_muByPt);
  fChain->SetBranchAddress("discr_prob", discr_prob, &b_discr_prob);
  fChain->SetBranchAddress("discr_probb", discr_probb, &b_discr_probb);
  fChain->SetBranchAddress("discr_tcHighEff", discr_tcHighEff, &b_discr_tcHighEff);
  fChain->SetBranchAddress("discr_tcHighPur", discr_tcHighPur, &b_discr_tcHighPur);
  fChain->SetBranchAddress("ndiscr_ssvHighEff", ndiscr_ssvHighEff, &b_ndiscr_ssvHighEff);
  fChain->SetBranchAddress("ndiscr_ssvHighPur", ndiscr_ssvHighPur, &b_ndiscr_ssvHighPur);
  fChain->SetBranchAddress("ndiscr_csvSimple", ndiscr_csvSimple, &b_ndiscr_csvSimple);
  fChain->SetBranchAddress("ndiscr_muByPt", ndiscr_muByPt, &b_ndiscr_muByPt);
  fChain->SetBranchAddress("ndiscr_prob", ndiscr_prob, &b_ndiscr_prob);
  fChain->SetBranchAddress("ndiscr_probb", ndiscr_probb, &b_ndiscr_probb);
  fChain->SetBranchAddress("ndiscr_tcHighEff", ndiscr_tcHighEff, &b_ndiscr_tcHighEff);
  fChain->SetBranchAddress("ndiscr_tcHighPur", ndiscr_tcHighPur, &b_ndiscr_tcHighPur);
  fChain->SetBranchAddress("pdiscr_csvSimple", pdiscr_csvSimple, &b_pdiscr_csvSimple);
  fChain->SetBranchAddress("pdiscr_prob", pdiscr_prob, &b_pdiscr_prob);
  fChain->SetBranchAddress("pdiscr_probb", pdiscr_probb, &b_pdiscr_probb);
  fChain->SetBranchAddress("nsvtx", nsvtx, &b_nsvtx);
  fChain->SetBranchAddress("svtxntrk", svtxntrk, &b_svtxntrk);
  fChain->SetBranchAddress("svtxdl", svtxdl, &b_svtxdl);
  fChain->SetBranchAddress("svtxdls", svtxdls, &b_svtxdls);
  fChain->SetBranchAddress("svtxm", svtxm, &b_svtxm);
  fChain->SetBranchAddress("svtxpt", svtxpt, &b_svtxpt);
  fChain->SetBranchAddress("nIPtrk", nIPtrk, &b_nIPtrk);
  fChain->SetBranchAddress("nselIPtrk", nselIPtrk, &b_nselIPtrk);
  fChain->SetBranchAddress("nIP", &nIP, &b_nIP);
  fChain->SetBranchAddress("ipJetIndex", ipJetIndex, &b_ipJetIndex);
  fChain->SetBranchAddress("ipPt", ipPt, &b_ipPt);
  fChain->SetBranchAddress("ipProb0", ipProb0, &b_ipProb0);
  fChain->SetBranchAddress("ipProb1", ipProb1, &b_ipProb1);
  fChain->SetBranchAddress("ip2d", ip2d, &b_ip2d);
  fChain->SetBranchAddress("ip2dSig", ip2dSig, &b_ip2dSig);
  fChain->SetBranchAddress("ip3d", ip3d, &b_ip3d);
  fChain->SetBranchAddress("ip3dSig", ip3dSig, &b_ip3dSig);
  fChain->SetBranchAddress("ipDist2Jet", ipDist2Jet, &b_ipDist2Jet);
  fChain->SetBranchAddress("ipDist2JetSig", ipDist2JetSig, &b_ipDist2JetSig);
  fChain->SetBranchAddress("ipClosest2Jet", ipClosest2Jet, &b_ipClosest2Jet);
  fChain->SetBranchAddress("mue", mue, &b_mue);
  fChain->SetBranchAddress("mupt", mupt, &b_mupt);
  fChain->SetBranchAddress("mueta", mueta, &b_mueta);
  fChain->SetBranchAddress("muphi", muphi, &b_muphi);
  fChain->SetBranchAddress("mudr", mudr, &b_mudr);
  fChain->SetBranchAddress("muptrel", muptrel, &b_muptrel);
  fChain->SetBranchAddress("muchg", muchg, &b_muchg);
  fChain->SetBranchAddress("beamId1", &beamId1, &b_beamId1);
  fChain->SetBranchAddress("beamId2", &beamId2, &b_beamId2);
  fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
  fChain->SetBranchAddress("refpt", refpt, &b_refpt);
  fChain->SetBranchAddress("refeta", refeta, &b_refeta);
  fChain->SetBranchAddress("refy", refy, &b_refy);
  fChain->SetBranchAddress("refphi", refphi, &b_refphi);
  fChain->SetBranchAddress("refdphijt", refdphijt, &b_refdphijt);
  fChain->SetBranchAddress("refdrjt", refdrjt, &b_refdrjt);
  fChain->SetBranchAddress("refparton_pt", refparton_pt, &b_refparton_pt);
  fChain->SetBranchAddress("refparton_flavor", refparton_flavor, &b_refparton_flavor);
  fChain->SetBranchAddress("refparton_flavorForB", refparton_flavorForB, &b_refparton_flavorForB);
  fChain->SetBranchAddress("genChargedSum", genChargedSum, &b_genChargedSum);
  fChain->SetBranchAddress("genHardSum", genHardSum, &b_genHardSum);
  fChain->SetBranchAddress("signalChargedSum", signalChargedSum, &b_signalChargedSum);
  fChain->SetBranchAddress("signalHardSum", signalHardSum, &b_signalHardSum);
  fChain->SetBranchAddress("ngen", &ngen, &b_ngen);
  fChain->SetBranchAddress("genmatchindex", genmatchindex, &b_genmatchindex);
  fChain->SetBranchAddress("genpt", genpt, &b_genpt);
  fChain->SetBranchAddress("geneta", geneta, &b_geneta);
  fChain->SetBranchAddress("geny", geny, &b_geny);
  fChain->SetBranchAddress("genphi", genphi, &b_genphi);
  fChain->SetBranchAddress("gendphijt", gendphijt, &b_gendphijt);
  fChain->SetBranchAddress("gendrjt", gendrjt, &b_gendrjt);
  Notify();
}

//__________________________________________________________
Bool_t topEvt::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

//__________________________________________________________
void topEvt::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

//__________________________________________________________
Int_t topEvt::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.

  Int_t accept = 1;
  if(TMath::Abs(vz)>15.) accept = -1;

  return accept;
}


