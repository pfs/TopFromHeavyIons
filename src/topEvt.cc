#include "UserCode/TopFromHeavyIons/interface/topEvt.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TChain.h>
#include <TGraph.h>
#include <vector>
#include <TLorentzVector.h>

ClassImp(topEvt)

//__________________________________________________________
topEvt::topEvt() : 
  hiEvt()
{
  //Default constructor
}

//__________________________________________________________
topEvt::topEvt(std::vector<std::string> &infnames,int maxEvts) :
  hiEvt(infnames),
  maxEvts_(maxEvts)
{	
  TChain *jetTree = new TChain("akPu3PFJetAnalyzer/t");
  for(size_t i=0; i<infnames.size(); i++) jetTree->Add(infnames[i].c_str());
  fChain->AddFriend(jetTree);

  TChain *muonTree = new TChain("hltMuTree/HLTMuTree");
  for(size_t i=0; i<infnames.size(); i++) muonTree->Add(infnames[i].c_str());
  fChain->AddFriend(muonTree);

  TChain *candTree = new TChain("pfcandAnalyzer/pfTree");
  for(size_t i=0; i<infnames.size(); i++) candTree->Add(infnames[i].c_str());
  fChain->AddFriend(candTree);

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
  if(maxEvts_>0 && maxEvts_<=nentries) nentries=maxEvts_;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;

    printf("\r [ %d/100 ] done", (int)(100.*jentry/(float)(nentries)));

    fPtHat->Fill(pthat);
    fEventSelection->Fill(0);

    // muon selection
    std::vector<int> selected_muon_indices;
    selected_muon_indices.reserve(100);
    for (int nglb = 0; nglb < n_glb; ++nglb){
      
      //check MC match
      float minR = 10.;
      Int_t closest_index = -1;      
      for (int ngen = 0; ngen < n_gen; ++ngen)
	{
	  float DeltaR = deltaR(gen_eta[ngen],gen_phi[ngen],glb_eta[nglb],glb_phi[nglb]);
	  if( DeltaR <= minR){
	    minR = DeltaR;
	    closest_index = ngen;
	  }
	}      

      bool isMatched(minR < 0.1);
      bool passKin(glb_pt[nglb] >= 20 && fabs(glb_eta[nglb]) <= 2.1);
      bool passId(fabs(chi[nglb]) <= 10 && abs(nmhits[nglb]) >= 0 && abs(nMS[nglb]) >= 1 && fabs(glb_dz[nglb]) <= 0.5 && abs(nphits[nglb]) >= 0 && fabs(tLWM[nglb]) >= 5 && fabs(glb_dxy[nglb]) <= 0.05);
      
      if (isMatched && abs(gen_mom[closest_index])==24 )
	{
	  hist_R->Fill(minR);
	  hist_gen_pt_signal->Fill(gen_pt[closest_index]);
	  hist_glb_pt_signal->Fill(glb_pt[nglb]);
	  hist_glb_eta_signal->Fill(glb_eta[nglb]);
	  if(passKin)
	    {
	      hist_glb_dxy_signal->Fill(glb_dxy[nglb]);
	      hist_nmhits_signal->Fill(nmhits[nglb]);
	      hist_nthits_signal->Fill(nthits[nglb]);
	      hist_nphits_signal->Fill(nphits[nglb]);
	      hist_chi_signal->Fill(chi[nglb]);
	      hist_nMS_signal->Fill(nMS[nglb]);
	      hist_glb_dz_signal->Fill(glb_dz[nglb]);
	      hist_tLWM_signal->Fill(tLWM[nglb]);
	    }
	} 
      else 
	{
	  hist_glb_pt_bg->Fill(glb_pt[nglb]);
	  hist_glb_eta_bg->Fill(glb_eta[nglb]);
	  if(passKin)
	    {
	      hist_glb_dxy_bg->Fill(glb_dxy[nglb]);
	      hist_nmhits_bg->Fill(nmhits[nglb]);
	      hist_nthits_bg->Fill(nthits[nglb]);
	      hist_nphits_bg->Fill(nphits[nglb]);
	      hist_chi_bg->Fill(chi[nglb]);	   
	      hist_nMS_bg->Fill(nMS[nglb]);
	      hist_glb_dz_bg->Fill(glb_dz[nglb]);
	      hist_tLWM_bg->Fill(tLWM[nglb]);
	    }
	}
      
      //charged particle activity around the muon
      float sumChPt(0);
      for (Int_t lpk = 0; lpk< nPFpart; ++lpk) {
	float dR = deltaR(glb_eta[nglb],glb_phi[nglb],pfEta[lpk],pfPhi[lpk]);	
	if (abs(dR) < 0.3) sumChPt +=pfPt[lpk];
      }

      //muon is selected
      if(!passKin || !passId) continue;
      selected_muon_indices.push_back(nglb);
      if (isMatched && abs(gen_mom[closest_index])==24 ) hist_glb_pt_signal_pass->Fill(glb_pt[nglb]);
      else hist_glb_pt_bg_pass->Fill(glb_pt[nglb]);
      hist_sumchpt->Fill(TMath::Max(Float_t(sumChPt-glb_pt[nglb]),Float_t(0.))/glb_pt[nglb]);
    }
    

    //
    //di-muon selection
    //
    if(selected_muon_indices.size() < 2) continue;
    fEventSelection->Fill(1);
    
    TLorentzVector mu1, mu2;
    int mu_1 = selected_muon_indices[0];
    int mu_2 = selected_muon_indices[1];
    mu1.SetPtEtaPhiM(glb_pt[mu_1], glb_eta[mu_1], glb_phi[mu_1], 0.);
    mu2.SetPtEtaPhiM(glb_pt[mu_2], glb_eta[mu_2], glb_phi[mu_2], 0.);    
    invariant_mass_histogram->Fill((mu1+mu2).M());
    
    if((mu1+mu2).M()>80 && (mu1+mu2).M()<100) continue;
    if((mu1+mu2).M()<20) continue;
    fEventSelection->Fill(2);
	
    //
    //Jet selection
    //
    int njets15(0),njets30(0),njets40(0);
    for(Int_t j = 0; j < nref; ++j) 
      {
	if(rawpt[j] < 15.) continue; //remove low pT jets
	if(TMath::Abs(jteta[j]) > 2. ) continue;
	
	Float_t ptsub = jtpt[j]; //jet pT after subtracting background
	njets15 += (ptsub>15);
	njets30 += (ptsub>30);
	njets40 += (ptsub>40);
	fPtJet->Fill(ptsub);
	if(refdrjt[j]<0.05 && refpt[j]>0.) { 
	  //cut on deltaR needs to be optimized: ask HI jet expert
	  Float_t ptgen = refpt[j];
	  fPtResponse->Fill(ptgen,ptsub);
	}
	
	//discriminator from b-tagger
	if(ptsub>15)
	  {
	    bool isMatchedToB(TMath::Abs(refparton_flavorForB[j])==5);
	    fDiscrCSVSimple[isMatchedToB]->Fill(discr_csvSimple[j]);
	  }
      }//jet loop
    
    fNJets15->Fill(njets15);
    fNJets30->Fill(njets30);
    fNJets40->Fill(njets40);
    
    if(njets15>0) fEventSelection->Fill(2);
    if(njets15>1) fEventSelection->Fill(3);
    if(njets15>2) fEventSelection->Fill(4);
  }

  //finalize summary plots

  //muon selection efficiency
  hist_eff_pt_signal->BayesDivide(hist_glb_pt_signal_pass,hist_glb_pt_signal);
  hist_eff_pt_bg->BayesDivide(hist_glb_pt_bg_pass,hist_glb_pt_bg);

  //csv selection efficiency and purity
  int totalB(fDiscrCSVSimple[1]->Integral()), totalOther(fDiscrCSVSimple[0]->Integral());
  int ncsvbins(fDiscrCSVSimple[0]->GetXaxis()->GetNbins());
  for(int xbin=1; xbin<=ncsvbins; xbin++)
    {
      Double_t csvcut=fDiscrCSVSimple[0]->GetXaxis()->GetBinLowEdge(xbin);
      Double_t passBerr(0),passOthererr(0);
      Double_t passB     = fDiscrCSVSimple[1]->IntegralAndError(xbin,ncsvbins,passBerr);
      Double_t passOther = fDiscrCSVSimple[0]->IntegralAndError(xbin,ncsvbins,passOthererr);
      Int_t np=csveffgraph[0]->GetN();
      csveffgraph[0]->SetPoint(np,csvcut,passOther/totalOther);
      csveffgraph[0]->SetPointError(np,0,passOthererr/totalOther);
      csveffgraph[1]->SetPoint(np,csvcut,passB/totalB);
      csveffgraph[1]->SetPointError(np,0,passBerr/totalB);
      csvpurgraph->SetPoint(np,csvcut,passB/passOther);
      csvpurgraph->SetPointError(np,0,TMath::Sqrt(TMath::Power(passB*passOthererr,2)+TMath::Power(passBerr*passOther,2))/TMath::Power(passOther,2));      
    }
}

//__________________________________________________________
void topEvt::CreateOutputObjects(const char* outname) {

  hiEvt::CreateOutputObjects(outname);

  fPtHat = new TH1F("fPtHat","fPtHat;p_{T} (GeV/c);counts",500,0,500);
  fOutput->Add(fPtHat);

  //event selection
  fEventSelection = new TH1F("fEventSelection","fEventSelection;Selection step;counts",5,0,5);
  fEventSelection->GetXaxis()->SetBinLabel(1,"Generated");
  fEventSelection->GetXaxis()->SetBinLabel(2,"#geq2#mu");
  fEventSelection->GetXaxis()->SetBinLabel(3,"Z/low mass veto");
  fEventSelection->GetXaxis()->SetBinLabel(4,"#geq1jet");
  fEventSelection->GetXaxis()->SetBinLabel(3,"#geq2jets");
  fEventSelection->GetXaxis()->SetBinLabel(5,"#geq3jets");

  //generator level muons
  hist_gen_pt_signal = new TH1F("gen_pt_signal","Gen pt signal;Gen p_{T} [GeV]", 100, 0., 200.);
  fOutput->Add(hist_gen_pt_signal);
  hist_R = new TH1F("dR","Event;dR",100, 0.,6.);
  fOutput->Add(hist_R);

  //reconstructed muons
  hist_glb_pt_signal = new TH1F("glb_pt_signal","Glb pt signal;Glb p_{T} [GeV]", 100, 0., 200.);
  fOutput->Add(hist_glb_pt_signal);
  hist_glb_pt_signal_pass = new TH1F("glb_pt_signal_pass","Glb pt signal;Glb p_{T} [GeV]", 100, 0., 200.);
  fOutput->Add(hist_glb_pt_signal_pass);
  hist_glb_pt_bg = new TH1F("glb_pt_bg","Glb pt signal;Glb p_{T} [GeV]", 100, 0., 200.);
  fOutput->Add(hist_glb_pt_bg);
  hist_glb_pt_bg_pass = new TH1F("glb_pt_bg_pass","Glb pt signal;Glb p_{T} [GeV]", 100, 0., 200.);
  fOutput->Add(hist_glb_pt_bg_pass);
  hist_eff_pt_signal = new TGraphAsymmErrors();
  hist_eff_pt_signal->SetName("eff_pt_signal");
  fOutput->Add(hist_eff_pt_signal);
  hist_eff_pt_bg = new TGraphAsymmErrors();
  hist_eff_pt_bg->SetName("eff_pt_bg");
  fOutput->Add(hist_eff_pt_bg);

  //muon id
  hist_glb_dxy_signal = new TH1F("glb_dxy_signal","Glb_dxy;dxy", 100, -0.05, 0.05);
  fOutput->Add(hist_glb_dxy_signal);
  hist_glb_dxy_bg = new TH1F("glb_dxy_bg","Glb_dxy;dxy", 100, -0.05, 0.05);
  fOutput->Add(hist_glb_dxy_bg);
  hist_nmhits_signal = new TH1F("nmhits_signal","Glb_nValMuHits;npoints", 100, 0., 55.);
  fOutput->Add(hist_nmhits_signal);
  hist_nmhits_bg = new TH1F("nmhits_bg","Glb_nValMuHits;npoints", 100, 0., 55.);
  fOutput->Add(hist_nmhits_bg);
  hist_nthits_signal = new TH1F("nthits_signal","Glb_nValTrkHits;npoints", 100, 0., 32.);
  fOutput->Add(hist_nthits_signal);
  hist_nthits_bg = new TH1F("nthits_bg","Glb_nValTrkHits;npoints", 100, 0., 32.);
  fOutput->Add(hist_nthits_bg);
  hist_nphits_signal = new TH1F("nphits_signal","Glb_nValPixHits;npoints", 100, 0., 10.);
  fOutput->Add(hist_nphits_signal);
  hist_nphits_bg = new TH1F("nphits_bg","Glb_nValPixHits;npoints", 100, 0., 10.);
  fOutput->Add(hist_nphits_bg);
  hist_chi_signal = new TH1F("chi_signal","Glb_trkChi2_ndof;npoints", 100, 0., 3.5);
  fOutput->Add(hist_chi_signal);
  hist_chi_bg = new TH1F("chi_bg","Glb_trkChi2_ndof;npoints", 100, 0., 3.5);
  fOutput->Add(hist_chi_bg);
  hist_glb_eta_signal = new TH1F("eta_signal","Glb_eta;Glb eta", 100, 0., 3.);
  fOutput->Add(hist_glb_eta_signal);
  hist_glb_eta_bg = new TH1F("eta_bg","Glb_eta;Glb eta", 100, 0., 3.);
  fOutput->Add(hist_glb_eta_bg);
  hist_nMS_signal = new TH1F("nMS_signal","Glb_nMatchedStations;Glb_nMatchedStations", 100, 0., 100.);
  fOutput->Add(hist_nMS_signal);
  hist_nMS_bg = new TH1F("nMS_bg","Glb_nMatchedStations;Glb_nMatchedStations", 100, 0., 100.);
  fOutput->Add(hist_nMS_bg);
  hist_glb_dz_signal = new TH1F("glb_dz_signal","Glb_trkDz;dz", 100, 0, 0.05);
  fOutput->Add(hist_glb_dz_signal);
  hist_glb_dz_bg = new TH1F("glb_dz_bg","Glb_trkDz;dz", 100, 0, 0.05);
  fOutput->Add(hist_glb_dz_bg);
  hist_tLWM_signal = new TH1F("tLWM_signal","Glb_trkLayerWMeas;pixLayerWMeas", 100, 0., 16.);
  fOutput->Add(hist_tLWM_signal);
  hist_tLWM_bg = new TH1F("tLWM_bg","Glb_trkLayerWMeas;pixLayerWMeas", 100, 0., 16.);
  fOutput->Add(hist_tLWM_bg);
  hist_sumchpt = new TH1F("hist_sumchpt","sumchpt;#Sigma_{ch PF}p_{T}/p_{T}(#mu);counts",100,0,0.8);
  fOutput->Add(hist_sumchpt);

  //dimuons
  invariant_mass_histogram = new TH1F("invariant_mass_histogram","invariant_mass; [GeV]", 100, 0., 200.);
  fOutput->Add(invariant_mass_histogram);

  //jets
  fPtJet = new TH1F("fPtJet","fPtJet;p_{T} (GeV/c);counts",300,0,300);
  fOutput->Add(fPtJet);
  fPtResponse = new TH2F("fPtResponse","fPtResponse;p_{T,part} (GeV/c);p_{T,det} (GeV/c)",300,0,300,300,0,300);
  fOutput->Add(fPtResponse);
  fNJets15 = new TH1F("fNJets15","fNJets15;Jet multiplicity (>15 GeV/c);counts",10,0,10);
  fOutput->Add(fNJets15);
  fNJets30 = new TH1F("fNJets30","fNJets30;Jet multiplicity (>30 GeV/c);counts",10,0,10);
  fOutput->Add(fNJets30);
  fNJets40 = new TH1F("fNJets40","fNJets40;Jet multiplicity (>40 GeV/c);counts",10,0,10);
  fOutput->Add(fNJets40);

  
  TString strTypes[2] = {"OtherJets","BJets"};
  for(Int_t i = 0; i<2; i++) {
    fDiscrCSVSimple[i] = new TH1F(Form("fDiscrCSVSimple%s",strTypes[i].Data()),Form("fDiscrCSVSimple%s;discriminator",strTypes[i].Data()),100,0,10);
    fOutput->Add(fDiscrCSVSimple[i]);
    csveffgraph[i]=new TGraphErrors();
    csveffgraph[i]->SetName(Form("csveffgraph%s",strTypes[i].Data()));
  }
  csvpurgraph=new TGraphErrors();
  csvpurgraph->SetName("csvbpurgraph");
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

  fChain->SetBranchAddress("Gen_nptl", &n_gen, &b_n_gen); // Number of generated muons
  fChain->SetBranchAddress("Gen_pt",  gen_pt, &b_gen_pt);
  fChain->SetBranchAddress("Gen_eta", gen_eta, &b_gen_eta);
  fChain->SetBranchAddress("Gen_phi", gen_phi, &b_gen_phi);
  fChain->SetBranchAddress("Gen_mom", gen_mom, &b_gen_mom);
  fChain->SetBranchAddress("Glb_nptl", &n_glb, &b_n_glb); // Number of glb muons
  fChain->SetBranchAddress("Glb_pt",  glb_pt, &b_glb_pt);
  fChain->SetBranchAddress("Glb_eta", glb_eta, &b_glb_eta);
  fChain->SetBranchAddress("Glb_phi", glb_phi, &b_glb_phi);
  fChain->SetBranchAddress("Glb_dxy", glb_dxy, &b_glb_dxy);
  fChain->SetBranchAddress("Glb_nValMuHits", nmhits, &b_nmhits);
  fChain->SetBranchAddress("Glb_nValTrkHits", nthits, &b_nthits);
  fChain->SetBranchAddress("Glb_nValPixHits", nphits, &b_nphits);
  fChain->SetBranchAddress("Glb_trkChi2_ndof", chi, &b_chi);
  fChain->SetBranchAddress("Glb_nMatchedStations", nMS, &b_nMS);
  fChain->SetBranchAddress("Glb_trkDz", glb_dz, &b_glb_dz);
  fChain->SetBranchAddress("Glb_trkLayerWMeas", tLWM, &b_tLWM);

  fChain->SetBranchAddress("nPFpart", &nPFpart, &b_nPFpart);
  //fChain->SetBranchAddress("pfId", &pfId, &b_pfId);
  fChain->SetBranchAddress("pfPt", pfPt, &b_pfPt);
  fChain->SetBranchAddress("pfEta", pfEta, &b_pfEta);
  fChain->SetBranchAddress("pfPhi", pfPhi, &b_pfPhi);

 


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
  //if(hiBin<100. || hiBin>=160.) accept = -1; //centrality	
 


  return accept;
}


