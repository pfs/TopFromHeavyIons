#include "hiEvt.cc"
#include "analyzeBJets.cc"

void runBJetAna(TString inf = "~/work/top/data/PythiaTTbar/HIForest_pythiaTTbar_2.root") {

  //gSystem->Load("libBJets.so");

  analyzeBJets *ana = new analyzeBJets(inf.Data());
  ana->Run();
}
