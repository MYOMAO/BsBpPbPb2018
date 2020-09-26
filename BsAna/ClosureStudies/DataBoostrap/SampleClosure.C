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
#include <vector>
#include <random>

//#include "his.h"
using namespace std;

using std::cout;
using std::endl;

void SampleClosure(int CentMin, int CentMax, int PtOpt){


	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	double ptWidth;
	double RawYield;
	double CorrectedYield;

	double NCorrMin;
	double NCorrMax;


	double AverageRawYield = 0;
	double RawYieldPullValue;
	double RawYieldError;



	double NEvents = 10;


	double ptBins[2];
	double BsRaw = 0;

	TString outfilefolder;

	if(CentMin == 0 && CentMax == 90 && PtOpt == 0){

		NEvents = 6;
		ptBins[0] = 7;
		ptBins[1] = 10;
		NCorrMin = 0;
		NCorrMax = 7000;
		BsRaw = 7.75993;
	}

	if(CentMin == 0 && CentMax == 90 && PtOpt == 1){

		NEvents = 30.5269;
		ptBins[0] = 10;
		ptBins[1] = 15;
		NCorrMin = 0;
		NCorrMax = 5500;
		BsRaw =  30.5269;
	}


	if(CentMin == 0 && CentMax == 90 && PtOpt == 2){

		NEvents = 30;
		ptBins[0] = 15;
		ptBins[1] = 20;
		NCorrMin = 0;
		NCorrMax = 1000;
		BsRaw = 26.0915;
	}



	if(CentMin == 0 && CentMax == 90 && PtOpt == 3){

		NEvents = 34;
		ptBins[0] = 20;
		ptBins[1] = 50;
		NCorrMin = 0;
		NCorrMax = 1000;
		BsRaw = 29.455;
	}


	if(CentMin == 0 && CentMax == 90 && PtOpt == -1){

		NEvents = 83.9719;
		ptBins[0] = 10;
		ptBins[1] = 50;
		NCorrMin = 100;
		NCorrMax = 6500;
		BsRaw =  83.9719;

	}

	if(CentMin == 0 && CentMax == 30 && PtOpt == -1){

		NEvents = 60;
		ptBins[0] = 10;
		ptBins[1] = 50;
		NCorrMin = 1000;
		NCorrMax = 8000;
		BsRaw =  57.7147;

	}


	if(CentMin == 30 && CentMax == 90 && PtOpt == -1){

		NEvents = 31;
		ptBins[0] = 10;
		ptBins[1] = 50;
		NCorrMin = 0;
		NCorrMax = 1000;
		BsRaw =  31.195;

	}


	TF1 *f3 = new TF1("f3","gaus",NEvents * 0.5,NEvents *2.5);
	TF1 *f2 = new TF1("f2","gaus",NEvents * 0.1,NEvents *0.4);



	if(CentMin == 0 && CentMax ==90 && PtOpt == 0) outfilefolder = "7-10";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 1)  outfilefolder = "10-15";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 2)  outfilefolder = "15-20";
	if(CentMin == 0 && CentMax ==90 && PtOpt == 3)	 outfilefolder = "20-50";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 0 && CentMax ==30 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 30 && CentMax ==90 && PtOpt == -1)  outfilefolder = "10-50";
	if(CentMin == 0 && CentMax ==90 && PtOpt == -2)  outfilefolder = "10-50";

	const int NCand = 10;


	TH1D * SampleSize = new TH1D("SampleSize","",100, 0 ,100);
	if(PtOpt == -1  && CentMin == 0 && CentMax == 90 ) SampleSize = new TH1D("SampleSize","",100, 100 ,200);
	if(PtOpt == -1  && CentMin == 0 && CentMax == 30 ) SampleSize = new TH1D("SampleSize","",100, 60 ,170);
	if(PtOpt == -1  && CentMin == 30 && CentMax == 90 ) SampleSize = new TH1D("SampleSize","",50, 10 ,60);
	if(PtOpt == 0  && CentMin == 0 && CentMax == 90 ) SampleSize = new TH1D("SampleSize","",20, 0 ,20);

	SampleSize->GetXaxis()->SetTitle("Pseudo Data Resamples Size");
	SampleSize->GetYaxis()->SetTitle("Counts");
	SampleSize->SetTitle("");
	SampleSize->GetXaxis()->CenterTitle();
	SampleSize->GetYaxis()->CenterTitle();

	
	const int NBinsEffDis = 150;



	TH1D * EffDis = new TH1D("EffDis","",NBinsEffDis,0, 100);
	if(PtOpt == -1 && CentMin == 0 && CentMax == 30) EffDis = new TH1D("EffDis","",NBinsEffDis,0, 100);
	if(PtOpt == -1 && CentMin == 30 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,0, 30);
	if(PtOpt == 0 && CentMin == 0 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,100, 1000);
	if(PtOpt == 1 && CentMin == 0 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,50, 200);
	if(PtOpt == 2 && CentMin == 0 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,10, 30);
	if(PtOpt == 3 && CentMin == 0 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,0, 20);
	if(PtOpt == -1 && CentMin == 0 && CentMax == 90)  EffDis = new TH1D("EffDis","",NBinsEffDis,20, 80);
	EffDis->GetXaxis()->SetTitle("<1/acc x eff> Distribution");
	EffDis->GetYaxis()->SetTitle("Counts");
	EffDis->SetTitle("");
	EffDis->GetXaxis()->CenterTitle();
	EffDis->GetYaxis()->CenterTitle();

	TH1D * CorrYieldDis = new TH1D("CorrYieldDis","",50,NCorrMin, NCorrMax);
	CorrYieldDis->GetXaxis()->SetTitle("Corrected Yield Distribution");
	CorrYieldDis->GetYaxis()->SetTitle("Counts");
	CorrYieldDis->SetTitle("");
	CorrYieldDis->GetXaxis()->CenterTitle();
	CorrYieldDis->GetYaxis()->CenterTitle();



	TH1D * RawYieldPlot = new TH1D("RawYieldPlot","",50,0, NEvents * 4);
	RawYieldPlot->GetXaxis()->SetTitle("Raw Yield Distribution");
	RawYieldPlot->GetYaxis()->SetTitle("Counts");
	RawYieldPlot->SetTitle("");
	RawYieldPlot->GetXaxis()->CenterTitle();
	RawYieldPlot->GetYaxis()->CenterTitle();



	TH1D * RawYieldErrorPlot = new TH1D("RawYieldErrorPlot","",50,0, NEvents * 0.5);
	if(PtOpt == 0) RawYieldErrorPlot = new TH1D("RawYieldErrorPlot","",50,0, 12);

	RawYieldErrorPlot->GetXaxis()->SetTitle("Raw Yield Error Distribution");
	RawYieldErrorPlot->GetYaxis()->SetTitle("Counts");
	RawYieldErrorPlot->SetTitle("");
	RawYieldErrorPlot->GetXaxis()->CenterTitle();
	RawYieldErrorPlot->GetYaxis()->CenterTitle();


	TH1D * RawYieldPull = new TH1D("RawYieldPull","",50,-5, 5);
	//if(PtOpt == 0) RawYieldPull = new TH1D("RawYieldPull","",50,-5, 5);
	RawYieldPull->GetXaxis()->SetTitle("Raw Yield Pull Distribution");
	RawYieldPull->GetYaxis()->SetTitle("Counts");
	RawYieldPull->SetTitle("");
	RawYieldPull->GetXaxis()->CenterTitle();
	RawYieldPull->GetYaxis()->CenterTitle();



	const int NFiles = 1000;

	TString FitFile; 
	TString EffFile; 

	TFile * finFit;
	TFile  * finEff;

	int NCounts;
	double TotalEfficiency; 
	double Efficiency;

//	const int NTotalPar = 8;
//	int lumikey[NTotalPar] = {204,285,433,305,1070,120,473,353};

//	int evtkey[NTotalPar] = {106921701,152788405,240695209,145993081,525319086,41108459,191174250,151945735};

//	int lumikey[NTotalPar] = {204,285,433,305,1070,120,473,353};

//	const int NTotalPar = 8;
//	int evtkey[NTotalPar] = {106921701,152788405,240695209,145993081,525319086,41108459,191174250,151945735};


//	const int NTotalPar = 63;
//	int evtkey[NTotalPar] = {238067182,359558265,39973536,84106221,110999482,134509540,280186337,1630389,111291661,112916331,202307592,42241605,200248301,95389722,99045380,179998168,243506486,66466158,269829565,203432337,89708841,74294344,143652629,266928832,26087816,110996470,151994711,272933351,397054662,267244646,416971381,451270705,317348973,8215120,15542894,49779327,62953932,605175199,8131666,330763337,132786295,19100286,89140398,419810053,276996069,183781341,5589195,91527871,48998190,24101037,64505542,25066161,48349604,339298391,126564739,171624112,22618249,7812328,3379182,53572903,144872395,90509330,108396742};

//	const int NTotalPar = 8;

//	const int NTotalPar = 43;
//	int evtkey[NTotalPar] = {5810272,159246933,200570164,92838266,151089051,21050659,427252314,89872073,96321574,394574003,102658856,186411653,109022613,91436751,376746978,218146048,13081735,188384823,19267158,7110284,137767744,11157967,102340045,62423768,106963455,30432602,311958396,21878536,120460857,156159289,62290090,78463505,83355954,92335708,208403560,254058938,311472320,94085354,371625873,165770526,120138674,159440286,31062772};


//	const int NTotalPar = 48;
//	int evtkey[NTotalPar] = {336605745,37221809,212613636,308715188,539237792,253442021,434121757,469986216,54548406,133368392,242438421,87985990,529009977,205404750,141454508,33618470,150133779,193508992,241652273,313646428,76850973,132992799,135494878,31065670,31810417,3927827,6779706,7756148,5143967,324532920,92044479,223534290,227919267,33193239,137050817,96420176,200443399,38078840,15145834,17786913,29252827,129598712,126338642,259153015,104335565,246596711,431509544,373267314};


	//const int NTotalPar = 120;
	//int evtkey[NTotalPar] = {238067182,336605745,359558265,39973536,37221809,84106221,539237792,5810272,159246933,253442021,110999482,434121757,469986216,54548406,134509540,151089051,242438421,242438421,280186337, 1630389,111291661,112916331,427252314,89872073,96321574,394574003,102658856,42241605,109022613,200248301,91436751,95389722,99045380,205404750,376746978,218146048,243506486,141454508,66466158,13081735,33618470,188384823,137767744,89708841,150133779,74294344,241652273,266928832,11157967,26087816,102340045,110996470,62423768,106963455,151994711,272933351,397054662,30432602,267244646,313646428,416971381,76850973,317348973,8215120,21878536,15542894,120460857,135494878,49779327,605175199,8131666,62290090,132786295,19100286,89140398,7756148,324532920,419810053,78463505,83355954,92044479,92335708,208403560,227919267,33193239,137050817,254058938,276996069,183781341,5589195,311472320,91527871,48998190,24101037,94085354,371625873,165770526,96420176,159440286,25066161,48349604};



//	const int NTotalPar = 40;
//	int evtkey[NTotalPar] = {212613636,308715188,200570164,92838266,133368392,21050659,202307592,87985990,529009977,186411653,200248301,179998168,188384823,19267158,7110284,269829565,203432337,143652629,193508992,62423768,106963455,311958396,451270705,132992799,156159289,62953932,330763337,31065670,31810417,3927827,6779706,5143967,78463505,223534290,64505542,120138674,38078840,7812328,144872395,246596711};


	//Start Input Files//

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



	//DONE INPUTING FILES



	const int NTotalPar = 154;
	int evtkey[NTotalPar] = {238067182,336605745,359558265,39973536,37221809,84106221,212613636,308715188,539237792,5810272,159246933,200570164,253442021,110999482,434121757,469986216,54548406,92838266,133368392,134509540,151089051,242438421,280186337,1630389,21050659,111291661,112916331,202307592,427252314,87985990,89872073,96321574,394574003,529009977,102658856,186411653,42241605,109022613,200248301,91436751,95389722,99045380,205404750,376746978,218146048,179998168,243506486,141454508,66466158,13081735,33618470,188384823,19267158,7110284,269829565,137767744,203432337,89708841,150133779,74294344,143652629,193508992,241652273,266928832,11157967,26087816,102340045,110996470,62423768,106963455,151994711,272933351,397054662,30432602,267244646,311958396,313646428,416971381,451270705,76850973,317348973,8215120,21878536,15542894,120460857,132992799,135494878,156159289,49779327,62953932,605175199,8131666,330763337,62290090,132786295,19100286,89140398,31065670,31810417,3927827,6779706,7756148,5143967,324532920,419810053,78463505,83355954,92044479,92335708,208403560,223534290,227919267,33193239,137050817,254058938,276996069,183781341,5589195,311472320,91527871,48998190,24101037,94085354,64505542,371625873,165770526,96420176,120138674,159440286,25066161,48349604,339298391,126564739,171624112,200443399,38078840,22618249,7812328,15145834,3379182,17786913,53572903,29252827,129598712,126338642,259153015,104335565,144872395,90509330,31062772,246596711,431509544,373267314,108396742};

	int DoLater = 1;

	int EtaBin;
	int PtBin;

	int index;

	int ReuseEach[NFiles][NTotalPar];
	int ReuseTotalSummed[NTotalPar];
	int ReUseLargest[NFiles];
	double TotalEventSample[NFiles];

	double LargestPerSample = 0;
	double SumTotalSamles = 0;
	double ReuseTotalLargest = 0;


	for(int i = 0; i < NFiles; i++){
		ReUseLargest[i] = 0;
	}
	
	for(int j = 0; j < NTotalPar; j++){
		for(int i = 0; i < NFiles; i++){
			ReuseEach[i][j] = -1;
		}

		ReuseTotalSummed[j] = 0;
	}	

	for(int q = 0; q < NFiles; q++){
	
		EffFile = Form("DataResample/%d-%d/%s/MC_%d.root",CentMin,CentMax,outfilefolder.Data(),q);
		finEff = new TFile(EffFile.Data());
		finEff->cd();

		TTree * EffInfoTree = (TTree * ) finEff->Get("EffInfoTree");
		TTree * MuonInfoTree = (TTree * ) finEff->Get("MuonInfoTree");


		Efficiency = 0;
		TotalEfficiency = 0;
		NCounts = 0;

		Int_t BsizeNew;
		Float_t BmassNew[NCand];
		Float_t BptNew[NCand];
		Float_t ByNew[NCand];
		Float_t BEffInv[NCand];
		Int_t evtNew;
		Int_t lumiNew;	
		Int_t Bmu1Type[NCand];
		Int_t Bmu2Type[NCand];

		EffInfoTree->SetBranchAddress("BsizeNew",&BsizeNew);
		EffInfoTree->SetBranchAddress("BEffInv",BEffInv);
		EffInfoTree->SetBranchAddress("BmassNew",BmassNew);
		EffInfoTree->SetBranchAddress("ByNew",ByNew);
		EffInfoTree->SetBranchAddress("BptNew",BptNew);
		EffInfoTree->SetBranchAddress("evtNew",&evtNew);
		EffInfoTree->SetBranchAddress("lumiNew",&lumiNew);

		MuonInfoTree->SetBranchAddress("Bmu1Type",Bmu1Type);
		MuonInfoTree->SetBranchAddress("Bmu2Type",Bmu2Type);

			

		NEvents = EffInfoTree->GetEntries();
		SampleSize->Fill(NEvents);
		TotalEventSample[q] = NEvents;

		for( int i = 0; i < NEvents; i++){


			EffInfoTree->GetEntry(i);
		
			MuonInfoTree->GetEntry(i);

			for(int j = 0; j < BsizeNew; j++){


				if(BptNew[j] > ptBins[0] && BptNew[j] < ptBins[1] && (( BptNew[j] < 10 && TMath::Abs(BmassNew[j] - 5.36682) < 0.09) || (BptNew[j] > 10 && TMath::Abs(BmassNew[j] - 5.36682) < 0.08)))
				{

					if(DoLater == 1){

							EtaBin = tnp_scale1->GetYaxis()->FindBin(ByNew[j]);
							PtBin = tnp_scale1->GetXaxis()->FindBin(BptNew[j]);
							
				//			cout<< "tnp_scaleOld = " << tnp_scaleOld->GetBinContent(PtBin,EtaBin)  << "   tnp_scale = " <<   tnp_scale->GetBinContent(PtBin,EtaBin) << "  tnp_scale0 =  " << tnp_scale0->GetBinContent(PtBin,EtaBin)  <<  "   tnp_scale1 =  " << tnp_scale1->GetBinContent(PtBin,EtaBin) <<   "   tnp_scale2 =  " << tnp_scale2->GetBinContent(PtBin,EtaBin) <<  "   tnp_scale3 =  " << tnp_scale3->GetBinContent(PtBin,EtaBin) <<  "   tnp_scale4 =  " << tnp_scale4->GetBinContent(PtBin,EtaBin) << endl;
				
							if(Bmu1Type[j] == 0 && Bmu2Type[j] == 1){
								
								EtaBin = tnp_scale1->GetYaxis()->FindBin(ByNew[j]);
								PtBin = tnp_scale1->GetXaxis()->FindBin(BptNew[j]);
								BEffInv[j] =  BEffInv[j]/tnp_scale1->GetBinContent(PtBin,EtaBin);

							
							}
						

				
							if(Bmu1Type[j] == 1 && Bmu2Type[j] == 0){
								
								EtaBin = tnp_scale2->GetYaxis()->FindBin(ByNew[j]);
								PtBin = tnp_scale2->GetXaxis()->FindBin(BptNew[j]);
								BEffInv[j] =  BEffInv[j]/tnp_scale2->GetBinContent(PtBin,EtaBin);
							
							}


				
							if(Bmu1Type[j] == 0 && Bmu2Type[j] == 0){
								
								EtaBin = tnp_scale3->GetYaxis()->FindBin(ByNew[j]);
								PtBin = tnp_scale3->GetXaxis()->FindBin(BptNew[j]);
								BEffInv[j] =  BEffInv[j]/tnp_scale3->GetBinContent(PtBin,EtaBin);
						
							}


							if(Bmu1Type[j] == 1 && Bmu2Type[j] == 1){
						
								EtaBin = tnp_scale4->GetYaxis()->FindBin(ByNew[j]);
								PtBin = tnp_scale4->GetXaxis()->FindBin(BptNew[j]);
								BEffInv[j] =  0.5 * ( BEffInv[j]/tnp_scale1->GetBinContent(PtBin,EtaBin) +  BEffInv[j]/tnp_scale2->GetBinContent(PtBin,EtaBin));
							
							}



						}



					TotalEfficiency = BEffInv[j] + TotalEfficiency;
					NCounts = NCounts + 1;
					
				}

			}
			
			for(int k = 0; k < NTotalPar; k++){
				
				if(evtNew == evtkey[k]){
					ReuseEach[q][k] = ReuseEach[q][k] + 1;
				
				}
			}

		}

		//		cout << "TotalEfficiency = " << TotalEfficiency << "  NCounts = " << NCounts << endl;

		if(NCounts > 0) Efficiency = TotalEfficiency/NCounts;

		FitFile = Form("ROOTfiles/%d-%d/%s/yields_Bs_full_%d.root",CentMin,CentMax,outfilefolder.Data(),q);
		finFit	= new TFile(FitFile.Data());

		TH1D * hisFit = (TH1D *) finFit->Get("hPt");
		RawYield = hisFit->GetBinContent(1) * (ptBins[1] - ptBins[0]);
		RawYieldError =  hisFit->GetBinError(1) * (ptBins[1] - ptBins[0]);
		

		CorrectedYield = RawYield * Efficiency;

		//cout << "Efficiency = " << Efficiency << endl;

		CorrYieldDis->Fill(CorrectedYield);

		EffDis->Fill(Efficiency);

		AverageRawYield = AverageRawYield + RawYield;

		RawYieldPullValue = (RawYield - BsRaw)/RawYieldError;

		finEff->Close();
		finFit->Close();

		RawYieldPlot->Fill(RawYield);
		RawYieldErrorPlot->Fill(RawYieldError);
		RawYieldPull->Fill(RawYieldPullValue);



	}

	for(int q = 0; q < NFiles; q++){

			for(int k = 0; k < NTotalPar; k++){
			
				if(ReuseEach[q][k] > ReUseLargest[q])  ReUseLargest[q] = ReuseEach[q][k];
			
				//cout << "ReuseEach[q][k]   =  " <<  ReuseEach[q][k] << endl;
			}

			if(double(ReUseLargest[q])/double(TotalEventSample[q]) > LargestPerSample  )  LargestPerSample = double(ReUseLargest[q])/double(TotalEventSample[q]);
	}

	for(int k = 0; k < NTotalPar; k++){
			for(int q = 0; q < NFiles; q++){
			
				ReuseTotalSummed[k] = ReuseTotalSummed[k] + ReuseEach[q][k];
			
			}
	}


	for(int q = 0; q < NFiles; q++){
		SumTotalSamles = SumTotalSamles + TotalEventSample[q];

	}


	for(int k = 0; k < NTotalPar; k++){
			
		if(ReuseTotalSummed[k]/SumTotalSamles > ReuseTotalLargest) ReuseTotalLargest = ReuseTotalSummed[k]/SumTotalSamles;
			
	}




	AverageRawYield = AverageRawYield/NFiles;

	cout << "Average Raw Yield is " << AverageRawYield << endl;

	double StatError = CorrYieldDis->GetRMS()/CorrYieldDis->GetMean();

	cout << "Statistical Error = " << 	StatError << endl;

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();
	CorrYieldDis->Draw();

	TLatex * texMeanOnly2 = new TLatex(0.88,0.77,Form("RMS/Mean = %.3f",StatError));
	texMeanOnly2->SetNDC();
	texMeanOnly2->SetTextAlign(32);
	texMeanOnly2->SetTextFont(42);
	texMeanOnly2->SetTextSize(0.03);
	texMeanOnly2->SetLineWidth(2);
	texMeanOnly2->Draw("SAME");

	c->SaveAs(Form("Plots/CorrYield_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));

	double SampleSizeMean = SampleSize->GetMean();


	SampleSize->Draw();

	TLatex * SampleMeanTex = new TLatex(0.88,0.77,Form("NEvent Mean = %.0f",SampleSizeMean));
	SampleMeanTex->SetNDC();
	SampleMeanTex->SetTextAlign(32);
	SampleMeanTex->SetTextFont(42);
	SampleMeanTex->SetTextSize(0.03);
	SampleMeanTex->SetLineWidth(2);
	SampleMeanTex->Draw("SAME");

	c->SaveAs(Form("Plots/SampleSize_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));


	RawYieldPull->Draw();
	TF1 *f4 = new TF1("f4","gaus",-3,3);
	RawYieldPull->Fit(f4,"R");


	double	MeanYieldPullFinal = f4->GetParameter(1);
	double	WidthYieldPullFinal = f4->GetParameter(2);

	double	MeanYieldPullFinalErr = f4->GetParError(1);
	double	WidthYieldPullFinalErr = f4->GetParError(2);

	TLatex * texMeanYield = new TLatex(0.88,0.77,Form("Mean = %.3f #pm %.3f",MeanYieldPullFinal,MeanYieldPullFinalErr));
	texMeanYield->SetNDC();
	texMeanYield->SetTextAlign(32);
	texMeanYield->SetTextFont(42);
	texMeanYield->SetTextSize(0.03);
	texMeanYield->SetLineWidth(2);
	texMeanYield->Draw("SAME");


	TLatex * texWidthYield = new TLatex(0.88,0.67,Form("Width = %.3f #pm %.3f",WidthYieldPullFinal,WidthYieldPullFinalErr));
	texWidthYield->SetNDC();
	texWidthYield->SetTextAlign(32);
	texWidthYield->SetTextFont(42);
	texWidthYield->SetTextSize(0.03);
	texWidthYield->SetLineWidth(2);
	texWidthYield->Draw("SAME");

	c->SaveAs(Form("PlotsRaw/RawYieldPull_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));



	RawYieldPlot->Draw();
	RawYieldPlot->Fit(f3,"R");


	double	MeanYieldFinal = f3->GetParameter(1);
	double	WidthYieldFinal = f3->GetParameter(2);

	double	MeanYieldFinalErr = f3->GetParError(1);
	double	WidthYieldFinalErr = f3->GetParError(2);

	TLatex * texMeanRawYield = new TLatex(0.88,0.77,Form("Mean = %.3f #pm %.3f",MeanYieldFinal,MeanYieldFinalErr));
	texMeanRawYield->SetNDC();
	texMeanRawYield->SetTextAlign(32);
	texMeanRawYield->SetTextFont(42);
	texMeanRawYield->SetTextSize(0.03);
	texMeanRawYield->SetLineWidth(2);
	texMeanRawYield->Draw("SAME");


	TLatex * texWidthRawYield = new TLatex(0.88,0.67,Form("Width = %.3f #pm %.3f",WidthYieldFinal,WidthYieldFinalErr));
	texWidthRawYield->SetNDC();
	texWidthRawYield->SetTextAlign(32);
	texWidthRawYield->SetTextFont(42);
	texWidthRawYield->SetTextSize(0.03);
	texWidthRawYield->SetLineWidth(2);
	texWidthRawYield->Draw("SAME");

	c->SaveAs(Form("PlotsRaw/RawYieldPlot_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));


	RawYieldErrorPlot->Draw();
	RawYieldErrorPlot->Fit(f2,"R");


	double	MeanYieldErrorFinal = f2->GetParameter(1);
	double	WidthYieldErrorFinal = f2->GetParameter(2);

	double	MeanYieldErrorFinalErr = f2->GetParError(1);
	double	WidthYieldErrorFinalErr = f2->GetParError(2);



	TLatex * texMeanRawYieldError = new TLatex(0.88,0.77,Form("Mean = %.3f #pm %.3f",MeanYieldErrorFinal,MeanYieldErrorFinalErr));
	texMeanRawYieldError->SetNDC();
	texMeanRawYieldError->SetTextAlign(32);
	texMeanRawYieldError->SetTextFont(42);
	texMeanRawYieldError->SetTextSize(0.03);
	texMeanRawYieldError->SetLineWidth(2);
	texMeanRawYieldError->Draw("SAME");


	TLatex * texWidthRawYieldError = new TLatex(0.88,0.67,Form("Width = %.3f #pm %.3f",WidthYieldErrorFinal,WidthYieldErrorFinalErr));
	texWidthRawYieldError->SetNDC();
	texWidthRawYieldError->SetTextAlign(32);
	texWidthRawYieldError->SetTextFont(42);
	texWidthRawYieldError->SetTextSize(0.03);
	texWidthRawYieldError->SetLineWidth(2);
	texWidthRawYieldError->Draw("SAME");

	c->SaveAs(Form("PlotsRaw/RawYieldPlotError_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));





	EffDis->Draw();


	double EffMeanCal = EffDis->GetMean();
	double EffWidthCal = EffDis->GetRMS();
	double EffError = EffWidthCal/EffMeanCal;



	TLatex * texEff = new TLatex(0.88,0.77,Form("RMS/Mean = %.3f",EffError));
	texEff->SetNDC();
	texEff->SetTextAlign(32);
	texEff->SetTextFont(42);
	texEff->SetTextSize(0.03);
	texEff->SetLineWidth(2);
	texEff->Draw("SAME");


	c->SaveAs(Form("PlotsEff/Eff_%d_%d_%s.png",CentMin,CentMax,outfilefolder.Data()));


	int MeanBinEff =  EffDis->GetXaxis()->FindBin(EffMeanCal);
	double PercentileEff = 0.3414 * 2;
	double UpPercentileEff = 0;
	double DownPercentileEff = 0;
	int UpBinEff = MeanBinEff;
	int DownBinEff = MeanBinEff;


	cout << "Mean Bin = " << MeanBinEff << endl;
	cout << "Eff :: Performing Up Down Integration" << endl;


	while(UpPercentileEff < PercentileEff){
		UpBinEff = UpBinEff + 1;
		UpPercentileEff = EffDis->Integral(MeanBinEff,UpBinEff)/EffDis->Integral(MeanBinEff,200);
		cout << "Current Up Percentile Eff = " << UpPercentileEff <<  endl;
	}

	while(DownPercentileEff < PercentileEff){
		DownBinEff = DownBinEff - 1;
		DownPercentileEff = EffDis->Integral(DownBinEff,MeanBinEff)/EffDis->Integral(0,MeanBinEff);
		cout << "Current Down Percentile Eff = " << DownPercentileEff <<  endl;

	}

	double SystErrorUpEff = EffDis->GetBinCenter(UpBinEff);
	double SystErrorDownEff = EffDis->GetBinCenter(DownBinEff);


	cout << "Method 2:  SystErrorUp = " << SystErrorUpEff << "  SystErrorDown = " << SystErrorDownEff << endl;


	cout << "INFO : MeanEffForCal = " << EffMeanCal << "  RMS = " << EffWidthCal << endl;

	double PercentageUpEff = (SystErrorUpEff - EffMeanCal)/EffMeanCal;

	double PercentageDownEff = (EffMeanCal - SystErrorDownEff)/EffMeanCal;

	cout << "Method 1 Eff:  Percentile = " << EffWidthCal/EffMeanCal << endl;
	cout << "Method 2 Eff:  PercentileUp = " << PercentageUpEff << "  PercentileDown = " << PercentageDownEff << endl;

	EffDis->Draw();
	texEff->Draw("SAME");
	TLatex * texEff2 = new TLatex(0.88,0.67,Form("RMS/Mean = +%.3f and -%.3f",PercentageUpEff, PercentageDownEff));
	texEff2->SetNDC();
	texEff2->SetTextAlign(32);
	texEff2->SetTextFont(42);
	texEff2->SetTextSize(0.03);
	texEff2->SetLineWidth(2);
	texEff2->Draw("SAME");

	c->SaveAs(Form("PlotsEff/EffDis_%d_%d_%s_Assym.png",CentMin,CentMax,outfilefolder.Data()));






	//if(CentMin == 0 && CentMax == 90 && PtOpt == 0){

	double MeanEffForCal = CorrYieldDis->GetMean();
	double Percentile = 0.3414 * 2;
	int MeanBin =  CorrYieldDis->GetXaxis()->FindBin(MeanEffForCal);
	int ZeroBin =  CorrYieldDis->GetXaxis()->FindBin(0.0);

	double UpPercentile = 0;
	double DownPercentile = 0;
	int UpBin = MeanBin;
	int DownBin = MeanBin;


	cout << "Mean Bin = " << MeanBin << "  Zero Bin = " << ZeroBin << endl;
	cout << "Performing Up Down Integration" << endl;


	while(UpPercentile < Percentile){
		UpBin = UpBin + 1;
		UpPercentile = CorrYieldDis->Integral(MeanBin,UpBin)/CorrYieldDis->Integral(MeanBin,200);
		cout << "Current Up Percentile = " << UpPercentile <<  endl;
	}

	while(DownPercentile < Percentile){
		DownBin = DownBin - 1;
		DownPercentile = CorrYieldDis->Integral(DownBin,MeanBin)/CorrYieldDis->Integral(0,MeanBin);
		cout << "Current Down Percentile = " << DownPercentile <<  endl;

	}

	double SystErrorUp = CorrYieldDis->GetBinCenter(UpBin);
	double SystErrorDown = CorrYieldDis->GetBinCenter(DownBin);


	cout << "Method 2:  SystErrorUp = " << SystErrorUp << "  SystErrorDown = " << SystErrorDown << endl;


	cout << "INFO : MeanEffForCal = " << MeanEffForCal << "  RMS = " << CorrYieldDis->GetRMS() << endl;

	double PercentageUp = (SystErrorUp - MeanEffForCal)/MeanEffForCal;

	double PercentageDown = (MeanEffForCal - SystErrorDown)/MeanEffForCal;

	cout << "Method 1:  Percentile = " << CorrYieldDis->GetRMS()/CorrYieldDis->GetMean() << endl;
	cout << "Method 2:  PercentileUp = " << PercentageUp << "  PercentileDown = " << PercentageDown << endl;

	CorrYieldDis->Draw();
	texMeanOnly2->Draw("SAME");
	TLatex * texMeanOnly3 = new TLatex(0.88,0.67,Form("RMS/Mean = +%.3f and -%.3f",PercentageUp, PercentageDown));
	texMeanOnly3->SetNDC();
	texMeanOnly3->SetTextAlign(32);
	texMeanOnly3->SetTextFont(42);
	texMeanOnly3->SetTextSize(0.03);
	texMeanOnly3->SetLineWidth(2);
	texMeanOnly3->Draw("SAME");

	c->SaveAs(Form("Plots/CorrYield_%d_%d_%s_Assym.png",CentMin,CentMax,outfilefolder.Data()));

	//}



	//Eff Asymmetric//


	cout << "------------------------------------------------------------------------------------------------------------------------"<< endl;

	cout << "Largest Reuse Per Sample = " << LargestPerSample << "    Lagrest Reuse Overall = " << ReuseTotalLargest << endl;
	
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

}
