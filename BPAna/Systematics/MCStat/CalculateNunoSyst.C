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


void CalculateNunoSyst(int CentMin, int CentMax,	const int NBins, int drop ){


	int DoLater = 1;


	const int NCand = 10;

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TString infile;

	infile = Form("NunoSyst/%d-%d/AllTrials.root",CentMin,CentMax);


	TFile * fin = new TFile(infile.Data());
	fin->cd();

	TTree * NunoSyst = (TTree *) fin->Get("NunoSyst");
	int NEvents = NunoSyst->GetEntries();

	Int_t BsizeNewSyst;
	Float_t BmassNewSyst[NCand];
	Float_t BptNewSyst[NCand];
	Float_t ByNewSyst[NCand];
	Float_t BEffInvSyst[NCand];
	Float_t BSelInvSyst[NCand];
	Float_t BAccInvSyst[NCand];

	Int_t Bmu1TypeSyst[NCand];
	Int_t Bmu2TypeSyst[NCand];


	NunoSyst->SetBranchAddress("BsizeNewSyst",&BsizeNewSyst);
	NunoSyst->SetBranchAddress("BmassNewSyst",BmassNewSyst);
	NunoSyst->SetBranchAddress("BptNewSyst",BptNewSyst);
	NunoSyst->SetBranchAddress("ByNewSyst",ByNewSyst);
	NunoSyst->SetBranchAddress("BEffInvSyst",BEffInvSyst);
	NunoSyst->SetBranchAddress("BSelInvSyst",BSelInvSyst);
	NunoSyst->SetBranchAddress("BAccInvSyst",BAccInvSyst);

	NunoSyst->SetBranchAddress("Bmu1TypeSyst",Bmu1TypeSyst);
	NunoSyst->SetBranchAddress("Bmu2TypeSyst",Bmu2TypeSyst);


	std::vector<double> ptbinsvec;
	std::vector<double> minvec;
	std::vector<double> maxvec;
	std::vector<double> meanvec;


	std::vector<double> minselvec;
	std::vector<double> maxselvec;



	std::vector<double> minaccvec;
	std::vector<double> maxaccvec;


	int NTrials = 10000;

	if(NBins == 1){

		if(drop == 0 && CentMin == 0) ptbinsvec.push_back(7.0);
		if(drop == 0 && CentMin == 30) ptbinsvec.push_back(9.0);
		if(drop == 1)  ptbinsvec.push_back(10.0);

		ptbinsvec.push_back(50);
		minvec.push_back(0);


		if(drop == 0){
			if(CentMin==0 && CentMax == 90) 	maxvec.push_back(100);
			if(CentMin==0 && CentMax == 30) 	maxvec.push_back(200);
			if(CentMin==30 && CentMax == 90) 	maxvec.push_back(35);


			if(CentMin == 0 && CentMax == 90){

				minselvec.push_back(0);
				maxselvec.push_back(50);

				minaccvec.push_back(3.90);
				maxaccvec.push_back(4.10);

				meanvec.push_back(63.3055);

			}


			if(CentMin == 0 && CentMax == 30){

				minselvec.push_back(0);
				maxselvec.push_back(25);

				minaccvec.push_back(4.2);
				maxaccvec.push_back(4.6);
				meanvec.push_back(91.265);

			}


			if(CentMin == 30 && CentMax == 90){

				minselvec.push_back(0);
				maxselvec.push_back(15);

				minaccvec.push_back(2.9);
				maxaccvec.push_back(3.2);
				meanvec.push_back(21.7475);

			}

		}

		if(drop == 1){

			if(CentMin == 0 && CentMax == 90){

				minselvec.push_back(0);
				maxselvec.push_back(20);

				minaccvec.push_back(3.1);
				maxaccvec.push_back(3.3);
				maxvec.push_back(50);
				meanvec.push_back(18.0782);

			}

			if(CentMin == 0 && CentMax == 30){

				minselvec.push_back(0);
				maxselvec.push_back(20);

				minaccvec.push_back(3.4);
				maxaccvec.push_back(3.5);
				maxvec.push_back(70);
				meanvec.push_back(20.135);

			}

			if(CentMin == 30 && CentMax == 90){

				minselvec.push_back(0);
				maxselvec.push_back(10);

				minaccvec.push_back(2.5);
				maxaccvec.push_back(2.8);
				maxvec.push_back(20);
				meanvec.push_back(11.4551);

			}




		}




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



		minvec.push_back(14);
		minvec.push_back(5.9);
		minvec.push_back(2.9);
		minvec.push_back(0);

		minaccvec.push_back(12);
		minaccvec.push_back(5.2);
		minaccvec.push_back(2.7);
		minaccvec.push_back(1.60);

		minselvec.push_back(0);
		minselvec.push_back(0);
		minselvec.push_back(0);
		minselvec.push_back(0);




		maxvec.push_back(900);
		maxvec.push_back(100);
		maxvec.push_back(30);
		maxvec.push_back(16);




		maxaccvec.push_back(15);
		maxaccvec.push_back(5.55);
		maxaccvec.push_back(2.8);
		maxaccvec.push_back(1.75);


		maxselvec.push_back(200);
		maxselvec.push_back(40);
		maxselvec.push_back(20);
		maxselvec.push_back(12);






		meanvec.push_back(102.739);
		meanvec.push_back(34.6897);
		meanvec.push_back(10.6322);
		meanvec.push_back(5.97351);



	}



	double ptBins[NBins + 1];

	int Counts[NBins];
	double SumCounts[NBins];
	double NewEff[NBins];
	double 	Mean[NBins];
	double 	Min[NBins];
	double 	Max[NBins];


	double 	MinAcc[NBins];
	double 	MaxAcc[NBins];

	double 	MinSel[NBins];
	double 	MaxSel[NBins];


	double SumCountsSel[NBins];
	double SumCountsAcc[NBins];

	double NewSel[NBins];
	double NewAcc[NBins];


	/*
	   double Mean[NBins]={203.113,60.8946,19.2579,9.95329};
	   double Min[NBins] = {50,40,10,0};
	   double Max[NBins] = {400,100,30,16};
	   */


	for(int i = 0; i < NBins + 1; i++){
		ptBins[i] =  ptbinsvec[i];

	}

	for(int i = 0; i < NBins; i++){

		Mean[i] = meanvec[i];
		Min[i] = minvec[i];
		Max[i] = maxvec[i];

		MinAcc[i] = minaccvec[i];
		MaxAcc[i] = maxaccvec[i];

		MinSel[i] = minselvec[i];
		MaxSel[i] = maxselvec[i];


	}



	TH1D * EffInvDistribution[NBins];
	TH1D * SelInvDistribution[NBins];
	TH1D * AccInvDistribution[NBins];



	for(int i = 0; i < NBins; i++){
		Counts[i] = 0;
		SumCounts[i] = 0;
		SumCountsAcc[i] = 0;
		SumCountsSel[i] = 0;

	}




	for(int i = 0; i < NBins; i++){

		EffInvDistribution[i] = new TH1D("EffInvDistribution","",200,Min[i],Max[i]);
		EffInvDistribution[i]->GetXaxis()->SetTitle("<1/(acc x eff)>");
		EffInvDistribution[i]->GetYaxis()->SetTitle("Counts");
		EffInvDistribution[i]->SetTitle(Form("MC Smeared Distribution for %.0f < Bpt < %.0f",ptBins[i],ptBins[i+1]));

		EffInvDistribution[i]->GetXaxis()->CenterTitle();
		EffInvDistribution[i]->GetYaxis()->CenterTitle();
		EffInvDistribution[i]->GetYaxis()->SetTitleOffset(1.4);


		SelInvDistribution[i] = new TH1D("SelInvDistribution","",200,MinSel[i],MaxSel[i]);
		SelInvDistribution[i]->GetXaxis()->SetTitle("<1/(eff)>");
		SelInvDistribution[i]->GetYaxis()->SetTitle("Counts");
		SelInvDistribution[i]->SetTitle(Form("MC Smeared Distribution for %.0f < Bpt < %.0f",ptBins[i],ptBins[i+1]));

		SelInvDistribution[i]->GetXaxis()->CenterTitle();
		SelInvDistribution[i]->GetYaxis()->CenterTitle();
		SelInvDistribution[i]->GetYaxis()->SetTitleOffset(1.4);



		AccInvDistribution[i] = new TH1D("AccInvDistribution","",200,MinAcc[i],MaxAcc[i]);
		AccInvDistribution[i]->GetXaxis()->SetTitle("<1/(acc)>");
		AccInvDistribution[i]->GetYaxis()->SetTitle("Counts");
		AccInvDistribution[i]->SetTitle(Form("MC Smeared Distribution for %.0f < Bpt < %.0f",ptBins[i],ptBins[i+1]));

		AccInvDistribution[i]->GetXaxis()->CenterTitle();
		AccInvDistribution[i]->GetYaxis()->CenterTitle();
		AccInvDistribution[i]->GetYaxis()->SetTitleOffset(1.4);


	}


	int Inteval;
	if(CentMin == 0 && CentMax == 90) Inteval = 1908;
	if(CentMin == 0 && CentMax == 30) Inteval = 1326;
	if(CentMin == 30 && CentMax == 90) Inteval = 597;

	int iTrial;
	int iTrialPre = 0;
	int NFill = 0;
	int EtaBin;
	int PtBin;




	for(int i = 0; i < NEvents; i++){

		NunoSyst->GetEntry(i);

		iTrial = i/Inteval;



		if(iTrial>iTrialPre && iTrial%1000==0) cout << "Now Working on Trial = " << iTrial << " OUT OF " << NTrials << endl;


		if(iTrial > iTrialPre){


			for(int q = 0; q < NBins; q++){

				//		cout << "q = " << q << " Counts[q] = " << Counts[q] << endl;

				NewSel[q] = SumCountsSel[q]/Counts[q];
				NewAcc[q] = SumCountsAcc[q]/Counts[q];
				NewEff[q] = SumCounts[q]/Counts[q];

				EffInvDistribution[q]->Fill(NewEff[q]);
				SelInvDistribution[q]->Fill(NewSel[q]);
				AccInvDistribution[q]->Fill(NewAcc[q]);



				Counts[q] = 0;
				SumCounts[q] = 0;
				SumCountsSel[q] = 0;
				SumCountsAcc[q] = 0;



			}

			NFill = NFill + 1;

			//cout << "NFill = " << NFill << endl;

		}


		for(int j = 0; j < BsizeNewSyst; j++){


			for(int k = 0; k < NBins; k++){

			//	if(BptNewSyst[j] > ptBins[k] && BptNewSyst[j] < ptBins[k+1] &&  (( BptNewSyst[j] < 10 && TMath::Abs(BmassNewSyst[j] - 5.36682) < 0.08) || (BptNewSyst[j] > 10 && TMath::Abs(BmassNewSyst[j] - 5.36682) < 0.08)) )
				if(BptNewSyst[j] > ptBins[k] && BptNewSyst[j] < ptBins[k+1] && TMath::Abs(BmassNewSyst[j] - 5.27932) < 0.08  && ((BptNewSyst[j] > 7 && BptNewSyst[j] < 10 && ByNewSyst[j] > 1.5 )||(BptNewSyst[j] > 10) ))
				{
					//	SumCountsReal[k] = SumCountsReal[k] + BEff[j];
					//cout << "BEffInv[j] = " << BEffInv[j] << endl; 
					//    cout << "BSelInvSyst = " << BSelInvSyst[j] << endl;
					//	cout << "Counts = " << Counts[k] << endl;

			
					SumCountsSel[k] = SumCountsSel[k] + BSelInvSyst[j];
					SumCountsAcc[k] = SumCountsAcc[k] + BAccInvSyst[j];

					SumCounts[k] = SumCounts[k] + BEffInvSyst[j];
					Counts[k] = Counts[k] + 1;



				}

			}


		}
		iTrialPre = iTrial;

	}




	TCanvas * c = new TCanvas("c","c",600,600);
	if(NBins == 4)	c->Divide(2,2);
	if(NBins == 1)	c->Divide(1,1);


	TLine *l4[NBins];

	TLatex * texChi[NBins];




	for(int i = 0; i < NBins; i++){
		c->cd(i+1);
		EffInvDistribution[i]->SetMinimum(0);
		EffInvDistribution[i]->Draw();

		texChi[i] = new TLatex(0.30,0.95, Form("B_{s} GeV/c %.0f < p_{T} < %0.f GeV/c", ptBins[i],ptBins[i+1] ));
		texChi[i]->SetNDC();
		texChi[i]->SetTextAlign(12);
		texChi[i]->SetTextSize(0.06);
		texChi[i]->SetTextFont(42);
		texChi[i]->SetTextColor(1);

		texChi[i]->Draw("SAME");

		l4[i] = new TLine(Mean[i],0,Mean[i],EffInvDistribution[i]->GetMaximum());
		l4[i]->SetLineStyle(2);
		l4[i]->SetLineWidth(2);
		l4[i]->SetLineColor(2);
		l4[i]->Draw("SAME");

	}
	c->SaveAs(Form("MCStatSyst/NunoSyst_%d_%d_%dBinsPT.png",CentMin,CentMax,NBins));
	//Selection Smear//

	for(int i = 0; i < NBins; i++){
		c->cd(i+1);
		SelInvDistribution[i]->SetMinimum(0);
		SelInvDistribution[i]->Draw();

		texChi[i] = new TLatex(0.30,0.95, Form("GeV/c B_{s} %.0f < p_{T} < %0.f GeV/c", ptBins[i],ptBins[i+1] ));
		texChi[i]->SetNDC();
		texChi[i]->SetTextAlign(12);
		texChi[i]->SetTextSize(0.06);
		texChi[i]->SetTextFont(42);
		texChi[i]->SetTextColor(1);

		texChi[i]->Draw("SAME");

	}


	c->SaveAs(Form("MCStatSyst/NunoSelSyst_%d_%d_%dBinsPT.png",CentMin,CentMax,NBins));
	//	if(Rebin == 1)	c->SaveAs(Form("MCStatSyst/Rebin/NunoSelSyst_%d_%d_%dBinsPT.png",CentMin,CentMax,NBins));


	//Acceptance Smear//

	for(int i = 0; i < NBins; i++){
		c->cd(i+1);
		AccInvDistribution[i]->SetMinimum(0);
		AccInvDistribution[i]->Draw();

		texChi[i] = new TLatex(0.30,0.95, Form("B_{s} GeV/c %.0f < p_{T} < %0.f GeV/c", ptBins[i],ptBins[i+1] ));
		texChi[i]->SetNDC();
		texChi[i]->SetTextAlign(12);
		texChi[i]->SetTextSize(0.06);
		texChi[i]->SetTextFont(42);
		texChi[i]->SetTextColor(1);

		texChi[i]->Draw("SAME");

	}



	c->SaveAs(Form("MCStatSyst/NunoAccSyst_%d_%d_%dBinsPT.png",CentMin,CentMax,NBins));



	TString outFile;

	outFile = Form("NunoSyst/%d-%d/%dBins.root",CentMin,CentMax,NBins);

	TFile * fout = new TFile(outFile.Data(),"RECREATE");
	fout->cd();
	for(int i = 0; i < NBins; i++){

		EffInvDistribution[i]->Write();

	}
	fout->Close();

	double RMSSyst;
	double RMSSystAcc;
	double RMSSystSel;

	for(int i = 0; i < NBins; i++){

		RMSSystAcc =	AccInvDistribution[i]->GetRMS()/AccInvDistribution[i]->GetMean();
		cout << "i = " << i << " Acc  Percentage Syst = " << RMSSystAcc << endl;

		RMSSystSel =	SelInvDistribution[i]->GetRMS()/SelInvDistribution[i]->GetMean();
		cout << "i = " << i << " Sel Percentage Syst = " << RMSSystSel << endl;


		RMSSyst = 	EffInvDistribution[i]->GetRMS()/EffInvDistribution[i]->GetMean();
		cout << "i = " << i << "   Percentage Syst = " << RMSSyst << endl;

	}



}
