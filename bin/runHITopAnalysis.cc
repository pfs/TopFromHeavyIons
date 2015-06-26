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
      std::cout << "Usage : " << argv[0] << " parameters_cfg.py inputDir/inputFile" << std::endl;
      return 0;
    }
  
  // read configuration
  const edm::ParameterSet &runProcess = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("config");
  std::vector<std::string> urls=runProcess.getParameter<std::vector<std::string> >("input");

  // run the analysis
  topEvt *ana = new topEvt(urls);
  ana->Run();
}
