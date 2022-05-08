//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 27 18:36:03 2017 by ROOT version 6.08/00
// from TTree tree/tree
// found on file: run0038.ver20170324.root
//////////////////////////////////////////////////////////

#ifndef RIBF132Raw_h
#define RIBF132Raw_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"
#include "TNamed.h"
#include "iostream"

using namespace std;
const Int_t kMaxEventInfo = 1;

class RIBF132Raw {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  // moved to top
  
  // from here
  // Declaration of leaf types
  Int_t           EventInfo_;
  UInt_t          EventInfo_fUniqueID[kMaxEventInfo];   //[EventInfo_]
  UInt_t          EventInfo_fBits[kMaxEventInfo];   //[EventInfo_]
  TString         EventInfo_fName[kMaxEventInfo];
  TString         EventInfo_fTitle[kMaxEventInfo];
  Int_t           EventInfo_runnumber[kMaxEventInfo];   //[EventInfo_]
  Int_t           EventInfo_eventnumber[kMaxEventInfo];   //[EventInfo_]
  TString         EventInfo_subsysname[kMaxEventInfo];
  ULong64_t       EventInfo_timestamp[kMaxEventInfo];   //[EventInfo_]
  Int_t           EventInfo_comp_val[kMaxEventInfo];   //[EventInfo_]
  UInt_t          EventInfo_fBit[kMaxEventInfo];   //[EventInfo_]
  Int_t           fbit;
  Double_t        F3X;
  Double_t        F3A;
  Double_t        F3Y;
  Double_t        F3B;
  Double_t        F5X;
  Double_t        F5A;
  Double_t        F5Y;
  Double_t        F5B;
  Double_t        F7X;
  Double_t        F7A;
  Double_t        F7Y;
  Double_t        F7B;
  Double_t        F8X;
  Double_t        F8A;
  Double_t        F8Y;
  Double_t        F8B;
  Double_t        F9X;
  Double_t        F9A;
  Double_t        F9Y;
  Double_t        F9B;
  Double_t        F11X;
  Double_t        F11A;
  Double_t        F11Y;
  Double_t        F11B;
  Double_t        F3PLA_TL_raw;
  Double_t        F3PLA_TR_raw;
  Double_t        F5PLA_TL_raw;
  Double_t        F5PLA_TR_raw;
  Double_t        F7PLA_TL_raw;
  Double_t        F7PLA_TR_raw;
  Double_t        F8PLA_TL_raw;
  Double_t        F8PLA_TR_raw;
  Double_t        F11PLA_TL_raw;
  Double_t        F11PLA_TR_raw;
  Double_t        F11LONG_TL_raw;
  Double_t        F11LONG_TR_raw;
  Double_t        F11VETO_TL_raw;
  Double_t        F11VETO_TR_raw;
  Double_t        PLATDC_B3F_Trig;
  Double_t        F3PLA_TL_raw_multi[4];
  Double_t        F3PLA_TR_raw_multi[4];
  Double_t        F5PLA_TL_raw_multi[4];
  Double_t        F5PLA_TR_raw_multi[4];
  Double_t        F7PLA_TL_raw_multi[4];
  Double_t        F7PLA_TR_raw_multi[4];
  Double_t        F8PLA_TL_raw_multi[4];
  Double_t        F8PLA_TR_raw_multi[4];
  Double_t        F11PLA_TL_raw_multi[4];
  Double_t        F11PLA_TR_raw_multi[4];
  Double_t        F11LONG_TL_raw_multi[4];
  Double_t        F11LONG_TR_raw_multi[4];
  Double_t        F11VETO_TL_raw_multi[4];
  Double_t        F11VETO_TR_raw_multi[4];
  Int_t           F3PLA_TL_NumHit;
  Int_t           F3PLA_TR_NumHit;
  Int_t           F5PLA_TL_NumHit;
  Int_t           F5PLA_TR_NumHit;
  Int_t           F7PLA_TL_NumHit;
  Int_t           F7PLA_TR_NumHit;
  Int_t           F8PLA_TL_NumHit;
  Int_t           F8PLA_TR_NumHit;
  Int_t           F11PLA_TL_NumHit;
  Int_t           F11PLA_TR_NumHit;
  Int_t           F11LONG_TL_NumHit;
  Int_t           F11LONG_TR_NumHit;
  Int_t           F11VETO_TL_NumHit;
  Int_t           F11VETO_TR_NumHit;
  Double_t        F3PLA_TL_raw_s;
  Double_t        F3PLA_TR_raw_s;
  Double_t        F5PLA_TL_raw_s;
  Double_t        F5PLA_TR_raw_s;
  Double_t        F7PLA_TL_raw_s;
  Double_t        F7PLA_TR_raw_s;
  Double_t        F8PLA_TL_raw_s;
  Double_t        F8PLA_TR_raw_s;
  Double_t        F11PLA_TL_raw_s;
  Double_t        F11PLA_TR_raw_s;
  Double_t        F11LONG_TL_raw_s;
  Double_t        F11LONG_TR_raw_s;
  Double_t        F11VETO_TL_raw_s;
  Double_t        F11VETO_TR_raw_s;
  Double_t        F3PLA_QL_raw;
  Double_t        F3PLA_QR_raw;
  Double_t        F5PLA_QL_raw;
  Double_t        F5PLA_QR_raw;
  Double_t        F7PLA_QL_raw;
  Double_t        F7PLA_QR_raw;
  Double_t        F8PLA_QL_raw;
  Double_t        F8PLA_QR_raw;
  Double_t        F11PLA_QL_raw;
  Double_t        F11PLA_QR_raw;
  Double_t        F11LONG_QL_raw;
  Double_t        F11LONG_QR_raw;
  Double_t        F11VETO_QL_raw;
  Double_t        F11VETO_QR_raw;
  Double_t        F7ICEnergySqSum;
  Double_t        F7ICEnergyAvSum;
  Double_t        F7ICADCraw[6];
  Double_t        F11IC1EnergySqSum;
  Double_t        F11IC1EnergyAvSum;
  Double_t        F11IC1ADCraw[8];
  Double_t        F11IC1TDCraw[8];
  Double_t        F11IC1TDCraw_multi[8][4];
  Int_t           F11IC1TDC_NumHit[8];
  Double_t        F11IC2EnergySqSum;
  Double_t        F11IC2EnergyAvSum;
  Double_t        F11IC2ADCraw[8];
  Double_t        F11IC2TDCraw[8];
  Double_t        F11IC2TDCraw_multi[8][4];
  Int_t           F11IC2TDC_NumHit[8];
  Int_t           F11TDC_F11PLA_TL_NumHit;
  Double_t        F11TDC_F11PLA_TL_raw;
  Double_t        F11TDC_F11PLA_TL_raw_multi[4];
  Int_t           F11TDC_F11PLA_TR_NumHit;
  Double_t        F11TDC_F11PLA_TR_raw;
  Double_t        F11TDC_F11PLA_TR_raw_multi[4];
  Int_t           F11TDC_F11LONG_TL_NumHit;
  Double_t        F11TDC_F11LONG_TL_raw;
  Double_t        F11TDC_F11LONG_TL_raw_multi[4];
  Int_t           F11TDC_F11LONG_TR_NumHit;
  Double_t        F11TDC_F11LONG_TR_raw;
  Double_t        F11TDC_F11LONG_TR_raw_multi[4];
  Int_t           F11TDC_F11VETO_TL_NumHit;
  Double_t        F11TDC_F11VETO_TL_raw;
  Double_t        F11TDC_F11VETO_TL_raw_multi[4];
  Int_t           F11TDC_F11VETO_TR_NumHit;
  Double_t        F11TDC_F11VETO_TR_raw;
  Double_t        F11TDC_F11VETO_TR_raw_multi[4];
  Int_t           F11TDC_TRIG_NumHit;
  Double_t        F11TDC_TRIG_raw;
  Double_t        F11TDC_TRIG_raw_multi[4];
  Double_t        tof[3];
  Double_t        beta[3];
  Double_t        zet[6];
  Double_t        zetc[6];
  Double_t        aoq[6];
  Double_t        aoqc[6];
  Double_t        delta[4];
  Double_t        dipolebrho[8];
  Double_t        PPACQX1[7][4];
  Double_t        PPACQX2[7][4];
  Double_t        PPACQY1[7][4];
  Double_t        PPACQY2[7][4];
  Double_t        PPACQA[7][4];
  Double_t        PPACTX1[7][4];
  Double_t        PPACTX2[7][4];
  Double_t        PPACTY1[7][4];
  Double_t        PPACTY2[7][4];
  Double_t        PPACTA[7][4];
  Double_t        PPACX[7][4];
  Double_t        PPACY[7][4];
  Double_t        PPACXZpos[7][4];
  Double_t        PPACYZpos[7][4];
  Double_t        PPACTX1_multi[7][4][4];
  Double_t        PPACTX2_multi[7][4][4];
  Double_t        PPACTY1_multi[7][4][4];
  Double_t        PPACTY2_multi[7][4][4];
  Double_t        PPACTA_multi[7][4][4];
  Int_t           PPACTX1_NumHit[7][4];
  Int_t           PPACTX2_NumHit[7][4];
  Int_t           PPACTY1_NumHit[7][4];
  Int_t           PPACTY2_NumHit[7][4];
  Int_t           PPACTA_NumHit[7][4];
  Double_t        PPACTX1_s[7][4];
  Double_t        PPACTX2_s[7][4];
  Double_t        PPACTY1_s[7][4];
  Double_t        PPACTY2_s[7][4];
  Double_t        PPACTA_s[7][4];
  Double_t        daliadc[188];
  Double_t        dalitdc[188];
  Double_t        dalitdc_s[188];
  Int_t           dalitdc_numhit[188];
  
  
  // List of branches
  TBranch        *b_EventInfo_;   //!
  TBranch        *b_EventInfo_fUniqueID;   //!
  TBranch        *b_EventInfo_fBits;   //!
  TBranch        *b_EventInfo_fName;   //!
  TBranch        *b_EventInfo_fTitle;   //!
  TBranch        *b_EventInfo_runnumber;   //!
  TBranch        *b_EventInfo_eventnumber;   //!
  TBranch        *b_EventInfo_subsysname;   //!
  TBranch        *b_EventInfo_timestamp;   //!
  TBranch        *b_EventInfo_comp_val;   //!
  TBranch        *b_EventInfo_fBit;   //!
  TBranch        *b_fbit;   //!
  TBranch        *b_F3X;   //!
  TBranch        *b_F3A;   //!
  TBranch        *b_F3Y;   //!
  TBranch        *b_F3B;   //!
  TBranch        *b_F5X;   //!
  TBranch        *b_F5A;   //!
  TBranch        *b_F5Y;   //!
  TBranch        *b_F5B;   //!
  TBranch        *b_F7X;   //!
  TBranch        *b_F7A;   //!
  TBranch        *b_F7Y;   //!
  TBranch        *b_F7B;   //!
  TBranch        *b_F8X;   //!
  TBranch        *b_F8A;   //!
  TBranch        *b_F8Y;   //!
  TBranch        *b_F8B;   //!
  TBranch        *b_F9X;   //!
  TBranch        *b_F9A;   //!
  TBranch        *b_F9Y;   //!
  TBranch        *b_F9B;   //!
  TBranch        *b_F11X;   //!
  TBranch        *b_F11A;   //!
  TBranch        *b_F11Y;   //!
  TBranch        *b_F11B;   //!
  TBranch        *b_F3PLA_TL_raw;   //!
  TBranch        *b_F3PLA_TR_raw;   //!
  TBranch        *b_F5PLA_TL_raw;   //!
  TBranch        *b_F5PLA_TR_raw;   //!
  TBranch        *b_F7PLA_TL_raw;   //!
  TBranch        *b_F7PLA_TR_raw;   //!
  TBranch        *b_F8PLA_TL_raw;   //!
  TBranch        *b_F8PLA_TR_raw;   //!
  TBranch        *b_F11PLA_TL_raw;   //!
  TBranch        *b_F11PLA_TR_raw;   //!
  TBranch        *b_F11LONG_TL_raw;   //!
  TBranch        *b_F11LONG_TR_raw;   //!
  TBranch        *b_F11VETO_TL_raw;   //!
  TBranch        *b_F11VETO_TR_raw;   //!
  TBranch        *b_PLATDC_B3F_Trig;   //!
  TBranch        *b_F3PLA_TL_raw_multi;   //!
  TBranch        *b_F3PLA_TR_raw_multi;   //!
  TBranch        *b_F5PLA_TL_raw_multi;   //!
  TBranch        *b_F5PLA_TR_raw_multi;   //!
  TBranch        *b_F7PLA_TL_raw_multi;   //!
  TBranch        *b_F7PLA_TR_raw_multi;   //!
  TBranch        *b_F8PLA_TL_raw_multi;   //!
  TBranch        *b_F8PLA_TR_raw_multi;   //!
  TBranch        *b_F11PLA_TL_raw_multi;   //!
  TBranch        *b_F11PLA_TR_raw_multi;   //!
  TBranch        *b_F11LONG_TL_raw_multi;   //!
  TBranch        *b_F11LONG_TR_raw_multi;   //!
  TBranch        *b_F11VETO_TL_raw_multi;   //!
  TBranch        *b_F11VETO_TR_raw_multi;   //!
  TBranch        *b_F3PLA_TL_NumHit;   //!
  TBranch        *b_F3PLA_TR_NumHit;   //!
  TBranch        *b_F5PLA_TL_NumHit;   //!
  TBranch        *b_F5PLA_TR_NumHit;   //!
  TBranch        *b_F7PLA_TL_NumHit;   //!
  TBranch        *b_F7PLA_TR_NumHit;   //!
  TBranch        *b_F8PLA_TL_NumHit;   //!
  TBranch        *b_F8PLA_TR_NumHit;   //!
  TBranch        *b_F11PLA_TL_NumHit;   //!
  TBranch        *b_F11PLA_TR_NumHit;   //!
  TBranch        *b_F11LONG_TL_NumHit;   //!
  TBranch        *b_F11LONG_TR_NumHit;   //!
  TBranch        *b_F11VETO_TL_NumHit;   //!
  TBranch        *b_F11VETO_TR_NumHit;   //!
  TBranch        *b_F3PLA_TL_raw_s;   //!
  TBranch        *b_F3PLA_TR_raw_s;   //!
  TBranch        *b_F5PLA_TL_raw_s;   //!
  TBranch        *b_F5PLA_TR_raw_s;   //!
  TBranch        *b_F7PLA_TL_raw_s;   //!
  TBranch        *b_F7PLA_TR_raw_s;   //!
  TBranch        *b_F8PLA_TL_raw_s;   //!
  TBranch        *b_F8PLA_TR_raw_s;   //!
  TBranch        *b_F11PLA_TL_raw_s;   //!
  TBranch        *b_F11PLA_TR_raw_s;   //!
  TBranch        *b_F11LONG_TL_raw_s;   //!
  TBranch        *b_F11LONG_TR_raw_s;   //!
  TBranch        *b_F11VETO_TL_raw_s;   //!
  TBranch        *b_F11VETO_TR_raw_s;   //!
  TBranch        *b_F3PLA_QL_raw;   //!
  TBranch        *b_F3PLA_QR_raw;   //!
  TBranch        *b_F5PLA_QL_raw;   //!
  TBranch        *b_F5PLA_QR_raw;   //!
  TBranch        *b_F7PLA_QL_raw;   //!
  TBranch        *b_F7PLA_QR_raw;   //!
  TBranch        *b_F8PLA_QL_raw;   //!
  TBranch        *b_F8PLA_QR_raw;   //!
  TBranch        *b_F11PLA_QL_raw;   //!
  TBranch        *b_F11PLA_QR_raw;   //!
  TBranch        *b_F11LONG_QL_raw;   //!
  TBranch        *b_F11LONG_QR_raw;   //!
  TBranch        *b_F11VETO_QL_raw;   //!
  TBranch        *b_F11VETO_QR_raw;   //!
  TBranch        *b_F7ICEnergySqSum;   //!
  TBranch        *b_F7ICEnergyAvSum;   //!
  TBranch        *b_F7ICADCraw;   //!
  TBranch        *b_F11IC1EnergySqSum;   //!
  TBranch        *b_F11IC1EnergyAvSum;   //!
  TBranch        *b_F11IC1ADCraw;   //!
  TBranch        *b_F11IC1TDCraw;   //!
  TBranch        *b_F11IC1TDCraw_multi;   //!
  TBranch        *b_F11IC1TDC_NumHit;   //!
  TBranch        *b_F11IC2EnergySqSum;   //!
  TBranch        *b_F11IC2EnergyAvSum;   //!
  TBranch        *b_F11IC2ADCraw;   //!
  TBranch        *b_F11IC2TDCraw;   //!
  TBranch        *b_F11IC2TDCraw_multi;   //!
  TBranch        *b_F11IC2TDC_NumHit;   //!
  TBranch        *b_F11TDC_F11PLA_TL_NumHit;   //!
  TBranch        *b_F11TDC_F11PLA_TL_raw;   //!
  TBranch        *b_F11TDC_F11PLA_TL_raw_multi;   //!
  TBranch        *b_F11TDC_F11PLA_TR_NumHit;   //!
  TBranch        *b_F11TDC_F11PLA_TR_raw;   //!
  TBranch        *b_F11TDC_F11PLA_TR_raw_multi;   //!
  TBranch        *b_F11TDC_F11LONG_TL_NumHit;   //!
  TBranch        *b_F11TDC_F11LONG_TL_raw;   //!
  TBranch        *b_F11TDC_F11LONG_TL_raw_multi;   //!
  TBranch        *b_F11TDC_F11LONG_TR_NumHit;   //!
  TBranch        *b_F11TDC_F11LONG_TR_raw;   //!
  TBranch        *b_F11TDC_F11LONG_TR_raw_multi;   //!
  TBranch        *b_F11TDC_F11VETO_TL_NumHit;   //!
  TBranch        *b_F11TDC_F11VETO_TL_raw;   //!
  TBranch        *b_F11TDC_F11VETO_TL_raw_multi;   //!
  TBranch        *b_F11TDC_F11VETO_TR_NumHit;   //!
  TBranch        *b_F11TDC_F11VETO_TR_raw;   //!
  TBranch        *b_F11TDC_F11VETO_TR_raw_multi;   //!
  TBranch        *b_F11TDC_TRIG_NumHit;   //!
  TBranch        *b_F11TDC_TRIG_raw;   //!
  TBranch        *b_F11TDC_TRIG_raw_multi;   //!
  TBranch        *b_tof;   //!
  TBranch        *b_beta;   //!
  TBranch        *b_zet;   //!
  TBranch        *b_zetc;   //!
  TBranch        *b_aoq;   //!
  TBranch        *b_aoqc;   //!
  TBranch        *b_delta;   //!
  TBranch        *b_dipolebrho;   //!
  TBranch        *b_PPACQX1;   //!
  TBranch        *b_PPACQX2;   //!
  TBranch        *b_PPACQY1;   //!
  TBranch        *b_PPACQY2;   //!
  TBranch        *b_PPACQA;   //!
  TBranch        *b_PPACTX1;   //!
  TBranch        *b_PPACTX2;   //!
  TBranch        *b_PPACTY1;   //!
  TBranch        *b_PPACTY2;   //!
  TBranch        *b_PPACTA;   //!
  TBranch        *b_PPACX;   //!
  TBranch        *b_PPACY;   //!
  TBranch        *b_PPACXZpos;   //!
  TBranch        *b_PPACYZpos;   //!
  TBranch        *b_PPACTX1_multi;   //!
  TBranch        *b_PPACTX2_multi;   //!
  TBranch        *b_PPACTY1_multi;   //!
  TBranch        *b_PPACTY2_multi;   //!
  TBranch        *b_PPACTA_multi;   //!
  TBranch        *b_PPACTX1_NumHit;   //!
  TBranch        *b_PPACTX2_NumHit;   //!
  TBranch        *b_PPACTY1_NumHit;   //!
  TBranch        *b_PPACTY2_NumHit;   //!
  TBranch        *b_PPACTA_NumHit;   //!
  TBranch        *b_PPACTX1_s;   //!
  TBranch        *b_PPACTX2_s;   //!
  TBranch        *b_PPACTY1_s;   //!
  TBranch        *b_PPACTY2_s;   //!
  TBranch        *b_PPACTA_s;   //!  //to here
  TBranch        *b_daliadc;   //!  //to here
  TBranch        *b_dalitdc;   //!  //to here
  TBranch        *b_dalitdc_s;   //!  //to here
  TBranch        *b_dalitdc_numhit;   //!  //to here
  
   RIBF132Raw(TTree *tree=0);
   virtual ~RIBF132Raw();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  
};

#endif

#ifdef RIBF132Raw_cxx
RIBF132Raw::RIBF132Raw(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     /*
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run0038.ver20170324.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("run0038.ver20170324.root");
      }
      f->GetObject("tree",tree);
*/
     std::cout << "===== Input Tree does not exist... =====" << std::endl;
     
   }
   Init(tree);
}

RIBF132Raw::~RIBF132Raw()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RIBF132Raw::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RIBF132Raw::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void RIBF132Raw::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

  //from here
  
  
  fChain->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
  fChain->SetBranchAddress("EventInfo.fUniqueID", EventInfo_fUniqueID, &b_EventInfo_fUniqueID);
  fChain->SetBranchAddress("EventInfo.fBits", EventInfo_fBits, &b_EventInfo_fBits);
  fChain->SetBranchAddress("EventInfo.fName", EventInfo_fName, &b_EventInfo_fName);
  fChain->SetBranchAddress("EventInfo.fTitle", EventInfo_fTitle, &b_EventInfo_fTitle);
  fChain->SetBranchAddress("EventInfo.runnumber", EventInfo_runnumber, &b_EventInfo_runnumber);
  fChain->SetBranchAddress("EventInfo.eventnumber", EventInfo_eventnumber, &b_EventInfo_eventnumber);
  fChain->SetBranchAddress("EventInfo.subsysname", EventInfo_subsysname, &b_EventInfo_subsysname);
  fChain->SetBranchAddress("EventInfo.timestamp", EventInfo_timestamp, &b_EventInfo_timestamp);
  fChain->SetBranchAddress("EventInfo.comp_val", EventInfo_comp_val, &b_EventInfo_comp_val);
  fChain->SetBranchAddress("EventInfo.fBit", EventInfo_fBit, &b_EventInfo_fBit);
  fChain->SetBranchAddress("fbit", &fbit, &b_fbit);
  fChain->SetBranchAddress("F3X", &F3X, &b_F3X);
  fChain->SetBranchAddress("F3A", &F3A, &b_F3A);
  fChain->SetBranchAddress("F3Y", &F3Y, &b_F3Y);
  fChain->SetBranchAddress("F3B", &F3B, &b_F3B);
  fChain->SetBranchAddress("F5X", &F5X, &b_F5X);
  fChain->SetBranchAddress("F5A", &F5A, &b_F5A);
  fChain->SetBranchAddress("F5Y", &F5Y, &b_F5Y);
  fChain->SetBranchAddress("F5B", &F5B, &b_F5B);
  fChain->SetBranchAddress("F7X", &F7X, &b_F7X);
  fChain->SetBranchAddress("F7A", &F7A, &b_F7A);
  fChain->SetBranchAddress("F7Y", &F7Y, &b_F7Y);
  fChain->SetBranchAddress("F7B", &F7B, &b_F7B);
  fChain->SetBranchAddress("F8X", &F8X, &b_F8X);
  fChain->SetBranchAddress("F8A", &F8A, &b_F8A);
  fChain->SetBranchAddress("F8Y", &F8Y, &b_F8Y);
  fChain->SetBranchAddress("F8B", &F8B, &b_F8B);
  fChain->SetBranchAddress("F9X", &F9X, &b_F9X);
  fChain->SetBranchAddress("F9A", &F9A, &b_F9A);
  fChain->SetBranchAddress("F9Y", &F9Y, &b_F9Y);
  fChain->SetBranchAddress("F9B", &F9B, &b_F9B);
  fChain->SetBranchAddress("F11X", &F11X, &b_F11X);
  fChain->SetBranchAddress("F11A", &F11A, &b_F11A);
  fChain->SetBranchAddress("F11Y", &F11Y, &b_F11Y);
  fChain->SetBranchAddress("F11B", &F11B, &b_F11B);
  fChain->SetBranchAddress("F3PLA_TL_raw", &F3PLA_TL_raw, &b_F3PLA_TL_raw);
  fChain->SetBranchAddress("F3PLA_TR_raw", &F3PLA_TR_raw, &b_F3PLA_TR_raw);
  fChain->SetBranchAddress("F5PLA_TL_raw", &F5PLA_TL_raw, &b_F5PLA_TL_raw);
  fChain->SetBranchAddress("F5PLA_TR_raw", &F5PLA_TR_raw, &b_F5PLA_TR_raw);
  fChain->SetBranchAddress("F7PLA_TL_raw", &F7PLA_TL_raw, &b_F7PLA_TL_raw);
  fChain->SetBranchAddress("F7PLA_TR_raw", &F7PLA_TR_raw, &b_F7PLA_TR_raw);
  fChain->SetBranchAddress("F8PLA_TL_raw", &F8PLA_TL_raw, &b_F8PLA_TL_raw);
  fChain->SetBranchAddress("F8PLA_TR_raw", &F8PLA_TR_raw, &b_F8PLA_TR_raw);
  fChain->SetBranchAddress("F11PLA_TL_raw", &F11PLA_TL_raw, &b_F11PLA_TL_raw);
  fChain->SetBranchAddress("F11PLA_TR_raw", &F11PLA_TR_raw, &b_F11PLA_TR_raw);
  fChain->SetBranchAddress("F11LONG_TL_raw", &F11LONG_TL_raw, &b_F11LONG_TL_raw);
  fChain->SetBranchAddress("F11LONG_TR_raw", &F11LONG_TR_raw, &b_F11LONG_TR_raw);
  fChain->SetBranchAddress("F11VETO_TL_raw", &F11VETO_TL_raw, &b_F11VETO_TL_raw);
  fChain->SetBranchAddress("F11VETO_TR_raw", &F11VETO_TR_raw, &b_F11VETO_TR_raw);
  fChain->SetBranchAddress("PLATDC_B3F_Trig", &PLATDC_B3F_Trig, &b_PLATDC_B3F_Trig);
  fChain->SetBranchAddress("F3PLA_TL_raw_multi", F3PLA_TL_raw_multi, &b_F3PLA_TL_raw_multi);
  fChain->SetBranchAddress("F3PLA_TR_raw_multi", F3PLA_TR_raw_multi, &b_F3PLA_TR_raw_multi);
  fChain->SetBranchAddress("F5PLA_TL_raw_multi", F5PLA_TL_raw_multi, &b_F5PLA_TL_raw_multi);
  fChain->SetBranchAddress("F5PLA_TR_raw_multi", F5PLA_TR_raw_multi, &b_F5PLA_TR_raw_multi);
  fChain->SetBranchAddress("F7PLA_TL_raw_multi", F7PLA_TL_raw_multi, &b_F7PLA_TL_raw_multi);
  fChain->SetBranchAddress("F7PLA_TR_raw_multi", F7PLA_TR_raw_multi, &b_F7PLA_TR_raw_multi);
  fChain->SetBranchAddress("F8PLA_TL_raw_multi", F8PLA_TL_raw_multi, &b_F8PLA_TL_raw_multi);
  fChain->SetBranchAddress("F8PLA_TR_raw_multi", F8PLA_TR_raw_multi, &b_F8PLA_TR_raw_multi);
  fChain->SetBranchAddress("F11PLA_TL_raw_multi", F11PLA_TL_raw_multi, &b_F11PLA_TL_raw_multi);
  fChain->SetBranchAddress("F11PLA_TR_raw_multi", F11PLA_TR_raw_multi, &b_F11PLA_TR_raw_multi);
  fChain->SetBranchAddress("F11LONG_TL_raw_multi", F11LONG_TL_raw_multi, &b_F11LONG_TL_raw_multi);
  fChain->SetBranchAddress("F11LONG_TR_raw_multi", F11LONG_TR_raw_multi, &b_F11LONG_TR_raw_multi);
  fChain->SetBranchAddress("F11VETO_TL_raw_multi", F11VETO_TL_raw_multi, &b_F11VETO_TL_raw_multi);
  fChain->SetBranchAddress("F11VETO_TR_raw_multi", F11VETO_TR_raw_multi, &b_F11VETO_TR_raw_multi);
  fChain->SetBranchAddress("F3PLA_TL_NumHit", &F3PLA_TL_NumHit, &b_F3PLA_TL_NumHit);
  fChain->SetBranchAddress("F3PLA_TR_NumHit", &F3PLA_TR_NumHit, &b_F3PLA_TR_NumHit);
  fChain->SetBranchAddress("F5PLA_TL_NumHit", &F5PLA_TL_NumHit, &b_F5PLA_TL_NumHit);
  fChain->SetBranchAddress("F5PLA_TR_NumHit", &F5PLA_TR_NumHit, &b_F5PLA_TR_NumHit);
  fChain->SetBranchAddress("F7PLA_TL_NumHit", &F7PLA_TL_NumHit, &b_F7PLA_TL_NumHit);
  fChain->SetBranchAddress("F7PLA_TR_NumHit", &F7PLA_TR_NumHit, &b_F7PLA_TR_NumHit);
  fChain->SetBranchAddress("F8PLA_TL_NumHit", &F8PLA_TL_NumHit, &b_F8PLA_TL_NumHit);
  fChain->SetBranchAddress("F8PLA_TR_NumHit", &F8PLA_TR_NumHit, &b_F8PLA_TR_NumHit);
  fChain->SetBranchAddress("F11PLA_TL_NumHit", &F11PLA_TL_NumHit, &b_F11PLA_TL_NumHit);
  fChain->SetBranchAddress("F11PLA_TR_NumHit", &F11PLA_TR_NumHit, &b_F11PLA_TR_NumHit);
  fChain->SetBranchAddress("F11LONG_TL_NumHit", &F11LONG_TL_NumHit, &b_F11LONG_TL_NumHit);
  fChain->SetBranchAddress("F11LONG_TR_NumHit", &F11LONG_TR_NumHit, &b_F11LONG_TR_NumHit);
  fChain->SetBranchAddress("F11VETO_TL_NumHit", &F11VETO_TL_NumHit, &b_F11VETO_TL_NumHit);
  fChain->SetBranchAddress("F11VETO_TR_NumHit", &F11VETO_TR_NumHit, &b_F11VETO_TR_NumHit);
  fChain->SetBranchAddress("F3PLA_TL_raw_s", &F3PLA_TL_raw_s, &b_F3PLA_TL_raw_s);
  fChain->SetBranchAddress("F3PLA_TR_raw_s", &F3PLA_TR_raw_s, &b_F3PLA_TR_raw_s);
  fChain->SetBranchAddress("F5PLA_TL_raw_s", &F5PLA_TL_raw_s, &b_F5PLA_TL_raw_s);
  fChain->SetBranchAddress("F5PLA_TR_raw_s", &F5PLA_TR_raw_s, &b_F5PLA_TR_raw_s);
  fChain->SetBranchAddress("F7PLA_TL_raw_s", &F7PLA_TL_raw_s, &b_F7PLA_TL_raw_s);
  fChain->SetBranchAddress("F7PLA_TR_raw_s", &F7PLA_TR_raw_s, &b_F7PLA_TR_raw_s);
  fChain->SetBranchAddress("F8PLA_TL_raw_s", &F8PLA_TL_raw_s, &b_F8PLA_TL_raw_s);
  fChain->SetBranchAddress("F8PLA_TR_raw_s", &F8PLA_TR_raw_s, &b_F8PLA_TR_raw_s);
  fChain->SetBranchAddress("F11PLA_TL_raw_s", &F11PLA_TL_raw_s, &b_F11PLA_TL_raw_s);
  fChain->SetBranchAddress("F11PLA_TR_raw_s", &F11PLA_TR_raw_s, &b_F11PLA_TR_raw_s);
  fChain->SetBranchAddress("F11LONG_TL_raw_s", &F11LONG_TL_raw_s, &b_F11LONG_TL_raw_s);
  fChain->SetBranchAddress("F11LONG_TR_raw_s", &F11LONG_TR_raw_s, &b_F11LONG_TR_raw_s);
  fChain->SetBranchAddress("F11VETO_TL_raw_s", &F11VETO_TL_raw_s, &b_F11VETO_TL_raw_s);
  fChain->SetBranchAddress("F11VETO_TR_raw_s", &F11VETO_TR_raw_s, &b_F11VETO_TR_raw_s);
  fChain->SetBranchAddress("F3PLA_QL_raw", &F3PLA_QL_raw, &b_F3PLA_QL_raw);
  fChain->SetBranchAddress("F3PLA_QR_raw", &F3PLA_QR_raw, &b_F3PLA_QR_raw);
  fChain->SetBranchAddress("F5PLA_QL_raw", &F5PLA_QL_raw, &b_F5PLA_QL_raw);
  fChain->SetBranchAddress("F5PLA_QR_raw", &F5PLA_QR_raw, &b_F5PLA_QR_raw);
  fChain->SetBranchAddress("F7PLA_QL_raw", &F7PLA_QL_raw, &b_F7PLA_QL_raw);
  fChain->SetBranchAddress("F7PLA_QR_raw", &F7PLA_QR_raw, &b_F7PLA_QR_raw);
  fChain->SetBranchAddress("F8PLA_QL_raw", &F8PLA_QL_raw, &b_F8PLA_QL_raw);
  fChain->SetBranchAddress("F8PLA_QR_raw", &F8PLA_QR_raw, &b_F8PLA_QR_raw);
  fChain->SetBranchAddress("F11PLA_QL_raw", &F11PLA_QL_raw, &b_F11PLA_QL_raw);
  fChain->SetBranchAddress("F11PLA_QR_raw", &F11PLA_QR_raw, &b_F11PLA_QR_raw);
  fChain->SetBranchAddress("F11LONG_QL_raw", &F11LONG_QL_raw, &b_F11LONG_QL_raw);
  fChain->SetBranchAddress("F11LONG_QR_raw", &F11LONG_QR_raw, &b_F11LONG_QR_raw);
  fChain->SetBranchAddress("F11VETO_QL_raw", &F11VETO_QL_raw, &b_F11VETO_QL_raw);
  fChain->SetBranchAddress("F11VETO_QR_raw", &F11VETO_QR_raw, &b_F11VETO_QR_raw);
  fChain->SetBranchAddress("F7ICEnergySqSum", &F7ICEnergySqSum, &b_F7ICEnergySqSum);
  fChain->SetBranchAddress("F7ICEnergyAvSum", &F7ICEnergyAvSum, &b_F7ICEnergyAvSum);
  fChain->SetBranchAddress("F7ICADCraw", F7ICADCraw, &b_F7ICADCraw);
  fChain->SetBranchAddress("F11IC1EnergySqSum", &F11IC1EnergySqSum, &b_F11IC1EnergySqSum);
  fChain->SetBranchAddress("F11IC1EnergyAvSum", &F11IC1EnergyAvSum, &b_F11IC1EnergyAvSum);
  fChain->SetBranchAddress("F11IC1ADCraw", F11IC1ADCraw, &b_F11IC1ADCraw);
  fChain->SetBranchAddress("F11IC1TDCraw", F11IC1TDCraw, &b_F11IC1TDCraw);
  fChain->SetBranchAddress("F11IC1TDCraw_multi", F11IC1TDCraw_multi, &b_F11IC1TDCraw_multi);
  fChain->SetBranchAddress("F11IC1TDC_NumHit", F11IC1TDC_NumHit, &b_F11IC1TDC_NumHit);
  fChain->SetBranchAddress("F11IC2EnergySqSum", &F11IC2EnergySqSum, &b_F11IC2EnergySqSum);
  fChain->SetBranchAddress("F11IC2EnergyAvSum", &F11IC2EnergyAvSum, &b_F11IC2EnergyAvSum);
  fChain->SetBranchAddress("F11IC2ADCraw", F11IC2ADCraw, &b_F11IC2ADCraw);
  fChain->SetBranchAddress("F11IC2TDCraw", F11IC2TDCraw, &b_F11IC2TDCraw);
  fChain->SetBranchAddress("F11IC2TDCraw_multi", F11IC2TDCraw_multi, &b_F11IC2TDCraw_multi);
  fChain->SetBranchAddress("F11IC2TDC_NumHit", F11IC2TDC_NumHit, &b_F11IC2TDC_NumHit);
  fChain->SetBranchAddress("F11TDC_F11PLA_TL_NumHit", &F11TDC_F11PLA_TL_NumHit, &b_F11TDC_F11PLA_TL_NumHit);
  fChain->SetBranchAddress("F11TDC_F11PLA_TL_raw", &F11TDC_F11PLA_TL_raw, &b_F11TDC_F11PLA_TL_raw);
  fChain->SetBranchAddress("F11TDC_F11PLA_TL_raw_multi", F11TDC_F11PLA_TL_raw_multi, &b_F11TDC_F11PLA_TL_raw_multi);
  fChain->SetBranchAddress("F11TDC_F11PLA_TR_NumHit", &F11TDC_F11PLA_TR_NumHit, &b_F11TDC_F11PLA_TR_NumHit);
  fChain->SetBranchAddress("F11TDC_F11PLA_TR_raw", &F11TDC_F11PLA_TR_raw, &b_F11TDC_F11PLA_TR_raw);
  fChain->SetBranchAddress("F11TDC_F11PLA_TR_raw_multi", F11TDC_F11PLA_TR_raw_multi, &b_F11TDC_F11PLA_TR_raw_multi);
  fChain->SetBranchAddress("F11TDC_F11LONG_TL_NumHit", &F11TDC_F11LONG_TL_NumHit, &b_F11TDC_F11LONG_TL_NumHit);
  fChain->SetBranchAddress("F11TDC_F11LONG_TL_raw", &F11TDC_F11LONG_TL_raw, &b_F11TDC_F11LONG_TL_raw);
  fChain->SetBranchAddress("F11TDC_F11LONG_TL_raw_multi", F11TDC_F11LONG_TL_raw_multi, &b_F11TDC_F11LONG_TL_raw_multi);
  fChain->SetBranchAddress("F11TDC_F11LONG_TR_NumHit", &F11TDC_F11LONG_TR_NumHit, &b_F11TDC_F11LONG_TR_NumHit);
  fChain->SetBranchAddress("F11TDC_F11LONG_TR_raw", &F11TDC_F11LONG_TR_raw, &b_F11TDC_F11LONG_TR_raw);
  fChain->SetBranchAddress("F11TDC_F11LONG_TR_raw_multi", F11TDC_F11LONG_TR_raw_multi, &b_F11TDC_F11LONG_TR_raw_multi);
  fChain->SetBranchAddress("F11TDC_F11VETO_TL_NumHit", &F11TDC_F11VETO_TL_NumHit, &b_F11TDC_F11VETO_TL_NumHit);
  fChain->SetBranchAddress("F11TDC_F11VETO_TL_raw", &F11TDC_F11VETO_TL_raw, &b_F11TDC_F11VETO_TL_raw);
  fChain->SetBranchAddress("F11TDC_F11VETO_TL_raw_multi", F11TDC_F11VETO_TL_raw_multi, &b_F11TDC_F11VETO_TL_raw_multi);
  fChain->SetBranchAddress("F11TDC_F11VETO_TR_NumHit", &F11TDC_F11VETO_TR_NumHit, &b_F11TDC_F11VETO_TR_NumHit);
  fChain->SetBranchAddress("F11TDC_F11VETO_TR_raw", &F11TDC_F11VETO_TR_raw, &b_F11TDC_F11VETO_TR_raw);
  fChain->SetBranchAddress("F11TDC_F11VETO_TR_raw_multi", F11TDC_F11VETO_TR_raw_multi, &b_F11TDC_F11VETO_TR_raw_multi);
  fChain->SetBranchAddress("F11TDC_TRIG_NumHit", &F11TDC_TRIG_NumHit, &b_F11TDC_TRIG_NumHit);
  fChain->SetBranchAddress("F11TDC_TRIG_raw", &F11TDC_TRIG_raw, &b_F11TDC_TRIG_raw);
  fChain->SetBranchAddress("F11TDC_TRIG_raw_multi", F11TDC_TRIG_raw_multi, &b_F11TDC_TRIG_raw_multi);
  fChain->SetBranchAddress("tof", tof, &b_tof);
  fChain->SetBranchAddress("beta", beta, &b_beta);
  fChain->SetBranchAddress("zet", zet, &b_zet);
  fChain->SetBranchAddress("zetc", zetc, &b_zetc);
  fChain->SetBranchAddress("aoq", aoq, &b_aoq);
  fChain->SetBranchAddress("aoqc", aoqc, &b_aoqc);
  fChain->SetBranchAddress("delta", delta, &b_delta);
  fChain->SetBranchAddress("dipolebrho", dipolebrho, &b_dipolebrho);
  fChain->SetBranchAddress("PPACQX1", PPACQX1, &b_PPACQX1);
  fChain->SetBranchAddress("PPACQX2", PPACQX2, &b_PPACQX2);
  fChain->SetBranchAddress("PPACQY1", PPACQY1, &b_PPACQY1);
  fChain->SetBranchAddress("PPACQY2", PPACQY2, &b_PPACQY2);
  fChain->SetBranchAddress("PPACQA", PPACQA, &b_PPACQA);
  fChain->SetBranchAddress("PPACTX1", PPACTX1, &b_PPACTX1);
  fChain->SetBranchAddress("PPACTX2", PPACTX2, &b_PPACTX2);
  fChain->SetBranchAddress("PPACTY1", PPACTY1, &b_PPACTY1);
  fChain->SetBranchAddress("PPACTY2", PPACTY2, &b_PPACTY2);
  fChain->SetBranchAddress("PPACTA", PPACTA, &b_PPACTA);
  fChain->SetBranchAddress("PPACX", PPACX, &b_PPACX);
  fChain->SetBranchAddress("PPACY", PPACY, &b_PPACY);
  fChain->SetBranchAddress("PPACXZpos", PPACXZpos, &b_PPACXZpos);
  fChain->SetBranchAddress("PPACYZpos", PPACYZpos, &b_PPACYZpos);
  fChain->SetBranchAddress("PPACTX1_multi", PPACTX1_multi, &b_PPACTX1_multi);
  fChain->SetBranchAddress("PPACTX2_multi", PPACTX2_multi, &b_PPACTX2_multi);
  fChain->SetBranchAddress("PPACTY1_multi", PPACTY1_multi, &b_PPACTY1_multi);
  fChain->SetBranchAddress("PPACTY2_multi", PPACTY2_multi, &b_PPACTY2_multi);
  fChain->SetBranchAddress("PPACTA_multi", PPACTA_multi, &b_PPACTA_multi);
  fChain->SetBranchAddress("PPACTX1_NumHit", PPACTX1_NumHit, &b_PPACTX1_NumHit);
  fChain->SetBranchAddress("PPACTX2_NumHit", PPACTX2_NumHit, &b_PPACTX2_NumHit);
  fChain->SetBranchAddress("PPACTY1_NumHit", PPACTY1_NumHit, &b_PPACTY1_NumHit);
  fChain->SetBranchAddress("PPACTY2_NumHit", PPACTY2_NumHit, &b_PPACTY2_NumHit);
  fChain->SetBranchAddress("PPACTA_NumHit", PPACTA_NumHit, &b_PPACTA_NumHit);
  fChain->SetBranchAddress("PPACTX1_s", PPACTX1_s, &b_PPACTX1_s);
  fChain->SetBranchAddress("PPACTX2_s", PPACTX2_s, &b_PPACTX2_s);
  fChain->SetBranchAddress("PPACTY1_s", PPACTY1_s, &b_PPACTY1_s);
  fChain->SetBranchAddress("PPACTY2_s", PPACTY2_s, &b_PPACTY2_s);
  fChain->SetBranchAddress("PPACTA_s", PPACTA_s, &b_PPACTA_s);
  fChain->SetBranchAddress("daliadc",  daliadc,  &b_daliadc);
  fChain->SetBranchAddress("dalitdc",  dalitdc,  &b_dalitdc);
  fChain->SetBranchAddress("dalitdc_s",dalitdc_s,&b_dalitdc_s);
  fChain->SetBranchAddress("dalitdc_numhit", dalitdc_numhit, &b_dalitdc_numhit);
  
  // to here
  
   Notify();
}

Bool_t RIBF132Raw::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RIBF132Raw::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RIBF132Raw::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RIBF132Raw_cxx
