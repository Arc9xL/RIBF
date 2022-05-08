#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtDALIParameters.hh"
#include "TArtCalibDALI.hh"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "segidlist.h"

// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void stop_interrupt()
{
  printf("keyboard interrupt\n");
  stoploop = true;
}

void ShowDALIADC()
//int main(int argc, char *argv[])
{

  gSystem->Load("libXMLParser.so");
  gSystem->Load("libanacore.so");

  TArtEventStore *estore = new TArtEventStore();
  TArtRawEventObject *rawevent = estore->GetRawEventObject();
  estore->Open();

  TArtDALIParameters *dpara = TArtDALIParameters::Instance();
  dpara->LoadParameter("db/DALI.xml");
  TArtCalibDALI *dalicalib= new TArtCalibDALI();

//  TCanvas *c1 = new TCanvas("c1","ADC",700,500);
//  c1->Draw();
//  TH2F* h1 = new TH2F("module","module",50,-0.5,49.5,50,-0.5,49.5);
//  h1->Draw();
//  c1->Modified();
//  c1->Update();

  TCanvas *cDALI = new TCanvas("DALI2","ADC all",1400,800);
  cDALI->Divide(3,3);
  TH2I *adc1=new TH2I("adc1","adc(V785) geo=11",33,-0.5,33.5,512,0,8096); 
  TH2I *adc2=new TH2I("adc2","adc(V785) geo=12",33,-0.5,33.5,512,0,8096); 
  TH2I *adc3=new TH2I("adc3","adc(V785) geo=13",33,-0.5,33.5,512,0,8096); 
  TH2I *adc4=new TH2I("adc4","adc(V785) geo=14",33,-0.5,33.5,512,0,8096); 
  TH2I *adc5=new TH2I("adc5","adc(V785) geo=15",33,-0.5,33.5,512,0,8096); 
  TH2I *adc6=new TH2I("adc6","adc(V785) geo=16",33,-0.5,33.5,512,0,8096); 
  TH2I *adc7=new TH2I("adc7","adc(V785) geo=17",33,-0.5,33.5,512,0,8096); 

  cDALI->cd(1);
  adc1->Draw("colz");
  cDALI->cd(2);
  adc2->Draw("colz");
  cDALI->cd(3);
  adc3->Draw("colz");
  cDALI->cd(4);
  adc4->Draw("colz");
  cDALI->cd(5);
  adc5->Draw("colz");
  cDALI->cd(6);
  adc6->Draw("colz");
  cDALI->cd(7);
  adc7->Draw("colz");
  
  cDALI->Modified();
  cDALI->Update();

  //dali calib
  //TTree *tree = new TTree("tree","tree");
  // define data nodes which are supposed to be dumped to tree 
  //TClonesArray * info_array = (TClonesArray *)sman->FindDataContainer("EventInfo");
  //std::cout<<info_array->GetName()<<std::endl;
  //tree->Branch(info_array->GetName(),&info_array);
  //TClonesArray * dali_array=
  //   (TClonesArray *)sman->FindDataContainer("DALINaI");
  //tree->Branch(dali_array->GetName(),&dali_array);

  int neve = 0;
  while(estore->GetNextEvent()){
    for(int i=0;i<rawevent->GetNumSeg();i++){
      TArtRawSegmentObject *seg = rawevent->GetSegment(i);
      int detid = seg->GetDetector();
      int modid = seg->GetModule();
      //h1->Fill(detid,modid);
      //add by Shiga
      int device = seg->GetDevice();
      int fp = seg->GetFP();
      int detector = seg->GetDetector();
      int module = seg->GetModule();
      if(DALI==device&&DALIA==detector){
	//cout << "    seg:"<< i <<" dev:"<< device 
	//     << " fp:"<<fp<< " det:"<<detector<< " mod:"<<module
	//     << " #data=" << seg->GetNumData() << endl;
	for(int j=0;j<seg->GetNumData();j++){
	  TArtRawDataObject *d = seg->GetData(j);
	  int geo = d->GetGeo();
	  int ch = d->GetCh();
	  unsigned int val = d->GetVal();
	  //cout << "       geo:" << geo 
	  //     << " ch:" << ch << " val:" << val << endl;
	  //ntp->Fill((float)geo,(float)ch,(float)val);

          //fill data
          if(geo==11)adc1->Fill(ch,val);
          if(geo==12)adc2->Fill(ch,val);
          if(geo==13)adc3->Fill(ch,val);
          if(geo==14)adc4->Fill(ch,val);
          if(geo==15)adc5->Fill(ch,val);
          if(geo==16)adc6->Fill(ch,val);
          if(geo==17)adc7->Fill(ch,val);
	}
      } 
    }

    rawevent->Clear();
    neve ++;

    if(neve%100==0){
      //h1->Draw();
      //c1->Update();
      cDALI->cd(1);
      adc1->Draw("colz");
      cDALI->cd(2);
      adc2->Draw("colz");
      cDALI->cd(3);
      adc3->Draw("colz");
      cDALI->cd(4);
      adc4->Draw("colz");
      cDALI->cd(5);
      adc5->Draw("colz");
      cDALI->cd(6);
      adc6->Draw("colz");
      cDALI->cd(7);
      adc7->Draw("colz");
      cDALI->Update();
    }
  }
}
