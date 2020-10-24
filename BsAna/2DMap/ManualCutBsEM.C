#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include <iostream>
#include <fstream>




//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void ManualCutBsEM(int CentMin, int CentMax, int TwoShot){



	TString FolderName = "NoTnP";






	TString FileName = "../../../../BsBPInputSamples/BsData.root";





	TFile * fin = new TFile(FileName.Data());

	TTree * ntphi = (TTree * ) fin->Get("Bfinder/ntphi");
	TTree * BDT1 = (TTree * ) fin->Get("BDT_pt_5_10");
	TTree * BDT2 = (TTree * ) fin->Get("BDT_pt_10_15");
	TTree * BDT3 = (TTree * ) fin->Get("BDT_pt_15_20");
	TTree * BDT4 = (TTree * ) fin->Get("BDT_pt_20_50");
	TTree * ntHi = (TTree * ) fin->Get("hiEvtAnalyzer/HiTree");
	TTree * ntSkim = (TTree * ) fin->Get("skimanalysis/HltTree");
	TTree * ntHlt = (TTree *) fin->Get("hltanalysis/HltTree");






	TF1 * func;

	if(CentMin == 0 && CentMax == 90) func = new TF1("func","1/0.144708+TMath::Exp(-1.035696*(x-15.321432))+TMath::Exp(-0.204131*(x-30.289313))",5,50);

	if(CentMin == 0 && CentMax == 30) func = new TF1("func","1/0.131733+TMath::Exp(-1.051514*(x-15.468517))+TMath::Exp(-0.204272*(x-31.002324))",5,50);

//	if(CentMin == 30 && CentMax == 40) func = new TF1("func","1/0.131733+TMath::Exp(-1.051514*(x-15.468517))+TMath::Exp(-0.204272*(x-31.002324))",5,50);
//	if(CentMin == 40 && CentMax == 90) func = new TF1("func","1/0.131733+TMath::Exp(-1.051514*(x-15.468517))+TMath::Exp(-0.204272*(x-31.002324))",5,50);


	if(CentMin == 30 && CentMax == 90) func = new TF1("func","1/0.204307+TMath::Exp(-1.041731*(x-14.608514))+TMath::Exp(-0.206513*(x-27.599694))",5,50);





	const int NCand = 20000;


	int run;
	int lumi;
	int evt;
	int hiBin;
	Float_t PVz;
	Int_t pclusterCompatibilityFilter;
	Int_t pprimaryVertexFilter;
	Int_t phfCoincFilter2Th4;


	//TFile * finEff = new TFile(Form("CheckSystNuno/%s/EffFine_%d_%d.root",FolderName.Data(),CentMin,CentMax));
	TFile * finEff = new TFile(Form("WeightedMap/EffFine_%d_%d.root",CentMin,CentMax));
	finEff->cd();

	/*
	TH2D * EffBptBy = (TH2D *) finEff->Get("EffBptBy");
	TH2D * EffBptByInv = (TH2D *) finEff->Get("EffBptByInv");
	TH2D * EffBptByInvErr = (TH2D *) finEff->Get("EffBptByInvErr");


	TH2D * hEff2DInv2Shots = (TH2D *) finEff->Get("hEff2DInv2Shots");

	

	TH2D * EffBptByInvBDTWeighted = (TH2D *) finEff->Get("EffBptByInvBDTWeighted");
	*/
	TH2D * EffBptBy = (TH2D *) finEff->Get("hEff2DInv2Shots");
	TH2D * EffBptByInv = (TH2D *) finEff->Get("hEff2DInv2Shots");
	TH2D * EffBptByInvErr = (TH2D *) finEff->Get("hEff2DInv2Shots");
	TH2D * hEff2DInv2Shots = (TH2D *) finEff->Get("hEff2DInv2Shots");

	

	TH2D * EffBptByInvBDTWeighted = (TH2D *) finEff->Get("hEff2DInv2Shots");




	Int_t   Bsize;
	Float_t Btrk1Pt[NCand];
	Float_t Btrk2Pt[NCand];

	Float_t Btrk1PtErr[NCand];
	Float_t Btrk2PtErr[NCand];


	Float_t Bchi2cl[NCand];
	Float_t BsvpvDistance[NCand];
	Float_t BsvpvDisErr[NCand];
	Float_t Bpt[NCand];
	Float_t Btrk1Eta[NCand];
	Float_t Btrk2Eta[NCand];
	Float_t By[NCand];



	Float_t Bmass[NCand];


	Float_t Bmumumass[NCand];
	Float_t Bmu1eta[NCand];
	Float_t Bmu1pt[NCand];
	Float_t Bmu2eta[NCand];
	Float_t Bmu2pt[NCand];

	Float_t Bmu1phi[NCand];
	Float_t Bmu2phi[NCand];

	Bool_t Bmu1TMOneStationTight[NCand];
	Int_t Bmu1InPixelLayer[NCand];
	Int_t Bmu1InStripLayer[NCand];

	Bool_t Bmu2TMOneStationTight[NCand];	
	Int_t Bmu2InPixelLayer[NCand];
	Int_t Bmu2InStripLayer[NCand];


	Bool_t Bmu1isGlobalMuon[NCand];
	Bool_t Bmu2isGlobalMuon[NCand];


	Bool_t Bmu1isTrackerMuon[NCand];
	Bool_t Bmu2isTrackerMuon[NCand];

	Float_t Bmu1dxyPV[NCand];
	Float_t Bmu2dxyPV[NCand];

	Float_t Bmu1dzPV[NCand];
	Float_t Bmu2dzPV[NCand];

	Bool_t Btrk1highPurity[NCand];
	Bool_t Btrk2highPurity[NCand];

	Float_t Btktkmass[NCand];

	Float_t Btrk1PixelHit[NCand];
	Float_t Btrk2PixelHit[NCand];

	Float_t Btrk1StripHit[NCand];
	Float_t Btrk2StripHit[NCand];

	Float_t Btrk1Chi2ndf[NCand];
	Float_t Btrk2Chi2ndf[NCand];


	Float_t Btrk1nStripLayer[NCand];
	Float_t Btrk2nStripLayer[NCand];

	Float_t Btrk1nPixelLayer[NCand];
	Float_t Btrk2nPixelLayer[NCand];


	Double_t BDT_pt_5_10[NCand];
	Double_t BDT_pt_10_15[NCand];
	Double_t BDT_pt_15_20[NCand];
	Double_t BDT_pt_20_50[NCand];

	Float_t Bgen[NCand];




	Float_t DataWeight_5_10[NCand];
	Float_t DataWeight_10_15[NCand];
	Float_t DataWeight_15_20[NCand];
	Float_t DataWeight_20_50[NCand];


	Bool_t Bmu1isTriggered[NCand];
	Bool_t Bmu2isTriggered[NCand];

	ntHi->SetBranchAddress("hiBin",&hiBin);
	BDT1->SetBranchAddress("run",&run);
	BDT1->SetBranchAddress("evt",&evt);
	BDT1->SetBranchAddress("lumi",&lumi);



	ntSkim->SetBranchAddress("pclusterCompatibilityFilter",&pclusterCompatibilityFilter);
	ntSkim->SetBranchAddress("pprimaryVertexFilter",&pprimaryVertexFilter);
	ntSkim->SetBranchAddress("phfCoincFilter2Th4",&phfCoincFilter2Th4);


	ntphi->SetBranchAddress("Bsize",&Bsize);
	ntphi->SetBranchAddress("PVz",&PVz);
	ntphi->SetBranchAddress("Btrk1Pt",Btrk1Pt);
	ntphi->SetBranchAddress("Btrk2Pt",Btrk2Pt);
	ntphi->SetBranchAddress("Btrk1PtErr",Btrk1PtErr);
	ntphi->SetBranchAddress("Btrk2PtErr",Btrk2PtErr);
	ntphi->SetBranchAddress("Bchi2cl",Bchi2cl);
	ntphi->SetBranchAddress("BsvpvDistance",BsvpvDistance);
	ntphi->SetBranchAddress("BsvpvDisErr",BsvpvDisErr);
	ntphi->SetBranchAddress("Bpt",Bpt);
	ntphi->SetBranchAddress("By",By);
	ntphi->SetBranchAddress("Btrk1Eta",Btrk1Eta);
	ntphi->SetBranchAddress("Btrk2Eta",Btrk2Eta);
	ntphi->SetBranchAddress("Bmass",Bmass);


	
	ntphi->SetBranchAddress("Bmu1isTriggered",Bmu1isTriggered);
	ntphi->SetBranchAddress("Bmu2isTriggered",Bmu2isTriggered);


	ntphi->SetBranchAddress("Bmumumass",Bmumumass);
	ntphi->SetBranchAddress("Bmu1eta",Bmu1eta);
	ntphi->SetBranchAddress("Bmu2eta",Bmu2eta);
	ntphi->SetBranchAddress("Bmu1pt",Bmu1pt);
	ntphi->SetBranchAddress("Bmu2pt",Bmu2pt);

	ntphi->SetBranchAddress("Bmu1phi",Bmu1phi);
	ntphi->SetBranchAddress("Bmu2phi",Bmu2phi);

	ntphi->SetBranchAddress("Bmu1TMOneStationTight",Bmu1TMOneStationTight);
	ntphi->SetBranchAddress("Bmu1InPixelLayer",Bmu1InPixelLayer);
	ntphi->SetBranchAddress("Bmu1InStripLayer",Bmu1InStripLayer);

	ntphi->SetBranchAddress("Bmu2TMOneStationTight",Bmu2TMOneStationTight);
	ntphi->SetBranchAddress("Bmu2InPixelLayer",Bmu2InPixelLayer);
	ntphi->SetBranchAddress("Bmu2InStripLayer",Bmu2InStripLayer);


	ntphi->SetBranchAddress("Bmu1isGlobalMuon",Bmu1isGlobalMuon);
	ntphi->SetBranchAddress("Bmu2isGlobalMuon",Bmu2isGlobalMuon);

	ntphi->SetBranchAddress("Bmu1isTrackerMuon",Bmu1isTrackerMuon);
	ntphi->SetBranchAddress("Bmu2isTrackerMuon",Bmu2isTrackerMuon);

	
	Int_t HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1;


	ntHlt->SetBranchAddress("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1",&HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1);



	ntphi->SetBranchAddress("Bmu1dxyPV",Bmu1dxyPV);
	ntphi->SetBranchAddress("Bmu2dxyPV",Bmu2dxyPV);
	ntphi->SetBranchAddress("Bmu1dzPV",Bmu1dzPV);
	ntphi->SetBranchAddress("Bmu2dzPV",Bmu2dzPV);


	ntphi->SetBranchAddress("Btrk1highPurity",Btrk1highPurity);
	ntphi->SetBranchAddress("Btrk2highPurity",Btrk2highPurity);

	ntphi->SetBranchAddress("Btktkmass",Btktkmass);


	ntphi->SetBranchAddress("Btrk1PixelHit",Btrk1PixelHit);
	ntphi->SetBranchAddress("Btrk2PixelHit",Btrk2PixelHit);
	ntphi->SetBranchAddress("Btrk1StripHit",Btrk1StripHit);
	ntphi->SetBranchAddress("Btrk2StripHit",Btrk2StripHit);



	ntphi->SetBranchAddress("Btrk1Chi2ndf",Btrk1Chi2ndf);
	ntphi->SetBranchAddress("Btrk2Chi2ndf",Btrk2Chi2ndf);



	ntphi->SetBranchAddress("Btrk1nStripLayer",Btrk1nStripLayer);	
	ntphi->SetBranchAddress("Btrk2nStripLayer",Btrk2nStripLayer);
	ntphi->SetBranchAddress("Btrk1nPixelLayer",Btrk1nPixelLayer);
	ntphi->SetBranchAddress("Btrk2nPixelLayer",Btrk2nPixelLayer);

	BDT1->SetBranchAddress("BDT_pt_5_10",BDT_pt_5_10);
	BDT2->SetBranchAddress("BDT_pt_10_15",BDT_pt_10_15);
	BDT3->SetBranchAddress("BDT_pt_15_20",BDT_pt_15_20);
	BDT4->SetBranchAddress("BDT_pt_20_50",BDT_pt_20_50);



	TFile * fout = new TFile(Form("/data/szhaozho/BsBP2018PbPb/Codes/BsAna/Nominal/Efficiency/BeforeMerge/EffInfo_%d_%d.root",CentMin,CentMax),"RECREATE");

	fout->cd();
	TTree* EffInfoTree = new TTree("EffInfoTree","EffInfoTree");	

	Int_t BsizeNew;
	Int_t runNew;
	Int_t lumiNew;
	Int_t evtNew;
	Int_t hiBinNew;

	Float_t BmassNew[NCand];
	Float_t BptNew[NCand];
	Float_t ByNew[NCand];
	Float_t BEff[NCand];
	Float_t BEffInv[NCand];
	Float_t BEffInvErr[NCand];

	Float_t BEffInvUp[NCand];
	Float_t BEffInvErrUp[NCand];
	Float_t BEffInvDown[NCand];
	Float_t BEffInvErrDown[NCand];


	Float_t Bmu1ptNew[NCand];
	Float_t Bmu1etaNew[NCand];
	Float_t Bmu1phiNew[NCand];


	Float_t Bmu2ptNew[NCand];
	Float_t Bmu2etaNew[NCand];
	Float_t Bmu2phiNew[NCand];


	Float_t BEffInvBDTWeighted[NCand];
	Float_t BEffInvErrBDTWeighted[NCand];


	Float_t BEff1D[NCand];
	Float_t BEffInv1D[NCand];
	Float_t BEffInvErr1D[NCand];

	Float_t BEffInvFit[NCand];
	Float_t BEffInvErrFit[NCand];

	Float_t BEffInvCent[NCand];
	Float_t BEffInvErrCent[NCand];



	Float_t TnPScale[NCand];
	Float_t TnPErrUp[NCand];
	Float_t TnPErrDown[NCand];

	Bool_t Bmu1isTriggeredNew[NCand];
	Bool_t Bmu2isTriggeredNew[NCand];



	Float_t BgenNew[NCand];


	int NumCand = 0;
	int BSizeCount;
	int iPass;

	int XLoc;
	int YLoc;

	int XLocTnP;
	int YLocTnP;

	int XLoc1D;
	int XLocCent;


	EffInfoTree->Branch("BsizeNew",&BsizeNew,"BsizeNew/I");
	EffInfoTree->Branch("runNew",&runNew,"runNew/I");
	EffInfoTree->Branch("evtNew",&evtNew,"evtNew/I");
	EffInfoTree->Branch("lumiNew",&lumiNew,"lumiNew/I");
	EffInfoTree->Branch("hiBinNew",&hiBinNew,"hiBinNew/I");


	EffInfoTree->Branch("BmassNew",BmassNew,"BmassNew/F");
	EffInfoTree->Branch("ByNew",ByNew,"ByNew/F");
	EffInfoTree->Branch("BptNew",BptNew,"BptNew/F");
	EffInfoTree->Branch("BEff",BEff,"BEff/F");
	EffInfoTree->Branch("BEffInv",BEffInv,"BEffInv/F");
	EffInfoTree->Branch("BEffInvErr",BEffInvErr,"BEffInvErr/F");


	//Muon Kinematics//
	
	EffInfoTree->Branch("Bmu1ptNew",Bmu1ptNew,"Bmu1ptNew/F");
	EffInfoTree->Branch("Bmu1etaNew",Bmu1etaNew,"Bmu1etaNew/F");
	EffInfoTree->Branch("Bmu1phiNew",Bmu1phiNew,"Bmu1phiNew/F");
	

	EffInfoTree->Branch("Bmu2ptNew",Bmu2ptNew,"Bmu2ptNew/F");
	EffInfoTree->Branch("Bmu2etaNew",Bmu2etaNew,"Bmu2etaNew/F");
	EffInfoTree->Branch("Bmu2phiNew",Bmu2phiNew,"Bmu2phiNew/F");



	

	EffInfoTree->Branch("DataWeight_5_10",DataWeight_5_10,"DataWeight_5_10/F");
	EffInfoTree->Branch("DataWeight_10_15",DataWeight_10_15,"DataWeight_10_15/F");
	EffInfoTree->Branch("DataWeight_15_20",DataWeight_15_20,"DataWeight_15_20/F");
	EffInfoTree->Branch("DataWeight_20_50",DataWeight_20_50,"DataWeight_20_50/F");

	EffInfoTree->Branch("BEffInvBDTWeighted",BEffInvBDTWeighted,"BEffInvBDTWeighted/F");
	EffInfoTree->Branch("BEffInvErrBDTWeighted",BEffInvErrBDTWeighted,"BEffInvErrBDTWeighted/F");


	EffInfoTree->Branch("Bmu1isTriggeredNew",Bmu1isTriggeredNew,"Bmu1isTriggeredNew/O");
	EffInfoTree->Branch("Bmu2isTriggeredNew",Bmu2isTriggeredNew,"Bmu2isTriggeredNew/O");

	EffInfoTree->Branch("BEff1D",BEff1D,"BEff1D/F");
	EffInfoTree->Branch("BEffInv1D",BEffInv1D,"BEffInv1D/F");
	EffInfoTree->Branch("BEffInvErr1D",BEffInvErr1D,"BEffInvErr1D/F");


	EffInfoTree->Branch("BEffInvFit",BEffInvFit,"BEffInvFit/F");
	EffInfoTree->Branch("BEffInvErrFit",BEffInvErrFit,"BEffInvErrFit/F");


	EffInfoTree->Branch("BEffInvCent",BEffInvCent,"BEffInvCent/F");
	EffInfoTree->Branch("BEffInvErrCent",BEffInvErrCent,"BEffInvErrCent/F");



	EffInfoTree->Branch("TnPScale",TnPScale,"TnPScale/F");
	EffInfoTree->Branch("TnPErrUp",TnPErrUp,"TnPErrUp/F");
	EffInfoTree->Branch("TnPErrDown",TnPErrDown,"TnPErrDown/F");

	EffInfoTree->Branch("BEffInvUp",BEffInvUp,"BEffInvUp/F");
	EffInfoTree->Branch("BEffInvErrUp",BEffInvErrUp,"BEffInvErrUp/F");

	EffInfoTree->Branch("BEffInvDown",BEffInvDown,"BEffInvDown/F");
	EffInfoTree->Branch("BEffInvErrDown",BEffInvErrDown,"BEffInvErrDown/F");




	int NEvents = ntphi->GetEntries();


	int LocWeightX;
	

	int LocWeightY;

	double BDTSystemWeight;


	//Copy a new tree//
	
	cout << "Copying Fit Tree for Framework" << endl;  

	TTree* EffInfoTree_NewFit;
	EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
	EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");


	//Done Copying//
	
	for(int i = 0; i < NEvents; i++){

		if(i%100000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<ntphi->GetEntries()<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/ntphi->GetEntries())<<"%\033[0m"<<"\r"<<std::flush;


		ntphi->GetEntry(i);
		ntSkim->GetEntry(i);
		ntHi->GetEntry(i);
		ntHlt->GetEntry(i);
		BDT1->GetEntry(i);
		BDT2->GetEntry(i);
		BDT3->GetEntry(i);
		BDT4->GetEntry(i);



		

		BSizeCount = 0;
		iPass = 0;

		runNew = run;
		lumiNew = lumi;
		evtNew = evt;

		double lowstBDTCut = 0.32;




		if(CentMin == 30) lowstBDTCut = 0.32;
		if(CentMin == 0) lowstBDTCut = 0.32;


		for(int j =0; j < Bsize; j++){

			if(((HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1 == 1) && (Bmu1isTriggered[j] == 1 && Bmu2isTriggered[j] == 1) &&  (hiBin < 181) && Btrk1Pt[j] > 0.9 && Btrk2Pt[j] > 0.9 && Bchi2cl[j] > 0.05 && BsvpvDistance[j]/BsvpvDisErr[j] > 2.0 && Bpt[j] > 5 && abs(Btrk1Eta[j]-0.0) < 2.4 && abs(Btrk2Eta[j]-0.0) < 2.4 && (TMath::Abs(By[j])<2.4&&TMath::Abs(Bmumumass[j]-3.096916)<0.15&&((abs(Bmu1eta[j])<1.2&&Bmu1pt[j]>3.5)||(abs(Bmu1eta[j])>1.2&&abs(Bmu1eta[j])<2.1&&Bmu1pt[j]>(5.47-1.89*abs(Bmu1eta[j])))||(abs(Bmu1eta[j])>2.1&&abs(Bmu1eta[j])<2.4&&Bmu1pt[j]>1.5))&&((abs(Bmu2eta[j])<1.2&&Bmu2pt[j]>3.5)||(abs(Bmu2eta[j])>1.2&&abs(Bmu2eta[j])<2.1&&Bmu2pt[j]>(5.47-1.89*abs(Bmu2eta[j])))||(abs(Bmu2eta[j])>2.1&&abs(Bmu2eta[j])<2.4&&Bmu2pt[j]>1.5))&&Bmu1TMOneStationTight[j]&&Bmu2TMOneStationTight[j]&&Bmu1InPixelLayer[j]>0&&(Bmu1InPixelLayer[j]+Bmu1InStripLayer[j])>5&&Bmu2InPixelLayer[j]>0&&(Bmu2InPixelLayer[j]+Bmu2InStripLayer[j])>5&&Bmu1dxyPV[j]<0.3&&Bmu2dxyPV[j]<0.3&&Bmu1dzPV[j]<20&&Bmu2dzPV[j]<20&&Bmu1isTrackerMuon[j]&&Bmu2isTrackerMuon[j]&&Bmu1isGlobalMuon[j]&&Bmu2isGlobalMuon[j]&&Btrk1highPurity[j]&&Btrk2highPurity[j]&&abs(Btrk1Eta[j])<2.4&&abs(Btrk2Eta[j])<2.4&&Btrk1Pt[j]>1.&&Btrk2Pt[j]>1.&&abs(Btktkmass[j]-1.019455)<0.015) && (abs(PVz)<15&&pclusterCompatibilityFilter == 1 &&pprimaryVertexFilter == 1) && (Btrk1PixelHit[j] + Btrk1StripHit[j] > 10) && (Btrk2PixelHit[j] + Btrk2StripHit[j] > 10) && (Btrk1PtErr[j]/Btrk1Pt[j] < 0.1)&& (Btrk2PtErr[j]/Btrk2Pt[j] < 0.1) && Btrk1Chi2ndf[j]/(Btrk1nStripLayer[j]+Btrk1nPixelLayer[j]) < 0.18 && Btrk2Chi2ndf[j]/(Btrk2nStripLayer[j]+Btrk2nPixelLayer[j]) < 0.18&&((Bpt[j]>5&&Bpt[j]<10&&BDT_pt_5_10[j]>lowstBDTCut )||(Bpt[j]>10&&Bpt[j]<15&&BDT_pt_10_15[j]> 0.29)||(Bpt[j]>15&&Bpt[j]<20&&BDT_pt_15_20[j]>0.35)||(Bpt[j]>20&&Bpt[j]<50&&BDT_pt_20_50[j]>0.33))&&abs(PVz)<15&&pclusterCompatibilityFilter == 1 &&pprimaryVertexFilter == 1 && phfCoincFilter2Th4 == 1) && (Bmass[j] > 5 &&Bmass[j] < 6 && hiBin >= CentMin * 2&& hiBin <= CentMax * 2 ) ){
				
				BmassNew[iPass] =  Bmass[j];
				BptNew[iPass] =  Bpt[j];
				ByNew[iPass] =  TMath::Abs(By[j]);

				Bmu1isTriggeredNew[iPass] = Bmu1isTriggered[j];
				Bmu2isTriggeredNew[iPass] = Bmu2isTriggered[j];



				Bmu1ptNew[iPass] = Bmu1pt[j];
				Bmu1etaNew[iPass] = Bmu1eta[j];
				Bmu1phiNew[iPass] = Bmu1phi[j];

				Bmu2ptNew[iPass] = Bmu2pt[j];
				Bmu2etaNew[iPass] = Bmu2eta[j];
				Bmu2phiNew[iPass] = Bmu2phi[j];



				DataWeight_5_10[iPass] = 1.0;
				DataWeight_10_15[iPass] = 1.0;
				DataWeight_15_20[iPass] = 1.0;
				DataWeight_20_50[iPass] = 1.0;

			
				/*	
				if(Bpt[j]>5&&Bpt[j]<10)		DataWeight_5_10[iPass] = 0.895 - BDT_pt_5_10[j] * 0.213;
				if(Bpt[j]>10&&Bpt[j]<15)	DataWeight_10_15[iPass] = 1.030 + BDT_pt_10_15[j] * 0.050;
				if(Bpt[j]>15&&Bpt[j]<20)	DataWeight_15_20[iPass] = 1.068 + BDT_pt_15_20[j] * 0.116;
				if(Bpt[j]>20&&Bpt[j]<50)	DataWeight_20_50[iPass] = 1.056 + BDT_pt_20_50[j] * 0.285;
				*/

				if(Bpt[j]>5&&Bpt[j]<10)		DataWeight_5_10[iPass] = 0.931 - BDT_pt_5_10[j] * 0.128;
				if(Bpt[j]>10&&Bpt[j]<15)	DataWeight_10_15[iPass] = 1.030 + BDT_pt_10_15[j] * 0.052;
				if(Bpt[j]>15&&Bpt[j]<20)	DataWeight_15_20[iPass] = 1.055 + BDT_pt_15_20[j] * 0.084;
				if(Bpt[j]>20&&Bpt[j]<50)	DataWeight_20_50[iPass] = 1.059 + BDT_pt_20_50[j] * 0.314;

				
	
				XLoc = EffBptBy->GetXaxis()->FindBin(BptNew[iPass]);
				YLoc = EffBptBy->GetYaxis()->FindBin(ByNew[iPass]);


				BEff[iPass] =  EffBptBy->GetBinContent(XLoc,YLoc);
				BEffInv[iPass] =  EffBptByInv->GetBinContent(XLoc,YLoc);
				BEffInvErr[iPass] =  EffBptByInvErr->GetBinContent(XLoc,YLoc);


				LocWeightX = EffBptByInvBDTWeighted->GetXaxis()->FindBin(BptNew[iPass]);
				LocWeightY = EffBptByInvBDTWeighted->GetYaxis()->FindBin(ByNew[iPass]);
			
	
				BEffInvBDTWeighted[iPass] =  EffBptByInvBDTWeighted->GetBinContent(LocWeightX,LocWeightY)/ TnPScale[iPass]; 
				BEffInvErrBDTWeighted[iPass] =  EffBptByInvBDTWeighted->GetBinError(LocWeightX,LocWeightY)/ TnPScale[iPass];


			//	cout << "LocWeightX = " <<LocWeightX <<  "  BEffInvBDTWeighted[iPass] " << BEffInvBDTWeighted[iPass] << endl;

				//Add BDT Systematics Weight to File//
				/*
				if(BptNew[iPass] > 5 && BptNew[iPass] < 10){

					LocWeightX = weights_BDT_pt_5_10->GetXaxis()->FindBin(BDT_pt_5_10[iPass]);
					BDTSystemWeight = weights_BDT_pt_5_10->GetBinContent(LocWeightX);
					BEffInvBDTWeighted[iPass] =  EffBptByInv->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight; 
					BEffInvErrBDTWeighted[iPass] =  EffBptByInvErr->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight;

				}

				if(BptNew[iPass] > 10 && BptNew[iPass] < 15){

					LocWeightX = weights_BDT_pt_10_15->GetXaxis()->FindBin(BDT_pt_10_15[iPass]);
					BDTSystemWeight = weights_BDT_pt_10_15->GetBinContent(LocWeightX);
					BEffInvBDTWeighted[iPass] =  EffBptByInv->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight; 
					BEffInvErrBDTWeighted[iPass] =  EffBptByInvErr->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight;

				}

				if(BptNew[iPass] > 15 && BptNew[iPass] < 20){

					LocWeightX = weights_BDT_pt_15_20->GetXaxis()->FindBin(BDT_pt_15_20[iPass]);
					BDTSystemWeight = weights_BDT_pt_15_20->GetBinContent(LocWeightX);
					BEffInvBDTWeighted[iPass] =  EffBptByInv->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight; 
					BEffInvErrBDTWeighted[iPass] =  EffBptByInvErr->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight;

				}

				if(BptNew[iPass] > 20 && BptNew[iPass] < 50){

					LocWeightX = weights_BDT_pt_20_50->GetXaxis()->FindBin(BDT_pt_20_50[iPass]);
					BDTSystemWeight = weights_BDT_pt_20_50->GetBinContent(LocWeightX);
					BEffInvBDTWeighted[iPass] =  EffBptByInv->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight; 
					BEffInvErrBDTWeighted[iPass] =  EffBptByInvErr->GetBinContent(XLoc,YLoc)/ TnPScale[iPass] * BDTSystemWeight;

				}
				*/

		//		XLoc1D = hEffFineInv->GetXaxis()->FindBin(BptNew[iPass]);

		//		BEff1D[iPass] =  hEffFine->GetBinContent(XLoc1D);
		//		BEffInv1D[iPass] =  hEffFineInv->GetBinContent(XLoc1D);
		//		BEffInvErr1D[iPass] =  hEffFineInv->GetBinError(XLoc1D);


				BEffInvFit[iPass] = func->Eval(BptNew[iPass]);
				BEffInvErrFit[iPass] = 0;





				NumCand = NumCand + 1;
				BSizeCount = BSizeCount + 1;
				iPass = iPass + 1;

			}



		}

		BsizeNew = BSizeCount;
		hiBinNew = hiBin;
		if(BsizeNew > 0) EffInfoTree->Fill();
		if(BsizeNew > 0) EffInfoTree_NewFit->Fill();
	
	}
	
	fout->Write();
	fout->Close();


}


