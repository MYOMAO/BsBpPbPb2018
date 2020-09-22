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
#include "TTree.h"

using namespace std;

using std::cout;
using std::endl;
#endif



void DrawTypes(int CentMin, int CentMax, int Option){

	gStyle->SetOptStat(0);

	TString BType;

	if(Option == 0) BType = "Bs";
	if(Option == 1) BType = "BP";


	TString infile = Form("FinalFiles/%s/EffInfo_%d_%d.root",BType.Data(),CentMin,CentMax);

	TFile * fin = new TFile(infile.Data());

	TTree * MuonInfoTree = (TTree *) fin->Get("MuonInfoTree");

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();




	TH1D * Bmu1TypeHis = new TH1D("Bmu1TypeHis","",40,-2,2);
	MuonInfoTree->Project("Bmu1TypeHis","Bmu1Type");
	
	Bmu1TypeHis->GetXaxis()->SetTitle("Bmu1Type");
	Bmu1TypeHis->GetYaxis()->SetTitle("Number of Muons");
	Bmu1TypeHis->GetXaxis()->CenterTitle();
	Bmu1TypeHis->GetYaxis()->CenterTitle();
	Bmu1TypeHis->GetYaxis()->SetTitleOffset(1.50);



	Bmu1TypeHis->Draw();

    TLatex *lat = new TLatex();
    lat->SetNDC();
    lat->SetTextFont(42);
    lat->SetTextSize(0.04);
    lat->DrawLatex(0.2,0.8,"-1 -> Not Passing L2 and L3");
    lat->DrawLatex(0.2,0.75,"0 -> L2");
    lat->DrawLatex(0.2,0.70,"1 -> L3");


	c->SaveAs(Form("Plots/Bmu1Type_%s_%d_%d.png",BType.Data(),CentMin,CentMax));


	TH1D * Bmu2TypeHis = new TH1D("Bmu2TypeHis","",40,-2,2);
	MuonInfoTree->Project("Bmu2TypeHis","Bmu2Type");
	Bmu2TypeHis->GetXaxis()->SetTitle("Bmu2Type");
	Bmu2TypeHis->GetYaxis()->SetTitle("Number of Muons");
	Bmu2TypeHis->GetXaxis()->CenterTitle();
	Bmu2TypeHis->GetYaxis()->CenterTitle();
	Bmu2TypeHis->GetYaxis()->SetTitleOffset(1.50);



	Bmu2TypeHis->Draw();

	c->SaveAs(Form("Plots/Bmu2Type_%s_%d_%d.png",BType.Data(),CentMin,CentMax));


	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");
	EffInfoTree->AddFriend("MuonInfoTree");

	TH1D * BadBMass = new TH1D("BadBMass","",50,5,6);

	EffInfoTree->Project("BadBMass","BmassNew","(Bmu1isTriggeredNew== 0) || (Bmu2isTriggeredNew== 0)");
		

	BadBMass->GetXaxis()->SetTitle("B^{0}_{s} mass (GeV/c^{2})");
	BadBMass->GetYaxis()->SetTitle("Counts");

	BadBMass->GetXaxis()->CenterTitle();
	BadBMass->GetYaxis()->CenterTitle();


	BadBMass->GetYaxis()->SetTitleOffset(1.4);

	BadBMass->Draw();

	c->SaveAs("Plots/BmassBad.png");

	
	TH1D * BadBPt = new TH1D("BadBPt","",40,5,50);

	EffInfoTree->Project("BadBPt","BptNew","(Bmu1isTriggeredNew== 0) || (Bmu2isTriggeredNew== 0)");
		

	BadBPt->GetXaxis()->SetTitle("B^{0}_{s} p_{T} (GeV/c)");
	BadBPt->GetYaxis()->SetTitle("Counts");
	BadBPt->GetXaxis()->CenterTitle();
	BadBPt->GetYaxis()->CenterTitle();
	BadBPt->GetYaxis()->SetTitleOffset(1.4);

	BadBPt->Draw();
	c->SaveAs("Plots/BptBad.png");



	TH1D * BadCent = new TH1D("BadCent","",200,0,100);


	EffInfoTree->Project("BadCent","hiBinNew/2","(Bmu1isTriggeredNew== 0) || (Bmu2isTriggeredNew== 0)");


	BadCent->GetXaxis()->SetTitle("Centrality (%)");
	BadCent->GetYaxis()->SetTitle("Counts");
	BadCent->GetXaxis()->CenterTitle();
	BadCent->GetYaxis()->CenterTitle();
	BadCent->GetYaxis()->SetTitleOffset(1.4);

	BadCent->Draw();
	c->SaveAs("Plots/CentBad.png");


	TH1D * lumiDiff = new TH1D("lumiDiff","",100,-1,1);
	
	EffInfoTree->Project("lumiDiff","lumiNew - lumi");
	lumiDiff->GetXaxis()->SetTitle("Difference Between B_{s}^{0} Tree and Muon Info Tree lumi");
	lumiDiff->GetYaxis()->SetTitle("Counts");
	lumiDiff->GetXaxis()->CenterTitle();
	lumiDiff->GetYaxis()->CenterTitle();
	lumiDiff->GetYaxis()->SetTitleOffset(1.4);


	lumiDiff->Draw();
	c->SaveAs("Plots/lumiDiff.png");


	TH1D * runDiff = new TH1D("runDiff","",100,-1,1);
	
	EffInfoTree->Project("runDiff","runNew - run");
	runDiff->GetXaxis()->SetTitle("Difference Between B_{s}^{0} Tree and Muon Info Tree run");
	runDiff->GetYaxis()->SetTitle("Counts");
	runDiff->GetXaxis()->CenterTitle();
	runDiff->GetYaxis()->CenterTitle();
	runDiff->GetYaxis()->SetTitleOffset(1.4);

	runDiff->Draw();
	c->SaveAs("Plots/runDiff.png");



	TH1D * evtDiff = new TH1D("evtDiff","",100,-1,1);
	
	EffInfoTree->Project("evtDiff","evtNew - evt");
	evtDiff->GetXaxis()->SetTitle("Difference Between B_{s}^{0} Tree and Muon Info Tree evt");
	evtDiff->GetYaxis()->SetTitle("Counts");
	evtDiff->GetXaxis()->CenterTitle();
	evtDiff->GetYaxis()->CenterTitle();
	evtDiff->GetYaxis()->SetTitleOffset(1.4);

	evtDiff->Draw();
	c->SaveAs("Plots/evtDiff.png");


	TH1D * Bmu1ptDiff = new TH1D("Bmu1ptDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu1ptDiff","Bmu1ptNew - Bmu1ptMatched");
	Bmu1ptDiff->GetXaxis()->SetTitle("Bfinder Bmu1pt - MuonInfoTree Bmu1pt");
	Bmu1ptDiff->GetYaxis()->SetTitle("Counts");
	Bmu1ptDiff->GetXaxis()->CenterTitle();
	Bmu1ptDiff->GetYaxis()->CenterTitle();
	Bmu1ptDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu1ptDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu1ptDiff.png");



	TH1D * Bmu2ptDiff = new TH1D("Bmu2ptDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu2ptDiff","Bmu2ptNew - Bmu2ptMatched");
	Bmu2ptDiff->GetXaxis()->SetTitle("Bfinder Bmu1pt - MuonInfoTree Bmu1pt");
	Bmu2ptDiff->GetYaxis()->SetTitle("Counts");
	Bmu2ptDiff->GetXaxis()->CenterTitle();
	Bmu2ptDiff->GetYaxis()->CenterTitle();
	Bmu2ptDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu2ptDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu2ptDiff.png");



	TH1D * Bmu1etaDiff = new TH1D("Bmu1etaDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu1etaDiff","Bmu1etaNew - Bmu1etaMatched");
	Bmu1etaDiff->GetXaxis()->SetTitle("Bfinder Bmu1eta - MuonInfoTree Bmu1eta");
	Bmu1etaDiff->GetYaxis()->SetTitle("Counts");
	Bmu1etaDiff->GetXaxis()->CenterTitle();
	Bmu1etaDiff->GetYaxis()->CenterTitle();
	Bmu1etaDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu1etaDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu1etaDiff.png");



	TH1D * Bmu2etaDiff = new TH1D("Bmu2etaDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu2etaDiff","Bmu2etaNew - Bmu2etaMatched");
	Bmu2etaDiff->GetXaxis()->SetTitle("Bfinder Bmu2eta - MuonInfoTree Bmu2eta");
	Bmu2etaDiff->GetYaxis()->SetTitle("Counts");
	Bmu2etaDiff->GetXaxis()->CenterTitle();
	Bmu2etaDiff->GetYaxis()->CenterTitle();
	Bmu2etaDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu2etaDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu2etaDiff.png");



	TH1D * Bmu1phiDiff = new TH1D("Bmu1phiDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu1phiDiff","Bmu1phiNew - Bmu1phiMatched");
	Bmu1phiDiff->GetXaxis()->SetTitle("Bfinder Bmu1phi - MuonInfoTree Bmu1phi");
	Bmu1phiDiff->GetYaxis()->SetTitle("Counts");
	Bmu1phiDiff->GetXaxis()->CenterTitle();
	Bmu1phiDiff->GetYaxis()->CenterTitle();
	Bmu1phiDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu1phiDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu1phiDiff.png");



	TH1D * Bmu2phiDiff = new TH1D("Bmu2phiDiff","",100,-1,1); 
	EffInfoTree->Project("Bmu2phiDiff","Bmu2phiNew - Bmu2phiMatched");
	Bmu2phiDiff->GetXaxis()->SetTitle("Bfinder Bmu2phi - MuonInfoTree Bmu2phi");
	Bmu2phiDiff->GetYaxis()->SetTitle("Counts");
	Bmu2phiDiff->GetXaxis()->CenterTitle();
	Bmu2phiDiff->GetYaxis()->CenterTitle();
	Bmu2phiDiff->GetYaxis()->SetTitleOffset(1.4);

	Bmu2phiDiff->Draw();
	c->SaveAs("Plots/MuonInfo/Bmu2phiDiff.png");





}
