//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////
#ifndef RIBF132CalibOut_h
#define RIBF132CalibOut_h
#include <TFile.h>
#include <TTree.h>

class RIBF132CalibOut{
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
 
    RIBF132CalibOut(TTree *tree=0);
    virtual ~RIBF132CalibOut();
    virtual void     Clear();
    virtual void     Init();
    virtual void     Fill();

    //----Declaration of leaf types-----
    Double_t        test_cal_var;
    Int_t           test_cal_numhit[7][4];
  
    Int_t ievent;
  
    //------PPAC------------
    Double_t PPACTSumX[7][4];
    Double_t PPACTDiffX[7][4];
    Double_t PPACTSumY[7][4];
    Double_t PPACTDiffY[7][4];
    Double_t PPACX[7][4];
    Double_t PPACY[7][4];
    Bool_t   PPACFiredX[7][4];
    Bool_t   PPACFiredY[7][4];
    //
    Double_t PPACX_online[7][4];
    Double_t PPACY_online[7][4];
    Int_t    PPACTX1_NumHit[7][4];
    Int_t    PPACTX2_NumHit[7][4];
    Int_t    PPACTY1_NumHit[7][4];
    Int_t    PPACTY2_NumHit[7][4];
    Int_t    PPACTA_NumHit[7][4];
    Double_t PPACXZpos[7][4];
    Double_t PPACYZpos[7][4];
    //--------------------------
  
    //-----------------------
    //  PPAC HV trip data (27Sep2017)
    Bool_t bF3PPACHVX;
    Bool_t bF3PPACHVY;
    Bool_t bF5PPACHVX;
    Bool_t bF5PPACHVY;
    Bool_t bF7PPACHVX;
    Bool_t bF7PPACHVY;
    Bool_t bF8PPACHVX;
    Bool_t bF8PPACHVY;
    Bool_t bF9PPACHVX;
    Bool_t bF9PPACHVY;
    Bool_t bF11PPACHVX;
    Bool_t bF11PPACHVY;
    Bool_t bF8PPAC1HVX;
    Bool_t bF8PPAC1HVY;
    Bool_t bF57911PPACHVX;
    Bool_t bF57911PPACHVY;
    Bool_t bF57911PPACHV;
    //--------------------------

  
    //---- Track (position+angle) -----
    Double_t X3, X5, X7, X8, X9, X11;
    Double_t Y3, Y5, Y7, Y8, Y9, Y11;
    Double_t A3, A5, A7, A8, A9, A11;
    Double_t B3, B5, B7, B8, B9, B11;
    Double_t X3_online, X5_online, X7_online, X8_online, X9_online, X11_online;
    Double_t Y3_online, Y5_online, Y7_online, Y8_online, Y9_online, Y11_online;
    Double_t A3_online, A5_online, A7_online, A8_online, A9_online, A11_online;
    Double_t B3_online, B5_online, B7_online, B8_online, B9_online, B11_online;
    Bool_t F3TrackedX, F5TrackedX, F7TrackedX, F8TrackedX, F9TrackedX, F11TrackedX;
    Bool_t F3TrackedY, F5TrackedY, F7TrackedY, F8TrackedY, F9TrackedY, F11TrackedY;
    Double_t F3SSRX, F5SSRX, F7SSRX, F8SSRX, F9SSRX, F11SSRX;
    Double_t F3SSRY, F5SSRY, F7SSRY, F8SSRY, F9SSRY, F11SSRY;
    Int_t  F3NumFiredPPACX, F5NumFiredPPACX, F7NumFiredPPACX, F8NumFiredPPACX, F9NumFiredPPACX, F11NumFiredPPACX;
    Int_t  F3NumFiredPPACY, F5NumFiredPPACY, F7NumFiredPPACY, F8NumFiredPPACY, F9NumFiredPPACY, F11NumFiredPPACY;
    Double_t PPACResX[7][4];
    Double_t PPACResY[7][4];
    //
    Double_t X3PPAC1, X3PPAC2, Y3PPAC1, Y3PPAC2;//
    Double_t X5PPAC1, X5PPAC2, Y5PPAC1, Y5PPAC2;//
    Double_t X7PPAC1, X7PPAC2, Y7PPAC1, Y7PPAC2;//
    Double_t X8PPAC1, X8PPAC2, Y8PPAC1, Y8PPAC2;//
    Double_t X9PPAC1, X9PPAC2, Y9PPAC1, Y9PPAC2;//
    Double_t X11PPAC1,X11PPAC2,Y11PPAC1,Y11PPAC2;//

    //-------Plastic------
    Double_t        F3PLA_TL_raw;
    Double_t        F3PLA_TR_raw;
    Double_t        F3PLA_TL_raw_s; // tdc range selection
    Double_t        F3PLA_TR_raw_s; // tdc range selection
    Double_t        F3PLA_TL_ns;
    Double_t        F3PLA_TR_ns;
    Double_t        F3PLA_TL;
    Double_t        F3PLA_TR;
    Double_t        F3PLA_T;
    Int_t           F3PLA_TL_NumHit;
    Int_t           F3PLA_TR_NumHit;
    Double_t        F3PLA_QL_raw;
    Double_t        F3PLA_QR_raw;
    Double_t        F3PLA_QL;
    Double_t        F3PLA_QR;
    Double_t        F3PLA_Q;
//
  Double_t        F5PLA_TL_raw;
  Double_t        F5PLA_TR_raw;
  Double_t        F5PLA_TL_raw_s; // tdc range selection
  Double_t        F5PLA_TR_raw_s; // tdc range selection
  Double_t        F5PLA_TL_ns;
  Double_t        F5PLA_TR_ns;
  Double_t        F5PLA_TL;
  Double_t        F5PLA_TR;
  Double_t        F5PLA_T;
  Int_t           F5PLA_TL_NumHit;
  Int_t           F5PLA_TR_NumHit;
  Double_t        F5PLA_QL_raw;
  Double_t        F5PLA_QR_raw;
  Double_t        F5PLA_QL;
  Double_t        F5PLA_QR;
  Double_t        F5PLA_Q;
  //
  Double_t        F7PLA_TL_raw;
  Double_t        F7PLA_TR_raw;
  Double_t        F7PLA_TL_raw_s; // tdc range selection
  Double_t        F7PLA_TR_raw_s; // tdc range selection
  Double_t        F7PLA_TL_ns;
  Double_t        F7PLA_TR_ns;
  Double_t        F7PLA_TL;
  Double_t        F7PLA_TR;
  Double_t        F7PLA_T;
  Int_t           F7PLA_TL_NumHit;
  Int_t           F7PLA_TR_NumHit;
  Double_t        F7PLA_QL_raw;
  Double_t        F7PLA_QR_raw;
  Double_t        F7PLA_QL;
  Double_t        F7PLA_QR;
  Double_t        F7PLA_Q;
  //
  Double_t        F8PLA_TL_raw;
  Double_t        F8PLA_TR_raw;
  Double_t        F8PLA_TL_raw_s; // tdc range selection
  Double_t        F8PLA_TR_raw_s; // tdc range selection
  Double_t        F8PLA_TL_ns;
  Double_t        F8PLA_TR_ns;
  Double_t        F8PLA_TL;
  Double_t        F8PLA_TR;
  Double_t        F8PLA_T;
  Int_t           F8PLA_TL_NumHit;
  Int_t           F8PLA_TR_NumHit;
  Double_t        F8PLA_QL_raw;
  Double_t        F8PLA_QR_raw;
  Double_t        F8PLA_QL;
  Double_t        F8PLA_QR;
  Double_t        F8PLA_Q;
  //
  Double_t        F11PLA_TL_raw;
  Double_t        F11PLA_TR_raw;
  Double_t        F11PLA_TL_raw_s; // tdc range selection
  Double_t        F11PLA_TR_raw_s; // tdc range selection
  Double_t        F11PLA_TL_ns;
  Double_t        F11PLA_TR_ns;
  Double_t        F11PLA_TL;
  Double_t        F11PLA_TR;
  Double_t        F11PLA_T;
  Int_t           F11PLA_TL_NumHit;
  Int_t           F11PLA_TR_NumHit;
  Double_t        F11PLA_QL_raw;
  Double_t        F11PLA_QR_raw;
  Double_t        F11PLA_QL;
  Double_t        F11PLA_QR;
  Double_t        F11PLA_Q;
  //
  Double_t        F11LONG_TL_raw;
  Double_t        F11LONG_TR_raw;
  Double_t        F11LONG_TL_raw_s; // tdc range selection
  Double_t        F11LONG_TR_raw_s; // tdc range selection
  Double_t        F11LONG_TL_ns;
  Double_t        F11LONG_TR_ns;
  Double_t        F11LONG_TL;
  Double_t        F11LONG_TR;
  Double_t        F11LONG_T;
  Int_t           F11LONG_TL_NumHit;
  Int_t           F11LONG_TR_NumHit;
  Double_t        F11LONG_QL_raw;
  Double_t        F11LONG_QR_raw;
  Double_t        F11LONG_QL;
  Double_t        F11LONG_QR;
  Double_t        F11LONG_Q;
  //
  Double_t        F11VETO_TL_raw;
  Double_t        F11VETO_TR_raw;
  Double_t        F11VETO_TL_raw_s; // tdc range selection
  Double_t        F11VETO_TR_raw_s; // tdc range selection
  Double_t        F11VETO_TL_ns;
  Double_t        F11VETO_TR_ns;
  Double_t        F11VETO_TL;
  Double_t        F11VETO_TR;
  Double_t        F11VETO_T;
  Int_t           F11VETO_TL_NumHit;
  Int_t           F11VETO_TR_NumHit;
  Double_t        F11VETO_QL_raw;
  Double_t        F11VETO_QR_raw;
  Double_t        F11VETO_QL;
  Double_t        F11VETO_QR;
  Double_t        F11VETO_Q;
  
  //-----IC-----
  Double_t        F7ICADCraw[6];
  Double_t        F7ICADCcal[6];
  Double_t        F7ICEnergySqSum_online;
  Double_t        F7ICEnergyAvSum_online;
  Double_t        F7ICEnergySqSum_offline;
  Double_t        F7ICEnergyAvSum_offline;

  Double_t        F11IC1ADCraw[8];   
  Double_t        F11IC1ADCcal[8];
  Double_t        F11IC1EnergySqSum_online;
  Double_t        F11IC1EnergyAvSum_online;
  Double_t        F11IC1EnergySqSum_offline;
  Double_t        F11IC1EnergyAvSum_offline;

  Double_t        F11IC2ADCraw[8];
  Double_t        F11IC2ADCcal[8];
  Double_t        F11IC2EnergySqSum_online;
  Double_t        F11IC2EnergyAvSum_online;
  Double_t        F11IC2EnergySqSum_offline;
  Double_t        F11IC2EnergyAvSum_offline;
  
  Double_t        F11IC1Yanode[8];
  Double_t        F11IC2Yanode[8];
  Double_t        F11YIC1;
  Double_t        F11BIC1;
  Double_t        F11YIC2;
  Double_t        F11BIC2;

  //----------------------------------------------
  Double_t        dipolebrho[8];
  
  Double_t        tof37;
  Double_t        tof811;
  Double_t        beta37;
  Double_t        beta811;
  Double_t        beta35_dipoleratio;
  Double_t        beta57_dipoleratio;
///  Double_t        beta89_dipoleratio;
///  Double_t        beta911_dipoleratio;
  Double_t        delta35;
  Double_t        delta57;
  Double_t        delta911;
  
  Double_t        zet7;
  Double_t        zet11;
  Double_t        aoq57;
  Double_t        aoq911;

  Bool_t btof37;
  Bool_t btof811;
  Bool_t bdelta35;
  Bool_t bdelta57;
  Bool_t bdelta911;
  Bool_t bzet7;
  Bool_t bzet11;
  Bool_t baoq57;
  Bool_t baoq911;

  Bool_t btof78;
  Double_t        tof78;
  Double_t        beta78;
  
  
  Double_t delta35_1110;
  Double_t delta35_1101;
  Double_t delta35_1011;
  Double_t delta35_0111;
  Double_t delta35_ext;
  Double_t delta57_1110;
  Double_t delta57_1101;
  Double_t delta57_1011;
  Double_t delta57_0111;
  Double_t delta57_ext;
  Double_t delta911_1110;
  Double_t delta911_1101;
  Double_t delta911_1011;
  Double_t delta911_0111;
  Double_t delta911_ext;

  Bool_t  bdelta35_1110;
  Bool_t  bdelta35_1101;
  Bool_t  bdelta35_1011;
  Bool_t  bdelta35_0111;
  Bool_t  bdelta35_3plane;
  Bool_t  bdelta35_ext;
  Bool_t  bdelta57_1110;
  Bool_t  bdelta57_1101;
  Bool_t  bdelta57_1011;
  Bool_t  bdelta57_0111;
  Bool_t  bdelta57_3plane;
  Bool_t  bdelta57_ext;
  Bool_t  bdelta911_1110;
  Bool_t  bdelta911_1101;
  Bool_t  bdelta911_1011;
  Bool_t  bdelta911_0111;
  Bool_t  bdelta911_3plane;
  Bool_t  bdelta911_ext;

  Double_t aoq57_1110;
  Double_t aoq57_1101;
  Double_t aoq57_1011;
  Double_t aoq57_0111;
  Double_t aoq57_ext;
  Double_t aoq911_1110;
  Double_t aoq911_1101;
  Double_t aoq911_1011;
  Double_t aoq911_0111;
  Double_t aoq911_ext;

  Bool_t  baoq57_1110;
  Bool_t  baoq57_1101;
  Bool_t  baoq57_1011;
  Bool_t  baoq57_0111;
  Bool_t  baoq57_3plane;
  Bool_t  baoq57_ext;
  Bool_t  baoq911_1110;
  Bool_t  baoq911_1101;
  Bool_t  baoq911_1011;
  Bool_t  baoq911_0111;
  Bool_t  baoq911_3plane;
  Bool_t  baoq911_ext;


  // online reconstructed information, pid infomartion
  Double_t        tof_online[3];
  Double_t        beta_online[3];
  Double_t        zet_online[6];
  Double_t        aoq_online[6];
  Double_t        delta_online[4];

  //-----DALI info when ADC exsit -----//
  Int_t     DALINum_A;
  Double_t  DALIADC_A[10]; // raw adc
  Double_t  DALIE_A[10]; // energy in keV << adc
  Double_t  DALIT_A[10]; //
  Int_t     DALIID_A[10];
  
  //-----DALI info when ADC-TDC exsit -----//
  Int_t     DALINum_AT;
  Double_t  DALIADC_AT[10]; // raw adc
  Double_t  DALIE_AT[10]; // energy in keV << adc
  Int_t     DALIID_AT[10];
  Double_t  DALITheta_AT[10];
  Double_t  DALIX_AT[10];
  Double_t  DALIY_AT[10];
  Double_t  DALIZ_AT[10];
  Double_t  DALIT_AT[10]; // (TDC - T0) in ns
  Double_t  DALIEdop78_AT[10];
  
  //-----DALI info when ADC-TDC exsit X F7F8 particle exist X Timing OK -----//
  Int_t     DALINum;
  Double_t  DALIADC[10]; // raw adc
  Double_t  DALIE[10]; // energy in keV << adc
  Double_t  DALIEdop78[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdop811[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdopave[10]; //calculation possible only when F7F8 particle exists.
  Int_t     DALIID[10];
  Double_t  DALITheta[10];
  Double_t  DALIX[10];
  Double_t  DALIY[10];
  Double_t  DALIZ[10];
  Double_t  DALIT[10]; // (TDC - T0) in ns

  //-----DALI info when ADC-TDC exsit X F7F8 particle exist X Timing OK narrow gate-----//
  Int_t     DALINum_n;
  Double_t  DALIADC_n[10]; // raw adc
  Double_t  DALIE_n[10]; // energy in keV << adc
  Double_t  DALIEdop78_n[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdop811_n[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdopave_n[10]; //calculation possible only when F7F8 particle exists.
  Int_t     DALIID_n[10];
  Double_t  DALITheta_n[10];
  Double_t  DALIX_n[10];
  Double_t  DALIY_n[10];
  Double_t  DALIZ_n[10];
  Double_t  DALIT_n[10]; // (TDC - T0) in ns
  
  //-----DALI info for addback-----//
  Int_t     DALINum_addback;
//  Double_t  DALIADC_addback[10]; // raw adc
  Double_t  DALIE_addback[10]; // energy in keV << adc
  Double_t  DALIEdop78_addback[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdop811_addback[10]; //calculation possible only when F7F8 particle exists.
  Double_t  DALIEdopave_addback[10]; //calculation possible only when F7F8 particle exists.
  Int_t     DALIID_addback[10];
  Double_t  DALITheta_addback[10];
  Double_t  DALIX_addback[10];
  Double_t  DALIY_addback[10];
  Double_t  DALIZ_addback[10];
  Double_t  DALIT_addback[10]; // (TDC - T0) in ns
  Int_t     DALIN_addback[10]; //
};
#endif

#ifdef RIBF132Calib_cxx
void RIBF132CalibOut::Init()
{
  // Set branch
  fChain->Branch("ievent", &ievent, "ievent/I");
  
  fChain->Branch("test_cal_var", &test_cal_var, "test_cal_var/D");
  fChain->Branch("test_cal_numhit", test_cal_numhit, "test_cal_numhit[7][4]/I");
  fChain->Branch("PPACTSumX", PPACTSumX, "PPACTSumX[7][4]/D");
  fChain->Branch("PPACTDiffX", PPACTDiffX, "PPACTDiffX[7][4]/D");
  fChain->Branch("PPACTSumY", PPACTSumY, "PPACTSumY[7][4]/D");
  fChain->Branch("PPACTDiffY", PPACTDiffY, "PPACTDiffY[7][4]/D");
  fChain->Branch("PPACX", PPACX, "PPACX[7][4]/D");
  fChain->Branch("PPACY", PPACY, "PPACY[7][4]/D");
  fChain->Branch("PPACFiredX", PPACFiredX, "PPACFiredX[7][4]/O");
  fChain->Branch("PPACFiredY", PPACFiredY, "PPACFiredY[7][4]/O");
  fChain->Branch("PPACX_online", PPACX_online, "PPACX_online[7][4]/D");
  fChain->Branch("PPACY_online", PPACY_online, "PPACY_online[7][4]/D");
  fChain->Branch("PPACTX1_NumHit", PPACTX1_NumHit, "PPACTX1_NumHit[7][4]/I");
  fChain->Branch("PPACTX2_NumHit", PPACTX2_NumHit, "PPACTX2_NumHit[7][4]/I");
  fChain->Branch("PPACTY1_NumHit", PPACTY1_NumHit, "PPACTY1_NumHit[7][4]/I");
  fChain->Branch("PPACTY2_NumHit", PPACTY2_NumHit, "PPACTY2_NumHit[7][4]/I");
  fChain->Branch("PPACTA_NumHit", PPACTA_NumHit, "PPACTA_NumHit[7][4]/I");
  fChain->Branch("PPACXZpos", PPACXZpos, "PPACXZpos[7][4]/D");
  fChain->Branch("PPACYZpos", PPACYZpos, "PPACYZpos[7][4]/D");
  //
  fChain->Branch("X3", &X3, "X3/D");
  fChain->Branch("X5", &X5, "X5/D");
  fChain->Branch("X7", &X7, "X7/D");
  fChain->Branch("X8", &X8, "X8/D");
  fChain->Branch("X9", &X9, "X9/D");
  fChain->Branch("X11",&X11,"X11/D");
  fChain->Branch("A3", &A3, "A3/D");
  fChain->Branch("A5", &A5, "A5/D");
  fChain->Branch("A7", &A7, "A7/D");
  fChain->Branch("A8", &A8, "A8/D");
  fChain->Branch("A9", &A9, "A9/D");
  fChain->Branch("A11",&A11,"A11/D");
  fChain->Branch("Y3", &Y3, "Y3/D");
  fChain->Branch("Y5", &Y5, "Y5/D");
  fChain->Branch("Y7", &Y7, "Y7/D");
  fChain->Branch("Y8", &Y8, "Y8/D");
  fChain->Branch("Y9", &Y9, "Y9/D");
  fChain->Branch("Y11",&Y11,"Y11/D");
  fChain->Branch("B3", &B3, "B3/D");
  fChain->Branch("B5", &B5, "B5/D");
  fChain->Branch("B7", &B7, "B7/D");
  fChain->Branch("B8", &B8, "B8/D");
  fChain->Branch("B9", &B9, "B9/D");
  fChain->Branch("B11",&B11,"B11/D");
  fChain->Branch("F3TrackedX",  &F3TrackedX,  "F3TrackedX/O");
  fChain->Branch("F3TrackedY",  &F3TrackedY,  "F3TrackedY/O");
  fChain->Branch("F5TrackedX",  &F5TrackedX,  "F5TrackedX/O");
  fChain->Branch("F5TrackedY",  &F5TrackedY,  "F5TrackedY/O");
  fChain->Branch("F7TrackedX",  &F7TrackedX,  "F7TrackedX/O");
  fChain->Branch("F7TrackedY",  &F7TrackedY,  "F7TrackedY/O");
  fChain->Branch("F8TrackedX",  &F8TrackedX,  "F8TrackedX/O");
  fChain->Branch("F8TrackedY",  &F8TrackedY,  "F8TrackedY/O");
  fChain->Branch("F9TrackedX",  &F9TrackedX,  "F9TrackedX/O");
  fChain->Branch("F9TrackedY",  &F9TrackedY,  "F9TrackedY/O");
  fChain->Branch("F11TrackedX", &F11TrackedX, "F11TrackedX/O");
  fChain->Branch("F11TrackedY", &F11TrackedY, "F11TrackedY/O");
  fChain->Branch("F3SSRX",  &F3SSRX,  "F3SSRX/D");
  fChain->Branch("F3SSRY",  &F3SSRY,  "F3SSRY/D");
  fChain->Branch("F5SSRX",  &F5SSRX,  "F5SSRX/D");
  fChain->Branch("F5SSRY",  &F5SSRY,  "F5SSRY/D");
  fChain->Branch("F7SSRX",  &F7SSRX,  "F7SSRX/D");
  fChain->Branch("F7SSRY",  &F7SSRY,  "F7SSRY/D");
  fChain->Branch("F8SSRX",  &F8SSRX,  "F8SSRX/D");
  fChain->Branch("F8SSRY",  &F8SSRY,  "F8SSRY/D");
  fChain->Branch("F9SSRX",  &F9SSRX,  "F9SSRX/D");
  fChain->Branch("F9SSRY",  &F9SSRY,  "F9SSRY/D");
  fChain->Branch("F11SSRX", &F11SSRX, "F11SSRX/D");
  fChain->Branch("F11SSRY", &F11SSRY, "F11SSRY/D");
  fChain->Branch("F3NumFiredPPACX",  &F3NumFiredPPACX,  "F3NumFiredPPACX/I");
  fChain->Branch("F3NumFiredPPACY",  &F3NumFiredPPACY,  "F3NumFiredPPACY/I");
  fChain->Branch("F5NumFiredPPACX",  &F5NumFiredPPACX,  "F5NumFiredPPACX/I");
  fChain->Branch("F5NumFiredPPACY",  &F5NumFiredPPACY,  "F5NumFiredPPACY/I");
  fChain->Branch("F7NumFiredPPACX",  &F7NumFiredPPACX,  "F7NumFiredPPACX/I");
  fChain->Branch("F7NumFiredPPACY",  &F7NumFiredPPACY,  "F7NumFiredPPACY/I");
  fChain->Branch("F8NumFiredPPACX",  &F8NumFiredPPACX,  "F8NumFiredPPACX/I");
  fChain->Branch("F8NumFiredPPACY",  &F8NumFiredPPACY,  "F8NumFiredPPACY/I");
  fChain->Branch("F9NumFiredPPACX",  &F9NumFiredPPACX,  "F9NumFiredPPACX/I");
  fChain->Branch("F9NumFiredPPACY",  &F9NumFiredPPACY,  "F9NumFiredPPACY/I");
  fChain->Branch("F11NumFiredPPACX", &F11NumFiredPPACX, "F11NumFiredPPACX/I");
  fChain->Branch("F11NumFiredPPACY", &F11NumFiredPPACY, "F11NumFiredPPACY/I");
  //
  fChain->Branch("PPACResX", PPACResX, "PPACResX[7][4]/D");
  fChain->Branch("PPACResY", PPACResY, "PPACResY[7][4]/D");

  //
  fChain->Branch("X3PPAC1", &X3PPAC1, "X3PPAC1/D");
  fChain->Branch("X3PPAC2", &X3PPAC2, "X3PPAC2/D");
  fChain->Branch("Y3PPAC1", &Y3PPAC1, "Y3PPAC1/D");
  fChain->Branch("Y3PPAC2", &Y3PPAC2, "Y3PPAC2/D");
  
  fChain->Branch("X5PPAC1", &X5PPAC1, "X5PPAC1/D");
  fChain->Branch("X5PPAC2", &X5PPAC2, "X5PPAC2/D");
  fChain->Branch("Y5PPAC1", &Y5PPAC1, "Y5PPAC1/D");
  fChain->Branch("Y5PPAC2", &Y5PPAC2, "Y5PPAC2/D");
  
  fChain->Branch("X7PPAC1", &X7PPAC1, "X7PPAC1/D");
  fChain->Branch("X7PPAC2", &X7PPAC2, "X7PPAC2/D");
  fChain->Branch("Y7PPAC1", &Y7PPAC1, "Y7PPAC1/D");
  fChain->Branch("Y7PPAC2", &Y7PPAC2, "Y7PPAC2/D");
  
  fChain->Branch("X8PPAC1", &X8PPAC1, "X8PPAC1/D");
  fChain->Branch("X8PPAC2", &X8PPAC2, "X8PPAC2/D");
  fChain->Branch("Y8PPAC1", &Y8PPAC1, "Y8PPAC1/D");
  fChain->Branch("Y8PPAC2", &Y8PPAC2, "Y8PPAC2/D");
  
  fChain->Branch("X9PPAC1", &X9PPAC1, "X9PPAC1/D");
  fChain->Branch("X9PPAC2", &X9PPAC2, "X9PPAC2/D");
  fChain->Branch("Y9PPAC1", &Y9PPAC1, "Y9PPAC1/D");
  fChain->Branch("Y9PPAC2", &Y9PPAC2, "Y9PPAC2/D");
  
  fChain->Branch("X11PPAC1", &X11PPAC1, "X11PPAC1/D");
  fChain->Branch("X11PPAC2", &X11PPAC2, "X11PPAC2/D");
  fChain->Branch("Y11PPAC1", &Y11PPAC1, "Y11PPAC1/D");
  fChain->Branch("Y11PPAC2", &Y11PPAC2, "Y11PPAC2/D");
  
  //
  // PPAC HV trip flag
  fChain->Branch("bF3PPACHVX", &bF3PPACHVX, "bF3PPACHVX/O");
  fChain->Branch("bF3PPACHVY", &bF3PPACHVY, "bF3PPACHVY/O");
  fChain->Branch("bF5PPACHVX", &bF5PPACHVX, "bF5PPACHVX/O");
  fChain->Branch("bF5PPACHVY", &bF5PPACHVY, "bF5PPACHVY/O");
  fChain->Branch("bF7PPACHVX", &bF7PPACHVX, "bF7PPACHVX/O");
  fChain->Branch("bF7PPACHVY", &bF7PPACHVY, "bF7PPACHVY/O");
  fChain->Branch("bF8PPACHVX", &bF8PPACHVX, "bF8PPACHVX/O");
  fChain->Branch("bF8PPACHVY", &bF8PPACHVY, "bF8PPACHVY/O");
  fChain->Branch("bF9PPACHVX", &bF9PPACHVX, "bF9PPACHVX/O");
  fChain->Branch("bF9PPACHVY", &bF9PPACHVY, "bF9PPACHVY/O");
  fChain->Branch("bF11PPACHVX", &bF11PPACHVX, "bF11PPACHVX/O");
  fChain->Branch("bF11PPACHVY", &bF11PPACHVY, "bF11PPACHVY/O");
  fChain->Branch("bF8PPAC1HVX", &bF8PPAC1HVX, "bF8PPAC1HVX/O");
  fChain->Branch("bF8PPAC1HVY", &bF8PPAC1HVY, "bF8PPAC1HVY/O");
  fChain->Branch("bF57911PPACHVX", &bF57911PPACHVX, "bF57911PPACHVX/O");
  fChain->Branch("bF57911PPACHVY", &bF57911PPACHVY, "bF57911PPACHVY/O");
  fChain->Branch("bF57911PPACHV",  &bF57911PPACHV,  "bF57911PPACHV/O");
  
  //
  fChain->Branch("X3_online", &X3_online, "X3_online/D");
  fChain->Branch("X5_online", &X5_online, "X5_online/D");
  fChain->Branch("X7_online", &X7_online, "X7_online/D");
  fChain->Branch("X8_online", &X8_online, "X8_online/D");
  fChain->Branch("X9_online", &X9_online, "X9_online/D");
  fChain->Branch("X11_online",&X11_online,"X11_online/D");
  fChain->Branch("A3_online", &A3_online, "A3_online/D");
  fChain->Branch("A5_online", &A5_online, "A5_online/D");
  fChain->Branch("A7_online", &A7_online, "A7_online/D");
  fChain->Branch("A8_online", &A8_online, "A8_online/D");
  fChain->Branch("A9_online", &A9_online, "A9_online/D");
  fChain->Branch("A11_online",&A11_online,"A11_online/D");
  fChain->Branch("Y3_online", &Y3_online, "Y3_online/D");
  fChain->Branch("Y5_online", &Y5_online, "Y5_online/D");
  fChain->Branch("Y7_online", &Y7_online, "Y7_online/D");
  fChain->Branch("Y8_online", &Y8_online, "Y8_online/D");
  fChain->Branch("Y9_online", &Y9_online, "Y9_online/D");
  fChain->Branch("Y11_online",&Y11_online,"Y11_online/D");
  fChain->Branch("B3_online", &B3_online, "B3_online/D");
  fChain->Branch("B5_online", &B5_online, "B5_online/D");
  fChain->Branch("B7_online", &B7_online, "B7_online/D");
  fChain->Branch("B8_online", &B8_online, "B8_online/D");
  fChain->Branch("B9_online", &B9_online, "B9_online/D");
  fChain->Branch("B11_online",&B11_online,"B11_online/D");
  //
  fChain->Branch("F3PLA_TL_raw",   &F3PLA_TL_raw,   "F3PLA_TL_raw/D");
  fChain->Branch("F3PLA_TR_raw",   &F3PLA_TR_raw,   "F3PLA_TR_raw/D");
  fChain->Branch("F3PLA_TL_raw_s", &F3PLA_TL_raw_s, "F3PLA_TL_raw_s/D");
  fChain->Branch("F3PLA_TR_raw_s", &F3PLA_TR_raw_s, "F3PLA_TR_raw_s/D");
  fChain->Branch("F3PLA_TL_ns",    &F3PLA_TL_ns,    "F3PLA_TL_ns/D");
  fChain->Branch("F3PLA_TR_ns",    &F3PLA_TR_ns,    "F3PLA_TR_ns/D");
  fChain->Branch("F3PLA_TL",       &F3PLA_TL,       "F3PLA_TL/D");
  fChain->Branch("F3PLA_TR",       &F3PLA_TR,       "F3PLA_TR/D");
  fChain->Branch("F3PLA_T",        &F3PLA_T,        "F3PLA_T/D");
  fChain->Branch("F3PLA_TL_NumHit",&F3PLA_TL_NumHit,"F3PLA_TL_NumHit/I");
  fChain->Branch("F3PLA_TR_NumHit",&F3PLA_TR_NumHit,"F3PLA_TR_NumHit/I");
  fChain->Branch("F3PLA_QL_raw",   &F3PLA_QL_raw,   "F3PLA_QL_raw/D");
  fChain->Branch("F3PLA_QR_raw",   &F3PLA_QR_raw,   "F3PLA_QR_raw/D");
  fChain->Branch("F3PLA_QL",       &F3PLA_QL,       "F3PLA_QL/D");
  fChain->Branch("F3PLA_QR",       &F3PLA_QR,       "F3PLA_QR/D");
  fChain->Branch("F3PLA_Q",        &F3PLA_Q,        "F3PLA_Q/D");
  //
  fChain->Branch("F5PLA_TL_raw",   &F5PLA_TL_raw,   "F5PLA_TL_raw/D");
  fChain->Branch("F5PLA_TR_raw",   &F5PLA_TR_raw,   "F5PLA_TR_raw/D");
  fChain->Branch("F5PLA_TL_raw_s", &F5PLA_TL_raw_s, "F5PLA_TL_raw_s/D");
  fChain->Branch("F5PLA_TR_raw_s", &F5PLA_TR_raw_s, "F5PLA_TR_raw_s/D");
  fChain->Branch("F5PLA_TL_ns",    &F5PLA_TL_ns,    "F5PLA_TL_ns/D");
  fChain->Branch("F5PLA_TR_ns",    &F5PLA_TR_ns,    "F5PLA_TR_ns/D");
  fChain->Branch("F5PLA_TL",       &F5PLA_TL,       "F5PLA_TL/D");
  fChain->Branch("F5PLA_TR",       &F5PLA_TR,       "F5PLA_TR/D");
  fChain->Branch("F5PLA_T",        &F5PLA_T,        "F5PLA_T/D");
  fChain->Branch("F5PLA_TL_NumHit",&F5PLA_TL_NumHit,"F5PLA_TL_NumHit/I");
  fChain->Branch("F5PLA_TR_NumHit",&F5PLA_TR_NumHit,"F5PLA_TR_NumHit/I");
  fChain->Branch("F5PLA_QL_raw",   &F5PLA_QL_raw,   "F5PLA_QL_raw/D");
  fChain->Branch("F5PLA_QR_raw",   &F5PLA_QR_raw,   "F5PLA_QR_raw/D");
  fChain->Branch("F5PLA_QL",       &F5PLA_QL,       "F5PLA_QL/D");
  fChain->Branch("F5PLA_QR",       &F5PLA_QR,       "F5PLA_QR/D");
  fChain->Branch("F5PLA_Q",        &F5PLA_Q,        "F5PLA_Q/D");
  //
  fChain->Branch("F7PLA_TL_raw",   &F7PLA_TL_raw,   "F7PLA_TL_raw/D");
  fChain->Branch("F7PLA_TR_raw",   &F7PLA_TR_raw,   "F7PLA_TR_raw/D");
  fChain->Branch("F7PLA_TL_raw_s", &F7PLA_TL_raw_s, "F7PLA_TL_raw_s/D");
  fChain->Branch("F7PLA_TR_raw_s", &F7PLA_TR_raw_s, "F7PLA_TR_raw_s/D");
  fChain->Branch("F7PLA_TL_ns",    &F7PLA_TL_ns,    "F7PLA_TL_ns/D");
  fChain->Branch("F7PLA_TR_ns",    &F7PLA_TR_ns,    "F7PLA_TR_ns/D");
  fChain->Branch("F7PLA_TL",       &F7PLA_TL,       "F7PLA_TL/D");
  fChain->Branch("F7PLA_TR",       &F7PLA_TR,       "F7PLA_TR/D");
  fChain->Branch("F7PLA_T",        &F7PLA_T,        "F7PLA_T/D");
  fChain->Branch("F7PLA_TL_NumHit",&F7PLA_TL_NumHit,"F7PLA_TL_NumHit/I");
  fChain->Branch("F7PLA_TR_NumHit",&F7PLA_TR_NumHit,"F7PLA_TR_NumHit/I");
  fChain->Branch("F7PLA_QL_raw",   &F7PLA_QL_raw,   "F7PLA_QL_raw/D");
  fChain->Branch("F7PLA_QR_raw",   &F7PLA_QR_raw,   "F7PLA_QR_raw/D");
  fChain->Branch("F7PLA_QL",       &F7PLA_QL,       "F7PLA_QL/D");
  fChain->Branch("F7PLA_QR",       &F7PLA_QR,       "F7PLA_QR/D");
  fChain->Branch("F7PLA_Q",        &F7PLA_Q,        "F7PLA_Q/D");
  //
  fChain->Branch("F8PLA_TL_raw",   &F8PLA_TL_raw,   "F8PLA_TL_raw/D");
  fChain->Branch("F8PLA_TR_raw",   &F8PLA_TR_raw,   "F8PLA_TR_raw/D");
  fChain->Branch("F8PLA_TL_raw_s", &F8PLA_TL_raw_s, "F8PLA_TL_raw_s/D");
  fChain->Branch("F8PLA_TR_raw_s", &F8PLA_TR_raw_s, "F8PLA_TR_raw_s/D");
  fChain->Branch("F8PLA_TL_ns",    &F8PLA_TL_ns,    "F8PLA_TL_ns/D");
  fChain->Branch("F8PLA_TR_ns",    &F8PLA_TR_ns,    "F8PLA_TR_ns/D");
  fChain->Branch("F8PLA_TL",       &F8PLA_TL,       "F8PLA_TL/D");
  fChain->Branch("F8PLA_TR",       &F8PLA_TR,       "F8PLA_TR/D");
  fChain->Branch("F8PLA_T",        &F8PLA_T,        "F8PLA_T/D");
  fChain->Branch("F8PLA_TL_NumHit",&F8PLA_TL_NumHit,"F8PLA_TL_NumHit/I");
  fChain->Branch("F8PLA_TR_NumHit",&F8PLA_TR_NumHit,"F8PLA_TR_NumHit/I");
  fChain->Branch("F8PLA_QL_raw",   &F8PLA_QL_raw,   "F8PLA_QL_raw/D");
  fChain->Branch("F8PLA_QR_raw",   &F8PLA_QR_raw,   "F8PLA_QR_raw/D");
  fChain->Branch("F8PLA_QL",       &F8PLA_QL,       "F8PLA_QL/D");
  fChain->Branch("F8PLA_QR",       &F8PLA_QR,       "F8PLA_QR/D");
  fChain->Branch("F8PLA_Q",        &F8PLA_Q,        "F8PLA_Q/D");
  //
  fChain->Branch("F11PLA_TL_raw",   &F11PLA_TL_raw,   "F11PLA_TL_raw/D");
  fChain->Branch("F11PLA_TR_raw",   &F11PLA_TR_raw,   "F11PLA_TR_raw/D");
  fChain->Branch("F11PLA_TL_raw_s", &F11PLA_TL_raw_s, "F11PLA_TL_raw_s/D");
  fChain->Branch("F11PLA_TR_raw_s", &F11PLA_TR_raw_s, "F11PLA_TR_raw_s/D");
  fChain->Branch("F11PLA_TL_ns",    &F11PLA_TL_ns,    "F11PLA_TL_ns/D");
  fChain->Branch("F11PLA_TR_ns",    &F11PLA_TR_ns,    "F11PLA_TR_ns/D");
  fChain->Branch("F11PLA_TL",       &F11PLA_TL,       "F11PLA_TL/D");
  fChain->Branch("F11PLA_TR",       &F11PLA_TR,       "F11PLA_TR/D");
  fChain->Branch("F11PLA_T",        &F11PLA_T,        "F11PLA_T/D");
  fChain->Branch("F11PLA_TL_NumHit",&F11PLA_TL_NumHit,"F11PLA_TL_NumHit/I");
  fChain->Branch("F11PLA_TR_NumHit",&F11PLA_TR_NumHit,"F11PLA_TR_NumHit/I");
  fChain->Branch("F11PLA_QL_raw",   &F11PLA_QL_raw,   "F11PLA_QL_raw/D");
  fChain->Branch("F11PLA_QR_raw",   &F11PLA_QR_raw,   "F11PLA_QR_raw/D");
  fChain->Branch("F11PLA_QL",       &F11PLA_QL,       "F11PLA_QL/D");
  fChain->Branch("F11PLA_QR",       &F11PLA_QR,       "F11PLA_QR/D");
  fChain->Branch("F11PLA_Q",        &F11PLA_Q,        "F11PLA_Q/D");
  //
  fChain->Branch("F11LONG_TL_raw",   &F11LONG_TL_raw,   "F11LONG_TL_raw/D");
  fChain->Branch("F11LONG_TR_raw",   &F11LONG_TR_raw,   "F11LONG_TR_raw/D");
  fChain->Branch("F11LONG_TL_raw_s", &F11LONG_TL_raw_s, "F11LONG_TL_raw_s/D");
  fChain->Branch("F11LONG_TR_raw_s", &F11LONG_TR_raw_s, "F11LONG_TR_raw_s/D");
  fChain->Branch("F11LONG_TL_ns",    &F11LONG_TL_ns,    "F11LONG_TL_ns/D");
  fChain->Branch("F11LONG_TR_ns",    &F11LONG_TR_ns,    "F11LONG_TR_ns/D");
  fChain->Branch("F11LONG_TL",       &F11LONG_TL,       "F11LONG_TL/D");
  fChain->Branch("F11LONG_TR",       &F11LONG_TR,       "F11LONG_TR/D");
  fChain->Branch("F11LONG_T",        &F11LONG_T,        "F11LONG_T/D");
  fChain->Branch("F11LONG_TL_NumHit",&F11LONG_TL_NumHit,"F11LONG_TL_NumHit/I");
  fChain->Branch("F11LONG_TR_NumHit",&F11LONG_TR_NumHit,"F11LONG_TR_NumHit/I");
  fChain->Branch("F11LONG_QL_raw",   &F11LONG_QL_raw,   "F11LONG_QL_raw/D");
  fChain->Branch("F11LONG_QR_raw",   &F11LONG_QR_raw,   "F11LONG_QR_raw/D");
  fChain->Branch("F11LONG_QL",       &F11LONG_QL,       "F11LONG_QL/D");
  fChain->Branch("F11LONG_QR",       &F11LONG_QR,       "F11LONG_QR/D");
  fChain->Branch("F11LONG_Q",        &F11LONG_Q,        "F11LONG_Q/D");
  //
  fChain->Branch("F11VETO_TL_raw",   &F11VETO_TL_raw,   "F11VETO_TL_raw/D");
  fChain->Branch("F11VETO_TR_raw",   &F11VETO_TR_raw,   "F11VETO_TR_raw/D");
  fChain->Branch("F11VETO_TL_raw_s", &F11VETO_TL_raw_s, "F11VETO_TL_raw_s/D");
  fChain->Branch("F11VETO_TR_raw_s", &F11VETO_TR_raw_s, "F11VETO_TR_raw_s/D");
  fChain->Branch("F11VETO_TL_ns",    &F11VETO_TL_ns,    "F11VETO_TL_ns/D");
  fChain->Branch("F11VETO_TR_ns",    &F11VETO_TR_ns,    "F11VETO_TR_ns/D");
  fChain->Branch("F11VETO_TL",       &F11VETO_TL,       "F11VETO_TL/D");
  fChain->Branch("F11VETO_TR",       &F11VETO_TR,       "F11VETO_TR/D");
  fChain->Branch("F11VETO_T",        &F11VETO_T,        "F11VETO_T/D");
  fChain->Branch("F11VETO_TL_NumHit",&F11VETO_TL_NumHit,"F11VETO_TL_NumHit/I");
  fChain->Branch("F11VETO_TR_NumHit",&F11VETO_TR_NumHit,"F11VETO_TR_NumHit/I");
  fChain->Branch("F11VETO_QL_raw",   &F11VETO_QL_raw,   "F11VETO_QL_raw/D");
  fChain->Branch("F11VETO_QR_raw",   &F11VETO_QR_raw,   "F11VETO_QR_raw/D");
  fChain->Branch("F11VETO_QL",       &F11VETO_QL,       "F11VETO_QL/D");
  fChain->Branch("F11VETO_QR",       &F11VETO_QR,       "F11VETO_QR/D");
  fChain->Branch("F11VETO_Q",        &F11VETO_Q,        "F11VETO_Q/D");
  //
  fChain->Branch("F7ICADCraw",        F7ICADCraw,        "F7ICADCraw[6]/D");
  fChain->Branch("F7ICADCcal",        F7ICADCcal,        "F7ICADCcal[6]/D");
  fChain->Branch("F7ICEnergySqSum_online",        &F7ICEnergySqSum_online,        "F7ICEnergySqSum_online/D");
  fChain->Branch("F7ICEnergyAvSum_online",        &F7ICEnergyAvSum_online,        "F7ICEnergyAvSum_online/D");
  fChain->Branch("F7ICEnergySqSum_offline",       &F7ICEnergySqSum_offline,       "F7ICEnergySqSum_offline/D");
  fChain->Branch("F7ICEnergyAvSum_offline",       &F7ICEnergyAvSum_offline,       "F7ICEnergyAvSum_offline/D");
  //
  fChain->Branch("F11IC1ADCraw",        F11IC1ADCraw,        "F11IC1ADCraw[8]/D");
  fChain->Branch("F11IC1ADCcal",        F11IC1ADCcal,        "F11IC1ADCcal[8]/D");
  fChain->Branch("F11IC1EnergySqSum_online",        &F11IC1EnergySqSum_online,        "F11IC1EnergySqSum_online/D");
  fChain->Branch("F11IC1EnergyAvSum_online",        &F11IC1EnergyAvSum_online,        "F11IC1EnergyAvSum_online/D");
  fChain->Branch("F11IC1EnergySqSum_offline",       &F11IC1EnergySqSum_offline,       "F11IC1EnergySqSum_offline/D");
  fChain->Branch("F11IC1EnergyAvSum_offline",       &F11IC1EnergyAvSum_offline,       "F11IC1EnergyAvSum_offline/D");
  //
  fChain->Branch("F11IC2ADCraw",        F11IC2ADCraw,        "F11IC2ADCraw[8]/D");
  fChain->Branch("F11IC2ADCcal",        F11IC2ADCcal,        "F11IC2ADCcal[8]/D");
  fChain->Branch("F11IC2EnergySqSum_online",        &F11IC2EnergySqSum_online,        "F11IC2EnergySqSum_online/D");
  fChain->Branch("F11IC2EnergyAvSum_online",        &F11IC2EnergyAvSum_online,        "F11IC2EnergyAvSum_online/D");
  fChain->Branch("F11IC2EnergySqSum_offline",       &F11IC2EnergySqSum_offline,       "F11IC2EnergySqSum_offline/D");
  fChain->Branch("F11IC2EnergyAvSum_offline",       &F11IC2EnergyAvSum_offline,       "F11IC2EnergyAvSum_offline/D");
  
  fChain->Branch("F11IC1Yanode",   F11IC1Yanode,  "F11IC1Yanode[8]/D");
  fChain->Branch("F11IC2Yanode",   F11IC2Yanode,  "F11IC2Yanode[8]/D");
  fChain->Branch("F11YIC1",    &F11YIC1,    "F11YIC1/D");
  fChain->Branch("F11BIC1",    &F11BIC1,    "F11BIC1/D");
  fChain->Branch("F11YIC2",    &F11YIC2,    "F11YIC2/D");
  fChain->Branch("F11BIC2",    &F11BIC2,    "F11BIC2/D");
  
  // online information
  fChain->Branch("tof_online",   tof_online,  "tof_online[3]/D");
  fChain->Branch("beta_online",  beta_online, "beta_online[3]/D");
  fChain->Branch("zet_online",   zet_online,  "zet_online[6]/D");
  fChain->Branch("aoq_online",   aoq_online,  "aoq_online[6]/D");
  fChain->Branch("delta_online", delta_online,"delta_online[4]/D");
  
  //
  fChain->Branch("dipolebrho",   dipolebrho,  "dipolebrho[8]/D");
  fChain->Branch("tof37",    &tof37,    "tof37/D");
  fChain->Branch("tof811",   &tof811,   "tof811/D");
  fChain->Branch("beta37",   &beta37,   "beta37/D");
  fChain->Branch("beta811",  &beta811,  "beta811/D");
  fChain->Branch("beta35_dipoleratio",   &beta35_dipoleratio,   "beta35_dipoleratio/D");
  fChain->Branch("beta57_dipoleratio",   &beta57_dipoleratio,   "beta57_dipoleratio/D");
//  fChain->Branch("beta89_dipoleratio",   &beta89_dipoleratio,   "beta89_dipoleratio/D");
//  fChain->Branch("beta911_dipoleratio",  &beta911_dipoleratio,  "beta911_dipoleratio/D");
  fChain->Branch("delta35",   &delta35,   "delta35/D");
  fChain->Branch("delta57",   &delta57,   "delta57/D");
  fChain->Branch("delta911",  &delta911,  "delta911/D");
  
  fChain->Branch("zet7",  &zet7,  "zet7/D");
  fChain->Branch("zet11", &zet11, "zet11/D");
  fChain->Branch("aoq57", &aoq57, "aoq57/D");
  fChain->Branch("aoq911",&aoq911,"aoq911/D");

  fChain->Branch("btof37",    &btof37,    "btof37/O");
  fChain->Branch("btof811",   &btof811,   "btof811/O");
  fChain->Branch("bdelta35",   &bdelta35,   "bdelta35/O");
  fChain->Branch("bdelta57",   &bdelta57,   "bdelta57/O");
  fChain->Branch("bdelta911",  &bdelta911,  "bdelta911/O");
  fChain->Branch("bzet7",  &bzet7,  "bzet7/O");
  fChain->Branch("bzet11", &bzet11, "bzet11/O");
  fChain->Branch("baoq57", &baoq57, "baoq57/O");
  fChain->Branch("baoq911",&baoq911,"baoq911/O");
  
  //------------
  fChain->Branch("delta35_1110",   &delta35_1110,   "delta35_1110/D");
  fChain->Branch("delta35_1101",   &delta35_1101,   "delta35_1101/D");
  fChain->Branch("delta35_1011",   &delta35_1011,   "delta35_1011/D");
  fChain->Branch("delta35_0111",   &delta35_0111,   "delta35_0111/D");
  fChain->Branch("delta35_ext",    &delta35_ext,    "delta35_ext/D");
  fChain->Branch("delta57_1110",   &delta57_1110,   "delta57_1110/D");
  fChain->Branch("delta57_1101",   &delta57_1101,   "delta57_1101/D");
  fChain->Branch("delta57_1011",   &delta57_1011,   "delta57_1011/D");
  fChain->Branch("delta57_0111",   &delta57_0111,   "delta57_0111/D");
  fChain->Branch("delta57_ext",    &delta57_ext,    "delta57_ext/D");
  fChain->Branch("delta911_1110",   &delta911_1110,   "delta911_1110/D");
  fChain->Branch("delta911_1101",   &delta911_1101,   "delta911_1101/D");
  fChain->Branch("delta911_1011",   &delta911_1011,   "delta911_1011/D");
  fChain->Branch("delta911_0111",   &delta911_0111,   "delta911_0111/D");
  fChain->Branch("delta911_ext",    &delta911_ext,    "delta911_ext/D");
 
  fChain->Branch("bdelta35_1110",   &bdelta35_1110,   "bdelta35_1110/O");
  fChain->Branch("bdelta35_1101",   &bdelta35_1101,   "bdelta35_1101/O");
  fChain->Branch("bdelta35_1011",   &bdelta35_1011,   "bdelta35_1011/O");
  fChain->Branch("bdelta35_0111",   &bdelta35_0111,   "bdelta35_0111/O");
  fChain->Branch("bdelta35_3plane", &bdelta35_3plane, "bdelta35_3plane/O");
  fChain->Branch("bdelta35_ext",    &bdelta35_ext,    "bdelta35_ext/O");
  fChain->Branch("bdelta57_1110",   &bdelta57_1110,   "bdelta57_1110/O");
  fChain->Branch("bdelta57_1101",   &bdelta57_1101,   "bdelta57_1101/O");
  fChain->Branch("bdelta57_1011",   &bdelta57_1011,   "bdelta57_1011/O");
  fChain->Branch("bdelta57_0111",   &bdelta57_0111,   "bdelta57_0111/O");
  fChain->Branch("bdelta57_3plane", &bdelta57_3plane, "bdelta57_3plane/O");
  fChain->Branch("bdelta57_ext",    &bdelta57_ext,    "bdelta57_ext/O");
  fChain->Branch("bdelta911_1110",   &bdelta911_1110,   "bdelta911_1110/O");
  fChain->Branch("bdelta911_1101",   &bdelta911_1101,   "bdelta911_1101/O");
  fChain->Branch("bdelta911_1011",   &bdelta911_1011,   "bdelta911_1011/O");
  fChain->Branch("bdelta911_0111",   &bdelta911_0111,   "bdelta911_0111/O");
  fChain->Branch("bdelta911_3plane", &bdelta911_3plane, "bdelta911_3plane/O");
  fChain->Branch("bdelta911_ext",    &bdelta911_ext,    "bdelta911_ext/O");
  
  fChain->Branch("aoq57_1110",   &aoq57_1110,   "aoq57_1110/D");
  fChain->Branch("aoq57_1101",   &aoq57_1101,   "aoq57_1101/D");
  fChain->Branch("aoq57_1011",   &aoq57_1011,   "aoq57_1011/D");
  fChain->Branch("aoq57_0111",   &aoq57_0111,   "aoq57_0111/D");
  fChain->Branch("aoq57_ext",    &aoq57_ext,    "aoq57_ext/D");
  fChain->Branch("aoq911_1110",   &aoq911_1110,   "aoq911_1110/D");
  fChain->Branch("aoq911_1101",   &aoq911_1101,   "aoq911_1101/D");
  fChain->Branch("aoq911_1011",   &aoq911_1011,   "aoq911_1011/D");
  fChain->Branch("aoq911_0111",   &aoq911_0111,   "aoq911_0111/D");
  fChain->Branch("aoq911_ext",    &aoq911_ext,    "aoq911_ext/D");
  
  fChain->Branch("baoq57_1110",   &baoq57_1110,   "baoq57_1110/O");
  fChain->Branch("baoq57_1101",   &baoq57_1101,   "baoq57_1101/O");
  fChain->Branch("baoq57_1011",   &baoq57_1011,   "baoq57_1011/O");
  fChain->Branch("baoq57_0111",   &baoq57_0111,   "baoq57_0111/O");
  fChain->Branch("baoq57_3plane", &baoq57_3plane, "baoq57_3plane/O");
  fChain->Branch("baoq57_ext",    &baoq57_ext,    "baoq57_ext/O");
  fChain->Branch("baoq911_1110",   &baoq911_1110,   "baoq911_1110/O");
  fChain->Branch("baoq911_1101",   &baoq911_1101,   "baoq911_1101/O");
  fChain->Branch("baoq911_1011",   &baoq911_1011,   "baoq911_1011/O");
  fChain->Branch("baoq911_0111",   &baoq911_0111,   "baoq911_0111/O");
  fChain->Branch("baoq911_3plane", &baoq911_3plane, "baoq911_3plane/O");
  fChain->Branch("baoq911_ext",    &baoq911_ext,    "baoq911_ext/O");
  //-------------------------------------------------------------------------------
  
  //-------------------------------------------------------
  fChain->Branch("tof78",    &tof78,    "tof78/D");
  fChain->Branch("beta78",   &beta78,   "beta78/D");
  fChain->Branch("btof78",   &btof78,   "btof78/O");
  
  fChain->Branch("DALINum_A", &DALINum_A,  "DALINum_A/I");
  fChain->Branch("DALIADC_A",  DALIADC_A,  "DALIADC_A[10]/D");
  fChain->Branch("DALIE_A",    DALIE_A,    "DALIE_A[10]/D");
  fChain->Branch("DALIT_A",    DALIT_A,    "DALIT_A[10]/D");
  fChain->Branch("DALIID_A",   DALIID_A,   "DALIID_A[10]/I");
  
  fChain->Branch("DALINum_AT", &DALINum_AT,  "DALINum_AT/I");
  fChain->Branch("DALIADC_AT",  DALIADC_AT,  "DALIADC_AT[10]/D");
  fChain->Branch("DALIE_AT",    DALIE_AT,    "DALIE_AT[10]/D");
  fChain->Branch("DALIID_AT",   DALIID_AT,   "DALIID_AT[10]/I");
  fChain->Branch("DALITheta_AT",DALITheta_AT,"DALITheta_AT[10]/D");
  fChain->Branch("DALIX_AT",    DALIX_AT,    "DALIX_AT[10]/D");
  fChain->Branch("DALIY_AT",    DALIY_AT,    "DALIY_AT[10]/D");
  fChain->Branch("DALIZ_AT",    DALIZ_AT,    "DALIZ_AT[10]/D");
  fChain->Branch("DALIT_AT",    DALIT_AT,    "DALIT_AT[10]/D");
  fChain->Branch("DALIEdop78_AT",DALIEdop78_AT, "DALIEdop78_AT[10]/D");

  
  fChain->Branch("DALINum", &DALINum,  "DALINum/I");
  fChain->Branch("DALIADC",  DALIADC,  "DALIADC[10]/D");
  fChain->Branch("DALIE",    DALIE,    "DALIE[10]/D");
  fChain->Branch("DALIEdop78", DALIEdop78, "DALIEdop78[10]/D");
  fChain->Branch("DALIEdop811", DALIEdop811, "DALIEdop811[10]/D");
  fChain->Branch("DALIEdopave", DALIEdopave, "DALIEdopave[10]/D");
  fChain->Branch("DALIID",   DALIID,   "DALIID[10]/I");
  fChain->Branch("DALITheta",DALITheta,"DALITheta[10]/D");
  fChain->Branch("DALIX",    DALIX,    "DALIX[10]/D");
  fChain->Branch("DALIY",    DALIY,    "DALIY[10]/D");
  fChain->Branch("DALIZ",    DALIZ,    "DALIZ[10]/D");
  fChain->Branch("DALIT",    DALIT,    "DALIT[10]/D");

  fChain->Branch("DALINum_n", &DALINum_n,  "DALINum_n/I");
  fChain->Branch("DALIADC_n",  DALIADC_n,  "DALIADC_n[10]/D");
  fChain->Branch("DALIE_n",    DALIE_n,    "DALIE_n[10]/D");
  fChain->Branch("DALIEdop78_n", DALIEdop78_n, "DALIEdop78_n[10]/D");
  fChain->Branch("DALIEdop811_n", DALIEdop811_n, "DALIEdop811_n[10]/D");
  fChain->Branch("DALIEdopave_n", DALIEdopave_n, "DALIEdopave_n[10]/D");
  fChain->Branch("DALIID_n",   DALIID_n,   "DALIID_n[10]/I");
  fChain->Branch("DALITheta_n",DALITheta_n,"DALITheta_n[10]/D");
  fChain->Branch("DALIX_n",    DALIX_n,    "DALIX_n[10]/D");
  fChain->Branch("DALIY_n",    DALIY_n,    "DALIY_n[10]/D");
  fChain->Branch("DALIZ_n",    DALIZ_n,    "DALIZ_n[10]/D");
  fChain->Branch("DALIT_n",    DALIT_n,    "DALIT_n[10]/D");

  
  fChain->Branch("DALINum_addback", &DALINum_addback,  "DALINum_addback/I");
//  fChain->Branch("DALIADC_addback",  DALIADC_addback,  "DALIADC_addback[10]/D");
  fChain->Branch("DALIE_addback",    DALIE_addback,    "DALIE_addback[10]/D");
  fChain->Branch("DALIEdop78_addback", DALIEdop78_addback, "DALIEdop78_addback[10]/D");
  fChain->Branch("DALIEdop811_addback", DALIEdop811_addback, "DALIEdop811_addback[10]/D");
  fChain->Branch("DALIEdopave_addback", DALIEdopave_addback, "DALIEdopave_addback[10]/D");
  fChain->Branch("DALIID_addback",   DALIID_addback,   "DALIID_addback[10]/I");
  fChain->Branch("DALITheta_addback",DALITheta_addback,"DALITheta_addback[10]/D");
  fChain->Branch("DALIX_addback",    DALIX_addback,    "DALIX_addback[10]/D");
  fChain->Branch("DALIY_addback",    DALIY_addback,    "DALIY_addback[10]/D");
  fChain->Branch("DALIZ_addback",    DALIZ_addback,    "DALIZ_addback[10]/D");
  fChain->Branch("DALIT_addback",    DALIT_addback,    "DALIT_addback[10]/D");
  fChain->Branch("DALIN_addback",    DALIN_addback,    "DALIN_addback[10]/I");
}
#endif
