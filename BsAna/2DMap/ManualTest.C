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



void  ManualTest(int CentMin, int CentMax){

	TString infile = "../../../../BsBPInputSamples/BsMC.root";

	TFile * fin = new TFile(infile.Data());

	fin->cd();

	TTree * ntphi = (TTree * ) fin->Get("Bfinder/ntphi");
	TTree * BDT1 = (TTree * ) fin->Get("BDT_pt_5_10");
	TTree * BDT2 = (TTree * ) fin->Get("BDT_pt_10_15");
	TTree * BDT3 = (TTree * ) fin->Get("BDT_pt_15_20");
	TTree * BDT4 = (TTree * ) fin->Get("BDT_pt_20_50");
	TTree * ntHi = (TTree * ) fin->Get("hiEvtAnalyzer/HiTree");
	TTree * ntSkim = (TTree * ) fin->Get("skimanalysis/HltTree");
	TTree * ntHlt = (TTree *) fin->Get("hltanalysis/HltTree");
	TTree * TnPInfo = (TTree * ) fin->Get("TnPInfo");
	TTree * CentWeightTree =	(TTree * ) fin->Get("CentWeightTree");
	TTree * ntGen = (TTree * ) fin->Get("Bfinder/ntGen");


	const int NCand = 13000;


	int run;
	int lumi;
	int evt;
	int hiBin;
	Float_t PVz;
	Int_t pclusterCompatibilityFilter;
	Int_t pprimaryVertexFilter;
	Int_t phfCoincFilter2Th4;



	Int_t   Bsize;
	Float_t Btrk1Pt[NCand];
	Float_t Btrk2Pt[NCand];

	Float_t Btrk1PtErr[NCand];
	Float_t Btrk2PtErr[NCand];


	Float_t Bchi2cl[NCand];
	Float_t BsvpvDistance[NCand];
	Float_t BsvpvDisErr[NCand];
	Float_t Bpt[NCand];
	Float_t Btrk1Eta[NCand];
	Float_t Btrk2Eta[NCand];
	Float_t By[NCand];

	Bool_t Bmu1isTriggered[NCand];
	Bool_t Bmu2isTriggered[NCand];

	Float_t Bmass[NCand];


	Float_t Bmumumass[NCand];
	Float_t Bmu1eta[NCand];
	Float_t Bmu1pt[NCand];
	Float_t Bmu2eta[NCand];
	Float_t Bmu2pt[NCand];

	//	Float_t Bmu1phi[NCand];
	//	Float_t Bmu2phi[NCand];

	Bool_t Bmu1TMOneStationTight[NCand];
	Int_t Bmu1InPixelLayer[NCand];
	Int_t Bmu1InStripLayer[NCand];

	Bool_t Bmu2TMOneStationTight[NCand];	
	Int_t Bmu2InPixelLayer[NCand];
	Int_t Bmu2InStripLayer[NCand];


	Bool_t Bmu1isGlobalMuon[NCand];
	Bool_t Bmu2isGlobalMuon[NCand];


	Bool_t Bmu1isTrackerMuon[NCand];
	Bool_t Bmu2isTrackerMuon[NCand];

	Float_t Bmu1dxyPV[NCand];
	Float_t Bmu2dxyPV[NCand];

	Float_t Bmu1dzPV[NCand];
	Float_t Bmu2dzPV[NCand];

	Bool_t Btrk1highPurity[NCand];
	Bool_t Btrk2highPurity[NCand];

	Float_t Btktkmass[NCand];

	Float_t Btrk1PixelHit[NCand];
	Float_t Btrk2PixelHit[NCand];

	Float_t Btrk1StripHit[NCand];
	Float_t Btrk2StripHit[NCand];

	Float_t Btrk1Chi2ndf[NCand];
	Float_t Btrk2Chi2ndf[NCand];


	Float_t Btrk1nStripLayer[NCand];
	Float_t Btrk2nStripLayer[NCand];

	Float_t Btrk1nPixelLayer[NCand];
	Float_t Btrk2nPixelLayer[NCand];


	Double_t BDT_pt_5_10[NCand];
	Double_t BDT_pt_10_15[NCand];
	Double_t BDT_pt_15_20[NCand];
	Double_t BDT_pt_20_50[NCand];

	Float_t Bgen[NCand];



	Float_t pthatweight;





	ntHi->SetBranchAddress("hiBin",&hiBin);
	ntHi->SetBranchAddress("pthatweight",&pthatweight);
	BDT1->SetBranchAddress("run",&run);
	BDT1->SetBranchAddress("evt",&evt);
	BDT1->SetBranchAddress("lumi",&lumi);




	ntSkim->SetBranchAddress("pclusterCompatibilityFilter",&pclusterCompatibilityFilter);
	ntSkim->SetBranchAddress("pprimaryVertexFilter",&pprimaryVertexFilter);
	ntSkim->SetBranchAddress("phfCoincFilter2Th4",&phfCoincFilter2Th4);


	ntphi->SetBranchAddress("Bsize",&Bsize);
	ntphi->SetBranchAddress("PVz",&PVz);
	ntphi->SetBranchAddress("Btrk1Pt",Btrk1Pt);
	ntphi->SetBranchAddress("Btrk2Pt",Btrk2Pt);
	ntphi->SetBranchAddress("Btrk1PtErr",Btrk1PtErr);
	ntphi->SetBranchAddress("Btrk2PtErr",Btrk2PtErr);
	ntphi->SetBranchAddress("Bchi2cl",Bchi2cl);
	ntphi->SetBranchAddress("BsvpvDistance",BsvpvDistance);
	ntphi->SetBranchAddress("BsvpvDisErr",BsvpvDisErr);
	ntphi->SetBranchAddress("Bpt",Bpt);
	ntphi->SetBranchAddress("By",By);
	ntphi->SetBranchAddress("Btrk1Eta",Btrk1Eta);
	ntphi->SetBranchAddress("Btrk2Eta",Btrk2Eta);
	ntphi->SetBranchAddress("Bmass",Bmass);



	ntphi->SetBranchAddress("Bmu1isTriggered",Bmu1isTriggered);
	ntphi->SetBranchAddress("Bmu2isTriggered",Bmu2isTriggered);


	ntphi->SetBranchAddress("Bmumumass",Bmumumass);
	ntphi->SetBranchAddress("Bmu1eta",Bmu1eta);
	ntphi->SetBranchAddress("Bmu2eta",Bmu2eta);
	ntphi->SetBranchAddress("Bmu1pt",Bmu1pt);
	ntphi->SetBranchAddress("Bmu2pt",Bmu2pt);

	//	ntphi->SetBranchAddress("Bmu1phi",Bmu1phi);
	//	ntphi->SetBranchAddress("Bmu2phi",Bmu2phi);

	ntphi->SetBranchAddress("Bmu1TMOneStationTight",Bmu1TMOneStationTight);
	ntphi->SetBranchAddress("Bmu1InPixelLayer",Bmu1InPixelLayer);
	ntphi->SetBranchAddress("Bmu1InStripLayer",Bmu1InStripLayer);

	ntphi->SetBranchAddress("Bmu2TMOneStationTight",Bmu2TMOneStationTight);
	ntphi->SetBranchAddress("Bmu2InPixelLayer",Bmu2InPixelLayer);
	ntphi->SetBranchAddress("Bmu2InStripLayer",Bmu2InStripLayer);


	ntphi->SetBranchAddress("Bmu1isGlobalMuon",Bmu1isGlobalMuon);
	ntphi->SetBranchAddress("Bmu2isGlobalMuon",Bmu2isGlobalMuon);

	ntphi->SetBranchAddress("Bmu1isTrackerMuon",Bmu1isTrackerMuon);
	ntphi->SetBranchAddress("Bmu2isTrackerMuon",Bmu2isTrackerMuon);


	Int_t HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1;


	ntHlt->SetBranchAddress("HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1",&HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1);



	ntphi->SetBranchAddress("Bmu1dxyPV",Bmu1dxyPV);
	ntphi->SetBranchAddress("Bmu2dxyPV",Bmu2dxyPV);
	ntphi->SetBranchAddress("Bmu1dzPV",Bmu1dzPV);
	ntphi->SetBranchAddress("Bmu2dzPV",Bmu2dzPV);


	ntphi->SetBranchAddress("Btrk1highPurity",Btrk1highPurity);
	ntphi->SetBranchAddress("Btrk2highPurity",Btrk2highPurity);

	ntphi->SetBranchAddress("Btktkmass",Btktkmass);


	ntphi->SetBranchAddress("Btrk1PixelHit",Btrk1PixelHit);
	ntphi->SetBranchAddress("Btrk2PixelHit",Btrk2PixelHit);
	ntphi->SetBranchAddress("Btrk1StripHit",Btrk1StripHit);
	ntphi->SetBranchAddress("Btrk2StripHit",Btrk2StripHit);



	ntphi->SetBranchAddress("Btrk1Chi2ndf",Btrk1Chi2ndf);
	ntphi->SetBranchAddress("Btrk2Chi2ndf",Btrk2Chi2ndf);

	ntphi->SetBranchAddress("Bgen",Bgen);


	ntphi->SetBranchAddress("Btrk1nStripLayer",Btrk1nStripLayer);	
	ntphi->SetBranchAddress("Btrk2nStripLayer",Btrk2nStripLayer);
	ntphi->SetBranchAddress("Btrk1nPixelLayer",Btrk1nPixelLayer);
	ntphi->SetBranchAddress("Btrk2nPixelLayer",Btrk2nPixelLayer);

	BDT1->SetBranchAddress("BDT_pt_5_10",BDT_pt_5_10);
	BDT2->SetBranchAddress("BDT_pt_10_15",BDT_pt_10_15);
	BDT3->SetBranchAddress("BDT_pt_15_20",BDT_pt_15_20);
	BDT4->SetBranchAddress("BDT_pt_20_50",BDT_pt_20_50);


	Int_t Gsize;
	Float_t Gy[NCand];
	Float_t Gpt[NCand];
	Int_t GisSignal[NCand];
	Int_t GcollisionId[NCand];
	Int_t GpdgId[NCand];

	Float_t Gmu1pt[NCand];
	Float_t Gmu1eta[NCand];
	Float_t Gmu1phi[NCand];

	Float_t Gmu2pt[NCand];
	Float_t Gmu2eta[NCand];
	Float_t Gmu2phi[NCand];

	Float_t Gtk1pt[NCand];
	Float_t Gtk1eta[NCand];
	Float_t Gtk1phi[NCand];

	Float_t Gtk2pt[NCand];
	Float_t Gtk2eta[NCand];
	Float_t Gtk2phi[NCand];



	ntGen->SetBranchAddress("Gsize",&Gsize);
	ntGen->SetBranchAddress("Gy",Gy);
	ntGen->SetBranchAddress("Gpt",Gpt);
	ntGen->SetBranchAddress("GisSignal",GisSignal);
	ntGen->SetBranchAddress("GcollisionId",GcollisionId);
	ntGen->SetBranchAddress("GpdgId",GpdgId);
	ntGen->SetBranchAddress("Gmu1pt",Gmu1pt);
	ntGen->SetBranchAddress("Gmu1eta",Gmu1eta);
	ntGen->SetBranchAddress("Gmu1phi",Gmu1phi);
	ntGen->SetBranchAddress("Gmu2pt",Gmu2pt);
	ntGen->SetBranchAddress("Gmu2eta",Gmu2eta);
	ntGen->SetBranchAddress("Gmu2phi",Gmu2phi);


	ntGen->SetBranchAddress("Gtk1pt",Gtk1pt);
	ntGen->SetBranchAddress("Gtk1eta",Gtk1eta);
	ntGen->SetBranchAddress("Gtk1phi",Gtk1phi);
	ntGen->SetBranchAddress("Gtk2pt",Gtk2pt);
	ntGen->SetBranchAddress("Gtk2eta",Gtk2eta);
	ntGen->SetBranchAddress("Gtk2phi",Gtk2phi);





	double CentWeight;

	CentWeightTree->SetBranchAddress("CentWeight",&CentWeight);


	double muid1[NCand];
	double muid2[NCand];
	double trk1[NCand];
	double trk2[NCand];
	double trg1[NCand];
	double trg2[NCand];

	TnPInfo->SetBranchAddress("muid1",muid1);
	TnPInfo->SetBranchAddress("muid2",muid2);
	TnPInfo->SetBranchAddress("trk1",trk1);
	TnPInfo->SetBranchAddress("trk2",trk2);
	TnPInfo->SetBranchAddress("trg1",trg1);
	TnPInfo->SetBranchAddress("trg2",trg2);



	//Syst Purpose//
	double muid1statup[NCand];
	double trk1statup[NCand];
	double trg1statup[NCand];

	double muid1statdown[NCand];
	double trk1statdown[NCand];
	double trg1statdown[NCand];


	double muid1systup[NCand];
	double trk1systup[NCand];
	double trg1systup[NCand];

	double muid1systdown[NCand];
	double trk1systdown[NCand];
	double trg1systdown[NCand];


	double muid2statup[NCand];
	double trk2statup[NCand];
	double trg2statup[NCand];

	double muid2statdown[NCand];
	double trk2statdown[NCand];
	double trg2statdown[NCand];


	double muid2systup[NCand];
	double trk2systup[NCand];
	double trg2systup[NCand];

	double muid2systdown[NCand];
	double trk2systdown[NCand];
	double trg2systdown[NCand];



	double muid1syst;
	double muid1stat;
	double muid2syst;
	double muid2stat;

	double trk1syst;
	double trk1stat;
	double trk2syst;
	double trk2stat;

	double trg1syst;
	double trg1stat;
	double trg2syst;
	double trg2stat;


	double tnptotal1syst;
	double tnptotal1stat;


	double tnptotal2syst;
	double tnptotal2stat;


	double tnptotal1err;
	double tnptotal2err;

	double tnptotalerr;





	TnPInfo->SetBranchAddress("muid1statup",muid1statup);
	TnPInfo->SetBranchAddress("trk1statup",trk1statup);
	TnPInfo->SetBranchAddress("trg1statup",trg1statup);
	TnPInfo->SetBranchAddress("muid1statdown",muid1statdown);
	TnPInfo->SetBranchAddress("trk1statdown",trk1statdown);
	TnPInfo->SetBranchAddress("trg1statdown",trg1statdown);
	TnPInfo->SetBranchAddress("muid1systup",muid1systup);
	TnPInfo->SetBranchAddress("trk1systup",trk1systup);
	TnPInfo->SetBranchAddress("trg1systup",trg1systup);
	TnPInfo->SetBranchAddress("muid1systdown",muid1systdown);
	TnPInfo->SetBranchAddress("trk1systdown",trk1systdown);
	TnPInfo->SetBranchAddress("trg1systdown",trg1systdown);



	TnPInfo->SetBranchAddress("muid2statup",muid2statup);
	TnPInfo->SetBranchAddress("trk2statup",trk2statup);
	TnPInfo->SetBranchAddress("trg2statup",trg2statup);
	TnPInfo->SetBranchAddress("muid2statdown",muid2statdown);
	TnPInfo->SetBranchAddress("trk2statdown",trk2statdown);
	TnPInfo->SetBranchAddress("trg2statdown",trg2statdown);
	TnPInfo->SetBranchAddress("muid2systup",muid2systup);
	TnPInfo->SetBranchAddress("trk2systup",trk2systup);
	TnPInfo->SetBranchAddress("trg2systup",trg2systup);
	TnPInfo->SetBranchAddress("muid2systdown",muid2systdown);
	TnPInfo->SetBranchAddress("trk2systdown",trk2systdown);
	TnPInfo->SetBranchAddress("trg2systdown",trg2systdown);







	int NEvents = ntphi->GetEntries();

	const int yBinN = 5;
	double yBinning[yBinN+1] = {0.0,0.5, 1.0, 1.5,2.0, 2.4};

	double LowBinWidth = 0.5;

	int NLowBin = 5/LowBinWidth;
	//	int NLowBin = 5;

	double MidBinWidth = 1;
	int NMidBin = 10/MidBinWidth;
	double HighBinWidth = 1;
	int NHighBin = 30/HighBinWidth;
	const int BptBin = NHighBin + NMidBin + NLowBin;
	double BptBinning[BptBin + 1];




	for(int i = 0; i < NLowBin; i++){
		BptBinning[i] = 5 + i * LowBinWidth;
	}
	for(int i = 0; i < NMidBin; i++){
		BptBinning[i+NLowBin] = 10 + i * MidBinWidth;
	}
	for(int i = 0; i <  NHighBin+1; i++){
		BptBinning[i+NLowBin+NMidBin] = 20 + i * HighBinWidth;
	}



	double PVzWeight;


	double EventWeight;
	double TnPWeight;
	double muidWeight;
	double trkWeight;
	double TotalWeight;
	double TotalWeightSystUp;
	double TotalWeightSystDown;

	double TotalWeightMuidUp;
	double TotalWeightMuidDown;
	double TotalWeightTrkUp;
	double TotalWeightTrkDown;
	double TotalWeightTrgUp;
	double TotalWeightTrgDown;



	TH2D * NoWeightHis = new TH2D("NoWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * EvtWeightHis = new TH2D("EvtWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * muidWeightHis = new TH2D("muidWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * trkWeightHis = new TH2D("trkWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * muidtrkWeightHis = new TH2D("muidtrkWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHis = new TH2D("TnPWeightHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHisSystUp = new TH2D("TnPWeightHisSystUp","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHisSystDown = new TH2D("TnPWeightHisSystDown","",BptBin,BptBinning,yBinN,yBinning);


	TH2D * TnPWeightHisMuidUp = new TH2D("TnPWeightHisMuidUp","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHisMuidDown = new TH2D("TnPWeightHisMuidDown","",BptBin,BptBinning,yBinN,yBinning);

	TH2D * TnPWeightHisTrkUp = new TH2D("TnPWeightHisTrkUp","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHisTrkDown = new TH2D("TnPWeightHisTrkDown","",BptBin,BptBinning,yBinN,yBinning);


	TH2D * TnPWeightHisTrgUp = new TH2D("TnPWeightHisTrgUp","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * TnPWeightHisTrgDown = new TH2D("TnPWeightHisTrgDown","",BptBin,BptBinning,yBinN,yBinning);


	//Gen//
	TH2D * NoWeightGenHis = new TH2D("NoWeightGenHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * EvtWeightGenHis = new TH2D("EvtWeightGenHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * EvtWeightGenAccHis = new TH2D("EvtWeightGenAccHis","",BptBin,BptBinning,yBinN,yBinning);
	TH2D * NoWeightGenAccHis = new TH2D("NoWeightGenAccHis","",BptBin,BptBinning,yBinN,yBinning);


	TString outfileName = Form("NewEff2DMaps/EffFine_%d_%d.root",CentMin,CentMax);

	TFile * fout = new TFile(outfileName.Data(),"RECREATE");
	fout->cd();

	double muidtrkWeight;


	double muid1total;
	double muid2total;

	double trk1total;
	double trk2total;
	
	double trg1total;
	double trg2total;


	double muidtotalerr;
	double trktotalerr;
	double trgtotalerr;


	for(int i = 0; i < NEvents; i++){


		if(i%10000==0) cout << "Now Working on = " << i  <<  endl;

		ntphi->GetEntry(i);
		ntSkim->GetEntry(i);
		ntHi->GetEntry(i);
		ntHlt->GetEntry(i);
		BDT1->GetEntry(i);
		BDT2->GetEntry(i);
		BDT3->GetEntry(i);
		BDT4->GetEntry(i);
		CentWeightTree->GetEntry(i);
		TnPInfo->GetEntry(i);

		for(int j = 0; j < Bsize; j++){
			//cout << "j = " << j << endl;

			if(((HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1 == 1 && (Bmu1isTriggered[j] == 1 && Bmu2isTriggered[j] == 1)) && (Bgen[j]==23333) &&  (hiBin < 181) && Btrk1Pt[j] > 0.9 && Btrk2Pt[j] > 0.9 && Bchi2cl[j] > 0.05 && BsvpvDistance[j]/BsvpvDisErr[j] > 2.0 && Bpt[j] > 5 && abs(Btrk1Eta[j]-0.0) < 2.4 && abs(Btrk2Eta[j]-0.0) < 2.4 && (TMath::Abs(By[j])<2.4&&TMath::Abs(Bmumumass[j]-3.096916)<0.15&&((abs(Bmu1eta[j])<1.2&&Bmu1pt[j]>3.5)||(abs(Bmu1eta[j])>1.2&&abs(Bmu1eta[j])<2.1&&Bmu1pt[j]>(5.47-1.89*abs(Bmu1eta[j])))||(abs(Bmu1eta[j])>2.1&&abs(Bmu1eta[j])<2.4&&Bmu1pt[j]>1.5))&&((abs(Bmu2eta[j])<1.2&&Bmu2pt[j]>3.5)||(abs(Bmu2eta[j])>1.2&&abs(Bmu2eta[j])<2.1&&Bmu2pt[j]>(5.47-1.89*abs(Bmu2eta[j])))||(abs(Bmu2eta[j])>2.1&&abs(Bmu2eta[j])<2.4&&Bmu2pt[j]>1.5))&&Bmu1TMOneStationTight[j]&&Bmu2TMOneStationTight[j]&&Bmu1InPixelLayer[j]>0&&(Bmu1InPixelLayer[j]+Bmu1InStripLayer[j])>5&&Bmu2InPixelLayer[j]>0&&(Bmu2InPixelLayer[j]+Bmu2InStripLayer[j])>5&&Bmu1dxyPV[j]<0.3&&Bmu2dxyPV[j]<0.3&&Bmu1dzPV[j]<20&&Bmu2dzPV[j]<20&&Bmu1isTrackerMuon[j]&&Bmu2isTrackerMuon[j]&&Bmu1isGlobalMuon[j]&&Bmu2isGlobalMuon[j]&&Btrk1highPurity[j]&&Btrk2highPurity[j]&&abs(Btrk1Eta[j])<2.4&&abs(Btrk2Eta[j])<2.4&&Btrk1Pt[j]>1.&&Btrk2Pt[j]>1.&&abs(Btktkmass[j]-1.019455)<0.015) && (abs(PVz)<15&&pclusterCompatibilityFilter == 1 &&pprimaryVertexFilter == 1) && (Btrk1PixelHit[j] + Btrk1StripHit[j] > 10) && (Btrk2PixelHit[j] + Btrk2StripHit[j] > 10) && (Btrk1PtErr[j]/Btrk1Pt[j] < 0.1)&& (Btrk2PtErr[j]/Btrk2Pt[j] < 0.1) && Btrk1Chi2ndf[j]/(Btrk1nStripLayer[j]+Btrk1nPixelLayer[j]) < 0.18 && Btrk2Chi2ndf[j]/(Btrk2nStripLayer[j]+Btrk2nPixelLayer[j]) < 0.18&&((Bpt[j]>5&&Bpt[j]<10&&BDT_pt_5_10[j]>0.32 )||(Bpt[j]>10&&Bpt[j]<15&&BDT_pt_10_15[j]> 0.29)||(Bpt[j]>15&&Bpt[j]<20&&BDT_pt_15_20[j]>0.35)||(Bpt[j]>20&&Bpt[j]<50&&BDT_pt_20_50[j]>0.33))&&abs(PVz)<15&&pclusterCompatibilityFilter == 1 &&pprimaryVertexFilter == 1 && phfCoincFilter2Th4 == 1) && (Bmass[j] > 5 &&Bmass[j] < 6 && hiBin >= CentMin * 2&& hiBin <= CentMax * 2 ) ){

				//cout << "j = " << j << endl;

				PVzWeight = (0.163562 * TMath::Exp(- 0.021039 * (PVz - 0.426587)*(PVz - 0.426587)))/(0.159629 * TMath::Exp(- 0.020014 * (PVz - 0.589381)*(PVz - 0.589381)));


				EventWeight = PVzWeight * CentWeight * pthatweight;


				TnPWeight = muid1[j] * trk1[j] * trg1[j] * muid2[j] * trk2[j] * trg2[j];

				muidWeight = EventWeight * muid1[j] * muid2[j];
				trkWeight = EventWeight * trk1[j] * trk2[j];

				muidtrkWeight = EventWeight * muidWeight * trkWeight;
				TotalWeight = EventWeight * TnPWeight;



				NoWeightHis->Fill(Bpt[j],abs(By[j]),1);
				EvtWeightHis->Fill(Bpt[j],abs(By[j]),EventWeight);
				muidWeightHis->Fill(Bpt[j],abs(By[j]),muidWeight);
				trkWeightHis->Fill(Bpt[j],abs(By[j]),trkWeight);
				muidtrkWeightHis->Fill(Bpt[j],abs(By[j]),muidtrkWeight);
				TnPWeightHis->Fill(Bpt[j],abs(By[j]),TotalWeight);



				//Now Everything is About the Error//
				if(muid1systup[j] >= muid1systdown[j]) muid1syst = muid1systup[j];
				if(muid1systdown[j] > muid1systup[j]) muid1syst = muid1systdown[j];
				if(muid2systup[j] >= muid2systdown[j]) muid2syst = muid2systup[j];
				if(muid2systdown[j] > muid2systup[j]) muid2syst = muid2systdown[j];

				if(muid1statup[j] >= muid1statdown[j]) muid1stat = muid1statup[j];
				if(muid1statdown[j] > muid1statup[j]) muid1stat = muid1statdown[j];
				if(muid2statup[j] >= muid2statdown[j]) muid2stat = muid2statup[j];
				if(muid2statdown[j] > muid2statup[j]) muid2stat = muid2statdown[j];

				//Trk
				if(trk1systup[j] >= trk1systdown[j]) trk1syst = trk1systup[j];
				if(trk1systdown[j] > trk1systup[j]) trk1syst = trk1systdown[j];
				if(trk2systup[j] >= trk2systdown[j]) trk2syst = trk2systup[j];
				if(trk2systdown[j] > trk2systup[j]) trk2syst = trk2systdown[j];

				if(trk1statup[j] >= trk1statdown[j]) trk1stat = trk1statup[j];
				if(trk1statdown[j] > trk1statup[j]) trk1stat = trk1statdown[j];
				if(trk2statup[j] >= trk2statdown[j]) trk2stat = trk2statup[j];
				if(trk2statdown[j] > trk2statup[j]) trk2stat = trk2statdown[j];



				//Trg
				if(trg1systup[j] >= trg1systdown[j]) trg1syst = trg1systup[j];
				if(trg1systdown[j] > trg1systup[j]) trg1syst = trg1systdown[j];
				if(trg2systup[j] >= trg2systdown[j]) trg2syst = trg2systup[j];
				if(trg2systdown[j] > trg2systup[j]) trg2syst = trg2systdown[j];

				if(trg1statup[j] >= trg1statdown[j]) trg1stat = trg1statup[j];
				if(trg1statdown[j] > trg1statup[j]) trg1stat = trg1statdown[j];
				if(trg2statup[j] >= trg2statdown[j]) trg2stat = trg2statup[j];
				if(trg2statdown[j] > trg2statup[j]) trg2stat = trg2statdown[j];

			
				tnptotal1syst = sqrt(muid1syst/muid1[j] * muid1syst/muid1[j] + trk1syst/trk1[j] * trk1syst/trk1[j] + trg1syst/trg1[j] * trg1syst/trg1[j]);
				tnptotal1stat = sqrt(muid1stat/muid1[j] * muid1stat/muid1[j] + trk1stat/trk1[j] * trk1stat/trk1[j] + trg1stat/trg1[j] * trg1stat/trg1[j]);
				
				
				tnptotal2syst = sqrt(muid2syst/muid2[j] * muid2syst/muid2[j] + trk2syst/trk2[j] * trk2syst/trk2[j] + trg2syst/trg2[j] * trg2syst/trg2[j]);
				tnptotal2stat = sqrt(muid2stat/muid2[j] * muid2stat/muid2[j] + trk2stat/trk2[j] * trk2stat/trk2[j] + trg2stat/trg2[j] * trg2stat/trg2[j]);
	

				tnptotal1err = sqrt(tnptotal1stat * tnptotal1stat + tnptotal1syst * tnptotal1syst);
				tnptotal2err = sqrt(tnptotal2stat * tnptotal2stat + tnptotal2syst * tnptotal2syst);	

				tnptotalerr = sqrt(tnptotal1err * tnptotal1err + tnptotal2err * tnptotal2err);

			//	cout << "tnptotalerr = " << tnptotalerr << endl;

				TotalWeightSystUp = TotalWeight * ( 1 + tnptotalerr);
				TotalWeightSystDown = TotalWeight * ( 1 - tnptotalerr);
	
				
				TnPWeightHisSystUp->Fill(Bpt[j],abs(By[j]),TotalWeightSystUp);
				TnPWeightHisSystDown->Fill(Bpt[j],abs(By[j]),TotalWeightSystDown);


				muid1total =  sqrt(muid1syst/muid1[j] * muid1syst/muid1[j] + muid1stat/muid1[j] * muid1stat/muid1[j]);
				muid2total =  sqrt(muid2syst/muid2[j] * muid2syst/muid2[j] + muid2stat/muid2[j] * muid2stat/muid2[j]);

				trk1total =  sqrt(trk1syst/trk1[j] * trk1syst/trk1[j] + trk1stat/trk1[j] * trk1stat/trk1[j]);
				trk2total =	 sqrt(trk2syst/trk2[j] * trk2syst/trk2[j] + trk2stat/trk2[j] * trk2stat/trk2[j]);

				trg1total =  sqrt(trg1syst/trg1[j] * trg1syst/trg1[j] + trg1stat/trg1[j] * trg1stat/trg1[j]);
				trg2total =	sqrt(trg2syst/trg2[j] * trg2syst/trg2[j] + trg2stat/trg2[j] * trg2stat/trg2[j]);
	
	
				muidtotalerr = sqrt(muid1total * muid1total + muid2total * muid2total);
				trktotalerr = sqrt(trk1total * trk1total + trk2total * trk2total);
				trgtotalerr = sqrt(trg1total * trg1total + trg2total * trg2total);
				
		//		cout << "muid1total = " << muid1total << "    muid2total = " <<muid2total << "  muidtotalerr = " << muidtotalerr  << endl;

				
				TotalWeightMuidUp = TotalWeight * ( 1 + muidtotalerr);
				TotalWeightMuidDown = TotalWeight * ( 1 - muidtotalerr);

				TotalWeightTrkUp = TotalWeight * ( 1 + trktotalerr);
				TotalWeightTrkDown = TotalWeight * ( 1 - trktotalerr);

				TotalWeightTrgUp = TotalWeight * ( 1 + trgtotalerr);
				TotalWeightTrgDown = TotalWeight * ( 1 - trgtotalerr);


				TnPWeightHisMuidUp->Fill(Bpt[j],abs(By[j]),TotalWeightMuidUp);
				TnPWeightHisMuidDown->Fill(Bpt[j],abs(By[j]),TotalWeightMuidDown);

				//cout << "TotalWeightMuidUp = " << TotalWeightMuidUp  << "   TotalWeightMuidDown = " << TotalWeightMuidDown << endl;
			

				TnPWeightHisTrkUp->Fill(Bpt[j],abs(By[j]),TotalWeightTrkUp);
				TnPWeightHisTrkDown->Fill(Bpt[j],abs(By[j]),TotalWeightTrkDown);



				TnPWeightHisTrgUp->Fill(Bpt[j],abs(By[j]),TotalWeightTrgUp);
				TnPWeightHisTrgDown->Fill(Bpt[j],abs(By[j]),TotalWeightTrgDown);



			}





		}



	}

	cout << "Now Loop Gen" << endl;



	for(int i = 0; i < NEvents; i++){


		ntGen->GetEntry(i);
		ntHi->GetEntry(i);
		CentWeightTree->GetEntry(i);
		ntphi->GetEntry(i);


		PVzWeight = (0.163562 * TMath::Exp(- 0.021039 * (PVz - 0.426587)*(PVz - 0.426587)))/(0.159629 * TMath::Exp(- 0.020014 * (PVz - 0.589381)*(PVz - 0.589381)));
		EventWeight = PVzWeight * CentWeight * pthatweight;


		for(int j = 0; j < Gsize; j++){





			if(hiBin >= CentMin * 2 && hiBin <= CentMax * 2 && TMath::Abs(Gy[j])<2.4&&TMath::Abs(GpdgId[j])==531&&GisSignal[j]>0 &&((Gpt[j] > 5 && Gpt[j] < 10 && TMath::Abs(Gy[j])>1.5)||(Gpt[j] > 10 && Gpt[j] < 50 && TMath::Abs(Gy[j])>0))){


				NoWeightGenHis->Fill(Gpt[j],abs(Gy[j]),1);
				EvtWeightGenHis->Fill(Gpt[j],abs(Gy[j]),EventWeight);
			}

			if(hiBin >= CentMin * 2 && hiBin <= CentMax * 2 && TMath::Abs(Gy[j])<2.4&&abs(GpdgId[j])==531&&GisSignal[j]>0&&((Gpt[j] > 5 && Gpt[j] < 10 && TMath::Abs(Gy[j])>1.5)||(Gpt[j] > 10 && Gpt[j] < 50 && TMath::Abs(Gy[j])>0))&&((TMath::Abs(Gmu1eta[j])<1.2&&Gmu1pt[j]>3.5)||(TMath::Abs(Gmu1eta[j])>1.2&&TMath::Abs(Gmu1eta[j])<2.1&&Gmu1pt[j]>(5.47-1.89*TMath::Abs(Gmu1eta[j])))||(TMath::Abs(Gmu1eta[j])>2.1&&TMath::Abs(Gmu1eta[j])<2.4&&Gmu1pt[j]>1.5))&&((TMath::Abs(Gmu2eta[j])<1.2&&Gmu2pt[j]>3.5)||(TMath::Abs(Gmu2eta[j])>1.2&&TMath::Abs(Gmu2eta[j])<2.1&&Gmu2pt[j]>(5.47-1.89*TMath::Abs(Gmu2eta[j])))||(TMath::Abs(Gmu2eta[j])>2.1&&TMath::Abs(Gmu2eta[j])<2.4&&Gmu2pt[j]>1.5))&&Gtk1pt[j]>0.9&&Gtk2pt[j]>0.9&&TMath::Abs(Gtk1eta[j])<2.4&&TMath::Abs(Gtk2eta[j])<2.4){

				NoWeightGenAccHis->Fill(Gpt[j],abs(Gy[j]),EventWeight);
				EvtWeightGenAccHis->Fill(Gpt[j],abs(Gy[j]),EventWeight);

			}

		}

	}


	TH1D * hEffSelectionFine = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFine");
	hEffSelectionFine->Sumw2();
	hEffSelectionFine->Divide(hEffSelectionFine,TnPWeightHis,1,1,"b");



	TString FileNameAcc ="AccNew.root";
	TFile * finAcc = new TFile(FileNameAcc.Data());
	finAcc->cd();
	TH2D * hEffAcc2DFine = (TH2D * ) finAcc->Get("hEffAcc2DFine");


	TH2D* hEff2DInv2Shots = (TH2D*)hEffSelectionFine->Clone("hEff2DInv2Shots");
	hEff2DInv2Shots->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2Shots->Multiply(hEffAcc2DFine);


	//For TnP Syst
	TH1D * hEffSelectionFineSystUp = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineSystUp");
	hEffSelectionFineSystUp->Sumw2();
	hEffSelectionFineSystUp->Divide(hEffSelectionFineSystUp,TnPWeightHisSystDown,1,1,"b");

	TH1D * hEffSelectionFineSystDown = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineSystDown");
	hEffSelectionFineSystDown->Sumw2();
	hEffSelectionFineSystDown->Divide(hEffSelectionFineSystDown,TnPWeightHisSystUp,1,1,"b");


	TH1D * hEffSelectionFineMuidUp = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineMuidUp");
	hEffSelectionFineMuidUp->Sumw2();
	hEffSelectionFineMuidUp->Divide(hEffSelectionFineMuidUp,TnPWeightHisMuidDown,1,1,"b");

	TH1D * hEffSelectionFineMuidDown = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineMuidDown");
	hEffSelectionFineMuidDown->Sumw2();
	hEffSelectionFineMuidDown->Divide(hEffSelectionFineMuidDown,TnPWeightHisMuidUp,1,1,"b");


	TH1D * hEffSelectionFineTrkUp = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineTrkUp");
	hEffSelectionFineTrkUp->Sumw2();
	hEffSelectionFineTrkUp->Divide(hEffSelectionFineTrkUp,TnPWeightHisTrkDown,1,1,"b");

	TH1D * hEffSelectionFineTrkDown = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineTrkDown");
	hEffSelectionFineTrkDown->Sumw2();
	hEffSelectionFineTrkDown->Divide(hEffSelectionFineTrkDown,TnPWeightHisTrkUp,1,1,"b");

	TH1D * hEffSelectionFineTrgUp = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineTrgUp");
	hEffSelectionFineTrgUp->Sumw2();
	hEffSelectionFineTrgUp->Divide(hEffSelectionFineTrgUp,TnPWeightHisTrgDown,1,1,"b");

	TH1D * hEffSelectionFineTrgDown = (TH1D *) EvtWeightGenAccHis->Clone("hEffSelectionFineTrgDown");
	hEffSelectionFineTrgDown->Sumw2();
	hEffSelectionFineTrgDown->Divide(hEffSelectionFineTrgDown,TnPWeightHisTrgUp,1,1,"b");



	//For Tnp Syst

	TH2D* hEff2DInv2ShotsSystUp = (TH2D* ) hEffSelectionFineSystUp->Clone("hEff2DInv2ShotsSystUp");
	hEff2DInv2ShotsSystUp->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsSystUp->Multiply(hEffAcc2DFine);

	TH2D* hEff2DInv2ShotsSystDown = (TH2D* ) hEffSelectionFineSystDown->Clone("hEff2DInv2ShotsSystDown");
	hEff2DInv2ShotsSystDown->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsSystDown->Multiply(hEffAcc2DFine);


	TH2D* hEff2DInv2ShotsMuidUp = (TH2D* ) hEffSelectionFineMuidUp->Clone("hEff2DInv2ShotsMuidUp");
	hEff2DInv2ShotsMuidUp->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsMuidUp->Multiply(hEffAcc2DFine);

	TH2D* hEff2DInv2ShotsMuidDown = (TH2D* ) hEffSelectionFineMuidDown->Clone("hEff2DInv2ShotsMuidDown");
	hEff2DInv2ShotsMuidDown->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsMuidDown->Multiply(hEffAcc2DFine);


	TH2D* hEff2DInv2ShotsTrkUp = (TH2D* ) hEffSelectionFineTrkUp->Clone("hEff2DInv2ShotsTrkUp");
	hEff2DInv2ShotsTrkUp->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsTrkUp->Multiply(hEffAcc2DFine);

	TH2D* hEff2DInv2ShotsTrkDown = (TH2D* ) hEffSelectionFineTrkDown->Clone("hEff2DInv2ShotsTrkDown");
	hEff2DInv2ShotsTrkDown->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsTrkDown->Multiply(hEffAcc2DFine);

	TH2D* hEff2DInv2ShotsTrgUp = (TH2D* ) hEffSelectionFineTrgUp->Clone("hEff2DInv2ShotsTrgUp");
	hEff2DInv2ShotsTrgUp->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsTrgUp->Multiply(hEffAcc2DFine);

	TH2D* hEff2DInv2ShotsTrgDown = (TH2D* ) hEffSelectionFineTrgDown->Clone("hEff2DInv2ShotsTrgDown");
	hEff2DInv2ShotsTrgDown->Sumw2();
	hEffAcc2DFine->Sumw2();
	hEff2DInv2ShotsTrgDown->Multiply(hEffAcc2DFine);



	double RECOErr;
	double GENErr;

	double AccErr;

	double EffMCStatErr;
	double EffMCStatAbsErr;

	double EffTnPErr;



	TH1D * hEffSelectionFineStatErr = (TH1D *) hEffSelectionFine->Clone("hEffSelectionFineStatErr");
	TH2D * hEff2DInv2ShotsStatErr = (TH2D *) hEff2DInv2Shots->Clone("hEff2DInv2ShotsStatErr");


	for(int i = 0; i < hEffSelectionFineStatErr->GetNbinsX(); i ++){

		for(int j = 0; j < hEffSelectionFineStatErr->GetNbinsY(); j++){


			RECOErr = 1/sqrt(NoWeightHis->GetBinContent(i+1,j+1));  //RECO
			GENErr = 1/sqrt(NoWeightGenHis->GetBinContent(i+1,j+1));
			EffMCStatErr = sqrt(RECOErr * RECOErr + GENErr * GENErr);
		//	if(NoWeightHis->GetBinContent(i+1,j+1) > 0) 	cout << "i = "  << i << "   j = " << j << "   NRECO  = " <<  NoWeightHis->GetBinContent(i+1,j+1) << "   NGen = " << NoWeightGenHis->GetBinContent(i+1,j+1) << "  EffMCStatErr = " << EffMCStatErr << endl;
			
			EffMCStatAbsErr = hEffSelectionFineStatErr->GetBinContent(i+1,j+1)  * EffMCStatErr;
			hEffSelectionFineStatErr->SetBinError(i+1,j+1,EffMCStatAbsErr);

		}

	}


	for(int i = 0; i < hEff2DInv2ShotsStatErr->GetNbinsX(); i ++){

		for(int j = 0; j < hEff2DInv2ShotsStatErr->GetNbinsY(); j++){


			RECOErr = 1/sqrt(NoWeightHis->GetBinContent(i+1,j+1));  //RECO
			GENErr = 1/sqrt(NoWeightGenHis->GetBinContent(i+1,j+1));
			AccErr = hEffAcc2DFine->GetBinError(i+1,j+1)/hEffAcc2DFine->GetBinContent(i+1,j+1);
			EffMCStatErr = sqrt(RECOErr * RECOErr + GENErr * GENErr + AccErr * AccErr);
			EffMCStatAbsErr = hEff2DInv2ShotsStatErr->GetBinContent(i+1,j+1)  * EffMCStatErr;
			hEff2DInv2ShotsStatErr->SetBinError(i+1,j+1,EffMCStatAbsErr);

		}

	}


	fout->cd();

	NoWeightHis->Write();
	EvtWeightHis->Write();
	muidWeightHis->Write();
	trkWeightHis->Write();
	muidtrkWeightHis->Write();
	TnPWeightHis->Write();	

	NoWeightGenHis->Write();
	EvtWeightGenHis->Write();


	NoWeightGenAccHis->Write();
	EvtWeightGenAccHis->Write();


	hEffAcc2DFine->Write();
	hEffSelectionFine->Write();
	hEff2DInv2Shots->Write();

	hEffSelectionFineStatErr->Write();
	hEff2DInv2ShotsStatErr->Write();


	hEffSelectionFineSystUp->Write();
	hEffSelectionFineSystDown->Write();
	hEff2DInv2ShotsSystUp->Write();
	hEff2DInv2ShotsSystDown->Write();




	hEffSelectionFineSystUp->Write();
	hEffSelectionFineSystDown->Write();
	hEff2DInv2ShotsSystUp->Write();
	hEff2DInv2ShotsSystDown->Write();





	hEffSelectionFineMuidUp->Write();
	hEffSelectionFineMuidDown->Write();
	hEff2DInv2ShotsMuidUp->Write();
	hEff2DInv2ShotsMuidDown->Write();


	hEffSelectionFineTrkUp->Write();
	hEffSelectionFineTrkDown->Write();
	hEff2DInv2ShotsTrkUp->Write();
	hEff2DInv2ShotsTrkDown->Write();


	hEffSelectionFineTrgUp->Write();
	hEffSelectionFineTrgDown->Write();
	hEff2DInv2ShotsTrgUp->Write();
	hEff2DInv2ShotsTrgDown->Write();


	fout->Close();
	fin->Close();


}
