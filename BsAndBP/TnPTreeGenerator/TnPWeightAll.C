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
#include "tnp_weight_lowptPbPb.h"

using namespace std;

using std::cout;
using std::endl;


void TnPWeightAll(int Opt, int DoWeight){


	const int NCand = 13000;

	TString infile;
	TString TreeName;
	TString outfile;




	if(Opt == 0){

		infile = "../../../../BsBPInputSamples/BsMC.root";
		TreeName = "Bfinder/ntphi";
		//	outfile = "BsTnPInfo.root";
		if(DoWeight == 0) outfile = "BsTnP/BsTnPNoInfo.root";
		if(DoWeight == 1) outfile = "BsTnP/BsTnPmuidInfo.root";
		if(DoWeight == 2) outfile = "BsTnP/BsTnPtrkInfo.root";
		if(DoWeight == 3) outfile = "BsTnP/BsTnPmuidtrkInfo.root";
		if(DoWeight == 4) outfile = "BsTnP/BsTnPTotalInfo.root";

	}

	if(Opt == 1){

		infile = "../../../../BsBPInputSamples/BPMC.root";
		TreeName = "Bfinder/ntKp";
		if(DoWeight == 0) outfile = "BPTnP/BPTnPNoInfo.root";
		if(DoWeight == 1) outfile = "BPTnP/BPTnPmuidInfo.root";
		if(DoWeight == 2) outfile = "BPTnP/BPTnPtrkInfo.root";
		if(DoWeight == 3) outfile = "BPTnP/BPTnPmuidtrkInfo.root";
		if(DoWeight == 4) outfile = "BPTnP/BPTnPTotalInfo.root";

	}



	float Bmu1pt[NCand];
	float Bmu2pt[NCand];

	float Bmu1eta[NCand];
	float Bmu2eta[NCand];

	int Bsize;



	TFile * fin = new TFile(infile.Data());
	fin->cd();

	cout << "Pass 1" << endl;


	cout << "TreeName = " << TreeName.Data() << endl;

	TFile * fout = new TFile(outfile.Data(),"RECREATE");
	fout->cd();
	TTree * t = (TTree * ) fin->Get(TreeName.Data());

	cout << "Pass 1.5" << endl;


	t->SetBranchAddress("Bsize",&Bsize);
	t->SetBranchAddress("Bmu1pt",Bmu1pt);
	t->SetBranchAddress("Bmu2pt",Bmu2pt);
	t->SetBranchAddress("Bmu1eta",Bmu1eta);
	t->SetBranchAddress("Bmu2eta",Bmu2eta);


	int BsizeMatched;
	int Bmu1Type[NCand];
	int Bmu2Type[NCand];


	TTree * MuonInfoTree = (TTree *) fin->Get("MuonInfoTree");

	cout << "Pass 1.7" << endl;

	MuonInfoTree->SetBranchAddress("BsizeMatched",&BsizeMatched);
	cout << "Pass 1.8" << endl;


	MuonInfoTree->SetBranchAddress("Bmu1Type",Bmu1Type);
	MuonInfoTree->SetBranchAddress("Bmu2Type",Bmu2Type);

	cout << "Pass 2" << endl;


	int BsizeTnP;

	double muid1[NCand];
	double trk1[NCand];
	double trg1[NCand];

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

	cout << "Pass 3" << endl;



	double muid2[NCand];
	double trk2[NCand];
	double trg2[NCand];

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



	TTree * TnPInfo = new TTree("TnPInfo","TnPInfo");
	TnPInfo->Branch("BsizeTnP",&BsizeTnP,"BsizeTnP/I");
	TnPInfo->Branch("muid1",muid1,"muid1[BsizeTnP]/D");
	TnPInfo->Branch("trk1",trk1,"trk1[BsizeTnP]/D");
	TnPInfo->Branch("trg1",trg1,"trg1[BsizeTnP]/D");

	TnPInfo->Branch("muid2",muid2,"muid2[BsizeTnP]/D");
	TnPInfo->Branch("trk2",trk2,"trk2[BsizeTnP]/D");
	TnPInfo->Branch("trg2",trg2,"trg2[BsizeTnP]/D");


	TnPInfo->Branch("muid1statup",muid1statup,"muid1statup[BsizeTnP]/D");
	TnPInfo->Branch("trk1statup",trk1statup,"trk1statup[BsizeTnP]/D");
	TnPInfo->Branch("trg1statup",trg1statup,"trg1statup[BsizeTnP]/D");

	TnPInfo->Branch("muid2statup",muid2statup,"muid2statup[BsizeTnP]/D");
	TnPInfo->Branch("trk2statup",trk2statup,"trk2statup[BsizeTnP]/D");
	TnPInfo->Branch("trg2statup",trg2statup,"trg2statup[BsizeTnP]/D");


	TnPInfo->Branch("muid1systup",muid1systup,"muid1systup[BsizeTnP]/D");
	TnPInfo->Branch("trk1systup",trk1systup,"trk1systup[BsizeTnP]/D");
	TnPInfo->Branch("trg1systup",trg1systup,"trg1systup[BsizeTnP]/D");


	TnPInfo->Branch("muid2systup",muid2systup,"muid2systup[BsizeTnP]/D");
	TnPInfo->Branch("trk2systup",trk2systup,"trk2systup[BsizeTnP]/D");
	TnPInfo->Branch("trg2systup",trg2systup,"trg2systup[BsizeTnP]/D");



	TnPInfo->Branch("muid1statdown",muid1statdown,"muid1statdown[BsizeTnP]/D");
	TnPInfo->Branch("trk1statdown",trk1statdown,"trk1statdown[BsizeTnP]/D");
	TnPInfo->Branch("trg1statdown",trg1statdown,"trg1statdown[BsizeTnP]/D");

	TnPInfo->Branch("muid2statdown",muid2statdown,"muid2statdown[BsizeTnP]/D");
	TnPInfo->Branch("trk2statdown",trk2statdown,"trk2statdown[BsizeTnP]/D");
	TnPInfo->Branch("trg2statdown",trg2statdown,"trg2statdown[BsizeTnP]/D");


	TnPInfo->Branch("muid1systdown",muid1systdown,"muid1systdown[BsizeTnP]/D");
	TnPInfo->Branch("trk1systdown",trk1systdown,"trk1systdown[BsizeTnP]/D");
	TnPInfo->Branch("trg1systdown",trg1systdown,"trg1systdown[BsizeTnP]/D");


	TnPInfo->Branch("muid2systdown",muid2systdown,"muid2systdown[BsizeTnP]/D");
	TnPInfo->Branch("trk2systdown",trk2systdown,"trk2systdown[BsizeTnP]/D");
	TnPInfo->Branch("trg2systdown",trg2systdown,"trg2systdown[BsizeTnP]/D");




	cout << "Pass 4" << endl;


	int NEvent = t->GetEntries();

	for(int i = 0; i < NEvent; i++){

		if(i%100000 == 0) cout << "Event = " << i << endl;

		t->GetEntry(i);

		BsizeTnP = Bsize;

		for(int j = 0; j < Bsize; j++){




			if(DoWeight == 4){

				muid1[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 0);
				muid2[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 0);

				trk1[j] = tnp_weight_trk_pbpb(Bmu1eta[j], 0);
				trk2[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 0);


	
				muid1systup[j] = abs(tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -1) -  muid1[j]);
				muid1systdown[j] = abs(tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -2) - muid1[j]);
				muid1statup[j] = abs(tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 1)  - muid1[j] ) ;
				muid1statdown[j] = abs(tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 2) - muid1[j] );


				muid2systup[j] = abs(tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -1) - muid2[j] );
				muid2systdown[j] = abs(tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -2) - muid2[j]);
				muid2statup[j] = abs(tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 1) - muid2[j]);
				muid2statdown[j] = abs(tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 2) - muid2[j]);



				trk1systup[j] = abs( tnp_weight_trk_pbpb(Bmu1eta[j], -1) - trk1[j]  ) ;
				trk1systdown[j] = abs(tnp_weight_trk_pbpb( Bmu1eta[j], -2) - trk1[j] );
				trk1statup[j] = abs(tnp_weight_trk_pbpb( Bmu1eta[j], 1) - trk1[j] );
				trk1statdown[j] = abs(tnp_weight_trk_pbpb( Bmu1eta[j], 2) - trk1[j] );


				trk2systup[j] = abs( tnp_weight_trk_pbpb(Bmu2eta[j], -1) - trk2[j]  );
				trk2systdown[j] = abs( tnp_weight_trk_pbpb(Bmu2eta[j], -2) - trk2[j] );
				trk2statup[j] = abs( tnp_weight_trk_pbpb(Bmu2eta[j], 1) - trk2[j]  ) ;
				trk2statdown[j] = abs(tnp_weight_trk_pbpb(Bmu2eta[j], 2) - trk2[j] ) ;



				if(Bmu1Type[j] == 1 && Bmu2Type[j] == 1){

					trg1[j] = 0.5 * ( tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 0, 0));
					trg2[j] =  0.5 * ( tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 1, 0) +  tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 0, 0));

					trg1systup[j] = abs( 0.5 * (tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 1, -1) + tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 0, -1)) - trg1[j] );
					trg1systdown[j] = abs( 0.5 * (tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 1, -2) + tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 0, -2) ) - trg1[j] );
					trg1statup[j] = abs( 0.5 * ( tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 1, 1)  + tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 0, 1) ) - trg1[j]  ); 
					trg1statdown[j] = abs( 0.5 * ( tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 1, 2) + tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], 0, 2)  ) - trg1[j]  ) ;


					trg2systup[j] = abs( 0.5 * (tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 1, -1) + tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 0, -1)) - trg2[j]  );
					trg2systdown[j] = abs(0.5 * (tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 1, -2) + tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 0, -2) ) - trg2[j]);
					trg2statup[j] = abs(0.5 * ( tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 1, 1)  + tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 0, 1) ) - trg2[j] );
					trg2statdown[j] = abs(0.5 * ( tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 1, 2) + tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], 0, 2)  )  - trg2[j] );

				}
				else{



					trg1[j] = tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j], Bmu1Type[j], 0);
					trg2[j] = tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], Bmu2Type[j], 0);

					trg1systup[j] = abs( tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j],  Bmu1Type[j], -1) - trg1[j] );
					trg1systdown[j] = abs(tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j],  Bmu1Type[j], -2) - trg1[j]);
					trg1statup[j] = abs(tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j],  Bmu1Type[j], 1) - trg1[j] );
					trg1statdown[j] = abs(tnp_weight_trg_pbpb(Bmu1pt[j], Bmu1eta[j],  Bmu1Type[j], 2) - trg1[j] );


					trg2systup[j] = abs(tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j],  Bmu2Type[j], -1) - trg2[j] );
					trg2systdown[j] = abs(tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j],  Bmu2Type[j], -2) - trg2[j] ); 
					trg2statup[j] = abs(tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j],  Bmu2Type[j], 1) - trg2[j]);
					trg2statdown[j] = abs(tnp_weight_trg_pbpb(Bmu2pt[j], Bmu2eta[j], Bmu2Type[j], 2) - trg2[j]);


				}


			}



			if(DoWeight == 3){

				muid1[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 0);
				muid2[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 0);

				trk1[j] = tnp_weight_trk_pbpb(Bmu1eta[j], 0);
				trk2[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 0);

				trg1[j] = 1;
				trg2[j] = 1;

				muid1systup[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -1);
				muid1systdown[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -2);
				muid1statup[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 1);
				muid1statdown[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 2);


				muid2systup[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -1);
				muid2systdown[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -2);
				muid2statup[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 1);
				muid2statdown[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 2);


				trk1systup[j] = tnp_weight_trk_pbpb(Bmu1eta[j], -1);
				trk1systdown[j] = tnp_weight_trk_pbpb( Bmu1eta[j], -2);
				trk1statup[j] = tnp_weight_trk_pbpb( Bmu1eta[j], 1);
				trk1statdown[j] = tnp_weight_trk_pbpb( Bmu1eta[j], 2);


				trk2systup[j] = tnp_weight_trk_pbpb(Bmu2eta[j], -1);
				trk2systdown[j] = tnp_weight_trk_pbpb(Bmu2eta[j], -2);
				trk2statup[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 1);
				trk2statdown[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 2);




				trg1systup[j] = 1;
				trg1systdown[j] = 1;
				trg1statup[j] = 1;
				trg1statdown[j] = 1;


				trg2systup[j] = 1;
				trg2systdown[j] = 1;
				trg2statup[j] = 1;
				trg2statdown[j] = 1;

			}

			if(DoWeight == 2){

				muid1[j] = 1;
				muid2[j] = 1;

				trk1[j] = tnp_weight_trk_pbpb(Bmu1eta[j], 0);
				trk2[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 0);

				trg1[j] = 1;
				trg2[j] = 1;

				muid1systup[j] = 1;
				muid1systdown[j] = 1;
				muid1statup[j] = 1;
				muid1statdown[j] = 1;


				muid2systup[j] = 1;
				muid2systdown[j] = 1;
				muid2statup[j] = 1;
				muid2statdown[j] = 1;


				trk1systup[j] = tnp_weight_trk_pbpb(Bmu1eta[j], -1);
				trk1systdown[j] = tnp_weight_trk_pbpb( Bmu1eta[j], -2);
				trk1statup[j] = tnp_weight_trk_pbpb( Bmu1eta[j], 1);
				trk1statdown[j] = tnp_weight_trk_pbpb( Bmu1eta[j], 2);


				trk2systup[j] = tnp_weight_trk_pbpb(Bmu2eta[j], -1);
				trk2systdown[j] = tnp_weight_trk_pbpb(Bmu2eta[j], -2);
				trk2statup[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 1);
				trk2statdown[j] = tnp_weight_trk_pbpb(Bmu2eta[j], 2);




				trg1systup[j] = 1;
				trg1systdown[j] = 1;
				trg1statup[j] = 1;
				trg1statdown[j] = 1;


				trg2systup[j] = 1;
				trg2systdown[j] = 1;
				trg2statup[j] = 1;
				trg2statdown[j] = 1;

			}



			if(DoWeight == 1){

				muid1[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 0);
				muid2[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 0);

				trk1[j] = 1;
				trk2[j] = 1;

				trg1[j] = 1;
				trg2[j] = 1;

				muid1systup[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -1);
				muid1systdown[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], -2);
				muid1statup[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 1);
				muid1statdown[j] = tnp_weight_muid_pbpb(Bmu1pt[j], Bmu1eta[j], 2);


				muid2systup[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -1);
				muid2systdown[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], -2);
				muid2statup[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 1);
				muid2statdown[j] = tnp_weight_muid_pbpb(Bmu2pt[j], Bmu2eta[j], 2);



				trk1systup[j] = 1;
				trk1systdown[j] = 1;
				trk1statup[j] = 1;
				trk1statdown[j] = 1;


				trk2systup[j] = 1;
				trk2systdown[j] = 1;
				trk2statup[j] = 1;
				trk2statdown[j] = 1;



				trg1systup[j] = 1;
				trg1systdown[j] = 1;
				trg1statup[j] = 1;
				trg1statdown[j] = 1;


				trg2systup[j] = 1;
				trg2systdown[j] = 1;
				trg2statup[j] = 1;
				trg2statdown[j] = 1;

			}




			if(DoWeight == 0){

				muid1[j] = 1;
				muid2[j] = 1;

				trk1[j] = 1;
				trk2[j] = 1;

				trg1[j] = 1;
				trg2[j] = 1;

				muid1systup[j] = 1;
				muid1systdown[j] = 1;
				muid1statup[j] = 1;
				muid1statdown[j] = 1;


				muid2systup[j] = 1;
				muid2systdown[j] = 1;
				muid2statup[j] = 1;
				muid2statdown[j] = 1;


				trk1systup[j] = 1;
				trk1systdown[j] = 1;
				trk1statup[j] = 1;
				trk1statdown[j] = 1;


				trk2systup[j] = 1;
				trk2systdown[j] = 1;
				trk2statup[j] = 1;
				trk2statdown[j] = 1;




				trg1systup[j] = 1;
				trg1systdown[j] = 1;
				trg1statup[j] = 1;
				trg1statdown[j] = 1;


				trg2systup[j] = 1;
				trg2systdown[j] = 1;
				trg2statup[j] = 1;
				trg2statdown[j] = 1;

			}



		}


		TnPInfo->Fill();	

	}

	fout->Write();
	fout->Close();

	fin->Close();
}


