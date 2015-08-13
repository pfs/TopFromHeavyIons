#include "UserCode/TopFromHeavyIons/interface/topEvt.h"

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
  
  // read configuration
  const edm::ParameterSet &runProcess = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("config");
  std::vector<std::string> urls=runProcess.getParameter<std::vector<std::string> >("input");
  std::string outname = runProcess.getParameter<std::string>("output");
  int maxEvts = runProcess.getParameter<int>("maxEvents");
  int minCentrality = runProcess.getParameter<int>("minCentrality");
  int maxCentrality = runProcess.getParameter<int>("maxCentrality");

  // run the analysis
  cout << "Running analysis over " << urls.size() << " files" << std::endl
       << maxEvts << " events will be processed" << std::endl
       << "Centrality bins : [" << minCentrality << "," << maxCentrality << "]" << std::endl;
  
  topEvt *ana = new topEvt(urls,maxEvts,minCentrality,maxCentrality);
  ana->Run(outname.c_str());
  cout << "Results have been stored in " << outname << endl;
}
