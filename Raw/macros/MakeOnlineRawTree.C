#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtRawEventObject.hh"

#include <iostream>

#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"

void MakeOnlineRawTree(){

  gSystem->Load("libanaroot.so");

  TArtStoreManager *sman = TArtStoreManager::Instance();
  
  TArtEventStore *estore = new TArtEventStore();
  estore->Open();  //for online

  TArtRawEventObject *rawevent = estore->GetRawEventObject();

  TTree *tree = new TTree("tree","tree");
  
  tree->Branch("rawdata",&rawevent);

  int neve = 0;
 
  cout<<"Starting loop."<<endl;

  while(estore->GetNextEvent()&&neve<2000){
    if(neve%1000==0) cout << "Event:" << neve << endl;

    tree->Fill();
    estore->ClearData();
    neve ++;
  }
}
