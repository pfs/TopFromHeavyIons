#include "UserCode/TopFromHeavyIons/analyze.C"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TSystem.h"

#include <iostream>

using namespace std;

//
// MAIN METHOD
//
int main(int argc, char* argv[])
{
  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  //check arguments
  if ( argc < 2 ) 
    {
      std::cout << "Usage : " << argv[0] << " parameters_cfg.py" << std::endl;
      return 0;
    }

  // int anaFile = 1;
  int firstFile = 0;
  int lastFile  = 1;
  if(argc>2) {
    firstFile = atoi(argv[2]);
    lastFile = atoi(argv[3]);
  }
  
  std::cout << "Have " << argc << " arguments:" << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << std::endl;
  }
  
  // read configuration
  const edm::ParameterSet &runProcess = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("config");
  std::vector<std::string> urls=runProcess.getParameter<std::vector<std::string> >("input");

//  for (std::vector<std::string>::const_iterator i = urls.begin(); i != urls.end(); ++i)
//    std::cout << *i << std::endl;
  
  std::string outname = "AnaResults.root";
  // std::string outname = runProcess.getParameter<std::string>("output");
  int maxEvts = runProcess.getParameter<int>("maxEvents");
  // int minCentrality = runProcess.getParameter<int>("minCentrality");
  // int maxCentrality = runProcess.getParameter<int>("maxCentrality");

  // run the analysis
  // cout << "Running analysis over " << urls.size() << " files" << std::endl
  //      << maxEvts << " events will be processed" << std::endl
  //      << "Centrality bins : [" << minCentrality << "," << maxCentrality << "]" << std::endl;
  
  analyze(urls,outname.c_str(),maxEvts,firstFile,lastFile);
  
  //  topEvt *ana = new topEvt(urls,maxEvts,minCentrality,maxCentrality);
  //ana->Run(outname.c_str());
  cout << "Results have been stored in " << outname << endl;
}
