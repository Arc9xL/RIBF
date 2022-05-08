#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtDALIParameters.hh"
#include "TArtCalibDALI.hh"
#include "TArtDALINaI.hh"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH2I.h"
#include "TH2D.h"
#include "TClonesArray.h"
#include "TArtCalibCoin.hh"
#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtBigRIPSParameters.hh"
#include "TArtPlastic.hh"
#include "TArtPPAC.hh"
#include "TArtRecoPID.hh"
#include "TArtRecoRIPS.hh"
#include "TArtRecoTOF.hh"
#include "TArtRecoBeam.hh"
#include "TArtCalibPID.hh"
#include "TArtBeam.hh"
#include "TArtTOF.hh"
#include "TVector3.h"
#include "TArtFocalPlane.hh"
#include "TArtCalibFocalPlane.hh"
#include "TVectorD.h"

ClassImp(TArtCalibCoin);

#include <fstream>
#include <iostream>

#include "signal.h"

using namespace std;

// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void stop_interrupt() {
  printf("keyboard interrupt\n");
  stoploop = true;
}

//int main(int argc, char** argv)
void MakeDALITreeShort(char *infile, char *outfile="run001.root", int events=10e7)  {
  
  gSystem->Load("libXMLParser.so");
  gSystem->Load("libanaroot.so");

  //char* infile;
  //infile = argv[1];

  TArtStoreManager * sman = TArtStoreManager::Instance();
  TArtEventStore *estore = new TArtEventStore();

  estore->SetInterrupt(&stoploop);
  estore->Open(infile);

  TFile *fout = new TFile(outfile,"RECREATE");
  TTree *tree = new TTree("tree","tree");

  // TOF --------------------------------------------------------------------------------------------------------------------------
  // Necessary to get the TOF from F7 to F8
  // Create RecoPID to get calibrated data and to reconstruct TOF, AoQ, Z, ... (RecoPID -> 
  //[ RecoTOF , RecoRIPS , RecoBeam] )
  TArtBigRIPSParameters *para = TArtBigRIPSParameters::Instance();
  para->LoadParameter("db/BigRIPSPlastic.xml");
  para->LoadParameter("db/FocalPlane.xml");
  para->SetFocusPosOffset(8,138.5);

  TArtRecoPID *recopid = new TArtRecoPID();

  TArtCalibPID *brcalib  = new TArtCalibPID();
  TArtCalibPlastic *plasticcalib = brcalib->GetCalibPlastic();
  TArtTOF *tof7to8  = recopid->DefineNewTOF("F7pl","F8pl"); // F7 - F8

  // DALI --------------------------------------------------------------------------------------------------------------------------
  TArtDALIParameters *dpara = TArtDALIParameters::Instance();
  dpara->LoadParameter("db/DALI.xml");
  TArtCalibDALI *dalicalib = new TArtCalibDALI();

  Int_t id[186];
  
  Int_t rawEnergy[186];
  Int_t rawTime[186];

  Float_t calEnergy[186];
  Float_t calTime[186];

  Int_t dalimultwithoutt = 0;
  Int_t dalimult = 0;
  Int_t dalitimetruemult = 0;
  Int_t dalimultthres = 0;
  Int_t dalitimetruemultthres = 0;

  Float_t tof;

  tree->Branch("id[186]",id);

  tree->Branch("rawEnergy[186]",rawEnergy);
  tree->Branch("rawTime[186]",rawTime);
  
  tree->Branch("calEnergy[186]",calEnergy);
  tree->Branch("calTime[186]",calTime);

  tree->Branch("dalimultwithoutt",&dalimultwithoutt,"dalimultwithoutt/I");
  tree->Branch("dalimult",&dalimult,"dalimult/I");
  tree->Branch("dalitimetruemult",&dalitimetruemult,"dalitimetruemult/I");
  tree->Branch("dalimultthres",&dalimultthres,"dalimultthres/I");
  tree->Branch("dalitimetruemultthres",&dalitimetruemultthres,"dalitimetruemultthres/I");

  tree->Branch("tof",&tof);

  TH2I *h_dali_raw_energy_id  = new TH2I("Raw_Energy_id","Energy vs ID",187,0,186,4096,0,4095);
  TH2I *h_dali_raw_time_id  = new TH2I("Raw_Time_id","Time vs ID",187,0,186,4000,-2000,2000);

  TH2F *h_dali_cal_energy_id  = new TH2F("Cal_Energy_id","Cal Energy vs ID",187,0,186,1000,0,10000);
  TH2F *h_dali_cal_time_id  = new TH2F("Cal_Time_id","Cal Time vs ID",187,0,186,4000,-2000,2000);

  int neve = 0;
  Int_t NumDALI;//, firstCrystal = 0.;
  
  for(Int_t j=0;j<186;j++) {
    id = j+1;
  }

  while(estore->GetNextEvent() &&neve < events ){
    if(neve%1000==0){
      std::cout << "Event: " << neve <<", "<< (100.*neve/events) <<"% of events done\r" <<std::flush;
      // fflush(stdin);
    }

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //Making the BigRIPS tree calibration
    brcalib->ClearData();
    brcalib->ReconstructData();
    
    //Reconstructiong the PID
    recopid->ClearData();
    recopid->ReconstructData();

    tof = tof7to8->GetTOF();

    dalicalib->ClearData();
    dalicalib->ReconstructData();
    
    neve++;
    
    NumDALI = dalicalib->GetNumNaI(); // Get number of crystals hit by radiation

    // Zero everything:
    for(Int_t j=0;j<186;j++) {
      rawEnergy[j] = -999.0;
      rawTime[j] = -9999.0;
      
      calEnergy[j] = -999.0;
      calTime[j] = -9999.0;
    }

    for(Int_t j=0;j<NumDALI;j++) { // Loop over this number to fill the energy vectors
      
      TArtDALINaI *nai = (TArtDALINaI*)dalicalib->GetNaI(j);
      
      if(nai->GetID()!=187&&nai->GetID()!=188) {
        
        //Raw Energy
        rawEnergy[(int)nai->GetID()-1] = (int)nai->GetRawADC();
        h_dali_raw_energy_id->Fill((int)nai->GetID()-1,rawEnergy[(int)nai->GetID()-1]);
        
        //Raw Time
        rawTime[(int)nai->GetID()-1] = (int)nai->GetRawTDC();
        h_dali_raw_time_id->Fill((int)nai->GetID()-1,rawTime[(int)nai->GetID()-1]);
        
        //Calibrated Energy
        calEnergy[(int)nai->GetID()-1] = (float)nai->GetEnergy();
        h_dali_cal_energy_id->Fill((int)nai->GetID()-1,calEnergy[(int)nai->GetID()-1]);
        
        //Calibrated Time
        calTime[(int)nai->GetID()-1] = (float)nai->GetTimeOffseted();
        h_dali_cal_time_id->Fill((int)nai->GetID()-1,calTime[(int)nai->GetID()-1]);

      }
    }

    //----------------------------------------------------------------------------------------------------------------------------
      
    dalimultwithoutt = dalicalib->GetMultWithoutT();
    dalimult = dalicalib->GetMult();
    dalitimetruemult = dalicalib->GetTimeTrueMult();
    dalimultthres = dalicalib->GetMultThres();
    dalitimetruemultthres = dalicalib->GetTimeTrueMultThres();

    tree->Fill();
  }
  
  fout->Write();
  fout->Close();
  
  cout <<std::endl;
  //return 0;
}
