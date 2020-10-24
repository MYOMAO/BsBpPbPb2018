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
#include <vector>
#include <random>

//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void SpiltDataBoot(int CentMin, int CentMax, int PtOpt){


	int Factor = 1;

	double NBackground = 40;
	double Lambda = -1.0;

	TString Func = Form("%f * TMath::Exp(%f * x)",NBackground,Lambda);

	TF1 * bkgd = new TF1("bkgd",Func.Data(),5,6);

	//	TString infile = Form("CheckSystNuno/NoWeight/EffInfo_%d_%d_MC_Closure.root",CentMin,CentMax);


	TString infile;

	/*
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 0)  infile = Form("New/0-90/7-10/EffInfo_MC_Closure%d.root",pthatCut);
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  infile = Form("New/0-90/10-15/EffInfo_MC_Closure%d.root",pthatCut);	
	//	if(CentMin == 0 && CentMax ==90 && PtOpt == 1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-15_Cent0-90.root";
	//	if(CentMin == 0 && CentMax ==90 && PtOpt == 2) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt15-20_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2) infile = Form("New/0-90/15-20/EffInfo_MC_Closure%d.root",pthatCut);
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3) infile = Form("New/0-90/20-50/EffInfo_MC_Closure%d.root",pthatCut);

	//	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt20-50_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1 && pthatCut == -1) infile = "CheckSystNuno/NoWeight/EffInfo_MC_Closure.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1 && pthatCut == 1) infile = "New/0-90/10-50/EffInfo_MC_Closure1.root";
	//	if(CentMin == 0 && CentMax ==30 && PtOpt == -1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-50_Cent0-30.root";
	//	if(CentMin == 30 && CentMax ==90 && PtOpt == -1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-50_Cent30-90.root";

	if(CentMin == 0 && CentMax ==30 && PtOpt == -1) infile = "New/0-30/10-50/EffInfo_MC_Closure1.root";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1 && pthatCut == 1) infile = "New/30-90/10-50/EffInfo_MC_Closure1.root";
	*/



	TString outfilefolder;

	cout << "Pass 0 " << endl;





	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) outfilefolder = "7-10";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  outfilefolder = "10-15";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  outfilefolder = "15-20";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 outfilefolder = "20-50";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";

	infile = Form("FinalInput/%d-%d/%s/EffInfo.root",CentMin,CentMax,outfilefolder.Data());

	TFile * fin = new TFile(infile.Data());
	fin->cd();

	cout << "Pass 0.5 " << endl;

	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");
	TTree * MuonInfoTree = (TTree * ) fin->Get("MuonInfoTree");

	int NEvents = EffInfoTree->GetEntries();
	
	/*
	int NEvents;
	if(CentMin == 0 && CentMax ==90 &&PtOpt == 0) NEvents = 150;
	if(CentMin == 0 && CentMax ==90 &&PtOpt == 1) NEvents = 355;
	if(CentMin == 0 && CentMax ==90 &&PtOpt == 2) NEvents = 272;
	if(CentMin == 0 && CentMax ==90 &&PtOpt == 3) NEvents = 347;

	if(CentMin == 0 && CentMax ==90 &&PtOpt == -1) NEvents = 1900;
	if(CentMin == 0 && CentMax ==30 &&PtOpt == -1) NEvents = 649;
	if(CentMin == 30 && CentMax == 90 &&PtOpt == -1) NEvents = 328;
	*/
	cout << "Pass 0.6 " << endl;

	if(CentMin == 0 && CentMax ==90 &&PtOpt == 0) NEvents = 169;
	if(CentMin == 0 && CentMax ==90 &&PtOpt == -1) NEvents = 1690;
	if(CentMin == 0 && CentMax ==30 &&PtOpt == -1) NEvents = 1180;

	int BsizeNew;




	EffInfoTree->SetBranchAddress("BsizeNew",&BsizeNew);






	cout << "Pass 1 " << endl;


	//	int NEventSpilt = NEvents;
	/*
	   if(SpiltOpt == 0) {

	   cout << "Split RECO" << endl;

	   if(CentMin == 0 && CentMax ==90 && PtOpt == 0) NEventSpilt = 6;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  NEventSpilt = 33;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  NEventSpilt = 29;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 NEventSpilt = 35;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 95;
	   if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  NEventSpilt = 68;
	   if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 31;

	   }


	   if(SpiltOpt == 1) {

	   cout << "Split Gen" << endl;

	   if(CentMin == 0 && CentMax ==90 && PtOpt == 0) NEventSpilt = 600;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  NEventSpilt = 1500;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  NEventSpilt = 380;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 NEventSpilt = 240;
	   if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 800;
	   if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  NEventSpilt = 800;
	   if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 250;

	   }

*/

	//NEventSpilt = NEventSpilt * Factor;



	TString OutFileName;

	OutFileName = Form("DataResample/%d-%d/%s/MC_0.root",CentMin,CentMax,outfilefolder.Data());
	
	TFile * outf = new TFile(OutFileName.Data(),"RECREATE");;


	outf->cd();

	TTree* EffInfoTree_New;
	TTree* EffInfoTree_NewFit;
	TTree* MuonInfoTree_New;

	int NSets = 1000;

	int Index = 0;
	int IndexPre = 0;

	cout << "Pass 2 " << endl;
   // NEvents = EffInfoTree->GetEntries();

	cout << "NEvent = " << NEvents << endl;
	EffInfoTree_New = EffInfoTree->CloneTree(0);
	EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
	EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");
	MuonInfoTree_New = MuonInfoTree->CloneTree(0);

//	cout << "NEvents = " << NEvents << endl;

	int SampleSize;
	std::vector<int> EventVec;


	for(int i = 0; i < NEvents; i++){

		EventVec.push_back(i);

	}
	

	TString f1Name = Form("TMath::Poisson(x,%d)",NEvents);
	TF1 *f1 = new TF1("f1",f1Name.Data(),0,4000);

	TF1 *f2 = new TF1("f2","x",-0.5,NEvents-0.5);



	//		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	for(int i = 0; i < NSets; i++){

		cout << "Now Working on " << i << "  File" << endl;

		//std::shuffle(EventVec.begin(), EventVec.end(), std::default_random_engine(seed));

	

		SampleSize =  f1->GetRandom();

//		cout << "SampleSize = " << SampleSize << endl;

		for(int k = 0; k< SampleSize;k++){
			EventVec.push_back(f2->GetRandom());
		}


		outf = new TFile(Form("DataResample/%d-%d/%s/MC_%d.root",CentMin,CentMax,outfilefolder.Data(),i),"RECREATE");
		outf->cd();
		EffInfoTree_New = EffInfoTree->CloneTree(0);
		EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
		EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");
		MuonInfoTree_New = MuonInfoTree->CloneTree(0);


		for(int j = 0; j < SampleSize; j++){

			EffInfoTree->GetEntry(EventVec[j]);
			MuonInfoTree->GetEntry(EventVec[j]);


			EffInfoTree_New->Fill();
			MuonInfoTree_New->Fill();
			if(BsizeNew > 0) EffInfoTree_NewFit->Fill();

		}


	
	
/*
		if(CentMin == 0 && CentMax == 90 && PtOpt == 0){

			float Bmassbkgd[1];

			EffInfoTree_NewFit->SetBranchAddress("BmassNew",Bmassbkgd);

	//		TTree* BackgroundTree = new TTree("BackgroundTree","BackgroundTree");
	//		BackgroundTree->Branch("Bmassbkgd",&Bmassbkgd,"Bmassbkgd/F");


			for(int u = 0; u < NBackground; u++){
			EffInfoTree->GetEntry(1);
//			EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
		

			Bmassbkgd[0] = bkgd->GetRandom();
			EffInfoTree_NewFit->Fill();
			}

		}
		*/

		outf->Write();
		outf->Close();
		EventVec.clear();
	}






}
