#include "MakeOnlineBigRIPSTree.hh"

#include <iostream>

#include "TArtAnaFile.hh"
#include "TArtAnaClock.hh"

#include "EWNum.hh"

#include "TArtFocalPlane.hh"
#include "TArtIC.hh"
#include "TArtPlastic.hh"
#include "TArtPPAC.hh"
#include "TArtTOF.hh"
#include "TArtRIPS.hh"

#include "TArtCore.hh"
#include "TArtStoreManager.hh"

#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"
#include "signal.h"

#include "TArtRecoBeam.hh"
#include "TArtBeam.hh"
//#include "TClonesArray.h"

#include "segidlist.hh"

// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void stop_interrupt(int) {
  printf("keyboard interrupt\n");
  stoploop = true;
}

MakeOnlineBigRIPSTree::MakeOnlineBigRIPSTree() : TArtAnaLoop(), bigripsparameters(0) {
}

MakeOnlineBigRIPSTree::~MakeOnlineBigRIPSTree() {
}

void MakeOnlineBigRIPSTree::Construct() {
  cout<<"call constructor!!"<<endl; 
 
  sman = TArtStoreManager::Instance();

  //fout = new TFile("OnlineBigRIPSTree.root","RECREATE");
  tree = new TTree("tree","tree");

  bigripsparameters  = TArtBigRIPSParameters::Instance();
  bigripsparameters->LoadParameter("db/BigRIPSPPAC.xml");
  bigripsparameters->LoadParameter("db/BigRIPSPlastic.xml");
  bigripsparameters->LoadParameter("db/BigRIPSIC.xml");
  bigripsparameters->LoadParameter("db/FocalPlane.xml");
  bigripsparameters->SetFocusPosOffset(8,138.5);

  cpid  = new TArtCalibPID();
  cppac = cpid->GetCalibPPAC();
  cpla  = cpid->GetCalibPlastic();
  cic   = cpid->GetCalibIC();
  cfpl  = cpid->GetCalibFocalPlane(); 

  std::cout << "Defining bigrips parameters" << std::endl;
   
  recopid = new TArtRecoPID();
  rips3to5 = recopid->DefineNewRIPS(3,5,"matrix/mat1.mat","D3"); // F3 - F5
  rips5to7 = recopid->DefineNewRIPS(5,7,"matrix/mat2.mat","D5"); // F5 - F7
  rips8to9 = recopid->DefineNewRIPS(8,9,"matrix/F8F9_LargeAccAchr.mat","D7"); // F8 - F9 
  rips9to11 = recopid->DefineNewRIPS(9,11,"matrix/F9F11_LargeAccAchr.mat","D8"); // F9 - F11  
  
  // Reconstruction of TOF DefineNewTOF(fisrt plane, second plane, time offset)
  // I try not to shift the A/Q but adjust the TOF offset instead
  //For 66Cr 
  //tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.88,5); // F3 - F7 // OK
  //tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-161.45,9); // F8 - F11 // OK

  //For 72Fe
  tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.95,5); // F3 - F7
  tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159.6,9); // F8 - F11
  tof3to5 =  recopid->DefineNewTOF("F3pl","F5pl",100); //F3 - F5
  tof5to7 =  recopid->DefineNewTOF("F5pl","F7pl",100); //F5 - F7
  tof7to8 =  recopid->DefineNewTOF("F7pl","F8pl"); //F7 - F8
   
  // For 78Ni:
  //tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.25,5); // F3 - F7 // OK
  //tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159.45,9); // F8 - F11 //OK 
  
  // Reconstruction of IC observables for ID
  //beam_br_37 = recopid->DefineNewBeam(rips3to5,rips5to7,tof3to7,"F7IC");
  beam_br_35 = recopid->DefineNewBeam(rips3to5,tof3to5,"F7IC");
  beam_br_57 = recopid->DefineNewBeam(rips5to7,tof5to7,"F7IC");   
  beam_zd_89 = recopid->DefineNewBeam(rips8to9,tof8to11,"F11IC");
  beam_zd_911 = recopid->DefineNewBeam(rips9to11,tof8to11,"F11IC");
 
  //Using both
  beam_br_37 = recopid->DefineNewBeam(rips3to5,rips5to7,tof3to7,(char*)"F7IC");
  beam_zd_811 =recopid->DefineNewBeam(rips8to9,rips9to11,tof8to11,(char*)"F11IC");

  tree->Branch("fbit",&fbit,"fbit/I");

  tree->Branch("F3PPAC1A_X",&F3PPAC1A_X,"F3PPAC1A_X/D");
  tree->Branch("F3PPAC1A_Y",&F3PPAC1A_Y,"F3PPAC1A_Y/D");
  tree->Branch("F3PPAC1B_X",&F3PPAC1B_X,"F3PPAC1B_X/D");
  tree->Branch("F3PPAC1B_Y",&F3PPAC1A_Y,"F3PPAC1B_Y/D");
  tree->Branch("F3PPAC2A_X",&F3PPAC2A_X,"F3PPAC2A_X/D");
  tree->Branch("F3PPAC2A_Y",&F3PPAC2A_Y,"F3PPAC2A_Y/D");
  tree->Branch("F3PPAC2B_X",&F3PPAC2B_X,"F3PPAC2B_X/D");
  tree->Branch("F3PPAC2B_Y",&F3PPAC2A_Y,"F3PPAC2B_Y/D");
  
  tree->Branch("F3PPAC1A_sum_x",&F3PPAC1A_sum_x,"F3PPAC1A_sum_x/D");
  tree->Branch("F3PPAC1A_sum_y",&F3PPAC1A_sum_y,"F3PPAC1A_sum_y/D");
  tree->Branch("F3PPAC1B_sum_x",&F3PPAC1B_sum_x,"F3PPAC1B_sum_x/D");
  tree->Branch("F3PPAC1B_sum_y",&F3PPAC1B_sum_y,"F3PPAC1B_sum_y/D");
  tree->Branch("F3PPAC2A_sum_x",&F3PPAC2A_sum_x,"F3PPAC2A_sum_x/D");
  tree->Branch("F3PPAC2A_sum_y",&F3PPAC2A_sum_y,"F3PPAC2A_sum_y/D");
  tree->Branch("F3PPAC2B_sum_x",&F3PPAC2B_sum_x,"F3PPAC2B_sum_x/D");
  tree->Branch("F3PPAC2B_sum_y",&F3PPAC2B_sum_y,"F3PPAC2B_sum_y/D");

  tree->Branch("F3PPAC1A_diff_x",&F3PPAC1A_diff_x,"F3PPAC1A_diff_x/D");
  tree->Branch("F3PPAC1A_diff_y",&F3PPAC1A_diff_y,"F3PPAC1A_diff_y/D");
  tree->Branch("F3PPAC1B_diff_x",&F3PPAC1B_diff_x,"F3PPAC1B_diff_x/D");
  tree->Branch("F3PPAC1B_diff_y",&F3PPAC1B_diff_y,"F3PPAC1B_diff_y/D");
  tree->Branch("F3PPAC2A_diff_x",&F3PPAC2A_diff_x,"F3PPAC2A_diff_x/D");
  tree->Branch("F3PPAC2A_diff_y",&F3PPAC2A_diff_y,"F3PPAC2A_diff_y/D");
  tree->Branch("F3PPAC2B_diff_x",&F3PPAC2B_diff_x,"F3PPAC2B_diff_x/D");
  tree->Branch("F3PPAC2B_diff_y",&F3PPAC2B_diff_y,"F3PPAC2B_diff_y/D");

  tree->Branch("F3X",&F3X,"F3X/D");
  tree->Branch("F3A",&F3A,"F3A/D");
  tree->Branch("F3Y",&F3Y,"F3Y/D");
  tree->Branch("F3B",&F3B,"F3B/D");

  tree->Branch("F3PLA_TL_raw",&F3PLA_TL_raw,"F3PLA_TL_raw/D");
  tree->Branch("F3PLA_TR_raw",&F3PLA_TR_raw,"F3PLA_TR_raw/D");
  tree->Branch("F3PLA_TL",&F3PLA_TL,"F3PLA_TL/D");
  tree->Branch("F3PLA_TR",&F3PLA_TR,"F3PLA_TR/D");
  tree->Branch("F3PLA_T",&F3PLA_T,"F3PLA_T/D");

  tree->Branch("F3PLA_QL_raw",&F3PLA_QL_raw,"F3PLA_QL_raw/I");
  tree->Branch("F3PLA_QR_raw",&F3PLA_QR_raw,"F3PLA_QR_raw/I");
  tree->Branch("F3PLA_Q_ave",&F3PLA_Q_ave,"F3PLA_Q_ave/I");

  tree->Branch("F5PPAC1A_X",&F5PPAC1A_X,"F5PPAC1A_X/D");
  tree->Branch("F5PPAC1A_Y",&F5PPAC1A_Y,"F5PPAC1A_Y/D");
  tree->Branch("F5PPAC1B_X",&F5PPAC1B_X,"F5PPAC1B_X/D");
  tree->Branch("F5PPAC1B_Y",&F5PPAC1A_Y,"F5PPAC1B_Y/D");
  tree->Branch("F5PPAC2A_X",&F5PPAC2A_X,"F5PPAC2A_X/D");
  tree->Branch("F5PPAC2A_Y",&F5PPAC2A_Y,"F5PPAC2A_Y/D");
  tree->Branch("F5PPAC2B_X",&F5PPAC2B_X,"F5PPAC2B_X/D");
  tree->Branch("F5PPAC2B_Y",&F5PPAC2A_Y,"F5PPAC2B_Y/D");

  tree->Branch("F5PPAC1A_sum_x",&F5PPAC1A_sum_x,"F5PPAC1A_sum_x/D");
  tree->Branch("F5PPAC1A_sum_y",&F5PPAC1A_sum_y,"F5PPAC1A_sum_y/D");
  tree->Branch("F5PPAC1B_sum_x",&F5PPAC1B_sum_x,"F5PPAC1B_sum_x/D");
  tree->Branch("F5PPAC1B_sum_y",&F5PPAC1B_sum_y,"F5PPAC1B_sum_y/D");
  tree->Branch("F5PPAC2A_sum_x",&F5PPAC2A_sum_x,"F5PPAC2A_sum_x/D");
  tree->Branch("F5PPAC2A_sum_y",&F5PPAC2A_sum_y,"F5PPAC2A_sum_y/D");
  tree->Branch("F5PPAC2B_sum_x",&F5PPAC2B_sum_x,"F5PPAC2B_sum_x/D");
  tree->Branch("F5PPAC2B_sum_y",&F5PPAC2A_sum_y,"F5PPAC2B_sum_y/D");

  tree->Branch("F5PPAC1A_diff_x",&F5PPAC1A_diff_x,"F5PPAC1A_diff_x/D");
  tree->Branch("F5PPAC1A_diff_y",&F5PPAC1A_diff_y,"F5PPAC1A_diff_y/D");
  tree->Branch("F5PPAC1B_diff_x",&F5PPAC1B_diff_x,"F5PPAC1B_diff_x/D");
  tree->Branch("F5PPAC1B_diff_y",&F5PPAC1B_diff_y,"F5PPAC1B_diff_y/D");
  tree->Branch("F5PPAC2A_diff_x",&F5PPAC2A_diff_x,"F5PPAC2A_diff_x/D");
  tree->Branch("F5PPAC2A_diff_y",&F5PPAC2A_diff_y,"F5PPAC2A_diff_y/D");
  tree->Branch("F5PPAC2B_diff_x",&F5PPAC2B_diff_x,"F5PPAC2B_diff_x/D");
  tree->Branch("F5PPAC2B_diff_y",&F5PPAC2B_diff_y,"F5PPAC2B_diff_y/D");
  
  tree->Branch("F5X",&F5X,"F5X/D");
  tree->Branch("F5A",&F5A,"F5A/D");
  tree->Branch("F5Y",&F5Y,"F5Y/D");
  tree->Branch("F5B",&F5B,"F5B/D");

  tree->Branch("F5PLA_TL_raw",&F5PLA_TL_raw,"F5PLA_TL_raw/D");
  tree->Branch("F5PLA_TR_raw",&F5PLA_TR_raw,"F5PLA_TR_raw/D");
  tree->Branch("F5PLA_TL",&F5PLA_TL,"F5PLA_TL/D");
  tree->Branch("F5PLA_TR",&F5PLA_TR,"F5PLA_TR/D");
  tree->Branch("F5PLA_T",&F5PLA_T,"F5PLA_T/D");

  tree->Branch("F5PLA_QL_raw",&F5PLA_QL_raw,"F5PLA_QL_raw/I");
  tree->Branch("F5PLA_QR_raw",&F5PLA_QR_raw,"F5PLA_QR_raw/I");
  tree->Branch("F5PLA_Q_ave",&F5PLA_Q_ave,"F5PLA_Q_ave/I");

  tree->Branch("F7PPAC1A_X",&F7PPAC1A_X,"F7PPAC1A_X/D");
  tree->Branch("F7PPAC1A_Y",&F7PPAC1A_Y,"F7PPAC1A_Y/D");
  tree->Branch("F7PPAC1B_X",&F7PPAC1B_X,"F7PPAC1B_X/D");
  tree->Branch("F7PPAC1B_Y",&F7PPAC1A_Y,"F7PPAC1B_Y/D");
  tree->Branch("F7PPAC2A_X",&F7PPAC2A_X,"F7PPAC2A_X/D");
  tree->Branch("F7PPAC2A_Y",&F7PPAC2A_Y,"F7PPAC2A_Y/D");
  tree->Branch("F7PPAC2B_X",&F7PPAC2B_X,"F7PPAC2B_X/D");
  tree->Branch("F7PPAC2B_Y",&F7PPAC2A_Y,"F7PPAC2B_Y/D");
  
  tree->Branch("F7PPAC1A_sum_x",&F7PPAC1A_sum_x,"F7PPAC1A_sum_x/D");
  tree->Branch("F7PPAC1A_sum_y",&F7PPAC1A_sum_y,"F7PPAC1A_sum_y/D");
  tree->Branch("F7PPAC1B_sum_x",&F7PPAC1B_sum_x,"F7PPAC1B_sum_x/D");
  tree->Branch("F7PPAC1B_sum_y",&F7PPAC1B_sum_y,"F7PPAC1B_sum_y/D");
  tree->Branch("F7PPAC2A_sum_x",&F7PPAC2A_sum_x,"F7PPAC2A_sum_x/D");
  tree->Branch("F7PPAC2A_sum_y",&F7PPAC2A_sum_y,"F7PPAC2A_sum_y/D");
  tree->Branch("F7PPAC2B_sum_x",&F7PPAC2B_sum_x,"F7PPAC2B_sum_x/D");
  tree->Branch("F7PPAC2B_sum_y",&F7PPAC2B_sum_y,"F7PPAC2B_sum_y/D");
		 
  tree->Branch("F7PPAC1A_diff_x",&F7PPAC1A_diff_x,"F7PPAC1A_diff_x/D");
  tree->Branch("F7PPAC1A_diff_y",&F7PPAC1A_diff_y,"F7PPAC1A_diff_y/D");
  tree->Branch("F7PPAC1B_diff_x",&F7PPAC1B_diff_x,"F7PPAC1B_diff_x/D");
  tree->Branch("F7PPAC1B_diff_y",&F7PPAC1B_diff_y,"F7PPAC1B_diff_y/D");
  tree->Branch("F7PPAC2A_diff_x",&F7PPAC2A_diff_x,"F7PPAC2A_diff_x/D");
  tree->Branch("F7PPAC2A_diff_y",&F7PPAC2A_diff_y,"F7PPAC2A_diff_y/D");
  tree->Branch("F7PPAC2B_diff_x",&F7PPAC2B_diff_x,"F7PPAC2B_diff_x/D");
  tree->Branch("F7PPAC2B_diff_y",&F7PPAC2B_diff_y,"F7PPAC2B_diff_y/D");

  tree->Branch("F7X",&F7X,"F7X/D");
  tree->Branch("F7A",&F7A,"F7A/D");
  tree->Branch("F7Y",&F7Y,"F7Y/D");
  tree->Branch("F7B",&F7B,"F7B/D");

  tree->Branch("F7PLA_TL_raw",&F7PLA_TL_raw,"F7PLA_TL_raw/D");
  tree->Branch("F7PLA_TR_raw",&F7PLA_TR_raw,"F7PLA_TR_raw/D");
  tree->Branch("F7PLA_TL",&F7PLA_TL,"F7PLA_TL/D");
  tree->Branch("F7PLA_TR",&F7PLA_TR,"F7PLA_TR/D");
  tree->Branch("F7PLA_T",&F7PLA_T,"F7PLA_T/D");

  tree->Branch("F7PLA_QL_raw",&F7PLA_QL_raw,"F7PLA_QL_raw/I");
  tree->Branch("F7PLA_QR_raw",&F7PLA_QR_raw,"F7PLA_QR_raw/I");
  tree->Branch("F7PLA_Q_ave",&F7PLA_Q_ave,"F7PLA_Q_ave/I");

  tree->Branch("F8PPAC1A_X",&F8PPAC1A_X,"F8PPAC1A_X/D");
  tree->Branch("F8PPAC1A_Y",&F8PPAC1A_Y,"F8PPAC1A_Y/D");
  tree->Branch("F8PPAC1B_X",&F8PPAC1B_X,"F8PPAC1B_X/D");
  tree->Branch("F8PPAC1B_Y",&F8PPAC1B_Y,"F8PPAC1B_Y/D");
  tree->Branch("F8PPAC2A_X",&F8PPAC2A_X,"F8PPAC2A_X/D");
  tree->Branch("F8PPAC2A_Y",&F8PPAC2A_Y,"F8PPAC2A_Y/D");
  tree->Branch("F8PPAC2B_X",&F8PPAC2B_X,"F8PPAC2B_X/D");
  tree->Branch("F8PPAC2B_Y",&F8PPAC2A_Y,"F8PPAC2B_Y/D");
  tree->Branch("F8PPAC3A_X",&F8PPAC3A_X,"F8PPAC3A_X/D");
  tree->Branch("F8PPAC3A_Y",&F8PPAC3A_Y,"F8PPAC3A_Y/D");
  tree->Branch("F8PPAC3B_X",&F8PPAC3B_X,"F8PPAC3B_X/D");
  tree->Branch("F8PPAC3B_Y",&F8PPAC3B_Y,"F8PPAC3B_Y/D");

  tree->Branch("F8PPAC1A_sum_x",&F8PPAC1A_sum_x,"F8PPAC1A_sum_x/D");
  tree->Branch("F8PPAC1A_sum_y",&F8PPAC1A_sum_y,"F8PPAC1A_sum_y/D");
  tree->Branch("F8PPAC1B_sum_x",&F8PPAC1B_sum_x,"F8PPAC1B_sum_x/D");
  tree->Branch("F8PPAC1B_sum_y",&F8PPAC1B_sum_y,"F8PPAC1B_sum_y/D");
  tree->Branch("F8PPAC2A_sum_x",&F8PPAC2A_sum_x,"F8PPAC2A_sum_x/D");
  tree->Branch("F8PPAC2A_sum_y",&F8PPAC2A_sum_y,"F8PPAC2A_sum_y/D");
  tree->Branch("F8PPAC2B_sum_x",&F8PPAC2B_sum_x,"F8PPAC2B_sum_x/D");
  tree->Branch("F8PPAC2B_sum_y",&F8PPAC2A_sum_y,"F8PPAC2B_sum_y/D");
  tree->Branch("F8PPAC3A_sum_x",&F8PPAC3A_sum_x,"F8PPAC3A_sum_x/D");
  tree->Branch("F8PPAC3A_sum_y",&F8PPAC3A_sum_y,"F8PPAC3A_sum_y/D");
  tree->Branch("F8PPAC3B_sum_x",&F8PPAC3B_sum_x,"F8PPAC3B_sum_x/D");
  tree->Branch("F8PPAC3B_sum_y",&F8PPAC3B_sum_y,"F8PPAC3B_sum_y/D");

  tree->Branch("F8PPAC1A_diff_x",&F8PPAC1A_diff_x,"F8PPAC1A_diff_x/D");
  tree->Branch("F8PPAC1A_diff_y",&F8PPAC1A_diff_y,"F8PPAC1A_diff_y/D");
  tree->Branch("F8PPAC1B_diff_x",&F8PPAC1B_diff_x,"F8PPAC1B_diff_x/D");
  tree->Branch("F8PPAC1B_diff_y",&F8PPAC1B_diff_y,"F8PPAC1B_diff_y/D");
  tree->Branch("F8PPAC2A_diff_x",&F8PPAC2A_diff_x,"F8PPAC2A_diff_x/D");
  tree->Branch("F8PPAC2A_diff_y",&F8PPAC2A_diff_y,"F8PPAC2A_diff_y/D");
  tree->Branch("F8PPAC2B_diff_x",&F8PPAC2B_diff_x,"F8PPAC2B_diff_x/D");
  tree->Branch("F8PPAC2B_diff_y",&F8PPAC2B_diff_y,"F8PPAC2B_diff_y/D");
  tree->Branch("F8PPAC3A_diff_x",&F8PPAC3A_diff_x,"F8PPAC3A_diff_x/D");
  tree->Branch("F8PPAC3A_diff_y",&F8PPAC3A_diff_y,"F8PPAC3A_diff_y/D");
  tree->Branch("F8PPAC3B_diff_x",&F8PPAC3B_diff_x,"F8PPAC3B_diff_x/D");
  tree->Branch("F8PPAC3B_diff_y",&F8PPAC3B_diff_y,"F8PPAC3B_diff_y/D");

  tree->Branch("F8X",&F8X,"F8X/D");
  tree->Branch("F8A",&F8A,"F8A/D");
  tree->Branch("F8Y",&F8Y,"F8Y/D");
  tree->Branch("F8B",&F8B,"F8B/D");

  tree->Branch("F8PLA_TL_raw",&F8PLA_TL_raw,"F8PLA_TL_raw/D");
  tree->Branch("F8PLA_TR_raw",&F8PLA_TR_raw,"F8PLA_TR_raw/D");
  tree->Branch("F8PLA_TL",&F8PLA_TL,"F8PLA_TL/D");
  tree->Branch("F8PLA_TR",&F8PLA_TR,"F8PLA_TR/D");
  tree->Branch("F8PLA_T",&F8PLA_T,"F8PLA_T/D");

  tree->Branch("F8PLA_QL_raw",&F8PLA_QL_raw,"F8PLA_QL_raw/I");
  tree->Branch("F8PLA_QR_raw",&F8PLA_QR_raw,"F8PLA_QR_raw/I");
  tree->Branch("F8PLA_Q_ave",&F8PLA_Q_ave,"F8PLA_Q_ave/I");

  tree->Branch("F9PPAC1A_X",&F9PPAC1A_X,"F9PPAC1A_X/D");
  tree->Branch("F9PPAC1A_Y",&F9PPAC1A_Y,"F9PPAC1A_Y/D");
  tree->Branch("F9PPAC1B_X",&F9PPAC1B_X,"F9PPAC1B_X/D");
  tree->Branch("F9PPAC1B_Y",&F9PPAC1A_Y,"F9PPAC1B_Y/D");
  tree->Branch("F9PPAC2A_X",&F9PPAC2A_X,"F9PPAC2A_X/D");
  tree->Branch("F9PPAC2A_Y",&F9PPAC2A_Y,"F9PPAC2A_Y/D");
  tree->Branch("F9PPAC2B_X",&F9PPAC2B_X,"F9PPAC2B_X/D");
  tree->Branch("F9PPAC2B_Y",&F9PPAC2A_Y,"F9PPAC2B_Y/D");
  
  tree->Branch("F9PPAC1A_sum_x",&F9PPAC1A_sum_x,"F9PPAC1A_sum_x/D");
  tree->Branch("F9PPAC1A_sum_y",&F9PPAC1A_sum_y,"F9PPAC1A_sum_y/D");
  tree->Branch("F9PPAC1B_sum_x",&F9PPAC1B_sum_x,"F9PPAC1B_sum_x/D");
  tree->Branch("F9PPAC1B_sum_y",&F9PPAC1B_sum_y,"F9PPAC1B_sum_y/D");
  tree->Branch("F9PPAC2A_sum_x",&F9PPAC2A_sum_x,"F9PPAC2A_sum_x/D");
  tree->Branch("F9PPAC2A_sum_y",&F9PPAC2A_sum_y,"F9PPAC2A_sum_y/D");
  tree->Branch("F9PPAC2B_sum_x",&F9PPAC2B_sum_x,"F9PPAC2B_sum_x/D");
  tree->Branch("F9PPAC2B_sum_y",&F9PPAC2B_sum_y,"F9PPAC2B_sum_y/D");
		 
  tree->Branch("F9PPAC1A_diff_x",&F9PPAC1A_diff_x,"F9PPAC1A_diff_x/D");
  tree->Branch("F9PPAC1A_diff_y",&F9PPAC1A_diff_y,"F9PPAC1A_diff_y/D");
  tree->Branch("F9PPAC1B_diff_x",&F9PPAC1B_diff_x,"F9PPAC1B_diff_x/D");
  tree->Branch("F9PPAC1B_diff_y",&F9PPAC1B_diff_y,"F9PPAC1B_diff_y/D");
  tree->Branch("F9PPAC2A_diff_x",&F9PPAC2A_diff_x,"F9PPAC2A_diff_x/D");
  tree->Branch("F9PPAC2A_diff_y",&F9PPAC2A_diff_y,"F9PPAC2A_diff_y/D");
  tree->Branch("F9PPAC2B_diff_x",&F9PPAC2B_diff_x,"F9PPAC2B_diff_x/D");
  tree->Branch("F9PPAC2B_diff_y",&F9PPAC2B_diff_y,"F9PPAC2B_diff_y/D");

  tree->Branch("F9X",&F9X,"F9X/D");
  tree->Branch("F9A",&F9A,"F9A/D");
  tree->Branch("F9Y",&F9Y,"F9Y/D");
  tree->Branch("F9B",&F9B,"F9B/D");
    
  tree->Branch("F11PPAC1A_X",&F11PPAC1A_X,"F11PPAC1A_X/D");
  tree->Branch("F11PPAC1A_Y",&F11PPAC1A_Y,"F11PPAC1A_Y/D");
  tree->Branch("F11PPAC1B_X",&F11PPAC1B_X,"F11PPAC1B_X/D");
  tree->Branch("F11PPAC1B_Y",&F11PPAC1A_Y,"F11PPAC1B_Y/D");
  tree->Branch("F11PPAC2A_X",&F11PPAC2A_X,"F11PPAC2A_X/D");
  tree->Branch("F11PPAC2A_Y",&F11PPAC2A_Y,"F11PPAC2A_Y/D");
  tree->Branch("F11PPAC2B_X",&F11PPAC2B_X,"F11PPAC2B_X/D");
  tree->Branch("F11PPAC2B_Y",&F11PPAC2A_Y,"F11PPAC2B_Y/D");

  tree->Branch("F11PPAC1A_sum_x",&F11PPAC1A_sum_x,"F11PPAC1A_sum_x/D");
  tree->Branch("F11PPAC1A_sum_y",&F11PPAC1A_sum_y,"F11PPAC1A_sum_y/D");
  tree->Branch("F11PPAC1B_sum_x",&F11PPAC1B_sum_x,"F11PPAC1B_sum_x/D");
  tree->Branch("F11PPAC1B_sum_y",&F11PPAC1B_sum_y,"F11PPAC1B_sum_y/D");
  tree->Branch("F11PPAC2A_sum_x",&F11PPAC2A_sum_x,"F11PPAC2A_sum_x/D");
  tree->Branch("F11PPAC2A_sum_y",&F11PPAC2A_sum_y,"F11PPAC2A_sum_y/D");
  tree->Branch("F11PPAC2B_sum_x",&F11PPAC2B_sum_x,"F11PPAC2B_sum_x/D");
  tree->Branch("F11PPAC2B_sum_y",&F11PPAC2B_sum_y,"F11PPAC2B_sum_y/D");
		 
  tree->Branch("F11PPAC1A_diff_x",&F11PPAC1A_diff_x,"F11PPAC1A_diff_x/D");
  tree->Branch("F11PPAC1A_diff_y",&F11PPAC1A_diff_y,"F11PPAC1A_diff_y/D");
  tree->Branch("F11PPAC1B_diff_x",&F11PPAC1B_diff_x,"F11PPAC1B_diff_x/D");
  tree->Branch("F11PPAC1B_diff_y",&F11PPAC1B_diff_y,"F11PPAC1B_diff_y/D");
  tree->Branch("F11PPAC2A_diff_x",&F11PPAC2A_diff_x,"F11PPAC2A_diff_x/D");
  tree->Branch("F11PPAC2A_diff_y",&F11PPAC2A_diff_y,"F11PPAC2A_diff_y/D");
  tree->Branch("F11PPAC2B_diff_x",&F11PPAC2B_diff_x,"F11PPAC2B_diff_x/D");
  tree->Branch("F11PPAC2B_diff_y",&F11PPAC2B_diff_y,"F11PPAC2B_diff_y/D");

  tree->Branch("F11X",&F11X,"F11X/D");
  tree->Branch("F11A",&F11A,"F11A/D");
  tree->Branch("F11Y",&F11Y,"F11Y/D");
  tree->Branch("F11B",&F11B,"F11B/D");

  tree->Branch("F11PLA_TL_raw",&F11PLA_TL_raw,"F11PLA_TL_raw/D");
  tree->Branch("F11PLA_TR_raw",&F11PLA_TR_raw,"F11PLA_TR_raw/D");
  tree->Branch("F11PLA_TL",&F11PLA_TL,"F11PLA_TL/D");
  tree->Branch("F11PLA_TR",&F11PLA_TR,"F11PLA_TR/D");
  tree->Branch("F11PLA_T",&F11PLA_T,"F11PLA_T/D");

  tree->Branch("F11PLA_QL_raw",&F11PLA_QL_raw,"F11PLA_QL_raw/I");
  tree->Branch("F11PLA_QR_raw",&F11PLA_QR_raw,"F11PLA_QR_raw/I");
  tree->Branch("F11PLA_Q_ave",&F11PLA_Q_ave,"F11PLA_Q_ave/I");

  tree->Branch("F11VetoPLA_TL_raw",&F11VetoPLA_TL_raw,"F11VetoPLA_TL_raw/D");
  tree->Branch("F11VetoPLA_TR_raw",&F11VetoPLA_TR_raw,"F11VetoPLA_TR_raw/D");
  tree->Branch("F11VetoPLA_TL",&F11VetoPLA_TL,"F11VetoPLA_TL/D");
  tree->Branch("F11VetoPLA_TR",&F11VetoPLA_TR,"F11VetoPLA_TR/D");
  tree->Branch("F11VetoPLA_T",&F11VetoPLA_T,"F11VetoPLA_T/D");

  tree->Branch("F11VetoPLA_QL_raw",&F11VetoPLA_QL_raw,"F11VetoPLA_QL_raw/I");
  tree->Branch("F11VetoPLA_QR_raw",&F11VetoPLA_QR_raw,"F11VetoPLA_QR_raw/I");
  tree->Branch("F11VetoPLA_Q_ave",&F11VetoPLA_Q_ave,"F11VetoPLA_Q_ave/I");

  tree->Branch("F11longPLA_TL_raw",&F11longPLA_TL_raw,"F11longPLA_TL_raw/D");
  tree->Branch("F11longPLA_TR_raw",&F11longPLA_TR_raw,"F11longPLA_TR_raw/D");
  tree->Branch("F11longPLA_TL",&F11longPLA_TL,"F11longPLA_TL/D");
  tree->Branch("F11longPLA_TR",&F11longPLA_TR,"F11longPLA_TR/D");
  tree->Branch("F11longPLA_T",&F11longPLA_T,"F11longPLA_T/D");

  tree->Branch("F11longPLA_QL_raw",&F11longPLA_QL_raw,"F11longPLA_QL_raw/I");
  tree->Branch("F11longPLA_QR_raw",&F11longPLA_QR_raw,"F11longPLA_QR_raw/I");
  tree->Branch("F11longPLA_Q_ave",&F11longPLA_Q_ave,"F11longPLA_Q_ave/I");

  tree->Branch("F7ICRawADC",F7ICRawADC,"F7ICRawADC[8]/I");
  tree->Branch("F7ICNumHit",&F7ICNumHit,"F7ICNumHit/I");
  tree->Branch("F7ICEnergySqSum",&F7ICEnergySqSum,"F7ICEnergySqSum/D");
  tree->Branch("F7ICEnergyAvSum",&F7ICEnergyAvSum,"F7ICEnergyAvSum/D");

  tree->Branch("F11ICRawADC",F11ICRawADC,"F11ICRawADC[8]/I");
  tree->Branch("F11ICRawTDC",F11ICRawTDC,"F11ICRawTDC[8]/I");
  tree->Branch("F11ICT",F11ICT,"F11ICT[8]/I");
  tree->Branch("F11ICNumHit",&F11ICNumHit,"F11ICNumHit/I");
  tree->Branch("F11ICEnergySqSum",&F11ICEnergySqSum,"F11ICEnergySqSum/D");
  tree->Branch("F11ICEnergyAvSum",&F11ICEnergyAvSum,"F11ICEnergyAvSum/D");

  tree->Branch("F11ICRawADC2",F11ICRawADC2,"F11ICRawADC2[8]/I");
  tree->Branch("F11ICRawTDC2",F11ICRawTDC2,"F11ICRawTDC2[8]/I");
  tree->Branch("F11ICT2",F11ICT2,"F11ICT2[8]/I");
  tree->Branch("F11ICNumHit2",&F11ICNumHit2,"F11ICNumHit2/I");
  tree->Branch("F11ICEnergySqSum2",&F11ICEnergySqSum2,"F11ICEnergySqSum2/D");
  tree->Branch("F11ICEnergyAvSum2",&F11ICEnergyAvSum2,"F11ICEnergyAvSum2/D");
  
  //---f11 tdc---                                                                                                       
  tree->Branch("F11TDCref",F11TDCref,"F11TDCref/I");
  tree->Branch("F11PLA_TR_F11T",F11PLA_TR_F11T,"F11PLA_TR_F11T/I");
  tree->Branch("F11PLA_TL_F11T",F11PLA_TL_F11T,"F11PLA_TL_F11T/I");
  tree->Branch("F11VetoPLA_TL_F11T",F11VetoPLA_TL_F11T,"F11VetoPLA_TL_F11T/I");
  tree->Branch("F11VetoPLA_TR_F11T",F11VetoPLA_TR_F11T,"F11VetoPLA_TR_F11T/I");
  tree->Branch("F11longPLA_TL_F11T",F11longPLA_TL_F11T,"F11longPLA_TL_F11T/I");
  tree->Branch("F11longPLA_TR_F11T",F11longPLA_TR_F11T,"F11longPLA_TR_F11T/I");
  //----

  tree->Branch("tof",tof,"tof[5]/D");
  tree->Branch("beta",beta,"beta[5]/D");
 
  tree->Branch("zet",zet,"zet[6]/D");
  tree->Branch("aoq",aoq,"aoq[6]/D");
  tree->Branch("zetc",zetc,"zetc[6]/D");
  tree->Branch("aoqc",aoqc,"aoqc[6]/D");

  tree->Branch("delta",delta,"delta[4]/D");

  neve=0; 
}

void MakeOnlineBigRIPSTree::Calculate()  {
  //cout<<"call Calculate()"<<endl;
  signal(SIGINT,stop_interrupt); // CTRL + C , interrupt

  TArtRawEventObject *rawevent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");

  int id = 0;
  int eventnum = rawevent->GetEventNumber();
  //cout<<"Eventumber: "<<eventnum<<endl;

  //-------F11 TDC-------                                                                                               
  double tdc[32];
  double timeref=-999999;
  for(int i=0;i<32;i++) tdc[i]=-9999999;
  for(int i=0;i<rawevent -> GetNumSeg();i++){
    TArtRawSegmentObject *seg = rawevent -> GetSegment(i);
    Int_t fpl = seg -> GetFP();
    Int_t detector = seg -> GetDetector();
    if(fpl==41 && detector==5){
      for(int j=0; j < seg -> GetNumData(); j++){
        TArtRawDataObject *d = seg -> GetData(j);
        //geo==12                                                                                                       
        int ch = d -> GetCh();
        int val = d -> GetVal();
        if(ch<32) tdc[ch]=val;
        //      if(ch==31) F11TDCref=val;                                                                               
      }
    }
  }

  if(0<tdc[31]){
    F11TDCref = tdc[31];
    for(int i=0; i<8; i++){
      F11ICRawTDC[i]  = tdc[i];
      F11ICRawTDC2[i] = tdc[i+8];
      F11ICT[i] = tdc[i] - F11TDCref;
      F11ICT2[i] = tdc[i+8] - F11TDCref;
    }
    F11PLA_TR_F11T = tdc[16] - F11TDCref;
    F11PLA_TL_F11T = tdc[17] - F11TDCref;
    //    F11PLA_TUR_F11T = tdc[16] - F11TDCref;
    //    F11PLA_TUL_F11T = tdc[17] - F11TDCref;
    //    F11PLA_TDR_F11T = tdc[18] - F11TDCref;
    //    F11PLA_TDL_F11T = tdc[19] - F11TDCref;
    F11VetoPLA_TR_F11T = tdc[20] - F11TDCref;
    F11VetoPLA_TL_F11T = tdc[21] - F11TDCref;
    F11longPLA_TR_F11T = tdc[22] - F11TDCref;
    F11longPLA_TL_F11T = tdc[23] - F11TDCref;
  }
  //----------F11 TDC end-----------    

  TClonesArray *info = (TClonesArray*)sman->FindDataContainer("EventInfo");
  int triggerbit = -9999;
  fbit = 0;
  //triggerbit = (Int_t)((TArtEventInfo *)info->At(0))->GetTriggerBit();

  for(int i=0;i<rawevent -> GetNumSeg();i++){
    TArtRawSegmentObject *seg = rawevent -> GetSegment(i);
    Int_t fpl = seg -> GetFP();
    Int_t detector = seg -> GetDetector();
    if(fpl==63 && detector==10){
      for(int j=0; j < seg -> GetNumData(); j++){
        TArtRawDataObject *d = seg -> GetData(j);
        triggerbit = d -> GetVal();
      }
    }
  }
  fbit=triggerbit;
  //for(Int_t i = 0; i < 7; i++){
  //  if ((triggerbit >> i) & 0x1)
  //    fbit = i+1;
  //} 
  
 
  cpid->ReconstructData();
  recopid->ReconstructData();
  
  //The ppacs
  F3PPAC1A_X=-9999; F3PPAC1A_Y=-9999; F3PPAC1B_X=-9999; F3PPAC1B_Y=-9999;
  F3PPAC2A_X=-9999; F3PPAC2A_Y=-9999; F3PPAC2B_X=-9999; F3PPAC2B_Y=-9999;
  
  F3PPAC1A_sum_x=-9999; F3PPAC1A_sum_y=-9999; F3PPAC1B_sum_x=-9999; F3PPAC1B_sum_y=-9999;
  F3PPAC2A_sum_x=-9999; F3PPAC2A_sum_y=-9999; F3PPAC2B_sum_x=-9999; F3PPAC2B_sum_y=-9999;

  F3PPAC1A_diff_x=-9999; F3PPAC1A_diff_y=-9999; F3PPAC1B_diff_x=-9999; F3PPAC1B_diff_y=-9999;
  F3PPAC2A_diff_x=-9999; F3PPAC2A_diff_y=-9999; F3PPAC2B_diff_x=-9999; F3PPAC2B_diff_y=-9999;
  
  F5PPAC1A_X=-9999; F5PPAC1A_Y=-9999; F5PPAC1B_X=-9999; F5PPAC1B_Y=-9999;
  F5PPAC2A_X=-9999; F5PPAC2A_Y=-9999; F5PPAC2B_X=-9999; F5PPAC2B_Y=-9999;

  F5PPAC1A_sum_x=-9999; F5PPAC1A_sum_y=-9999; F5PPAC1B_sum_x=-9999; F5PPAC1B_sum_y=-9999;
  F5PPAC2A_sum_x=-9999; F5PPAC2A_sum_y=-9999; F5PPAC2B_sum_x=-9999; F5PPAC2B_sum_y=-9999;
   
  F5PPAC1A_diff_x=-9999; F5PPAC1A_diff_y=-9999; F5PPAC1B_diff_x=-9999; F5PPAC1B_diff_y=-9999;
  F5PPAC2A_diff_x=-9999; F5PPAC2A_diff_y=-9999; F5PPAC2B_diff_x=-9999; F5PPAC2B_diff_y=-9999;
  
  F7PPAC1A_X=-9999; F7PPAC1A_Y=-9999; F7PPAC1B_X=-9999; F7PPAC1B_Y=-9999;
  F7PPAC2A_X=-9999; F7PPAC2A_Y=-9999; F7PPAC2B_X=-9999; F7PPAC2B_Y=-9999;
  
  F7PPAC1A_sum_x=-9999; F7PPAC1A_sum_y=-9999; F7PPAC1B_sum_x=-9999; F7PPAC1B_sum_y=-9999;
  F7PPAC2A_sum_x=-9999; F7PPAC2A_sum_y=-9999; F7PPAC2B_sum_x=-9999; F7PPAC2B_sum_y=-9999;
   
  F7PPAC1A_diff_x=-9999; F7PPAC1A_diff_y=-9999; F7PPAC1B_diff_x=-9999; F7PPAC1B_diff_y=-9999;
  F7PPAC2A_diff_x=-9999; F7PPAC2A_diff_y=-9999; F7PPAC2B_diff_x=-9999; F7PPAC2B_diff_y=-9999;

  F8PPAC1A_X=-9999; F8PPAC1A_Y=-9999; F8PPAC1B_X=-9999; F8PPAC1B_Y=-9999;
  F8PPAC2A_X=-9999; F8PPAC2A_Y=-9999; F8PPAC2B_X=-9999; F8PPAC2B_Y=-9999;
  F8PPAC3A_X=-9999; F8PPAC3A_Y=-9999; F8PPAC3B_X=-9999; F8PPAC3B_Y=-9999;

  F8PPAC1A_sum_x=-9999; F8PPAC1A_sum_y=-9999; F8PPAC1B_sum_x=-9999; F8PPAC1B_sum_y=-9999;
  F8PPAC2A_sum_x=-9999; F8PPAC2A_sum_y=-9999; F8PPAC2B_sum_x=-9999; F8PPAC2B_sum_y=-9999;
  F8PPAC3A_sum_x=-9999; F8PPAC3A_sum_y=-9999; F8PPAC3B_sum_x=-9999; F8PPAC3B_sum_y=-9999;
   
  F8PPAC1A_diff_x=-9999; F8PPAC1A_diff_y=-9999; F8PPAC1B_diff_x=-9999; F8PPAC1B_diff_y=-9999;
  F8PPAC2A_diff_x=-9999; F8PPAC2A_diff_y=-9999; F8PPAC2B_diff_x=-9999; F8PPAC2B_diff_y=-9999;
  F8PPAC2A_diff_x=-9999; F8PPAC2A_diff_y=-9999; F8PPAC2B_diff_x=-9999; F8PPAC2B_diff_y=-9999;

  F9PPAC1A_X=-9999; F9PPAC1A_Y=-9999; F9PPAC1B_X=-9999; F9PPAC1B_Y=-9999;
  F9PPAC2A_X=-9999; F9PPAC2A_Y=-9999; F9PPAC2B_X=-9999; F9PPAC2B_Y=-9999;

  F9PPAC1A_sum_x=-9999; F9PPAC1A_sum_y=-9999; F9PPAC1B_sum_x=-9999; F9PPAC1B_sum_y=-9999;
  F9PPAC2A_sum_x=-9999; F9PPAC2A_sum_y=-9999; F9PPAC2B_sum_x=-9999; F9PPAC2B_sum_y=-9999;
   
  F9PPAC1A_diff_x=-9999; F9PPAC1A_diff_y=-9999; F9PPAC1B_diff_x=-9999; F9PPAC1B_diff_y=-9999;
  F9PPAC2A_diff_x=-9999; F9PPAC2A_diff_y=-9999; F9PPAC2B_diff_x=-9999; F9PPAC2B_diff_y=-9999;
  
  F11PPAC1A_X=-9999; F11PPAC1A_Y=-9999; F11PPAC1B_X=-9999; F11PPAC1B_Y=-9999;
  F11PPAC2A_X=-9999; F11PPAC2A_Y=-9999; F11PPAC2B_X=-9999; F11PPAC2B_Y=-9999;

  F11PPAC1A_sum_x=-9999; F11PPAC1A_sum_y=-9999; F11PPAC1B_sum_x=-9999; F11PPAC1B_sum_y=-9999;
  F11PPAC2A_sum_x=-9999; F11PPAC2A_sum_y=-9999; F11PPAC2B_sum_x=-9999; F11PPAC2B_sum_y=-9999;
   
  F11PPAC1A_diff_x=-9999; F7PPAC1A_diff_y=-9999; F11PPAC1B_diff_x=-9999; F11PPAC1B_diff_y=-9999;
  F11PPAC2A_diff_x=-9999; F7PPAC2A_diff_y=-9999; F11PPAC2B_diff_x=-9999; F11PPAC2B_diff_y=-9999;

  TArtPPAC *tppac;
  tppac = cppac->FindPPAC("F3PPAC-1A");
  if(tppac){F3PPAC1A_X = tppac->GetX(); F3PPAC1A_Y = tppac->GetY();
    F3PPAC1A_sum_x = tppac->GetTSumX(); F3PPAC1A_sum_y = tppac->GetTSumY();
    F3PPAC1A_diff_x = tppac->GetTDiffX(); F3PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F3PPAC-1B");
  if(tppac){F3PPAC1B_X = tppac->GetX(); F3PPAC1B_Y = tppac->GetY();
    F3PPAC1B_sum_x = tppac->GetTSumX(); F3PPAC1B_sum_y = tppac->GetTSumY();
    F3PPAC1B_diff_x = tppac->GetTDiffX(); F3PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F3PPAC-2A");
  if(tppac){F3PPAC2A_X = tppac->GetX(); F3PPAC2A_Y = tppac->GetY();
    F3PPAC2A_sum_x = tppac->GetTSumX(); F3PPAC2A_sum_y = tppac->GetTSumY();
    F3PPAC2A_diff_x = tppac->GetTDiffX(); F3PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F3PPAC-2B");
  if(tppac){F3PPAC2B_X = tppac->GetX(); F3PPAC2B_Y = tppac->GetY();
    F3PPAC2B_sum_x = tppac->GetTSumX(); F3PPAC2B_sum_y = tppac->GetTSumY();
    F3PPAC2B_diff_x = tppac->GetTDiffX(); F3PPAC2B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F5PPAC-1A");
  if(tppac){F5PPAC1A_X = tppac->GetX(); F5PPAC1A_Y = tppac->GetY();
    F5PPAC1A_sum_x = tppac->GetTSumX(); F5PPAC1A_sum_y = tppac->GetTSumY();
    F5PPAC1A_diff_x = tppac->GetTDiffX(); F5PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F5PPAC-1B");
  if(tppac){F5PPAC1B_X = tppac->GetX(); F5PPAC1B_Y = tppac->GetY();
    F5PPAC1B_sum_x = tppac->GetTSumX(); F5PPAC1B_sum_y = tppac->GetTSumY();
    F5PPAC1B_diff_x = tppac->GetTDiffX(); F5PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F5PPAC-2A");
  if(tppac){F5PPAC2A_X = tppac->GetX(); F5PPAC2A_Y = tppac->GetY();
    F5PPAC2A_sum_x = tppac->GetTSumX(); F5PPAC2A_sum_y = tppac->GetTSumY();
    F5PPAC2A_diff_x = tppac->GetTDiffX(); F5PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F5PPAC-2B");
  if(tppac){F5PPAC2B_X = tppac->GetX(); F5PPAC2B_Y = tppac->GetY();
    F5PPAC2B_sum_x = tppac->GetTSumX(); F5PPAC2B_sum_y = tppac->GetTSumY();
    F5PPAC2B_diff_x = tppac->GetTDiffX(); F5PPAC2B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F7PPAC-1A");
  if(tppac){F7PPAC1A_X = tppac->GetX(); F7PPAC1A_Y = tppac->GetY();
    F7PPAC1A_sum_x = tppac->GetTSumX(); F7PPAC1A_sum_y = tppac->GetTSumY();
    F7PPAC1A_diff_x = tppac->GetTDiffX(); F7PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F7PPAC-1B");
  if(tppac){F7PPAC1B_X = tppac->GetX(); F7PPAC1B_Y = tppac->GetY();
    F7PPAC1B_sum_x = tppac->GetTSumX(); F7PPAC1B_sum_y = tppac->GetTSumY();
    F7PPAC1B_diff_x = tppac->GetTDiffX(); F7PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F7PPAC-2A");
  if(tppac){F7PPAC2A_X = tppac->GetX(); F7PPAC2A_Y = tppac->GetY();
    F7PPAC2A_sum_x = tppac->GetTSumX(); F7PPAC2A_sum_y = tppac->GetTSumY();
    F7PPAC2A_diff_x = tppac->GetTDiffX(); F7PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F7PPAC-2B");
  if(tppac){F7PPAC2B_X = tppac->GetX(); F7PPAC2B_Y = tppac->GetY();
    F7PPAC2B_sum_x = tppac->GetTSumX(); F7PPAC2B_sum_y = tppac->GetTSumY();
    F7PPAC2B_diff_x = tppac->GetTDiffX(); F7PPAC2B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-1A");
  if(tppac){F8PPAC1A_X = tppac->GetX(); F8PPAC1A_Y = tppac->GetY();
    F8PPAC1A_sum_x = tppac->GetTSumX(); F8PPAC1A_sum_y = tppac->GetTSumY();
    F8PPAC1A_diff_x = tppac->GetTDiffX(); F8PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-1B");
  if(tppac){F8PPAC1B_X = tppac->GetX(); F8PPAC1B_Y = tppac->GetY();
    F8PPAC1B_sum_x = tppac->GetTSumX(); F8PPAC1B_sum_y = tppac->GetTSumY();
    F8PPAC1B_diff_x = tppac->GetTDiffX(); F8PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-2A");
  if(tppac){F8PPAC2A_X = tppac->GetX(); F8PPAC2A_Y = tppac->GetY();
    F8PPAC2A_sum_x = tppac->GetTSumX(); F8PPAC2A_sum_y = tppac->GetTSumY();
    F8PPAC2A_diff_x = tppac->GetTDiffX(); F8PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-2B");
  if(tppac){F8PPAC2B_X = tppac->GetX(); F8PPAC2B_Y = tppac->GetY();
    F8PPAC2B_sum_x = tppac->GetTSumX(); F8PPAC2B_sum_y = tppac->GetTSumY();
    F8PPAC2B_diff_x = tppac->GetTDiffX(); F8PPAC2B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-3A");
  if(tppac){F8PPAC3A_X = tppac->GetX(); F8PPAC3A_Y = tppac->GetY();
    F8PPAC3A_sum_x = tppac->GetTSumX(); F8PPAC3A_sum_y = tppac->GetTSumY();
    F8PPAC3A_diff_x = tppac->GetTDiffX(); F8PPAC3A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F8PPAC-3B");
  if(tppac){F8PPAC3B_X = tppac->GetX(); F8PPAC3B_Y = tppac->GetY();
    F8PPAC3B_sum_x = tppac->GetTSumX(); F8PPAC3B_sum_y = tppac->GetTSumY();
    F8PPAC3B_diff_x = tppac->GetTDiffX(); F8PPAC3B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F9PPAC-1A");
  if(tppac){F9PPAC1A_X = tppac->GetX(); F9PPAC1A_Y = tppac->GetY();
    F9PPAC1A_sum_x = tppac->GetTSumX(); F9PPAC1A_sum_y = tppac->GetTSumY();
    F9PPAC1A_diff_x = tppac->GetTDiffX(); F9PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F9PPAC-1B");
  if(tppac){F9PPAC1B_X = tppac->GetX(); F9PPAC1B_Y = tppac->GetY();
    F9PPAC1B_sum_x = tppac->GetTSumX(); F9PPAC1B_sum_y = tppac->GetTSumY();
    F9PPAC1B_diff_x = tppac->GetTDiffX(); F9PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F9PPAC-2A");
  if(tppac){F9PPAC2A_X = tppac->GetX(); F9PPAC2A_Y = tppac->GetY();
    F9PPAC2A_sum_x = tppac->GetTSumX(); F9PPAC2A_sum_y = tppac->GetTSumY();
    F9PPAC2A_diff_x = tppac->GetTDiffX(); F9PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F9PPAC-2B");
  if(tppac){F9PPAC2B_X = tppac->GetX(); F9PPAC2B_Y = tppac->GetY();
    F9PPAC2B_sum_x = tppac->GetTSumX(); F9PPAC2B_sum_y = tppac->GetTSumY();
    F9PPAC2B_diff_x = tppac->GetTDiffX(); F9PPAC2B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F11PPAC-1A");
  if(tppac){F11PPAC1A_X = tppac->GetX(); F11PPAC1A_Y = tppac->GetY();
    F11PPAC1A_sum_x = tppac->GetTSumX(); F11PPAC1A_sum_y = tppac->GetTSumY();
    F11PPAC1A_diff_x = tppac->GetTDiffX(); F11PPAC1A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F11PPAC-1B");
  if(tppac){F11PPAC1B_X = tppac->GetX(); F11PPAC1B_Y = tppac->GetY();
    F11PPAC1B_sum_x = tppac->GetTSumX(); F11PPAC1B_sum_y = tppac->GetTSumY();
    F11PPAC1B_diff_x = tppac->GetTDiffX(); F11PPAC1B_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F11PPAC-2A");
  if(tppac){F11PPAC2A_X = tppac->GetX(); F11PPAC2A_Y = tppac->GetY();
    F11PPAC2A_sum_x = tppac->GetTSumX(); F11PPAC2A_sum_y = tppac->GetTSumY();
    F11PPAC2A_diff_x = tppac->GetTDiffX(); F11PPAC2A_diff_y = tppac->GetTDiffY();
  }
  tppac = cppac->FindPPAC("F11PPAC-2B");
  if(tppac){F11PPAC2B_X = tppac->GetX(); F11PPAC2B_Y = tppac->GetY();
    F11PPAC2B_sum_x = tppac->GetTSumX(); F11PPAC2B_sum_y = tppac->GetTSumY();
    F11PPAC2B_diff_x = tppac->GetTDiffX(); F11PPAC2B_diff_y = tppac->GetTDiffY();
  }

  //The Focalplane:
  F3X=-9999; F3A=-9999; F3Y=-9999; F3B=-9999;
  F5X=-9999; F5A=-9999; F5Y=-9999; F5B=-9999;
  F7X=-9999; F7A=-9999; F7Y=-9999; F7B=-9999;
  F8X=-9999; F8A=-9999; F8Y=-9999; F8B=-9999;
  F9X=-9999; F9A=-9999; F9Y=-9999; F9B=-9999;
  F11X=-9999; F11A=-9999; F11Y=-9999; F11B=-9999;
  
  TArtFocalPlane *tfpl;
  TVectorD *vec;
  tfpl = cfpl->FindFocalPlane(3); 
  if(tfpl){vec=tfpl->GetOptVector(); F3X=(*vec)(0); F3A=(*vec)(1); F3Y=(*vec)(2); F3B=(*vec)(3);}
  tfpl = cfpl->FindFocalPlane(5); 
  if(tfpl){vec=tfpl->GetOptVector(); F5X=(*vec)(0); F5A=(*vec)(1); F5Y=(*vec)(2); F5B=(*vec)(3);}
  tfpl = cfpl->FindFocalPlane(7); 
  if(tfpl){vec=tfpl->GetOptVector(); F7X=(*vec)(0); F7A=(*vec)(1); F7Y=(*vec)(2); F7B=(*vec)(3);}
  tfpl = cfpl->FindFocalPlane(8); 
  if(tfpl){vec=tfpl->GetOptVector(); F8X=(*vec)(0); F8A=(*vec)(1); F8Y=(*vec)(2); F8B=(*vec)(3);}
  tfpl = cfpl->FindFocalPlane(9); 
  if(tfpl){vec=tfpl->GetOptVector(); F9X=(*vec)(0); F9A=(*vec)(1); F9Y=(*vec)(2); F9B=(*vec)(3);}
  tfpl = cfpl->FindFocalPlane(11); 
  if(tfpl){vec=tfpl->GetOptVector(); F11X=(*vec)(0); F11A=(*vec)(1); F11Y=(*vec)(2); F11B=(*vec)(3);}

  //The plastics
  F3PLA_TL_raw=-9999; F3PLA_TR_raw=-9999; F3PLA_TL=-9999; F3PLA_TR=-9999; F3PLA_T=-9999; 
  F3PLA_QL_raw=-9999; F3PLA_QR_raw=-9999; F3PLA_Q_ave=-9999; 

  F5PLA_TL_raw=-9999; F5PLA_TR_raw=-9999; F5PLA_TL=-9999; F5PLA_TR=-9999; F5PLA_T=-9999; 
  F5PLA_QL_raw=-9999; F5PLA_QR_raw=-9999; F5PLA_Q_ave=-9999; 
 
  F7PLA_TL_raw=-9999; F7PLA_TR_raw=-9999; F7PLA_TL=-9999; F7PLA_TR=-9999; F7PLA_T=-9999; 
  F7PLA_QL_raw=-9999; F7PLA_QR_raw=-9999; F7PLA_Q_ave=-9999;  
  
  F8PLA_TL_raw=-9999; F8PLA_TR_raw=-9999; F8PLA_TL=-9999; F8PLA_TR=-9999; F8PLA_T=-9999;
  F8PLA_QL_raw=-9999; F8PLA_QR_raw=-9999; F8PLA_Q_ave=-9999;
 
  F11PLA_QL_raw=-9999; F11PLA_QR_raw=-9999; F11PLA_TL=-9999; F11PLA_TR=-9999; F11PLA_T=-9999;
  F11PLA_QL_raw=-9999; F11PLA_QR_raw=-9999; F11PLA_Q_ave=-9999; 

  F11VetoPLA_QL_raw=-9999; F11VetoPLA_QR_raw=-9999; F11VetoPLA_TL=-9999; F11VetoPLA_TR=-9999; F11VetoPLA_T=-9999;
  F11VetoPLA_QL_raw=-9999; F11VetoPLA_QR_raw=-9999; F11VetoPLA_Q_ave=-9999; 

  F11longPLA_QL_raw=-9999; F11longPLA_QR_raw=-9999; F11longPLA_TL=-9999; F11longPLA_TR=-9999; F11longPLA_T=-9999;
  F11longPLA_QL_raw=-9999; F11longPLA_QR_raw=-9999; F11longPLA_Q_ave=-9999; 


  TArtPlastic *tpla;
  tpla = cpla->FindPlastic("F3pl");
  if(tpla){
    F3PLA_TL_raw = tpla->GetTLRaw(); F3PLA_TR_raw = tpla->GetTRRaw(); 
    F3PLA_TL = tpla->GetTimeL(); F3PLA_TR = tpla->GetTimeR(); 
    F3PLA_T = tpla->GetTime();

    F3PLA_QL_raw = tpla->GetQLRaw(); F3PLA_QR_raw = tpla->GetQRRaw();
    F3PLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F5pl");
  if(tpla){
    F5PLA_TL_raw = tpla->GetTLRaw(); F5PLA_TR_raw = tpla->GetTRRaw(); 
    F5PLA_TL = tpla->GetTimeL(); F5PLA_TR = tpla->GetTimeR(); 
    F5PLA_T = tpla->GetTime();

    F5PLA_QL_raw = tpla->GetQLRaw(); F5PLA_QR_raw = tpla->GetQRRaw();
    F5PLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F7pl");
  if(tpla){
    F7PLA_TL_raw = tpla->GetTLRaw(); F7PLA_TR_raw = tpla->GetTRRaw(); 
    F7PLA_TL = tpla->GetTimeL(); F7PLA_TR = tpla->GetTimeR(); 
    F7PLA_T = tpla->GetTime();

    F7PLA_QL_raw = tpla->GetQLRaw(); F7PLA_QR_raw = tpla->GetQRRaw(); 
    F7PLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F8pl");
  if(tpla){
    F8PLA_TL_raw = tpla->GetTLRaw(); F8PLA_TR_raw = tpla->GetTRRaw(); 
    F8PLA_TL = tpla->GetTimeL(); F8PLA_TR = tpla->GetTimeR(); 
    F8PLA_T = tpla->GetTime();

    F8PLA_QL_raw = tpla->GetQLRaw(); F8PLA_QR_raw = tpla->GetQRRaw(); 
    F8PLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F11pl-1");
  if(tpla){
    F11PLA_TL_raw = tpla->GetTLRaw(); F11PLA_TR_raw = tpla->GetTRRaw(); 
    F11PLA_TL = tpla->GetTimeL(); F11PLA_TR = tpla->GetTimeR(); 
    F11PLA_T = tpla->GetTime();

    F11PLA_QL_raw = tpla->GetQLRaw(); F11PLA_QR_raw = tpla->GetQRRaw(); 
    F11PLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F11veto");
  if(tpla){
    F11VetoPLA_TL_raw = tpla->GetTLRaw(); F11VetoPLA_TR_raw = tpla->GetTRRaw(); 
    F11VetoPLA_TL = tpla->GetTimeL(); F11VetoPLA_TR = tpla->GetTimeR(); 
    F11VetoPLA_T = tpla->GetTime();

    F11VetoPLA_QL_raw = tpla->GetQLRaw(); F11VetoPLA_QR_raw = tpla->GetQRRaw(); 
    F11VetoPLA_Q_ave = tpla->GetQAveRaw();
  }

  tpla = cpla->FindPlastic("F11long");
  if(tpla){
    F11longPLA_TL_raw = tpla->GetTLRaw(); F11longPLA_TR_raw = tpla->GetTRRaw(); 
    F11longPLA_TL = tpla->GetTimeL(); F11longPLA_TR = tpla->GetTimeR(); 
    F11longPLA_T = tpla->GetTime();

    F11longPLA_QL_raw = tpla->GetQLRaw(); F11longPLA_QR_raw = tpla->GetQRRaw(); 
    F11longPLA_Q_ave = tpla->GetQAveRaw();
  }
    
  //The MUSICs
  for(int i=0;i<8;i++) F7ICRawADC[i]=-9999;
  F7ICNumHit=-9999;
  F7ICEnergySqSum=-9999;
  F7ICEnergyAvSum=-9999;
  
  for(int i=0;i<8;i++) F11ICRawADC[i]=-9999;
  F11ICNumHit=-9999;
  F11ICEnergySqSum=-9999;
  F11ICEnergyAvSum=-9999;

  for(int i=0;i<8;i++) F11ICRawADC2[i]=-9999;
  F11ICNumHit2=-9999;
  F11ICEnergySqSum2=-9999;
  F11ICEnergyAvSum2=-9999;

  TArtIC *tic;  
  tic = cic->FindIC("F7IC");
  if(tic) {
    for(int i=0;i<8;i++)F7ICRawADC[i] = tic->GetRawADC(i);
    F7ICNumHit=tic->GetNumHit();
    F7ICEnergySqSum=tic->GetEnergySqSum();
    F7ICEnergyAvSum=tic->GetEnergyAvSum();
  }

  tic = cic->FindIC("F11IC");
  if(tic) {
    for(int i=0;i<8;i++)F11ICRawADC[i] = tic->GetRawADC(i);
    F11ICNumHit=tic->GetNumHit();
    F11ICEnergySqSum=tic->GetEnergySqSum();
    F11ICEnergyAvSum=tic->GetEnergyAvSum();
  }

   tic = cic->FindIC("F11IC_2");
  if(tic) {
    for(int i=0;i<8;i++)F11ICRawADC2[i] = tic->GetRawADC(i);
    F11ICNumHit2=tic->GetNumHit();
    F11ICEnergySqSum2=tic->GetEnergySqSum();
    F11ICEnergyAvSum2=tic->GetEnergyAvSum();
  }

  //The TOF
  tof[0] = tof3to7->GetTOF();
  beta[0] = tof3to7->GetBeta();
  
  tof[1] = tof8to11->GetTOF();
  beta[1] = tof8to11->GetBeta();

  tof[2] = tof3to5->GetTOF();
  beta[2]= tof3to5->GetBeta();

  tof[3] = tof5to7->GetTOF();
  beta[3]= tof5to7->GetBeta();
 
  tof[4] = tof7to8->GetTOF();
  beta[4]= tof7to8->GetBeta();

  //The PID
  zet[0] = beam_br_35->GetZet();
  aoq[0] = beam_br_35->GetAoQ();
  
  zet[1] = beam_br_57->GetZet();
  aoq[1] = beam_br_57->GetAoQ();

  zet[2] = beam_br_37->GetZet();
  aoq[2] = beam_br_37->GetAoQ();

  zet[3] = beam_zd_89->GetZet();
  aoq[3] = beam_zd_89->GetAoQ();
  
  zet[4] = beam_zd_911->GetZet();
  aoq[4] = beam_zd_911->GetAoQ();

  zet[5] = beam_zd_811->GetZet();
  aoq[5] = beam_zd_811->GetAoQ();

  /* 
  //For 66Cr:
  zetc[0] = zet[0]-0.21; //OK
  zetc[1] = zet[1]-0.2; //OK
  zetc[2] = zet[2]; //OK
  zetc[3] = zet[3]; //OK
  zetc[4] = zet[4]; //OK
  zetc[5] = zet[5]; //OK

  aoqc[0] = aoq[0]-0.041+0.000022*F5X+0.00005*F5A+(1058-F3PLA_Q_ave)*0.000017-(570-F7PLA_Q_ave)*0.000027; 
  aoqc[1] = aoq[1]+0.038+0.00002*F5X+0.00000015*F5X*F5X+0.00001*F5A-0.00007*F7A+0.0001*F7X+(1058-F3PLA_Q_ave)*0.000017-(570-F7PLA_Q_ave)*0.000022;
  aoqc[2] = aoq[2]+0.00002*F5X+0.00000015*F5X*F5X+0.00001*F5A-0.0001*F7X+0.000002*F7A*F7A+(1058-F3PLA_Q_ave)*0.000016-(570-F7PLA_Q_ave)*0.000022; //OK
  aoqc[3] = aoq[3]+0.0005*F8X-0.0004*F8A+0.000001*F9X*F9X-0.0003*F9A+(455-F8PLA_Q_ave)*0.000055-(1229-F11PLA_Q_ave)*0.000012;
  aoqc[4] = aoq[4]-0.0025+0.00003*F9X-0.0000005*F9X*F9X+0.0006*F9A-0.00005*F9A*F9A-0.0006*F11X+0.00001*F11X*F11X+0.00025*F11A+0.00002*F11A*F11A+(455-F8PLA_Q_ave)*0.000055-(1229-F11PLA_Q_ave)*0.000012; //OK
  aoqc[5] = aoq[5]+0.000025*F9X-0.0000005*F9X*F9X+0.001*F9A-0.00007*F9A*F9A+0.000002*F9A*F9A*F9A-0.00025*F11X+0.000012*F11X*F11X-0.0000003*F11X*F11X*F11X+0.000025*F11A*F11A+0.00005*F11A+(454-F8PLA_Q_ave)*0.00006-(1229-F11PLA_Q_ave)*0.00001; //OK
  */
  
  
  //For 72Fe:
  zetc[0] = zet[0]-0.16; //OK 
  zetc[1] = zet[1]-0.16; //OK
  zetc[2] = zet[2]; //OK
  zetc[3] = zet[3]; //OK
  zetc[4] = zet[4]; //OK
  zetc[5] = zet[5]; //OK

  aoqc[0] = aoq[0]-0.046-0.00015*F3X+0.0001*F3A+0.0000003*F5X*F5X+0.000012*(1185-F3PLA_Q_ave)-0.00002*(635-F7PLA_Q_ave);//OK
  aoqc[1] = aoq[1]+0.046+0.00001*F5X-0.00015*F7A+0.000012*(1185-F3PLA_Q_ave)-0.000015*(635-F7PLA_Q_ave); //OK
  aoqc[2] = aoq[2]+0.00002*F5X-0.0001*F7X+0.00001*F7X*F7X-0.0000002*F7A*F7A*F7A-0.00001*F7A+0.000012*(1185-F3PLA_Q_ave)-0.000017*(635-F7PLA_Q_ave);//OK
  aoqc[3] = aoq[3]+0.0008*F8X-0.0001*F8A+0.0000007*F9X*F9X+0.00002*(497-F8PLA_Q_ave);//OK
  aoqc[4] = aoq[4]+0.0000*F9X-0.0001*(F9A-2)*(F9A-2)+0.000035*(F11A+11)*(F11A+11)-0.0002*F11A-0.0009*F11X+0.00003*(497-F8PLA_Q_ave);//OK
  aoqc[5] = aoq[5]+0.000015*F9X-0.00005*(F9A-3)*(F9A-3)+0.00002*(F11A+11)*(F11A+11)-0.0001*F11A-0.0005*F11X+0.00003*(497-F8PLA_Q_ave);//OK
  
   
  
  /*
  //For 78Ni:
  zetc[0] = zet[0]-0.29; //OK
  zetc[1] = zet[1]-0.27; //OK
  zetc[2] = zet[2]; //OK
  zetc[3] = zet[3]; //OK
  zetc[4] = zet[4]; //OK
  zetc[5] = zet[5]; //OK

  aoqc[0] = aoq[0]-0.0491-0.00015*F3A-0.0001*F3X-0.00004*F5A+(1287-F3PLA_Q_ave)*0.000013-(560-F7PLA_Q_ave)*0.000025; //OK
  aoqc[1] = aoq[1]+0.047-0.000017*F7A+0.00001*F7X-0.00000*F5A+(1287-F3PLA_Q_ave)*0.000013-(560-F7PLA_Q_ave)*0.00002; //OK
  aoqc[2] = aoq[2]-0.0001*F5A+0.00001*F5X+(1287-F3PLA_Q_ave)*0.000013-(560-F7PLA_Q_ave)*0.00002; //OK
  aoqc[3] = aoq[3]+0.0000007*F9X*F9X+0.00055*F8X+0.00001*F8X*F8X+0.00025*F8A; //OK
  aoqc[4] = aoq[4]+0.002-0.0000002*F9X*F9X-0.00015*F9A-0.00005*F9A*F9A-0.001*F11X+0.000002*F11X*F11X+0.0002*F11A+0.00002*F11A*F11A+(560-F8PLA_Q_ave)*0.00002+(2235-F11PLA_Q_ave)*0.000003; //OK
  aoqc[5] = aoq[5]-0.00001*F9X+0.0002*F9A-0.00004*F9A*F9A-0.0006*F11X+0.000007*F11X*F11X+0.000011*F11A*F11A+(560-F8PLA_Q_ave)*0.00003-(2235-F11PLA_Q_ave)*0.000005; //OK
  //old
  //aoqc[5] = aoq[5]+0.00001*F9X+0.0002*F9A-0.00004*F9A*F9A-0.0006*F11X+0.000007*F11X*F11X+0.0001*F11A+0.000011*F11A*F11A+(560-F8PLA_Q_ave)*0.00003-(2235-F11PLA_Q_ave)*0.000005; //OK
  */

  //Delta 
  delta[0] = rips3to5->GetDelta();
  delta[1] = rips5to7->GetDelta();
  delta[2] = rips8to9->GetDelta();
  delta[3] = rips9to11->GetDelta();

  if(neve<100000)
  tree->Fill();
  neve++;

  //if(neve%1000==0)
  //  std::cout << "event: " << neve << std::endl;
  
  //********************* Clear *****************
  cpid->ClearData();
  recopid->ClearData();
  rawevent->Clear();
}

void MakeOnlineBigRIPSTree::Destruct()  {
  cout<<"call Destruct() !!" <<endl;

  delete cpid;
  cpid = 0;
  delete recopid;
  recopid = 0;
  
  if(bigripsparameters)   bigripsparameters->Delete();
  bigripsparameters= 0;
}

const char* MakeOnlineBigRIPSTree::ClassName() const  {
  return "MakeOnlineBigRIPSTree";
}
