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


//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void SpiltMCFlat(int CentMin, int CentMax, int PtOpt){


	

//	TString infile = Form("CheckSystNuno/NoWeight/EffInfo_%d_%d_MC_Closure.root",CentMin,CentMax);

	TString infile;

	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt7-10_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-15_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt15-20_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt20-50_Cent0-90.root";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-50_Cent0-90.root";
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-50_Cent0-30.root";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1) infile = "/export/d00/scratch/gwangjun/selected_mc_ntphi_PbPb_2018_pt10-50_Cent30-90.root";



	TString outfilefolder;



	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) outfilefolder = "7-10";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  outfilefolder = "10-15";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  outfilefolder = "15-20";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 outfilefolder = "20-50";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";





	TFile * fin = new TFile(infile.Data());
	fin->cd();



	TTree * EffInfoTree = (TTree * ) fin->Get("ntphi");

	int NEvents = EffInfoTree->GetEntries();

	int NEventSpilt;


	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) NEventSpilt = 7;
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  NEventSpilt = 33;
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  NEventSpilt = 29;
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 NEventSpilt = 35;
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 95;
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  NEventSpilt = 68;
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  NEventSpilt = 31;





	TFile * outf = new TFile(Form("Flat/%d-%d/%s/MCFlat_0.root",CentMin,CentMax,outfilefolder.Data()),"RECREATE");
	outf->cd();
	TTree* EffInfoTree_New;

	int Index = 0;
	int IndexPre = 0;

	EffInfoTree_New = EffInfoTree->CloneTree(0);
	cout << "NEvents = " << NEvents << endl;

	for(int i = 0; i < NEvents; i++){

		EffInfoTree->GetEntry(i);

		Index = i/NEventSpilt;

		if(Index > IndexPre) cout << "Now working on File = " << Index << endl;


		if(Index > IndexPre){
			outf->Write();
			outf->Close();

			outf = new TFile(Form("Flat/%d-%d/%s/MCFlat_%d.root",CentMin,CentMax,outfilefolder.Data(),Index),"RECREATE");
			outf->cd();
	
			EffInfoTree_New = EffInfoTree->CloneTree(0);
	//		cout << "Pass 1" << endl;


			IndexPre = Index;
			
		}

		EffInfoTree_New->Fill();


	}


}
