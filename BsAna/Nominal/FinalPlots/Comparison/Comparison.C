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


void Comparison(){
		
	gStyle->SetOptStat(0);

	const int NPt = 4;
	const int NCent = 3;
	
	double Pt[NPt+1] = {7,10,15,20,50};

	double Cent[NCent+1] = {0,1,2,3};

	double BsPtBefore[NPt] = {206848,79349.2,23078.5,2348.84};
	double BsPtAfter[NPt] = {164627,76708.1,25219.2,2292.81};

	double BPPtBefore[NPt] = {337744,258447,61633.8,7454.01};
	double BPPtAfter[NPt] = {319290,271975,64325.4,7734.97};

	double BsBPPtBefore[NPt] = {0.61244,0.307023,0.374445,0.315111};
	double BsBPPtAfter[NPt] = {0.515605,0.282041,0.392057,0.296421};




	double BsCentBefore[NCent] = {627470,465295,602714};
	double BsCentAfter[NCent] = {651456,502495,601428};

	double BPCentBefore[NCent] = {1.68636e+06,2.16961e+06,1.85517e+06};
	double BPCentAfter[NCent] = {1.76218e+06, 2.296e+06,1.94646e+06  };

	double BsBPCentBefore[NCent] = {0.372086,0.21446,0.324883};
	double BsBPCentAfter[NCent] = {0.369688,0.218857,0.308985};



	TH1D * BsPtHisBefore = new TH1D("BsPtHisBefore","",NPt,Pt);
	TH1D * BsPtHisAfter = new TH1D("BsPtHisAfter","",NPt,Pt);

	
	TH1D * BPPtHisBefore = new TH1D("BPPtHisBefore","",NPt,Pt);
	TH1D * BPPtHisAfter = new TH1D("BPPtHisAfter","",NPt,Pt);

	TH1D * BsBPPtHisBefore = new TH1D("BsBPPtHisBefore","",NPt,Pt);
	TH1D * BsBPPtHisAfter = new TH1D("BsBPPtHisAfter","",NPt,Pt);


	for(int i = 0; i < NPt; i++){

		BsPtHisBefore->SetBinContent(i+1,BsPtBefore[i]);
		BsPtHisAfter->SetBinContent(i+1,BsPtAfter[i]);

		BPPtHisBefore->SetBinContent(i+1,BPPtBefore[i]);
		BPPtHisAfter->SetBinContent(i+1,BPPtAfter[i]);


		BsBPPtHisBefore->SetBinContent(i+1,BsBPPtBefore[i]);
		BsBPPtHisBefore->SetBinError(i+1,0.00001);
	
		BsBPPtHisAfter->SetBinContent(i+1,BsBPPtAfter[i]);
		BsBPPtHisAfter->SetBinError(i+1,0.00001);

	}

	BsPtHisBefore->SetMarkerSize(1.5);
	BsPtHisBefore->SetMarkerStyle(20);
	BsPtHisBefore->SetMarkerColor(kBlue);

	BsPtHisAfter->SetMarkerSize(1.5);
	BsPtHisAfter->SetMarkerStyle(21);
	BsPtHisAfter->SetMarkerColor(kRed);


	BPPtHisBefore->SetMarkerSize(1.5);
	BPPtHisBefore->SetMarkerStyle(20);
	BPPtHisBefore->SetMarkerColor(kBlue);

	BPPtHisAfter->SetMarkerSize(1.5);
	BPPtHisAfter->SetMarkerStyle(21);
	BPPtHisAfter->SetMarkerColor(kRed);


	BsBPPtHisBefore->SetMarkerSize(1);
	BsBPPtHisBefore->SetMarkerStyle(20);
	BsBPPtHisBefore->SetMarkerColor(kBlue);

	BsBPPtHisAfter->SetMarkerSize(1);
	BsBPPtHisAfter->SetMarkerStyle(21);
	BsBPPtHisAfter->SetMarkerColor(kRed);



	//Cent//

	TH1D * BsCentHisBefore = new TH1D("BsCentHisBefore","",NCent,Cent);
	TH1D * BsCentHisAfter = new TH1D("BsCentHisAfter","",NCent,Cent);


	TH1D * BPCentHisBefore = new TH1D("BPCentHisBefore","",NCent,Cent);
	TH1D * BPCentHisAfter = new TH1D("BPCentHisAfter","",NCent,Cent);



	TH1D * BsBPCentHisBefore = new TH1D("BsBPCentHisBefore","",NCent,Cent);
	TH1D * BsBPCentHisAfter = new TH1D("BsBPCentHisAfter","",NCent,Cent);



	for(int i = 0; i < NCent; i++){

		BsCentHisBefore->SetBinContent(i+1,BsCentBefore[i]);
		BsCentHisAfter->SetBinContent(i+1,BsCentAfter[i]);

		BPCentHisBefore->SetBinContent(i+1,BPCentBefore[i]);
		BPCentHisAfter->SetBinContent(i+1,BPCentAfter[i]);


		BsBPCentHisBefore->SetBinContent(i+1,BsBPCentBefore[i]);
		BsBPCentHisBefore->SetBinError(i+1,0.00001);

		
		BsBPCentHisAfter->SetBinContent(i+1,BsBPCentAfter[i]);
		BsBPCentHisAfter->SetBinError(i+1,0.00001);



	}




	BsCentHisBefore->SetMarkerSize(1.5);
	BsCentHisBefore->SetMarkerStyle(20);
	BsCentHisBefore->SetMarkerColor(kBlue);

	BsCentHisAfter->SetMarkerSize(1.5);
	BsCentHisAfter->SetMarkerStyle(21);
	BsCentHisAfter->SetMarkerColor(kRed);


	BPCentHisBefore->SetMarkerSize(1.5);
	BPCentHisBefore->SetMarkerStyle(20);
	BPCentHisBefore->SetMarkerColor(kBlue);

	BPCentHisAfter->SetMarkerSize(1.5);
	BPCentHisAfter->SetMarkerStyle(21);
	BPCentHisAfter->SetMarkerColor(kRed);


	BsBPCentHisBefore->SetMarkerSize(1);
	BsBPCentHisBefore->SetMarkerStyle(20);
	BsBPCentHisBefore->SetMarkerColor(kBlue);

	BsBPCentHisAfter->SetMarkerSize(1);
	BsBPCentHisAfter->SetMarkerStyle(21);
	BsBPCentHisAfter->SetMarkerColor(kRed);



	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();

	BsPtHisBefore->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	BsPtHisBefore->GetYaxis()->SetTitle("B_{s}^{0} Corrected Yield");

	BsPtHisBefore->GetXaxis()->CenterTitle();
	BsPtHisBefore->GetYaxis()->CenterTitle();
	
	BsPtHisBefore->GetYaxis()->SetTitleOffset(1.4);



	BsPtHisBefore->Draw("e0xp");
	BsPtHisAfter->Draw("e0xpSAME");

	TLegend* legBs = new TLegend(0.55,0.45,0.85,0.67,NULL,"brNDC");
	legBs->SetBorderSize(0);
	legBs->SetTextSize(0.04);
	legBs->SetTextFont(42);
	legBs->SetFillStyle(0);
	legBs->AddEntry(BsPtHisBefore,"B_{s}^{0} Before","pl");
	legBs->AddEntry(BsPtHisAfter,"B_{s}^{0} After","pl");
	legBs->Draw("same");




	c->SaveAs("Plots/BsPtHis.png");


	BPPtHisBefore->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	BPPtHisBefore->GetYaxis()->SetTitle("B^{+} Corrected Yield");

	BPPtHisBefore->GetXaxis()->CenterTitle();
	BPPtHisBefore->GetYaxis()->CenterTitle();
	
	BPPtHisBefore->GetYaxis()->SetTitleOffset(1.4);



	BPPtHisBefore->Draw("e0xp");
	BPPtHisAfter->Draw("e0xpSAME");



	TLegend* legBP = new TLegend(0.55,0.45,0.85,0.67,NULL,"brNDC");
	legBP->SetBorderSize(0);
	legBP->SetTextSize(0.04);
	legBP->SetTextFont(42);
	legBP->SetFillStyle(0);
	legBP->AddEntry(BsPtHisBefore,"B^{+} Before","pl");
	legBP->AddEntry(BsPtHisAfter,"B^{+} After","pl");
	legBP->Draw("same");

	c->SaveAs("Plots/BPPtHis.png");


	BsBPPtHisBefore->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	BsBPPtHisBefore->GetYaxis()->SetTitle("B_{s}^{0}/B^{+}");

	BsBPPtHisBefore->GetXaxis()->CenterTitle();
	BsBPPtHisBefore->GetYaxis()->CenterTitle();
	
	BsBPPtHisBefore->GetYaxis()->SetTitleOffset(1.4);


	BsBPPtHisBefore->SetMinimum(0.25);

	BsBPPtHisBefore->Draw("ep");
	BsBPPtHisAfter->Draw("epSAME");

	TLegend* legBsBP = new TLegend(0.55,0.55,0.85,0.77,NULL,"brNDC");
	legBsBP->SetBorderSize(0);
	legBsBP->SetTextSize(0.04);
	legBsBP->SetTextFont(42);
	legBsBP->SetFillStyle(0);
	legBsBP->AddEntry(BsPtHisBefore,"B_{s}^{0}/B^{+} Before","pl");
	legBsBP->AddEntry(BsPtHisAfter,"B_{s}^{0}/B^{+} After","pl");
	legBsBP->Draw("same");

	c->SaveAs("Plots/BsBPPtHis.png");


	BsCentHisBefore->SetMaximum(700000);

	BsCentHisBefore->GetXaxis()->SetTitle("Centrality Bin");
	BsCentHisBefore->GetYaxis()->SetTitle("B_{s}^{0} Corrected Yield");

	BsCentHisBefore->GetXaxis()->CenterTitle();
	BsCentHisBefore->GetYaxis()->CenterTitle();
	
	BsCentHisBefore->GetYaxis()->SetTitleOffset(1.4);

	BsCentHisBefore->Draw("e0xp");
	BsCentHisAfter->Draw("e0xpSAME");

	legBs->Draw("SAME");

	c->SaveAs("Plots/BsCentHis.png");

	BPCentHisBefore->GetXaxis()->SetTitle("Centrality Bin");
	BPCentHisBefore->GetYaxis()->SetTitle("B^{+} Corrected Yield");

	BPCentHisBefore->GetXaxis()->CenterTitle();
	BPCentHisBefore->GetYaxis()->CenterTitle();
	
	BPCentHisBefore->GetYaxis()->SetTitleOffset(1.4);

	BPCentHisAfter->Draw("e0xp");
	BPCentHisBefore->Draw("e0xpSAME");
	
	BPCentHisAfter->SetMinimum(1500000);
	BPCentHisAfter->SetMaximum(2500000);
	legBP->Draw("SAME");

	c->SaveAs("Plots/BPCentHis.png");




	BsBPCentHisBefore->GetXaxis()->SetTitle("Centrality Bin");
	BsBPCentHisBefore->GetYaxis()->SetTitle("B_{s}^{0}/B^{+}");

	BsBPCentHisBefore->GetXaxis()->CenterTitle();
	BsBPCentHisBefore->GetYaxis()->CenterTitle();
	
	BsBPCentHisBefore->GetYaxis()->SetTitleOffset(1.4);

	BsBPCentHisAfter->SetMaximum(0.45);

	BsBPCentHisAfter->Draw("ep");
	BsBPCentHisBefore->Draw("epSAME");
	legBsBP->Draw("SAME");

	c->SaveAs("Plots/BsBPCentHis.png");
}
