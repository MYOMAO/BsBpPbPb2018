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


//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void ReAnaEffNew(int CentMin, int CentMax,	const int NBins,	int DoTwoD, int drop, int Weight){

	int TnP = 1;



	TString WeightName;


	if(Weight == 16) WeightName = "NoWeight";
	if(Weight == 1) WeightName = "FONLL";
	if(Weight == 11) WeightName = "Linear";
	if(Weight == 12) WeightName = "Quadratic";
	if(Weight == 13) WeightName = "LInverse";
	if(Weight == 14) WeightName = "LSqrt";
	if(Weight == 15) WeightName = "LLog";
	if(Weight == 0) WeightName = "NoTnP";

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);


	TString FileName = Form("NewTnPScheme/EffInfo_%d_%d.root",CentMin,CentMax);


	//TString FileName = Form("/Users/zhaozhongshi/Desktop/TempDownload/EffInfo_%d_%d.root",CentMin,CentMax);

	//TString FileName = Form("12BptBins/EffInfo_%d_%d.root",CentMin,CentMax);

	TFile * fin = new TFile(FileName.Data());
	fin->cd();

	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");

	int NEvents = EffInfoTree->GetEntries();

	const int NCand = 10;

	Int_t BsizeNew;
	Int_t runNew;
	Int_t lumiNew;
	Int_t evtNew;
	Float_t BmassNew[NCand];
	Float_t BptNew[NCand];
	Float_t ByNew[NCand];
	Float_t BEff[NCand];
	Float_t BEffErr[NCand];


	Float_t BEffInv[NCand];
	Float_t BEffInvErr[NCand];
	Float_t BEffInv1D[NCand];
	Float_t BEffInvErr1D[NCand];

	Float_t BEffInvFit[NCand];
	Float_t BEffInvErrFit[NCand];

	Float_t BEffInvBDTWeighted[NCand];
	Float_t BEffInvErrBDTWeighted[NCand];




	Float_t BEffInvUp[NCand];
	Float_t BEffInvErrUp[NCand];
	Float_t BEffInvDown[NCand];
	Float_t BEffInvErrDown[NCand];




	EffInfoTree->SetBranchAddress("evtNew",&evtNew);

	EffInfoTree->SetBranchAddress("BsizeNew",&BsizeNew);
	EffInfoTree->SetBranchAddress("BmassNew",BmassNew);
	EffInfoTree->SetBranchAddress("ByNew",ByNew);
	EffInfoTree->SetBranchAddress("BptNew",BptNew);
	EffInfoTree->SetBranchAddress("BEffInv",BEffInv);
	EffInfoTree->SetBranchAddress("BEffInvErr",BEffInvErr);
	EffInfoTree->SetBranchAddress("BEff",BEff);
	EffInfoTree->SetBranchAddress("BEffInv1D",BEffInv1D);
	EffInfoTree->SetBranchAddress("BEffInvErr1D",BEffInvErr1D);

	EffInfoTree->SetBranchAddress("BEffInvFit",BEffInvFit);
	EffInfoTree->SetBranchAddress("BEffInvErrFit",BEffInvErrFit);

	EffInfoTree->SetBranchAddress("BEffInv",BEffInv);
	EffInfoTree->SetBranchAddress("BEffInvErr",BEffInvErr);

	EffInfoTree->SetBranchAddress("BEffInvBDTWeighted",BEffInvBDTWeighted);
	EffInfoTree->SetBranchAddress("BEffInvErrBDTWeighted",BEffInvErrBDTWeighted);



	EffInfoTree->SetBranchAddress("BEffInvUp",BEffInvUp);
	EffInfoTree->SetBranchAddress("BEffInvErrUp",BEffInvErrUp);

	EffInfoTree->SetBranchAddress("BEffInvDown",BEffInvDown);
	EffInfoTree->SetBranchAddress("BEffInvErrDown",BEffInvErrDown);






	Float_t Bmu1etaNew[NCand];
	Float_t Bmu2etaNew[NCand];

	Float_t Bmu1ptNew[NCand];
	Float_t Bmu2ptNew[NCand];


	EffInfoTree->SetBranchAddress("Bmu1etaNew",Bmu1etaNew);
	EffInfoTree->SetBranchAddress("Bmu2etaNew",Bmu2etaNew);

	EffInfoTree->SetBranchAddress("Bmu1ptNew",Bmu1ptNew);
	EffInfoTree->SetBranchAddress("Bmu2ptNew",Bmu2ptNew);




	int hiBinMin = CentMin * 2;
	int hiBinMax = CentMax * 2;

	double ptBins[NBins + 1];

	int Counts[NBins];
	double SumCounts[NBins];
	double SumCountsErr[NBins];
	double NewEff[NBins];
	double NewEffErr[NBins];

	double NewEffReal[NBins];
	double NewEffRealErr[NBins];



	double SumCountsUp[NBins];
	double SumCountsErrUp[NBins];

	double SumCountsDown[NBins];
	double SumCountsErrDown[NBins];


	double SumCountsEff[NBins];
	double SumCountsEffErr[NBins];



	double SumCountsSyst[NBins];
	double SumCountsSystErr[NBins];
	double NewEffSyst[NBins];
	double NewEffSystErr[NBins];


	//	double CorrectionFactor[NBins];

	double NewEffUp[NBins];
	double NewEffErrUp[NBins];
	double NewEffDown[NBins];
	double NewEffErrDown[NBins];




	double TAA;
	std::vector<double> ptbinsvec;
	std::vector<double> corrfactvec;


	if(NBins == 1){


		if(drop == 0 && CentMin == 0) ptbinsvec.push_back(7.0);
		if(drop == 0 && CentMin == 30) ptbinsvec.push_back(9.0);

		if(drop == 1)  ptbinsvec.push_back(10.0);

		ptbinsvec.push_back(50);
		//	if(drop == 0 && CentMin == 0)	corrfactvec.push_back(1.08798);
		//	if(drop == 0 && CentMin == 30)	corrfactvec.push_back(1.05741);


	}


	if(NBins == 3){

		ptbinsvec.push_back(5);
		ptbinsvec.push_back(15);
		ptbinsvec.push_back(20);
		ptbinsvec.push_back(50);

	}


	if(NBins == 4){

		if(CentMin == 0) ptbinsvec.push_back(7);
		if(CentMin == 30)  ptbinsvec.push_back(9);
		ptbinsvec.push_back(10);
		ptbinsvec.push_back(15);
		ptbinsvec.push_back(20);
		ptbinsvec.push_back(50);

		/*
		   corrfactvec.push_back(1.24759);
		   corrfactvec.push_back(1.05256);
		   corrfactvec.push_back(1.02614);
		   corrfactvec.push_back(1.01174);
		   */


	}






	for(int i = 0; i < NBins + 1; i++){
		ptBins[i] =  ptbinsvec[i];
	}

	for(int i = 0; i < NBins; i++){
		Counts[i] = 0;
		SumCounts[i] = 0;
		SumCountsErr[i] = 0;
		SumCountsEff[i] = 0;
		SumCountsEffErr[i] = 0;
		SumCountsSyst[i] = 0;
		SumCountsSystErr[i] = 0;
		//	CorrectionFactor[i] = corrfactvec[i];
		SumCountsUp[i] = 0;
		SumCountsErrUp[i] = 0;
		SumCountsDown[i] = 0;
		SumCountsErrDown[i] = 0;
	}

	double MinPt;
	if(drop == 0) MinPt = 7;
	if(drop == 0) MinPt = 10;



	/*
	   const int NBins = 3;
	   double ptBins[NBins + 1] ={5,15,20,50};

	   int Counts[NBins]={0,0,0};
	   double SumCounts[NBins]={0,0,0};
	   double SumCountsErr[NBins]={0,0,0};
	   */


	/*
	   const int NBins = 4;
	   double ptBins[NBins + 1] ={5,10,15,20,50};

	   int Counts[NBins]={0,0,0,0};
	   double SumCounts[NBins]={0,0,0,0};
	   double SumCountsErr[NBins]={0,0,0,0};
	   */



	double trgtnp1;
	double trktnp1;
	double muidtnp1;

	double trgtnp1systup;
	double trgtnp1systdown;
	double trgtnp1statup;
	double trgtnp1statdown;


	double trktnp1systup;
	double trktnp1systdown;
	double trktnp1statup;
	double trktnp1statdown;

	double muidtnp1systup;
	double muidtnp1systdown;
	double muidtnp1statup;
	double muidtnp1statdown;


	double tnptotal1;
	double tnptotal1up;
	double tnptotal1down;


	double tnptotal1systup;
	double tnptotal1systdown;
	double tnptotal1statup;
	double tnptotal1statdown;



	double trgtnp2;
	double trktnp2;
	double muidtnp2;

	double trgtnp2systup;
	double trgtnp2systdown;
	double trgtnp2statup;
	double trgtnp2statdown;


	double trktnp2systup;
	double trktnp2systdown;
	double trktnp2statup;
	double trktnp2statdown;

	double muidtnp2systup;
	double muidtnp2systdown;
	double muidtnp2statup;
	double muidtnp2statdown;


	double tnptotal2;
	double tnptotal2up;
	double tnptotal2down;

	double tnptotal2systup;
	double tnptotal2systdown;
	double tnptotal2statup;
	double tnptotal2statdown;


	double tnptotal1L2;
	double tnptotal1L3;
	double tnptotal2L2;
	double tnptotal2L3;


	double tnptotal1L2systup;
	double tnptotal1L2systdown;
	double tnptotal1L2statup;
	double tnptotal1L2statdown;


	double tnptotal1L3systup;
	double tnptotal1L3systdown;
	double tnptotal1L3statup;
	double tnptotal1L3statdown;


	double tnptotal2L2systup;
	double tnptotal2L2systdown;
	double tnptotal2L2statup;
	double tnptotal2L2statdown;

	double tnptotal2L3systup;
	double tnptotal2L3systdown;
	double tnptotal2L3statup;
	double tnptotal2L3statdown;

	
	double tnptotal1L2up;
	double tnptotal1L2down;
	double tnptotal2L2up;
	double tnptotal2L2down;

	double tnptotal1L3up;
	double tnptotal1L3down;
	double tnptotal2L3up;
	double tnptotal2L3down;

	double tnpabssystup;
	double tnpabssystdown;



	//DONE INPUTING FILES
	

	int totalL3 = 0;

	int Random;

	int EtaBin;
	int PtBin;

	for( int i = 0; i < NEvents; i++){

		EffInfoTree->GetEntry(i);

		for(int j = 0; j < BsizeNew; j++){


			for(int k = 0; k < NBins; k++){

				if(BptNew[j] > ptBins[k] && BptNew[j] < ptBins[k+1] && (( BptNew[j] < 10 && TMath::Abs(BmassNew[j] - 5.36682) < 0.09) || (BptNew[j] > 10 && TMath::Abs(BmassNew[j] - 5.36682) < 0.08))){

					//	SumCountsReal[k] = SumCountsReal[k] + BEff[j];
					//cout << "BEffInv[j] = " << BEffInv[j] << endl; 
					//		cout << "Candidate: " << "   Bpt = " << BptNew[j] << "   Efficiency =  " << BEffInv[j] << "   Efficiency Error  = " << BEffInvErr[j] << endl;

					tnptotal1 = 1;
					tnptotal2 = 1;
					


					if(DoTwoD == 0){
						BEffErr[j] = BEffInvErr1D[j]/(BEffInv1D[j] * BEffInv1D[j]);
						if(BEffInv1D[j] > 0){
							//cout << "UnFit =" << BEffInv1D[j] << endl;
							SumCounts[k] = SumCounts[k] + BEffInv1D[j];
							SumCountsErr[k] = SumCountsErr[k] + BEffInvErr1D[j] * BEffInvErr1D[j];
							SumCountsEff[k] = SumCountsEff[k] + BEff[j];
							SumCountsEffErr[k] = SumCountsEffErr[k] + BEffErr[j] * BEffErr[j];
							Counts[k] = Counts[k] + 1;


						}
					}


					if(DoTwoD == 1){
						BEffErr[j] = BEffInvErr[j]/(BEffInv[j] * BEffInv[j]);
				//		cout << "BEffInv[j] = " <<  BEffInv[j] << endl;
						if(BEffInv[j] > 0){
							SumCounts[k] = SumCounts[k] + BEffInv[j];
							SumCountsErr[k] = SumCountsErr[k] + BEffInvErr[j] * BEffInvErr[j];
							SumCountsEff[k] = SumCountsEff[k] + BEff[j];
							SumCountsEffErr[k] = SumCountsEffErr[k] + BEffErr[j] * BEffErr[j];
							SumCountsSyst[k] = 	SumCountsSyst[k]  + BEffInvBDTWeighted[j];
							SumCountsSystErr[k] = 	SumCountsSystErr[k]  + BEffInvErrBDTWeighted[j] * BEffInvErrBDTWeighted[j];

							SumCountsUp[k] = SumCountsUp[k] + BEffInvUp[j];
							
					//		cout << "DoLater = " << DoLater << "	SumCountsUp[k] = " << 	SumCountsUp[k] << " BEffInvUp[j] = " << BEffInvUp[j] << endl; 
							SumCountsErrUp[k] = SumCountsErrUp[k] + BEffInvErrUp[j] * BEffInvErrUp[j];

							SumCountsDown[k] = SumCountsDown[k] + BEffInvDown[j];
							SumCountsErrDown[k] = SumCountsErrUp[k] + BEffInvErrDown[j] * BEffInvErrDown[j];

							Counts[k] = Counts[k] + 1;

							//cout << "Candidate: " << "   Bpt = " << BptNew[j] << "   Efficiency =  " << BEffInv[j] << "   Efficiency Error  = " << BEffInvErr[j] << endl;
						}
					}
					if(DoTwoD == 2){
						BEffErr[j] = BEffInvErrFit[j]/(BEffInvFit[j] * BEffInvFit[j]);	
						//cout << "Fit =" << BEffInvFit[j] << endl;
						//cout << "Err = " << BEffInvErrFit[j] << endl;
						SumCounts[k] = SumCounts[k] + BEffInvFit[j];
						SumCountsErr[k] = SumCountsErr[k] + BEffInvErrFit[j] * BEffInvErrFit[j];
						SumCountsEff[k] = SumCountsEff[k] + BEff[j];
						SumCountsEffErr[k] = SumCountsEffErr[k] + BEffErr[j] * BEffErr[j];
						Counts[k] = Counts[k] + 1;
					}
				}

			}


		}

	}


	TH1D * hInvEff = new TH1D("hInvEff","",NBins,ptBins);


	hInvEff->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	hInvEff->GetYaxis()->SetTitle("<1/(Eff * Acc)>");
	hInvEff->GetYaxis()->SetTitleOffset(1.4);
	hInvEff->GetXaxis()->CenterTitle();
	hInvEff->GetYaxis()->CenterTitle();
	hInvEff->SetMarkerColor(1);
	hInvEff->SetLineColor(1);
	hInvEff->SetMarkerStyle(20);

	hInvEff->SetMinimum(0);


	TH1D * hInvEffSyst = new TH1D("hInvEffSyst","",NBins,ptBins);

	hInvEffSyst->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	hInvEffSyst->GetYaxis()->SetTitle("<1/(Eff * Acc)> - BDT Data-MC Weighted");
	hInvEffSyst->GetYaxis()->SetTitleOffset(1.4);
	hInvEffSyst->GetXaxis()->CenterTitle();
	hInvEffSyst->GetYaxis()->CenterTitle();
	hInvEffSyst->SetMarkerColor(1);
	hInvEffSyst->SetLineColor(2);
	hInvEffSyst->SetMarkerStyle(20);

	hInvEffSyst->SetMinimum(0);

	TH1D * hEff = new TH1D("hEff","",NBins,ptBins);


	hEff->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	hEff->GetYaxis()->SetTitle("<(Eff * Acc)>");
	hEff->GetYaxis()->SetTitleOffset(1.4);
	hEff->GetXaxis()->CenterTitle();
	hEff->GetYaxis()->CenterTitle();
	hEff->SetMarkerColor(1);
	hEff->SetLineColor(1);
	hEff->SetMarkerStyle(20);

	hEff->SetMinimum(0);


	TH1D * hInvEffUp = new TH1D("hInvEffUp","",NBins,ptBins);


	hInvEffUp->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	hInvEffUp->GetYaxis()->SetTitle("<1./(Eff * Acc)>");
	hInvEffUp->GetYaxis()->SetTitleOffset(1.4);
	hInvEffUp->GetXaxis()->CenterTitle();
	hInvEffUp->GetYaxis()->CenterTitle();
	hInvEffUp->SetMarkerColor(1);
	hInvEffUp->SetLineColor(1);
	hInvEffUp->SetMarkerStyle(20);
	hInvEffUp->SetMinimum(0);



	TH1D * hInvEffDown = new TH1D("hInvEffDown","",NBins,ptBins);


	hInvEffDown->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	hInvEffDown->GetYaxis()->SetTitle("<1/(Eff * Acc)>");
	hInvEffDown->GetYaxis()->SetTitleOffset(1.4);
	hInvEffDown->GetXaxis()->CenterTitle();
	hInvEffDown->GetYaxis()->CenterTitle();
	hInvEffDown->SetMarkerColor(1);
	hInvEffDown->SetLineColor(1);
	hInvEffDown->SetMarkerStyle(20);
	hInvEffDown->SetMinimum(0);

	for(int i = 0; i < NBins; i++){


		NewEff[i] = SumCounts[i]/Counts[i];
		NewEffErr[i] = TMath::Sqrt(SumCountsErr[i])/Counts[i];


		NewEffUp[i] = SumCountsUp[i]/Counts[i];
		NewEffErrUp[i] = TMath::Sqrt(SumCountsErrUp[i])/Counts[i];



		NewEffDown[i] = SumCountsDown[i]/Counts[i];
		NewEffErrDown[i] = TMath::Sqrt(SumCountsErrDown[i])/Counts[i];


		NewEffReal[i] = SumCountsEff[i]/Counts[i];
		NewEffRealErr[i] = TMath::Sqrt(SumCountsEffErr[i])/Counts[i];


		hInvEff->SetBinContent(i+1,NewEff[i]);
		hInvEff->SetBinError(i+1,NewEffErr[i]);

		hEff->SetBinContent(i+1,NewEffReal[i]);
		hEff->SetBinError(i+1,NewEffRealErr[i]);


		NewEffSyst[i] = SumCountsSyst[i]/Counts[i];
		NewEffSystErr[i] = TMath::Sqrt(SumCountsSystErr[i])/Counts[i];


		hInvEffSyst->SetBinContent(i+1,	NewEffSyst[i]);
		hInvEffSyst->SetBinError(i+1, NewEffSystErr[i]);



		hInvEffUp->SetBinContent(i+1,NewEffUp[i]);
		hInvEffUp->SetBinError(i+1,NewEffErrUp[i]);


		hInvEffDown->SetBinContent(i+1,NewEffDown[i]);
		hInvEffDown->SetBinError(i+1,NewEffErrDown[i]);

		//	cout << "Real eff = " << SumCountsReal[i]/Counts[i] << endl;
		//cout << "Counts = " << Counts[i] << endl;
		cout << "Count =  " <<  Counts[i] << "   NewEff = " << NewEff[i] << "     NewEffErr = " << NewEffErr[i] << endl;
		cout << "Count =  " <<  Counts[i] << "   NewEffSyst = " << NewEffSyst[i] << "     NewEffSystErr = " << NewEffSystErr[i] << endl;

		cout << "-----------------------------------------------------------------------------------------------" << endl;

		cout << "   NewEff = " << NewEff[i] << "     NewEffErr = " << NewEffErr[i] << "  Fractional = " << NewEffErr[i]/NewEff[i] << endl;


		//	cout << "-----------------------------------------------------------------------------------------------" << endl;






		NewEffErr[i]  = 0; //Remove Error on Efficiency Corrections

	}

	for(int i = 0 ; i < NBins; i++){

		cout << "--------------------------------------------------  Eff Systematics Uncertainties  -----------------------------------------------" << endl;


		cout << "i = " << i << "    NewEffUp =   "  << NewEffUp[i]  <<    "    NewEffDown =   " <<  NewEffDown[i] << endl;

		cout << "i = " << i << "    SystUp =   "  << (NewEffUp[i] - NewEff[i])/ NewEff[i] <<    "    NewEffDown =   " << (NewEff[i] - NewEffDown[i])/NewEff[i] << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
	}


	hInvEff->SetMaximum(NewEff[0]*1.5);
	TCanvas *c = new TCanvas("c","c",600,600);

	c->cd();

	hInvEff->Draw("ep");

	cout << "OK" << endl;

	c->SaveAs(Form("Plots/NewEff/ReAnaEff_%d_%d_%dBins.png",CentMin,CentMax,NBins));

	hInvEff->SetMarkerColor(2);
	hInvEff->SetLineColor(2);
	hInvEffSyst->SetMarkerColor(3);
	hInvEffSyst->SetLineColor(3);



	TLegend *leg = new TLegend(0.19,0.60,0.39,0.87,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);

	leg->AddEntry(hInvEff,"Nominal Correction","pl");
	leg->AddEntry(hInvEffSyst,"BDT MC-Data Weighted Correction","pl");

	hInvEffSyst->SetMinimum(0);

	hInvEffSyst->Draw("ep");
	hInvEff->Draw("epSAME");
	leg->Draw("SAME");

	c->SaveAs(Form("Plots/%s/EBDTWeightedComp_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));

	TH1D * SelEffSystRatio =  (TH1D * ) hInvEffSyst->Clone("SelEffSystRatio");
	SelEffSystRatio->GetYaxis()->SetTitle("Syst Variation/Nominal");
	SelEffSystRatio->Sumw2();
	hInvEff->Sumw2();
	SelEffSystRatio->Divide(hInvEff);

	SelEffSystRatio->SetMaximum(3);

	SelEffSystRatio->SetMinimum(0);


	TLatex	*texChi = new TLatex(0.20,0.95, Form("BDT Weighted/Nominal at Centrality %d - %d",CentMin,CentMax));
	texChi->SetNDC();
	texChi->SetTextAlign(12);
	texChi->SetTextSize(0.04);
	texChi->SetTextFont(42);
	texChi->SetTextColor(1);

	SelEffSystRatio->GetYaxis()->SetTitleOffset(1.2);
	SelEffSystRatio->SetMarkerColor(1);
	SelEffSystRatio->SetLineColor(1);
	SelEffSystRatio->Draw("ep");

	


	TLine *l5 = new TLine(MinPt,1,50,1);
	l5->SetLineStyle(2);
	l5->SetLineWidth(2);
	l5->SetLineColor(2);

	l5->Draw("SAME");
	texChi->Draw("SAME");
	c->SaveAs(Form("Plots/%s/SystEffRatio_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));

	//TnP Comparison//

	hInvEff->SetMarkerColor(1);
	hInvEff->SetLineColor(1);
	hInvEff->Draw("ep");


	hInvEffUp->SetMarkerColor(2);
	hInvEffUp->SetLineColor(2);
	hInvEffDown->SetMarkerColor(3);
	hInvEffDown->SetLineColor(3);


	hInvEffUp->Draw("epSAME");
	hInvEffDown->Draw("epSAME");

	TLegend *legTnP = new TLegend(0.17,0.20,0.44,0.47,NULL,"brNDC");
	legTnP->SetBorderSize(0);
	legTnP->SetTextSize(0.04);
	legTnP->SetTextFont(42);
	legTnP->SetFillStyle(0);

	legTnP->AddEntry(hInvEff,"TnP - Total: Nominal Correction","pl");
	legTnP->AddEntry(hInvEffUp,"TnP - Total: Upper Bound of Scale Factor","pl");
	legTnP->AddEntry(hInvEffDown,"TnP - Total: Lower Bound of Scale Factor","pl");
	legTnP->Draw("SAME");



	c->SaveAs(Form("Plots/%s/TnPFinal/TnPEffComp_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));



	TH1D * hInvUpRatio =	(TH1D *) hInvEffUp->Clone("hInvUpRatio");
	TH1D * hInvDownRatio =	(TH1D *) hInvEffDown->Clone("hInvDownRatio");

	hInvUpRatio->Sumw2();
	hInvEff->Sumw2();
	hInvUpRatio->Divide(hInvEff);

	//		cout << "hInvUpRatio = " << hInvUpRatio

	hInvDownRatio->Sumw2();
	hInvEff->Sumw2();
	hInvDownRatio->Divide(hInvEff);

	hInvUpRatio->Draw("ep");
	hInvDownRatio->Draw("epSAME");


	TLegend *legTnPRatio = new TLegend(0.49,0.30,0.69,0.45,NULL,"brNDC");
	legTnPRatio->SetBorderSize(0);
	legTnPRatio->SetTextSize(0.04);
	legTnPRatio->SetTextFont(42);
	legTnPRatio->SetFillStyle(0);

	legTnPRatio->AddEntry(hInvUpRatio,"TnP - Total Up/Nominal","pl");
	legTnPRatio->AddEntry(hInvDownRatio,"TnP - Total Down/Nominal","pl");
	legTnPRatio->Draw("SAME");

	TLine *l6 = new TLine(MinPt,1,50,1);
	l6->SetLineStyle(2);
	l6->SetLineWidth(1);
	l6->SetLineColor(1);

	l6->Draw("SAME");



	c->SaveAs(Form("Plots/%s/TnPFinal/SystTnPRatio_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));



	for(int i = 0; i < hInvEffUp->GetNbinsX();i++){

		cout << "i = " << i << "   Upper TnP Syst = " << hInvUpRatio->GetBinContent(i+1) - 1 << endl;
		cout << "i = " << i << "   Lower TnP Syst = " << 1 - hInvDownRatio->GetBinContent(i+1)  << endl;

	}


	//TnP Syst DONE//




	for(int i = 0; i < SelEffSystRatio->GetNbinsX(); i++){


		cout << "i = " << i << "  hInvEff = " << hInvEff->GetBinContent(i+1) << "  hInvEffSyst = " << hInvEffSyst->GetBinContent(i+1) << "   SelEffSystRatio = " << SelEffSystRatio->GetBinContent(i+1) - 1 << endl;

	}


	//Yield and Corrected Yield//

	TFile * fout = new TFile(Form("Efficiency/ReAnaEff_%d_%d.root",CentMin,CentMax),"RECREATE");


	fout->cd();
	hInvEff->Write();
	hInvEffSyst->Write();
	hEff->Write();
	fout->Close();



	TFile * RawYield;






	if(CentMin ==0 && CentMax==90){
		TAA = 6.274; 
		if(NBins == 1 && drop == 0)		RawYield = new TFile("RawYields/yields_Bs_full_0_90_750.root");
		if(NBins == 1 && drop == 1)		RawYield = new TFile("RawYields/yields_Bs_full_0_90.root");
		if(NBins == 4) RawYield = new TFile("RawYields/yields_Bs_binned_pt.root");
	}


	if(CentMin ==0 && CentMax==30){
		TAA = 15.41;
		if(NBins == 1 && drop == 1)	RawYield = new TFile("RawYields/yields_Bs_full_0_30.root");

	}

	if(CentMin ==30 && CentMax==90){
		TAA = 1.705;
		if(NBins == 1 && drop == 1)	RawYield = new TFile("RawYields/yields_Bs_full_30_90.root");

	}




	/*
	   RawYield->cd();

	   TH1D * hPt = new TH1D("hPt","hPt",NBins,ptBins); 
	   TTree * EffInfoTreeRaw = (TTree *) RawYield->Get("EffInfoTree");
	   EffInfoTreeRaw->Project("hPt","BptNew");

	   TH1D * hPtWidth = new TH1D("hPtWidth","hPtWidth",NBins,ptBins); 

	   for(int i = 0; i < NBins; i++){

	   hPtWidth->SetBinContent(i+1,ptBins[i+1] - ptBins[i]);
	   hPtWidth->SetBinError(i+1,0);

	   }
	   hPt->Sumw2();
	   hPtWidth->Sumw2();
	   hPt->Divide(hPtWidth);

*/



	RawYield->cd();

	TH1D * hPt = (TH1D *) RawYield->Get("hPt");

	/*

	   TH1D * hPt = new TH1D("hPt","hPt",NBins,ptBins); 


	   EffInfoTree->Project("hPt","BptNew");

*/


	double RawCount;
	double RawCountErr;

	double CorrYield= 0;
	double CorrYieldErr= 0;

	int start;

	if(drop == 0) start = 0;

	if(drop == 1 && NBins == 4) start = 1;
	if(drop == 1 && NBins == 1) start = 0;

	cout << "start = " << start <<  "   hPt->GetNbinsX() = " << hPt->GetNbinsX() << endl;
	Double_t BRchain=3.118974e-5;
	double ptBinWidth;

	if(drop == 0 && CentMin == 0) ptBinWidth = 43;
	if(drop == 1 && CentMin == 0) ptBinWidth = 40;
	if(drop == 0 && CentMin == 30) ptBinWidth = 41;
	if(drop == 1 && CentMin == 30) ptBinWidth = 40;


	for(int i = start; i < hPt->GetNbinsX();i++){

		RawCount = hPt->GetBinContent(i+1);
		RawCountErr = hPt->GetBinError(i+1);

		cout << "RawCount = " << RawCount * (ptBins[i+1] - ptBins[i]) << "  RawCountErr = " << RawCountErr * (ptBins[i+1] - ptBins[i]) << " NewEff[i] =   " << NewEff[i] << "  NewEffErr[i] =  " << NewEffErr[i] << endl; 

		cout << "CORR YIELD Gen:  " <<  RawCount * (ptBins[i+1] - ptBins[i]) *  NewEff[i] << endl;
		cout << "CORR YIELD GenErr:  " << sqrt((RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) *(RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) + (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i]) * (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i])) << endl;


		//		cout << "CORR YIELD PT:  " <<  RawCount * (ptBins[i+1] - ptBins[i]) *  NewEff[i]/(BRchain*2 *ptBinWidth) << endl;
		//		cout << "CORR YIELD PTErr:  " <<  sqrt((RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) *(RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) + (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i]) * (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i]))/(BRchain*2 *ptBinWidth)  << endl;

		CorrYield = RawCount * (ptBins[i+1] - ptBins[i]) *  NewEff[i]  + CorrYield;
		CorrYieldErr = ((RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) *(RawCountErr * (ptBins[i+1] - ptBins[i]) *  NewEff[i]) + (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i]) * (RawCount * (ptBins[i+1] - ptBins[i]) *  NewEffErr[i]))  + CorrYieldErr;

	}

	CorrYieldErr = TMath::Sqrt(CorrYieldErr);

	cout << "CorrYield Final = " << CorrYield << "   CorrYield Error = " << CorrYieldErr  << endl;

	double FinalCorrYield;
	double FinalCorrYieldErr;



	cout << "ptBins[NBins] = " << ptBins[NBins] <<  "  ptBins[0] =  " << ptBins[0] << endl; 

	if(CentMin ==0 && CentMax==90){
		TAA = 6.274; 
	}

	if(CentMin ==30 && CentMax==90){
		TAA = 1.705;
	}

	if(CentMin ==0 && CentMax==30){
		TAA = 15.41;
	}


	FinalCorrYield = CorrYield/(BRchain*2*ptBinWidth * TAA);
	FinalCorrYieldErr = CorrYieldErr/(BRchain*2* ptBinWidth* TAA);

	cout << "FinalCorrYield = " << FinalCorrYield <<  "     FinalCorrYieldErr = " << FinalCorrYieldErr << endl;


	cout << "Corr Yield Relative Error = " << FinalCorrYieldErr/FinalCorrYield << endl;


	TH1D * hPtSigma;
	double hiBinning[3] = {0,60,180};

	if(CentMin == 0 && CentMax == 90)	hPtSigma = new TH1D("hPtSigma","hPtSigma",1,hiBinMin, hiBinMax);
	//	if(CentMin == 0 && CentMax == 30 || CentMin == 30 && CentMax == 90)	hPtSigma = new TH1D("hPtSigma","hPtSigma",2,hiBinning);

	if((CentMin == 0 && CentMax == 30) || (CentMin == 30 && CentMax == 90))	hPtSigma = new TH1D("hPtSigma","hPtSigma",1,hiBinMin, hiBinMax);

	if(CentMin == 0 && CentMax == 90){	
		hPtSigma->SetBinContent(1,FinalCorrYield);
		hPtSigma->SetBinError(1,FinalCorrYieldErr);
	}


	/*
	   if(CentMin == 0 && CentMax == 30){	
	   hPtSigma->SetBinContent(1,FinalCorrYield);
	   hPtSigma->SetBinError(1,FinalCorrYieldErr);
	   }



	   if(CentMin == 30 && CentMax == 90){	
	   hPtSigma->SetBinContent(2,FinalCorrYield);
	   hPtSigma->SetBinError(2,FinalCorrYieldErr);
	   }

*/

	if(CentMin == 0 && CentMax == 30){	
		hPtSigma->SetBinContent(1,FinalCorrYield);
		hPtSigma->SetBinError(1,FinalCorrYieldErr);
	}



	if(CentMin == 30 && CentMax == 90){	
		hPtSigma->SetBinContent(1,FinalCorrYield);
		hPtSigma->SetBinError(1,FinalCorrYieldErr);
	}


	//	TFile  * foutCorr = new TFile(Form("%dBptBins/NewCorr_%d_%d.root",NBptBins,CentMin,CentMax),"RECREATE");
	TFile * foutCorr = new TFile(Form("FinalFiles/NewCorr_%d_%d.root",CentMin,CentMax),"RECREATE");


	foutCorr->cd();
	hPtSigma->Write();
	foutCorr->Close();



	if(NBins == 4){

		//	TFile  * PtDiffFile = new TFile(Form("%dBptBins/PtDiffFile_%d_%d.root",NBptBins,CentMin,CentMax),"RECREATE");
		TFile * PtDiffFile = new TFile(Form("FinalFiles/PtDiffFile_%d_%d.root",CentMin,CentMax),"RECREATE");

		PtDiffFile->cd();


		int NBinsDiffBefore = hPt->GetNbinsX();
		const int NBinsDiff = NBinsDiffBefore;
		double CorrYieldDiff[NBinsDiff];
		double CorrYieldDiffErr[NBinsDiff];
		double Correction[NBinsDiff];
		if(CentMin == 0) Correction[0] = 4.0/3.8;
		if(CentMin == 30) Correction[0] = 1.0/1.0;

		for(int i = 1; i < NBinsDiff; i++){
			Correction[i] = 1;
		}



		double ptBinsNew[5]={7,10,15,20,50};
		TH1D * CorrDiffHis = new TH1D("hPtSigma","",NBins,ptBinsNew);


		for(int i = start; i < hPt->GetNbinsX();i++){

			RawCount = hPt->GetBinContent(i+1);
			RawCountErr = hPt->GetBinError(i+1);
			CorrYieldDiff[i] = (RawCount *  NewEff[i])/(BRchain*2* TAA);
			CorrYieldDiffErr[i] = TMath::Sqrt((RawCountErr *  NewEff[i]) *(RawCountErr  *  NewEff[i]) + (RawCountErr *  NewEffErr[i]) * (RawCount  *  NewEffErr[i]))/(BRchain*2* TAA);
			CorrDiffHis->SetBinContent(i+1,CorrYieldDiff[i]);
			CorrDiffHis->SetBinError(i+1,CorrYieldDiffErr[i]);


		}

		for(int i = start; i < hPt->GetNbinsX();i++){

			cout << "i = " << i << "  CorrYieldDiff =  " << CorrYieldDiff[i]  << "  Fractional Error = " << CorrYieldDiffErr[i]/CorrYieldDiff[i] << endl;

		}


		CorrDiffHis->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
		CorrDiffHis->GetYaxis()->SetTitle("B_{s} Corrected Yield");
		CorrDiffHis->GetYaxis()->SetTitleOffset(1.4);
		CorrDiffHis->GetXaxis()->CenterTitle();
		CorrDiffHis->GetYaxis()->CenterTitle();
		CorrDiffHis->SetMarkerColor(1);
		CorrDiffHis->SetLineColor(1);
		CorrDiffHis->SetMarkerStyle(20);

		CorrDiffHis->SetMinimum(1000);
		CorrDiffHis->SetMaximum(100000000);


		CorrDiffHis->Draw("ep");
		c->SetLogy();
		c->SaveAs(Form("Nuno_CorrectedYield_%d_%d.png",CentMin,CentMax));

		PtDiffFile->cd();
		CorrDiffHis->Write();
		PtDiffFile->Close();



		double PtBinForComp[4] = {3,5,5,30};

		for(int i = start; i < hPt->GetNbinsX();i++){

			cout << "i = " << i << "  CorrYieldDiff =  " << CorrYieldDiff[i] * PtBinForComp[i] * TAA/43  << endl;
			//
		}


	}

	cout << "FinalCorrYieldComp = " << FinalCorrYield *TAA <<  "     FinalCorrYieldErr = " << FinalCorrYieldErr << endl;

	cout << "FinalCorrYieldComp = " << FinalCorrYield *TAA <<  "     FinalCorrYieldErr = " << FinalCorrYieldErr << endl;


	//For Comparison//




}
