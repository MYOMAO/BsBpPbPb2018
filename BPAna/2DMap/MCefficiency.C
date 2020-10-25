#include "uti.h"
#include "parameters.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

Float_t hiBinMin,hiBinMax,centMin,centMax;

bool useFiducial = 1;
bool useSplotweight = 0;//must change the inputfile below!
bool usetrkweight = 0;//must change the inputfile below!

int _nBins = nBins;
double *_ptBins = ptBins;

void MCefficiency(int isPbPb=0,TString inputmc="", TString selmcgen="",TString selmcgenacceptance="", TString cut_recoonly="", TString cut="",TString label="PP",TString outputfile="test", int useweight=1,Float_t centmin=0., Float_t centmax=100.)
{ 
  gStyle->SetPalette(55,0);

  if(label=="ppInc"){
    _nBins = nBinsInc;
    _ptBins = ptBinsInc;
  }
  
  std::string str = label.Data();
  std::size_t found = str.find("Fine");
  //if(label=="ppFine"||label=="PbPbFine"){
  if (found!=std::string::npos){
    _nBins = nBinsFine;
    _ptBins = ptBinsFine;
  }
  
  hiBinMin = centmin*2;
  hiBinMax = centmax*2;
  centMin = centmin;
  centMax = centmax;


	 if(useFiducial)
    {
      cut_recoonly=Form("%s&&((Bpt>5&&Bpt<10&&TMath::Abs(By)>1.5)||(Bpt>10))",cut_recoonly.Data());
      cut=Form("%s&&((Bpt>5&&Bpt<10&&TMath::Abs(By)>1.5)||(Bpt>10))",cut.Data());
    }


  if(isPbPb==1)
    {

      selmcgen = selmcgen+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
      selmcgenacceptance=selmcgenacceptance+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
      cut_recoonly=cut_recoonly+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
      cut=cut+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);

    }
  
  std::cout<<"selmcgen="<<selmcgen<<std::endl;
  std::cout<<"selmcgenacceptance="<<selmcgenacceptance<<std::endl;
  std::cout<<"cut_recoonly="<<cut_recoonly<<std::endl;
  std::cout<<"cut="<<cut<<std::endl;
  std::cout<<"option="<<useweight<<std::endl;
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
   
  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("Bfinder/ntKp");
  ntMC->AddFriend("hltanalysis/HltTree");
  ntMC->AddFriend("hiEvtAnalyzer/HiTree");
  ntMC->AddFriend("Bfinder/ntGen");
  ntMC->AddFriend("skimanalysis/HltTree");
  ntMC->AddFriend("BDT");
  ntMC->AddFriend("splot");
  ntMC->AddFriend("TnPInfo");
  ntMC->AddFriend("CentWeightTree");


  TTree* ntGen = (TTree*)infMC->Get("Bfinder/ntGen");
  ntGen->AddFriend("hltanalysis/HltTree");
  ntGen->AddFriend("hiEvtAnalyzer/HiTree");
  ntGen->AddFriend("Bfinder/ntKp");
  ntGen->AddFriend("skimanalysis/HltTree");
  ntGen->AddFriend("BDT");

  // optimal weights
  TCut weighpthat = "1";
  TCut weightGpt = "1";
  TCut weightBgenpt = "1";
  TCut weightHiBin = "1";
  TCut weightPVz = "1";




   weighpthat = "pthatweight";
   weightHiBin = "CentWeight";
   weightPVz = "(TMath::Gaus(PVz,0.432315,4.874300)/(sqrt(2*3.14159)*4.874300))/(TMath::Gaus(PVz,0.909938,4.970989)/(sqrt(2*3.14159)*4.970989))";

	if(useweight==0) { //PbPb
	    weightGpt = "1";
		weightBgenpt = "1";
	}

	if(useweight == 1){
		weightBgenpt = "(2.907795+-0.436572*Bgenpt+0.006372*Bgenpt*Bgenpt)*TMath::Exp(-0.157563*Bgenpt)+1.01308";  
		weightGpt = "(2.907795+-0.436572*Gpt+0.006372*Gpt*Gpt)*TMath::Exp(-0.157563*Gpt)+1.01308";
	}

    if(useweight == 2){
		weightGpt = "(3.00448277-0.35865276*Gpt+0.01997413*Gpt*Gpt-0.00042585*Gpt*Gpt*Gpt+0.00000315*Gpt*Gpt*Gpt*Gpt)";
		weightBgenpt = "(3.00448277-0.35865276*Bgenpt+0.01997413*Bgenpt*Bgenpt-0.00042585*Bgenpt*Bgenpt*Bgenpt+0.00000315*Bgenpt*Bgenpt*Bgenpt*Bgenpt)";
	}
  //double LowBinWidth = 0.5;
 
  TCut muid1 = "muid1";
  TCut muid2 = "muid2";
  TCut trk1 = "trk1";
  TCut trk2 = "trk2";
  TCut trg1 = "trg1";	 
  TCut trg2 = "trg2";


  double LowBinWidth = 0.5;
  int NLowBin = 5/LowBinWidth;
  double HighBinWidth = 1;
  int NHighBin = 50/HighBinWidth;
  const int BptBin = NHighBin + NLowBin;
  double BptBinning[BptBin + 1];
  for(int i = 0; i < NLowBin; i++){
    BptBinning[i] = 5 + i * LowBinWidth;
  }
  for(int i = 0; i <  NHighBin+1; i++){
  BptBinning[i+NLowBin] = 10 + i * HighBinWidth;
  }

  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtMCrecoonly = new TH1D("hPtMCrecoonly","",nBins,ptBins);
  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);
  TH1D* hPtGenAcc = new TH1D("hPtGenAcc","",nBins,ptBins);
  TH1D* hPtGenAccWeighted = new TH1D("hPtGenAccWeighted","",nBins,ptBins);
  TH1D* hPthat = new TH1D("hPthat","",100,0,500);
  TH1D* hPthatweight = new TH1D("hPthatweight","",100,0,500);



  cout << "selmcgen = " << selmcgen.Data() << endl;

  ntMC->Project("hPtMC","Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
  ntMC->Project("hPtMCrecoonly","Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut_recoonly.Data())&&"(Bgen==23333)"));
  ntGen->Project("hPtGen","Gpt",TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgen.Data())));
  ntGen->Project("hPtGenAcc","Gpt",TCut(weighpthat)*TCut(weightGpt)*(TCut(selmcgenacceptance.Data())));
  ntGen->Project("hPtGenAccWeighted","Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));


  ntMC->Project("hPthat","pthat","1");
  ntMC->Project("hPthatweight","pthat","pthatweight");

  divideBinWidth(hPtMC);
  divideBinWidth(hPtMCrecoonly);
  divideBinWidth(hPtGen);
  divideBinWidth(hPtGenAcc);
  divideBinWidth(hPtGenAccWeighted);



  //Acceptance
  TH1D* hEffAcc = (TH1D*)hPtGenAcc->Clone("hEffAcc");
  hEffAcc->Divide(hEffAcc,hPtGen,1,1,"b");
  //Selection
  TH1D* hEffSelection = (TH1D*)hPtMC->Clone("hEffSelection");
  hEffSelection->Divide(hEffSelection,hPtGenAccWeighted,1,1,"b");
  //Acc * Eff (one shot)
  TH1D* hEffReco = (TH1D*)hPtMCrecoonly->Clone("hEffReco");
  hEffReco->Divide(hEffReco,hPtGen,1,1,"b");
  //Acc * Eff
  TH1D* hEff = (TH1D*)hEffSelection->Clone("hEff");
  hEff->Multiply(hEff,hEffAcc,1,1);
  TH1D* invEff = (TH1D*)hPtGenAccWeighted->Clone("invEff");
  invEff->Divide(hPtMC);
  
  //2D projection
  TH2D* hPtMC2D = new TH2D("hPtMC2D","",BptBin,BptBinning,nBinsY,ptBinsY);
  TH2D* hPtGen2D = new TH2D("hPtGen2D","",BptBin,BptBinning,nBinsY,ptBinsY);
  TH2D* hPtGenAcc2D = new TH2D("hPtGenAcc2D","",BptBin,BptBinning,nBinsY,ptBinsY);

  TCut weightsplot = "splotweight";
  TCut weight_Btrk1Eta = "Btrk1Eta_weight";
  TCut weight_Btrk1Y = "Btrk1Y_weight";
  TCut weight_Btrk1Pt = "Btrk1Pt_weight";
  TCut weight_Btrk1Dz1 = "Btrk1Dz1_weight";
  TCut weight_Btrk1DzError1 = "Btrk1DzError1_weight";
  TCut weight_Btrk1Dxy1 = "Btrk1Dxy1_weight";
  TCut weight_Btrk1DxyError1 = "Btrk1DxyError1_weight";

  if(useweight == 3)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt", (TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) * TCut(weightsplot)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }



  if(useweight == 4)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1Eta)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }

    if(useweight == 5)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1Y)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }

    if(useweight == 6)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1Pt)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }


    if(useweight == 7)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1Dz1)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }

    if(useweight == 8)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1DzError1)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }

    if(useweight == 9)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1Dxy1)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }

    if(useweight == 10)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weight_Btrk1DxyError1)*TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));
    }


  if(useweight < 3)
    {
      ntMC->Project("hPtMC2D","abs(By):Bpt",(TCut(muid1) * TCut(trk1) * TCut(trg1) * TCut(muid2) * TCut(trk2) * TCut(trg2)) *TCut(weighpthat)*TCut(weightBgenpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(cut.Data())&&"(Bgen==23333)"));      
    }


  cout << "weightGpt = " << weightGpt << endl;

  

  ntGen->Project("hPtGenAcc2D","abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgenacceptance.Data())));
  ntGen->Project("hPtGen2D","abs(Gy):Gpt",TCut(weighpthat)*TCut(weightGpt)*TCut(weightHiBin)*TCut(weightPVz)*(TCut(selmcgen.Data())));
  hPtMC2D->Sumw2();
  hPtGen2D->Sumw2();
  hPtGenAcc2D->Sumw2();

  TH2D* hEff2D = (TH2D*)hPtMC2D->Clone("hEff2D");
  hEff2D->Divide(hPtGen2D);
  TH2D* invEff2D = (TH2D*)hPtGen2D->Clone("invEff2D");
  invEff2D->Divide(hPtMC2D);
  TH2D* hAcc2D = (TH2D*)hPtGenAcc2D->Clone("hAcc2D");
  hAcc2D->Divide(hPtGen2D);
  TH2D* invAcc2D = (TH2D*)hPtGen2D->Clone("invAcc2D");
  invAcc2D->Divide(hPtGenAcc2D);
  TH2D* hEffonly2D = (TH2D*)hPtMC2D->Clone("hEffonly2D");
  hEffonly2D->Divide(hPtGenAcc2D);
  TH2D* invEffonly2D = (TH2D*)hPtGenAcc2D->Clone("invEffonly2D");
  invEffonly2D->Divide(hPtMC2D);

  hEff2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  hEff2D->GetYaxis()->SetTitle("B^{+} |y|");
  hEff2D->GetYaxis()->SetTitleOffset(1.5);
  hEff2D->GetXaxis()->CenterTitle();
  hEff2D->GetYaxis()->CenterTitle();

  invEff2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  invEff2D->GetYaxis()->SetTitle("B^{+} |y|");
  invEff2D->GetYaxis()->SetTitleOffset(1.5);
  invEff2D->GetXaxis()->CenterTitle();
  invEff2D->GetYaxis()->CenterTitle();

  hAcc2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  hAcc2D->GetYaxis()->SetTitle("B^{+} |y|");
  hAcc2D->GetYaxis()->SetTitleOffset(1.5);
  hAcc2D->GetXaxis()->CenterTitle();
  hAcc2D->GetYaxis()->CenterTitle();

  invAcc2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  invAcc2D->GetYaxis()->SetTitle("B^{+} |y|");
  invAcc2D->GetYaxis()->SetTitleOffset(1.5);
  invAcc2D->GetXaxis()->CenterTitle();
  invAcc2D->GetYaxis()->CenterTitle();

  hEff2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  hEff2D->GetYaxis()->SetTitle("B^{+} |y|");
  hEff2D->GetYaxis()->SetTitleOffset(1.5);
  hEff2D->GetXaxis()->CenterTitle();
  hEff2D->GetYaxis()->CenterTitle();

  invEff2D->GetXaxis()->SetTitle("B^{+} p_{T} (GeV/c)");
  invEff2D->GetYaxis()->SetTitle("B^{+} |y|");
  invEff2D->GetYaxis()->SetTitleOffset(1.5);
  invEff2D->GetXaxis()->CenterTitle();
  invEff2D->GetYaxis()->CenterTitle();

  TCanvas* cEff2D = new TCanvas("","",600,600);
  cEff2D->cd();
  hEff2D->Draw("COLZ");
  //cEff2D->SaveAs(Form("plotAverageEff/Eff2D_Cent%.0f-%.0f.png",centmin,centmax));
  //cEff2D->SaveAs(Form("plotAverageEff/Eff2D_Cent%.0f-%.0f.pdf",centmin,centmax));

  TCanvas* cinvEff2D = new TCanvas("","",600,600);
  cinvEff2D->cd();
  invEff2D->Draw("COLZ");

  

  TH2F* hemptyEff=new TH2F("hemptyEff","",50,_ptBins[0]-5.,_ptBins[_nBins]+5.,10,0.,1.);  
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  //hemptyEff->GetYaxis()->SetTitle("acceptance x #epsilon_{reco} x #epsilon_{sel} ");
  hemptyEff->GetYaxis()->SetTitle("#alpha x #epsilon");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.9);
  hemptyEff->GetYaxis()->SetTitleOffset(0.95);
  hemptyEff->GetXaxis()->SetTitleSize(0.05);
  hemptyEff->GetYaxis()->SetTitleSize(0.05);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.035);
  hemptyEff->GetYaxis()->SetLabelSize(0.035);  
  hemptyEff->SetMaximum(1.0);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TH2F* hemptyEffAcc=(TH2F*)hemptyEff->Clone("hemptyEffAcc");
  TH2F* hemptyEffReco=(TH2F*)hemptyEff->Clone("hemptyEffReco");
  TH2F* hemptyEffSelection=(TH2F*)hemptyEff->Clone("hemptyEffSelection"); 

  TCanvas*canvasEff=new TCanvas("canvasEff","canvasEff",1000.,500);
  canvasEff->Divide(2,1);
  canvasEff->cd(1);
  
  hemptyEffAcc->SetYTitle("#alpha");
  hemptyEffAcc->Draw();
  hEffAcc->Draw("same");
  canvasEff->cd(2);
  hemptyEff->Draw();
  hEff->Draw("same");
  canvasEff->SaveAs(Form("plotEff/canvasEff_study%s.png",Form(label.Data())));
  canvasEff->SaveAs(Form("plotEff/canvasEff_study%s.pdf",Form(label.Data())));
  
  for(int j=0;j<_nBins;j++)
    {
      //printf("p_t bins %.0f-%.0f hEff: %f hEffErr: %f hEffErr/hEff: %f\n",_ptBins[j],_ptBins[j+1],hEff->GetBinContent(j+1),hEff->GetBinError(j+1),hEff->GetBinError(j+1)/hEff->GetBinContent(j+1));
    }
  
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0.,500.,10,1e-5,1e9);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Entries");
  hemptyPthat->GetXaxis()->SetTitle("pthat");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(0.95);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  
  hemptyPthat->SetMaximum(1.0);
  hemptyPthat->SetMinimum(0.);
  
  TH2F* hemptySpectra=new TH2F("hemptySpectra","",50,0.,130.,10,1,1e9);  
  hemptySpectra->GetXaxis()->CenterTitle();
  hemptySpectra->GetYaxis()->CenterTitle();
  hemptySpectra->GetYaxis()->SetTitle("Entries");
  hemptySpectra->GetXaxis()->SetTitle("p_{T}");
  hemptySpectra->GetXaxis()->SetTitleOffset(0.9);
  hemptySpectra->GetYaxis()->SetTitleOffset(0.95);
  hemptySpectra->GetXaxis()->SetTitleSize(0.05);
  hemptySpectra->GetYaxis()->SetTitleSize(0.05);
  hemptySpectra->GetXaxis()->SetTitleFont(42);
  hemptySpectra->GetYaxis()->SetTitleFont(42);
  hemptySpectra->GetXaxis()->SetLabelFont(42);
  hemptySpectra->GetYaxis()->SetLabelFont(42);
  hemptySpectra->GetXaxis()->SetLabelSize(0.035);
  hemptySpectra->GetYaxis()->SetLabelSize(0.035);  
  
  TH2F* hemptyPthatWeighted=(TH2F*)hemptyPthat->Clone("hemptyPthatWeighted");
  hemptyPthatWeighted->GetXaxis()->SetTitle("pthat reweighted");
  
  TCanvas*canvasPthat=new TCanvas("canvasPthat","canvasPthat",1000.,500);
  canvasPthat->Divide(2,1);
  canvasPthat->cd(1);
  gPad->SetLogy();
  hemptyPthat->Draw("same");
  hPthat->Draw("same");
  canvasPthat->cd(2);
  gPad->SetLogy();
  hemptyPthatWeighted->Draw();
  hPthatweight->Draw("same");
  canvasPthat->SaveAs(Form("plotEff/canvasPthat_%s.pdf",Form(label.Data())));
  
  TCanvas*canvasSpectra=new TCanvas("canvasSpectra","canvasSpectra",1000.,500);
  canvasSpectra->Divide(2,1);
  canvasSpectra->cd(1);
  gPad->SetLogy();
  hemptySpectra->Draw();
  hPtMC->Draw("same");
  canvasSpectra->cd(2);
  gPad->SetLogy();
  hemptySpectra->Draw();
  hPtGen->Draw("same");
  canvasSpectra->SaveAs(Form("plotEff/canvasSpectra_%s.pdf",Form(label.Data())));
  
  TString text;
  if (isPbPb) { text="1.5 nb^{-1} (5.02 TeV PbPb)";}
  else {text="28.0 pb^{-1} (5.02 TeV pp)";}
  TLatex* texlumi = new TLatex(0.9,0.92,text.Data());
  texlumi->SetNDC();
  texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  
  TString texper="%";
  TLatex* texCent = new TLatex(0.5,0.815,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextFont(42);
  texCent->SetTextSize(0.05);
  
  TLatex* texY = new TLatex(0.5,0.750,"|y| < 2.4");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.05);
  texY->SetLineWidth(2);
  
  TLatex* texCms = new TLatex(0.08,0.95, "CMS Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(13);
  texCms->SetTextSize(0.038);
  texCms->SetTextFont(62);
  
  TCanvas*canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy(0);
  //hemptyEff->SetYTitle("hPtMC / hPtGen");
  hemptyEff->SetMaximum(0.6);
  hemptyEff->SetYTitle("#alpha x #epsilon");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->Draw();
  hEff->SetLineColor(2);
  hEff->SetMarkerColor(2);
  hEff->Draw("same");
  if(isPbPb) texCent->Draw();
  texY->Draw();
  texCms->Draw();
  texlumi->Draw();
  canvas1D->SaveAs(Form("plotEff/canvas1DhEff_%s.pdf",Form(label.Data())));
  canvas1D->SaveAs(Form("plotEff/canvas1DhEff_%s.C",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy();
  hemptySpectra->SetYTitle("Entries of hPtMC");
  hemptySpectra->Draw(); 
  hPtMC->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhPtMC_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy();
  hemptySpectra->SetYTitle("Entries of hPtMCrecoonly");
  hemptySpectra->Draw(); 
  hPtMCrecoonly->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhPtMCrecoonly_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
 
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy();
  hemptySpectra->SetYTitle("Entries of hPtGen");
  hemptySpectra->Draw(); 
  hPtGen->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhPtGen_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy();
  hemptySpectra->SetYTitle("Entries of hPtGenAcc");
  hemptySpectra->Draw(); 
  hPtGenAcc->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhPtGenAcc_%s.pdf",Form(label.Data())));
  canvas1D->Clear();

  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  gPad->SetLogy();
  hemptyEff->SetYTitle("hPtMC / hPtGen");
  hemptyEff->Draw();
  hEff->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhEff_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  hemptyEff->SetYTitle("hPtMCrecoonly / hPtGen");
  hemptyEff->Draw(); 
  hEffReco->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhEffReco_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  hemptyEff->SetYTitle("hPtGenAcc / hPtGen");
  hemptyEff->Draw(); 
  hEffAcc->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhEffAcc_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  canvas1D=new TCanvas("canvas1D","",600,600);
  canvas1D->cd();
  hemptyEff->SetYTitle("hPtMC / hPtGenAcc");
  hemptyEff->Draw(); 
  hEffSelection->Draw("same");
  canvas1D->SaveAs(Form("plotEff/canvas1DhEffSelection_%s.pdf",Form(label.Data())));
  canvas1D->Clear();
  
  gStyle->SetPalette(55);
  TCanvas* canvas2D=new TCanvas("canvas2D","",600,600);

  if(useweight == 0) outputfile = Form("EffMapFilesNew/NoWeight_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 1) outputfile = Form("EffMapFilesNew/Expo_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 2) outputfile = Form("EffMapFilesNew/Poly_%0.f_%0.f.root",centmin,centmax);
	
  if(useweight == 3) outputfile = Form("MCDataMapNew/sPLOT/sPLOT_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 4) outputfile = Form("MCDataMapNew/Trk/Btrk1Eta_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 5) outputfile = Form("MCDataMapNew/Trk/Btrk1Y_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 6) outputfile = Form("MCDataMapNew/Trk/Btrk1Pt_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 7) outputfile = Form("MCDataMapNew/Trk/Btrk1Dz1_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 8) outputfile = Form("MCDataMapNew/Trk/Btrk1DzError1_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 9) outputfile = Form("MCDataMapNew/Trk/Btrk1Dxy1_%0.f_%0.f.root",centmin,centmax);
  if(useweight == 10) outputfile = Form("MCDataMapNew/Trk/Btrk1DxyError1_%0.f_%0.f.root",centmin,centmax);


  TFile *fout=new TFile(outputfile.Data(),"recreate");
  fout->cd();


  //hPtMC->Write();
  //hPtGen->Write();
  //hEffAcc->Write();
  //hEffReco->Write();
  //hEffSelection->Write();
  //hEff->Write();
  //invEff->Write();


  hPtMC->Write();
  hPtGenAccWeighted->Write();
  invEff->Write();

  hPtMC2D->Write();
  hPtGen2D->Write();
  hPtGenAcc2D->Write();

  hEff2D->Write();
  invEff2D->Write();
  hAcc2D->Write();
  invAcc2D->Write();
  hEffonly2D->Write();
  invEffonly2D->Write();


  cout << "cut = " << cut.Data() << endl;

  TH2D* hPtMC2DNoWeight = new TH2D("hPtMC2DNoWeight","",BptBin,BptBinning,nBinsY,ptBinsY);
  TH2D* hPtGen2DNoWeight = new TH2D("hPtGen2DNoWeight","",BptBin,BptBinning,nBinsY,ptBinsY);

  ntMC->Project("hPtMC2DNoWeight","abs(By):Bpt",(TCut(cut.Data())&&"(Bgen==23333)"));
  ntGen->Project("hPtGen2DNoWeight","abs(Gy):Gpt",(TCut(selmcgen.Data())));

  hPtMC2DNoWeight->Write();
  hPtGen2DNoWeight->Write();

  fout->Close();
  
}

int main(int argc, char *argv[])
{
  if((argc !=12))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 12)
    MCefficiency(atoi(argv[1]),argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],atoi(argv[9]),atof(argv[10]),atof(argv[11]));
  return 0;
}
