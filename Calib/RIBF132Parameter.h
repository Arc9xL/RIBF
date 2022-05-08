#ifndef  RIBF132Parameter_H
#define  RIBF132Parameter_H
#include <iostream>
#include <TMath.h>
#include <TROOT.h>
#include <TList.h>
#include <TXMLNode.h>
#include <TXMLParser.h>
#include <TDOMParser.h>
#include <TObject.h>
#include <TString.h>
#include "DALINaIPara.h"
#include "PPACPara.h"
#include "PlasticPara.h"
#include "ICPara.h"
#include "FocalPlanePara.h"

class RIBF132Parameter
{
public:
  RIBF132Parameter();
  ~RIBF132Parameter();
  void Init(void);
  bool LoadParameter(char*);
  void ParseParaList(TXMLNode*);
  int AddPPACPara(TXMLNode*);
  int AddPlasticPara(TXMLNode*);
  int AddMUSICPara(TXMLNode*);
  int AddFocalPlanePara(TXMLNode*);
  int AddDALINaIPara(TXMLNode*);
  
  //---------list of parameters-----
  double dummy;
  PPACPara *ppac[7][4];
  ICPara   *f7ic;
  ICPara   *music1;
  ICPara   *music2;
  PlasticPara *pla[8];
  FocalPlanePara *fp[12];
  DALINaIPara  *nai[188];
  //--------------------------------
  double platdcb3f_ch2ns;
  double pla_twcoeff[7][2][2];
  double plaqdc_pedestal[7][2];

  double f7icadc_gain[6];
  double f7icadc_pedestal[6];
  double f11icadc_gain[2][8];
  double f11icadc_pedestal[2][8];
  double f11ictdc_factor[2][8];
  double f11ictdc_offset[2][8];
  double f11iczposF11ref[2][8];

  double zet7_coeff1;
  double zet7_coeff2;//now not used
  double zet7_coeff3;//now not used
  double zet11_coeff1;
  double zet11_coeff2;
  double zet11_coeff3;
  
  //--------------------
  // tof offset
  double offset37_default;
  double offset811_default;
  double clight;
  double length37;
  double length35;
  double length57;
  double length811;
  double length89;
  double length911;

  double offset78_default;
  double length78;
  //-------------------------
  // dali
  double dali_adc_factor[186];
  double dali_adc_offset[186];
  double dali_time_offset[186];
  double dali_time_sigma[186];
  
};
#endif

