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
#include "StatReCal4Bins.h"

//TString BsName, TString BPlusName

void BsOverBPlus4Bins(){
	int TNP = 1; 

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TString BsName; 
	if(TNP == 1) BsName = "BsBP4Bins/CrossSectionPbPbBs.root";
	if(TNP == 0) BsName = "BsBP/CrossSectionPbPbBsNoTnP.root";

	TString	BPlusName;
	if(TNP == 1) BPlusName = "BsBP4Bins/CrossSectionPbPbBPlus.root";
	if(TNP == 0) BPlusName = "BsBP/CrossSectionPbPbBPlusNoTnP.root";



	TFile * finBs = new TFile(BsName.Data());
	TFile * finBPlus = new TFile(BPlusName.Data());

	//TGraphAsymmErrors * BsCross = (TGraphAsymmErrors *) finBs->Get("gaeCrossSyst");
	//TGraphAsymmErrors * BPlusCross = (TGraphAsymmErrors *) finBPlus->Get("gaeCrossSyst");

	TH1D * hBPlusCross=(TH1D*)finBPlus->Get("hPtSigma");
	TH1D * hBsCross=(TH1D*)finBs->Get("hPtSigma");


	double BsCorr[nBins];
	double BPCorr[nBins];

	double TnPErrBsUp[nBins] ={0.20,0.0934,0.0601,0.0605};
	double TnPErrBsDown[nBins] ={0.142,0.0808,0.0568,0.0573};

//	double TnPErrBPUp[nBins] ={0.1039,0.0699,0.0590,0.0584};
//	double TnPErrBPDown[nBins] ={0.0874,0.0651,0.0554,0.0559};

	double TnPErrBPUp[nBins] ={0.0972,0.0696,0.0588,0.0585};
	double TnPErrBPDown[nBins] ={0.0828,0.0648,0.0552,0.0560};


	double BsUp[nBins];
	double BsDown[nBins];


	double BPUp[nBins];
	double BPDown[nBins];

	double BsBPUp[nBins];
	double BsBPDown[nBins];

	double BsBPUpSyst[nBins];
	double BsBPDownSyst[nBins];

	double BsBPCenter[nBins];


	for(int i = 0; i < nBins; i++){

		BsUp[i]	= hBsCross->GetBinContent(i+1) * (1 + TnPErrBsUp[i]);
		BPUp[i]	= hBPlusCross->GetBinContent(i+1) * (1 + TnPErrBPUp[i]);
		BsDown[i]	= hBsCross->GetBinContent(i+1) * (1 - TnPErrBsDown[i]);
		BPDown[i]	= hBPlusCross->GetBinContent(i+1) * (1 - TnPErrBPDown[i]);

		BsBPUp[i] = BsUp[i]/BPUp[i];
		BsBPDown[i] = BsDown[i]/BPDown[i];

	//	cout << "TNP UP: " << "  Bs = " <<  BsUp[i] << "  BP =   " << BPUp[i]  <<  "   Bs/B+ = " << BsBPUp[i]   << endl;
//		cout << "TNP Down: " << "  Bs = " <<  BsDown[i] << "  BP =   " << BPDown[i]  <<  "   Bs/B+ = " << BsBPDown[i]   << endl;

	}




	hBsCross->Divide(hBPlusCross);
	hBsCross->SetMaximum(1.2);
	hBsCross->SetMinimum(0.0);



	for(int i = 0; i < nBins; i++){

		BsBPCenter[i] = hBsCross->GetBinContent(i+1);

		BsBPUpSyst[i] = TMath::Abs(BsBPUp[i] - BsBPCenter[i])/BsBPCenter[i];
		BsBPDownSyst[i] = TMath::Abs(BsBPDown[i] - BsBPCenter[i])/BsBPCenter[i];

		cout << "TNP UP Final: " << 	BsBPUpSyst[i] << endl;
		cout << "TNP Down Final: " << BsBPDownSyst[i]  << endl;

	}



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
	hBsCross->GetYaxis()->SetTitleOffset(1.3);

	hBsCross->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	hBsCross->GetYaxis()->SetTitle("B^{0}_{S}/B^{+}");


	for(int i =0; i < nBins; i++){

		cout << "Ratio = " << 	hBsCross->GetBinContent(i+1) << endl;
		cout << "Ratio Error = " << 	hBsCross->GetBinError(i+1) << endl;
		cout << "Ratio Frac Error = " << hBsCross->GetBinError(i+1)/hBsCross->GetBinContent(i+1) << endl;
	}


	hBsCross->Draw("ep");


	double SystErrUp[nBins];
	double SystErrDown[nBins];

	//Bs//
	double SystErrBs[nBins];
	double TrackingErrBs[nBins] ={0.10,0.10,0.10,0.10};
//	double SelErrBs[nBins] ={0.378,0.0479,0.0441,0.1044};
	double SelErrBs[nBins] ={0.3472,0.0474,0.0496,0.1036};

	double PTErrBs[nBins] ={0.0017,0.00013,0.00008,0.00093};
//	double AccErrBs[nBins] ={0.0046,0.0343,0.0468,0.0425};
	double AccErrBs[nBins] ={0.000,0.00,0.00,0.00};

	double PDFBErrBs[nBins] ={0,0.0272,0.0156,0.0329};
	double PDFSErrBs[nBins] ={0.0862,0.0262,0.0099,0.00177};
	double MCStatBs[nBins] ={0.288,0.0626,0.0317,0.0349};
	double sPLOTBs[nBins] ={0.21,0.0162,0.0112,0.0077};

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

	double TrackingErrBsBP[nBins] ={0.05,0.05,0.05,0.05};
	double StatUp[nBins];
	double StatDown[nBins];

	for(int i = 0; i < nBins; i++){

		SystErrBs[i] =  sqrt(SelErrBs[i] *SelErrBs[i] + PTErrBs[i] * PTErrBs[i] + AccErrBs[i]* AccErrBs[i] + PDFBErrBs[i]* PDFBErrBs[i] + PDFSErrBs[i]* PDFSErrBs[i] + MCStatBs[i] * MCStatBs[i]);
		SystErrBP[i] =  sqrt(SelErrBP[i] *SelErrBP[i] + PTErrBP[i] * PTErrBP[i] + AccErrBP[i]* AccErrBP[i] + PDFBErrBP[i]* PDFBErrBP[i] + PDFSErrBP[i]* PDFSErrBP[i]  + MCStatBP[i] * MCStatBP[i]);

		SystErrUp[i] = sqrt(SystErrBs[i]* SystErrBs[i] + SystErrBP[i] * SystErrBP[i] + TrackingErrBsBP[i] * TrackingErrBsBP[i] + BsBPUpSyst[i] * BsBPUpSyst[i]);

		SystErrDown[i] = sqrt(SystErrBs[i]* SystErrBs[i] + SystErrBP[i] * SystErrBP[i] + TrackingErrBsBP[i] * TrackingErrBsBP[i] + BsBPDownSyst[i] * BsBPDownSyst[i]);

		StatUp[i] = sqrt(StatUpBs[i] * StatUpBs[i] + StatUpBP[i] * StatUpBP[i]);	
		StatDown[i] = sqrt(StatDownBs[i] * StatDownBs[i] + StatDownBP[i] * StatDownBP[i]);
		cout << "i = "  << i  << "    SystErrUp = "  << SystErrUp[i] << "  SystErrDown =  " << SystErrDown[i] << endl;

	}



	double Y[nBins];


	double X[nBins];
	double YErr[nBins];
	//	double SystErr[nBins] ={0.220,0.182,0.201,0.147};
	double YErrorHigh[nBins];
	double YErrorLow[nBins];
	double MyXlow[nBins] = {2.5,2.5,2.5,15};
	double MyXhigh[nBins] = {2.5,2.5,2.5,15};

	for(int i = 0; i < nBins; i++){
		Y[i] = hBsCross->GetBinContent(i+1);
		YErr[i] = hBsCross->GetBinError(i+1);
		X[i] = (ptBins[i]+ptBins[i+1])/2;
		YErrorHigh[i] =  hBsCross->GetBinContent(i+1)*SystErrUp[i];
		YErrorLow[i] =  hBsCross->GetBinContent(i+1)*SystErrDown[i];

	}



	double	glbUncert = TMath::Sqrt(2.8*2.8 + 7.6*7.6)/100;



	double ptBinsSave[5]={7,10,15,20,50};

	ofstream outratio("OutText/Ratio/ratio_pt.txt");
	outratio << "ptmin" << "   " << "ptmax" << "   " <<  "xsec" << "   " << "statUncertUp"  << "   " << "statUncertDown" << "   " << "systUncert Up "  << "   " << "systUncert Down "  << "   " <<  "glbUncert Up " << "   " <<  "glbUncert Down" << endl;

	for(int i = 0; i < nBins; i++){
		outratio << ptBinsSave[i] << "   " << ptBinsSave[i+1] << "   " << Y[i] << "   " << StatUp[i] << "   " << StatDown[i] << "   " << SystErrUp[i] << "   " << SystErrDown[i] << "   " << glbUncert  << "   " << glbUncert << endl;

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




	TLatex* texlumi = new TLatex(0.96,0.95,"1.7 nb^{-1} (PbPb) 5.02 TeV");
	texlumi->SetNDC();
	texlumi->SetTextAlign(32);
	texlumi->SetTextFont(42);
	texlumi->SetTextSize(0.05);
	texlumi->SetLineWidth(2);
	texlumi->Draw("SAME");


	TLatex* texcms = new TLatex(0.17,0.88,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw("SAME");


	TLatex* texcent = new TLatex(0.50,0.62,"Cent. 0-90%");
	texcent->SetNDC();
	texcent->SetTextFont(42);
	texcent->SetTextSize(0.04);
	texcent->SetLineWidth(2);
	texcent->Draw("SAME");

	TLatex *texY = new TLatex(0.21,0.79,"7 GeV/c < B p_{T} < 50 GeV/c and B |y| < 2.4");
	texY->SetNDC();
	texY->SetTextFont(42);
	texY->SetTextSize(0.04);
	texY->SetLineWidth(2);
	texY->Draw("SAME");


	TLatex *texY2 = new TLatex(0.21,0.70,"7 GeV/c < B p_{T} < 10 GeV/c and B |y| > 1.5");
	texY2->SetNDC();
	texY2->SetTextFont(42);
	texY2->SetTextSize(0.04);
	texY2->SetLineWidth(2);
	texY2->Draw("SAME");



	/*
	   TLine *line = new TLine(ptBins[0],10.5/40.5,ptBins[nBins],10.5/40.5);
	   line->SetLineStyle(2);
	   line->SetLineWidth(2);
	   line->Draw("SAME");
	   */


	double BsFrag = 10.3;
	double BsErr = 0.5;

	double BPFrag = 40.5;
	double BPErr = 0.6;

	const int BandBin = 1;
	double BandX[BandBin] = {(ptBins[nBins]+ptBins[0])/2};
	double BandY[BandBin] = {BsFrag/BPFrag};


	double BandXErr[BandBin] = {(ptBins[nBins]-ptBins[0])/2};
	double BandYErr[BandBin] = { BsFrag/BPFrag*TMath::Sqrt((BsErr/BsFrag)*(BsErr/BsFrag)+(BPErr/BPFrag)*(BPErr/BPFrag)) };



	TGraphAsymmErrors * FragBand = new TGraphAsymmErrors(BandBin,BandX,BandY,BandXErr,BandXErr,BandYErr,BandYErr);
	FragBand->SetName("BandErr");
	FragBand->SetMarkerStyle(20);
	FragBand->SetMarkerSize(0.8);
	FragBand->SetFillColorAlpha(kGreen,0.5);
	FragBand->SetFillStyle(3004);
	FragBand->SetLineWidth(2);
	FragBand->SetLineColor(kGreen);

	FragBand->Draw("5same");  


	TLegend* leg = new TLegend(0.40,0.38,0.76,0.58,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->AddEntry(hBsCross,"Data Points","pl");
	leg->AddEntry(MyCrossSyst,"Syst. Uncert.","l");
	leg->AddEntry(FragBand,"f_{s}/f_{u} in vacuum","l");
	leg->Draw("same");

	if(TNP == 1)	c->SaveAs("BstoBPlusPt.pdf");
	if(TNP == 0)	c->SaveAs("BstoBPlusPtNoTnP.pdf");

	//Following is including TAMU//


	std::ifstream TAMUBsBP("TAMUPT.dat");

	const int NBinsTAMU = 150; 
	double TAMUBsBPPt[NBinsTAMU];
	double TAMUBsBPPtErr[NBinsTAMU];
	
	double TAMUBsBPRatio[NBinsTAMU];
	double TAMUBsBPRatioErr[NBinsTAMU];

	for(int i = 0; i < NBinsTAMU; i++){

	TAMUBsBP >> TAMUBsBPPt[i] >> TAMUBsBPRatio[i];
	
	}

	for(int i = 0; i < NBinsTAMU; i++){

		TAMUBsBPPtErr[i] = 0.1;
		TAMUBsBPRatioErr[i] = 0.01;
		cout  << "TAMUBsBPPt[i] = "  <<  TAMUBsBPPt[i] << "     TAMUBsBPRatio[i] = " <<  TAMUBsBPRatio[i] << endl;
	
	}




	TGraphErrors* TAMUTheory = new TGraphErrors(NBinsTAMU,TAMUBsBPPt,TAMUBsBPRatio,TAMUBsBPPtErr,TAMUBsBPRatioErr);
	TAMUTheory->SetName("TAMUTheory");
	TAMUTheory->SetMarkerStyle(20);
	TAMUTheory->SetMarkerSize(0.0);
	TAMUTheory->SetFillColor(kOrange+3);
	TAMUTheory->SetFillStyle(3002); 
	TAMUTheory->SetLineColor(kOrange);
	TAMUTheory->SetLineWidth(2.5);
	TAMUTheory->Draw("5same");  
	hBsCross->Draw("epSAME");

	leg->AddEntry(TAMUTheory,"TAMU 0 - 100%","l");
	leg->Draw("SAME");

	if(TNP == 1)	c->SaveAs("BstoBPlusPtTAMU.pdf");
	if(TNP == 0)	c->SaveAs("BstoBPlusPtNoTnPTAMU.pdf");




}
