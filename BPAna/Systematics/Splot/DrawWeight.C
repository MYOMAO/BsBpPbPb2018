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
#include "TCanvas.h"



void DrawWeight(){

	
	
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);





	TFile * fin = new TFile("DataWeight/sPLOTEffWeight0_90.root");
	
	fin->cd();




	TTree * t = (TTree * ) fin->Get("EffWeightTreesPLOT");

	TH1D * EffSplotWeighthis = new TH1D("EffSplotWeighthis","",50,-3,1.5);
	EffSplotWeighthis->GetXaxis()->SetTitle("sPlot Weight");
	EffSplotWeighthis->GetYaxis()->SetTitle("B^{+} Candidates Counts");
	EffSplotWeighthis->GetYaxis()->SetTitleOffset(1.4);
	EffSplotWeighthis->GetXaxis()->CenterTitle();
	EffSplotWeighthis->GetYaxis()->CenterTitle();


	t->Project("EffSplotWeighthis","EffSplotWeight");



	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();
	EffSplotWeighthis->Draw();
	c->SaveAs("Plots/sPLOTEffDistribution.png");


	TFile * fin1 = new TFile("CompFile/ReAnaEff_0_90.root");
	
	TFile * fin1Comp = new TFile("CompFile/ReAnaEffsPlotWeighted_0_90_7_50.root");
	
	TH1D * hInvEffNom = (TH1D*) fin1->Get("hInvEff");

	TH1D * hInvEffWeighted = (TH1D*) fin1Comp->Get("hInvEff");
	
	hInvEffNom->SetMarkerSize(2);
	hInvEffNom->SetMarkerStyle(20);
	hInvEffNom->SetMarkerColor(2);

	hInvEffWeighted->SetMarkerSize(2);
	hInvEffWeighted->SetMarkerStyle(20);
	hInvEffWeighted->SetMarkerColor(3);
	

	hInvEffNom->Draw("ep");
	hInvEffWeighted->Draw("epSAME");

	c->SaveAs("Plots/4BinComp.png");
}
