// C++ Libraries
#include "signal.h"
#include "fstream"
#include "iostream"
using namespace std;

// ROOT Libraries
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TVector3.h"

// ANAROOT Libraries
#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtBigRIPSParameters.hh"
#include "TArtDALIParameters.hh"

#include "TArtCalibPID.hh"
#include "TArtCalibDALI.hh"
#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibIC.hh"
#include "TArtCalibFocalPlane.hh"

#include "TArtPlasticPara.hh"
#include "TArtPPACPara.hh"
#include "TArtICPara.hh"
#include "TArtFocalPlanePara.hh"

#include "TArtEventInfo.hh"
#include "TArtPlastic.hh"
#include "TArtIC.hh"
#include "TArtPPAC.hh"
#include "TArtRecoPID.hh"
#include "TArtRecoRIPS.hh"
#include "TArtRecoTOF.hh"
#include "TArtRecoBeam.hh"
#include "TArtFocalPlane.hh"
#include "TArtTOF.hh"
#include "TArtRIPS.hh"
#include "TArtBeam.hh"

#include "./macros/segidlist.h"

// #include "TArtMINOSParameters.hh"
// #include "TArtCalibMINOS.hh"
// #include "TArtAnalyzedMINOS.hh"
// #include "TArtTrackMINOS.hh"
// #include "TArtVertexMINOS.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void stop_interrupt()
{
  printf("keyboard interrupt\n");
  stoploop = true;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void Func_Print_Parameters(TArtBigRIPSParameters *para)
{
	// Print parameters for detectors
	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	cout << "\t Hey Divyang, here are the PPAC parameters" << endl;
	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	para -> PrintListOfPPACPara();

	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	cout << "\t Hey Divyang, here are the Plastic parameters" << endl;
	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	para -> PrintListOfPlasticPara();

	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	cout << "\t Hey Divyang, here are the IC parameters" << endl;
	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
  para -> PrintListOfICPara();

	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	cout << "\t Hey Divyang, here are the Focal plane parameters" << endl;
	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
	para -> PrintListOfFocalPlanePara();

	cout << "\n....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......\n" << endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void MakeTree(char *infile, char *outfile, int runnum)
{
  cout << "\n MakeTree: " << infile << " -> " << outfile << "\n" << endl;
  
  //  signal(SIGINT,stop_interrupt); // CTRL + C , interrupt

  // Store Manager both for calibration (TArtCalib...) and treatment (TArtReco...)
  TArtStoreManager * sman = TArtStoreManager::Instance();
  
  // EventStore to control the loop and get the EventInfo
  TArtEventStore *estore = new TArtEventStore();
  estore -> SetInterrupt(&stoploop); 
  estore -> Open(infile);
  cout << "\n estore ->" << infile << "\n" << endl;
  
  // BigRIPSParameters to get Plastics, PPACs, ICs and FocalPlanes parameters from ".xml" files in "db" folder
  TArtBigRIPSParameters *para = TArtBigRIPSParameters::Instance();
  para -> LoadParameter("db/BigRIPSPPAC.xml");
  para -> LoadParameter("db/BigRIPSPlastic.xml");
  para -> LoadParameter("db/BigRIPSIC.xml");
  para -> LoadParameter("db/FocalPlane.xml");
  para -> SetFocusPosOffset(8,138.5);

  // CalibPID to get and calibrate raw data from PPAC, IC, Plastic, FocalPlane 
  TArtCalibPID        *brcalib      = new TArtCalibPID();
  TArtCalibPPAC       *ppaccalib    = brcalib -> GetCalibPPAC();
  TArtCalibPlastic    *plasticcalib = brcalib -> GetCalibPlastic();
  TArtCalibIC         *iccalib      = brcalib -> GetCalibIC(); 
  TArtCalibFocalPlane *cfpl         = brcalib -> GetCalibFocalPlane();
  
 	// RecoPID to get calibrated data and to reconstruct TOF, AoQ, Z,... (RecoPID -> [RecoTOF, RecoRIPS, RecoBeam])
  TArtRecoPID *recopid = new TArtRecoPID();

  // Print detector parameters
	Func_Print_Parameters(para);

  // Definition of observables we want to reconstruct
  cout << "\n  Defining bigrips parameters \n" << endl;  
  TArtRIPS *rips3to5  = recopid -> DefineNewRIPS(3, 5,  "matrix/mat1.mat",               "D3");    // F3 - F5
  TArtRIPS *rips5to7  = recopid -> DefineNewRIPS(5, 7,  "matrix/mat2.mat",               "D5");    // F5 - F7
  TArtRIPS *rips8to9  = recopid -> DefineNewRIPS(8, 9,  "matrix/F8F9_LargeAccAchr.mat",  "D7");    // F8 - F9
  TArtRIPS *rips9to11 = recopid -> DefineNewRIPS(9, 11, "matrix/F9F11_LargeAccAchr.mat", "D8");    // F9 - F11  

  // Reconstruction of TOF DefineNewTOF(fisrt plane, second plane, time offset)
  // For 66Cr
  // TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.88,5);     // F3 - F7   // setting used in online during RIBF132
  // TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl",-161.45,9);   // F8 - F11  // setting used in online during RIBF132
  // TArtTOF *tof7to8  = recopid->DefineNewTOF("F7pl","F8pl");              // F7 - F8   // setting used in online during RIBF132
  
  // Syntex: DefineNewTOF(up-stream fpl, down-stream fpl, Double_t TOF offset = 0, Int_t middle fpl = -1)
  TArtTOF *tof3to7  = recopid -> DefineNewTOF("F3pl", "F7pl",  (300.88  + 8.1), 5);   // F3 - F7  // rough adustment for RIBF132Unpack+Sort
  TArtTOF *tof8to11 = recopid -> DefineNewTOF("F8pl", "F11pl", (-161.45 - 5.5), 9);   // F8 - F11 // rough adustment for RIBF132Unpack+Sort
  TArtTOF *tof7to8  = recopid -> DefineNewTOF("F7pl", "F8pl",  80.6);                 // F7 - F8  // rough adustment for RIBF132Unpack+Sort

  
  //For 70,72Fe
  //TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.95,5); // F3 - F7
  //TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159,9); // F8 - F11

  //For 78Ni
  //TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.25,5); // F3 - F7
  //TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159.45,9); // F8 - F11
  


  // Reconstruction of IC observables for ID
  TArtBeam *beam_br_35  = recopid -> DefineNewBeam(rips3to5,  tof3to7,   (char*)("F7IC"));
  TArtBeam *beam_br_57  = recopid -> DefineNewBeam(rips5to7,  tof3to7,   "F7IC");   
  TArtBeam *beam_br_37  = recopid -> DefineNewBeam(rips3to5,  rips5to7,  tof3to7, "F7IC");
  
  TArtBeam *beam_zd_89  = recopid -> DefineNewBeam(rips8to9,  tof8to11,  "F11IC");
  TArtBeam *beam_zd_911 = recopid -> DefineNewBeam(rips9to11, tof8to11,  "F11IC");
  TArtBeam *beam_zd_811 = recopid -> DefineNewBeam(rips8to9,  rips9to11, tof8to11, "F11IC");

  // to get trigger pattern
  // TArtEventInfo *evtinfo = new TArtEventInfo();

  // DALIParameters to get ".xml"
  TArtDALIParameters *dpara = TArtDALIParameters::Instance();
  dpara -> LoadParameter("db/DALI.xml");
  
  // CalibDALI to get and calibrate raw data
  TArtCalibDALI *dalicalib = new TArtCalibDALI();

  cout << "\n para \n" << endl;

  TFile *fout = new TFile(outfile, "RECREATE");
  TTree *tree = new TTree("tree",  "tree");

  // define data nodes which are supposed to be dumped to tree 
  //EventInfo is important for the fBit information to know the trigger!
  TClonesArray *info_array = (TClonesArray *)sman -> FindDataContainer("EventInfo");

  int triggerbit = -9999;
  int fbit       = 0;

  cout << "\n" << info_array -> GetName() << "\n" << endl;
  tree -> Branch(info_array -> GetName(), &info_array);
  tree -> Branch("fbit", &fbit, "fbit/I");
  
  /*
  TClonesArray * ppac_array = (TClonesArray *)sman -> FindDataContainer("BigRIPSPPAC");
  cout << ppac_array->GetName() << endl;
  tree -> Branch(ppac_array->GetName(), &ppac_array);
  
  TClonesArray * pla_array = (TClonesArray *)sman -> FindDataContainer("BigRIPSPlastic");
  tree -> Branch(pla_array->GetName(), &pla_array);
 
  TClonesArray * ic_array = (TClonesArray *)sman -> FindDataContainer("BigRIPSIC");
  tree -> Branch(ic_array->GetName(), &ic_array);
  
  TClonesArray * fpl_array = (TClonesArray *)sman->FindDataContainer("BigRIPSFocalPlane");
  tree -> Branch(fpl_array->GetName(), &fpl_array);
  */
  
  //Dali data
  TClonesArray * dali_array = (TClonesArray *)sman->FindDataContainer("DALINaI");
  
  /*
  tree -> Branch(dali_array->GetName(),&dali_array);
  
  //PID reconstructed data:
  TClonesArray *rips_array = (TClonesArray *)sman->FindDataContainer("BigRIPSRIPS");
  cout << rips_array->GetName() << endl;     
  tree -> Branch(rips_array->GetName(), &rips_array); 
  
  TClonesArray *tof_array  = (TClonesArray *)sman->FindDataContainer("BigRIPSTOF");
  cout << tof_array->GetName() << endl;     
  tree -> Branch(tof_array->GetName(), &tof_array);   
  
  TClonesArray *beam_array = (TClonesArray *)sman->FindDataContainer("BigRIPSBeam");	
  cout << beam_array->GetName() << endl;     
  tree -> Branch(beam_array->GetName(), &beam_array); 
  */

	//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	//
	//                                BigRIPS tree
	//
	//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

	//______________________________________________________________________________
	//
	// 1. Focalplanes
	//______________________________________________________________________________

  
  // X position, x-angle A, Y position, y-angle B
  Double_t F3X  = -9999, F3A  = -9999, F3Y  = -9999, F3B  = -9999,
			     F5X  = -9999, F5A  = -9999, F5Y  = -9999, F5B  = -9999,
			     F7X  = -9999, F7A  = -9999, F7Y  = -9999, F7B  = -9999,
			     F8X  = -9999, F8A  = -9999, F8Y  = -9999, F8B  = -9999,
			     F9X  = -9999, F9A  = -9999, F9Y  = -9999, F9B  = -9999,
			     F11X = -9999, F11A = -9999, F11Y = -9999, F11B = -9999;
  
  tree->Branch("F3X",&F3X,"F3X/D");
  tree->Branch("F3A",&F3A,"F3A/D");
  tree->Branch("F3Y",&F3Y,"F3Y/D");
  tree->Branch("F3B",&F3B,"F3B/D");
    
  tree->Branch("F5X",&F5X,"F5X/D");
  tree->Branch("F5A",&F5A,"F5A/D");
  tree->Branch("F5Y",&F5Y,"F5Y/D");
  tree->Branch("F5B",&F5B,"F5B/D");

  tree->Branch("F7X",&F7X,"F7X/D");
  tree->Branch("F7A",&F7A,"F7A/D");
  tree->Branch("F7Y",&F7Y,"F7Y/D");
  tree->Branch("F7B",&F7B,"F7B/D");
  
  tree->Branch("F8X",&F8X,"F8X/D");
  tree->Branch("F8A",&F8A,"F8A/D");
  tree->Branch("F8Y",&F8Y,"F8Y/D");
  tree->Branch("F8B",&F8B,"F8B/D");
  
  tree->Branch("F9X",&F9X,"F9X/D");
  tree->Branch("F9A",&F9A,"F9A/D");
  tree->Branch("F9Y",&F9Y,"F9Y/D");
  tree->Branch("F9B",&F9B,"F9B/D");
  
  tree->Branch("F11X",&F11X,"F11X/D");
  tree->Branch("F11A",&F11A,"F11A/D");
  tree->Branch("F11Y",&F11Y,"F11Y/D");
  tree->Branch("F11B",&F11B,"F11B/D");

  //______________________________________________________________________________
	//
	// 2. Plastic time
	//______________________________________________________________________________

  Double_t F3PLA_TL_raw   = -9999; Double_t F3PLA_TR_raw   = -9999;  
  Double_t F5PLA_TL_raw   = -9999; Double_t F5PLA_TR_raw   = -9999;  
  Double_t F7PLA_TL_raw   = -9999; Double_t F7PLA_TR_raw   = -9999;  
  Double_t F8PLA_TL_raw   = -9999; Double_t F8PLA_TR_raw   = -9999;  
  Double_t F11PLA_TL_raw  = -9999; Double_t F11PLA_TR_raw  = -9999; 
  Double_t F11PLA2_TL_raw = -9999; Double_t F11PLA2_TR_raw = -9999; 
  Double_t F11LONG_TL_raw = -9999; Double_t F11LONG_TR_raw = -9999; 
  Double_t F11VETO_TL_raw = -9999; Double_t F11VETO_TR_raw = -9999;
  
  Double_t PLATDC_B3F_Trig = -9999.;

  tree -> Branch("F3PLA_TL_raw",  &F3PLA_TL_raw,  "F3PLA_TL_raw/D");
  tree -> Branch("F3PLA_TR_raw",  &F3PLA_TR_raw,  "F3PLA_TR_raw/D");
  tree -> Branch("F5PLA_TL_raw",  &F5PLA_TL_raw,  "F5PLA_TL_raw/D");
  tree -> Branch("F5PLA_TR_raw",  &F5PLA_TR_raw,  "F5PLA_TR_raw/D");
  tree -> Branch("F7PLA_TL_raw",  &F7PLA_TL_raw,  "F7PLA_TL_raw/D");
  tree -> Branch("F7PLA_TR_raw",  &F7PLA_TR_raw,  "F7PLA_TR_raw/D");
  tree -> Branch("F8PLA_TL_raw",  &F8PLA_TL_raw,  "F8PLA_TL_raw/D");
  tree -> Branch("F8PLA_TR_raw",  &F8PLA_TR_raw,  "F8PLA_TR_raw/D");
  tree -> Branch("F11PLA_TL_raw", &F11PLA_TL_raw, "F11PLA_TL_raw/D");
  tree -> Branch("F11PLA_TR_raw", &F11PLA_TR_raw, "F11PLA_TR_raw/D");
  // tree -> Branch("F11PLA2_TL_raw", &F11PLA2_TL_raw, "F11PLA2_TL_raw/D");
  // tree -> Branch("F11PLA2_TR_raw", &F11PLA2_TR_raw, "F11PLA2_TR_raw/D");
  tree -> Branch("F11LONG_TL_raw", &F11LONG_TL_raw, "F11LONG_TL_raw/D");
  tree -> Branch("F11LONG_TR_raw", &F11LONG_TR_raw, "F11LONG_TR_raw/D");
  tree -> Branch("F11VETO_TL_raw", &F11VETO_TL_raw, "F11VETO_TL_raw/D");
  tree -> Branch("F11VETO_TR_raw", &F11VETO_TR_raw, "F11VETO_TR_raw/D");

  tree -> Branch("PLATDC_B3F_Trig", &PLATDC_B3F_Trig, "PLATDC_B3F_Trig/D");
  
  const int max_multihit_pla = 4;
  Double_t F3PLA_TL_raw_multi[max_multihit_pla];
  Double_t F5PLA_TL_raw_multi[max_multihit_pla];
  Double_t F7PLA_TL_raw_multi[max_multihit_pla];
  Double_t F8PLA_TL_raw_multi[max_multihit_pla];
  Double_t F11PLA_TL_raw_multi[max_multihit_pla];
  Double_t F11PLA2_TL_raw_multi[max_multihit_pla];
  Double_t F11LONG_TL_raw_multi[max_multihit_pla];
  Double_t F11VETO_TL_raw_multi[max_multihit_pla];
  Double_t F3PLA_TR_raw_multi[max_multihit_pla];
  Double_t F5PLA_TR_raw_multi[max_multihit_pla];
  Double_t F7PLA_TR_raw_multi[max_multihit_pla];
  Double_t F8PLA_TR_raw_multi[max_multihit_pla];
  Double_t F11PLA_TR_raw_multi[max_multihit_pla];
  Double_t F11PLA2_TR_raw_multi[max_multihit_pla];
  Double_t F11LONG_TR_raw_multi[max_multihit_pla];
  Double_t F11VETO_TR_raw_multi[max_multihit_pla];

  Int_t F3PLA_TL_NumHit;
  Int_t F5PLA_TL_NumHit;
  Int_t F7PLA_TL_NumHit;
  Int_t F8PLA_TL_NumHit;
  Int_t F11PLA_TL_NumHit;
  Int_t F11PLA2_TL_NumHit;
  Int_t F11LONG_TL_NumHit;
  Int_t F11VETO_TL_NumHit;
  Int_t F3PLA_TR_NumHit;
  Int_t F5PLA_TR_NumHit;
  Int_t F7PLA_TR_NumHit;
  Int_t F8PLA_TR_NumHit;
  Int_t F11PLA_TR_NumHit;
  Int_t F11PLA2_TR_NumHit;
  Int_t F11LONG_TR_NumHit;
  Int_t F11VETO_TR_NumHit;
  
  tree -> Branch("F3PLA_TL_raw_multi",  F3PLA_TL_raw_multi,  Form("F3PLA_TL_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F3PLA_TR_raw_multi",  F3PLA_TR_raw_multi,  Form("F3PLA_TR_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F5PLA_TL_raw_multi",  F5PLA_TL_raw_multi,  Form("F5PLA_TL_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F5PLA_TR_raw_multi",  F5PLA_TR_raw_multi,  Form("F5PLA_TR_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F7PLA_TL_raw_multi",  F7PLA_TL_raw_multi,  Form("F7PLA_TL_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F7PLA_TR_raw_multi",  F7PLA_TR_raw_multi,  Form("F7PLA_TR_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F8PLA_TL_raw_multi",  F8PLA_TL_raw_multi,  Form("F8PLA_TL_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F8PLA_TR_raw_multi",  F8PLA_TR_raw_multi,  Form("F8PLA_TR_raw_multi[%d]/D",  max_multihit_pla));
  tree -> Branch("F11PLA_TL_raw_multi", F11PLA_TL_raw_multi, Form("F11PLA_TL_raw_multi[%d]/D", max_multihit_pla));
  tree -> Branch("F11PLA_TR_raw_multi", F11PLA_TR_raw_multi, Form("F11PLA_TR_raw_multi[%d]/D", max_multihit_pla));
  // tree -> Branch("F11PLA2_TL_raw_multi", F11PLA2_TL_raw_multi, Form("F11PLA2_TL_raw_multi[%d]/D", max_multihit_pla));
  // tree -> Branch("F11PLA2_TR_raw_multi", F11PLA2_TR_raw_multi, Form("F11PLA2_TR_raw_multi[%d]/D", max_multihit_pla));
  tree -> Branch("F11LONG_TL_raw_multi", F11LONG_TL_raw_multi, Form("F11LONG_TL_raw_multi[%d]/D", max_multihit_pla));
  tree -> Branch("F11LONG_TR_raw_multi", F11LONG_TR_raw_multi, Form("F11LONG_TR_raw_multi[%d]/D", max_multihit_pla));
  tree -> Branch("F11VETO_TL_raw_multi", F11VETO_TL_raw_multi, Form("F11VETO_TL_raw_multi[%d]/D", max_multihit_pla));
  tree -> Branch("F11VETO_TR_raw_multi", F11VETO_TR_raw_multi, Form("F11VETO_TR_raw_multi[%d]/D", max_multihit_pla));
  
  tree -> Branch("F3PLA_TL_NumHit",  &F3PLA_TL_NumHit,  "F3PLA_TL_NumHit/I");
  tree -> Branch("F3PLA_TR_NumHit",  &F3PLA_TR_NumHit,  "F3PLA_TR_NumHit/I");
  tree -> Branch("F5PLA_TL_NumHit",  &F5PLA_TL_NumHit,  "F5PLA_TL_NumHit/I");
  tree -> Branch("F5PLA_TR_NumHit",  &F5PLA_TR_NumHit,  "F5PLA_TR_NumHit/I");
  tree -> Branch("F7PLA_TL_NumHit",  &F7PLA_TL_NumHit,  "F7PLA_TL_NumHit/I");
  tree -> Branch("F7PLA_TR_NumHit",  &F7PLA_TR_NumHit,  "F7PLA_TR_NumHit/I");
  tree -> Branch("F8PLA_TL_NumHit",  &F8PLA_TL_NumHit,  "F8PLA_TL_NumHit/I");
  tree -> Branch("F8PLA_TR_NumHit",  &F8PLA_TR_NumHit,  "F8PLA_TR_NumHit/I");
  tree -> Branch("F11PLA_TL_NumHit", &F11PLA_TL_NumHit, "F11PLA_TL_NumHit/I");
  tree -> Branch("F11PLA_TR_NumHit", &F11PLA_TR_NumHit, "F11PLA_TR_NumHit/I");
  // tree -> Branch("F11PLA2_TL_NumHit", &F11PLA2_TL_NumHit, "F11PLA2_TL_NumHit/I");
  // tree -> Branch("F11PLA2_TR_NumHit", &F11PLA2_TR_NumHit, "F11PLA2_TR_NumHit/I");
  tree -> Branch("F11LONG_TL_NumHit", &F11LONG_TL_NumHit, "F11LONG_TL_NumHit/I");
  tree -> Branch("F11LONG_TR_NumHit", &F11LONG_TR_NumHit, "F11LONG_TR_NumHit/I");
  tree -> Branch("F11VETO_TL_NumHit", &F11VETO_TL_NumHit, "F11VETO_TL_NumHit/I");
  tree -> Branch("F11VETO_TR_NumHit", &F11VETO_TR_NumHit, "F11VETO_TR_NumHit/I");
  
  Double_t F3PLA_TL_raw_s   = -9999; Double_t F3PLA_TR_raw_s   = -9999;
  Double_t F5PLA_TL_raw_s   = -9999; Double_t F5PLA_TR_raw_s   = -9999;
  Double_t F7PLA_TL_raw_s   = -9999; Double_t F7PLA_TR_raw_s   = -9999;
  Double_t F8PLA_TL_raw_s   = -9999; Double_t F8PLA_TR_raw_s   = -9999;
  Double_t F11PLA_TL_raw_s  = -9999; Double_t F11PLA_TR_raw_s  = -9999;
  Double_t F11PLA2_TL_raw_s = -9999; Double_t F11PLA2_TR_raw_s = -9999;
  Double_t F11LONG_TL_raw_s = -9999; Double_t F11LONG_TR_raw_s = -9999;
  Double_t F11VETO_TL_raw_s = -9999; Double_t F11VETO_TR_raw_s = -9999;
  
  tree -> Branch("F3PLA_TL_raw_s",   &F3PLA_TL_raw_s,   "F3PLA_TL_raw_s/D");
  tree -> Branch("F3PLA_TR_raw_s",   &F3PLA_TR_raw_s,   "F3PLA_TR_raw_s/D");
  tree -> Branch("F5PLA_TL_raw_s",   &F5PLA_TL_raw_s,   "F5PLA_TL_raw_s/D");
  tree -> Branch("F5PLA_TR_raw_s",   &F5PLA_TR_raw_s,   "F5PLA_TR_raw_s/D");
  tree -> Branch("F7PLA_TL_raw_s",   &F7PLA_TL_raw_s,   "F7PLA_TL_raw_s/D");
  tree -> Branch("F7PLA_TR_raw_s",   &F7PLA_TR_raw_s,   "F7PLA_TR_raw_s/D");
  tree -> Branch("F8PLA_TL_raw_s",   &F8PLA_TL_raw_s,   "F8PLA_TL_raw_s/D");
  tree -> Branch("F8PLA_TR_raw_s",   &F8PLA_TR_raw_s,   "F8PLA_TR_raw_s/D");
  tree -> Branch("F11PLA_TL_raw_s",  &F11PLA_TL_raw_s,  "F11PLA_TL_raw_s/D");
  tree -> Branch("F11PLA_TR_raw_s",  &F11PLA_TR_raw_s,  "F11PLA_TR_raw_s/D");
  tree -> Branch("F11LONG_TL_raw_s", &F11LONG_TL_raw_s, "F11LONG_TL_raw_s/D");
  tree -> Branch("F11LONG_TR_raw_s", &F11LONG_TR_raw_s, "F11LONG_TR_raw_s/D");
  tree -> Branch("F11VETO_TL_raw_s", &F11VETO_TL_raw_s, "F11VETO_TL_raw_s/D");
  tree -> Branch("F11VETO_TR_raw_s", &F11VETO_TR_raw_s, "F11VETO_TR_raw_s/D");
  
  double platdc_cut_min_l[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double platdc_cut_max_l[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double platdc_cut_min_r[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double platdc_cut_max_r[7] = {-999., -999., -999., -999., -999., -999., -999.};
  
  // See RIBF-132_Overview.xlsx for the run information
	// Runnumber 1 to 20 are for calibration
  if(1 <= runnum && runnum <= 20)
  {
    platdc_cut_min_l[0] = 105000. + 18000.;  platdc_cut_max_l[0] = 120000. + 18000.;    // F3PLA
    platdc_cut_min_r[0] = 105000. + 18000.;  platdc_cut_max_r[0] = 120000. + 18000.;    // F3PLA
    
    platdc_cut_min_l[1] = 105000. + 18000.;  platdc_cut_max_l[1] = 120000. + 18000.;    // F5PLA
    platdc_cut_min_r[1] = 105000. + 18000.;  platdc_cut_max_r[1] = 120000. + 18000.;    // F5PLA
    
    platdc_cut_min_l[2] = 105000. + 18000.;  platdc_cut_max_l[2] = 120000. + 18000.;    // F7PLA
    platdc_cut_min_r[2] = 105000. + 18000.;  platdc_cut_max_r[2] = 120000. + 18000.;    // F7PLA
    
    platdc_cut_min_l[3] = 105000. + 18000.;  platdc_cut_max_l[3] = 120000. + 18000.;    // F8PLA
    platdc_cut_min_r[3] = 105000. + 18000.;  platdc_cut_max_r[3] = 120000. + 18000.;    // F8PLA
    
    platdc_cut_min_l[4] = 120000. + 18000.;  platdc_cut_max_l[4] = 135000. + 18000.;    // F11PLA
    platdc_cut_min_r[4] = 120000. + 18000.;  platdc_cut_max_r[4] = 135000. + 18000.;    // F11PLA
    
    platdc_cut_min_l[5] = 120000. + 18000.;  platdc_cut_max_l[5] = 135000. + 18000.;    // F11LONG
    platdc_cut_min_r[5] = 120000. + 18000.;  platdc_cut_max_r[5] = 135000. + 18000.;    // F11LONG
    
    platdc_cut_min_l[6] = 120000. + 18000.;  platdc_cut_max_l[6] = 135000. + 18000.;    // F11VETO
    platdc_cut_min_r[6] = 120000. + 18000.;  platdc_cut_max_r[6] = 135000. + 18000.;    // F11VETO
  }
  else if(21<=runnum && runnum <= 147)	  // Runnumber 21 to 147 are the actual experiment
  {
    platdc_cut_min_l[0] = 105000.;  platdc_cut_max_l[0] = 120000.;      // F3PLA
    platdc_cut_min_r[0] = 105000.;  platdc_cut_max_r[0] = 120000.;      // F3PLA
    
    platdc_cut_min_l[1] = 105000.;  platdc_cut_max_l[1] = 120000.;      // F5PLA
    platdc_cut_min_r[1] = 105000.;  platdc_cut_max_r[1] = 120000.;      // F5PLA
    
    platdc_cut_min_l[2] = 105000.;  platdc_cut_max_l[2] = 120000.;      // F7PLA
    platdc_cut_min_r[2] = 105000.;  platdc_cut_max_r[2] = 120000.;      // F7PLA
    
    platdc_cut_min_l[3] = 105000.;  platdc_cut_max_l[3] = 120000.;      // F8PLA
    platdc_cut_min_r[3] = 105000.;  platdc_cut_max_r[3] = 120000.;      // F8PLA
    
    platdc_cut_min_l[4] = 120000.;  platdc_cut_max_l[4] = 135000.;      // F11PLA
    platdc_cut_min_r[4] = 120000.;  platdc_cut_max_r[4] = 135000.;      // F11PLA
    
    platdc_cut_min_l[5] = 120000.;  platdc_cut_max_l[5] = 135000.;      // F11LONG
    platdc_cut_min_r[5] = 120000.;  platdc_cut_max_r[5] = 135000.;      // F11LONG
    
    platdc_cut_min_l[6] = 120000.;  platdc_cut_max_l[6] = 135000.;      // F11VETO
    platdc_cut_min_r[6] = 120000.;  platdc_cut_max_r[6] = 135000.;      // F11VETO
  }

  
  //______________________________________________________________________________
	//
	// 3. Plastic Q values
	//______________________________________________________________________________


  Double_t F3PLA_QL_raw   = -9999;  Double_t F3PLA_QR_raw   = -9999;  
  Double_t F5PLA_QL_raw   = -9999;  Double_t F5PLA_QR_raw   = -9999;  
  Double_t F7PLA_QL_raw   = -9999;  Double_t F7PLA_QR_raw   = -9999;  
  Double_t F8PLA_QL_raw   = -9999;  Double_t F8PLA_QR_raw   = -9999;  
  Double_t F11PLA_QL_raw  = -9999;  Double_t F11PLA_QR_raw  = -9999; 
  Double_t F11PLA2_QL_raw = -9999;  Double_t F11PLA2_QR_raw = -9999; 
  Double_t F11LONG_QL_raw = -9999;  Double_t F11LONG_QR_raw = -9999; 
  Double_t F11VETO_QL_raw = -9999;  Double_t F11VETO_QR_raw = -9999; 

  Double_t F3PLA_Q_ave   = -9999; 
  Double_t F5PLA_Q_ave   = -9999; 
  Double_t F7PLA_Q_ave   = -9999;   
  Double_t F8PLA_Q_ave   = -9999; 
  Double_t F11PLA_Q_ave  = -9999;
  Double_t F11PLA2_Q_ave = -9999;
  Double_t F11LONG_Q_ave = -9999;
  Double_t F11VETO_Q_ave = -9999;
  
  tree -> Branch("F3PLA_QL_raw", &F3PLA_QL_raw, "F3PLA_QL_raw/D");
  tree -> Branch("F3PLA_QR_raw", &F3PLA_QR_raw, "F3PLA_QR_raw/D");
  // tree -> Branch("F3PLA_Q_ave", &F3PLA_Q_ave, "F3PLA_Q_ave/D");

  tree -> Branch("F5PLA_QL_raw", &F5PLA_QL_raw, "F5PLA_QL_raw/D");
  tree -> Branch("F5PLA_QR_raw", &F5PLA_QR_raw, "F5PLA_QR_raw/D");
  // tree -> Branch("F5PLA_Q_ave", &F5PLA_Q_ave, "F5PLA_Q_ave/D");

  tree -> Branch("F7PLA_QL_raw", &F7PLA_QL_raw, "F7PLA_QL_raw/D");
  tree -> Branch("F7PLA_QR_raw", &F7PLA_QR_raw, "F7PLA_QR_raw/D");
  // tree -> Branch("F7PLA_Q_ave", &F7PLA_Q_ave, "F7PLA_Q_ave/D");

  tree -> Branch("F8PLA_QL_raw", &F8PLA_QL_raw, "F8PLA_QL_raw/D");
  tree -> Branch("F8PLA_QR_raw", &F8PLA_QR_raw, "F8PLA_QR_raw/D");
  // tree -> Branch("F8PLA_Q_ave", &F8PLA_Q_ave, "F8PLA_Q_ave/D");

  tree -> Branch("F11PLA_QL_raw", &F11PLA_QL_raw, "F11PLA_QL_raw/D");
  tree -> Branch("F11PLA_QR_raw", &F11PLA_QR_raw, "F11PLA_QR_raw/D");
  // tree -> Branch("F11PLA_Q_ave", &F11PLA_Q_ave, "F11PLA_Q_ave/D");

  // tree -> Branch("F11PLA2_QL_raw", &F11PLA2_QL_raw, "F11PLA2_QL_raw/D");
  // tree -> Branch("F11PLA2_QR_raw", &F11PLA2_QR_raw, "F11PLA2_QR_raw/D");
  // tree -> Branch("F11PLA2_Q_ave",  &F11PLA2_Q_ave,  "F11PLA2_Q_ave/D");

  tree -> Branch("F11LONG_QL_raw", &F11LONG_QL_raw, "F11LONG_QL_raw/D");
  tree -> Branch("F11LONG_QR_raw", &F11LONG_QR_raw, "F11LONG_QR_raw/D");
  // tree -> Branch("F11LONG_Q_ave", &F11LONG_Q_ave, "F11LONG_Q_ave/D");

  tree -> Branch("F11VETO_QL_raw", &F11VETO_QL_raw, "F11VETO_QL_raw/D");
  tree -> Branch("F11VETO_QR_raw", &F11VETO_QR_raw, "F11VETO_QR_raw/D");
  // tree -> Branch("F11VETO_Q_ave", &F11VETO_Q_ave, "F11VETO_Q_ave/D");


  //______________________________________________________________________________
	//
	// 4. MUSIC
	//______________________________________________________________________________


  const int max_multihit_f11tdc=4;
  
  Int_t    F7ICNumHit      = -9999;
  Double_t F7ICEnergySqSum = -9999;
  Double_t F7ICEnergyAvSum = -9999;
  Double_t F7ICADCraw[6]   = {-9999., -9999., -9999., -9999., -9999., -9999.};

  Int_t    F11IC1NumHit      = -9999;
  Double_t F11IC1EnergySqSum = -9999;
  Double_t F11IC1EnergyAvSum = -9999;
  Double_t F11IC1ADCraw[8]   = {-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.};
  Double_t F11IC1TDCraw[8]   = {-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.};
  Double_t F11IC1TDCraw_multi[8][max_multihit_f11tdc];
  Int_t    F11IC1TDC_NumHit[8];
  
  Int_t    F11IC2NumHit      = -9999;
  Double_t F11IC2EnergySqSum = -9999;
  Double_t F11IC2EnergyAvSum = -9999;
  Double_t F11IC2ADCraw[8]   = {-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.};
  Double_t F11IC2TDCraw[8]   = {-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.};
  Double_t F11IC2TDCraw_multi[8][max_multihit_f11tdc];
  Int_t    F11IC2TDC_NumHit[8];

  Int_t    F11VMETDC_NumHit[32];                            // not for tree
  Double_t F11VMETDCraw_multi[32][max_multihit_f11tdc];;    // not for tree
  Double_t F11VMETDCraw[32];;                               // not for tree

  Int_t    F11TDC_F11PLA_TL_NumHit;
  Double_t F11TDC_F11PLA_TL_raw;
  Double_t F11TDC_F11PLA_TL_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_F11PLA_TR_NumHit;
  Double_t F11TDC_F11PLA_TR_raw;
  Double_t F11TDC_F11PLA_TR_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_F11LONG_TL_NumHit;
  Double_t F11TDC_F11LONG_TL_raw;
  Double_t F11TDC_F11LONG_TL_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_F11LONG_TR_NumHit;
  Double_t F11TDC_F11LONG_TR_raw;
  Double_t F11TDC_F11LONG_TR_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_F11VETO_TL_NumHit;
  Double_t F11TDC_F11VETO_TL_raw;
  Double_t F11TDC_F11VETO_TL_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_F11VETO_TR_NumHit;
  Double_t F11TDC_F11VETO_TR_raw;
  Double_t F11TDC_F11VETO_TR_raw_multi[max_multihit_f11tdc];
  
  Int_t    F11TDC_TRIG_NumHit;
  Double_t F11TDC_TRIG_raw;
  Double_t F11TDC_TRIG_raw_multi[max_multihit_f11tdc];

  // tree -> Branch("F7ICNumHit", &F7ICNumHit, "F7ICNumHit/I");
  tree -> Branch("F7ICEnergySqSum", &F7ICEnergySqSum, "F7ICEnergySqSum/D");
  tree -> Branch("F7ICEnergyAvSum", &F7ICEnergyAvSum, "F7ICEnergyAvSum/D");
  tree -> Branch("F7ICADCraw",       F7ICADCraw,      "F7ICADCraw[6]/D");
    
  // tree -> Branch("F11IC1NumHit", &F11IC1NumHit, "F11IC1NumHit/I");
  tree -> Branch("F11IC1EnergySqSum",  &F11IC1EnergySqSum,  "F11IC1EnergySqSum/D");
  tree -> Branch("F11IC1EnergyAvSum",  &F11IC1EnergyAvSum,  "F11IC1EnergyAvSum/D");
  tree -> Branch("F11IC1ADCraw",        F11IC1ADCraw,       "F11IC1ADCraw[8]/D");
  tree -> Branch("F11IC1TDCraw",        F11IC1TDCraw,       "F11IC1TDCraw[8]/D");
  tree -> Branch("F11IC1TDCraw_multi",  F11IC1TDCraw_multi, Form("F11IC1TDCraw_multi[8][%d]/D", max_multihit_f11tdc));
  tree -> Branch("F11IC1TDC_NumHit",    F11IC1TDC_NumHit,   "F11IC1TDC_NumHit[8]/I");
  
  // tree -> Branch("F11IC2NumHit", &F11IC2NumHit, "F11IC2NumHit/I");
  tree -> Branch("F11IC2EnergySqSum",  &F11IC2EnergySqSum,  "F11IC2EnergySqSum/D");
  tree -> Branch("F11IC2EnergyAvSum",  &F11IC2EnergyAvSum,  "F11IC2EnergyAvSum/D");
  tree -> Branch("F11IC2ADCraw",        F11IC2ADCraw,       "F11IC2ADCraw[8]/D");
  tree -> Branch("F11IC2TDCraw",        F11IC2TDCraw,       "F11IC2TDCraw[8]/D");
  tree -> Branch("F11IC2TDCraw_multi",  F11IC2TDCraw_multi, Form("F11IC2TDCraw_multi[8][%d]/D", max_multihit_f11tdc));
  tree -> Branch("F11IC2TDC_NumHit",    F11IC2TDC_NumHit,   "F11IC2TDC_NumHit[8]/I");
  
  // tree -> Branch("F11VMETDC_NumHit",   F11VMETDC_NumHit,   "F11VMETDC_NumHit[8]/I");
  // tree -> Branch("F11VMETDCraw_multi", F11VMETDCraw_multi, Form("F11VMETDCraw_multi[32][%d]/D", max_multihit_f11tdc));
  // tree -> Branch("F11VMETDCraw",       F11VMETDCraw,       "F11VMETDCraw[32]/D");
  
  tree -> Branch("F11TDC_F11PLA_TL_NumHit",    &F11TDC_F11PLA_TL_NumHit,   "F11TDC_F11PLA_TL_NumHit/I");
  tree -> Branch("F11TDC_F11PLA_TL_raw",       &F11TDC_F11PLA_TL_raw,      "F11TDC_F11PLA_TL_raw/D");
  tree -> Branch("F11TDC_F11PLA_TL_raw_multi", F11TDC_F11PLA_TL_raw_multi, Form("F11TDC_F11PLA_TL_raw_multi[%d]/D", max_multihit_f11tdc));

  tree -> Branch("F11TDC_F11PLA_TR_NumHit",    &F11TDC_F11PLA_TR_NumHit,   "F11TDC_F11PLA_TR_NumHit/I");
  tree -> Branch("F11TDC_F11PLA_TR_raw",       &F11TDC_F11PLA_TR_raw,      "F11TDC_F11PLA_TR_raw/D");
  tree -> Branch("F11TDC_F11PLA_TR_raw_multi", F11TDC_F11PLA_TR_raw_multi, Form("F11TDC_F11PLA_TR_raw_multi[%d]/D", max_multihit_f11tdc));

  tree -> Branch("F11TDC_F11LONG_TL_NumHit",    &F11TDC_F11LONG_TL_NumHit,   "F11TDC_F11LONG_TL_NumHit/I");
  tree -> Branch("F11TDC_F11LONG_TL_raw",       &F11TDC_F11LONG_TL_raw,      "F11TDC_F11LONG_TL_raw/D");
  tree -> Branch("F11TDC_F11LONG_TL_raw_multi", F11TDC_F11LONG_TL_raw_multi, Form("F11TDC_F11LONG_TL_raw_multi[%d]/D", max_multihit_f11tdc));
  
  tree -> Branch("F11TDC_F11LONG_TR_NumHit",    &F11TDC_F11LONG_TR_NumHit,   "F11TDC_F11LONG_TR_NumHit/I");
  tree -> Branch("F11TDC_F11LONG_TR_raw",       &F11TDC_F11LONG_TR_raw,      "F11TDC_F11LONG_TR_raw/D");
  tree -> Branch("F11TDC_F11LONG_TR_raw_multi", F11TDC_F11LONG_TR_raw_multi, Form("F11TDC_F11LONG_TR_raw_multi[%d]/D", max_multihit_f11tdc));

  tree -> Branch("F11TDC_F11VETO_TL_NumHit",    &F11TDC_F11VETO_TL_NumHit,   "F11TDC_F11VETO_TL_NumHit/I");
  tree -> Branch("F11TDC_F11VETO_TL_raw",       &F11TDC_F11VETO_TL_raw,      "F11TDC_F11VETO_TL_raw/D");
  tree -> Branch("F11TDC_F11VETO_TL_raw_multi", F11TDC_F11VETO_TL_raw_multi, Form("F11TDC_F11VETO_TL_raw_multi[%d]/D", max_multihit_f11tdc));
  
  tree -> Branch("F11TDC_F11VETO_TR_NumHit",    &F11TDC_F11VETO_TR_NumHit,   "F11TDC_F11VETO_TR_NumHit/I");
  tree -> Branch("F11TDC_F11VETO_TR_raw",       &F11TDC_F11VETO_TR_raw,      "F11TDC_F11VETO_TR_raw/D");
  tree -> Branch("F11TDC_F11VETO_TR_raw_multi", F11TDC_F11VETO_TR_raw_multi, Form("F11TDC_F11VETO_TR_raw_multi[%d]/D", max_multihit_f11tdc));

  tree -> Branch("F11TDC_TRIG_NumHit",    &F11TDC_TRIG_NumHit,   "F11TDC_TRIG_NumHit/I");
  tree -> Branch("F11TDC_TRIG_raw",       &F11TDC_TRIG_raw,      "F11TDC_TRIG_raw/D");
  tree -> Branch("F11TDC_TRIG_raw_multi", F11TDC_TRIG_raw_multi, Form("F11TDC_TRIG_raw_multi[%d]/D", max_multihit_f11tdc));


  //______________________________________________________________________________
	//
	// 5. PID
	//______________________________________________________________________________


  Double_t tof[3];
  Double_t beta[3];
  Double_t zet[6];
  Double_t aoq[6];
  Double_t zetc[6];
  Double_t aoqc[6];  //Corrected PID
  Double_t delta[4];
  
  tree -> Branch("tof",   tof,   "tof[3]/D");
  tree -> Branch("beta",  beta,  "beta[3]/D");
  tree -> Branch("zet",   zet,   "zet[6]/D");
  tree -> Branch("zetc",  zetc,  "zetc[6]/D");
  tree -> Branch("aoq",   aoq,   "aoq[6]/D");
  tree -> Branch("aoqc",  aoqc,  "aoqc[6]/D");
  tree -> Branch("delta", delta, "delta[4]/D");


  //______________________________________________________________________________
	//
	// 6. Dipole
	//______________________________________________________________________________

  
  Double_t dipolebrho[8];
  TString* namedipole[8];

  for(int idipole = 0; idipole < 8; idipole++){ namedipole[idipole] = new TString(Form("D%d", idipole+1)); }
  tree -> Branch("dipolebrho", dipolebrho, "dipolebrho[8]/D");
  

  //______________________________________________________________________________
	//
	// 7. PPAC raw
	//______________________________________________________________________________

  
  TString* nameppac[7][4];
  char nameppacfocalplane[7][64] = {"F3PPAC", "F5PPAC", "F7PPAC", "F8PPAC", "F9PPAC", "F10PPAC", "F11PPAC"};
  char nameppactype[4][64]       = {"1A", "1B", "2A", "2B"};

  for(int ii = 0; ii < 7; ii++)
  {
    for(int jj = 0; jj < 4; jj++)
    {
      nameppac[ii][jj] = new TString(Form("%s-%s", nameppacfocalplane[ii], nameppactype[jj]));
    }
  }
  Double_t PPACQX1[7][4];
  Double_t PPACQX2[7][4];
  Double_t PPACQY1[7][4];
  Double_t PPACQY2[7][4];
  Double_t PPACQA[7][4];
  Double_t PPACTX1[7][4];
  Double_t PPACTX2[7][4];
  Double_t PPACTY1[7][4];
  Double_t PPACTY2[7][4];
  Double_t PPACTA[7][4];
  Double_t PPACX[7][4];
  Double_t PPACY[7][4];
  Double_t PPACXZpos[7][4];
  Double_t PPACYZpos[7][4];

  tree -> Branch("PPACQX1",   PPACQX1,   "PPACQX1[7][4]/D");
  tree -> Branch("PPACQX2",   PPACQX2,   "PPACQX2[7][4]/D");
  tree -> Branch("PPACQY1",   PPACQY1,   "PPACQY1[7][4]/D");
  tree -> Branch("PPACQY2",   PPACQY2,   "PPACQY2[7][4]/D");
  tree -> Branch("PPACQA",    PPACQA,    "PPACQA[7][4]/D");
  tree -> Branch("PPACTX1",   PPACTX1,   "PPACTX1[7][4]/D");
  tree -> Branch("PPACTX2",   PPACTX2,   "PPACTX2[7][4]/D");
  tree -> Branch("PPACTY1",   PPACTY1,   "PPACTY1[7][4]/D");
  tree -> Branch("PPACTY2",   PPACTY2,   "PPACTY2[7][4]/D");
  tree -> Branch("PPACTA",    PPACTA,    "PPACTA[7][4]/D");
  tree -> Branch("PPACX",     PPACX,     "PPACX[7][4]/D");
  tree -> Branch("PPACY",     PPACY,     "PPACY[7][4]/D");
  tree -> Branch("PPACXZpos", PPACXZpos, "PPACXZpos[7][4]/D");
  tree -> Branch("PPACYZpos", PPACYZpos, "PPACYZpos[7][4]/D");
  
  
  //______________________________________________________________________________
	//
	// 8. PPAC multihit
	//______________________________________________________________________________

  
  const int max_multihit_ppac = 4;
  Double_t PPACTX1_multi[7][4][max_multihit_ppac];
  Double_t PPACTX2_multi[7][4][max_multihit_ppac];
  Double_t PPACTY1_multi[7][4][max_multihit_ppac];
  Double_t PPACTY2_multi[7][4][max_multihit_ppac];
  Double_t PPACTA_multi[7][4][max_multihit_ppac];
  
  Int_t PPACTX1_NumHit[7][4];
  Int_t PPACTX2_NumHit[7][4];
  Int_t PPACTY1_NumHit[7][4];
  Int_t PPACTY2_NumHit[7][4];
  Int_t PPACTA_NumHit[7][4];

  tree -> Branch("PPACTX1_multi", PPACTX1_multi, Form("PPACTX1_multi[7][4][%d]/D", max_multihit_ppac));
  tree -> Branch("PPACTX2_multi", PPACTX2_multi, Form("PPACTX2_multi[7][4][%d]/D", max_multihit_ppac));
  tree -> Branch("PPACTY1_multi", PPACTY1_multi, Form("PPACTY1_multi[7][4][%d]/D", max_multihit_ppac));
  tree -> Branch("PPACTY2_multi", PPACTY2_multi, Form("PPACTY2_multi[7][4][%d]/D", max_multihit_ppac));
  tree -> Branch("PPACTA_multi",  PPACTA_multi,  Form("PPACTA_multi[7][4][%d]/D",  max_multihit_ppac));
  
  tree -> Branch("PPACTX1_NumHit", PPACTX1_NumHit, "PPACTX1_NumHit[7][4]/I");
  tree -> Branch("PPACTX2_NumHit", PPACTX2_NumHit, "PPACTX2_NumHit[7][4]/I");
  tree -> Branch("PPACTY1_NumHit", PPACTY1_NumHit, "PPACTY1_NumHit[7][4]/I");
  tree -> Branch("PPACTY2_NumHit", PPACTY2_NumHit, "PPACTY2_NumHit[7][4]/I");
  tree -> Branch("PPACTA_NumHit" , PPACTA_NumHit,  "PPACTA_NumHit[7][4]/I");
  

  //______________________________________________________________________________
	//
	// 9. PPAC tdc raw
	//______________________________________________________________________________


  // tdc selected
  Double_t PPACTX1_s[7][4];
  Double_t PPACTX2_s[7][4];
  Double_t PPACTY1_s[7][4];
  Double_t PPACTY2_s[7][4];
  Double_t PPACTA_s[7][4];

  tree -> Branch("PPACTX1_s", PPACTX1_s, "PPACTX1_s[7][4]/D");
  tree -> Branch("PPACTX2_s", PPACTX2_s, "PPACTX2_s[7][4]/D");
  tree -> Branch("PPACTY1_s", PPACTY1_s, "PPACTY1_s[7][4]/D");
  tree -> Branch("PPACTY2_s", PPACTY2_s, "PPACTY2_s[7][4]/D");
  tree -> Branch("PPACTA_s",  PPACTA_s,  "PPACTA_s[7][4]/D");
  
  double ppactdc_cut_minx[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double ppactdc_cut_maxx[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double ppactdc_cut_miny[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double ppactdc_cut_maxy[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double ppactdc_cut_mina[7] = {-999., -999., -999., -999., -999., -999., -999.};
  double ppactdc_cut_maxa[7] = {-999., -999., -999., -999., -999., -999., -999.};
  
  // See RIBF-132_Overview.xlsx for the run information
	// Runnumber 1 to 20 are for calibration
  if(1 <= runnum && runnum <= 20)
  {
    ppactdc_cut_minx[0] = 31500. + 4500.;  ppactdc_cut_maxx[0] = 36000. + 4500.;     // F3
    ppactdc_cut_miny[0] = 31500. + 4500.;  ppactdc_cut_maxy[0] = 36000. + 4500.;     // F3
    ppactdc_cut_mina[0] = 31500. + 4500.;  ppactdc_cut_maxa[0] = 36000. + 4500.;     // F3
    
    ppactdc_cut_minx[1] = 31000. + 4500.;  ppactdc_cut_maxx[1] = 36000. + 4500.;     // F5
    ppactdc_cut_miny[1] = 31000. + 4500.;  ppactdc_cut_maxy[1] = 36000. + 4500.;     // F5
    ppactdc_cut_mina[1] = 31000. + 4500.;  ppactdc_cut_maxa[1] = 36000. + 4500.;     // F5
    
    ppactdc_cut_minx[2] = 31000. + 4500.;  ppactdc_cut_maxx[2] = 36000. + 4500.;     // F7
    ppactdc_cut_miny[2] = 31000. + 4500.;  ppactdc_cut_maxy[2] = 36000. + 4500.;     // F7
    ppactdc_cut_mina[2] = 31000. + 4500.;  ppactdc_cut_maxa[2] = 36000. + 4500.;     // F7
    
    ppactdc_cut_minx[3] = 31000. + 4500.;  ppactdc_cut_maxx[3] = 36000. + 4500.;     // F8
    ppactdc_cut_miny[3] = 31000. + 4500.;  ppactdc_cut_maxy[3] = 36000. + 4500.;     // F8
    ppactdc_cut_mina[3] = 31000. + 4500.;  ppactdc_cut_maxa[3] = 36000. + 4500.;     // F8
    
    ppactdc_cut_minx[4] = 33000. + 4500.;  ppactdc_cut_maxx[4] = 38000. + 4500.;     // F9
    ppactdc_cut_miny[4] = 33000. + 4500.;  ppactdc_cut_maxy[4] = 38000. + 4500.;     // F9
    ppactdc_cut_mina[4] = 33000. + 4500.;  ppactdc_cut_maxa[4] = 38000. + 4500.;     // F9
    
    ppactdc_cut_minx[5] = -999. + 4500.;   ppactdc_cut_maxx[5] = -999. + 4500.;      // F10
    ppactdc_cut_miny[5] = -999. + 4500.;   ppactdc_cut_maxy[5] = -999. + 4500.;      // F10
    ppactdc_cut_mina[5] = -999. + 4500.;   ppactdc_cut_maxa[5] = -999. + 4500.;      // F10
    
    ppactdc_cut_minx[6] = 34500. + 4500.;  ppactdc_cut_maxx[6] = 39500. + 4500.;     // F11
    ppactdc_cut_miny[6] = 34500. + 4500.;  ppactdc_cut_maxy[6] = 39500. + 4500.;     // F11
    ppactdc_cut_mina[6] = 34500. + 4500.;  ppactdc_cut_maxa[6] = 39500. + 4500.;     // F11
  }
  else if(21 <= runnum && runnum <= 147)          // Runnumber 21 to 147 are the actual experiment
  {
    ppactdc_cut_minx[0] = 31500.;  ppactdc_cut_maxx[0] = 36000.;    // F3
    ppactdc_cut_miny[0] = 31500.;  ppactdc_cut_maxy[0] = 36000.;    // F3
    ppactdc_cut_mina[0] = 31500.;  ppactdc_cut_maxa[0] = 36000.;    // F3
    
    ppactdc_cut_minx[1] = 31000.;  ppactdc_cut_maxx[1] = 36000.;    // F5
    ppactdc_cut_miny[1] = 31000.;  ppactdc_cut_maxy[1] = 36000.;    // F5
    ppactdc_cut_mina[1] = 31000.;  ppactdc_cut_maxa[1] = 36000.;    // F5
    
    ppactdc_cut_minx[2] = 31000.;  ppactdc_cut_maxx[2] = 36000.;    // F7
    ppactdc_cut_miny[2] = 31000.;  ppactdc_cut_maxy[2] = 36000.;    // F7
    ppactdc_cut_mina[2] = 31000.;  ppactdc_cut_maxa[2] = 36000.;    // F7
    
    ppactdc_cut_minx[3] = 31000.;  ppactdc_cut_maxx[3] = 36000.;    // F8
    ppactdc_cut_miny[3] = 31000.;  ppactdc_cut_maxy[3] = 36000.;    // F8
    ppactdc_cut_mina[3] = 31000.;  ppactdc_cut_maxa[3] = 36000.;    // F8
    
    ppactdc_cut_minx[4] = 33000.;  ppactdc_cut_maxx[4] = 38000.;    // F9
    ppactdc_cut_miny[4] = 33000.;  ppactdc_cut_maxy[4] = 38000.;    // F9
    ppactdc_cut_mina[4] = 33000.;  ppactdc_cut_maxa[4] = 38000.;    // F9
    
    ppactdc_cut_minx[5] = -999.;   ppactdc_cut_maxx[5] = -999.;     // F10
    ppactdc_cut_miny[5] = -999.;   ppactdc_cut_maxy[5] = -999.;     // F10
    ppactdc_cut_mina[5] = -999.;   ppactdc_cut_maxa[5] = -999.;     // F10
    
    ppactdc_cut_minx[6] = 34500.;  ppactdc_cut_maxx[6] = 39500.;    // F11
    ppactdc_cut_miny[6] = 34500.;  ppactdc_cut_maxy[6] = 39500.;    // F11
    ppactdc_cut_mina[6] = 34500.;  ppactdc_cut_maxa[6] = 39500.;    // F11
  }
  

  //______________________________________________________________________________
	//
	// 10. DALI
	//______________________________________________________________________________

 
  Int_t dalimultwotime        = 0;
  Int_t dalimult              = 0;
  Int_t dalitimetruemult      = 0;
  Int_t dalimultthres         = 0;
  Int_t dalitimetruemultthres = 0;

  /*
  tree->Branch("dalimultwotime",&dalimultwotime,"dalimultwotime/I");
  tree->Branch("dalimult",&dalimult,"dalimult/I");
  tree->Branch("dalitimetruemult",&dalitimetruemult,"dalitimetruemult/I");
  tree->Branch("dalimultthres",&dalimultthres,"dalimultthres/I");
  tree->Branch("dalitimetruemultthres",&dalitimetruemultthres,"dalitimetruemultthres/I");
  */


  //______________________________________________________________________________
	//
	// 11. MINOS
	//______________________________________________________________________________


  // Double_t z_vertex=0.;
  // tree -> Branch("z_vertex", &z_vertex, "z_vertex/D");

  int neve = 0;
  while(estore -> GetNextEvent())
  {
    if(neve%1000 == 0){cout << "Event: " << neve << " done\r" << flush;}

    // Making the BigRIPS tree calibration
    brcalib -> ClearData();
    brcalib -> ReconstructData();
    
    // Reconstructiong the PID
    recopid -> ClearData();
    recopid -> ReconstructData();
  
    
    //--------multihit for pla time ---------
    for(int ii = 0; ii < max_multihit_pla; ii++) { F3PLA_TL_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F5PLA_TL_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F7PLA_TL_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F8PLA_TL_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11PLA_TL_raw_multi[ii]  = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11PLA2_TL_raw_multi[ii] = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11LONG_TL_raw_multi[ii] = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11VETO_TL_raw_multi[ii] = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F3PLA_TR_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F5PLA_TR_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F7PLA_TR_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F8PLA_TR_raw_multi[ii]   = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11PLA_TR_raw_multi[ii]  = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11PLA2_TR_raw_multi[ii] = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11LONG_TR_raw_multi[ii] = -9999.; }
    for(int ii = 0; ii < max_multihit_pla; ii++) { F11VETO_TR_raw_multi[ii] = -9999.; }
    
    F3PLA_TL_NumHit   = 0;
    F5PLA_TL_NumHit   = 0;
    F7PLA_TL_NumHit   = 0;
    F8PLA_TL_NumHit   = 0;
    F11PLA_TL_NumHit  = 0;
    F11PLA2_TL_NumHit = 0;
    F11LONG_TL_NumHit = 0;
    F11VETO_TL_NumHit = 0;
    F3PLA_TR_NumHit   = 0;
    F5PLA_TR_NumHit   = 0;
    F7PLA_TR_NumHit   = 0;
    F8PLA_TR_NumHit   = 0;
    F11PLA_TR_NumHit  = 0;
    F11PLA2_TR_NumHit = 0;
    F11LONG_TR_NumHit = 0;
    F11VETO_TR_NumHit = 0;
    
    
    //--------multihit for ppac time ---------
    for(int ii = 0; ii < 7; ii++)
    {
      for(int jj = 0; jj < 4; jj++)
      {
        for(int kk = 0; kk < max_multihit_ppac; kk++)
        {
          PPACTX1_multi[ii][jj][kk] = -9999.;
          PPACTX2_multi[ii][jj][kk] = -9999.;
          PPACTY1_multi[ii][jj][kk] = -9999.;
          PPACTY2_multi[ii][jj][kk] = -9999.;
          PPACTA_multi[ii][jj][kk]  = -9999.;
        }
        PPACTX1_NumHit[ii][jj] = 0;
        PPACTX2_NumHit[ii][jj] = 0;
        PPACTY1_NumHit[ii][jj] = 0;
        PPACTY2_NumHit[ii][jj] = 0;
        PPACTA_NumHit[ii][jj]  = 0;
      }
    }

    //--------multihit for F11 TDC---------
    F7ICEnergySqSum = -9999.;
    F7ICEnergyAvSum = -9999.;

    for(int ii = 0; ii < 6; ii++) { F7ICADCraw[ii] = -9999.; }

    F11IC1EnergySqSum = -9999.;
    F11IC1EnergyAvSum = -9999.;
    F11IC2EnergySqSum = -9999.;
    F11IC2EnergyAvSum = -9999.;

    for(int ii = 0; ii < 8; ii++)
    {
      F11IC1ADCraw[ii]     = -9999.;
      F11IC1TDCraw[ii]     = -9999.;
      F11IC2ADCraw[ii]     = -9999.;
      F11IC2TDCraw[ii]     = -9999.;
      F11IC1TDC_NumHit[ii] = 0;
      F11IC2TDC_NumHit[ii] = 0;
      
      for(int jj = 0; jj < max_multihit_f11tdc; jj++)
      {
        F11IC1TDCraw_multi[ii][jj] = -9999.;
        F11IC2TDCraw_multi[ii][jj] = -9999.;
      }
    }

    for(int ii = 0; ii < 32; ii++)
    {
      F11VMETDCraw[ii]     = -9999.;
      F11VMETDC_NumHit[ii] = 0;

      for(int jj = 0; jj < max_multihit_f11tdc; jj++)
      {
        F11VMETDCraw_multi[ii][jj] = -9999.;
      }
    }
    
  
    fbit = 0;
    TArtRawEventObject *rawevent = (TArtRawEventObject *)sman -> FindDataContainer("RawEvent");

    for(int i = 0; i < rawevent -> GetNumSeg(); i++)
    {

      // The segment block in the .ridf file contains the raw data.
			// see full description here: https://ribf.riken.jp/RIBFDAQ/index.php?plugin=attach&refer=DAQ%2FManual%2FDataformat&openfile=dataformat_101112e.pdf
      TArtRawSegmentObject *seg = rawevent -> GetSegment(i);

      // each focal plane, detector, etc. has a unique id.
			// all defined on this webpage: https://ribf.riken.jp/RIBFDAQ/index.php?DAQ%2FManual%2FDataformat
			// or go to macros/segidlist.h
      Int_t fpl      = seg -> GetFP();
      Int_t detector = seg -> GetDetector();
      Int_t device   = seg -> GetDevice();

      if(fpl == 63 && detector == 10)
      {
        for(int j = 0; j < seg -> GetNumData(); j++)
        {
          TArtRawDataObject *d = seg -> GetData(j);
          triggerbit           = d -> GetVal();
          //cout<<"triggerbit: "<<triggerbit<<endl;
        }
      }
      else if(PLAT  == detector)
      {
        for(int j = 0; j < seg -> GetNumData(); j++)
        {
          TArtRawDataObject *d =      seg -> GetData(j);
          Int_t geo            =        d -> GetGeo();
          Int_t ch             =        d -> GetCh();
          Int_t val            = (Int_t)d -> GetVal();
          Int_t edge           = (Int_t)d -> GetEdge();
          
          if(edge == 1) continue;
          
          TArtRIDFMap mm(fpl, detector, geo, ch);
          TArtPlasticPara *plapara = (TArtPlasticPara*)para -> FindPlasticPara(&mm);

          if(NULL == plapara)
          {
            TArtCore::Warning(__FILE__,"Could not find TArtPlasticPara...: Dev:%d, %s", device, mm.GetMapInfo());
            continue;
          }
          else
          {
            TArtCore::Debug(__FILE__,"Find TArtPlasticPara...: Dev:%d, %s, : %s", device, mm.GetMapInfo(), plapara->GetDetectorName()->Data());
          }
          
          // F3pla
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F3pl") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F3PLA_TL_NumHit < max_multihit_pla) { F3PLA_TL_raw_multi[F3PLA_TL_NumHit] = val ; }
              F3PLA_TL_NumHit ++;
              // cout << "F3TL numhit=" << F3PLA_TL_NumHit << endl;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F3PLA_TR_NumHit < max_multihit_pla) { F3PLA_TR_raw_multi[F3PLA_TR_NumHit] = val ; }
              F3PLA_TR_NumHit ++;
            }
          }
          
          // F5pla
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F5pl") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F5PLA_TL_NumHit < max_multihit_pla) { F5PLA_TL_raw_multi[F5PLA_TL_NumHit] = val ; }
              F5PLA_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F5PLA_TR_NumHit < max_multihit_pla){ F5PLA_TR_raw_multi[F5PLA_TR_NumHit] = val ; }
              F5PLA_TR_NumHit ++;
            }
          }
          
          // F7pla
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F7pl") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F7PLA_TL_NumHit < max_multihit_pla) { F7PLA_TL_raw_multi[F7PLA_TL_NumHit] = val ; }
              F7PLA_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F7PLA_TR_NumHit < max_multihit_pla) { F7PLA_TR_raw_multi[F7PLA_TR_NumHit] = val ; }
              F7PLA_TR_NumHit ++;
            }
          }
          
          // F8pla
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F8pl") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F8PLA_TL_NumHit < max_multihit_pla) { F8PLA_TL_raw_multi[F8PLA_TL_NumHit] = val ; }
              F8PLA_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F8PLA_TR_NumHit < max_multihit_pla) { F8PLA_TR_raw_multi[F8PLA_TR_NumHit] = val ; }
              F8PLA_TR_NumHit ++;
            }
          }
          
          // F11pla
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F11pl") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F11PLA_TL_NumHit < max_multihit_pla) { F11PLA_TL_raw_multi[F11PLA_TL_NumHit] = val ; }
              F11PLA_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F11PLA_TR_NumHit < max_multihit_pla) { F11PLA_TR_raw_multi[F11PLA_TR_NumHit] = val ; }
              F11PLA_TR_NumHit ++;
            }
          }
        
          // F11PLA2
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F11pl-dummy") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F11PLA2_TL_NumHit < max_multihit_pla) { F11PLA2_TL_raw_multi[F11PLA2_TL_NumHit] = val ; }
              F11PLA2_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F11PLA2_TR_NumHit < max_multihit_pla) { F11PLA2_TR_raw_multi[F11PLA2_TR_NumHit] = val ; }
              F11PLA2_TR_NumHit ++;
            }
          }

          // F11LONG
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F11long") )
          {
            if( mm == *((TArtRIDFMap *)plapara -> GetTLMap()) )
            {
              if(F11LONG_TL_NumHit < max_multihit_pla) { F11LONG_TL_raw_multi[F11LONG_TL_NumHit] = val ; }
              F11LONG_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F11LONG_TR_NumHit < max_multihit_pla) { F11LONG_TR_raw_multi[F11LONG_TR_NumHit] = val ; }
              F11LONG_TR_NumHit ++;
            }
          }
          
          // F11VETO
          if( 0 == strcmp(plapara -> GetDetectorName() -> Data(), "F11veto") )
          {
            if( mm == *((TArtRIDFMap *) plapara -> GetTLMap()) )
            {
              if(F11VETO_TL_NumHit < max_multihit_pla){ F11VETO_TL_raw_multi[F11VETO_TL_NumHit] = val ; }
              F11VETO_TL_NumHit ++;
            }
            else if( mm == *((TArtRIDFMap *)plapara -> GetTRMap()) )
            {
              if(F11VETO_TR_NumHit < max_multihit_pla) { F11VETO_TR_raw_multi[F11VETO_TR_NumHit] = val ; }
              F11VETO_TR_NumHit ++;
            }
          }
        }
      
      }
      else if(PPACT == detector)
      {
        for(Int_t j = 0; j < seg -> GetNumData(); j++)
        {
          TArtRawDataObject *d =      seg -> GetData(j);
          Int_t geo            =        d -> GetGeo();
          Int_t ch             =        d -> GetCh();
          Int_t val            = (Int_t)d -> GetVal();
          
          TArtRIDFMap mm(fpl, detector, geo, ch);
          TArtPPACPara *ppacpara = (TArtPPACPara*)para -> FindPPACPara(&mm);

          if(NULL == ppacpara){
            TArtCore::Warning(__FILE__, "Could not find TArtPPACPara...: Dev:%d, %s", device, mm.GetMapInfo());
            continue;
          }
          else
          {
            TArtCore::Debug(__FILE__, "Find TArtPPACPara...: Dev:%d, %s, : %s", device, mm.GetMapInfo(), ppacpara->GetDetectorName()->Data());
          }
          
          // search (i,j)
          // cout << ppacpara -> GetDetectorName() -> Data() << endl;
          
          int i_ppac_focalplane, j_ppac;
          for(int ii = 0; ii < 7; ii++)
          {
            for(int jj = 0; jj < 4; jj++)
            {
              if( 0 == strcmp(nameppac[ii][jj] -> Data(), ppacpara -> GetDetectorName() -> Data()) )
              {
                i_ppac_focalplane = ii;
                j_ppac            = jj;
              }
            }
          }
          // cout << "i, j= " << i_ppac_focalplane << " ,  " << j_ppac << endl;

          if( mm == *((TArtRIDFMap *)ppacpara -> GetTX1Map()) )
          {
            int numhit_before = PPACTX1_NumHit[i_ppac_focalplane][j_ppac];
            if(numhit_before < max_multihit_ppac ) {PPACTX1_multi[i_ppac_focalplane][j_ppac][numhit_before] = val; }
            PPACTX1_NumHit[i_ppac_focalplane][j_ppac] ++;
          }
          if( mm == *((TArtRIDFMap *)ppacpara -> GetTX2Map()) )
          {
            int numhit_before = PPACTX2_NumHit[i_ppac_focalplane][j_ppac];
            if(numhit_before < max_multihit_ppac ) {PPACTX2_multi[i_ppac_focalplane][j_ppac][numhit_before] = val; }
            PPACTX2_NumHit[i_ppac_focalplane][j_ppac] ++;
          }
          if( mm == *((TArtRIDFMap *)ppacpara -> GetTY1Map()) )
          {
            int numhit_before = PPACTY1_NumHit[i_ppac_focalplane][j_ppac];
            if(numhit_before < max_multihit_ppac ) {PPACTY1_multi[i_ppac_focalplane][j_ppac][numhit_before] = val; }
            PPACTY1_NumHit[i_ppac_focalplane][j_ppac] ++;
          }
          if( mm == *((TArtRIDFMap *)ppacpara -> GetTY2Map()) )
          {
            int numhit_before = PPACTY2_NumHit[i_ppac_focalplane][j_ppac];
            if(numhit_before < max_multihit_ppac ) {PPACTY2_multi[i_ppac_focalplane][j_ppac][numhit_before] = val; }
            PPACTY2_NumHit[i_ppac_focalplane][j_ppac] ++;
          }
          if( mm == *((TArtRIDFMap *)ppacpara -> GetTAMap()) )
          {
            int numhit_before = PPACTA_NumHit[i_ppac_focalplane][j_ppac];
            if(numhit_before < max_multihit_ppac ) {PPACTA_multi[i_ppac_focalplane][j_ppac][numhit_before] = val; }
            PPACTA_NumHit[i_ppac_focalplane][j_ppac] ++;
          }
        }
      }
      else if(fpl == 41 && detector == 5)    // F11VME TDC
      { 
        for(Int_t j = 0; j < seg -> GetNumData(); j++)
        {
          TArtRawDataObject *d =      seg -> GetData(j);
          Int_t geo            =        d -> GetGeo();
          Int_t ch             =        d -> GetCh();
          Int_t val            = (Int_t)d -> GetVal();
          
          if(0 <= ch && ch <= 31)
          {
            F11VMETDCraw[ch] = val; // naiively fill to this channel
            if(0 <= F11VMETDC_NumHit[ch] && F11VMETDC_NumHit[ch] < max_multihit_f11tdc)
            {
              F11VMETDCraw_multi[ch][(F11VMETDC_NumHit[ch])] = val;
            }
            F11VMETDC_NumHit[ch]++;
          }
        }
      }
    
    }
    
    
    fbit = triggerbit;
    /*
    for(Int_t i = 0; i < 7; i++)
    {
      if ((triggerbit >> i) & 0x1)
        fbit = i+1;
    } 
    */
    
    //______________________________________________________________________________
	  //
	  // Focalplane
	  //______________________________________________________________________________

    
    F3X  = -9999;  F3A  = -9999; F3Y  = -9999; F3B  = -9999;
    F5X  = -9999;  F5A  = -9999; F5Y  = -9999; F5B  = -9999;
    F7X  = -9999;  F7A  = -9999; F7Y  = -9999; F7B  = -9999;
    F8X  = -9999;  F8A  = -9999; F8Y  = -9999; F8B  = -9999;
    F9X  = -9999;  F9A  = -9999; F9Y  = -9999; F9B  = -9999;
    F11X = -9999;  F11A = -9999; F11Y = -9999; F11B = -9999;
      
    TArtFocalPlane *tfpl;
    TVectorD *vec;

    tfpl = cfpl -> FindFocalPlane(3); 
    if(tfpl){vec = tfpl -> GetOptVector(); F3X  = (*vec)(0); F3A  = (*vec)(1); F3Y  = (*vec)(2); F3B  = (*vec)(3);}

    tfpl = cfpl -> FindFocalPlane(5); 
    if(tfpl){vec = tfpl -> GetOptVector(); F5X  = (*vec)(0); F5A  = (*vec)(1); F5Y  = (*vec)(2); F5B  = (*vec)(3);}

    tfpl = cfpl -> FindFocalPlane(7); 
    if(tfpl){vec = tfpl -> GetOptVector(); F7X  = (*vec)(0); F7A  = (*vec)(1); F7Y  = (*vec)(2); F7B  = (*vec)(3);}

    tfpl = cfpl -> FindFocalPlane(8); 
    if(tfpl){vec = tfpl -> GetOptVector(); F8X  = (*vec)(0); F8A  = (*vec)(1); F8Y  = (*vec)(2); F8B  = (*vec)(3);}

    tfpl = cfpl -> FindFocalPlane(9); 
    if(tfpl){vec = tfpl -> GetOptVector(); F9X  = (*vec)(0); F9A  = (*vec)(1); F9Y  = (*vec)(2); F9B  = (*vec)(3);}

    tfpl = cfpl -> FindFocalPlane(11); 
    if(tfpl){vec = tfpl -> GetOptVector(); F11X = (*vec)(0); F11A = (*vec)(1); F11Y = (*vec)(2); F11B = (*vec)(3);}


    //______________________________________________________________________________
	  //
	  // Plastics
	  //______________________________________________________________________________


    F3PLA_TL_raw    = -9999;   F3PLA_TR_raw   = -9999;       // F3PLA_TL      = -9999; F3PLA_TR = -9999; F3PLA_T = -9999;
    F3PLA_QL_raw    = -9999;   F3PLA_QR_raw   = -9999;       // F3PLA_Q_ave   = -9999;
 
    F5PLA_TL_raw    = -9999;   F5PLA_TR_raw   = -9999;       // F5PLA_TL      = -9999; F5PLA_TR = -9999; F5PLA_T = -9999;
    F5PLA_QL_raw    = -9999;   F5PLA_QR_raw   = -9999;       // F5PLA_Q_ave   = -9999;
 
    F7PLA_TL_raw    = -9999;   F7PLA_TR_raw   = -9999;       // F7PLA_TL      = -9999; F7PLA_TR = -9999; F7PLA_T = -9999;
    F7PLA_QL_raw    = -9999;   F7PLA_QR_raw   = -9999;       // F7PLA_Q_ave   = -9999;
  
    F8PLA_TL_raw    = -9999;   F8PLA_TR_raw   = -9999;       // F8PLA_TL      = -9999; F8PLA_TR = -9999; F8PLA_T = -9999;
    F8PLA_QL_raw    = -9999;   F8PLA_QR_raw   = -9999;       // F8PLA_Q_ave   = -9999;
 
    F11PLA_QL_raw   = -9999;   F11PLA_QR_raw  = -9999;       // F11PLA_TL     = -9999; F11PLA_TR = -9999; F11PLA_T = -9999;
    F11PLA_QL_raw   = -9999;   F11PLA_QR_raw  = -9999;       // F11PLA_Q_ave  = -9999;

    F11PLA2_QL_raw  = -9999;   F11PLA2_QR_raw = -9999;       // F11PLA2_TL    = -9999; F11PLA2_TR = -9999; F11PLA2_T = -9999;
    F11PLA2_QL_raw  = -9999;   F11PLA2_QR_raw = -9999;       // F11PLA2_Q_ave = -9999;

    F11LONG_QL_raw  = -9999;   F11LONG_QR_raw = -9999;       // F11LONG_TL    = -9999; F11LONG_TR = -9999; F11LONG_T = -9999;
    F11LONG_QL_raw  = -9999;   F11LONG_QR_raw = -9999;       // F11LONG_Q_ave = -9999;

    F11VETO_QL_raw  = -9999;   F11VETO_QR_raw = -9999;       // F11VETO_TL    = -9999; F11VETO_TR = -9999; F11VETO_T = -9999;
    F11VETO_QL_raw  = -9999;   F11VETO_QR_raw = -9999;       // F11VETO_Q_ave = -9999;

    PLATDC_B3F_Trig = -9999.;
    

    TArtPlastic *tpla;
    tpla = plasticcalib -> FindPlastic("F3pl");
    if(tpla)
    {
      F3PLA_TL_raw = tpla -> GetTLRaw();
      F3PLA_TR_raw = tpla -> GetTRRaw(); 
      // F3PLA_TL = tpla -> GetTimeL(); 
      // F3PLA_TR = tpla -> GetTimeR();
      // F3PLA_T  = tpla -> GetTime();

      F3PLA_QL_raw = tpla -> GetQLRaw();
      F3PLA_QR_raw = tpla -> GetQRRaw();
      // F3PLA_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F5pl");
    if(tpla)
    {
      F5PLA_TL_raw = tpla -> GetTLRaw();
      F5PLA_TR_raw = tpla -> GetTRRaw(); 
      // F5PLA_TL  = tpla -> GetTimeL();
      // F5PLA_TR  = tpla -> GetTimeR();
      // F5PLA_T   = tpla -> GetTime();

      F5PLA_QL_raw = tpla -> GetQLRaw();
      F5PLA_QR_raw = tpla -> GetQRRaw();
      // F5PLA_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F7pl");
    if(tpla)
    {
      F7PLA_TL_raw = tpla -> GetTLRaw();
      F7PLA_TR_raw = tpla -> GetTRRaw(); 
      // F7PLA_TL = tpla -> GetTimeL(); 
      // F7PLA_TR = tpla -> GetTimeR();
      // F7PLA_T  = tpla -> GetTime();
      
      F7PLA_QL_raw = tpla -> GetQLRaw();
      F7PLA_QR_raw = tpla -> GetQRRaw();
      // F7PLA_Q_ave = tpla -> GetQAveRaw();
    }
 
    tpla = plasticcalib -> FindPlastic("F8pl");
    if(tpla)
    {
      F8PLA_TL_raw = tpla -> GetTLRaw();
      F8PLA_TR_raw = tpla -> GetTRRaw();
      // F8PLA_TL = tpla -> GetTimeL(); 
      // F8PLA_TR = tpla -> GetTimeR();
      // F8PLA_T  = tpla -> GetTime();

      F8PLA_QL_raw = tpla -> GetQLRaw();
      F8PLA_QR_raw = tpla -> GetQRRaw();
      // F8PLA_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F11pl");
    if(tpla)
    {
      F11PLA_TL_raw = tpla -> GetTLRaw(); 
      F11PLA_TR_raw = tpla -> GetTRRaw(); 
      // F11PLA_TL = tpla -> GetTimeL(); 
      // F11PLA_TR = tpla -> GetTimeR();
      // F11PLA_T  = tpla -> GetTime();

      F11PLA_QL_raw = tpla -> GetQLRaw();
      F11PLA_QR_raw = tpla -> GetQRRaw();
      // F11PLA_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F11pl-dummy");
    if(tpla)
    {
      F11PLA2_TL_raw = tpla -> GetTLRaw();
      F11PLA2_TR_raw = tpla -> GetTRRaw(); 
      // F11PLA2_TL = tpla -> GetTimeL();
      // F11PLA2_TR = tpla -> GetTimeR();
      // F11PLA2_T  = tpla -> GetTime();

      F11PLA2_QL_raw = tpla -> GetQLRaw();
      F11PLA2_QR_raw = tpla -> GetQRRaw(); 
      // F11PLA2_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F11long");
    if(tpla)
    {
      F11LONG_TL_raw = tpla -> GetTLRaw();
      F11LONG_TR_raw = tpla -> GetTRRaw(); 
      // F11LONG_TL = tpla -> GetTimeL(); 
      // F11LONG_TR = tpla -> GetTimeR();
      // F11LONG_T  = tpla -> GetTime();

      F11LONG_QL_raw = tpla -> GetQLRaw();
      F11LONG_QR_raw = tpla -> GetQRRaw(); 
      // F11LONG_Q_ave = tpla -> GetQAveRaw();
    }

    tpla = plasticcalib -> FindPlastic("F11veto");
    if(tpla)
    {
      F11VETO_TL_raw = tpla -> GetTLRaw();
      F11VETO_TR_raw = tpla -> GetTRRaw(); 
      // F11VETO_TL = tpla -> GetTimeL();
      // F11VETO_TR = tpla -> GetTimeR();
      // F11VETO_T  = tpla -> GetTime();

      F11VETO_QL_raw = tpla -> GetQLRaw(); 
      F11VETO_QR_raw = tpla -> GetQRRaw(); 
      // F11VETO_Q_ave = tpla -> GetQAveRaw();
    }
    
    tpla = plasticcalib -> FindPlastic("Dummy");
    if(tpla)
    {
      PLATDC_B3F_Trig = tpla -> GetTRRaw();
    }

    
    //______________________________________________________________________________
	  //
	  // PPACs
	  //______________________________________________________________________________

    
    TArtPPAC *tppac;
    for(int ii = 0; ii < 7; ii++)
    {
      for(int jj = 0; jj < 4; jj++)
      {
        tppac = ppaccalib -> FindPPAC(nameppac[ii][jj]);

        PPACQX1[ii][jj] = tppac -> GetQX1Raw();
        PPACQX2[ii][jj] = tppac -> GetQX2Raw();
        PPACQY1[ii][jj] = tppac -> GetQY1Raw();
        PPACQY2[ii][jj] = tppac -> GetQY2Raw();
        PPACQA[ii][jj]  = tppac -> GetQARaw();
        PPACTX1[ii][jj] = tppac -> GetTX1Raw();
        PPACTX2[ii][jj] = tppac -> GetTX2Raw();
        PPACTY1[ii][jj] = tppac -> GetTY1Raw();
        PPACTY2[ii][jj] = tppac -> GetTY2Raw();
        PPACTA[ii][jj]  = tppac -> GetTARaw();

        PPACX[ii][jj]   = -9999.;
        PPACY[ii][jj]   = -9999.;

        if(tppac -> IsFiredX()) { PPACX[ii][jj] = tppac -> GetX(); }
        if(tppac -> IsFiredY()) { PPACY[ii][jj] = tppac -> GetY(); }

        PPACXZpos[ii][jj] = tppac -> GetXZPos();
        PPACYZpos[ii][jj] = tppac -> GetYZPos();
      }
    }
    

    //______________________________________________________________________________
	  //
	  // MUSICs
	  //______________________________________________________________________________


    // event-by-event init
    // done before readning rawdata
    
    TArtIC *tic;

    tic = iccalib -> FindIC("F7IC");
    if(tic)
    {
      F7ICNumHit      = tic -> GetNumHit();
      F7ICEnergySqSum = tic -> GetEnergySqSum();
      F7ICEnergyAvSum = tic -> GetEnergyAvSum();

      for(int ich = 0; ich < 6; ich++) { F7ICADCraw[ich] = tic -> GetRawADC(ich); }
    }

    tic = iccalib -> FindIC("F11IC");
    if(tic)
    {
      F11IC1NumHit      = tic -> GetNumHit();
      F11IC1EnergySqSum = tic -> GetEnergySqSum();
      F11IC1EnergyAvSum = tic -> GetEnergyAvSum();
      
      for(int ich = 0; ich < 8; ich++) { F11IC1ADCraw[ich] = tic -> GetRawADC(ich); }
    }

    tic = iccalib -> FindIC("F11IC_2");
    if(tic)
    {
      F11IC2NumHit      = tic -> GetNumHit();
      F11IC2EnergySqSum = tic -> GetEnergySqSum();
      F11IC2EnergyAvSum = tic -> GetEnergyAvSum();
      
      for(int ich=0; ich<8; ich++) { F11IC2ADCraw[ich] = tic -> GetRawADC(ich); }
    }
    
    
    for(int ii = 0; ii < 8; ii++)
    {
      F11IC1TDC_NumHit[ii] = F11VMETDC_NumHit[ii];
      F11IC2TDC_NumHit[ii] = F11VMETDC_NumHit[ii+8];
      F11IC1TDCraw[ii]     = F11VMETDCraw[ii];
      F11IC2TDCraw[ii]     = F11VMETDCraw[ii+8];

      for(int jj = 0; jj < max_multihit_f11tdc; jj++)
      {
        F11IC1TDCraw_multi[ii][jj] = F11VMETDCraw_multi[ii][jj];
        F11IC2TDCraw_multi[ii][jj] = F11VMETDCraw_multi[ii+8][jj];
      }
    }
    
    
    // F11TDC other channel, no need to init. all are copied from F11VMETDCraw, which were initialized.
    {
      // TDC channel
      int ii;
      
      // F11plaL
      ii = 17;
      F11TDC_F11PLA_TL_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11PLA_TL_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11PLA_TL_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }

      // F11plaR
      ii = 16;
      F11TDC_F11PLA_TR_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11PLA_TR_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11PLA_TR_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }

      // F11pla-long-L
      ii = 21;
      F11TDC_F11LONG_TL_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11LONG_TL_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11LONG_TL_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }

      // F11pla-long-R
      ii = 20;
      F11TDC_F11LONG_TR_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11LONG_TR_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11LONG_TR_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }
    
      // F11pla-veto-L
      ii = 23;
      F11TDC_F11VETO_TL_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11VETO_TL_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11VETO_TL_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }

      // F11pla-veto-R
      ii = 22;
      F11TDC_F11VETO_TR_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_F11VETO_TR_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_F11VETO_TR_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }

      // F11TDC-DAQtrigger reference
      ii = 31;
      F11TDC_TRIG_NumHit = F11VMETDC_NumHit[ii];
      F11TDC_TRIG_raw    = F11VMETDCraw[ii];
      for(int jj = 0; jj < max_multihit_f11tdc; jj++) { F11TDC_TRIG_raw_multi[jj] = F11VMETDCraw_multi[ii][jj]; }
    }
    

    //______________________________________________________________________________
	  //
	  // PID
	  //______________________________________________________________________________


    // The TOF
    tof[0]   = tof3to7 -> GetTOF();
    beta[0]  = tof3to7 -> GetBeta();
    
    tof[1]   = tof8to11 -> GetTOF();
    beta[1]  = tof8to11 -> GetBeta();
          
    tof[2]   = tof7to8 -> GetTOF();
    beta[2]  = tof7to8 -> GetBeta();

    // The PID
    zet[0]   = beam_br_35 -> GetZet();
    aoq[0]   = beam_br_35 -> GetAoQ();
    
    zet[1]   = beam_br_57 -> GetZet();
    aoq[1]   = beam_br_57 -> GetAoQ();

    zet[2]   = beam_br_37 -> GetZet();
    aoq[2]   = beam_br_37 -> GetAoQ();
    
    zet[3]   = beam_zd_89 -> GetZet();
    aoq[3]   = beam_zd_89 -> GetAoQ();
    
    zet[4]   = beam_zd_911 -> GetZet();
    aoq[4]   = beam_zd_911 -> GetAoQ();

    zet[5]   = beam_zd_811 -> GetZet();
    aoq[5]   = beam_zd_811 -> GetAoQ();

    // Delta
    delta[0] = rips3to5  -> GetDelta();
    delta[1] = rips5to7  -> GetDelta();
    delta[2] = rips8to9  -> GetDelta();
    delta[3] = rips9to11 -> GetDelta();
    
    
    for(int ii = 0; ii < 6; ii++)
    {
      zetc[ii] = -999.;
      aoqc[ii] = -999.;
    }
    
    bool isTOF37,   isTOF78,   isTOF811;
    bool isDelta35, isDelta57, isDelta89, isDelta911;
    bool isDE7,     isDE11;
    
    if( abs(delta[0]) < 10.0 ) { isDelta35  = true; } else { isDelta35  = false; }
    if( abs(delta[1]) < 10.0 ) { isDelta57  = true; } else { isDelta57  = false; }
    if( abs(delta[2]) < 10.0 ) { isDelta89  = true; } else { isDelta89  = false; }
    if( abs(delta[3]) < 10.0 ) { isDelta911 = true; } else { isDelta911 = false; }
    
    if( 0.0 < tof[0] && tof[0] < 500.0 && F3PLA_TL_raw != 0 && F7PLA_TL_raw  !=0 && F3PLA_TR_raw != 0 && F7PLA_TR_raw  !=0) { isTOF37  = true; } else { isTOF37  = false; }
    if( 0.0 < tof[1] && tof[1] < 500.0 && F8PLA_TL_raw != 0 && F11PLA_TL_raw !=0 && F8PLA_TR_raw != 0 && F11PLA_TR_raw !=0) { isTOF811 = true; } else { isTOF811 = false; }
    if( 0.0 < tof[2] && tof[2] < 500.0 && F8PLA_TL_raw != 0 && F7PLA_TL_raw  !=0 && F8PLA_TR_raw != 0 && F7PLA_TR_raw  !=0) { isTOF78  = true; } else { isTOF78  = false; }
    
    if( F7ICEnergySqSum   > 0.0 ){ isDE7  = true; } else { isDE7  = false; }
    if( F11IC1EnergySqSum > 0.0 ){ isDE11 = true; } else { isDE11 = false; }

    if( isDE7  && isTOF37  && isDelta35  &&     1     ) { zetc[0] = zet[0]; aoqc[0] = aoq[0]; }
    if( isDE7  && isTOF37  && isDelta57  &&     1     ) { zetc[1] = zet[1]; aoqc[1] = aoq[1]; }
    if( isDE7  && isTOF37  && isDelta35  && isDelta57 ) { zetc[2] = zet[2]; aoqc[2] = aoq[2]; }
    if( isDE11 && isTOF811 && isDelta89  &&     1     ) { zetc[3] = zet[3]; aoqc[3] = aoq[3]; }
    if( isDE11 && isTOF811 && isDelta911 &&     1     ) { zetc[4] = zet[4]; aoqc[4] = aoq[4]; }
    if( isDE11 && isTOF811 && isDelta89  && isDelta911) { zetc[5] = zet[5]; aoqc[5] = aoq[5]; }

    /*
    zetc[1] = zet[1]-0.2; //OK
    zetc[2] = zet[2];     //OK
    zetc[3] = zet[3];     //OK
    zetc[4] = zet[4];     //OK
    zetc[5] = zet[5];     //OK

    aoqc[0] = aoq[0]-0.041+0.000022*F5X+0.00005*F5A+(1058-F3PLA_Q_ave)*0.000017-(570-F7PLA_Q_ave)*0.000027; 
    aoqc[1] = aoq[1]+0.038+0.00002*F5X+0.00000015*F5X*F5X+0.00001*F5A-0.00007*F7A+0.0001*F7X+(1058-F3PLA_Q_ave)*0.000017-(570-F7PLA_Q_ave)*0.000022;
    aoqc[2] = aoq[2]+0.00002*F5X+0.00000015*F5X*F5X+0.00001*F5A-0.0001*F7X+0.000002*F7A*F7A+(1058-F3PLA_Q_ave)*0.000016-(570-F7PLA_Q_ave)*0.000022; //OK
    aoqc[3] = aoq[3]+0.0005*F8X-0.0004*F8A+0.000001*F9X*F9X-0.0003*F9A+(455-F8PLA_Q_ave)*0.000055-(1229-F11PLA_Q_ave)*0.000012;
    aoqc[4] = aoq[4]-0.0025+0.00003*F9X-0.0000005*F9X*F9X+0.0006*F9A-0.00005*F9A*F9A-0.0006*F11X+0.00001*F11X*F11X+0.00025*F11A+0.00002*F11A*F11A+(455-F8PLA_Q_ave)*0.000055-(1229-F11PLA_Q_ave)*0.000012; //OK
    aoqc[5] = aoq[5]+0.000025*F9X-0.0000005*F9X*F9X+0.001*F9A-0.00007*F9A*F9A+0.000002*F9A*F9A*F9A-0.00025*F11X+0.000012*F11X*F11X-0.0000003*F11X*F11X*F11X+0.000025*F11A*F11A+0.00005*F11A+(454-F8PLA_Q_ave)*0.00006-(1229-F11PLA_Q_ave)*0.00001; //OK
    */

    
    // dipole brho of this file
    for(int idipole = 0; idipole < 8; idipole++) { dipolebrho[idipole] = para -> GetDipoleBrho(namedipole[idipole]); }
    
    
    //-------selection from multi-hit-----------//

    for(int ii = 0; ii < 7; ii++)
    {
      for(int jj = 0; jj < 4; jj++)
      {
        PPACTX1_s[ii][jj] = -9999.;
        PPACTY1_s[ii][jj] = -9999.;
        PPACTX2_s[ii][jj] = -9999.;
        PPACTY2_s[ii][jj] = -9999.;
        PPACTA_s[ii][jj]  = -9999.;

        double tdccutminx1 = ppactdc_cut_minx[ii];   double tdccutmaxx1 = ppactdc_cut_maxx[ii];
        double tdccutminx2 = ppactdc_cut_minx[ii];   double tdccutmaxx2 = ppactdc_cut_maxx[ii];
        double tdccutminy1 = ppactdc_cut_miny[ii];   double tdccutmaxy1 = ppactdc_cut_maxy[ii];
        double tdccutminy2 = ppactdc_cut_miny[ii];   double tdccutmaxy2 = ppactdc_cut_maxy[ii];
        double tdccutmina  = ppactdc_cut_mina[ii];   double tdccutmaxa  = ppactdc_cut_maxa[ii];
        
        for(int kk = 0; kk < max_multihit_ppac; kk++)
        {  
          // x1 check
          if(tdccutminx1 < PPACTX1_multi[ii][jj][kk] && PPACTX1_multi[ii][jj][kk] < tdccutmaxx1)
          {
            if(PPACTX1_s[ii][jj] < tdccutminx1 || tdccutmaxx1 < PPACTX1_s[ii][jj] || PPACTX1_multi[ii][jj][kk] < PPACTX1_s[ii][jj])
            {
              PPACTX1_s[ii][jj] = PPACTX1_multi[ii][jj][kk];
            }
          }

          // x2 check
          if(tdccutminx2 < PPACTX2_multi[ii][jj][kk] && PPACTX2_multi[ii][jj][kk] < tdccutmaxx2)
          {
            if(PPACTX2_s[ii][jj] < tdccutminx2 || tdccutmaxx2 < PPACTX2_s[ii][jj] || PPACTX2_multi[ii][jj][kk] < PPACTX2_s[ii][jj]){
              PPACTX2_s[ii][jj] = PPACTX2_multi[ii][jj][kk];
            }
          }
          
          // y1 check
          if(tdccutminy1 < PPACTY1_multi[ii][jj][kk] && PPACTY1_multi[ii][jj][kk] < tdccutmaxy1)
          {
            if(PPACTY1_s[ii][jj] < tdccutminy1 || tdccutmaxy1 < PPACTY1_s[ii][jj] || PPACTY1_multi[ii][jj][kk] < PPACTY1_s[ii][jj])
            {
              PPACTY1_s[ii][jj] = PPACTY1_multi[ii][jj][kk];
            }
          }
          
          // y2 check
          if(tdccutminy2 < PPACTY2_multi[ii][jj][kk] && PPACTY2_multi[ii][jj][kk] < tdccutmaxy2)
          {
            if(PPACTY2_s[ii][jj] < tdccutminy2 || tdccutmaxy2 < PPACTY2_s[ii][jj] || PPACTY2_multi[ii][jj][kk] < PPACTY2_s[ii][jj])
            {
              PPACTY2_s[ii][jj] = PPACTY2_multi[ii][jj][kk];
            }
          }
          
          // a check
          if(tdccutmina < PPACTA_multi[ii][jj][kk] && PPACTA_multi[ii][jj][kk] < tdccutmaxa)
          {
            if(PPACTA_s[ii][jj] < tdccutmina || tdccutmaxa < PPACTA_s[ii][jj] || PPACTA_multi[ii][jj][kk] < PPACTA_s[ii][jj])
            {
              PPACTA_s[ii][jj] = PPACTA_multi[ii][jj][kk];
            }
          }
        
        }
      }
    }
    

    F3PLA_TL_raw_s   = -9999.;  F3PLA_TR_raw_s   = -9999.;
    F5PLA_TL_raw_s   = -9999.;  F5PLA_TR_raw_s   = -9999.;
    F7PLA_TL_raw_s   = -9999.;  F7PLA_TR_raw_s   = -9999.;
    F8PLA_TL_raw_s   = -9999.;  F8PLA_TR_raw_s   = -9999.;
    F11PLA_TL_raw_s  = -9999.;  F11PLA_TR_raw_s  = -9999.;
    F11PLA2_TL_raw_s = -9999.;  F11PLA2_TR_raw_s = -9999.;
    F11LONG_TL_raw_s = -9999.;  F11LONG_TR_raw_s = -9999.;
    F11VETO_TL_raw_s = -9999.;  F11VETO_TR_raw_s = -9999.;
    
    for(int kk = 0; kk < max_multihit_pla; kk++)
    {
      int ipla;

      // F3PLA
      ipla = 0;
      if(platdc_cut_min_l[ipla] < F3PLA_TL_raw_multi[kk] && F3PLA_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F3PLA_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F3PLA_TL_raw_s || F3PLA_TL_raw_multi[kk] < F3PLA_TL_raw_s)
        {
          F3PLA_TL_raw_s = F3PLA_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F3PLA_TR_raw_multi[kk] && F3PLA_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F3PLA_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F3PLA_TR_raw_s || F3PLA_TR_raw_multi[kk] < F3PLA_TR_raw_s)
        {
          F3PLA_TR_raw_s = F3PLA_TR_raw_multi[kk];
        }
      }

      // F5PLA
      ipla = 1;
      if(platdc_cut_min_l[ipla] < F5PLA_TL_raw_multi[kk] && F5PLA_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F5PLA_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F5PLA_TL_raw_s || F5PLA_TL_raw_multi[kk] < F5PLA_TL_raw_s)
        {
          F5PLA_TL_raw_s = F5PLA_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F5PLA_TR_raw_multi[kk] && F5PLA_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F5PLA_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F5PLA_TR_raw_s || F5PLA_TR_raw_multi[kk] < F5PLA_TR_raw_s)
        {
          F5PLA_TR_raw_s = F5PLA_TR_raw_multi[kk];
        }
      }

      // F7PLA
      ipla = 2;
      if(platdc_cut_min_l[ipla] < F7PLA_TL_raw_multi[kk] && F7PLA_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F7PLA_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F7PLA_TL_raw_s || F7PLA_TL_raw_multi[kk] < F7PLA_TL_raw_s)
        {
          F7PLA_TL_raw_s = F7PLA_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F7PLA_TR_raw_multi[kk] && F7PLA_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F7PLA_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F7PLA_TR_raw_s || F7PLA_TR_raw_multi[kk] < F7PLA_TR_raw_s)
        {
          F7PLA_TR_raw_s = F7PLA_TR_raw_multi[kk];
        }
      }

      // F8PLA
      ipla = 3;
      if(platdc_cut_min_l[ipla] < F8PLA_TL_raw_multi[kk] && F8PLA_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F8PLA_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F8PLA_TL_raw_s || F8PLA_TL_raw_multi[kk] < F8PLA_TL_raw_s)
        {
          F8PLA_TL_raw_s = F8PLA_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F8PLA_TR_raw_multi[kk] && F8PLA_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F8PLA_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F8PLA_TR_raw_s || F8PLA_TR_raw_multi[kk] < F8PLA_TR_raw_s)
        {
          F8PLA_TR_raw_s = F8PLA_TR_raw_multi[kk];
        }
      }

      // F11PLA
      ipla = 4;
      if(platdc_cut_min_l[ipla] < F11PLA_TL_raw_multi[kk] && F11PLA_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F11PLA_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F11PLA_TL_raw_s || F11PLA_TL_raw_multi[kk] < F11PLA_TL_raw_s)
        {
          F11PLA_TL_raw_s = F11PLA_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F11PLA_TR_raw_multi[kk] && F11PLA_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F11PLA_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F11PLA_TR_raw_s || F11PLA_TR_raw_multi[kk] < F11PLA_TR_raw_s)
        {
          F11PLA_TR_raw_s = F11PLA_TR_raw_multi[kk];
        }
      }

      // F11LONG
      ipla = 5;
      if(platdc_cut_min_l[ipla] < F11LONG_TL_raw_multi[kk] && F11LONG_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F11LONG_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F11LONG_TL_raw_s || F11LONG_TL_raw_multi[kk] < F11LONG_TL_raw_s)
        {
          F11LONG_TL_raw_s = F11LONG_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F11LONG_TR_raw_multi[kk] && F11LONG_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F11LONG_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F11LONG_TR_raw_s || F11LONG_TR_raw_multi[kk] < F11LONG_TR_raw_s)
        {
          F11LONG_TR_raw_s = F11LONG_TR_raw_multi[kk];
        }
      }

      // F11VETO
      ipla = 6;
      if(platdc_cut_min_l[ipla] < F11VETO_TL_raw_multi[kk] && F11VETO_TL_raw_multi[kk] < platdc_cut_max_l[ipla])
      {
        if(F11VETO_TL_raw_s < platdc_cut_min_l[ipla] ||  platdc_cut_max_l[ipla] < F11VETO_TL_raw_s || F11VETO_TL_raw_multi[kk] < F11VETO_TL_raw_s)
        {
          F11VETO_TL_raw_s = F11VETO_TL_raw_multi[kk];
        }
      }
      if(platdc_cut_min_r[ipla] < F11VETO_TR_raw_multi[kk] && F11VETO_TR_raw_multi[kk] < platdc_cut_max_r[ipla])
      {
        if(F11VETO_TR_raw_s < platdc_cut_min_r[ipla] ||  platdc_cut_max_r[ipla] < F11VETO_TR_raw_s || F11VETO_TR_raw_multi[kk] < F11VETO_TR_raw_s)
        {
          F11VETO_TR_raw_s = F11VETO_TR_raw_multi[kk];
        }
      }
      
    }
    

    //______________________________________________________________________________
	  //
	  // DALI
	  //______________________________________________________________________________

      
    dalicalib -> ClearData();
    dalicalib -> SetPlTime(tof[2]);
    // dalicalib -> SetVertex(z_vertex-3.9);
    dalicalib->SetVertex(0.0);
    
    // Add above to remove F8plastic tof.
    dalicalib -> ReconstructData();
    
    dalimultwotime        = dalicalib -> GetMultWithoutT();
    dalimult              = dalicalib -> GetMult();
    dalitimetruemult      = dalicalib -> GetTimeTrueMult();
    dalimultthres         = dalicalib -> GetMultThres();
    dalitimetruemultthres = dalicalib -> GetTimeTrueMultThres();
 
    tree -> Fill();
    neve++;
  }
  cout << "\n Writing the tree. \n" << endl;
  
  fout -> Write();
  fout -> Close();
}
