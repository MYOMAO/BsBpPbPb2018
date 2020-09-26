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
#include <iterator>
#include <chrono>
#include <random>

//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void RandomSample(int CentMin, int CentMax){

	
	TString infile = Form("CheckSystNuno/NoWeight/EffInfo_%d_%d_MC_Closure.root",CentMin,CentMax);

	TFile * fin = new TFile(infile.Data());
	fin->cd();



	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");

	int NEvents = EffInfoTree->GetEntries();

	int NEventSpilt;
	
	if (CentMin == 0 && CentMax == 90) NEventSpilt = 3640;
	if (CentMin == 30 && CentMax == 90) NEventSpilt = 42;
	if (CentMin == 0 && CentMax == 30) NEventSpilt = 128;


	TFile * outf = new TFile(Form("CheckSystNuno/NoWeight/RanGenMC/%d-%d/MC_0.root",CentMin,CentMax),"RECREATE");
	outf->cd();
	TTree* EffInfoTree_New;

	
	int NSets = 2000;

	int Index = 0;
	int IndexPre = 0;

	EffInfoTree_New = EffInfoTree->CloneTree(0);
	cout << "NEvents = " << NEvents << endl;

	std::vector<int> EventVec;


	for(int i = 0; i < NEvents; i++){

		EventVec.push_back(i);

	}




	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	for(int i = 0; i < NSets; i++){

		cout << "Now Working on " << i << "  File" << endl;

		std::shuffle(EventVec.begin(), EventVec.end(), std::default_random_engine(seed));
		outf = new TFile(Form("CheckSystNuno/NoWeight/RanGenMC/%d-%d/MC_%d.root",CentMin,CentMax,i),"RECREATE");
		outf->cd();
		EffInfoTree_New = EffInfoTree->CloneTree(0);


		for(int j = 0; j < NEventSpilt; j++){

			EffInfoTree->GetEntry(EventVec[j]);

			EffInfoTree_New->Fill();

		}

		outf->Write();
		outf->Close();

	}




}
