#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtMINOSParameters.hh"
#include "TArtCalibMINOS.hh"
#include "TArtAnalyzedMINOS.hh"
#include "TArtTrackMINOS.hh"
#include "TArtVertexMINOS.hh"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"

void MakeMINOSTree(char *infile, char *outfile="minos.root"){

  //gSystem->Load("libanaroot.so");
  //gSystem->Load("libanaminos.so");
  //gSystem->Load("libXMLParser.so");

  TArtStoreManager *sman = TArtStoreManager::Instance();

  TArtMINOSParameters *setup = new TArtMINOSParameters("MINOSParameters","MINOSParameters");
  setup->LoadParameters("./db/MINOS.xml");
  //setup->PrintListOfMINOSPara();
  
  TArtEventStore *estore = new TArtEventStore();
  estore->Open(infile);
  TArtRawEventObject *rawevent = estore->GetRawEventObject();

  TArtCalibMINOS *CalibMINOS = new TArtCalibMINOS();
 
  TArtAnalyzedMINOS *AnalyzedMINOS = new TArtAnalyzedMINOS(CalibMINOS);
  //TClonesArray fAnalyzedMINOSArray;
  //fAnalyzedMINOSArray.SetClass("TArtAnalyzedMINOSData");
  TClonesArray * fAnalyzedMINOSArray = (TClonesArray *)sman->FindDataContainer("AnalyzedMINOS");
                                                                                
  TArtTrackMINOS *TrackMINOS = new TArtTrackMINOS();
  //TClonesArray fTrackMINOSArray;
  //fTrackMINOSArray.SetClass("TArtTrackMINOSData");
  TClonesArray * fTrackMINOSArray = (TClonesArray *)sman->FindDataContainer("TrackMINOS");

  TArtVertexMINOS *VertexMINOS = new TArtVertexMINOS();
  Double_t Vertex[3];

  TFile *fout = new TFile(outfile,"RECREATE");
  TTree * tree = new TTree("tree","ridf tree");
  //  sman->RegistDataToTree(tree);

  tree->Branch("rawdata",&rawevent);
  //tree->Branch("calibdata",CalibMINOS);
  tree->Branch("analyzeddata",&fAnalyzedMINOSArray);
  tree->Branch("trackdata",&fTrackMINOSArray);
  tree->Branch("Vertex",Vertex,"Vertex[3]/D");

printf("good before\n");

  int neve = 0;

  //  estore->LoadMapConfig("conf/mapper.conf");  
 
  while(estore->GetNextEvent()&&neve<50000){
    if(neve%100==0) cout << "Event:" << neve << endl;

    //Calibration
    CalibMINOS->ClearData();
    CalibMINOS->ReconstructData();
    
    /*
    AnalyzedMINOS->ClearData();
    AnalyzedMINOS->ReconstructData(); 
    fAnalyzedMINOSArray=AnalyzedMINOS->GetAnalyzedMINOSArray();
    
    
    //Tracks
    TrackMINOS->ClearData();
    TrackMINOS->ReconstructData();
    fTrackMINOSArray=TrackMINOS->GetTrackMINOSArray();
    
    //Vertex
    VertexMINOS->ClearData();
    VertexMINOS->ReconstructVertex();
    Vertex[0]=VertexMINOS->GetXv();
    Vertex[1]=VertexMINOS->GetYv();
    Vertex[2]=VertexMINOS->GetZv();
    */

    //cout<<"Fill the tree..."<<endl;
    //tree->Fill();
    //cout<<"... tree filled."<<endl;
    
    //cout<<"Clear data..."<<endl;
    estore->ClearData();
    
    //cout<<"Implementation of event number..."<<endl;
    neve ++;
    //cout<<"... event number implemented."<<endl;
  }
  
  cout<<"Write..."<<endl;
  fout->Write();
  cout<<"Close..."<<endl;
  fout->Close();
  cout<<"Done!"<<endl;

}
