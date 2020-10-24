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


void PrintoutStat(){

	TFile * fin2 = new TFile("2DMapStat/EffFine_0_30.root");
	fin2->cd();

	TH2D * EffBptByGen = (TH2D * ) fin2->Get("EffBptByGen");
	TH2D * EffBptByMC = (TH2D * ) fin2->Get("EffBptByMC");
	TH2D * hEffSelectionFine = (TH2D * ) fin2->Get("hEffSelectionFine");
	TH2D * hEff2DInv2Shots = (TH2D * ) fin2->Get("hEff2DInv2Shots");
	

	const int NPtBins = hPtGen2DFine->GetNbinsX();
	const int NYBins = hPtGen2DFine->GetNbinsY();

	cout << "NPtBins = " << NPtBins << "   NYBins = " << NYBins << endl;

	double PtBin[51] = {5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
	double YBin[6] = {0,0.5,1.0,1.5,2.0,2.4};

	double ptmin = 7.0;
	double ptmax= 50.0;

	double pt;
	double y;

	double NGen;
	double NPass;
	double Acc;

	double NGen2;
	double NRECO;
	double SelEff;
	double Eff;
	
	int XBinNow;
	int YBinNow;

	const int NBins = 4;
	const int PtBinEdge[NBins+1] = {7,10,15,20,50};

	double TotalRECO[NBins] = {0,0,0,0};

	
	for(int j = 0; j < NYBins; j++){
	
		for(int i = 0; i < NPtBins+1; i++){


		pt = PtBin[i] + 0.01; 

		if(pt > ptmin && pt < ptmax){


				y = YBin[j] + 0.01;

				XBinNow = hPtGen2DFine->GetXaxis()->FindBin(pt);
				YBinNow = hPtGen2DFine->GetYaxis()->FindBin(y);
				
				NGen2 = EffBptByGen->GetBinContent(XBinNow,YBinNow);
				NRECO = EffBptByMC->GetBinContent(XBinNow,YBinNow);



		//		if(NPass > 0)	cout << "y from " <<  YBin[j] << "   -   " << YBin[j+1]  << "   pt from " << PtBin[i] << "   -   " << PtBin[i+1] << "   NGen =  " << NGen << "   NPass =  " << NPass << "   Acc = " << Acc << endl;  
				if(NGen2 > 0)	cout << "y from " <<  YBin[j] << "   -   " << YBin[j+1]  << "   pt from " << PtBin[i] << "   -   " << PtBin[i+1] << "   NGen2 =  " << NGen2 << "   NRECO =  " << NRECO << endl;  

				for(int k = 0; k < NBins; k++){

					if(pt < PtBinEdge[k+1] && pt > PtBinEdge[k] ) TotalRECO[k] = TotalRECO[k] + NRECO;

				}



			}

		}


	}


	double TotalSum = 0;

	for(int k = 0; k < NBins; k++){
	
		if(k > 0) TotalSum = TotalSum + TotalRECO[k];

		cout << "k = " << k << "   TotalRECO = " << TotalRECO[k] << endl;


	}

	
	cout <<  "TotalSum = " << TotalSum  << endl;



}
