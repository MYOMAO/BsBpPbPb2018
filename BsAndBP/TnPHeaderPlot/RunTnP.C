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
#include "tnp_weight_lowptPbPb.h"



//#include "his.h"
using namespace std;

using std::cout;
using std::endl;




void RunTnP(){

	gStyle->SetPadRightMargin(0.18);

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	const int NEtabin = 4;
	double Etabinning[NEtabin + 1] = {0,1.2,1.8,2.1,2.4};

	const int NPtbin = 50;
	double PtMin = 0;
	double PtMax = 18;
	double PtStep = (PtMax - PtMin)/NPtbin;

	const int NPlots = 5;


	TH2D * MuonIDSF[NPlots];
	TH2D *	MuonTRKSF[NPlots];
	TH2D *	MuonTRGSFL2[NPlots];
	TH2D *	MuonTRGSFL3[NPlots];

	TString NameTag[NPlots] = {"Syst Down","Syst Up","Nominal","Stat Up","Stat Down"};



	for(int i = 0; i < NPlots; i++){

		MuonIDSF[i] = new TH2D("MuonIDSF","",NPtbin,PtMin,PtMax,NEtabin,Etabinning);
		MuonIDSF[i]->GetXaxis()->SetTitle("Muon p_{T} (GeV/c)");
		MuonIDSF[i]->GetYaxis()->SetTitle("Muon |y|");
		MuonIDSF[i]->GetYaxis()->SetTitleOffset(1.4);
		MuonIDSF[i]->GetZaxis()->SetTitle(Form("Muon ID Scale Factor %s",NameTag[i].Data()));
	
		MuonIDSF[i]->GetZaxis()->SetTitleOffset(2.0);
		MuonIDSF[i]->SetMinimum(0.97);
		if(i == 4)	MuonIDSF[i]->SetMinimum(0.96);
		MuonIDSF[i]->SetMaximum(1.02);
		MuonIDSF[i]->GetXaxis()->CenterTitle();
		MuonIDSF[i]->GetYaxis()->CenterTitle();
		MuonIDSF[i]->GetZaxis()->CenterTitle();


		MuonTRKSF[i] = new TH2D("MuonTRKSF","",NPtbin,PtMin,PtMax,NEtabin,Etabinning);
		MuonTRKSF[i]->GetXaxis()->SetTitle("Muon p_{T} (GeV/c)");
		MuonTRKSF[i]->GetYaxis()->SetTitle("Muon |y|");
		MuonTRKSF[i]->GetZaxis()->SetTitle(Form("Muon Track Scale Factor %s",NameTag[i].Data()));
		MuonTRKSF[i]->GetZaxis()->SetTitleOffset(2.0);
		MuonTRKSF[i]->SetMinimum(0.97);
		if(i == 4)	MuonTRKSF[i]->SetMinimum(0.96);
		MuonTRKSF[i]->SetMaximum(1.02);
		MuonTRKSF[i]->GetXaxis()->CenterTitle();
		MuonTRKSF[i]->GetYaxis()->CenterTitle();
		MuonTRKSF[i]->GetZaxis()->CenterTitle();




		MuonTRGSFL2[i] = new TH2D("MuonTRGSF","",NPtbin,PtMin,PtMax,NEtabin,Etabinning);
		MuonTRGSFL2[i]->GetXaxis()->SetTitle("Muon p_{T} (GeV/c)");
		MuonTRGSFL2[i]->GetYaxis()->SetTitle("Muon |y|");
		MuonTRGSFL2[i]->GetZaxis()->SetTitle(Form("Muon Trigger Scale Factor L2 %s",NameTag[i].Data()));
		MuonTRGSFL2[i]->GetZaxis()->SetTitleOffset(2.0);
		MuonTRGSFL2[i]->SetMinimum(0.92);
		if(i == 4)	MuonTRGSFL2[i]->SetMinimum(0.90);
		MuonTRGSFL2[i]->SetMaximum(1.05);
		MuonTRGSFL2[i]->GetXaxis()->CenterTitle();
		MuonTRGSFL2[i]->GetYaxis()->CenterTitle();
		MuonTRGSFL2[i]->GetZaxis()->CenterTitle();


		MuonTRGSFL3[i] = new TH2D("MuonTRGSF","",NPtbin,PtMin,PtMax,NEtabin,Etabinning);
		MuonTRGSFL3[i]->GetXaxis()->SetTitle("Muon p_{T} (GeV/c)");
		MuonTRGSFL3[i]->GetYaxis()->SetTitle("Muon |y|");
		MuonTRGSFL3[i]->GetZaxis()->SetTitle(Form("Muon Trigger Scale Factor L3 %s",NameTag[i].Data()));
		MuonTRGSFL3[i]->GetZaxis()->SetTitleOffset(2.0);
		MuonTRGSFL3[i]->SetMinimum(0.85);
		if(i == 4)	MuonTRGSFL3[i]->SetMinimum(0.82);
		MuonTRGSFL3[i]->SetMaximum(1.05);
		MuonTRGSFL3[i]->GetXaxis()->CenterTitle();
		MuonTRGSFL3[i]->GetYaxis()->CenterTitle();
		MuonTRGSFL3[i]->GetZaxis()->CenterTitle();


	}


	int idx;





	double scalefactorid;
	double scalefactortrk;
	double scalefactortrgL2;
	double scalefactortrgL3;


	double pt;
	double eta;

	for(i = 0; i < NPtbin; i++){

		pt = PtStep * i + PtMin;

		for(int j = 0; j < NEtabin; j++){

			eta =  Etabinning[j];

			for(int k = 0; k < NPlots; k++){
	
				idx = k - 2;
				
				scalefactorid	= tnp_weight_muid_pbpb(pt, eta, idx);
				scalefactortrk	= tnp_weight_trk_pbpb(eta, idx);
				scalefactortrgL2	= tnp_weight_trg_pbpb(pt, eta, 0, idx);
				scalefactortrgL3	= tnp_weight_trg_pbpb(pt, eta, 1, idx);


				//cout << "muid scale factor = " << scalefactorid << endl;


				MuonIDSF[k]->SetBinContent(i+1,j+1,scalefactorid);
				MuonTRKSF[k]->SetBinContent(i+1,j+1,scalefactortrk);
				MuonTRGSFL2[k]->SetBinContent(i+1,j+1,scalefactortrgL2);
				MuonTRGSFL3[k]->SetBinContent(i+1,j+1,scalefactortrgL3);


			}

		}

	}


	TCanvas *c = new TCanvas("c","c",600,600);
	c->cd();



	for(int k = 0; k < NPlots; k++){

		MuonIDSF[k]->Draw("COLZ");
		c->SaveAs(Form("SFHeaderPlots/ID_%d.png",k));

		MuonTRKSF[k]->Draw("COLZ");
		c->SaveAs(Form("SFHeaderPlots/TRK_%d.png",k));
		
		MuonTRGSFL2[k]->Draw("COLZ");
		c->SaveAs(Form("SFHeaderPlots/TRG_L2_%d.png",k));
		
		MuonTRGSFL3[k]->Draw("COLZ");
		c->SaveAs(Form("SFHeaderPlots/TRG_L3_%d.png",k));



	}


}

