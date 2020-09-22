#ifndef __CINT__
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

using namespace std;

using std::cout;
using std::endl;
#endif


void EventMatched(int CentMin, int CentMax, int Option){




	TString BType;

	if(Option == 0) BType = "Bs";
	if(Option == 1) BType = "BP";


	int EventMuon;
	int RunMuon;
	int LumiMuon;

	//	unsigned long int MuonKey;

	int EventData;
	int RunData;
	int LumiData;


	//int HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1;

	//	unsigned long int DataKey;

	TFile * MuonInfoFile = new TFile("BMuonInfo.root");



	TString infile = Form("AnaData/%s/EffInfo_%d_%d.root",BType.Data(),CentMin,CentMax);

	TFile * fin = new TFile(infile.Data());
	

	TString MatchedFileName = Form("Matched%sEntries_%d_%d.dat",BType.Data(),CentMin,CentMax);

	TTree * root = (TTree *) MuonInfoFile->Get("Bfinder/root");
	root->SetBranchAddress("EvtInfo.RunNo",&RunMuon);
	root->SetBranchAddress("EvtInfo.EvtNo",&EventMuon);
	root->SetBranchAddress("EvtInfo.LumiNo",&LumiMuon);

	TTree * HltTree = (TTree *) MuonInfoFile->Get("hltanalysis/HltTree");
//	root->SetBranchAddress("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1",&HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1);





	TTree * EffInfoTree = (TTree *) fin->Get("EffInfoTree");
	EffInfoTree->SetBranchAddress("runNew",&RunData);
	EffInfoTree->SetBranchAddress("evtNew",&EventData);
	EffInfoTree->SetBranchAddress("lumiNew",&LumiData);


	int NMuonEvent = root->GetEntries();
	const int NDataEvent = EffInfoTree->GetEntries();
//	const int NDataEvent = 1;

	cout << "NDataEvent = " << NDataEvent << endl;

	int EventtoEntry[NDataEvent]; 

	std::ifstream MatchedFile(MatchedFileName.Data());


	for(int i = 0; i < NDataEvent; i++){
		
		
		MatchedFile >>	EventtoEntry[i];

//		EventtoEntry[i] = 0;


	}



	TString outfile = Form("Output/%s/EffInfo_%d_%d.root",BType.Data(),CentMin,CentMax);
	
	TFile * fout = new TFile(outfile.Data(),"RECREATE");
	fout->cd();
	TTree * EffInfoTree_new = EffInfoTree->CloneTree(0);
	TTree * root_new = root->CloneTree(0);
	TTree * HltTree_new = HltTree->CloneTree(0);

	for(int i = 0; i < NDataEvent; i++){

		cout << "Event " << i << "   Corresponds to Entry  " << EventtoEntry[i] << endl;

		EffInfoTree->GetEntry(i);
		root->GetEntry( EventtoEntry[i]);
		HltTree->GetEntry( EventtoEntry[i]);


		EffInfoTree_new->Fill();
		root_new->Fill();
		HltTree_new->Fill();

	}
	fout->Write();

	fin->Close();

	MuonInfoFile->Close();

	fout->Close();



}
