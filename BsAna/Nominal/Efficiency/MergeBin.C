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

void MergeBin(){

	TString File030 = "FinalFiles/NoTnP/NewCorr_0_30.root";
	TString File3090 = "FinalFiles/NoTnP/NewCorr_30_90.root";

	TFile * fin030 = new TFile(File030.Data());
	fin030->cd();
	TH1D * h030 = (TH1D * ) fin030->Get("hPtSigma");

	TFile * fin3090 = new TFile(File3090.Data());
	fin3090->cd();
	TH1D * h3090 = (TH1D * ) fin3090->Get("hPtSigma");
	

	double CentBinning[3] = {0,60,180};

	TH1D * hPtSigma = new TH1D("hPtSigma","",2,CentBinning);

	double V1 = h030->GetBinContent(1);
	double V1Err =  h030->GetBinError(1);

	double V2 = h3090->GetBinContent(1);
	double V2Err =  h3090->GetBinError(1);

	
	hPtSigma->SetBinContent(1,V1);
	hPtSigma->SetBinError(1,V1Err);
	hPtSigma->SetBinContent(2,V2);
	hPtSigma->SetBinError(2,V2Err);


	TFile * fout = new TFile("CrossSectionPbPbBs.root","RECREATE");
	fout->cd();
	hPtSigma->Write();
	fout->Close();
	
	cout << "DONE MY BRO" << endl;

}
