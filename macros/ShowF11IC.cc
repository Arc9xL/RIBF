#include "ShowF11IC.hh"

#include <iostream>
#include <signal.h>

#include "TArtAnaFile.hh"
#include "TArtAnaClock.hh"

#include "EWNum.hh"

#include "TArtIC.hh"
#include "TArtTOF.hh"
#include "TArtCore.hh"
#include "TArtStoreManager.hh"

#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"

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

ShowF11IC::ShowF11IC() : TArtAnaLoop(), bigripsparameters(0){
}

ShowF11IC::~ShowF11IC() {
}

void ShowF11IC::Construct() {
  
  cout<<"call constructor!!"<<endl; 
 
  sman = TArtStoreManager::Instance();

  tree = new TTree("tree","tree");

  //For Online
  cF11IC = new TCanvas("F11IC","F11IC",1500,900);
  cF11IC->Divide(4,4);

  h_adc[0] = new TH2F("F11IC1ADC","F11IC_1 ADC",10,0,10,8000,0,8000); 
  h_adc[1] = new TH2F("F11IC2ADC","F11IC_2 ADC",10,0,10,8000,0,8000); 

  h_tdc[0] = new TH2F("F11IC1TDC","F11IC_1 TDC",10,0,10,8000,0,2800000); 
  h_tdc[1] = new TH2F("F11IC2TDC","F11IC_2 TDC",10,0,10,8000,0,2800000); 
  h_tdc_offseted[0] = new TH2F("F11IC1TDC_off","F11IC_1 TDC offseted",10,0,10,8000,-80000,80000); 
  h_tdc_offseted[1] = new TH2F("F11IC2TDC_off","F11IC_2 TDC offseted",10,0,10,8000,-80000,80000); 

  h_adc_sq_sum[0] = new TH1F("F11IC1ADCSQSUM","F11IC_1 ADC SQ SUM",1000,0,8000); 
  h_adc_sq_sum[1] = new TH1F("F11IC2ADCSQSUM","F11IC_2 ADC SQ SUM",1000,0,8000); 

  h_de_sq_sum[0] = new TH1F("F11IC1DESQSUM","F11IC_1 DE SQ SUM",1000,0,3000); 
  h_de_sq_sum[1] = new TH1F("F11IC2DESQSUM","F11IC_2 DE SQ SUM",1000,0,3000); 
  
  h_de_av_sum[0] = new TH1F("F11IC1DEAVSUM","F11IC_1 DE AV SUM",1000,0,3000); 
  h_de_av_sum[1] = new TH1F("F11IC2DEAVSUM","F11IC_2 DE AV SUM",1000,0,3000); 

  h_num_hit[0] = new TH1F("F11IC1NumHit","F11IC_1 Num Hit",10,0,10); 
  h_num_hit[1] = new TH1F("F11IC2NumHit","F11IC_2 Num Hit",10,0,10); 

  h_zed[0] = new TH1F("F11IC1Zed","F11ICZed_1",1000,0,100); 
  h_zed[1] = new TH1F("F11IC2Zed","F11ICZed_2",1000,0,100); 

  h_tof_de[0] = new TH2F("F11TOFdE1","ZDTOF dE_1",500,0,500,200,0,2000); 
  h_tof_de[1] = new TH2F("F11TOFdE2","ZDTOF dE_2",500,0,500,200,0,2000); 

  h_zed_zed = new TH2F("IC2vsIC1Zed","IC_2 vs IC_1 Zed",500,0,100,500,0,100); 

  bigripsparameters  = TArtBigRIPSParameters::Instance();
  bigripsparameters->LoadParameter("db/BigRIPSPPAC.xml");
  bigripsparameters->LoadParameter("db/BigRIPSPlastic.xml");
  bigripsparameters->LoadParameter("db/BigRIPSIC.xml");
  bigripsparameters->LoadParameter("db/FocalPlane.xml");
  bigripsparameters->SetFocusPosOffset(8,138.5);

  brcalib = new TArtCalibPID();
  
  iccalib = brcalib->GetCalibIC();
  plasticcalib = brcalib->GetCalibPlastic();

  std::cout << "Defining bigrips parameters" << std::endl;
  recopid = new TArtRecoPID();
//  rips3to5 = recopid->DefineNewRIPS(3,5,"matrix/mat1.mat",5.45); // F3 - F5
//  rips5to7 = recopid->DefineNewRIPS(5,7,"matrix/mat2.mat",4.665); // F5 - F7
//  rips8to9 = recopid->DefineNewRIPS(8,9,"matrix/F8F9_LargeAccAchr.mat",3.831); // F8 - F9
// rips9to11 = recopid->DefineNewRIPS(9,11,"matrix/F9F11_LargeAccAchr.mat",3.805); // F9 - F11  

// modified by Kasia, 2015-04-06
  rips3to5 = recopid->DefineNewRIPS(3,5,"matrix/mat1.mat","D3"); // F3 - F5
  rips5to7 = recopid->DefineNewRIPS(5,7,"matrix/mat2.mat","D5"); // F5 - F7
  rips8to9 = recopid->DefineNewRIPS(8,9,"matrix/F8F9_LargeAccAchr.mat","D7"); // F8 - F9
  rips9to11 = recopid->DefineNewRIPS(9,11,"matrix/F9F11_LargeAccAchr.mat","D8"); // F9 - F11 
  
  // Reconstruction of TOF DefineNewTOF(fisrt plane, second plane, time offset)
  tof3to7  = recopid->DefineNewTOF("F3pl","F7pl",302,5); // F3 - F7
  tof8to11 = recopid->DefineNewTOF("F8pl","F11pl-1",-749.2,9); // F8 - F11
  
  // Reconstruction of IC observables for ID
  //beam_br_37 = recopid->DefineNewBeam(rips3to5,rips5to7,tof3to7,"F7IC");
  beam_br_35 = recopid->DefineNewBeam(rips3to5,rips5to7,tof3to7,"F7IC");
  beam_br_57 = recopid->DefineNewBeam(rips5to7,tof3to7,"F7IC");   
  beam_zd_89 = recopid->DefineNewBeam(rips8to9,tof8to11,"F11IC");
  beam_zd_911 = recopid->DefineNewBeam(rips9to11,tof8to11,"F11IC");
 
  // define data nodes which are supposed to be dumped to tree 
  TClonesArray *info_array = (TClonesArray *)sman->FindDataContainer("EventInfo");
  //std::cout<<info_array->GetName()<<std::endl;
  //tree->Branch(info_array->GetName(),&info_array);
  
  TClonesArray *beam_array = 
    (TClonesArray *)sman->FindDataContainer("BigRIPSBeam");	
  std::cout<<beam_array->GetName()<<std::endl;     
  tree->Branch(beam_array->GetName(),&beam_array); 

  TClonesArray * ic_array = 
    (TClonesArray *)sman->FindDataContainer("BigRIPSIC");
  tree->Branch(ic_array->GetName(),&ic_array);


   neve=0; 
}

void ShowF11IC::Calculate()  {
  //cout<<"call Calculate()"<<endl;
  signal(SIGINT,stop_interrupt); // CTRL + C , interrupt

  TArtRawEventObject *rawevent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");

  int id = 0;
  int eventnum = rawevent->GetEventNumber();
   
  brcalib->ReconstructData();
  recopid->ReconstructData();
    
  tree->Fill();
  neve ++;

  //if(neve%1000==0)
  //  std::cout << "event: " << neve << std::endl;
  double tdc[16];
  double timeref=-999999;
  for(int i=0;i<16;i++) tdc[i]=-9999999;
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
	if(ch<16) tdc[ch]=val;
	if(ch==31) timeref=val;
      }
    }
  }
  for(int i=0;i<16;i++){
    if(i<8)
      h_tdc[0]->Fill(i,tdc[i]);
    else
      h_tdc[1]->Fill(i-8,tdc[i]);

    if(timeref>0){
      if(i<8)
	h_tdc_offseted[0]->Fill(i,tdc[i]-timeref);
      else
	h_tdc_offseted[1]->Fill(i-8,tdc[i]-timeref);      
    }
  }


  double Zet1=beam_zd_911->GetZet();
  double Zet2;//calc
  h_zed[0]->Fill(Zet1);
  h_zed[1]->Fill(Zet2);
 
  h_zed_zed->Fill(Zet1,Zet2);

  TArtIC *ic;
  
  char *name_ic[2]={"F11IC","F11IC_2"};
  
  for(int i =0;i<2;i++){
    ic = iccalib->FindIC((char*)name_ic[i]);
  
    if(ic){ 
      for(int j=0;j<10;j++){
        h_adc[i]->Fill(j,ic->GetRawADC(j));
      }
      h_adc_sq_sum[i]->Fill(ic->GetRawADCSqSum());
      h_de_sq_sum[i]->Fill(ic->GetEnergySqSum());
      h_num_hit[i]->Fill(ic->GetNumHit());
      if(i==0)
        h_tof_de[0]->Fill(tof8to11->GetTOF(),ic->GetEnergySqSum());
      if(i==1)
        h_tof_de[1]->Fill(tof8to11->GetTOF(),ic->GetEnergySqSum());
    }
  }

  //For monitoring
  if(neve%200==0){

    cF11IC->cd(1);
    h_adc[0]->Draw("colz");

    cF11IC->cd(2);
    h_adc_sq_sum[0]->Draw();
    
    cF11IC->cd(3);
    h_num_hit[0]->Draw();

    cF11IC->cd(4);
    h_zed[0]->Draw();

    cF11IC->cd(5);
    h_tof_de[0]->Draw("colz");

    cF11IC->cd(6);
    h_tdc[0]->Draw("colz");

    cF11IC->cd(7);
    h_tdc_offseted[0]->Draw("colz");
    
    cF11IC->cd(9);
    h_adc[1]->Draw("colz");
    
    cF11IC->cd(10);
    h_adc_sq_sum[1]->Draw();
    
    cF11IC->cd(11);
    h_num_hit[1]->Draw();

    cF11IC->cd(12);
    h_zed[1]->Draw();

    cF11IC->cd(13);
    h_tof_de[1]->Draw("colz");

    cF11IC->cd(14);
    h_tdc[0]->Draw("colz");

    cF11IC->cd(15);
    h_tdc_offseted[0]->Draw("colz");
    
    cF11IC->cd(16);
    h_zed_zed->Draw("colz");

    cF11IC->Update();
  }
  
  //********************* Clear *****************
  brcalib->ClearData();
  recopid->ClearData();
  rawevent->Clear();
}

void ShowF11IC::Destruct()  {
cout<<"call Destruct() !!" <<endl;
}

const char* ShowF11IC::ClassName() const  {
  return "ShowF11IC";
}
