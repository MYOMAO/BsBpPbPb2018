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
#include "parameters1Bin.h"
#include "tdrstyle.C"

#include "StatReCal1Bin.h"

const int _nBins = nBinsCent;
double *_ptBins = ptBinsCent;
//TString BsName, TString BPlusName

void Bs1Bin(){


	gSystem->Load("tdrstyle.C");

	setTDRStyle();


	//gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetPadRightMargin(cRightMargin);
	gStyle->SetPadLeftMargin(cLeftMargin);
	gStyle->SetPadTopMargin(cTopMargin);
	gStyle->SetPadBottomMargin(cBottomMargin);


	TString BsName = "BsBP1Bin/CrossSectionPbPbBs.root";


	TFile * finBs = new TFile(BsName.Data());
	TH1D * hBsCross=(TH1D*)finBs->Get("hPtSigma");




	hBsCross->Sumw2();



	for(int i =0; i < _nBins; i++){

		cout << "BsYield = " << 	hBsCross->GetBinContent(i+1) << endl;
		cout << "BsYield Error = " << 	hBsCross->GetBinError(i+1) << endl;
		cout << "BsYield Frac Error = " << 	hBsCross->GetBinError(i+1)/hBsCross->GetBinContent(i+1) << endl;
	}
	TCanvas *c = new TCanvas("c","c",600,600);

	double NPartSwap[_nBins+1];
	NPartSwap[0] = 0;
	for(int i = 0; i < _nBins;i++){
		NPartSwap[i+1] =  npart[_nBins - i - 1];
		cout << "NPartSwap = " << NPartSwap[i+1] << endl;
	}



	TH1D * NPartPlot = new TH1D("NPartPlot","",_nBins,NPartSwap);


	for(int i = 0; i < _nBins; i++){

		int j = NPartPlot->FindBin(npart[i]);
		NPartPlot->SetBinContent(j-1,hBsCross->GetBinContent(i+1));
		NPartPlot->SetBinError(j-1,hBsCross->GetBinError(i+1));


	}

	NPartPlot->SetLineWidth(3);
	NPartPlot->SetLineColor(kAzure+10);
	NPartPlot->SetMarkerColor(kAzure+10);
	NPartPlot->SetMarkerStyle(33);
	NPartPlot->SetMarkerSize(2.2);

	double tpadr = 1;

	NPartPlot->GetXaxis()->SetTitle("<N_{Part}>");
	NPartPlot->GetYaxis()->SetTitle("#frac{1}{T_{AA}} #frac{dN}{dp_{T}} ( pb GeV^{-1}c)");
	NPartPlot->GetXaxis()->CenterTitle();
	NPartPlot->GetYaxis()->CenterTitle();
	NPartPlot->GetYaxis()->SetTitleOffset(1.3);
//	NPartPlot->Draw("epx0");

	TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,300,10.,8000,30000);  
	hemptySigma->GetXaxis()->CenterTitle();
	hemptySigma->GetYaxis()->CenterTitle();
	hemptySigma->GetYaxis()->SetTitle("#frac{1}{T_{AA}N_{MB}} #frac{dN}{dp_{T}} ( pb GeV^{-1}c)");

	hemptySigma->GetXaxis()->SetTitle("<N_{Part}>");
	hemptySigma->GetXaxis()->SetTitleOffset(1.);
	hemptySigma->GetYaxis()->SetTitleOffset(2.5);
	hemptySigma->GetXaxis()->SetTitleSize(0.055/tpadr);
	hemptySigma->GetYaxis()->SetTitleSize(0.050/1.5);
	hemptySigma->GetXaxis()->SetTitleFont(42);
	hemptySigma->GetYaxis()->SetTitleFont(42);
	hemptySigma->GetXaxis()->SetLabelFont(42);
	hemptySigma->GetYaxis()->SetLabelFont(42);
	hemptySigma->GetXaxis()->SetLabelSize(0.048/tpadr);
	hemptySigma->GetYaxis()->SetLabelSize(0.048/1.5);  



	hemptySigma->Draw();


	double SystErrUp[_nBins];
	double SystErrDown[_nBins];

	double SystTAA[_nBins ] = {0.022};
	double NMBSystUp[_nBins ] = {0.0103};
	double NMBSystDown[_nBins ] = {0.0051};


	double TrackingErrBs[_nBins] ={0.10};
	//double SelErrBs[_nBins] ={0.0249};
	double SelErrBs[_nBins] ={0.0181479};

	double PTErrBs[_nBins] ={0.00012};
	double AccErrBs[_nBins] ={0.0};
	double PDFBErrBs[_nBins] ={0.0154};
	double PDFSErrBs[_nBins] ={0.0168};
	double TnPErrBsUp[_nBins] ={0.0836};
	double TnPErrBsDown[_nBins] ={0.0737};
	double MCStat[_nBins] ={0.0446};
	double sPLOTBs[_nBins] ={0.0024};


	for(int i = 0; i < _nBins; i++){

		SystErrUp[i] =  sqrt(TrackingErrBs[i] * TrackingErrBs[i] + SelErrBs[i] *SelErrBs[i] + PTErrBs[i] * PTErrBs[i] + AccErrBs[i]* AccErrBs[i] + PDFBErrBs[i]* PDFBErrBs[i] + PDFSErrBs[i]* PDFSErrBs[i] + TnPErrBsUp[i]* TnPErrBsUp[i] + MCStat[i] * MCStat[i] + SystTAA[i] * SystTAA[i] + NMBSystUp[i] * NMBSystUp[i]);

		SystErrDown[i] =  sqrt(TrackingErrBs[i] * TrackingErrBs[i] + SelErrBs[i] *SelErrBs[i] + PTErrBs[i] * PTErrBs[i] + AccErrBs[i]* AccErrBs[i] + PDFBErrBs[i]* PDFBErrBs[i] + PDFSErrBs[i]* PDFSErrBs[i] + TnPErrBsDown[i]* TnPErrBsDown[i]+ MCStat[i] * MCStat[i]+ SystTAA[i] * SystTAA[i] + NMBSystDown[i] * NMBSystDown[i]);

	
		cout << "i = "  << i  << "    SystErrUp = "  << SystErrUp[i]  <<  "    SystErrDown = "  << SystErrDown[i] << endl;

	}

	//double NMB = 11.1;
	double NMB = 11.823737719;

	double CorrYield[_nBins];
	double CorrYieldErr[_nBins];
	double X[_nBins];

	for(int i = 0; i < _nBins;i++){
		CorrYield[i] = NPartPlot->GetBinContent(i+1)/NMB ;
		CorrYieldErr[i] = NPartPlot->GetBinError(i+1)/NMB ;
		X[i] = NPartSwap[i+1];
	}
	double MyX[_nBins];
	double MyXlow[_nBins] = {5};
	double MyXhigh[_nBins] = {5};
	//double SystErr[_nBins] ={0.552};
	double MyY[_nBins];
	double Mycrosssystlow[_nBins];
	double Mycrosssysthigh[_nBins];

	double PtRange = 40;

	for(int i = 0; i < _nBins; i++){
		MyX[i] =  (NPartSwap[i] + NPartSwap[i+1])/2;
		MyY[i] =  NPartPlot->GetBinContent(i+1)/NMB * PtRange;
		Mycrosssystlow[i] = MyY[i]* SystErrDown[i]* PtRange;
		Mycrosssysthigh[i] = MyY[i]* SystErrUp[i]* PtRange;
	}



	ofstream outratio("OutText/corryield_cent_0_90_Bs_New.txt");
	outratio << "NPart" << "   " <<  "xsec" << "   " << "statUncertUp" << "   " << "statUncertDown"  << "   " << "systUncert Up" << "   " << "systUncert Down" << "   " <<    "glbUncert Up"<< "   " <<  "glbUncert Down "  << endl;

	for(int i = 0; i < _nBins; i++){
		outratio <<  X[i]  << "   " << MyY[i] << "   " << StatUpBs[i] << "   " <<  StatDownBs[i] << "   " << SystErrUp[i]  << "   " << SystErrDown[i] << "   "   << 0.076 << "   " << 0.076 << endl;

	}


	TGraphErrors* GNPartPlot = new TGraphErrors(_nBins,X,CorrYield,0,CorrYieldErr);
	GNPartPlot->SetName("GNPartPlot");
	GNPartPlot->SetLineWidth(3);
	GNPartPlot->SetLineColor(kAzure+10);
	GNPartPlot->SetMarkerColor(kAzure+10);
	GNPartPlot->SetMarkerStyle(33);
	GNPartPlot->SetMarkerSize(2.2);


	GNPartPlot->Draw("ep");  



	TGraphAsymmErrors* MyCrossSyst = new TGraphAsymmErrors(_nBins,X,MyY,MyXlow,MyXhigh,Mycrosssystlow,Mycrosssysthigh);
	MyCrossSyst->SetName("gaeCrossSyst");
	MyCrossSyst->SetMarkerStyle(20);
	MyCrossSyst->SetMarkerSize(0.8/tpadr);
	MyCrossSyst->SetFillColor(1);
	MyCrossSyst->SetFillStyle(0); 
	MyCrossSyst->SetLineWidth(2);
	MyCrossSyst->SetLineColor(1);
	MyCrossSyst->Draw("5same");  






	TLatex* texlumi = new TLatex(0.96,0.95,"1.5 nb^{-1} (PbPb) 5.02 TeV");
	texlumi->SetNDC();
	texlumi->SetTextAlign(32);
	texlumi->SetTextFont(42);
	texlumi->SetTextSize(0.05);
	texlumi->SetLineWidth(2);
	texlumi->Draw("SAME");


	TLatex* texcms = new TLatex(0.21,0.88,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw("SAME");


	TLatex* texcent = new TLatex(0.23,0.75,"7 GeV/c < B p_{T} < 50 GeV/c and B |y| < 2.4");
	texcent->SetNDC();
	texcent->SetTextFont(42);
	texcent->SetTextSize(0.04);
	texcent->SetLineWidth(2);
	texcent->Draw("SAME");

	/*
	TLatex *texY = new TLatex(0.16,0.65,"B |y| < 2.4");
	texY->SetNDC();
	texY->SetTextFont(42);
	texY->SetTextSize(0.04);
	texY->SetLineWidth(2);
	texY->Draw("SAME");
*/
	TLatex *texY2 = new TLatex(0.23,0.70," 7 GeV/c < B p_{T} < 10 GeV/c and B |y| > 1.5");
	texY2->SetNDC();
	texY2->SetTextFont(42);
	texY2->SetTextSize(0.04);
	texY2->SetLineWidth(2);
	texY2->Draw("SAME");


	TLine *line = new TLine(0,10.5/40.5,300,10.5/40.5);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("SAME");



	TLatex* Bin1 = new TLatex(0.50,0.65,"Cent. 0 - 90%");
	Bin1->SetNDC();
	Bin1->SetTextAlign(13);
	Bin1->SetTextFont(62);//61
	Bin1->SetTextSize(0.04);
	Bin1->SetLineWidth(2);
	Bin1->Draw("SAME");



	double NPartMin = 0;
	double NPartMax = 300;

	c->SaveAs("FinalPlots/BsCorrYieldCent_0_90.pdf");



}
