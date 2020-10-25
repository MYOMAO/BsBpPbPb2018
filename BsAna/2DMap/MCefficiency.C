#include "uti.h"
#include "parameters.h"
#include "TMath.h"

using namespace std;

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=	1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString weightfunctiongen = "1";
TString weightfunctionreco = "1";
Float_t hiBinMin,hiBinMax,centMin,centMax;

int _nBins = nBins;
double *_ptBins = ptBins;
double *_sf_pp = sf_pp;
double *_sf_pbpb = sf_pbpb;
int customizedOpt = 0; //1: remove pt weight, 2: do tk eta weihting

void MCefficiency(int isPbPb=0, TString inputmc="", TString selmcgen="", TString selmcgenacceptance="", TString cut_recoonly="", TString cut="", TString _varExp = "", TString _varGenExp = "", TString label="", TString outputfile="", TString outplotf="", int PbPbweight=0, Float_t centmin=0., Float_t centmax=100.)
{    

	TString varExp = _varExp;
	TString varGenExp = _varGenExp;
	std::string str = _varExp.Data();
	std::size_t found = str.find("Bpt");
	if (found!=std::string::npos){
		varExp = "Bpt";
	}
	found = str.find("noPtWeight");
	if (found!=std::string::npos){
		customizedOpt = 1;
	}
	found = str.find("tkEtaWeight");
	if (found!=std::string::npos){
		customizedOpt = 2;
	}
	if(_varExp == "Bpt750" || _varExp == "Bpt750_noPtWeight"){
		_nBins = nBins750;
		_ptBins = ptBins750;
		_sf_pp = sf_pp_750;
	}
	if(_varExp == "Bpt750_acc"){
		_nBins = nBins750_acc;
		_ptBins = ptBins750_acc;
		_sf_pp = sf_pp_750_acc;
	}
	if(_varExp == "BptCutBase"){
		_sf_pp = sf_pp_CutBase;
	}
	if(_varExp == "BptPbPbBDT"){
		_sf_pp = sf_pp_PbPbBDT;
	}
	if(_varExp == "BptOLDPbPbBDT"){
		_sf_pp = sf_pp_OldPbPbBDT;
	}
	if(_varExp == "abs(By)"){
		_nBins = nBinsY;
		_ptBins = ptBinsY;
		_sf_pp = sf_pp_Y;
	} 

	str = label.Data();
	found = str.find("Fine");
	if (found!=std::string::npos){
		_nBins = nBinsFine;
		_ptBins = ptBinsFine;
	}
	if(label=="ppInc"){
		_nBins = nBinsInc;
		_ptBins = ptBinsInc;
	}

	hiBinMin = centmin*2;
	hiBinMax = centmax*2;
	centMin = centmin;
	centMax = centmax;

	if(isPbPb==1)
	{
		selmcgen = selmcgen+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
		selmcgenacceptance=selmcgenacceptance+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
		cut=cut+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
		cut_recoonly=cut_recoonly+Form("&&hiBin>=%f&&hiBin<=%f ",hiBinMin,hiBinMax);
	}




	printf("############## input parameters\n");
	std::cout<<"selmcgen = "<<selmcgen<<std::endl;
	std::cout<<"selmcgenacceptance = "<<selmcgenacceptance<<std::endl;
	std::cout<<"cut = "<<cut<<std::endl;
	std::cout<<"cut_recoonly = "<<cut_recoonly<<std::endl;
	std::cout<<"PbPbweight = "<<PbPbweight<<std::endl;
	printf("############## input parameters\n");

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetEndErrorSize(0);
	gStyle->SetMarkerStyle(20);

	TFile* infMC = new TFile(inputmc.Data());

	TTree* ntMC = (TTree*)infMC->Get("Bfinder/ntphi");
	TTree* ntGen = (TTree*)infMC->Get("Bfinder/ntGen");


	ntMC->AddFriend("hltanalysis/HltTree");
	ntMC->AddFriend("hiEvtAnalyzer/HiTree");
	ntMC->AddFriend("skimanalysis/HltTree");
	//	ntMC->AddFriend("BDT");
	ntMC->AddFriend("CentWeightTree");


	ntMC->AddFriend("BDT_pt_15_20");
	ntMC->AddFriend("BDT_pt_10_15");
	ntMC->AddFriend("BDT_pt_20_50");
	ntMC->AddFriend("BDT_pt_5_10");
	ntMC->AddFriend("TnPInfo");

	ntMC->AddFriend("Bfinder/ntGen");
	ntMC->AddFriend("BDTMCDataWeightTree");
	ntGen->AddFriend("hiEvtAnalyzer/HiTree");
	ntGen->AddFriend("Bfinder/ntphi");
	ntGen->AddFriend("BDTMCDataWeightTree");



	//ntMC->AddFriend(ntGen);
	//ntMC->AddFriend("ntSkim");
	//ntMC->AddFriend("ntHlt");
	//ntMC->AddFriend("ntHi");
	//ntMC->AddFriend("BDTStage1_pt15to50");

	//ntGen->AddFriend(ntMC);
	//ntGen->AddFriend("ntSkim");
	//ntGen->AddFriend("ntHlt");
	//ntGen->AddFriend("ntHi");
	//ntGen->AddFriend("BDTStage1_pt15to50");

	// weigths
	TCut weighpthat = "pthatweight";
	TCut weightGpt = "1";
	TCut weightBgenpt = "1";
	TCut weightHiBin = "1";
	TCut weightPVz = "1";
	if(PbPbweight==0) {
		weightGpt = weightGpt_pp;
		weightBgenpt = weightBgenpt_pp;
	}
	if(PbPbweight==1) {
		weightGpt = weightGpt_PbPb;
		weightBgenpt = weightBgenpt_PbPb;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==2) {
		weightGpt = weightGpt_PbPb_NLO;
		weightBgenpt = weightBgenpt_PbPb_NLO;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==3) {
		weightGpt = weightGpt_PbPb_NominalPP;
		weightBgenpt = weightBgenpt_PbPb_NominalPP;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==4) {
		weightGpt = weightGpt_PbPb_VariationPP;
		weightBgenpt = weightBgenpt_PbPb_VariationPP;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==5) {
		weightGpt = weightGpt_PbPb_NominalTAMU;
		weightBgenpt = weightBgenpt_PbPb_NominalTAMU;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==6) {
		weightGpt = weightGpt_PbPb_VariationTAMU;
		weightBgenpt = weightBgenpt_PbPb_VariationTAMU;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==7) {
		weightGpt = weightGpt_PbPb_TAMUPP;
		weightBgenpt = weightBgenpt_PbPb_TAMUPP;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==8) {
		weightGpt = weightGpt_PbPb_DataCentral;
		weightBgenpt = weightBgenpt_PbPb_DataCentral;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==9) {
		weightGpt = weightGpt_PbPb_Data1PS;
		weightBgenpt = weightBgenpt_PbPb_Data1PS;;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==10) {
		weightGpt = weightGpt_PbPb_Data1MS;
		weightBgenpt = weightBgenpt_PbPb_Data1MS;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==11) {
		weightGpt = weightGpt_PbPb_Linear;
		weightBgenpt = weightBgenpt_PbPb_Linear;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==12) {
		weightGpt = weightGpt_PbPb_Quadratic;
		weightBgenpt = weightBgenpt_PbPb_Quadratic;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==13) {
		weightGpt = weightGpt_PbPb_LInverse;
		weightBgenpt = weightBgenpt_PbPb_LInverse;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==14) {
		weightGpt = weightGpt_PbPb_LSqrt;
		weightBgenpt = weightBgenpt_PbPb_LSqrt;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==15) {
		weightGpt = weightGpt_PbPb_LLog;
		weightBgenpt = weightBgenpt_PbPb_LLog;
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==16) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==17) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}
	if(PbPbweight==18) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = "1";
		weightPVz = "1";
		weighpthat = "1";
	}
	if(PbPbweight==19) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = "1";
		weightPVz = "1";
	}
	if(PbPbweight==20) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
	}

	TCut BEffInvBDTWeighted = "BEffInvBDTWeighted";
	TCut muid1 = "muid1";
	TCut muid2 = "muid2";
	TCut trk1 = "trk1";
	TCut trk2 = "trk2";
	TCut trg1 = "trg1";	
	TCut trg2 = "trg2";


	if(PbPbweight==21) {
		weightGpt = "1";
		weightBgenpt = "1";
		weightHiBin = weightHiBin_PbPb;
		weightPVz = weightPVz_PbPb;
		muid1 = "1";
		muid2 = "1";
		trk1 = "1";
		trk2 = "1";
		trg1 = "1";	
		trg2 = "1";

	}


	if(customizedOpt == 1) { weightGpt = "1"; weightBgenpt = "1"; }
	//if(customizedOpt == 2) { weightGpt = weightGpt*TCut(weightGtk1eta); weightBgenpt = weightBgenpt*TCut(weightBtk1eta); }
	if(customizedOpt == 2) { weightGpt = weightGpt*TCut(weightGtk1eta)*TCut(weightGtk2eta); weightBgenpt = weightBgenpt*TCut(weightBtk1eta)*TCut(weightBtk2eta); }

	TH1D* hPtMC = new TH1D("hPtMC","",_nBins,_ptBins);
	TH1D* hPtMCrecoonly = new TH1D("hPtMCrecoonly","",_nBins,_ptBins);
	TH1D* hPtGen = new TH1D("hPtGen","",_nBins,_ptBins);
	TH1D* hPtGenWeighted = new TH1D("hPtGenWeighted","",_nBins,_ptBins);
	TH1D* hPtGenAcc = new TH1D("hPtGenAcc","",_nBins,_ptBins);
	TH1D* hPtGenAccWeighted = new TH1D("hPtGenAccWeighted","",_nBins,_ptBins);

	ntMC->Project("hPtMC",varExp.Data(),(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2))*
			TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
	ntMC->Project("hPtMCrecoonly",varExp.Data(), varExp.Data(),(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2))*
			TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut_recoonly.Data())&&"(Bgen==23333)"));

	ntGen->Project("hPtGen",varGenExp.Data(),
			TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgen.Data())));
	ntGen->Project("hPtGenWeighted",varGenExp.Data(),
			TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));
	ntGen->Project("hPtGenAcc",varGenExp.Data(),
			TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgenacceptance.Data())));
	ntGen->Project("hPtGenAccWeighted",varGenExp.Data(),
			TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));

	TH1D* hPthat = new TH1D("hPthat","",100,0,500);
	TH1D* hPthatweight = new TH1D("hPthatweight","",100,0,500);
	ntMC->Project("hPthat","pthat","1");
	ntMC->Project("hPthatweight","pthat",TCut("1"));



	cout << "hPtGen = " << hPtGen->Integral() << endl;
	cout << "hPtGenWeighted = " << hPtGenWeighted->Integral() << endl;


	cout << "Working on Fine" << endl;

	int CorrFactorUse = 0;


	TH1D* hPtMCFine;
	TH1D* hPtGenWeightedFine;
	TH1D* hPtMCrecoonlyFine;
	TH1D* hPtGenFine;
	TH1D* hPtGenAccFine;
	TH1D* hPtGenAccWeightedFine;
	int NFineBins;


	TH1D* hCentMCFine  = new TH1D("hCentMCFine","",200,0,200);
	TH1D* hCentGenWeightedFine = new TH1D("hCentGenWeightedFine","",200,0,200);

	ntMC->Project("hCentMCFine","hiBin", 	(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *
			TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bpt < 50 && Bpt > 5)"&&"(Bgen==23333)"));
	ntGen->Project("hCentGenWeightedFine","hiBin",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())&&"(Gpt < 50 && Gpt > 5)"));


	TH1D * hCentEffInv = (TH1D *) hCentGenWeightedFine->Clone("hCentEffInv");
	hCentEffInv->Sumw2();
	hCentGenWeightedFine->Sumw2();

	hCentEffInv->Divide(hCentMCFine);



	const int yBinN = 5;
	double yBinning[yBinN+1] = {0.0,0.5, 1.0, 1.5,2.0, 2.4};
	int Rebin = 0;

	double LowBinWidth;

	if(Rebin == 0)	LowBinWidth	= 0.5;
	if(Rebin == 1)	LowBinWidth	= 1.0;

	int NLowBin = 5/LowBinWidth;
	//	int NLowBin = 5;

	double MidBinWidth = 1;
	int NMidBin = 10/MidBinWidth;
	double HighBinWidth = 1;
	int NHighBin = 30/HighBinWidth;
	const int BptBin = NHighBin + NMidBin + NLowBin;
	double BptBinning[BptBin + 1];


	cout << "NLowBin = " << NLowBin << " NMidBin = " << NMidBin << " NHighBin = " << NHighBin << endl;

	for(int i = 0; i < NLowBin; i++){
		BptBinning[i] = 5 + i * LowBinWidth;
	}
	for(int i = 0; i < NMidBin; i++){
		BptBinning[i+NLowBin] = 10 + i * MidBinWidth;
	}
	for(int i = 0; i <  NHighBin+1; i++){
		BptBinning[i+NLowBin+NMidBin] = 20 + i * HighBinWidth;
	}



	int donewbinning = 1;
	if(donewbinning ==0){
		if(centmin == 0 && centmax == 90){
			NFineBins = 200;

			hPtMCFine = new TH1D("hPtMCFine","",NFineBins,5,50);
			hPtGenWeightedFine = new TH1D("hPtGenWeightedFine","",NFineBins,5,50);
			hPtMCrecoonlyFine  = new TH1D("hPtMCrecoonlyFine","",NFineBins,5,50);
			hPtGenFine  = new TH1D("hPtGenFine","",NFineBins,5,50);
			hPtGenAccFine  = new TH1D("hPtGenAccFine","",NFineBins,5,50);
			hPtGenAccWeightedFine  = new TH1D("hPtGenAccWeightedFine","",NFineBins,5,50);

		}
		else{
			NFineBins = 90;

			hPtMCFine = new TH1D("hPtMCFine","",NFineBins,5,50);
			hPtGenWeightedFine = new TH1D("hPtGenWeightedFine","",NFineBins,5,50);
			hPtMCrecoonlyFine  = new TH1D("hPtMCrecoonlyFine","",NFineBins,5,50);
			hPtGenFine  = new TH1D("hPtGenFine","",NFineBins,5,50);
			hPtGenAccFine  = new TH1D("hPtGenAccFine","",NFineBins,5,50);
			hPtGenAccWeightedFine  = new TH1D("hPtGenAccWeightedFine","",NFineBins,5,50);

		}
	}


	if(donewbinning == 1){
		hPtMCFine = new TH1D("hPtMCFine","",BptBin,BptBinning);
		hPtGenWeightedFine = new TH1D("hPtGenWeightedFine","",BptBin,BptBinning);
		hPtMCrecoonlyFine  = new TH1D("hPtMCrecoonlyFine","",BptBin,BptBinning);
		hPtGenFine  = new TH1D("hPtGenFine","",BptBin,BptBinning);
		hPtGenAccFine  = new TH1D("hPtGenAccFine","",BptBin,BptBinning);
		hPtGenAccWeightedFine  = new TH1D("hPtGenAccWeightedFine","",BptBin,BptBinning);
	}




	TH1D * hPtMCFineNW = new TH1D("hPtMCFineNW","",BptBin,BptBinning);
	TH1D * hPtGenWeightedFineNW = new TH1D("hPtGenWeightedFineNW","",BptBin,BptBinning);



	ntMC->Project("hPtMCFineNW",varExp.Data(), (TCut(cut.Data())&&"(Bgen==23333)"));
	ntGen->Project("hPtGenWeightedFineNW",varGenExp.Data(),(TCut(selmcgen.Data())));


	cout << "RECO = " << hPtMCFineNW->Integral() << "    GEN =  " << hPtGenWeightedFineNW->Integral() << endl;



	divideBinWidth(hPtMCFine);
	divideBinWidth(hPtMCrecoonlyFine);
	divideBinWidth(hPtGenFine);
	divideBinWidth(hPtGenWeightedFine);
	divideBinWidth(hPtGenAccFine);
	divideBinWidth(hPtGenAccWeightedFine);

	ntMC->Project("hPtMCFine",varExp.Data(), 	(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *
			TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
	ntGen->Project("hPtGenWeightedFine",varGenExp.Data(),TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));


	cout << "selmcgen = " << selmcgen.Data() << endl;
	cout << "Total  hPtMCFine = " << hPtMCFine->Integral() << endl;
	cout << "Total  hPtGenWeightedFine = " << hPtGenWeightedFine->Integral() << endl;

	ntGen->Project("hPtGenFine",varGenExp.Data(), TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgen.Data())));
	ntGen->Project("hPtGenWeightedFine",varGenExp.Data(),TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));
	ntGen->Project("hPtGenAccFine",varGenExp.Data(),	TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgenacceptance.Data())));
	ntGen->Project("hPtGenAccWeightedFine",varGenExp.Data(),TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));



	TH2D * hBptCent = new TH2D("hBptCent","hBptCent",9,0,90,5,5,10);
	ntMC->Project("hBptCent","Bpt:hiBin/2",	(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *
			TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));



	hPtMCFine->Sumw2();
	hPtMCrecoonlyFine->Sumw2();
	hPtGenFine->Sumw2();
	hPtGenAccFine->Sumw2();	gStyle->SetPadRightMargin(cRightMargin);
	hPtGenAccWeightedFine->Sumw2();
	//Acceptance
	TH1D* hEffAccFine = (TH1D*)hPtGenAccFine->Clone("hEffAccFine");
	hEffAccFine->Sumw2();
	hEffAccFine->Divide(hEffAccFine,hPtGenFine,1,1,"b");




	TH1D* hEffFineInv = (TH1D * ) hPtGenWeightedFine->Clone("hEffFineInv");
	hEffFineInv->Sumw2();
	hPtMCFine->Sumw2();
	hEffFineInv->Divide(hPtMCFine);

	TH1D* hEffFine = (TH1D * ) hPtMCFine->Clone("hEffFine");
	hEffFine->Sumw2();
	hPtGenWeightedFine->Sumw2();
	hEffFine->Divide(hPtGenWeightedFine);




	TH2D * EffBptByMC; 
	TH2D * EffBptByGen;

	gStyle->SetPadRightMargin(1.5);
	EffBptByMC	= new TH2D("EffBptByMC","EffBptByMC",BptBin,BptBinning,yBinN,yBinning);
	EffBptByGen  = new TH2D("EffBptByGen","EffBptByGen",BptBin,BptBinning,yBinN,yBinning);


	//Additional Codes Manually Weighting//



	TH2D * EffBptByGenZoom  = new TH2D("EffBptByGenZoom","EffBptByGenZoom",10,5,10,100,0,2.4);

	ntGen->Project("EffBptByGenZoom","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));


	TH2D * EffBptByMCZoom  = new TH2D("EffBptByMCZoom","EffBptByMCZoom",10,5,10,100,0,2.4);

	ntMC->Project("EffBptByMCZoom","TMath::Abs(By):Bpt", 	(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) * TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data()) &&"(Bgen==23333)"));


	TH2D * EffZoom = (TH2D *) EffBptByGenZoom->Clone("EffZoom");
	EffZoom->Sumw2();
	EffBptByMCZoom->Sumw2();
	EffZoom->Divide(EffBptByMCZoom);


	ntMC->Project("EffBptByMC","TMath::Abs(By):Bpt", (TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) * TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data()) &&"(Bgen==23333)"));
	ntGen->Project("EffBptByGen","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));


	TString FolderName;	

	if(Rebin == 0){
		if(PbPbweight == 21 ) FolderName = "NoTnP";		
		if(PbPbweight == 20 ) FolderName = "NoTrg";		
		if(PbPbweight == 19 ) FolderName = "Original";		
		if(PbPbweight == 18 ) FolderName = "NoPthat";	
		if(PbPbweight == 17 ) FolderName = "NoWightCut";
		if(PbPbweight == 16 ) FolderName = "NoWeight";
		if(PbPbweight == 1) FolderName = "FONLL";
		if(PbPbweight == 11) FolderName = "Linear";
		if(PbPbweight == 12) FolderName = "Quadratic";
		if(PbPbweight == 13) FolderName = "LInverse";
		if(PbPbweight == 14) FolderName = "LSqrt";
		if(PbPbweight == 15) FolderName = "LLog";
	}



	if(Rebin == 1){
		if(PbPbweight == 16 ) FolderName = "Rebin/NoWeight";
		if(PbPbweight == 1) FolderName = "Rebin/FONLL";
		if(PbPbweight == 11) FolderName = "Rebin/Linear";
		if(PbPbweight == 12) FolderName = "Rebin/Quadratic";
		if(PbPbweight == 13) FolderName = "Rebin/LInverse";
		if(PbPbweight == 14) FolderName = "Rebin/LSqrt";
		if(PbPbweight == 15) FolderName = "Rebin/LLog";
	}

	TH2D * EffBptByGenAccWeightedFine  = new TH2D("EffBptByGenAccWeightedFine","EffBptByGenAccWeightedFine",BptBin,BptBinning,yBinN,yBinning);


	ntGen->Project("EffBptByGenAccWeightedFine","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));


	TH2D * hPtGenAcc2DFine  = new TH2D("hPtGenAcc2DFine","hPtGenAcc2DFine",BptBin,BptBinning,yBinN,yBinning);
	ntGen->Project("hPtGenAcc2DFine","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));

	TH2D * hPtGen2DFine  = new TH2D("hPtGen2DFine","hPtGen2DFine",BptBin,BptBinning,yBinN,yBinning);
	ntGen->Project("hPtGen2DFine","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));

	TH2D * hPtAccInv2DFine = (TH2D * ) hPtGen2DFine->Clone("hPtAccInv2DFine");
	hPtAccInv2DFine->Sumw2();
	hPtGenAcc2DFine->Sumw2();
	hPtAccInv2DFine->Divide(hPtGenAcc2DFine);

	TH2D* hEffSelectionFine = (TH2D*) EffBptByGenAccWeightedFine->Clone("hEffSelectionFine");
	hEffSelectionFine->Sumw2();
	hEffSelectionFine->Divide(hEffSelectionFine,EffBptByMC,1,1,"b");

	TH2D * hInv2ShotHere = (TH2D *) hPtAccInv2DFine->Clone("hInv2ShotHere");
	hInv2ShotHere->Sumw2();
	hEffSelectionFine->Sumw2();
	hInv2ShotHere->Multiply(hEffSelectionFine);

	TString FinAccName;

	if(Rebin == 0) FinAccName = "AccNew.root";
	if(Rebin == 1) FinAccName = "AccNewRebin.root";


	TFile * finAccNew = new TFile(FinAccName.Data());
	finAccNew->cd();

	TH2D * hEffAcc2DFine = (TH2D *) finAccNew->Get("hEffAcc2DFine");
	TH2D* hEff2DInv2Shots = (TH2D*)hEffSelectionFine->Clone("hEff2DInv2Shots");
	hEff2DInv2Shots->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2Shots->Multiply(hEffAcc2DFine);



	if(CorrFactorUse == 1){
		TFile * finCorrFact = new TFile("CorrFactorHis.root");
		finCorrFact->cd();
		TH2D * CorrFactorRatio1 = (TH2D *) finCorrFact->Get("CorrFactorRatio1");

		EffBptByGen->Sumw2();
		CorrFactorRatio1->Sumw2();
		EffBptByGen->Multiply(CorrFactorRatio1);
	}

	TH2D *  EffBptByMCBDTWeighted	= new TH2D("EffBptByMCBDTWeighted","EffBptByMCBDTWeighted",BptBin,BptBinning,yBinN,yBinning);
	TH2D * 	EffBptByGenBDTWeighted  = new TH2D("EffBptByGenBDTWeighted","EffBptByGenBDTWeighted",BptBin,BptBinning,yBinN,yBinning);


	ntMC->Project("EffBptByMCBDTWeighted","TMath::Abs(By):Bpt", (TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *  TCut(BEffInvBDTWeighted)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data()) &&"(Bgen==23333)"));
	ntGen->Project("EffBptByGenBDTWeighted","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));



	TH2D * EffBptByMChyperfine = new TH2D("EffBptByMChyperfine","EffBptByMChyperfine",500,5,50,200,0,2.4); 
	TH2D * EffBptByGenhyperfine = new TH2D("EffBptByGenhyperfine","EffBptByGenhyperfine",500,5,50,200,0,2.4);;

	ntMC->Project("EffBptByMChyperfine","TMath::Abs(By):Bpt", (TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *  TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
	ntGen->Project("EffBptByGenhyperfine","TMath::Abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));




	TH2D * EffBptBy = (TH2D *) EffBptByMC->Clone("EffBptBy");
	EffBptByMC->Sumw2();
	EffBptByGen->Sumw2();
	EffBptBy->Divide(EffBptByGen);

	EffBptBy->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	EffBptBy->GetYaxis()->SetTitle("B_{s} y");
	EffBptBy->GetYaxis()->SetTitleOffset(1.5);


	EffBptBy->GetXaxis()->CenterTitle();
	EffBptBy->GetYaxis()->CenterTitle();





	TH2D * EffBptByInv = (TH2D *) EffBptByGen->Clone("EffBptByInv");

	EffBptByInv->Sumw2();
	EffBptByMC->Sumw2();
	EffBptByInv->Divide(EffBptByMC);

	EffBptByInv->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	EffBptByInv->GetYaxis()->SetTitle("B_{s} y");
	EffBptByInv->GetYaxis()->SetTitleOffset(1.5);


	EffBptByInv->GetXaxis()->CenterTitle();
	EffBptByInv->GetYaxis()->CenterTitle();



	TH2D * EffBptByInvBDTWeighted = (TH2D *) EffBptByGenBDTWeighted->Clone("EffBptByInvBDTWeighted");

	EffBptByInvBDTWeighted->Sumw2();
	EffBptByMCBDTWeighted->Sumw2();
	EffBptByInvBDTWeighted->Divide(EffBptByMCBDTWeighted);

	EffBptByInvBDTWeighted->GetXaxis()->SetTitle("B_{s} p_{T} (GeV/c)");
	EffBptByInvBDTWeighted->GetYaxis()->SetTitle("B_{s} y");
	EffBptByInvBDTWeighted->GetYaxis()->SetTitleOffset(1.5);


	EffBptByInvBDTWeighted->GetXaxis()->CenterTitle();
	EffBptByInvBDTWeighted->GetYaxis()->CenterTitle();




	TH2D * EffBptByInvhyperfine = (TH2D *) EffBptByGenhyperfine->Clone("EffBptByInvhyperfine");

	EffBptByInvhyperfine->Sumw2();
	EffBptByMChyperfine->Sumw2();
	EffBptByInvhyperfine->Divide(EffBptByMChyperfine);

	EffBptByInvhyperfine->GetXaxis()->SetTitle("|By| (hyperfine)");
	EffBptByInvhyperfine->GetYaxis()->SetTitle("Bp_{T} (hyperfine)");
	EffBptByInvhyperfine->GetYaxis()->SetTitleOffset(1.5);

	EffBptByInvhyperfine->GetXaxis()->CenterTitle();
	EffBptByInvhyperfine->GetYaxis()->CenterTitle();




	double EffRatioErr;

	TH2D * EffBptByInvErr = (TH2D *) EffBptByInv->Clone("EffBptByInvErr");
	EffBptByInvErr->Reset();
	EffBptByInvErr->GetZaxis()->SetTitle("1/eff Error ");

	for(int k = 0; k < EffBptByInv->GetNbinsX();k++){

		for(int l = 0; l < EffBptByInv->GetNbinsY();l++){

			EffRatioErr = EffBptByInv->GetBinError(k+1,l+1);

			EffBptByInvErr->SetBinContent(k+1,l+1,EffRatioErr);
		}
	}



	TH2D * EffBptByInvErrFrac = (TH2D *) EffBptByInvErr->Clone("EffBptByInvErrFrac");
	EffBptByInvErrFrac->Divide(EffBptByInv);
	EffBptByInvErrFrac->GetZaxis()->SetTitle("1/eff Fractional Error ");






	TCanvas * c2 = new TCanvas("c2","c2",600,600);
	c2->cd();
	EffBptBy->Draw("COLZ");
	c2->SaveAs(Form("ByBpt_%.0f_%.0f.png",centmin,centmax));


	EffBptByInvErrFrac->Draw("COLZ");
	c2->SaveAs(Form("ByBptInvErrFrac_%.0f_%.0f.png",centmin,centmax));


	c2->SetLogz();


	EffBptByInvErr->Draw("COLZ");
	c2->SaveAs(Form("ByBptInvErr_%.0f_%.0f.png",centmin,centmax));






	EffBptByInv->Draw("COLZ");
	c2->SaveAs(Form("ByBptInv_%.0f_%.0f.png",centmin,centmax));






	EffBptByInvhyperfine->Draw("COLZ");
	c2->SaveAs(Form("ByBptInvhyperfine_%.0f_%.0f.png",centmin,centmax));

	TFile * foutFine = new TFile(Form("CheckSystNuno/%s/EffFine_%.0f_%.0f.root",FolderName.Data(),centmin,centmax),"RECREATE");
	foutFine->cd();
	hPtMCFine->Write();
	hPtGenWeightedFine->Write();
	hEffFine->Write();
	hEffAccFine->Write();
	hEffFineInv->Write();
	EffBptByGen->Write();
	EffBptByMC->Write();
	EffBptBy->Write();
	EffBptByInv->Write();
	EffBptByInvErr->Write();
	EffBptByInvErrFrac->Write();
	EffBptByInvhyperfine->Write();
	hBptCent->Write();
	hCentEffInv->Write();
	EffBptByGenZoom->Write();
	EffBptByMCZoom->Write();
	EffZoom->Write();
	EffBptByInvBDTWeighted->Write();
	hEffSelectionFine->Write();
	hEff2DInv2Shots->Write();



	TH2D * CompRatio = (TH2D *) EffBptByInv->Clone("CompRatio");
	CompRatio->Sumw2();
	EffBptByInvBDTWeighted->Sumw2();
	CompRatio->Divide(hEff2DInv2Shots);
	CompRatio->Write();

	hInv2ShotHere->Write();

	TH2D * CompHere2Shots = (TH2D *) hInv2ShotHere->Clone("CompHere2Shots");
	CompHere2Shots->Sumw2();
	EffBptByInv->Sumw2();
	CompHere2Shots->Divide(EffBptByInv);
	CompHere2Shots->Write();
	hPtGen2DFine->Write();

	hPtAccInv2DFine->Write();
	hPtGenAcc2DFine->Write();
	foutFine->Close();


}

int main(int argc, char *argv[])
{
	if(argc == 15)
		MCefficiency(atoi(argv[1]),argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],argv[9],argv[10],argv[11],atoi(argv[12]),atof(argv[13]),atof(argv[14]));
	else
	{
		std::cout << "Wrong number of inputs" << std::endl;
		return 1;
	}
	return 0;
}




