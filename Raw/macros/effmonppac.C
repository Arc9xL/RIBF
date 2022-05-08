void effmonppac_ini(Int_t runnum){
	TArtStoreManager * sman = TArtStoreManager::Instance();
	TArtEventStore *estore = new TArtEventStore();
	TArtCalibCoin *coin = new TArtCalibCoin();
	/////////////////////////////////////	
	estore->Open(0);
	//---------------------------------------------------------------------------------------------
	//estore->Open(Form("ridf/run%04d.ridf",runnum));
	//---------------------------------------------------------------------------------------------
	//BigRIPS Parameters
	TArtBigRIPSParameters *setup = TArtBigRIPSParameters::Instance();
	//setup->LoadParameter((char*)"db/BigRIPSPPAC.xml_camac_20141023");//BigRIPS CAMAC
	setup->LoadParameter((char*)"db/BigRIPSPPAC.xml");
	TArtCalibPID *mycalib= new TArtCalibPID();
	//-----------------------------------------------------------------------------------------
	TFile* f=new TFile(Form("run%04dmon.root",runnum),"RECREATE");
	//-----------------------------------------------------------------------------------------	
	ofstream out("effmonppac.dat",std::ios::app);

	Int_t fneve = 0;

	Double_t F3PPAC1A_X; TH1D *f31ax = new TH1D("f31ax","f31ax",400,-200,200);  
	Double_t F3PPAC1A_Y; TH1D *f31ay = new TH1D("f31ay","f31ay",400,-200,200);  
	Double_t F3PPAC1B_X; TH1D *f31bx = new TH1D("f31bx","f31bx",400,-200,200);  
	Double_t F3PPAC1B_Y; TH1D *f31by = new TH1D("f31by","f31by",400,-200,200);  
	Double_t F3PPAC2A_X; TH1D *f32ax = new TH1D("f32ax","f32ax",400,-200,200);  
	Double_t F3PPAC2A_Y; TH1D *f32ay = new TH1D("f32ay","f32ay",400,-200,200);  
	Double_t F3PPAC2B_X; TH1D *f32bx = new TH1D("f32bx","f32bx",400,-200,200);  
	Double_t F3PPAC2B_Y; TH1D *f32by = new TH1D("f32by","f32by",400,-200,200);  

	// F5 PPAC
	Double_t F5PPAC1A_X; TH1D *f51ax = new TH1D("f51ax","f51ax",400,-200,200);
	Double_t F5PPAC1A_Y; TH1D *f51ay = new TH1D("f51ay","f51ay",400,-200,200);
	Double_t F5PPAC1B_X; TH1D *f51bx = new TH1D("f51bx","f51bx",400,-200,200);
	Double_t F5PPAC1B_Y; TH1D *f51by = new TH1D("f51by","f51by",400,-200,200);
	Double_t F5PPAC2A_X; TH1D *f52ax = new TH1D("f52ax","f52ax",400,-200,200);
	Double_t F5PPAC2A_Y; TH1D *f52ay = new TH1D("f52ay","f52ay",400,-200,200);
	Double_t F5PPAC2B_X; TH1D *f52bx = new TH1D("f52bx","f52bx",400,-200,200);
	Double_t F5PPAC2B_Y; TH1D *f52by = new TH1D("f52by","f52by",400,-200,200);

	//F7PPAC
	Double_t F7PPAC1A_X; TH1D *f71ax = new TH1D("f71ax","f71ax",400,-200,200);
	Double_t F7PPAC1A_Y; TH1D *f71ay = new TH1D("f71ay","f71ay",400,-200,200);
	Double_t F7PPAC1B_X; TH1D *f71bx = new TH1D("f71bx","f71bx",400,-200,200);
	Double_t F7PPAC1B_Y; TH1D *f71by = new TH1D("f71by","f71by",400,-200,200);
	Double_t F7PPAC2A_X; TH1D *f72ax = new TH1D("f72ax","f72ax",400,-200,200);
	Double_t F7PPAC2A_Y; TH1D *f72ay = new TH1D("f72ay","f72ay",400,-200,200);
	Double_t F7PPAC2B_X; TH1D *f72bx = new TH1D("f72bx","f72bx",400,-200,200);
	Double_t F7PPAC2B_Y; TH1D *f72by = new TH1D("f72by","f72by",400,-200,200);

	//F8PPAC
	Double_t F8PPAC1A_X; TH1D *f81ax = new TH1D("f81ax","f81ax",400,-200,200);
	Double_t F8PPAC1A_Y; TH1D *f81ay = new TH1D("f81ay","f81ay",400,-200,200);
	Double_t F8PPAC1B_X; TH1D *f81bx = new TH1D("f81bx","f81bx",400,-200,200);
	Double_t F8PPAC1B_Y; TH1D *f81by = new TH1D("f81by","f81by",400,-200,200);
	Double_t F8PPAC2A_X; TH1D *f82ax = new TH1D("f82ax","f82ax",400,-200,200);
	Double_t F8PPAC2A_Y; TH1D *f82ay = new TH1D("f82ay","f82ay",400,-200,200);
	Double_t F8PPAC2B_X; TH1D *f82bx = new TH1D("f82bx","f82bx",400,-200,200);
	Double_t F8PPAC2B_Y; TH1D *f82by = new TH1D("f82by","f82by",400,-200,200);
	Double_t F8PPAC3A_X; TH1D *f83ax = new TH1D("f83ax","f83ax",400,-200,200);
	Double_t F8PPAC3A_Y; TH1D *f83ay = new TH1D("f83ay","f83ay",400,-200,200);
	Double_t F8PPAC3B_X; TH1D *f83bx = new TH1D("f83bx","f83bx",400,-200,200);
	Double_t F8PPAC3B_Y; TH1D *f83by = new TH1D("f83by","f83by",400,-200,200);

	//F9PPAC
	Double_t F9PPAC1A_X; TH1D *f91ax = new TH1D("f91ax","f91ax",400,-200,200);
	Double_t F9PPAC1A_Y; TH1D *f91ay = new TH1D("f91ay","f91ay",400,-200,200);
	Double_t F9PPAC1B_X; TH1D *f91bx = new TH1D("f91bx","f91bx",400,-200,200);
	Double_t F9PPAC1B_Y; TH1D *f91by = new TH1D("f91by","f91by",400,-200,200);
	Double_t F9PPAC2A_X; TH1D *f92ax = new TH1D("f92ax","f92ax",400,-200,200);
	Double_t F9PPAC2A_Y; TH1D *f92ay = new TH1D("f92ay","f92ay",400,-200,200);
	Double_t F9PPAC2B_X; TH1D *f92bx = new TH1D("f92bx","f92bx",400,-200,200);
	Double_t F9PPAC2B_Y; TH1D *f92by = new TH1D("f92by","f92by",400,-200,200);

	//F10PPAC
	Double_t F10PPAC1A_X; TH1D *f101ax = new TH1D("f101ax","f101ax",400,-200,200);
	Double_t F10PPAC1A_Y; TH1D *f101ay = new TH1D("f101ay","f101ay",400,-200,200);
	Double_t F10PPAC1B_X; TH1D *f101bx = new TH1D("f101bx","f101bx",400,-200,200);
	Double_t F10PPAC1B_Y; TH1D *f101by = new TH1D("f101by","f101by",400,-200,200);
	Double_t F10PPAC2A_X; TH1D *f102ax = new TH1D("f102ax","f102ax",400,-200,200);
	Double_t F10PPAC2A_Y; TH1D *f102ay = new TH1D("f102ay","f102ay",400,-200,200);
	Double_t F10PPAC2B_X; TH1D *f102bx = new TH1D("f102bx","f102bx",400,-200,200);
	Double_t F10PPAC2B_Y; TH1D *f102by = new TH1D("f102by","f102by",400,-200,200);

	//F11PPAC
	Double_t F11PPAC1A_X; TH1D *f111ax = new TH1D("f111ax","f111ax",400,-200,200);
	Double_t F11PPAC1A_Y; TH1D *f111ay = new TH1D("f111ay","f111ay",400,-200,200);
	Double_t F11PPAC1B_X; TH1D *f111bx = new TH1D("f111bx","f111bx",400,-200,200);
	Double_t F11PPAC1B_Y; TH1D *f111by = new TH1D("f111by","f111by",400,-200,200);
	Double_t F11PPAC2A_X; TH1D *f112ax = new TH1D("f112ax","f112ax",400,-200,200);
	Double_t F11PPAC2A_Y; TH1D *f112ay = new TH1D("f112ay","f112ay",400,-200,200);
	Double_t F11PPAC2B_X; TH1D *f112bx = new TH1D("f112bx","f112bx",400,-200,200);
	Double_t F11PPAC2B_Y; TH1D *f112by = new TH1D("f112by","f112by",400,-200,200);

	//Triggerbit 
	Int_t ntriggerbit = 0;// TH1D *f72by = new TH1D("htriggerbit","htriggerbit",400,-200,200);
	Int_t ftriggerbit = 0;

	TClonesArray * triggerbit_array = (TClonesArray *)estore ->GetEventInfoArray();
	TArtEventInfo *triggerinfo = (TArtEventInfo *)triggerbit_array -> At(0);

	TArtCalibPPAC *cppac = mycalib->GetCalibPPAC();
	TClonesArray *ppac_array = (TClonesArray *)sman->FindDataContainer("BigRIPSPPAC");
	//eventLoop
	int neve =0;
	while( estore -> GetNextEvent() && neve < 1000){
		if(neve%100==0){
			std::cout<<"\r event: "<<neve<<" / "<<10000<<" ("<<100.*neve/10000<<" %)"<<std::flush;
		} 

		mycalib->ReconstructData();
		//------------------------------------------------
		coin->ClearData();
		coin->LoadData();

		ftriggerbit = triggerinfo -> GetTriggerBit();
		for(Int_t i = 0; i < 7; i++){
			if ((ftriggerbit >> i) & 0x1)
				triggerbit = i+1;
		}
		if ((ftriggerbit >> 0) & 0x1) ntriggerbit++;

		ntriggerbit = neve;
		// F3 PPAC
		F3PPAC1A_X=-9999; F3PPAC1A_Y=-9999;
		F3PPAC1B_X=-9999; F3PPAC1B_Y=-9999;
		F3PPAC2A_X=-9999; F3PPAC2A_Y=-9999;
		F3PPAC2B_X=-9999; F3PPAC2B_Y=-9999;

		// F5 PPAC
		F5PPAC1A_X=-9999; F5PPAC1A_Y=-9999;
		F5PPAC1B_X=-9999; F5PPAC1B_Y=-9999;
		F5PPAC2A_X=-9999; F5PPAC2A_Y=-9999;
		F5PPAC2B_X=-9999; F5PPAC2B_Y=-9999;

		// F7 PPAC
		F7PPAC1A_X=-9999; F7PPAC1A_Y=-9999;
		F7PPAC1B_X=-9999; F7PPAC1B_Y=-9999;
		F7PPAC2A_X=-9999; F7PPAC2A_Y=-9999;
		F7PPAC2B_X=-9999; F7PPAC2B_Y=-9999;

		// F8 PPAC
		F8PPAC1A_X=-9999; F8PPAC1A_Y=-9999;
		F8PPAC1B_X=-9999; F8PPAC1B_Y=-9999;
		F8PPAC2A_X=-9999; F8PPAC2A_Y=-9999;
		F8PPAC2B_X=-9999; F8PPAC2B_Y=-9999;
		F8PPAC3A_X=-9999; F8PPAC3A_Y=-9999;
		F8PPAC3B_X=-9999; F8PPAC3B_Y=-9999;

		// F9 PPAC
		F9PPAC1A_X=-9999; F9PPAC1A_Y=-9999;
		F9PPAC1B_X=-9999; F9PPAC1B_Y=-9999;
		F9PPAC2A_X=-9999; F9PPAC2A_Y=-9999;
		F9PPAC2B_X=-9999; F9PPAC2B_Y=-9999;

		// F10 PPAC
		F10PPAC1A_X=-9999; F10PPAC1A_Y=-9999;
		F10PPAC1B_X=-9999; F10PPAC1B_Y=-9999;
		F10PPAC2A_X=-9999; F10PPAC2A_Y=-9999;
		F10PPAC2B_X=-9999; F10PPAC2B_Y=-9999;

		// F11 PPAC
		F11PPAC1A_X=-9999; F11PPAC1A_Y=-9999;
		F11PPAC1B_X=-9999; F11PPAC1B_Y=-9999;
		F11PPAC2A_X=-9999; F11PPAC2A_Y=-9999;
		F11PPAC2B_X=-9999; F11PPAC2B_Y=-9999;

		//PPAC /////////////////////////////////////////////////////////////////
		TArtPPAC *ppac;

		// F3 PPAC
		ppac = cppac->FindPPAC((char*)"F3PPAC-1A");
		if( ppac ){
			F3PPAC1A_X = ppac->GetX(); F3PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F3PPAC-1B");
		if( ppac ){
			F3PPAC1B_X = ppac->GetX(); F3PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F3PPAC-2A");
		if( ppac ){
			F3PPAC2A_X = ppac->GetX(); F3PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F3PPAC-2B");
		if( ppac ){
			F3PPAC2B_X = ppac->GetX(); F3PPAC2B_Y = ppac->GetY();
		} 
		// F5 PPAC
		ppac = cppac->FindPPAC((char*)"F5PPAC-1A");
		TArtPPACPara *parap = cppac->GetPPACPara(10);
		if( ppac ){
			F5PPAC1A_X = ppac->GetX(); F5PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F5PPAC-1B");
		parap = cppac->GetPPACPara(11);
		if( ppac ){
			F5PPAC1B_X = ppac->GetX(); F5PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F5PPAC-2A");
		parap = cppac->GetPPACPara(12);
		if( ppac ){
			F5PPAC2A_X = ppac->GetX(); F5PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F5PPAC-2B");
		parap = cppac->GetPPACPara(13);
		if( ppac ){
			F5PPAC2B_X = ppac->GetX(); F5PPAC2B_Y = ppac->GetY();
		}

		// F7 PPAC
		ppac = cppac->FindPPAC((char*)"F7PPAC-1A");
		if( ppac ){
			F7PPAC1A_X = ppac->GetX(); F7PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F7PPAC-1B");
		if( ppac ){
			F7PPAC1B_X = ppac->GetX(); F7PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F7PPAC-2A");
		if( ppac ){
			F7PPAC2A_X = ppac->GetX(); F7PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F7PPAC-2B");
		if( ppac ){
			F7PPAC2B_X = ppac->GetX(); F7PPAC2B_Y = ppac->GetY();
		}

		// F8 PPAC
		ppac = cppac->FindPPAC((char*)"F8PPAC-1A");
		if( ppac ){
			F8PPAC1A_X = ppac->GetX(); F8PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F8PPAC-1B");
		if( ppac ){
			F8PPAC1B_X = ppac->GetX(); F8PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F8PPAC-2A");
		if( ppac ){
			F8PPAC2A_X = ppac->GetX(); F8PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F8PPAC-2B");
		if( ppac ){
			F8PPAC2B_X = ppac->GetX(); F8PPAC2B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F8PPAC-3A");
		if( ppac ){
			F8PPAC3A_X = ppac->GetX(); F8PPAC3A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F8PPAC-3B");
		if( ppac ){
			F8PPAC3B_X = ppac->GetX(); F8PPAC3B_Y = ppac->GetY();
		}

		// F9 PPAC
		ppac = cppac->FindPPAC((char*)"F9PPAC-1A");
		if( ppac ){
			F9PPAC1A_X = ppac->GetX(); F9PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F9PPAC-1B");
		if( ppac ){
			F9PPAC1B_X = ppac->GetX(); F9PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F9PPAC-2A");
		if( ppac ){
			F9PPAC2A_X = ppac->GetX(); F9PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F9PPAC-2B");
		if( ppac ){
			F9PPAC2B_X = ppac->GetX(); F9PPAC2B_Y = ppac->GetY();
		}

		// F10 PPAC
		ppac = cppac->FindPPAC((char*)"F10PPAC-1A");
		if( ppac ){
			F10PPAC1A_X = ppac->GetX(); F10PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F10PPAC-1B");
		if( ppac ){
			F10PPAC1B_X = ppac->GetX(); F10PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F10PPAC-2A");
		if( ppac ){
			F10PPAC2A_X = ppac->GetX(); F10PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F10PPAC-2B");
		if( ppac ){
			F10PPAC2B_X = ppac->GetX(); F10PPAC2B_Y = ppac->GetY();
		}

		// F11 PPAC
		ppac = cppac->FindPPAC((char*)"F11PPAC-1A");
		if( ppac ){
			F11PPAC1A_X = ppac->GetX(); F11PPAC1A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F11PPAC-1B");
		if( ppac ){
			F11PPAC1B_X = ppac->GetX(); F11PPAC1B_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F11PPAC-2A");
		if( ppac ){
			F11PPAC2A_X = ppac->GetX(); F11PPAC2A_Y = ppac->GetY();
		}
		ppac = cppac->FindPPAC((char*)"F11PPAC-2B");
		if( ppac ){
			F11PPAC2B_X = ppac->GetX(); F11PPAC2B_Y = ppac->GetY();
		}

		if ((ftriggerbit >> 0) & 0x1){
			f31ax -> Fill(F3PPAC1A_X); f51ax -> Fill(F5PPAC1A_X); f71ax -> Fill(F7PPAC1A_X); f81ax -> Fill(F8PPAC1A_X);
			f31ay -> Fill(F3PPAC1A_Y); f51ay -> Fill(F5PPAC1A_Y); f71ay -> Fill(F7PPAC1A_Y); f81ay -> Fill(F8PPAC1A_Y);
			f31bx -> Fill(F3PPAC1B_X); f51bx -> Fill(F5PPAC1B_X); f71bx -> Fill(F7PPAC1B_X); f81bx -> Fill(F8PPAC1B_X);
			f31by -> Fill(F3PPAC1B_Y); f51by -> Fill(F5PPAC1B_Y); f71by -> Fill(F7PPAC1B_Y); f81by -> Fill(F8PPAC1B_Y);
			f32ax -> Fill(F3PPAC2A_X); f52ax -> Fill(F5PPAC2A_X); f72ax -> Fill(F7PPAC2A_X); f82ax -> Fill(F8PPAC2A_X);
			f32ay -> Fill(F3PPAC2A_Y); f52ay -> Fill(F5PPAC2A_Y); f72ay -> Fill(F7PPAC2A_Y); f82ay -> Fill(F8PPAC2A_Y);
			f32bx -> Fill(F3PPAC2B_X); f52bx -> Fill(F5PPAC2B_X); f72bx -> Fill(F7PPAC2B_X); f82bx -> Fill(F8PPAC2B_X);
			f32by -> Fill(F3PPAC2B_Y); f52by -> Fill(F5PPAC2B_Y); f72by -> Fill(F7PPAC2B_Y); f82by -> Fill(F8PPAC2B_Y);
			f83ax -> Fill(F8PPAC3A_X);
			f83ay -> Fill(F8PPAC3A_Y);
			f83bx -> Fill(F8PPAC3B_X);
			f83by -> Fill(F8PPAC3B_Y);
			f91ax -> Fill(F9PPAC1A_X); f101ax -> Fill(F10PPAC1A_X); f111ax -> Fill(F11PPAC1A_X);
			f91ay -> Fill(F9PPAC1A_Y); f101ay -> Fill(F10PPAC1A_Y); f111ay -> Fill(F11PPAC1A_Y);
			f91bx -> Fill(F9PPAC1B_X); f101bx -> Fill(F10PPAC1B_X); f111bx -> Fill(F11PPAC1B_X);
			f91by -> Fill(F9PPAC1B_Y); f101by -> Fill(F10PPAC1B_Y); f111by -> Fill(F11PPAC1B_Y);
			f92ax -> Fill(F9PPAC2A_X); f102ax -> Fill(F10PPAC2A_X); f112ax -> Fill(F11PPAC2A_X);
			f92ay -> Fill(F9PPAC2A_Y); f102ay -> Fill(F10PPAC2A_Y); f112ay -> Fill(F11PPAC2A_Y);
			f92bx -> Fill(F9PPAC2B_X); f102bx -> Fill(F10PPAC2B_X); f112bx -> Fill(F11PPAC2B_X);
			f92by -> Fill(F9PPAC2B_Y); f102by -> Fill(F10PPAC2B_Y); f112by -> Fill(F11PPAC2B_Y);

		}

		//------------------------------------------------
		estore->ClearData();
		mycalib->ClearData();
		++neve;
		//------------------------------------------------
	}
	Double_t eff31ax = f31ax -> Integral(); Double_t eff51ax = f51ax -> Integral(); Double_t eff71ax = f71ax -> Integral();
	Double_t eff31ay = f31ay -> Integral(); Double_t eff51ay = f51ay -> Integral(); Double_t eff71ay = f71ay -> Integral();
	Double_t eff31bx = f31bx -> Integral(); Double_t eff51bx = f51bx -> Integral(); Double_t eff71bx = f71bx -> Integral();
	Double_t eff31by = f31by -> Integral(); Double_t eff51by = f51by -> Integral(); Double_t eff71by = f71by -> Integral();
	Double_t eff32ax = f32ax -> Integral(); Double_t eff52ax = f52ax -> Integral(); Double_t eff72ax = f72ax -> Integral();
	Double_t eff32ay = f32ay -> Integral(); Double_t eff52ay = f52ay -> Integral(); Double_t eff72ay = f72ay -> Integral();
	Double_t eff32bx = f32bx -> Integral(); Double_t eff52bx = f52bx -> Integral(); Double_t eff72bx = f72bx -> Integral();
	Double_t eff32by = f32by -> Integral(); Double_t eff52by = f52by -> Integral(); Double_t eff72by = f72by -> Integral();

	Double_t eff81ax = f81ax -> Integral();
	Double_t eff81ay = f81ay -> Integral();
	Double_t eff81bx = f81bx -> Integral();
	Double_t eff81by = f81by -> Integral();
	Double_t eff82ax = f82ax -> Integral();
	Double_t eff82ay = f82ay -> Integral();
	Double_t eff82bx = f82bx -> Integral();
	Double_t eff82by = f82by -> Integral();
	Double_t eff83ax = f83ax -> Integral();
	Double_t eff83ay = f83ay -> Integral();
	Double_t eff83bx = f83bx -> Integral();
	Double_t eff83by = f83by -> Integral();

	Double_t eff91ax = f91ax -> Integral(); Double_t eff101ax = f101ax -> Integral(); Double_t eff111ax = f111ax -> Integral();
	Double_t eff91ay = f91ay -> Integral(); Double_t eff101ay = f101ay -> Integral(); Double_t eff111ay = f111ay -> Integral();
	Double_t eff91bx = f91bx -> Integral(); Double_t eff101bx = f101bx -> Integral(); Double_t eff111bx = f111bx -> Integral();
	Double_t eff91by = f91by -> Integral(); Double_t eff101by = f101by -> Integral(); Double_t eff111by = f111by -> Integral();
	Double_t eff92ax = f92ax -> Integral(); Double_t eff102ax = f102ax -> Integral(); Double_t eff112ax = f112ax -> Integral();
	Double_t eff92ay = f92ay -> Integral(); Double_t eff102ay = f102ay -> Integral(); Double_t eff112ay = f112ay -> Integral();
	Double_t eff92bx = f92bx -> Integral(); Double_t eff102bx = f102bx -> Integral(); Double_t eff112bx = f112bx -> Integral();
	Double_t eff92by = f92by -> Integral(); Double_t eff102by = f102by -> Integral(); Double_t eff112by = f112by -> Integral();

	TCanvas * c1 = new TCanvas("c1","c1",900,600);
	TLatex *m1 = new TLatex(0.01,0.95,Form("RUN#%04d PPAC Efficiency",runnum));
	m1 -> SetNDC();
	m1 -> SetTextSize(0.04);
	m1 -> Draw();
	TLatex *m2 = new TLatex(0.01,0.90,"Efficiency = N(FXPPAC1A_X)/N(Beam Trigger)");
	m2 -> SetNDC();
	m2 -> SetTextSize(0.04);
	m2 -> Draw();
	//cout << ntriggerbit << endl;
	//cout << eff31ax << endl;

	TLatex *e1  = new TLatex(0.01,0.86,Form("F3/1A/X = %1.5f",100*eff31ax/ntriggerbit)); e1 -> SetNDC(); e1 -> SetTextSize(0.03); e1 -> Draw();
	TLatex *e2  = new TLatex(0.01,0.83,Form("F3/1A/Y = %1.5f",100*eff31ay/ntriggerbit)); e2 -> SetNDC(); e2 -> SetTextSize(0.03); e2 -> Draw();
	TLatex *e3  = new TLatex(0.01,0.80,Form("F3/1B/X = %1.5f",100*eff31bx/ntriggerbit)); e3 -> SetNDC(); e3 -> SetTextSize(0.03); e3 -> Draw();
	TLatex *e4  = new TLatex(0.01,0.77,Form("F3/1B/Y = %1.5f",100*eff31by/ntriggerbit)); e4 -> SetNDC(); e4 -> SetTextSize(0.03); e4 -> Draw();
	TLatex *e5  = new TLatex(0.01,0.74,Form("F3/2A/X = %1.5f",100*eff32ax/ntriggerbit)); e5 -> SetNDC(); e5 -> SetTextSize(0.03); e5 -> Draw();
	TLatex *e6  = new TLatex(0.01,0.71,Form("F3/2A/Y = %1.5f",100*eff32ay/ntriggerbit)); e6 -> SetNDC(); e6 -> SetTextSize(0.03); e6 -> Draw();
	TLatex *e7  = new TLatex(0.01,0.68,Form("F3/2B/X = %1.5f",100*eff32bx/ntriggerbit)); e7 -> SetNDC(); e7 -> SetTextSize(0.03); e7 -> Draw();
	TLatex *e8  = new TLatex(0.01,0.65,Form("F3/2B/Y = %1.5f",100*eff32by/ntriggerbit)); e8 -> SetNDC(); e8 -> SetTextSize(0.03); e8 -> Draw();

	TLatex *e9  = new TLatex(0.18,0.86,Form("F5/1A/X = %1.5f",100*eff51ax/ntriggerbit)); e9  -> SetNDC(); e9  -> SetTextSize(0.03); e9  -> Draw();
	TLatex *e10 = new TLatex(0.18,0.83,Form("F5/1A/Y = %1.5f",100*eff51ay/ntriggerbit)); e10 -> SetNDC(); e10 -> SetTextSize(0.03); e10 -> Draw();
	TLatex *e11 = new TLatex(0.18,0.80,Form("F5/1B/X = %1.5f",100*eff51bx/ntriggerbit)); e11 -> SetNDC(); e11 -> SetTextSize(0.03); e11 -> Draw();
	TLatex *e12 = new TLatex(0.18,0.77,Form("F5/1B/Y = %1.5f",100*eff51by/ntriggerbit)); e12 -> SetNDC(); e12 -> SetTextSize(0.03); e12 -> Draw();
	TLatex *e13 = new TLatex(0.18,0.74,Form("F5/2A/X = %1.5f",100*eff52ax/ntriggerbit)); e13 -> SetNDC(); e13 -> SetTextSize(0.03); e13 -> Draw();
	TLatex *e14 = new TLatex(0.18,0.71,Form("F5/2A/Y = %1.5f",100*eff52ay/ntriggerbit)); e14 -> SetNDC(); e14 -> SetTextSize(0.03); e14 -> Draw();
	TLatex *e15 = new TLatex(0.18,0.68,Form("F5/2B/X = %1.5f",100*eff52bx/ntriggerbit)); e15 -> SetNDC(); e15 -> SetTextSize(0.03); e15 -> Draw();
	TLatex *e16 = new TLatex(0.18,0.65,Form("F5/2B/Y = %1.5f",100*eff52by/ntriggerbit)); e16 -> SetNDC(); e16 -> SetTextSize(0.03); e16 -> Draw();

	TLatex *e17 = new TLatex(0.35,0.86,Form("F7/1A/X = %1.5f",100*eff71ax/ntriggerbit)); e17 -> SetNDC(); e17 -> SetTextSize(0.03); e17 -> Draw();
	TLatex *e18 = new TLatex(0.35,0.83,Form("F7/1A/Y = %1.5f",100*eff71ay/ntriggerbit)); e18 -> SetNDC(); e18 -> SetTextSize(0.03); e18 -> Draw();
	TLatex *e19 = new TLatex(0.35,0.80,Form("F7/1B/X = %1.5f",100*eff71bx/ntriggerbit)); e19 -> SetNDC(); e19 -> SetTextSize(0.03); e19 -> Draw();
	TLatex *e20 = new TLatex(0.35,0.77,Form("F7/1B/Y = %1.5f",100*eff71by/ntriggerbit)); e20 -> SetNDC(); e20 -> SetTextSize(0.03); e20 -> Draw();
	TLatex *e21 = new TLatex(0.35,0.74,Form("F7/2A/X = %1.5f",100*eff72ax/ntriggerbit)); e21 -> SetNDC(); e21 -> SetTextSize(0.03); e21 -> Draw();
	TLatex *e22 = new TLatex(0.35,0.71,Form("F7/2A/Y = %1.5f",100*eff72ay/ntriggerbit)); e22 -> SetNDC(); e22 -> SetTextSize(0.03); e22 -> Draw();
	TLatex *e23 = new TLatex(0.35,0.68,Form("F7/2B/X = %1.5f",100*eff72bx/ntriggerbit)); e23 -> SetNDC(); e23 -> SetTextSize(0.03); e23 -> Draw();
	TLatex *e24 = new TLatex(0.35,0.65,Form("F7/2B/Y = %1.5f",100*eff72by/ntriggerbit)); e24 -> SetNDC(); e24 -> SetTextSize(0.03); e24 -> Draw();

	TLatex *e25 = new TLatex(0.52,0.86,Form("F8/1A/X = %1.5f",100*eff81ax/ntriggerbit)); e25 -> SetNDC(); e25 -> SetTextSize(0.03); e25 -> Draw();
	TLatex *e26 = new TLatex(0.52,0.83,Form("F8/1A/Y = %1.5f",100*eff81ay/ntriggerbit)); e26 -> SetNDC(); e26 -> SetTextSize(0.03); e26 -> Draw();
	TLatex *e27 = new TLatex(0.52,0.80,Form("F8/1B/X = %1.5f",100*eff81bx/ntriggerbit)); e27 -> SetNDC(); e27 -> SetTextSize(0.03); e27 -> Draw();
	TLatex *e28 = new TLatex(0.52,0.77,Form("F8/1B/Y = %1.5f",100*eff81by/ntriggerbit)); e28 -> SetNDC(); e28 -> SetTextSize(0.03); e28 -> Draw();
	TLatex *e29 = new TLatex(0.52,0.74,Form("F8/2A/X = %1.5f",100*eff82ax/ntriggerbit)); e29 -> SetNDC(); e29 -> SetTextSize(0.03); e29 -> Draw();
	TLatex *e30 = new TLatex(0.52,0.71,Form("F8/2A/Y = %1.5f",100*eff82ay/ntriggerbit)); e30 -> SetNDC(); e30 -> SetTextSize(0.03); e30 -> Draw();
	TLatex *e31 = new TLatex(0.52,0.68,Form("F8/2B/X = %1.5f",100*eff82bx/ntriggerbit)); e31 -> SetNDC(); e31 -> SetTextSize(0.03); e31 -> Draw();
	TLatex *e32 = new TLatex(0.52,0.65,Form("F8/2B/Y = %1.5f",100*eff82by/ntriggerbit)); e32 -> SetNDC(); e32 -> SetTextSize(0.03); e32 -> Draw();
	TLatex *e33 = new TLatex(0.52,0.62,Form("F8/3A/X = %1.5f",100*eff83ax/ntriggerbit)); e33 -> SetNDC(); e33 -> SetTextSize(0.03); e33 -> Draw();
	TLatex *e34 = new TLatex(0.52,0.59,Form("F8/3A/Y = %1.5f",100*eff83ay/ntriggerbit)); e34 -> SetNDC(); e34 -> SetTextSize(0.03); e34 -> Draw();
	TLatex *e35 = new TLatex(0.52,0.56,Form("F8/3B/X = %1.5f",100*eff83bx/ntriggerbit)); e35 -> SetNDC(); e35 -> SetTextSize(0.03); e35 -> Draw();
	TLatex *e36 = new TLatex(0.52,0.53,Form("F8/3B/Y = %1.5f",100*eff83by/ntriggerbit)); e36 -> SetNDC(); e36 -> SetTextSize(0.03); e36 -> Draw();

	TLatex *e37 = new TLatex(0.69,0.86,Form("F9/1A/X = %1.5f",100*eff91ax/ntriggerbit)); e37 -> SetNDC(); e37 -> SetTextSize(0.03); e37 -> Draw();
	TLatex *e38 = new TLatex(0.69,0.83,Form("F9/1A/Y = %1.5f",100*eff91ay/ntriggerbit)); e38 -> SetNDC(); e38 -> SetTextSize(0.03); e38 -> Draw();
	TLatex *e39 = new TLatex(0.69,0.80,Form("F9/1B/X = %1.5f",100*eff91bx/ntriggerbit)); e39 -> SetNDC(); e39 -> SetTextSize(0.03); e39 -> Draw();
	TLatex *e40 = new TLatex(0.69,0.77,Form("F9/1B/Y = %1.5f",100*eff91by/ntriggerbit)); e40 -> SetNDC(); e40 -> SetTextSize(0.03); e40 -> Draw();
	TLatex *e41 = new TLatex(0.69,0.74,Form("F9/2A/X = %1.5f",100*eff92ax/ntriggerbit)); e41 -> SetNDC(); e41 -> SetTextSize(0.03); e41 -> Draw();
	TLatex *e42 = new TLatex(0.69,0.71,Form("F9/2A/Y = %1.5f",100*eff92ay/ntriggerbit)); e42 -> SetNDC(); e42 -> SetTextSize(0.03); e42 -> Draw();
	TLatex *e43 = new TLatex(0.69,0.68,Form("F9/2B/X = %1.5f",100*eff92bx/ntriggerbit)); e43 -> SetNDC(); e43 -> SetTextSize(0.03); e43 -> Draw();
	TLatex *e44 = new TLatex(0.69,0.65,Form("F9/2B/Y = %1.5f",100*eff92by/ntriggerbit)); e44 -> SetNDC(); e44 -> SetTextSize(0.03); e44 -> Draw();

	TLatex *e45 = new TLatex(0.01,0.56,Form("F10/1A/X = %1.5f",100*eff101ax/ntriggerbit)); e45 -> SetNDC(); e45 -> SetTextSize(0.03); e45 -> Draw();
	TLatex *e46 = new TLatex(0.01,0.53,Form("F10/1A/Y = %1.5f",100*eff101ay/ntriggerbit)); e46 -> SetNDC(); e46 -> SetTextSize(0.03); e46 -> Draw();
	TLatex *e47 = new TLatex(0.01,0.50,Form("F10/1B/X = %1.5f",100*eff101bx/ntriggerbit)); e47 -> SetNDC(); e47 -> SetTextSize(0.03); e47 -> Draw();
	TLatex *e48 = new TLatex(0.01,0.47,Form("F10/1B/Y = %1.5f",100*eff101by/ntriggerbit)); e48 -> SetNDC(); e48 -> SetTextSize(0.03); e48 -> Draw();
	TLatex *e49 = new TLatex(0.01,0.44,Form("F10/2A/X = %1.5f",100*eff102ax/ntriggerbit)); e49 -> SetNDC(); e49 -> SetTextSize(0.03); e49 -> Draw();
	TLatex *e50 = new TLatex(0.01,0.41,Form("F10/2A/Y = %1.5f",100*eff102ay/ntriggerbit)); e50 -> SetNDC(); e50 -> SetTextSize(0.03); e50 -> Draw();
	TLatex *e51 = new TLatex(0.01,0.38,Form("F10/2B/X = %1.5f",100*eff102bx/ntriggerbit)); e51 -> SetNDC(); e51 -> SetTextSize(0.03); e51 -> Draw();
	TLatex *e52 = new TLatex(0.01,0.35,Form("F10/2B/Y = %1.5f",100*eff102by/ntriggerbit)); e52 -> SetNDC(); e52 -> SetTextSize(0.03); e52 -> Draw(); 

	TLatex *e53 = new TLatex(0.18,0.56,Form("F11/1A/X = %1.5f",100*eff111ax/ntriggerbit)); e53 -> SetNDC(); e53 -> SetTextSize(0.03); e53 -> Draw();
	TLatex *e54 = new TLatex(0.18,0.53,Form("F11/1A/Y = %1.5f",100*eff111ay/ntriggerbit)); e54 -> SetNDC(); e54 -> SetTextSize(0.03); e54 -> Draw();
	TLatex *e55 = new TLatex(0.18,0.50,Form("F11/1B/X = %1.5f",100*eff111bx/ntriggerbit)); e55 -> SetNDC(); e55 -> SetTextSize(0.03); e55 -> Draw();
	TLatex *e56 = new TLatex(0.18,0.47,Form("F11/1B/Y = %1.5f",100*eff111by/ntriggerbit)); e56 -> SetNDC(); e56 -> SetTextSize(0.03); e56 -> Draw();
	TLatex *e57 = new TLatex(0.18,0.44,Form("F11/2A/X = %1.5f",100*eff112ax/ntriggerbit)); e57 -> SetNDC(); e57 -> SetTextSize(0.03); e57 -> Draw();
	TLatex *e58 = new TLatex(0.18,0.41,Form("F11/2A/Y = %1.5f",100*eff112ay/ntriggerbit)); e58 -> SetNDC(); e58 -> SetTextSize(0.03); e58 -> Draw();
	TLatex *e59 = new TLatex(0.18,0.38,Form("F11/2B/X = %1.5f",100*eff112bx/ntriggerbit)); e59 -> SetNDC(); e59 -> SetTextSize(0.03); e59 -> Draw();
	TLatex *e60 = new TLatex(0.18,0.35,Form("F11/2B/Y = %1.5f",100*eff112by/ntriggerbit)); e60 -> SetNDC(); e60 -> SetTextSize(0.03); e60 -> Draw();

	c1 -> SaveAs("effmonppac.eps");

	out << runnum << " " << eff31ax << " " << eff71ax << " " << eff81ax << " " << eff91ax <<  " " << eff101ax << endl;
	out.close();

	f->Write();
}
