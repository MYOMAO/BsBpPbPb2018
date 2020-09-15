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

#include "parameters4Bins.h"
#include "tdrstyle.C"

#include "StatReCal4Bins.h"

//TString BsName, TString BPlusName

void BP4Bins(){


	gSystem->Load("tdrstyle.C");

	setTDRStyle();
	

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TString BsName = "BsBP4Bins/CrossSectionPbPbBPlus.root";



	TFile * finBs = new TFile(BsName.Data());


	//TGraphAsymmErrors * BsCross = (TGraphAsymmErrors *) finBs->Get("gaeCrossSyst");
	//TGraphAsymmErrors * BPlusCross = (TGraphAsymmErrors *) finBPlus->Get("gaeCrossSyst");

	TH1D * hBsCross=(TH1D*)finBs->Get("hPtSigma");


	double BsCorr[nBins];
	double BPCorr[nBins];





	hBsCross->SetLineWidth(3);
	hBsCross->SetLineColor(BsPointColor);
	hBsCross->SetMarkerColor(BsPointColor);
	hBsCross->SetMarkerStyle(33);
	hBsCross->SetMarkerSize(2.2);

	double tpadr = 1;
	double xBPlus;
	double yBPlus;
	double yBlusErrU;
	double yBlusErrD;

	double xBs;
	double yBs;
	double yBsErrU;
	double yBsErrD;

	double xr[nBins];
	double xrlow[nBins];
	double xrhigh[nBins];

	double Ratio[nBins];
	double RatioErrU[nBins];
	double RatioErrD[nBins];



	/*

	for(int i =0; i < nBins; i++){
			BsCross->GetPoint(i,xBs,yBs);
		BPlusCross->GetPoint(i,xBPlus,yBPlus);
		yBsErrU = BsCross->GetErrorYhigh(i);
		yBsErrD = BsCross->GetErrorYlow(i);
		yBlusErrU = BPlusCross->GetErrorYhigh(i);
		yBlusErrD = BPlusCross->GetErrorYlow(i);
		xr[i] = xBs;
		xrlow[i] = BsCross->GetErrorXlow(i);
		xrhigh[i] = BsCross->GetErrorXhigh(i);

		Ratio[i] = yBs/yBPlus;
		RatioErrU[i] = Ratio[i]*TMath::Sqrt((yBsErrU/yBs)*(yBsErrU/yBs) + (yBlusErrU/yBPlus)*(yBlusErrU/yBPlus) );
		RatioErrD[i] = Ratio[i]*TMath::Sqrt((yBsErrD/yBs)*(yBsErrD/yBs) + (yBlusErrD/yBPlus)*(yBlusErrD/yBPlus) );
	}
	*/


//	TGraphAsymmErrors* BstoBPlus = new TGraphAsymmErrors(nBins,xr,Ratio,xrlow,xrhigh,RatioErrD,RatioErrU);


	TCanvas *c = new TCanvas("c","c",600,600);
	c->cd();

	hBsCross->GetXaxis()->CenterTitle();
	hBsCross->GetYaxis()->CenterTitle();
	hBsCross->GetYaxis()->SetTitleOffset(1.5);

	hBsCross->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hBsCross->GetYaxis()->SetTitle("#frac{1}{T_{AA}  N_{MB}} #frac{dN}{dp_{T}} ( pb GeV^{-1}c)");

	//double NMB = 11.1;
	double NMB = 11.823737719;

	hBsCross->Scale(1.0/NMB);



	for(int i =0; i < nBins; i++){

		cout << "Bs Corrected Yield = " << 	hBsCross->GetBinContent(i+1) << "     Start Err = " << hBsCross->GetBinError(i+1)/hBsCross->GetBinContent(i+1) << endl;
		cout << "Bs Corrected Yield Error = " << 	hBsCross->GetBinError(i+1) << endl;

	}



	hBsCross->SetMinimum(1000);
	hBsCross->SetMaximum(100000000);
	hBsCross->Draw("ep");

	double SystErrUp[nBins];
	double SystErrDown[nBins];

	double TnPErrBPUp[nBins] ={0.0972,0.0696,0.0588,0.0585};
	double TnPErrBPDown[nBins] ={0.0828,0.0648,0.0552,0.0560};

	//BPlus//
	double SystErrBP[nBins];
	double TrackingErrBP[nBins] ={0.05,0.05,0.05,0.05};
	double SelErrBP[nBins] ={0.0567,0.1530,0.0361,0.0174};
	double PTErrBP[nBins] ={0.00128,0.00206,0.0000,0.00010};
//	double AccErrBP[nBins] ={0.0001,0.00047,0.00026,0.00055};
	double AccErrBP[nBins] ={0.0000,0.0000,0.0000,0.00000};
	
	double PDFBErrBP[nBins] ={0.0446,0.0267,0.0274,0.0236};
	double PDFSErrBP[nBins] ={0.00117,0.00546,0.00576,0.0103};
	double MCStatBP[nBins] ={0.1486,0.0375,0.0220,0.0151};
	
	double sPLOTBP[nBins] = {0.0204,0.0003,0.0010,0.0018};

//	double MCStat[nBins] ={0.0,0.0,0.0,0.0};   // 2D Map MC Stat
//	double EffCorrUp[nBins] ={0.163,0.0900,0.0510,0.0390};  //Estimated from the width of <acc x eff>
//	double EffCorrDown[nBins] ={0.163,0.0900,0.0510,0.0390};  //Estimated from the width of <acc x eff>


//	double EffCorrUp[nBins] ={0.427,0.224,0.0560,0.0450};  //Estimated from the RMS of <1/acc x eff>
//	double EffCorrDown[nBins] ={0.427,0.224,0.0560,0.0450};  //Estimated from the RMS of <1/acc x eff>


//	double EffCorrUp[nBins] ={0.460,0.270,0.0570,0.0450};  //Estimated from the 33% deviation from the mean//
//	double EffCorrDown[nBins] ={0.380,0.190,0.0570,0.0390};  //Estimated from the 33% deviation from the mean//


	double EffCorrUp[nBins] ={0.0,0.0,0.0,0.0};  //Estimated from the RMS of <1/acc x eff>
	double EffCorrDown[nBins] ={0.0,0.0,0.0,0.0};  //Estimated from the RMS of <1/acc x eff>



	for(int i = 0; i < nBins; i++){

		SystErrUp[i] =  sqrt(TrackingErrBP[i] * TrackingErrBP[i] + SelErrBP[i] *SelErrBP[i] + PTErrBP[i] * PTErrBP[i] + AccErrBP[i]* AccErrBP[i] + PDFBErrBP[i]* PDFBErrBP[i] + PDFSErrBP[i]* PDFSErrBP[i] + TnPErrBPUp[i]* TnPErrBPUp[i] + MCStatBP[i] * MCStatBP[i]);
		SystErrDown[i] =  sqrt(TrackingErrBP[i] * TrackingErrBP[i] + SelErrBP[i] *SelErrBP[i] + PTErrBP[i] * PTErrBP[i] + AccErrBP[i]* AccErrBP[i] + PDFBErrBP[i]* PDFBErrBP[i] + PDFSErrBP[i]* PDFSErrBP[i] + TnPErrBPDown[i]* TnPErrBPDown[i]+ MCStatBP[i] * MCStatBP[i]);


		cout << "i = "  << i  << "    SystErrUp = "  << SystErrUp[i]  <<  "    SystErrDown = "  << SystErrDown[i] << endl;

	}

	double Y[nBins];


	double X[nBins];
	double YErr[nBins];
	//	double SystErr[nBins] ={0.220,0.182,0.201,0.147};
	double YErrorHigh[nBins];
	double YErrorLow[nBins];
	double MyXlow[nBins] = {1.5,2.5,2.5,15};
	double MyXhigh[nBins] = {1.5,2.5,2.5,15};


	for(int i = 0; i < nBins; i++){
		Y[i] = hBsCross->GetBinContent(i+1);
		YErr[i] = hBsCross->GetBinError(i+1);
		X[i] = (ptBins[i]+ptBins[i+1])/2;
		YErrorHigh[i] =  hBsCross->GetBinContent(i+1)*SystErrUp[i];
		YErrorLow[i] =  hBsCross->GetBinContent(i+1)*SystErrDown[i];

	}
	
	double ptBinsSave[5]={7,10,15,20,50};


	ofstream outratio("OutText/corryield_pt_Bp_New.txt");
	//outratio << "ptmin" << "   " << "ptmax" << "   " <<  "xsec" << "   " << "statUncert" << "   " << "SystUncert Up" <<  "   " << "SystUncert Down"  << "   "  <<  "glbUncert Up " << "   " <<  "glbUncert Down" << endl;
  	  outratio << "NPart" << "   " <<  "xsec" << "   " << "statUncertUp" << "   " << "statUncertDown"  << "   " << "systUncert Up" << "   " << "systUncert Down" << "   " <<    "glbUncert Up"<< "   " <<  "glbUncert Down "  << endl;

	for(int i = 0; i < nBins; i++){
		outratio << ptBinsSave[i] << "   " << ptBinsSave[i+1] << "   " << Y[i] << "   " << StatUpBP[i] << "    " <<  StatDownBP[i]  << "   " << SystErrUp[i]  << "   " << SystErrDown[i] << "   "  <<  0.0375 << "   " << 0.0375 << endl;

	}


	TGraphAsymmErrors* MyCrossSyst = new TGraphAsymmErrors(nBins,X,Y,MyXlow,MyXhigh,YErrorLow,YErrorHigh);
	MyCrossSyst->SetName("gaeCrossSyst");
	MyCrossSyst->SetMarkerStyle(20);
	MyCrossSyst->SetMarkerSize(0.8/tpadr);
	MyCrossSyst->SetFillColor(1);
	MyCrossSyst->SetFillStyle(0); 
	MyCrossSyst->SetLineWidth(2);
	MyCrossSyst->SetLineColor(1);
	MyCrossSyst->Draw("5same");  



	TLatex* texlumi = new TLatex(0.96,0.97,"1.7 nb^{-1} (PbPb) 5.02 TeV");
	texlumi->SetNDC();
	texlumi->SetTextAlign(32);
	texlumi->SetTextFont(42);
	texlumi->SetTextSize(0.05);
	texlumi->SetLineWidth(2);
	texlumi->Draw("SAME");


	TLatex* texcms = new TLatex(0.72,0.88,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw("SAME");


	TLatex* texcent = new TLatex(0.62,0.78,"Cent. 0-90%");
	texcent->SetNDC();
	texcent->SetTextFont(42);
	texcent->SetTextSize(0.05);
	texcent->SetLineWidth(2);
	texcent->Draw("SAME");

	TLatex *texY = new TLatex(0.17,0.68," 10 GeV/c < B p_{T} < 50 GeV/c and B |y| < 2.4");
	texY->SetNDC();
	texY->SetTextFont(42);
	texY->SetTextSize(0.04);
	texY->SetLineWidth(2);
	texY->Draw("SAME");

	TLatex *texY2 = new TLatex(0.17,0.61," 7 GeV/c < B p_{T} < 10 GeV/c and 1.5 < B |y| < 2.4");
	texY2->SetNDC();
	texY2->SetTextFont(42);
	texY2->SetTextSize(0.04);
	texY2->SetLineWidth(2);
	texY2->Draw("SAME");



	c->SetLogy();
	c->SaveAs("BPCorrYieldPt.pdf");


}
