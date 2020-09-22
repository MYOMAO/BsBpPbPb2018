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

void ReAnaEffTnPSyst(int CentMin, int CentMax,	const int NBins,	int DoTwoD, int drop, int Weight, int TnPOpt){

	int TnP = 1;
	int DoLater = 5;

	const int NTnPType = 4;
	TString TnPName[NTnPType] = {"muid","trk","trg","total"};

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


	TString FileName;
	if(TnP == 0) FileName = Form("EffInfo_%d_%d.root",CentMin,CentMax);
	//	if(TnP == 1) FileName = Form("%dBptBinsTnP/EffInfo_%d_%d.root",NBptBins,CentMin,CentMax);
	if(TnP == 2) FileName = Form("NonFiducial/EffInfo_%d_%d.root",CentMin,CentMax);

//	FileName = Form("CheckSystNuno/%s/EffInfo_%d_%d.root",WeightName.Data(),CentMin,CentMax);

//	FileName = Form("/export/d00/scratch/zzshi/CMSSW_7_5_8_patch3/Merge/L2L3Muons/Bs/FinalFiles/BP/EffInfo_%d_%d.root",CentMin,CentMax);

	FileName = Form("MergedInput/EffInfo_%d_%d.root",CentMin,CentMax);

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

	
	Int_t Bmu1Type[NCand];
	Int_t Bmu2Type[NCand];





	TTree * MuonInfoTree = (TTree * ) fin->Get("MuonInfoTree");
	
	MuonInfoTree->SetBranchAddress("Bmu1Type",Bmu1Type);
	MuonInfoTree->SetBranchAddress("Bmu2Type",Bmu2Type);
	

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


	TFile * finTnP =  new TFile(Form("DetailedTnP/TNP2D_Bplus_Cent_detailed%d-%d.root",CentMin,CentMax));
	finTnP->cd();
	TH2D * tnp_scale = (TH2D *) finTnP->Get("tnp_scale");
	TH2D * tnp_total_d = (TH2D *) finTnP->Get("tnp_total_d");
	TH2D * tnp_total_u = (TH2D *) finTnP->Get("tnp_total_u");

	int EtaBin;
	int PtBin;




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


	
	double tnpabssystup;
	double tnpabssystdown;



	for( int i = 0; i < NEvents; i++){

		EffInfoTree->GetEntry(i);
		MuonInfoTree->GetEntry(i);


		for(int j = 0; j < BsizeNew; j++){


			for(int k = 0; k < NBins; k++){

			//	if((BptNew[j] > ptBins[k] && BptNew[j] < ptBins[k+1] && TMath::Abs(BmassNew[j] - 5.27932) < 0.08  && ((BptNew[j] > 7 && BptNew[j] < 10 && ByNew[j] > 1.5 )||(BptNew[j] > 10)) && (Bmu1Type > -0.1 && Bmu2Type > -0.1)))
				if((BptNew[j] > ptBins[k] && BptNew[j] < ptBins[k+1] && TMath::Abs(BmassNew[j] - 5.27932) < 0.08  && ((BptNew[j] > 7 && BptNew[j] < 10 && ByNew[j] > 1.5 )||(BptNew[j] > 10))) && (Bmu1Type[j] > -0.1 && Bmu2Type[j] > -0.1) )
				{
					//	SumCountsReal[k] = SumCountsReal[k] + BEff[j];
					//	if(k == 0) cout << "Eff Inv Here  = " << BEffInv[j] << endl; 


					if(DoLater == 1){
						EtaBin = tnp_scale->GetYaxis()->FindBin(ByNew[j]);
						PtBin = tnp_scale->GetXaxis()->FindBin(BptNew[j]);
						BEffInv[j] =  BEffInv[j]/tnp_scale->GetBinContent(PtBin,EtaBin);
						BEffInvErr[j] = BEffInvErr[j]/tnp_scale->GetBinContent(PtBin,EtaBin);
						BEffInvUp[j] = BEffInv[j]/(1-tnp_total_d->GetBinContent(PtBin,EtaBin));
						BEffInvDown[j] = BEffInv[j]/(1+tnp_total_u->GetBinContent(PtBin,EtaBin));
						BEffInvErrUp[j] = BEffInvErr[j]/(1-tnp_total_d->GetBinContent(PtBin,EtaBin));
						BEffInvErrDown[j] = BEffInvErr[j]/(1+tnp_total_u->GetBinContent(PtBin,EtaBin));
				


					//	cout << "BEffInvErr = " << BEffInvErr[j] <<   "   BEffInvErrUp = " << BEffInvErrUp[j] << " BEffInvErrDown " << BEffInvErrDown[j] << endl; 
						//cout << "EtaBin = " << EtaBin << "  Pt Bin = " << PtBin << endl;
						//cout << "Bpt Low = " <<ptBins[k] << "    Bpt High = " << ptBins[k+1]  << "   Eff Inv Here  = " << BEffInv[j] << endl; 

					}


					if(DoLater == 5){

						muidtnp1 = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0);
						muidtnp2 = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0);

						trktnp1 = tnp_weight_trk_pbpb(Bmu1etaNew[j], 0);
						trktnp2 = tnp_weight_trk_pbpb(Bmu2etaNew[j], 0);

						trktnp1systup = tnp_weight_trk_pbpb(Bmu1etaNew[j], -1);
						trktnp1systdown = tnp_weight_trk_pbpb(Bmu1etaNew[j], -2);
						trktnp1statup  = tnp_weight_trk_pbpb(Bmu1etaNew[j], 1);
						trktnp1statdown = tnp_weight_trk_pbpb(Bmu1etaNew[j], 2);


						trktnp2systup = tnp_weight_trk_pbpb(Bmu2etaNew[j], -1);
						trktnp2systdown = tnp_weight_trk_pbpb(Bmu2etaNew[j], -2);
						trktnp2statup  = tnp_weight_trk_pbpb(Bmu2etaNew[j], 1);
						trktnp2statdown = tnp_weight_trk_pbpb(Bmu2etaNew[j], 2);



						muidtnp1systup = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], -1);
						muidtnp1systdown = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], -2);
						muidtnp1statup = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1);
						muidtnp1statdown = tnp_weight_muid_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 2);



						muidtnp2systup = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], -1);
						muidtnp2systdown = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], -2);
						muidtnp2statup = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1);
						muidtnp2statdown = tnp_weight_muid_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 2);



						if(Bmu1Type[j] == 1 && Bmu2Type[j] == 1){

							//	cout << "totalL3 = " << totalL3 << "   Bpt = " <<  BptNew[j] << "   evt = " << evtNew << endl;


							trgtnp1 = 0.5 * ( tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 0));
							trgtnp2 = 0.5 * ( tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 0));

							trgtnp1systup = 0.5 * (tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, -1) + tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, -1));
							trgtnp1systdown = 0.5 * (tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, -2) + tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, -2) );
							trgtnp1statup = 0.5 * ( tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 1)  + tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 1) );
							trgtnp1statdown = 0.5 * ( tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 1, 2) + tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], 0, 2)  );

							trgtnp2systup = 0.5 * (tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, -1) + tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, -1));
							trgtnp2systdown = 0.5 * (tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, -2) + tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, -2) );
							trgtnp2statup = 0.5 * ( tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 1)  + tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 1) );
							trgtnp2statdown = 0.5 * ( tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 1, 2) + tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], 0, 2)  );

						}
						else{



							trgtnp1 = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j], Bmu1Type[j], 0);
							trgtnp2 = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], Bmu2Type[j], 0);

							trgtnp1systup = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j],  Bmu1Type[j], -1);
							trgtnp1systdown = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j],  Bmu1Type[j], -2);
							trgtnp1statup = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j],  Bmu1Type[j], 1);
							trgtnp1statdown = tnp_weight_trg_pbpb(Bmu1ptNew[j], Bmu1etaNew[j],  Bmu1Type[j], 2);


							trgtnp2systup = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j],  Bmu2Type[j], -1);
							trgtnp2systdown = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j],  Bmu2Type[j], -2);
							trgtnp2statup = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j],  Bmu2Type[j], 1);
							trgtnp2statdown = tnp_weight_trg_pbpb(Bmu2ptNew[j], Bmu2etaNew[j], Bmu2Type[j], 2);



						}

						tnptotal1 = muidtnp1 * trktnp1 * trgtnp1;
						tnptotal2 = muidtnp2 * trktnp2 * trgtnp2;


						tnptotal1systup = muidtnp1systup * trktnp1systup * trgtnp1systup;
						tnptotal1systdown = muidtnp1systdown * trktnp1systdown * trgtnp1systdown;
						tnptotal1statup = muidtnp1statup * trktnp1statup * trgtnp1statup;
						tnptotal1statdown = muidtnp1statdown * trktnp1statdown * trgtnp1statdown;


						tnptotal2systup = muidtnp2systup * trktnp2systup * trgtnp2systup;
						tnptotal2systdown = muidtnp2systdown * trktnp2systdown * trgtnp2systdown;
						tnptotal2statup = muidtnp2statup * trktnp2statup * trgtnp2statup;
						tnptotal2statdown = muidtnp2statdown * trktnp2statdown * trgtnp2statdown;



						if(TnPOpt == 0){


							tnptotal1 = muidtnp1;
							tnptotal2 = muidtnp2;

							tnptotal1up =  sqrt( (muidtnp1systup ) * (muidtnp1systup ) + (muidtnp1statup ) * (muidtnp1statup ));
							tnptotal1down =  sqrt( (muidtnp1systdown ) * (muidtnp1systdown ) + (muidtnp1statdown ) * (muidtnp1statdown));


							tnptotal2up =  sqrt( (muidtnp2systup ) * (muidtnp2systup ) + (muidtnp2statup ) * (muidtnp2statup ));
							tnptotal2down =  sqrt( (muidtnp2systdown ) * (muidtnp2systdown ) + (muidtnp2statdown ) * (muidtnp2statdown));

						}

						if(TnPOpt == 1){


							tnptotal1 = trktnp1;
							tnptotal2 = trktnp2;

							tnptotal1up =  sqrt( (trktnp1systup ) * (trktnp1systup ) + (trktnp1statup ) * (trktnp1statup ));
							tnptotal1down =  sqrt( (trktnp1systdown ) * (trktnp1systdown ) + (trktnp1statdown ) * (trktnp1statdown));


							tnptotal2up =  sqrt( (trktnp2systup ) * (trktnp2systup ) + (trktnp2statup ) * (trktnp2statup ));
							tnptotal2down =  sqrt( (trktnp2systdown ) * (trktnp2systdown ) + (trktnp2statdown ) * (trktnp2statdown));

						}

						if(TnPOpt == 2){


							tnptotal1 = trgtnp1;
							tnptotal2 = trgtnp2;

							tnptotal1up =  sqrt( (trgtnp1systup ) * (trgtnp1systup ) + (trgtnp1statup ) * (trgtnp1statup ));
							tnptotal1down =  sqrt( (trgtnp1systdown ) * (trgtnp1systdown ) + (trgtnp1statdown ) * (trgtnp1statdown));


							tnptotal2up =  sqrt( (trgtnp2systup ) * (trgtnp2systup ) + (trgtnp2statup ) * (trgtnp2statup ));
							tnptotal2down =  sqrt( (trgtnp2systdown ) * (trgtnp2systdown ) + (trgtnp2statdown ) * (trgtnp2statdown));

						}


						
						if(TnPOpt == 3){


							tnptotal1 = muidtnp1 * trktnp1 * trgtnp1;
							tnptotal2 = muidtnp2 * trktnp2 * trgtnp2;

							tnptotal1up =  sqrt( (tnptotal1systup ) * (tnptotal1systup ) + (tnptotal1statup ) * (tnptotal1statup ));
							tnptotal1down =  sqrt( (tnptotal1systdown ) * (tnptotal1systdown ) + (tnptotal1statdown ) * (tnptotal1statdown));


							tnptotal2up = sqrt( (tnptotal2systup ) * (tnptotal2systup ) +  (tnptotal2statup ) * (tnptotal2statup ));
							tnptotal2down = sqrt( ( tnptotal2systdown) * (tnptotal2systdown ) + (tnptotal2statdown ) * (tnptotal2statdown )) ;

						}


							tnpabssystup = abs(tnptotal1up * tnptotal2up - tnptotal1 * tnptotal2)/(tnptotal1 * tnptotal2);
							tnpabssystdown = abs(tnptotal1down * tnptotal2down - tnptotal1 * tnptotal2)/(tnptotal1 * tnptotal2);
	
							tnpabssystup = abs(tnptotal1up * tnptotal2up - tnptotal1 * tnptotal2)/(tnptotal1 * tnptotal2);
							tnpabssystdown = abs(tnptotal1down * tnptotal2down - tnptotal1 * tnptotal2)/(tnptotal1 * tnptotal2);
						



						BEffInv[j]  = BEffInv[j]/(tnptotal1 * tnptotal2);
						BEffInvErr[j]  = BEffInvErr[j]/(tnptotal1 * tnptotal2);
						BEffInvUp[j] =  BEffInv[j] * tnpabssystup;
						BEffInvDown[j] =  BEffInv[j] * tnpabssystdown;	

						BEffInvErrUp[j] =  BEffInvErr[j] * tnpabssystup;
						BEffInvErrDown[j] =  BEffInvErr[j]* tnpabssystdown;	


					}





					//if( k == 0) cout << "iEvent = " << i << endl;
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
						if(BEffInv[j] > 0){
							SumCounts[k] = SumCounts[k] + BEffInv[j];
							SumCountsErr[k] = SumCountsErr[k] + BEffInvErr[j] * BEffInvErr[j];
							SumCountsEff[k] = SumCountsEff[k] + BEff[j];
							SumCountsEffErr[k] = SumCountsEffErr[k] + BEffErr[j] * BEffErr[j];
							SumCountsSyst[k] = 	SumCountsSyst[k]  + BEffInvBDTWeighted[j];
							SumCountsSystErr[k] = 	SumCountsSystErr[k]  + BEffInvErrBDTWeighted[j] * BEffInvErrBDTWeighted[j];

							SumCountsUp[k] = SumCountsUp[k] + BEffInvUp[j];
							SumCountsErrUp[k] = SumCountsErrUp[k] + BEffInvErrUp[j] * BEffInvErrUp[j];

							SumCountsDown[k] = SumCountsDown[k] + BEffInvDown[j];
							SumCountsErrDown[k] = SumCountsErrUp[k] + BEffInvErrDown[j] * BEffInvErrDown[j];

							Counts[k] = Counts[k] + 1;
							
							//cout << "SumCounts = " << SumCounts[k] << endl;

							//cout << "SumCountsUp = " << SumCountsUp[k] << endl;
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

	double MinPt;
	if(drop == 0) MinPt = 7;
	if(drop == 1) MinPt = 10;


	TH1D * hInvEff = new TH1D("hInvEff","",NBins,ptBins);


	hInvEff->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
	hInvEff->GetYaxis()->SetTitle("<1/(Eff * Acc)>");
	hInvEff->GetYaxis()->SetTitleOffset(1.4);
	hInvEff->GetXaxis()->CenterTitle();
	hInvEff->GetYaxis()->CenterTitle();
	hInvEff->SetMarkerColor(1);
	hInvEff->SetLineColor(1);
	hInvEff->SetMarkerStyle(20);

	hInvEff->SetMinimum(0);


	TH1D * hInvEffSyst = new TH1D("hInvEffSyst","",NBins,ptBins);

	hInvEffSyst->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
	hInvEffSyst->GetYaxis()->SetTitle("<1/(Eff * Acc)> - BDT Data-MC Weighted");
	hInvEffSyst->GetYaxis()->SetTitleOffset(1.4);
	hInvEffSyst->GetXaxis()->CenterTitle();
	hInvEffSyst->GetYaxis()->CenterTitle();
	hInvEffSyst->SetMarkerColor(1);
	hInvEffSyst->SetLineColor(2);
	hInvEffSyst->SetMarkerStyle(20);

	hInvEffSyst->SetMinimum(0);

	TH1D * hEff = new TH1D("hEff","",NBins,ptBins);


	hEff->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
	hEff->GetYaxis()->SetTitle("<(Eff * Acc)>");
	hEff->GetYaxis()->SetTitleOffset(1.4);
	hEff->GetXaxis()->CenterTitle();
	hEff->GetYaxis()->CenterTitle();
	hEff->SetMarkerColor(1);
	hEff->SetLineColor(1);
	hEff->SetMarkerStyle(20);

	hEff->SetMinimum(0);


	TH1D * hInvEffUp = new TH1D("hInvEffUp","",NBins,ptBins);


	hInvEffUp->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
	hInvEffUp->GetYaxis()->SetTitle("<1./(Eff * Acc)>");
	hInvEffUp->GetYaxis()->SetTitleOffset(1.4);
	hInvEffUp->GetXaxis()->CenterTitle();
	hInvEffUp->GetYaxis()->CenterTitle();
	hInvEffUp->SetMarkerColor(1);
	hInvEffUp->SetLineColor(1);
	hInvEffUp->SetMarkerStyle(20);
	hInvEffUp->SetMinimum(0);



	TH1D * hInvEffDown = new TH1D("hInvEffDown","",NBins,ptBins);


	hInvEffDown->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
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
	//	cout << "   NewEff = " << NewEffUp[i] << "     NewEffErr = " << NewEffErrUp[i] << "  Fractional = " << NewEffErrUp[i]/NewEffUp[i] << endl;



		NewEffErr[i] = 0; //Remove Error on Efficiency Correction//
	}


	for(int i = 0 ; i < NBins; i++){

		cout << "--------------------------------------------------  Eff Systematics Uncertainties  -----------------------------------------------" << endl;

			
		cout << "i = " << i << "    NewEffUp =   "  << NewEffUp[i]  <<    "    NewEffDown =   " <<  NewEffDown[i] << endl;
			
		cout << "i = " << i << "    SystUp =   "  << (NewEffUp[i] - NewEff[i])/ NewEff[i] <<    "    NewEffDown =   " << (NewEff[i] - NewEffDown[i])/NewEff[i] << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
	}

	//return;

	hInvEff->SetMaximum(NewEff[0]*1.5);
	TCanvas *c = new TCanvas("c","c",600,600);

	c->cd();

	hInvEff->Draw("ep");

	cout << "OK" << endl;
	
	c->SaveAs(Form("CheckSystNuno/EffFinal/ReAnaEff_%d_%d_%dBins.png",CentMin,CentMax,NBins));
	c->SaveAs(Form("CheckSystNuno/EffFinal/pdf/ReAnaEff_%d_%d_%dBins.pdf",CentMin,CentMax,NBins));

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

	c->SaveAs(Form("CheckSystNuno/%s/EBDTWeightedComp_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));

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
	c->SaveAs(Form("CheckSystNuno/%s/Syst/SystEffRatio_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));


	//TnP Comparison//
	
	if(NBins == 4){
		hInvEff->SetMinimum(0);
		hInvEff->SetMaximum(120);
	}
	
	if(NBins == 1){
		hInvEff->SetMinimum(10);
		hInvEff->SetMaximum(25);
	}


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



	//c->SaveAs(Form("CheckSystNuno/%s/TnPFinal/TnPEffComp_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));
	c->SaveAs(Form("TnPPlots/%s/TnPEffComp_%dBins_%d_%d.png",TnPName[TnPOpt].Data(),NBins,CentMin,CentMax));


	TH1D * hInvUpRatio =	(TH1D *) hInvEffUp->Clone("hInvUpRatio");
	TH1D * hInvDownRatio =	(TH1D *) hInvEffDown->Clone("hInvDownRatio");

	hInvUpRatio->Sumw2();
	hInvEff->Sumw2();
	hInvUpRatio->Divide(hInvEff);

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



//	c->SaveAs(Form("CheckSystNuno/%s/TnPFinal/SystTnPRatio_%dBins_%d_%d.png",WeightName.Data(),NBins,CentMin,CentMax));

	c->SaveAs(Form("TnPPlots/%s/SystTnPRatio_%dBins_%d_%d.png",TnPName[TnPOpt].Data(),NBins,CentMin,CentMax));

	for(int i = 0; i < hInvEffUp->GetNbinsX();i++){

		cout << "i = " << i << "   Upper TnP Syst = " << hInvUpRatio->GetBinContent(i+1) - 1 << endl;
		cout << "i = " << i << "   Lower TnP Syst = " << 1 - hInvDownRatio->GetBinContent(i+1)  << endl;

	}


	//TnP Syst DONE//


}
