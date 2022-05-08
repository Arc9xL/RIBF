#define RIBF132Calib_cxx
#include "RIBF132CalibOut.h"
#include <iostream>
#include <TTree.h>


RIBF132CalibOut::RIBF132CalibOut(TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    std::cout << "tree = 0 ....." << std::endl;
  }
  fChain = tree;
  fCurrent = -1;
}

RIBF132CalibOut::~RIBF132CalibOut()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

void RIBF132CalibOut::Clear(){
  test_cal_var = -9999.0;
  for(int i=0; i<7; i++){
    for(int j=0; j<4; j++){
      test_cal_numhit[i][j] = 0;
    }
  }
  return ;
}

void RIBF132CalibOut::Fill(){
  fChain->Fill();
  return ;
}
