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

void SpiltMC(){



	TFile * fin = new TFile("CheckSystNuno/NoWeight/EffInfo_0_90_MC_Closure.root");
	fin->cd();



	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");

	int NEvents = EffInfoTree->GetEntries();

	int NEventSpilt = 164;

	TFile * outf = new TFile("CheckSystNuno/NoWeight/MCSPlit/MC_0.root","RECREATE");
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

			outf = new TFile(Form("CheckSystNuno/NoWeight/MCSPlit/MC_%d.root",Index),"RECREATE");
			outf->cd();
		
			EffInfoTree_New = EffInfoTree->CloneTree(0);
	//		cout << "Pass 1" << endl;


			IndexPre = Index;
			
		}

		EffInfoTree_New->Fill();


	}


}
