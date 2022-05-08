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
void stop_interrupt() {
  printf("keyboard interrupt\n");
  stoploop = true;
}

void ShowDALITDC() {

  gSystem->Load("libXMLParser.so");
  gSystem->Load("libanacore.so");

  TArtEventStore *estore = new TArtEventStore();
  TArtRawEventObject *rawevent = estore->GetRawEventObject();
  estore->Open();

  TArtDALIParameters *dpara = TArtDALIParameters::Instance();
  dpara->LoadParameter("db/DALI.xml");
  TArtCalibDALI *dalicalib= new TArtCalibDALI();


  TCanvas *cDALI = new TCanvas("DALI2","TDC all",1400,800);
  cDALI->Divide(1,3);

  TH2I *tdc1=new TH2I("TDC1","tdc(1190) geo=6",130,-0.5,129.5,500,0,20000); 
  TH2I *tdc2=new TH2I("TDC2","tdc(1190) geo=8",130,-0.5,129.5,500,0,20000); 
  TH2I *tdc3=new TH2I("TDC3","tdc(1190) geo=10",130,-0.5,129.5,500,0,20000); 
  
  cDALI->cd(1);
  tdc1->Draw("colz");
  cDALI->cd(2);
  tdc2->Draw("colz");
  cDALI->cd(3);
  tdc3->Draw("colz");
 
  cDALI->Modified();
  cDALI->Update();

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
      if(DALI==device&&DALIT==detector){
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
          if(geo==6)tdc1->Fill(ch,val);
          if(geo==8)tdc2->Fill(ch,val);
          if(geo==10)tdc3->Fill(ch,val);
	}
      } 
    }

    rawevent->Clear();
    neve ++;

    if(neve%10==0){
      //h1->Draw();
      //c1->Update();
      cDALI->cd(1);
      tdc1->Draw("colz");
      cDALI->cd(2);
      tdc2->Draw("colz");
      cDALI->cd(3);
      tdc3->Draw("colz");
    }
  }
}
