#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtBigRIPSParameters.hh"
#include "TArtDALIParameters.hh"
//#include "TArtMINOSParameters.hh"
#include "TArtCalibPID.hh"
#include "TArtCalibDALI.hh"
//#include "TArtCalibMINOS.hh"

//#include "TArtAnalyzedMINOS.hh"
//#include "TArtTrackMINOS.hh"
//#include "TArtVertexMINOS.hh"
#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibIC.hh"
#include "TArtCalibFocalPlane.hh"
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

#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "signal.h"
#include "fstream"
#include "iostream"

#include "segidlist.hh"

using namespace std;

// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void stop_interrupt(){
  printf("keyboard interrupt\n");
  stoploop = true;
}

void MakeAllTree(char *infile="ridf/psp140035.ridf.gz", char *outfile="run0025.root"){

  //  signal(SIGINT,stop_interrupt); // CTRL + C , interrupt

  // Create StoreManager both for calibration "TArtCalib..." and treatment "TArtReco..."
  //------------------------------------------------------------------------------------
  TArtStoreManager * sman = TArtStoreManager::Instance();
  
  // Create EventStore to control the loop and get the EventInfo
  //------------------------------------------------------------
  TArtEventStore *estore = new TArtEventStore();
  estore->SetInterrupt(&stoploop); 
  estore->Open(infile);
  std::cout<<"estore ->"<< infile <<std::endl;
  
  // Create BigRIPSParameters to get Plastics, PPACs, ICs and FocalPlanes parameters from ".xml" files
  //--------------------------------------------------------------------------------------------------	
  TArtBigRIPSParameters *para = TArtBigRIPSParameters::Instance();
  para->LoadParameter("db/BigRIPSPPAC.xml");
  para->LoadParameter("db/BigRIPSPlastic.xml");
  para->LoadParameter("db/BigRIPSIC.xml");
  para->LoadParameter("db/FocalPlane.xml");
  para->SetFocusPosOffset(8,138.5);

  // Create CalibPID to get and calibrate raw data ( CalibPID -> 
  //[CalibPPAC , CalibIC, CalibPlastic , CalibFocalPlane] 
  TArtCalibPID *brcalib          = new TArtCalibPID();
  TArtCalibPPAC *ppaccalib       = brcalib->GetCalibPPAC();
  TArtCalibPlastic *plasticcalib = brcalib->GetCalibPlastic();
  TArtCalibIC *iccalib           = brcalib->GetCalibIC(); 
  TArtCalibFocalPlane *cfpl      = brcalib->GetCalibFocalPlane();
  
  // Create RecoPID to get calibrated data and to reconstruct TOF, AoQ, Z, ... (RecoPID -> 
  //[ RecoTOF , RecoRIPS , RecoBeam] )
  TArtRecoPID *recopid = new TArtRecoPID();
 
  //para->PrintListOfPPACPara();
  //return;

  // Definition of observables we want to reconstruct
  std::cout << "Defining bigrips parameters" << std::endl;  
  TArtRIPS *rips3to5  = recopid->DefineNewRIPS(3,5,"matrix/mat1.mat","D3"); // F3 - F5
  TArtRIPS *rips5to7  = recopid->DefineNewRIPS(5,7,"matrix/mat2.mat","D5"); // F5 - F7
  TArtRIPS *rips8to9  = recopid->DefineNewRIPS(8,9,"matrix/F8F9_LargeAccAchr.mat","D7"); // F8 - F9
  TArtRIPS *rips9to11 = recopid->DefineNewRIPS(9,11,"matrix/F9F11_LargeAccAchr.mat","D8"); // F9 - F11  

  // Reconstruction of TOF DefineNewTOF(fisrt plane, second plane, time offset)
  //For 66Cr
  TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.88,5); // F3 - F7
  TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-161.45,9); // F8 - F11
  
  //For 70,72Fe
  //TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.95,5); // F3 - F7
  //TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159,9); // F8 - F11

  //For 78Ni
  //TArtTOF *tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",300.25,5); // F3 - F7
  //TArtTOF *tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-159.45,9); // F8 - F11
  
  TArtTOF *tof7to8  = recopid->DefineNewTOF("F7pl","F8pl"); // F7 - F8

  // Reconstruction of IC observables for ID
  TArtBeam *beam_br_35 = recopid->DefineNewBeam(rips3to5,tof3to7,"F7IC");
  TArtBeam *beam_br_57 = recopid->DefineNewBeam(rips5to7,tof3to7,"F7IC");   
  TArtBeam *beam_br_37 = recopid->DefineNewBeam(rips3to5,rips5to7,tof3to7,"F7IC");   
  
  TArtBeam *beam_zd_89  = recopid->DefineNewBeam(rips8to9,tof8to11,"F11IC");
  TArtBeam *beam_zd_911 = recopid->DefineNewBeam(rips9to11,tof8to11,"F11IC");
  TArtBeam *beam_zd_811 = recopid->DefineNewBeam(rips8to9,rips9to11,tof8to11,"F11IC");

  //to get trigger pattern
  //TArtEventInfo *evtinfo=new TArtEventInfo();

  // Create DALIParameters to get ".xml"
  //------------------------------------

  TArtDALIParameters *dpara = TArtDALIParameters::Instance();
  dpara->LoadParameter("db/DALI.xml");
  
  // Create CalibDALI to get and calibrate raw data
  //-----------------------------------------------
  TArtCalibDALI *dalicalib = new TArtCalibDALI();

  std::cout<<"para"<<std::endl;

  TFile *fout = new TFile(outfile,"RECREATE");
  TTree *tree = new TTree("tree","tree");

  // define data nodes which are supposed to be dumped to tree 
  //EventInfo is important for the fBit information to know the trigger!
  TClonesArray * info_array = (TClonesArray *)sman->FindDataContainer("EventInfo");

  int triggerbit = -9999;
  int fbit = 0;

  std::cout<<info_array->GetName()<<std::endl;
  tree->Branch(info_array->GetName(),&info_array);
  tree->Branch("fbit",&fbit,"fbit/I");

  //TClonesArray * ppac_array = 
  //  (TClonesArray *)sman->FindDataContainer("BigRIPSPPAC");
  //std::cout<<ppac_array->GetName()<<std::endl;
  //tree->Branch(ppac_array->GetName(),&ppac_array);
  
  //TClonesArray * pla_array = 
  //  (TClonesArray *)sman->FindDataContainer("BigRIPSPlastic");
  //tree->Branch(pla_array->GetName(),&pla_array);
 
  //TClonesArray * ic_array = 
  //  (TClonesArray *)sman->FindDataContainer("BigRIPSIC");
  //tree->Branch(ic_array->GetName(),&ic_array);
  
  //TClonesArray * fpl_array = 
  //  (TClonesArray *)sman->FindDataContainer("BigRIPSFocalPlane");
  //tree->Branch(fpl_array->GetName(),&fpl_array);
  
  //Dali data
  TClonesArray * dali_array=
    (TClonesArray *)sman->FindDataContainer("DALINaI");
  tree->Branch(dali_array->GetName(),&dali_array);
  
  //PID reconstructed data:
  //TClonesArray *rips_array = 
  /// (TClonesArray *)sman->FindDataContainer("BigRIPSRIPS");
  //std::cout<<rips_array->GetName()<<std::endl;     
  //tree->Branch(rips_array->GetName(),&rips_array); 
  
  //TClonesArray *tof_array  = 
  //  (TClonesArray *)sman->FindDataContainer("BigRIPSTOF");
  //std::cout<<tof_array->GetName()<<std::endl;     
  //tree->Branch(tof_array->GetName(),&tof_array);   
  
  /*
    TClonesArray *beam_array = 
    (TClonesArray *)sman->FindDataContainer("BigRIPSBeam");	
    std::cout<<beam_array->GetName()<<std::endl;     
    tree->Branch(beam_array->GetName(),&beam_array); 
  */

  //_________________________________________________________________________
  //Making new branches
  
  //%%%%%%%%%%%%%%%%%%%%%%
  //BigRIPS
    
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //The Focalplane:
  
  Double_t F3X=-9999; Double_t F3A=-9999; Double_t F3Y=-9999; Double_t F3B=-9999;
  Double_t F5X=-9999; Double_t F5A=-9999; Double_t F5Y=-9999; Double_t F5B=-9999;
  Double_t F7X=-9999; Double_t F7A=-9999; Double_t F7Y=-9999; Double_t F7B=-9999;
  Double_t F8X=-9999; Double_t F8A=-9999; Double_t F8Y=-9999; Double_t F8B=-9999;
  Double_t F9X=-9999; Double_t F9A=-9999; Double_t F9Y=-9999; Double_t F9B=-9999;
  Double_t F11X=-9999; Double_t F11A=-9999; Double_t F11Y=-9999; Double_t F11B=-9999;
  
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

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //The plastic time:

  Double_t F3PLA_TL_raw=-9999;  Double_t F3PLA_TR_raw=-9999;  
  Double_t F5PLA_TL_raw=-9999;  Double_t F5PLA_TR_raw=-9999;  
  Double_t F7PLA_TL_raw=-9999;  Double_t F7PLA_TR_raw=-9999;  
  Double_t F8PLA_TL_raw=-9999;  Double_t F8PLA_TR_raw=-9999;  
  Double_t F11PLA_TL_raw=-9999; Double_t F11PLA_TR_raw=-9999; 
  Double_t F11PLA2_TL_raw=-9999; Double_t F11PLA2_TR_raw=-9999; 
  Double_t F11LONG_TL_raw=-9999; Double_t F11LONG_TR_raw=-9999; 
  Double_t F11VETO_TL_raw=-9999; Double_t F11VETO_TR_raw=-9999; 

  Double_t F3PLA_TL=-9999;  Double_t F3PLA_TR=-9999;  Double_t F3PLA_T=-9999;  
  Double_t F5PLA_TL=-9999;  Double_t F5PLA_TR=-9999;  Double_t F5PLA_T=-9999;  
  Double_t F7PLA_TL=-9999;  Double_t F7PLA_TR=-9999;  Double_t F7PLA_T=-9999;  
  Double_t F8PLA_TL=-9999;  Double_t F8PLA_TR=-9999;  Double_t F8PLA_T=-9999;  
  Double_t F11PLA_TL=-9999; Double_t F11PLA_TR=-9999; Double_t F11PLA_T=-9999; 
  Double_t F11PLA2_TL=-9999; Double_t F11PLA2_TR=-9999; Double_t F11PLA2_T=-9999; 
  Double_t F11LONG_TL=-9999; Double_t F11LONG_TR=-9999; Double_t F11LONG_T=-9999; 
  Double_t F11VETO_TL=-9999; Double_t F11VETO_TR=-9999; Double_t F11VETO_T=-9999; 

  tree->Branch("F3PLA_TL_raw",&F3PLA_TL_raw,"F3PLA_TL_raw/D");
  tree->Branch("F3PLA_TR_raw",&F3PLA_TR_raw,"F3PLA_TR_raw/D");
  tree->Branch("F3PLA_TL",&F3PLA_TL,"F3PLA_TL/D");
  tree->Branch("F3PLA_TR",&F3PLA_TR,"F3PLA_TR/D");
  tree->Branch("F3PLA_T",&F3PLA_T,"F3PLA_T/D");

  tree->Branch("F5PLA_TL_raw",&F5PLA_TL_raw,"F5PLA_TL_raw/D");
  tree->Branch("F5PLA_TR_raw",&F5PLA_TR_raw,"F5PLA_TR_raw/D");
  tree->Branch("F5PLA_TL",&F5PLA_TL,"F5PLA_TL/D");
  tree->Branch("F5PLA_TR",&F5PLA_TR,"F5PLA_TR/D");
  tree->Branch("F5PLA_T",&F5PLA_T,"F5PLA_T/D");

  tree->Branch("F7PLA_TL_raw",&F7PLA_TL_raw,"F7PLA_TL_raw/D");
  tree->Branch("F7PLA_TR_raw",&F7PLA_TR_raw,"F7PLA_TR_raw/D");
  tree->Branch("F7PLA_TL",&F7PLA_TL,"F7PLA_TL/D");
  tree->Branch("F7PLA_TR",&F7PLA_TR,"F7PLA_TR/D");
  tree->Branch("F7PLA_T",&F7PLA_T,"F7PLA_T/D");

  tree->Branch("F8PLA_TL_raw",&F8PLA_TL_raw,"F8PLA_TL_raw/D");
  tree->Branch("F8PLA_TR_raw",&F8PLA_TR_raw,"F8PLA_TR_raw/D");
  tree->Branch("F8PLA_TL",&F8PLA_TL,"F8PLA_TL/D");
  tree->Branch("F8PLA_TR",&F8PLA_TR,"F8PLA_TR/D");
  tree->Branch("F8PLA_T",&F8PLA_T,"F8PLA_T/D");

  tree->Branch("F11PLA_TL_raw",&F11PLA_TL_raw,"F11PLA_TL_raw/D");
  tree->Branch("F11PLA_TR_raw",&F11PLA_TR_raw,"F11PLA_TR_raw/D");
  tree->Branch("F11PLA_TL",&F11PLA_TL,"F11PLA_TL/D");
  tree->Branch("F11PLA_TR",&F11PLA_TR,"F11PLA_TR/D");
  tree->Branch("F11PLA_T",&F11PLA_T,"F11PLA_T/D");
  
  tree->Branch("F11PLA2_TL_raw",&F11PLA2_TL_raw,"F11PLA2_TL_raw/D");
  tree->Branch("F11PLA2_TR_raw",&F11PLA2_TR_raw,"F11PLA2_TR_raw/D");
  tree->Branch("F11PLA2_TL",&F11PLA2_TL,"F11PLA2_TL/D");
  tree->Branch("F11PLA2_TR",&F11PLA2_TR,"F11PLA2_TR/D");
  tree->Branch("F11PLA2_T",&F11PLA2_T,"F11PLA2_T/D");
  
  tree->Branch("F11LONG_TL_raw",&F11LONG_TL_raw,"F11LONG_TL_raw/D");
  tree->Branch("F11LONG_TR_raw",&F11LONG_TR_raw,"F11LONG_TR_raw/D");
  tree->Branch("F11LONG_TL",&F11LONG_TL,"F11LONG_TL/D");
  tree->Branch("F11LONG_TR",&F11LONG_TR,"F11LONG_TR/D");
  tree->Branch("F11LONG_T",&F11LONG_T,"F11LONG_T/D");
  
  tree->Branch("F11VETO_TL_raw",&F11VETO_TL_raw,"F11VETO_TL_raw/D");
  tree->Branch("F11VETO_TR_raw",&F11VETO_TR_raw,"F11VETO_TR_raw/D");
  tree->Branch("F11VETO_TL",&F11VETO_TL,"F11VETO_TL/D");
  tree->Branch("F11VETO_TR",&F11VETO_TR,"F11VETO_TR/D");
  tree->Branch("F11VETO_T",&F11VETO_T,"F11VETO_T/D");
  
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //The plastic Q values:

  Double_t F3PLA_QL_raw=-9999;  Double_t F3PLA_QR_raw=-9999;  
  Double_t F5PLA_QL_raw=-9999;  Double_t F5PLA_QR_raw=-9999;  
  Double_t F7PLA_QL_raw=-9999;  Double_t F7PLA_QR_raw=-9999;  
  Double_t F8PLA_QL_raw=-9999;  Double_t F8PLA_QR_raw=-9999;  
  Double_t F11PLA_QL_raw=-9999; Double_t F11PLA_QR_raw=-9999; 
  Double_t F11PLA2_QL_raw=-9999; Double_t F11PLA2_QR_raw=-9999; 
  Double_t F11LONG_QL_raw=-9999; Double_t F11LONG_QR_raw=-9999; 
  Double_t F11VETO_QL_raw=-9999; Double_t F11VETO_QR_raw=-9999; 

  Double_t F3PLA_Q_ave=-9999; 
  Double_t F5PLA_Q_ave=-9999; 
  Double_t F7PLA_Q_ave=-9999;   
  Double_t F8PLA_Q_ave=-9999; 
  Double_t F11PLA_Q_ave=-9999;
  Double_t F11PLA2_Q_ave=-9999;
  Double_t F11LONG_Q_ave=-9999;
  Double_t F11VETO_Q_ave=-9999;
  
  tree->Branch("F3PLA_QL_raw",&F3PLA_QL_raw,"F3PLA_QL_raw/D");
  tree->Branch("F3PLA_QR_raw",&F3PLA_QR_raw,"F3PLA_QR_raw/D");
  tree->Branch("F3PLA_Q_ave",&F3PLA_Q_ave,"F3PLA_Q_ave/D");

  tree->Branch("F5PLA_QL_raw",&F5PLA_QL_raw,"F5PLA_QL_raw/D");
  tree->Branch("F5PLA_QR_raw",&F5PLA_QR_raw,"F5PLA_QR_raw/D");
  tree->Branch("F5PLA_Q_ave",&F5PLA_Q_ave,"F5PLA_Q_ave/D");

  tree->Branch("F7PLA_QL_raw",&F7PLA_QL_raw,"F7PLA_QL_raw/D");
  tree->Branch("F7PLA_QR_raw",&F7PLA_QR_raw,"F7PLA_QR_raw/D");
  tree->Branch("F7PLA_Q_ave",&F7PLA_Q_ave,"F7PLA_Q_ave/D");

  tree->Branch("F8PLA_QL_raw",&F8PLA_QL_raw,"F8PLA_QL_raw/D");
  tree->Branch("F8PLA_QR_raw",&F8PLA_QR_raw,"F8PLA_QR_raw/D");
  tree->Branch("F8PLA_Q_ave",&F8PLA_Q_ave,"F8PLA_Q_ave/D");

  tree->Branch("F11PLA_QL_raw",&F11PLA_QL_raw,"F11PLA_QL_raw/D");
  tree->Branch("F11PLA_QR_raw",&F11PLA_QR_raw,"F11PLA_QR_raw/D");
  tree->Branch("F11PLA_Q_ave",&F11PLA_Q_ave,"F11PLA_Q_ave/D");

  tree->Branch("F11PLA2_QL_raw",&F11PLA2_QL_raw,"F11PLA2_QL_raw/D");
  tree->Branch("F11PLA2_QR_raw",&F11PLA2_QR_raw,"F11PLA2_QR_raw/D");
  tree->Branch("F11PLA2_Q_ave",&F11PLA2_Q_ave,"F11PLA2_Q_ave/D");

  tree->Branch("F11LONG_QL_raw",&F11LONG_QL_raw,"F11LONG_QL_raw/D");
  tree->Branch("F11LONG_QR_raw",&F11LONG_QR_raw,"F11LONG_QR_raw/D");
  tree->Branch("F11LONG_Q_ave",&F11LONG_Q_ave,"F11LONG_Q_ave/D");

  tree->Branch("F11VETO_QL_raw",&F11VETO_QL_raw,"F11VETO_QL_raw/D");
  tree->Branch("F11VETO_QR_raw",&F11VETO_QR_raw,"F11VETO_QR_raw/D");
  tree->Branch("F11VETO_Q_ave",&F11VETO_Q_ave,"F11VETO_Q_ave/D");

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //The MUSIC:

  Double_t F7ICNumHit=-9999;
  Double_t F7ICEnergySqSum=-9999;
  Double_t F7ICEnergyAvSum=-9999;

  Double_t F11ICNumHit=-9999;
  Double_t F11ICEnergySqSum=-9999;
  Double_t F11ICEnergyAvSum=-9999;

  Double_t F11ICNumHit2=-9999;
  Double_t F11ICEnergySqSum2=-9999;
  Double_t F11ICEnergyAvSum2=-9999;

  tree->Branch("F7ICNumHit",&F7ICNumHit,"F7ICNumHit/D");
  tree->Branch("F7ICEnergySqSum",&F7ICEnergySqSum,"F7ICEnergySqSum/D");
  tree->Branch("F7ICEnergyAvSum",&F7ICEnergyAvSum,"F7ICEnergyAvSum/D");

  tree->Branch("F11ICNumHit",&F11ICNumHit,"F11ICNumHit/D");
  tree->Branch("F11ICEnergySqSum",&F11ICEnergySqSum,"F11ICEnergySqSum/D");
  tree->Branch("F11ICEnergyAvSum",&F11ICEnergyAvSum,"F11ICEnergyAvSum/D");

  tree->Branch("F11ICNumHit2",&F11ICNumHit2,"F11ICNumHit2/D");
  tree->Branch("F11ICEnergySqSum2",&F11ICEnergySqSum2,"F11ICEnergySqSum2/D");
  tree->Branch("F11ICEnergyAvSum2",&F11ICEnergyAvSum2,"F11ICEnergyAvSum2/D");

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // PID:

  Double_t tof[3];
  Double_t beta[3];
 
  Double_t zet[6];
  Double_t aoq[6];
  Double_t zetc[6];
  Double_t aoqc[6];  //Corrected PID

  Double_t delta[4];
  
  tree->Branch("tof",tof,"tof[3]/D");
  tree->Branch("beta",beta,"beta[3]/D");
 
  tree->Branch("zet",zet,"zet[6]/D");
  tree->Branch("zetc",zetc,"zetc[6]/D");
  tree->Branch("aoq",aoq,"aoq[6]/D");
  tree->Branch("aoqc",aoqc,"aoqc[6]/D");
  tree->Branch("delta",delta,"delta[6]/D");

  //%%%%%%%%%%%%%%%%%%%%%%
  //DALI
 
  Int_t dalimultwotime = 0;
  Int_t dalimult = 0;
  Int_t dalitimetruemult = 0;
  Int_t dalimultthres = 0;
  Int_t dalitimetruemultthres = 0;

  tree->Branch("dalimultwotime",&dalimultwotime,"dalimultwotime/I");
  tree->Branch("dalimult",&dalimult,"dalimult/I");
  tree->Branch("dalitimetruemult",&dalitimetruemult,"dalitimetruemult/I");
  tree->Branch("dalimultthres",&dalimultthres,"dalimultthres/I");
  tree->Branch("dalitimetruemultthres",&dalitimetruemultthres,"dalitimetruemultthres/I");

  //%%%%%%%%%%%%%%%%%%%%%%
  //MINOS

  //Double_t z_vertex=0.;
  //tree->Branch("z_vertex",&z_vertex,"z_vertex/D");

  int neve = 0;
  while(estore->GetNextEvent()){
    if(neve%1000==0)
      //std::cout << "event: " << neve << std::endl;
      std::cout << "Event: " << neve <<" done\r"<<std::flush;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //Making the BigRIPS tree calibration
    brcalib->ClearData();
    brcalib->ReconstructData();
    
    //Reconstructiong the PID
    recopid->ClearData();
    recopid->ReconstructData();
  

    fbit = 0;
    TArtRawEventObject *rawevent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");
    for(int i=0;i<rawevent -> GetNumSeg();i++){
      TArtRawSegmentObject *seg = rawevent -> GetSegment(i);
      Int_t fpl = seg -> GetFP();
      Int_t detector = seg -> GetDetector();
      //if(fpl==63 && detector==10){
      if(fpl==B3F && detector==10){
        for(int j=0; j < seg -> GetNumData(); j++){
          TArtRawDataObject *d = seg -> GetData(j);
          triggerbit = d -> GetVal();
          //cout<<"triggerbit: "<<triggerbit<<endl;
        }
      }
    }
    fbit=triggerbit;
    //for(Int_t i = 0; i < 7; i++){
    //  if ((triggerbit >> i) & 0x1)
    //    fbit = i+1;
    //} 
    
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

    F11PLA2_QL_raw=-9999; F11PLA2_QR_raw=-9999; F11PLA2_TL=-9999; F11PLA2_TR=-9999; F11PLA2_T=-9999;
    F11PLA2_QL_raw=-9999; F11PLA2_QR_raw=-9999; F11PLA2_Q_ave=-9999; 

    F11LONG_QL_raw=-9999; F11LONG_QR_raw=-9999; F11LONG_TL=-9999; F11LONG_TR=-9999; F11LONG_T=-9999;
    F11LONG_QL_raw=-9999; F11LONG_QR_raw=-9999; F11LONG_Q_ave=-9999; 

    F11VETO_QL_raw=-9999; F11VETO_QR_raw=-9999; F11VETO_TL=-9999; F11VETO_TR=-9999; F11VETO_T=-9999;
    F11VETO_QL_raw=-9999; F11VETO_QR_raw=-9999; F11VETO_Q_ave=-9999; 

    TArtPlastic *tpla;
    tpla = plasticcalib->FindPlastic("F3pl");
    if(tpla){
      
      F3PLA_TL_raw = tpla->GetTLRaw(); F3PLA_TR_raw = tpla->GetTRRaw(); 
      F3PLA_TL = tpla->GetTimeL(); F3PLA_TR = tpla->GetTimeR(); 
      F3PLA_T = tpla->GetTime();

      F3PLA_QL_raw = tpla->GetQLRaw(); F3PLA_QR_raw = tpla->GetQRRaw();
      F3PLA_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F5pl");
    if(tpla){
      
      F5PLA_TL_raw = tpla->GetTLRaw(); F5PLA_TR_raw = tpla->GetTRRaw(); 
      F5PLA_TL = tpla->GetTimeL(); F5PLA_TR = tpla->GetTimeR(); 
      F5PLA_T = tpla->GetTime();

      F5PLA_QL_raw = tpla->GetQLRaw(); F5PLA_QR_raw = tpla->GetQRRaw();
      F5PLA_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F7pl");
    if(tpla){
      F7PLA_TL_raw = tpla->GetTLRaw(); F7PLA_TR_raw = tpla->GetTRRaw(); 
      F7PLA_TL = tpla->GetTimeL(); F7PLA_TR = tpla->GetTimeR(); 
      F7PLA_T = tpla->GetTime();
      
      F7PLA_QL_raw = tpla->GetQLRaw(); F7PLA_QR_raw = tpla->GetQRRaw(); 
      F7PLA_Q_ave = tpla->GetQAveRaw();
    }
 
    tpla = plasticcalib->FindPlastic("F8pl");
    if(tpla){
      F8PLA_TL_raw = tpla->GetTLRaw(); F8PLA_TR_raw = tpla->GetTRRaw(); 
      F8PLA_TL = tpla->GetTimeL(); F8PLA_TR = tpla->GetTimeR(); 
      F8PLA_T = tpla->GetTime();

      F8PLA_QL_raw = tpla->GetQLRaw(); F8PLA_QR_raw = tpla->GetQRRaw(); 
      F8PLA_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F11pl-1");
    if(tpla){
      F11PLA_TL_raw = tpla->GetTLRaw(); F11PLA_TR_raw = tpla->GetTRRaw(); 
      F11PLA_TL = tpla->GetTimeL(); F11PLA_TR = tpla->GetTimeR(); 
      F11PLA_T = tpla->GetTime();

      F11PLA_QL_raw = tpla->GetQLRaw(); F11PLA_QR_raw = tpla->GetQRRaw(); 
      F11PLA_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F11pl-2");
    if(tpla){
      F11PLA2_TL_raw = tpla->GetTLRaw(); F11PLA2_TR_raw = tpla->GetTRRaw(); 
      F11PLA2_TL = tpla->GetTimeL(); F11PLA2_TR = tpla->GetTimeR(); 
      F11PLA2_T = tpla->GetTime();

      F11PLA2_QL_raw = tpla->GetQLRaw(); F11PLA2_QR_raw = tpla->GetQRRaw(); 
      F11PLA2_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F11long");
    if(tpla){
      F11LONG_TL_raw = tpla->GetTLRaw(); F11LONG_TR_raw = tpla->GetTRRaw(); 
      F11LONG_TL = tpla->GetTimeL(); F11LONG_TR = tpla->GetTimeR(); 
      F11LONG_T = tpla->GetTime();

      F11LONG_QL_raw = tpla->GetQLRaw(); F11LONG_QR_raw = tpla->GetQRRaw(); 
      F11LONG_Q_ave = tpla->GetQAveRaw();
    }

    tpla = plasticcalib->FindPlastic("F11veto");
    if(tpla){
      F11VETO_TL_raw = tpla->GetTLRaw(); F11VETO_TR_raw = tpla->GetTRRaw(); 
      F11VETO_TL = tpla->GetTimeL(); F11VETO_TR = tpla->GetTimeR(); 
      F11VETO_T = tpla->GetTime();

      F11VETO_QL_raw = tpla->GetQLRaw(); F11VETO_QR_raw = tpla->GetQRRaw(); 
      F11VETO_Q_ave = tpla->GetQAveRaw();
    }

    //The MUSICs
    F7ICNumHit=-9999;
    F7ICEnergySqSum=-9999;
    F7ICEnergyAvSum=-9999;
  
    F11ICNumHit=-9999;
    F11ICEnergySqSum=-9999;
    F11ICEnergyAvSum=-9999;

    F11ICNumHit2=-9999;
    F11ICEnergySqSum2=-9999;
    F11ICEnergyAvSum2=-9999;

    TArtIC *tic;  
    tic = iccalib->FindIC("F7IC");
    if(tic) {
      F7ICNumHit=tic->GetNumHit();
      F7ICEnergySqSum=tic->GetEnergySqSum();
      F7ICEnergyAvSum=tic->GetEnergyAvSum();
    }

    tic = iccalib->FindIC("F11IC");
    if(tic) {
      F11ICNumHit=tic->GetNumHit();
      F11ICEnergySqSum=tic->GetEnergySqSum();
      F11ICEnergyAvSum=tic->GetEnergyAvSum();
    }

    tic = iccalib->FindIC("F11IC_2");
    if(tic) {
      F11ICNumHit2=tic->GetNumHit();
      F11ICEnergySqSum2=tic->GetEnergySqSum();
      F11ICEnergyAvSum2=tic->GetEnergyAvSum();
    }
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //PID

    //The TOF
    tof[0] = tof3to7->GetTOF();
    beta[0] = tof3to7->GetBeta();
    
    tof[1] = tof8to11->GetTOF();
    beta[1] = tof8to11->GetBeta();
          
    tof[2] = tof7to8->GetTOF();
    beta[2] = tof7to8->GetBeta();

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
   
  
    /*  
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
    */
   
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
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //Making DALI
      
    dalicalib->ClearData();
    dalicalib->SetPlTime(tof[2]);
    //dalicalib->SetVertex(z_vertex-3.9);
    dalicalib->SetVertex(0.0);
    //Add above to remove F8plastic tof.
    dalicalib->ReconstructData();
    
    dalimultwotime = dalicalib->GetMultWithoutT();
    dalimult = dalicalib->GetMult();
    dalitimetruemult = dalicalib->GetTimeTrueMult();
    dalimultthres = dalicalib->GetMultThres();
    dalitimetruemultthres = dalicalib->GetTimeTrueMultThres();
 
    //cout << "F3pl TL raw===" << F3PLA_TL_raw << endl;
    //cout << "F5pl TL raw===" << F5PLA_TL_raw << endl;
    //cout << "F7pl TL raw===" << F7PLA_TL_raw << endl;
    //cout << "F8pl TL raw===" << F8PLA_TL_raw << endl;
    //cout << "F11pl TL raw===" << F11PLA_TL_raw << endl;
    //cout << "F11pl2 TL raw===" << F11PLA2_TL_raw << endl;
    //cout << "F11long TL raw===" << F11LONG_TL_raw << endl;
    //cout << "F11veto TL raw===" << F11VETO_TL_raw << endl;

    tree->Fill();
    neve++;
  }
  cout<<"Writing the tree."<<endl;
  
  //fout->cd();
  //tree->Write();
  fout->Write();
  fout->Close();
}
