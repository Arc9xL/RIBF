#include "RIBF132Parameter.h"
#include <TROOT.h>
#include <TSystem.h>
#include <TDOMParser.h>
// #include </home/soumya/Documents/Products/root/include/TXMLNode.h>
#include <TXMLNode.h>

#include <TXMLParser.h>
#include <TObject.h>
#include <TString.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "PPACPara.h"
#include "PlasticPara.h"
#include "ICPara.h"
#include "FocalPlanePara.h"
#include "DALINaIPara.h"

#define PRINT_CHECK_PARAMETER_CC 1

static const int PLAQ = 2;
static const int PLAT = 3;
static const int ICE  = 4;
static const int NUM_IC_CHANNEL = 12;

RIBF132Parameter::RIBF132Parameter()
{
  Init();
}

RIBF132Parameter::~RIBF132Parameter()
{
  //
}

void RIBF132Parameter::Init(void){
  //init here if anything necessary
  for(int i=0; i<7; i++){ for(int j=0; j<4; j++){  ppac[i][j] = (PPACPara*)0 ;}}
  f7ic = (ICPara*)0;
  music1 = (ICPara*)0;
  music2 = (ICPara*)0;
  for(int i=0; i<8; i++){ pla[i] = (PlasticPara*)0 ; }
  for(int i=0; i<12; i++){ fp[i] = (FocalPlanePara*)0 ; }
  return ;
}

int RIBF132Parameter::AddPPACPara(TXMLNode *node){
  
  Int_t     id = -1;
  TString name;
  Int_t     fpl = 0;
  Double_t  a_ch2ns = 0, x1_ch2ns = 0, y1_ch2ns = 0, x2_ch2ns = 0, y2_ch2ns = 0;
  Double_t  xfactor = 0, yfactor = 0;
  Double_t  xoffset = 0, yoffset = 0;
  Double_t  xns_off = 0, yns_off = 0;
  Double_t  xpos_off = 0, ypos_off = 0;
  Double_t  xzpos = 0, yzpos = 0;
  Double_t  tdc_underflow = 0;
  Double_t  tdc_overflow = 4000;
  Double_t  txsum_min = 0, txsum_max = 999999., tysum_min = 0, tysum_max = 999999.;
  
  Int_t Tx1_fpl=0, Tx2_fpl=0, Ty1_fpl=0, Ty2_fpl=0, Ta_fpl=0;
  Int_t Qx1_fpl=0, Qx2_fpl=0, Qy1_fpl=0, Qy2_fpl=0, Qa_fpl=0;
  Int_t Tx1_geo, Tx1_ch, Tx2_geo, Tx2_ch, Ty1_geo, Ty1_ch, Ty2_geo, Ty2_ch, Ta_geo, Ta_ch;
  Int_t Qx1_geo, Qx1_ch, Qx2_geo, Qx2_ch, Qy1_geo, Qy1_ch, Qy2_geo, Qy2_ch, Qa_geo, Qa_ch;
  
  Bool_t findTDCoverflow = false;
  
  for ( ; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "ID") == 0)
        id = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "NAME") == 0)
        name = node->GetText();
      if (strcmp(node->GetNodeName(), "FPL") == 0)
        fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "a_ch2ns") == 0)
        a_ch2ns = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "x1_ch2ns") == 0)
        x1_ch2ns = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "y1_ch2ns") == 0)
        y1_ch2ns = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "x2_ch2ns") == 0)
        x2_ch2ns = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "y2_ch2ns") == 0)
        y2_ch2ns = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "xfactor") == 0)
        xfactor = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "yfactor") == 0)
        yfactor = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "xoffset") == 0)
        xoffset = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "yoffset") == 0)
        yoffset = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "xns_off") == 0)
        xns_off = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "yns_off") == 0)
        yns_off = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "xpos_off") == 0)
        xpos_off = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "ypos_off") == 0)
        ypos_off = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "xzpos") == 0)
        xzpos = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "yzpos") == 0)
        yzpos = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_underflow") == 0)
        tdc_underflow = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_overflow") == 0){
        tdc_overflow = (Double_t)atof(node->GetText());
        findTDCoverflow = true;
      }
      if (strcmp(node->GetNodeName(), "txsum_min") == 0)
        txsum_min = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "txsum_max") == 0)
        txsum_max = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tysum_min") == 0)
        tysum_min = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tysum_max") == 0)
        tysum_max = (Double_t)atof(node->GetText());
      
      
      if (strcmp(node->GetNodeName(), "Tx1_fpl") == 0)
        Tx1_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Tx1_geo") == 0)
        Tx1_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Tx1_ch") == 0)
        Tx1_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Tx2_fpl") == 0)
        Tx2_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Tx2_geo") == 0)
        Tx2_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Tx2_ch") == 0)
        Tx2_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty1_fpl") == 0)
        Ty1_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty1_geo") == 0)
        Ty1_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty1_ch") == 0)
        Ty1_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty2_fpl") == 0)
        Ty2_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty2_geo") == 0)
        Ty2_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ty2_ch") == 0)
        Ty2_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ta_fpl") == 0)
        Ta_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ta_geo") == 0)
        Ta_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Ta_ch") == 0)
        Ta_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx1_fpl") == 0)
        Qx1_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx1_geo") == 0)
        Qx1_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx1_ch") == 0)
        Qx1_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx2_fpl") == 0)
        Qx2_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx2_geo") == 0)
        Qx2_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qx2_ch") == 0)
        Qx2_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy1_fpl") == 0)
        Qy1_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy1_geo") == 0)
        Qy1_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy1_ch") == 0)
        Qy1_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy2_fpl") == 0)
        Qy2_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy2_geo") == 0)
        Qy2_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qy2_ch") == 0)
        Qy2_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qa_fpl") == 0)
        Qa_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qa_geo") == 0)
        Qa_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "Qa_ch") == 0)
        Qa_ch = atoi(node->GetText());
      
    }
  }
  
  if(!findTDCoverflow &&
     (63 == Tx1_fpl ||  63 == Tx2_fpl || 63 == Ty1_fpl || 63 == Ty2_fpl))
    tdc_overflow = 1000000; 
  
  //----------------
  // find i_ppac, j_ppac, skip from id, name etc.
  TString *nameppac[7][4];
  char nameppacfocalplane[7][64]={"F3PPAC", "F5PPAC", "F7PPAC", "F8PPAC", "F9PPAC", "F10PPAC", "F11PPAC"};
  char nameppactype[4][64]={"1A","1B","2A","2B"};
  for(int ii=0; ii<7; ii++){
    for(int jj=0; jj<4; jj++){
      nameppac[ii][jj] = new TString(Form("%s-%s",nameppacfocalplane[ii],nameppactype[jj]));
    }
  }
  
  int i_ppac;
  int j_ppac;
  int check_skip = 1;
  for(int ii=0; ii<7; ii++){
    for(int jj=0; jj<4; jj++){
      if (0==strcmp(nameppac[ii][jj]->Data(), name.Data())){
       i_ppac = ii;
       j_ppac = jj;
       check_skip = 0;
      }
    }
  }
  //----------------
  if(1==check_skip) {return -1;}
  
  if(PRINT_CHECK_PARAMETER_CC){
   std::cout << "---- AddPPACPara for name="<< name << ", id=" << id << " ----" <<std::endl;
  }
  if((PPACPara*)0 ==  ppac[i_ppac][j_ppac] ){
    ppac[i_ppac][j_ppac] = new PPACPara();
  }
  ppac[i_ppac][j_ppac]->SetPalameters(id, name, fpl, a_ch2ns, x1_ch2ns, y1_ch2ns, x2_ch2ns, y2_ch2ns, xfactor, yfactor, xoffset, yoffset, xns_off, yns_off, xpos_off, ypos_off, xzpos, yzpos, tdc_underflow, tdc_overflow, txsum_min, txsum_max, tysum_min, tysum_max);

  return 1;
}

int RIBF132Parameter::AddMUSICPara(TXMLNode *node){
  
  Int_t     id = -1;
  TString name;
  Int_t     det = ICE;
  Int_t     fpl = -1;
  Double_t  ch2mev_0 = 0, ch2mev_1 = 0;
  Double_t  zcoef_0 = 0, zcoef_1 = 0, zcoef_2 = 0;
  Double_t  ionpair = 0;
  Double_t pedestal[NUM_IC_CHANNEL];
  Int_t geo[NUM_IC_CHANNEL], ch[NUM_IC_CHANNEL];
  char dummyic[64];
  
  for(Int_t i=0;i<NUM_IC_CHANNEL;i++){
    pedestal[i] = 0;
  }
  
  for ( ; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "ID") == 0)
        id = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "NAME") == 0)
        name = node->GetText();
      if (strcmp(node->GetNodeName(), "FPL") == 0)
        fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "detectorid") == 0)
        det = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "ch2mev_0") == 0)
        ch2mev_0 = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "ch2mev_1") == 0)
        ch2mev_1 = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "zcoef_0") == 0)
        zcoef_0 = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "zcoef_1") == 0)
        zcoef_1 = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "zcoef_2") == 0)
        zcoef_2 = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "ionpair") == 0)
        ionpair = (Double_t)atof(node->GetText());
      
      for(Int_t i=0;i<NUM_IC_CHANNEL;i++){
        
        sprintf(dummyic,"pedestal%d",i);
        if (strcmp(node->GetNodeName(), dummyic) == 0)
          pedestal[i] = (Double_t)atof(node->GetText());
        
        sprintf(dummyic,"geo%d",i);
        if (strcmp(node->GetNodeName(), dummyic) == 0)
          geo[i] = atoi(node->GetText());
        
        sprintf(dummyic,"ch%d",i);
        if (strcmp(node->GetNodeName(), dummyic) == 0)
          ch[i] = atoi(node->GetText());
      }
      
    }
  }
  
  //----------------
  TString name_f7ic("F7IC");
  TString name_music1("F11IC");
  TString name_music2("F11IC_2");
  //----------------

  if(name_f7ic==name){
    if((ICPara*)0 ==  f7ic){
     f7ic = new ICPara();
    }
    if(PRINT_CHECK_PARAMETER_CC){
      std::cout << "---- AddMUSICPara for name="<< name << ", id=" << id << " ----" <<std::endl;
    }
    f7ic->SetParameters(id, name, fpl, ch2mev_0, ch2mev_1, zcoef_0, zcoef_1, zcoef_2, ionpair);
    f7ic->SetPedestal(pedestal);
  }
  
 if(name_music1==name){
    if((ICPara*)0 ==  music1){
      music1 = new ICPara();
    }
    if(PRINT_CHECK_PARAMETER_CC){
      std::cout << "---- AddMUSICPara for name="<< name << ", id=" << id << " ----" <<std::endl;
    }
    music1->SetParameters(id, name, fpl, ch2mev_0, ch2mev_1, zcoef_0, zcoef_1, zcoef_2, ionpair);
    music1->SetPedestal(pedestal);
  }

 if(name_music2==name){
    if((ICPara*)0 ==  music2){
      music2 = new ICPara();
    }
    if(PRINT_CHECK_PARAMETER_CC){
      std::cout << "---- AddMUSICPara for name="<< name << ", id=" << id << " ----" <<std::endl;
    }
    music2->SetParameters(id, name, fpl, ch2mev_0, ch2mev_1, zcoef_0, zcoef_1, zcoef_2, ionpair);
    music2->SetPedestal(pedestal);
  }

  return 1;
}
 
int RIBF132Parameter::AddPlasticPara(TXMLNode *node){
  
  Int_t     id = -1;
  TString name;
  Int_t     fpl = -1;
  Int_t     det_adc = PLAQ;
  Int_t     det_tdc = PLAT;
  Double_t  tcal_left = 0;
  Double_t  tcal_right = 0;
  Double_t  qped_left = 0;
  Double_t  qped_right = 0;
  Double_t  tslew_left_a = 0;
  Double_t  tslew_left_b = 0;
  Double_t  tslew_right_a = 0;
  Double_t  tslew_right_b = 0;
  Double_t  tdc_underflow = 0;
  Double_t  tdc_overflow = 4000;
  Double_t  zpos = 0;
  Int_t t_fpl=-1, t_det=-1;
  Int_t tleft_geo=-1, tleft_ch=-1, tright_geo=-1, tright_ch=-1;
  Int_t q_fpl=-1, q_det=-1;
  Int_t qleft_geo=-1, qleft_ch=-1, qright_geo=-1, qright_ch=-1;
  Bool_t findTDCoverflow = false;
  
  for ( ; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "ID") == 0)
        id = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "NAME") == 0)
        name = node->GetText();
      if (strcmp(node->GetNodeName(), "FPL") == 0)
        fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tcal_left") == 0)
        tcal_left = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tcal_right") == 0)
        tcal_right = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "qped_left") == 0)
        qped_left = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "qped_right") == 0)
        qped_right = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"tslew_left_a")==0)
        tslew_left_a = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"tslew_left_b")==0)
        tslew_left_b = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"tslew_right_a")==0)
        tslew_right_a = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"tslew_right_b")==0)
        tslew_right_b = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_underflow") == 0)
        tdc_underflow = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_overflow") == 0){
        tdc_overflow = (Double_t)atof(node->GetText());
        findTDCoverflow = true;
      }
      if (strcmp(node->GetNodeName(), "zpos") == 0)
        zpos = (Double_t)atof(node->GetText());
      
      if (strcmp(node->GetNodeName(), "t_fpl") == 0)
        t_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "t_det") == 0)
        t_det = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tleft_geo") == 0)
        tleft_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tleft_ch") == 0)
        tleft_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tright_geo") == 0)
        tright_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tright_ch") == 0)
        tright_ch = atoi(node->GetText());
      
      if (strcmp(node->GetNodeName(), "q_fpl") == 0)
        q_fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "q_det") == 0)
        q_det = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "qleft_geo") == 0)
        qleft_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "qleft_ch") == 0)
        qleft_ch = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "qright_geo") == 0)
        qright_geo = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "qright_ch") == 0)
        qright_ch = atoi(node->GetText());
      
      if (strcmp(node->GetNodeName(), "tleft_fpl") == 0)
        std::cout << "Please use t_fpl instead of tleft_fpl in xml file!" << std::endl;
      if (strcmp(node->GetNodeName(), "tright_fpl") == 0)
        std::cout << "Please use t_fpl instead of tright_fpl in xml file!" << std::endl;
      if (strcmp(node->GetNodeName(), "qleft_fpl") == 0)
         std::cout << "Please use q_fpl instead of qleft_fpl in xml file!" << std::endl;
      if (strcmp(node->GetNodeName(), "qright_fpl") == 0) 
        std::cout << "Please use q_fpl instead of qright_fpl in xml file!" << std::endl;
      
    }
  }
  
  if(!findTDCoverflow && 63 == t_fpl)
    tdc_overflow = 1000000;
  

  //----------------
  // find i_plastic skip from id, name etc.
  TString name_plastic[8];
  name_plastic[0] = "F3pl";
  name_plastic[1] = "F5pl";
  name_plastic[2] = "F7pl";
  name_plastic[3] = "F8pl";
  //  name_plastic[4] = "F11pl-1";
  //  name_plastic[5] = "F11pl-2";
  //  name_plastic[6] = "F11long";
  //  name_plastic[7] = "F11veto";
  name_plastic[4] = "F11pl";
  name_plastic[5] = "F11long";
  name_plastic[6] = "F11veto";
  name_plastic[7] = "F11pl-dummy";
  
  int check_skip = 1;
  int i_plastic;
  for(int itemp = 0; itemp <8; itemp++){
    if(name == name_plastic[itemp]){
      check_skip = 0;
      i_plastic = itemp;
    }
  }
  //----------------
  if(1==check_skip) {return -1;}
  
  if(PRINT_CHECK_PARAMETER_CC){
    std::cout << "---- AddPlasticPara for name="<< name << ", id=" << id << " ----" <<std::endl;
  }
  if((PlasticPara*)0 ==  pla[i_plastic]){
    pla[i_plastic] = new PlasticPara();
  }
  pla[i_plastic]->SetPalameters(id, name, fpl, tcal_left, tcal_right, qped_left, qped_right, tslew_left_a, tslew_left_b, tslew_right_a, tslew_right_b, tdc_underflow, tdc_overflow, zpos);
  

  return 1;
}

int RIBF132Parameter::AddFocalPlanePara(TXMLNode *node){
  
  Int_t     id = -1;
  Int_t     fpl = -1;
  Double_t  zpos = 0;
  
  for ( ; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "ID") == 0)
        id = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "FPL") == 0)
        fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "zpos") == 0)
        zpos = (Double_t)atof(node->GetText());
    }
  }
  //----------------
  int i_fpl;
  int check_skip=1;
  if(0<=fpl && fpl<=11){
    check_skip = 0;
    i_fpl = fpl;
  }
  //----------------
  if(1==check_skip) {return -1;}
  
  if(PRINT_CHECK_PARAMETER_CC){
    std::cout << "---- AddFocalPlanePara for id=" << id << ",  fpl="<< fpl << " ----" <<std::endl;
  }
  if((FocalPlanePara*)0 ==  fp[i_fpl]){
    fp[i_fpl] = new FocalPlanePara();
  }
  fp[i_fpl]->SetParameters(id,fpl,zpos);
  
  return 1;
}

/// ima koko
int RIBF132Parameter::AddDALINaIPara(TXMLNode *node){
  
  Int_t     id_1origin = -1;
  Int_t     id= -1;
  TString   detname;
  Int_t     fpl = -1;
  Int_t     layer = -1;
  Double_t  tcal = 0.0;
  Double_t  toff = 0.0;
  Double_t  qcal = 0.0;
  Double_t  qped = 0.0;
  Double_t theta = -9999.9; // angle w.r.t. target
  Double_t x_pos = -9999.9;
  Double_t y_pos = -9999.9;
  Double_t z_pos = -9999.9;
  Int_t    adc_geo = -1;
  Int_t    adc_ch = -1;
  Int_t    tdc_geo = -1;
  Int_t    tdc_ch = -1;
  
  for ( ; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "ID") == 0)
        id_1origin = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "NAME") == 0)
        detname = node->GetText();
      if (strcmp(node->GetNodeName(), "Id") == 0)
        id = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "FPL") == 0)
        fpl = atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "layer") == 0)
        layer = (Double_t)atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "theta") == 0)
        theta = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "x_pos") == 0)
        x_pos = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "y_pos") == 0)
        y_pos = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"z_pos")==0)
        z_pos = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"toff")==0)
        toff = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"tcal")==0)
        tcal = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(),"qped")==0)
        qped = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "qcal") == 0)
        qcal = (Double_t)atof(node->GetText());
      if (strcmp(node->GetNodeName(), "adc_geo") == 0)
        adc_geo = (Double_t)atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "adc_ch") == 0)
        adc_ch = (Double_t)atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_geo") == 0)
        tdc_geo = (Double_t)atoi(node->GetText());
      if (strcmp(node->GetNodeName(), "tdc_ch") == 0)
        tdc_ch = (Double_t)atoi(node->GetText());
    }
  }
  
  
  //----------------
  // find i_plastic skip from id, name etc.
  TString name_nai[188];
  for(int ii=0; ii<188; ii++){
    name_nai[ii] = Form("NaI%d",ii);
  }
  //  name_nai[0] = "NaI0";
  //  name_nai[1] = "NaI1";
  //  name_nai[2] = "NaI2";
  
  int check_skip = 1;
  int i_nai;
  for(int itemp = 0; itemp <188; itemp++){
    if(detname == name_nai[itemp]){
      check_skip = 0;
      i_nai = itemp;
    }
  }
  //----------------
  if(1==check_skip) {return -1;}
  
  if(PRINT_CHECK_PARAMETER_CC){
    std::cout << "---- AddDALINaIPara for name="<< detname << ", id_1origin=" << id_1origin << ", id=" << id << ", theta=" << theta << ", adc_geo/ch=" <<adc_geo <<"/"<<adc_ch<<  ", tdc_geo/ch=" <<tdc_geo <<"/"<<tdc_ch << " ----" <<std::endl;
  }
  if((DALINaIPara*)0 ==  nai[i_nai]){
    nai[i_nai] = new DALINaIPara();
  }
  nai[i_nai]->SetParameters(id_1origin, id, detname, fpl,layer, tcal, toff, qcal, qped, theta, x_pos, y_pos, z_pos,adc_geo,adc_ch,tdc_geo,tdc_ch);
  
  return 1;
}


bool RIBF132Parameter::LoadParameter(char *xmlfile)
{

  fprintf(stderr, "RIBF132Parameter: Load parameter from %s \n", xmlfile);
  TDOMParser *domParser = new TDOMParser();
  domParser->SetValidate(false);
  Int_t parsecode = domParser->ParseFile(xmlfile);
  if (parsecode < 0) {
    fprintf(stderr, "RIBF132Parameter: Error in Load parameter, code message = %s \n", domParser->GetParseCodeMessage(parsecode));
    return false;
  }
  TXMLNode * node = domParser->GetXMLDocument()->GetRootNode();
  ParseParaList(node->GetChildren());
  delete domParser;
  
  fprintf(stderr,"\n");
  return true;
}

void RIBF132Parameter::ParseParaList(TXMLNode *node) {
  for (; node; node = node->GetNextNode()) {
    if (node->GetNodeType() == TXMLNode::kXMLElementNode) { // Element Node
      if (strcmp(node->GetNodeName(), "BigRIPSPPAC") == 0)
        AddPPACPara(node->GetChildren());
      if (strcmp(node->GetNodeName(), "BigRIPSPlastic") == 0)
        AddPlasticPara(node->GetChildren());
      if (strcmp(node->GetNodeName(), "BigRIPSIC") == 0)
        AddMUSICPara(node->GetChildren());
      if (strcmp(node->GetNodeName(), "FocalPlane") == 0)
        AddFocalPlanePara(node->GetChildren());
      if (strcmp(node->GetNodeName(), "DALI") == 0)
        AddDALINaIPara(node->GetChildren());
    }
  }
  return;
}



