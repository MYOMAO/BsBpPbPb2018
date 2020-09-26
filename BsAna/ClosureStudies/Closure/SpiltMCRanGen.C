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

void SpiltMCRanGen(int CentMin, int CentMax, int PtOpt, int pthatCut, int SpiltOpt, int Seq){


	int Factor = 1;

	//	TString infile = Form("CheckSystNuno/NoWeight/EffInfo_%d_%d_MC_Closure.root",CentMin,CentMax);


	TString infile;


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


	TFile * fin = new TFile(infile.Data());
	fin->cd();


	TString outfilefolder;






	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) outfilefolder = "7-10";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  outfilefolder = "10-15";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  outfilefolder = "15-20";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 outfilefolder = "20-50";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";



	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");

	int NEvents = EffInfoTree->GetEntries();

	int BsizeNew;

	int NGenCand;

	EffInfoTree->SetBranchAddress("BsizeNew",&BsizeNew);

	EffInfoTree->SetBranchAddress("NGenCand",&NGenCand);


	TString pthatfolder;
	if(pthatCut == -1) pthatfolder="0-50";
	if(pthatCut == 0) pthatfolder="0";
	if(pthatCut == 1) pthatfolder="5";
	if(pthatCut == 2) pthatfolder="15";
	if(pthatCut == 3) pthatfolder="30";
	if(pthatCut == 4) pthatfolder="50";




	int NEventSpilt;

	if(SpiltOpt == 0) {

		cout << "Split RECO" << endl;

		if(CentMin == 0 && CentMax ==90 && PtOpt == 0) NEventSpilt = 7;
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



	NEventSpilt = NEventSpilt * Factor;


	
	TString OutFileName;

	if(Seq == 0) OutFileName = Form("CheckSystNuno/NoWeight/MCSPlitRanGen/%d-%d/%s/%s/MC_0.root",CentMin,CentMax,outfilefolder.Data(),pthatfolder.Data());
	if(Seq == 1) OutFileName = Form("CheckSystNuno/NoWeight/MCSPlitSeq/%d-%d/%s/%s/MC_0.root",CentMin,CentMax,outfilefolder.Data(),pthatfolder.Data());
	TFile * outf = new TFile(OutFileName.Data(),"RECREATE");;


	outf->cd();

	TTree* EffInfoTree_New;
	TTree* EffInfoTree_NewFit;


	int NSets = 2000;

	int Index = 0;
	int IndexPre = 0;



	EffInfoTree_New = EffInfoTree->CloneTree(0);
	EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
	EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");


	cout << "NEvents = " << NEvents << endl;

	std::vector<int> EventVec;


	for(int i = 0; i < NEvents; i++){

		EventVec.push_back(i);

	}


	if(Seq==0){


		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		for(int i = 0; i < NSets; i++){

			cout << "Now Working on " << i << "  File" << endl;

			std::shuffle(EventVec.begin(), EventVec.end(), std::default_random_engine(seed));
			outf = new TFile(Form("CheckSystNuno/NoWeight/MCSPlitRanGen/%d-%d/%s/%s/MC_%d.root",CentMin,CentMax,outfilefolder.Data(),pthatfolder.Data(),i),"RECREATE");
			outf->cd();
			EffInfoTree_New = EffInfoTree->CloneTree(0);
			EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
			EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");


			for(int j = 0; j < NEventSpilt; j++){

				EffInfoTree->GetEntry(EventVec[j]);

				EffInfoTree_New->Fill();
				if(BsizeNew > 0) EffInfoTree_NewFit->Fill();

			}

			outf->Write();
			outf->Close();

		}
	}


	if(Seq==1){
		
		
		for(int i = 0; i < NSets; i++){

			cout << "Now Working on " << i << "  File" << endl;
			outf = new TFile(Form("CheckSystNuno/NoWeight/MCSPlitSeq/%d-%d/%s/%s/MC_%d.root",CentMin,CentMax,outfilefolder.Data(),pthatfolder.Data(),i),"RECREATE");
			outf->cd();
			EffInfoTree_New = EffInfoTree->CloneTree(0);
			EffInfoTree_NewFit = EffInfoTree->CloneTree(0);
			EffInfoTree_NewFit->SetObject("EffInfoTreeFit","EffInfoTreeFit");


			for(int j = 0; j < NEventSpilt; j++){

				EffInfoTree->GetEntry(i * NSets + j);
				EffInfoTree_New->Fill();
				if(BsizeNew > 0) EffInfoTree_NewFit->Fill();
			}

			outf->Write();
			outf->Close();

		}


	}



}
