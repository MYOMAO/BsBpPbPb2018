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

void ReAnaEffSyst(int CentMin, int CentMax, int Weight ){

	int TnP = 1;
	int DoLater = 5;

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);


	TString WeightName;
	/*

	   if(Weight == 16) WeightName = "NoWeight";
	   if(Weight == 1) WeightName = "FONLL";
	   if(Weight == 11) WeightName = "Linear";
	   if(Weight == 12) WeightName = "Quadratic";
	   if(Weight == 13) WeightName = "LInverse";
	   if(Weight == 14) WeightName = "LSqrt";
	   if(Weight == 15) WeightName = "LLog";
	   */

	if(Weight == 16) WeightName = "NoWeight";
	if(Weight == 1) WeightName = "FONLL";
	if(Weight == 11) WeightName = "Linear";
	if(Weight == 12) WeightName = "Quadratic";
	if(Weight == 13) WeightName = "LInverse";
	if(Weight == 14) WeightName = "LSqrt";
	if(Weight == 15) WeightName = "LLog";
	if(Weight == 0) WeightName = "NoTnP";


	TString FileName;
	/*
	   if(TnP == 0) FileName = Form("%dBptBins/EffInfo_%d_%d.root",NBptBins,CentMin,CentMax);
	   if(TnP == 1) FileName = Form("%dBptBinsTnP/EffInfo_%d_%d.root",NBptBins,CentMin,CentMax);
	   if(TnP == 2) FileName = Form("NonFiducial/EffInfo_%d_%d.root",CentMin,CentMax);
	   */

	FileName = Form("CheckSystNunoNew/%s/EffInfo_%d_%d.root",WeightName.Data(),CentMin,CentMax);

	TFile * fin = new TFile(FileName.Data());
	fin->cd();

	TTree * EffInfoTree = (TTree * ) fin->Get("EffInfoTree");
	TTree * MuonInfoTree = (TTree * ) fin->Get("MuonInfoTree");


	int NEvents = EffInfoTree->GetEntries();

	const int NCand = 10;

	Int_t BsizeNew;
	Int_t runNew;
	Int_t lumiNew;
	Int_t evtNew;
	Float_t BmassNew[NCand];
	Float_t BptNew[NCand];
	Float_t ByNew[NCand];


	Int_t Bmu1Type[NCand]; 
	Int_t Bmu2Type[NCand]; 


	EffInfoTree->SetBranchAddress("BsizeNew",&BsizeNew);
	EffInfoTree->SetBranchAddress("BmassNew",BmassNew);
	EffInfoTree->SetBranchAddress("ByNew",ByNew);
	EffInfoTree->SetBranchAddress("BptNew",BptNew);

	MuonInfoTree->SetBranchAddress("Bmu1Type",Bmu1Type);
	MuonInfoTree->SetBranchAddress("Bmu2Type",Bmu2Type);

	TFile * finSystMap = new TFile(Form("10kTH2D/GenStatSyst_%d_%d.root",CentMin,CentMax));
	//TFile * finSystMap = new TFile(	Form("CheckSystNuno/%s/EffFine_%d_%d.root",WeightName.Data(),CentMin,CentMax));

	finSystMap->cd();

	TH2D * EffInv2DTrial;
	TH2D * SelInv2DTrial;
	TH2D * AccInv2DTrial;

	const int NTrials = 10000;

	//	const int NTrials = 1;

	TString outfileSyst;

	outfileSyst = Form("NunoSyst/%d-%d/AllTrials.root",CentMin,CentMax);



	TFile * finSyst = new TFile(outfileSyst.Data(),"RECREATE");
	finSyst->cd();
	TTree * NunoSyst = new TTree("NunoSyst","NunoSyst");


	Int_t BsizeNewSyst;
	Float_t BmassNewSyst[NCand];
	Float_t BptNewSyst[NCand];
	Float_t ByNewSyst[NCand];
	Float_t BEffInvSyst[NCand];
	Float_t BSelInvSyst[NCand];
	Float_t BAccInvSyst[NCand];

	Int_t Bmu1TypeSyst[NCand]; 
	Int_t Bmu2TypeSyst[NCand]; 


	NunoSyst->Branch("BsizeNewSyst",&BsizeNewSyst,"BsizeNewSyst/I");
	NunoSyst->Branch("BmassNewSyst",BmassNewSyst,"BmassNewSyst/F");
	NunoSyst->Branch("BptNewSyst",BptNewSyst,"BptNewSyst/F");
	NunoSyst->Branch("ByNewSyst",ByNewSyst,"ByNewSyst/F");
	NunoSyst->Branch("BEffInvSyst",BEffInvSyst,"BEffInvSyst/F");
	NunoSyst->Branch("BSelInvSyst",BSelInvSyst,"BSelInvSyst/F");
	NunoSyst->Branch("BAccInvSyst",BAccInvSyst,"BAccInvSyst/F");

	NunoSyst->Branch("Bmu1TypeSyst",Bmu1TypeSyst,"Bmu1TypeSyst/I");
	NunoSyst->Branch("Bmu2TypeSyst",Bmu2TypeSyst,"Bmu2TypeSyst/I");



	int XLOC;
	int YLOC;



	TFile * finTnP0 =  new TFile(Form("TnPL2L3/TNP2D_Bs_Cent_detailed%d-%d_Opt_0.root",CentMin,CentMax));
	TFile * finTnP1 =  new TFile(Form("TnPL2L3/TNP2D_Bs_Cent_detailed%d-%d_Opt_1.root",CentMin,CentMax));
	TFile * finTnP2 =  new TFile(Form("TnPL2L3/TNP2D_Bs_Cent_detailed%d-%d_Opt_2.root",CentMin,CentMax));
	TFile * finTnP3 =  new TFile(Form("TnPL2L3/TNP2D_Bs_Cent_detailed%d-%d_Opt_3.root",CentMin,CentMax));
	TFile * finTnP4 =  new TFile(Form("TnPL2L3/TNP2D_Bs_Cent_detailed%d-%d_Opt_4.root",CentMin,CentMax));

	finTnP0->cd();
	TH2D * tnp_scale0 = (TH2D *) finTnP0->Get("tnp_scale");
	TH2D * tnp_total_d0 = (TH2D *) finTnP0->Get("tnp_total_d");
	TH2D * tnp_total_u0 = (TH2D *) finTnP0->Get("tnp_total_u");

	
	finTnP1->cd();
	TH2D * tnp_scale1 = (TH2D *) finTnP1->Get("tnp_scale");
	TH2D * tnp_total_d1 = (TH2D *) finTnP1->Get("tnp_total_d");
	TH2D * tnp_total_u1 = (TH2D *) finTnP1->Get("tnp_total_u");

	
	finTnP2->cd();
	TH2D * tnp_scale2 = (TH2D *) finTnP2->Get("tnp_scale");
	TH2D * tnp_total_d2 = (TH2D *) finTnP2->Get("tnp_total_d");
	TH2D * tnp_total_u2 = (TH2D *) finTnP2->Get("tnp_total_u");

	finTnP3->cd();
	TH2D * tnp_scale3 = (TH2D *) finTnP3->Get("tnp_scale");
	TH2D * tnp_total_d3 = (TH2D *) finTnP3->Get("tnp_total_d");
	TH2D * tnp_total_u3 = (TH2D *) finTnP3->Get("tnp_total_u");


	finTnP4->cd();
	TH2D * tnp_scale4 = (TH2D *) finTnP4->Get("tnp_scale");
	TH2D * tnp_total_d4 = (TH2D *) finTnP4->Get("tnp_total_d");
	TH2D * tnp_total_u4 = (TH2D *) finTnP4->Get("tnp_total_u");



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

	int EtaBin;
	int PtBin;

	double tnptotal1L2;
	double tnptotal1L3;
	double tnptotal2L2;
	double tnptotal2L3;





	Float_t Bmu1etaNew[NCand];
	Float_t Bmu2etaNew[NCand];

	Float_t Bmu1ptNew[NCand];
	Float_t Bmu2ptNew[NCand];


	EffInfoTree->SetBranchAddress("Bmu1etaNew",Bmu1etaNew);
	EffInfoTree->SetBranchAddress("Bmu2etaNew",Bmu2etaNew);

	EffInfoTree->SetBranchAddress("Bmu1ptNew",Bmu1ptNew);
	EffInfoTree->SetBranchAddress("Bmu2ptNew",Bmu2ptNew);


	for(int iTrial = 0; iTrial < NTrials;  iTrial++){

		cout << "Now Working on Trial = " << iTrial << " OUT OF " << NTrials << endl;

		EffInv2DTrial = (TH2D * ) finSystMap->Get(Form("EffBptByInvTrial%d",iTrial));
		//EffInv2DTrial = (TH2D * ) finSystMap->Get("EffBptByInv");
		SelInv2DTrial = (TH2D * ) finSystMap->Get(Form("SelBptByInvTrial%d",iTrial));
		AccInv2DTrial = (TH2D * ) finSystMap->Get(Form("AccBptByInvTrial%d",iTrial));



		for( int i = 0; i < NEvents; i++){
		
			MuonInfoTree->GetEntry(i);
			EffInfoTree->GetEntry(i);
			BsizeNewSyst = BsizeNew;

			for(int j = 0; j < BsizeNewSyst; j++){

				BmassNewSyst[j] = BmassNew[j];
				BptNewSyst[j] = BptNew[j];
				ByNewSyst[j] = ByNew[j];
				Bmu1TypeSyst[j] = Bmu1Type[j];
				Bmu2TypeSyst[j] = Bmu2Type[j];


				XLOC = EffInv2DTrial->GetXaxis()->FindBin(BptNewSyst[j]);
				YLOC = EffInv2DTrial->GetYaxis()->FindBin(ByNewSyst[j]);




				BEffInvSyst[j] = EffInv2DTrial->GetBinContent(XLOC,YLOC);
				BSelInvSyst[j] = SelInv2DTrial->GetBinContent(XLOC,YLOC);
				BAccInvSyst[j] = AccInv2DTrial->GetBinContent(XLOC,YLOC);

				if(DoLater == 1){

						EtaBin = tnp_scale1->GetYaxis()->FindBin(ByNewSyst[j]);
						PtBin = tnp_scale1->GetXaxis()->FindBin(BptNewSyst[j]);

						//			cout<< "tnp_scaleOld = " << tnp_scaleOld->GetBinContent(PtBin,EtaBin)  << "   tnp_scale = " <<   tnp_scale->GetBinContent(PtBin,EtaBin) << "  tnp_scale0 =  " << tnp_scale0->GetBinContent(PtBin,EtaBin)  <<  "   tnp_scale1 =  " << tnp_scale1->GetBinContent(PtBin,EtaBin) <<   "   tnp_scale2 =  " << tnp_scale2->GetBinContent(PtBin,EtaBin) <<  "   tnp_scale3 =  " << tnp_scale3->GetBinContent(PtBin,EtaBin) <<  "   tnp_scale4 =  " << tnp_scale4->GetBinContent(PtBin,EtaBin) << endl;

						if(Bmu1TypeSyst[j] == 0 && Bmu2TypeSyst[j]  == 1){

							EtaBin = tnp_scale1->GetYaxis()->FindBin(ByNewSyst[j]);
							PtBin = tnp_scale1->GetXaxis()->FindBin(BptNewSyst[j]);
							BSelInvSyst[j] =  BSelInvSyst[j]/tnp_scale1->GetBinContent(PtBin,EtaBin);
							BEffInvSyst[j] = BEffInvSyst[j]/tnp_scale1->GetBinContent(PtBin,EtaBin);
	

						}



						if(Bmu1TypeSyst[j] == 1 && Bmu2TypeSyst[j] == 0){

							EtaBin = tnp_scale2->GetYaxis()->FindBin(ByNewSyst[j]);
							PtBin = tnp_scale2->GetXaxis()->FindBin(BptNewSyst[j]);
							BSelInvSyst[j] =  BSelInvSyst[j]/tnp_scale2->GetBinContent(PtBin,EtaBin);
							BEffInvSyst[j] = BEffInvSyst[j]/tnp_scale2->GetBinContent(PtBin,EtaBin);

						}



						if(Bmu1TypeSyst[j] == 0 && Bmu2TypeSyst[j] == 0){

							EtaBin = tnp_scale3->GetYaxis()->FindBin(ByNewSyst[j]);
							PtBin = tnp_scale3->GetXaxis()->FindBin(BptNewSyst[j]);
							BSelInvSyst[j] =  BSelInvSyst[j]/tnp_scale3->GetBinContent(PtBin,EtaBin);
							BEffInvSyst[j] = BEffInvSyst[j]/tnp_scale3->GetBinContent(PtBin,EtaBin);

						}


						if(Bmu1TypeSyst[j] == 1 && Bmu2TypeSyst[j] == 1){

							EtaBin = tnp_scale4->GetYaxis()->FindBin(ByNewSyst[j]);
							PtBin = tnp_scale4->GetXaxis()->FindBin(BptNewSyst[j]);
							BSelInvSyst[j] =  0.5 * ( BSelInvSyst[j]/tnp_scale1->GetBinContent(PtBin,EtaBin) +  BSelInvSyst[j]/tnp_scale2->GetBinContent(PtBin,EtaBin));
							BEffInvSyst[j] = 0.5 * ( BEffInvSyst[j]/tnp_scale1->GetBinContent(PtBin,EtaBin) +  BEffInvSyst[j]/tnp_scale2->GetBinContent(PtBin,EtaBin) );

						}


					}


					if(DoLater == 5){
					
						muidtnp1 = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0);
						muidtnp2 = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0);

						trktnp1 = tnp_weight_trk_pbpb(Bmu1etaNew[j], 0);
						trktnp2 = tnp_weight_trk_pbpb(Bmu2etaNew[j], 0);


						if(Bmu1Type[j] == 1 && Bmu2Type[j] == 1){

							trgtnp1 = 0.5 * ( tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 0));
							trgtnp2 = 0.5 * ( tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 0));

						}
						else{

							trgtnp1 = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], Bmu1Type[j], 0);
							trgtnp2 = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], Bmu2Type[j], 0);

						}

						tnptotal1 = muidtnp1 * trktnp1 * trgtnp1;
						tnptotal2 = muidtnp2 * trktnp2 * trgtnp2;

						//cout << "tnptotal1 = " << tnptotal1 <<   "    tnptotal2 =  "  << tnptotal2 << endl;


						BSelInvSyst[j]  = BSelInvSyst[j]/(tnptotal1 * tnptotal2);
						BEffInvSyst[j]  = BEffInvSyst[j]/(tnptotal1 * tnptotal2);


					}


					if(DoLater == 6){
					
						muidtnp1 = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0);
						muidtnp2 = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0);

						trktnp1 = tnp_weight_trk_pbpb(Bmu1etaNew[j], 0);
						trktnp2 = tnp_weight_trk_pbpb(Bmu2etaNew[j], 0);


						if(Bmu1Type[j] == 1 && Bmu2Type[j] == 1){

							trgtnp1 = 0.5 * ( tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 0));
							trgtnp2 = 0.5 * ( tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 0));

							tnptotal1L2 = muidtnp1 *  trktnp1 * tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 0);
							tnptotal1L3 = muidtnp1 *  trktnp1 * tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 0);

							tnptotal2L2 = muidtnp2 *  trktnp2 * tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 0);
							tnptotal2L3 = muidtnp2 *  trktnp2 * tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 0);

												
							BSelInvSyst[j]  = 2 * BSelInvSyst[j]/(tnptotal1L2 * tnptotal2L3 + tnptotal1L3 * tnptotal2L2);
							BEffInvSyst[j]  = 2 * BEffInvSyst[j]/(tnptotal1L2 * tnptotal2L3 + tnptotal1L3 * tnptotal2L2);


						}
						else{

							trgtnp1 = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], Bmu1Type[j], 0);
							trgtnp2 = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], Bmu2Type[j], 0);

						tnptotal1 = muidtnp1 * trktnp1 * trgtnp1;
						tnptotal2 = muidtnp2 * trktnp2 * trgtnp2;
					
						BSelInvSyst[j]  = BSelInvSyst[j]/(tnptotal1 * tnptotal2);
						BEffInvSyst[j]  = BEffInvSyst[j]/(tnptotal1 * tnptotal2);

						}

		
						//cout << "tnptotal1 = " << tnptotal1 <<   "    tnptotal2 =  "  << tnptotal2 << endl;





					}




			}


			NunoSyst->Fill();
		}

	}

	finSyst->Write();
	finSyst->Close();

}
