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

#include "parameters2Bins.h"
#include "StatReCal2Bins.h"

const int _nBins = nBinsCent;
double *_ptBins = ptBinsCent;
//TString BsName, TString BPlusName




void BsOverBPlus2Bins(){

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetPadRightMargin(cRightMargin);
	gStyle->SetPadLeftMargin(cLeftMargin);
	gStyle->SetPadTopMargin(cTopMargin);
	gStyle->SetPadBottomMargin(cBottomMargin);


	TString BsName = "BsBP2Bins/CrossSectionPbPbBs.root";
	TString	BPlusName = "BsBP2Bins/CrossSectionPbPbBPlus.root";

	TFile * finBs = new TFile(BsName.Data());
	TFile * finBPlus = new TFile(BPlusName.Data());


	TH1D * hBPlusCross=(TH1D*)finBPlus->Get("hPtSigma");
	TH1D * hBsCross=(TH1D*)finBs->Get("hPtSigma");

	double NMB = 11.1;
	//hBsCross->Scale(1/NMB);
	
//	double	TnPErrBPUp[_nBins] ={0.0660, 0.0673};
//	double	TnPErrBPDown[_nBins] ={0.0613, 0.0631};

	
	double	TnPErrBPUp[_nBins] ={0.0659131, 0.066841};
	double	TnPErrBPDown[_nBins] ={0.0618082, 0.0631};

//	double	TnPErrBsUp[_nBins] ={0.0798, 0.222};
//	double	TnPErrBsDown[_nBins] ={0.0709, 0.140};

	double	TnPErrBsUp[_nBins] ={0.0723, 0.0913};
	double	TnPErrBsDown[_nBins] ={0.0664, 0.0777};

	double BsUp[_nBins];
	double BsDown[_nBins];

	double BPUp[_nBins];
	double BPDown[_nBins];

	double BsBPUp[_nBins];
	double BsBPDown[_nBins];

	double BsBPUpSyst[_nBins];
	double BsBPDownSyst[_nBins];

	double BsBPCenter[_nBins];


	for(int i = 0; i < _nBins; i++){

		BsUp[i]	= hBsCross->GetBinContent(i+1) * (1 + TnPErrBsUp[i]);
		BPUp[i]	= hBPlusCross->GetBinContent(i+1) * (1 + TnPErrBPUp[i]);
		BsDown[i]	= hBsCross->GetBinContent(i+1) * (1 - TnPErrBsDown[i]);
		BPDown[i]	= hBPlusCross->GetBinContent(i+1) * (1 - TnPErrBPDown[i]);

		BsBPUp[i] = BsUp[i]/BPUp[i];
		BsBPDown[i] = BsDown[i]/BPDown[i];


			cout << "TNP UP: " << "  Bs = " <<  BsUp[i] << "  BP =   " << BPUp[i]  <<  "   Bs/B+ = " << BsBPUp[i]   << endl;
			cout << "TNP Down: " << "  Bs = " <<  BsDown[i] << "  BP =   " << BPDown[i]  <<  "   Bs/B+ = " << BsBPDown[i]   << endl;


	}




	hBsCross->Sumw2();
	hBPlusCross->Sumw2();

	hBsCross->Divide(hBPlusCross);



	for(int i = 0; i < _nBins; i++){

		BsBPCenter[i] = hBsCross->GetBinContent(i+1);

		BsBPUpSyst[i] = TMath::Abs(BsBPUp[i] - BsBPCenter[i])/BsBPCenter[i];
		BsBPDownSyst[i] = TMath::Abs(BsBPDown[i] - BsBPCenter[i])/BsBPCenter[i];

		cout << "TNP UP Final: " << 	BsBPUpSyst[i] << endl;
		cout << "TNP Down Final: " << BsBPDownSyst[i]  << endl;

	}


	for(int i =0; i < _nBins; i++){

		cout << "Ratio = " << 	hBsCross->GetBinContent(i+1) << endl;
		cout << "Ratio Error = " << 	hBsCross->GetBinError(i+1) << endl;
		cout << "Ratio Frac Error = " << 	hBsCross->GetBinError(i+1)/hBsCross->GetBinContent(i+1) << endl;

	}



/*
	for(int i =0; i < _nBins; i++){

		cout << "Ratio = " << 	hBsCross->GetBinContent(i+1) << endl;
		cout << "Ratio Error = " << 	hBsCross->GetBinError(i+1) << endl;

	}
	*/
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
	NPartPlot->GetYaxis()->SetTitle("B^{0}_{S}/B^{+}");
	NPartPlot->GetXaxis()->CenterTitle();
	NPartPlot->GetYaxis()->CenterTitle();
	NPartPlot->GetYaxis()->SetTitleOffset(1.3);
//	NPartPlot->Draw("epx0");

	TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,300,10.,0.0,0.8);  
	hemptySigma->GetXaxis()->CenterTitle();
	hemptySigma->GetYaxis()->CenterTitle();
	hemptySigma->GetYaxis()->SetTitle("B^{0}_{S}/B^{+}");

	hemptySigma->GetXaxis()->SetTitle("<N_{Part}>");
	hemptySigma->GetXaxis()->SetTitleOffset(1.);
	hemptySigma->GetYaxis()->SetTitleOffset(1.45*tpadr);
	hemptySigma->GetXaxis()->SetTitleSize(0.055/tpadr);
	hemptySigma->GetYaxis()->SetTitleSize(0.050/tpadr);
	hemptySigma->GetXaxis()->SetTitleFont(42);
	hemptySigma->GetYaxis()->SetTitleFont(42);
	hemptySigma->GetXaxis()->SetLabelFont(42);
	hemptySigma->GetYaxis()->SetLabelFont(42);
	hemptySigma->GetXaxis()->SetLabelSize(0.048/tpadr);
	hemptySigma->GetYaxis()->SetLabelSize(0.048/tpadr);  
	hemptySigma->Draw();



//	double SystErr[_nBins];

	double SystErrUp[_nBins];
	double SystErrDown[_nBins];

	//Bs//
	/*
	double SystErrBs[_nBins];
	double TrackingErrBs[_nBins] ={0.10,0.10};
	double SelErrBs[_nBins] ={0.105,0.0934};
	double PTErrBs[_nBins] ={0.00011,0.00012};
	double AccErrBs[_nBins] ={0.0,0.0};
	double PDFBErrBs[_nBins] ={0.0136,0.0236};
	double PDFSErrBs[_nBins] ={0.0171,0.0109};
//	double TnPErrBs[_nBins] ={0.0531,0.0563};
	double	MCStatBs[_nBins] ={0.0932, 0.286};
	*/

	//Bs//
	double SystErrBs[_nBins];
	double TrackingErrBs[_nBins] ={0.10,0.10};
	//double SelErrBs[_nBins] ={0.0307,0.0207};
	double SelErrBs[_nBins] ={0.0304,0.0226};
	double PTErrBs[_nBins] ={0.00011,0.00029};
	double AccErrBs[_nBins] ={0.0,0.0};
//	double PDFBErrBs[_nBins] ={0.0136,0.0236};
//	double PDFBErrBs[_nBins] ={0.000,0.000};
//	double PDFSErrBs[_nBins] ={0.0142,0.0279};
//	double TnPErrBs[_nBins] ={0.0531,0.0563};
	double PDFBErrBs[_nBins] ={0.0114,0.0592};
	double PDFSErrBs[_nBins] ={0.0079,0.0182};
	
	double MCStatBs[_nBins] ={0.0236, 0.0676};

	double ClosureUp[_nBins] ={0.0,0.0};
	double ClosureDown[_nBins] ={0.0,0.0};
	double sPLOTBs[_nBins] ={0.0038,0.0022};


	//BPlus//
	double SystErrBP[_nBins];
	double TrackingErrBP[_nBins] ={0.05,0.05};
//	double SelErrBP[_nBins] ={0.0897,0.0834};
	
	double SelErrBP[_nBins] ={0.0792,0.1286};
	double PTErrBP[_nBins] ={0.00163,0.00122};
	double AccErrBP[_nBins] ={0.0000,0.0000};
	//double PDFBErrBP[_nBins] ={0.0,0.0};
	//double PDFSErrBP[_nBins] ={0.0282,0.0257};
	double PDFSErrBP[_nBins] ={0.0257,0.0250};
	double PDFBErrBP[_nBins] ={0.0113,0.00412};

	double sPLOTBP[_nBins] = {0.0158,0.0047};
	//	double TnPErrBP[_nBins] ={0.06945,0.0634};


//	double MCStatBP[_nBins] = {0.0262,0.0299};
	double MCStatBP[_nBins] = {0.0224,0.0315};

	double TrackingErrBsBP[_nBins] ={0.05,0.05};

	double StatUp[_nBins];
	double StatDown[_nBins];

	for(int i = 0; i < _nBins; i++){

		SystErrBs[i] =  sqrt(SelErrBs[i] *SelErrBs[i] + PTErrBs[i] * PTErrBs[i] + AccErrBs[i]* AccErrBs[i] + PDFBErrBs[i]* PDFBErrBs[i] + PDFSErrBs[i]* PDFSErrBs[i] + MCStatBs[i] * MCStatBs[i]);
		SystErrBP[i] =  sqrt(SelErrBP[i] *SelErrBP[i] + PTErrBP[i] * PTErrBP[i] + AccErrBP[i]* AccErrBP[i] + PDFBErrBP[i]* PDFBErrBP[i] + PDFSErrBP[i]* PDFSErrBP[i]  + MCStatBP[i] * MCStatBP[i]);

		SystErrUp[i] = sqrt(SystErrBs[i]* SystErrBs[i] + SystErrBP[i] * SystErrBP[i] + TrackingErrBsBP[i] * TrackingErrBsBP[i] + BsBPUpSyst[i] * BsBPUpSyst[i] + ClosureUp[i]* ClosureUp[i]);

		SystErrDown[i] = sqrt(SystErrBs[i]* SystErrBs[i] + SystErrBP[i] * SystErrBP[i] + TrackingErrBsBP[i] * TrackingErrBsBP[i] + BsBPDownSyst[i] * BsBPDownSyst[i] + ClosureDown[i]* ClosureDown[i]);

		cout << "i = "  << i  << "    SystErrUp = "  << SystErrUp[i] << "  SystErrDown =  " << SystErrDown[i] << endl;
		StatUp[i] = sqrt(StatUpBs[i] * StatUpBs[i] + StatUpBP[i] * StatUpBP[i]);
		StatDown[i] = sqrt(StatDownBs[i] * StatDownBs[i] + StatDownBP[i] * StatDownBP[i]);

	}


	double CorrYield[_nBins];
	double CorrYieldErr[_nBins];
	double X[_nBins];

	for(int i = 0; i < _nBins;i++){
		CorrYield[i] = NPartPlot->GetBinContent(i+1);
		CorrYieldErr[i] = NPartPlot->GetBinError(i+1);
		X[i] = NPartSwap[i+1];
	}

	double MyX[_nBins];
	double MyXlow[_nBins] = {5,5};
	double MyXhigh[_nBins] = {5,5};
//	double SystErr[_nBins] ={0.53,0.578};
	double MyY[_nBins];
	double Mycrosssystlow[_nBins];
	double Mycrosssysthigh[_nBins];

	for(int i = 0; i < _nBins; i++){
		MyX[i] =  (NPartSwap[i] + NPartSwap[i+1])/2;
		MyY[i] =  NPartPlot->GetBinContent(i+1);
		Mycrosssystlow[i] = MyY[i]* SystErrDown[i];
		Mycrosssysthigh[i] = MyY[i]* SystErrUp[i];
	}


	double	glbUncert = TMath::Sqrt(2.8*2.8 + 7.6*7.6)/100;

	ofstream outratio("OutText/Ratio/ratio_cent_0_30_90_New.txt");
	outratio << "NPart" << "   " <<  "xsec" << "   " << "statUncertUp" << "   "<< "statUncertDown" << "   " << "systUncert Up" << "   " << "systUncert Down" << "   " <<  "glbUncert Up "<< "   " <<  "glbUncert Down "  << endl;

	for(int i = 0; i < _nBins; i++){
		outratio << X[i]  << "   " << MyY[i] << "   " << StatUp[i]  << "   " <<  StatDown[i]  << "   " << SystErrUp[i] << "   " << SystErrDown[i]  << "   " <<  glbUncert << "   " <<  glbUncert   << endl;
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






	TLatex* texlumi = new TLatex(0.96,0.95,"1.7 nb^{-1} (PbPb) 5.02 TeV");
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


	TLatex* texcent = new TLatex(0.42,0.80,"B p_{T} 10 - 50 GeV/c");
	texcent->SetNDC();
	texcent->SetTextFont(42);
	texcent->SetTextSize(0.05);
	texcent->SetLineWidth(2);
	texcent->Draw("SAME");

	TLatex *texY = new TLatex(0.21,0.79,"|y| < 2.4");
	texY->SetNDC();
	texY->SetTextFont(42);
	texY->SetTextSize(0.05);
	texY->SetLineWidth(2);
	texY->Draw("SAME");

	TLine *line = new TLine(0,10.5/40.5,300,10.5/40.5);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("SAME");


	TLatex* Bin1 = new TLatex(0.78,0.63,"Cent. 0 - 30%");
	Bin1->SetNDC();
	Bin1->SetTextAlign(13);
	Bin1->SetTextFont(62);//61
	Bin1->SetTextSize(0.032);
	Bin1->SetLineWidth(2);
	Bin1->Draw("SAME");


	TLatex* Bin2 = new TLatex(0.25,0.34,"Cent. 30 - 90%");
	Bin2->SetNDC();
	Bin2->SetTextAlign(13);
	Bin2->SetTextFont(62);//61
	Bin2->SetTextSize(0.032);
	Bin2->SetLineWidth(2);
	Bin2->Draw("SAME");


	double BsFrag = 10.3;
	double BsErr = 0.5;

	double BPFrag = 40.5;
	double BPErr = 0.6;

	double NPartMin = 0;
	double NPartMax = 300;

	const int BandBin = 1;
	double BandX[BandBin] = {(NPartMin+NPartMax)/2};
	double BandY[BandBin] = {BsFrag/BPFrag};


	double BandXErr[BandBin] = {(NPartMax-NPartMin)/2};
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


	TLegend* leg = new TLegend(0.35,0.42,0.66,0.72,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->AddEntry(NPartPlot,"Data Points","pl");
	leg->AddEntry(MyCrossSyst,"Systematics Uncertainties","l");
	leg->AddEntry(FragBand,"f_{s}/f_{u} in vacuum","l");
	leg->Draw("same");




	c->SaveAs("BstoBPlusCentAdd.pdf");


}
