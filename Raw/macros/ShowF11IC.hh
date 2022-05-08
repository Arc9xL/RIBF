#ifndef SHOW_F11IC_HH
#define SHOW_F11IC_HH

#include "TArtAnaLoop.hh"
#include "TArtStoreManager.hh"
#include "TArtCore.hh"

#include "TROOT.h"
#include "TH2.h"
#include "TGraph.h"
#include "TTree.h"

#include "TArtBigRIPSParameters.hh"
#include "TArtDALIParameters.hh"

#include "TArtCalibPID.hh"
#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibIC.hh"

#include "TArtRecoPID.hh"
#include "TArtRecoRIPS.hh"
#include "TArtRecoTOF.hh"
#include "TArtRecoBeam.hh"


class ShowF11IC : public virtual TArtAnaLoop {

public:
  ShowF11IC();
  virtual ~ShowF11IC();

protected:
  virtual void Construct();
  virtual void Calculate();
  virtual void Destruct();

  TTree *tree;
  int neve;

  TArtStoreManager * sman;
  //  TArtEventStore *estore;
  //  TArtRawEventObject *rawevent;

  //For Online
  TCanvas *cF11IC;
  
  TH2F * h_adc[2];
  TH2F * h_tdc[2];
  TH2F * h_tdc_offseted[2];

  TH1F * h_adc_sq_sum[2];

  TH1F * h_de_sq_sum[2];

  TH1F * h_de_av_sum[2];

  TH1F * h_num_hit[2];

  TH1F *h_zed[2];

  TH2F *h_tof_de[2];
  
  TH2F *h_zed_zed;

  //parameter
  TArtBigRIPSParameters *bigripsparameters;
  //TArtDALIParameters *daliparameters;
  
  // calibration classes 
  TArtCalibPID *brcalib;
  TArtCalibIC *iccalib;
  TArtCalibPPAC *ppaccalib;
  TArtCalibPlastic *plasticcalib;

  //TArtCalibDALI *dalicalib;
  
  TArtRecoPID *recopid;

  TArtRIPS *rips3to5;
  TArtRIPS *rips5to7;
  TArtRIPS *rips8to9;
  TArtRIPS *rips9to11;

  TArtTOF *tof3to7;
  TArtTOF *tof8to11;

  TArtBeam *beam_br_35;
  TArtBeam *beam_br_57;
  TArtBeam *beam_zd_89;
  TArtBeam *beam_zd_911;

private:
  
public:
  virtual const char* ClassName() const;

  ClassDef(ShowF11IC,1);
};
#endif
