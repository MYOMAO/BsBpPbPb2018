//List of the optimal cuts for each pt bin
const int nBins = 1;
const int nvar = 1; // number of variables
const int ncutvar = 10; // number of varied cuts (in equal spacing)

//double ptBins[nBins+1] = {5., 7.};
//double cutvarref[nvar] = {16.457, 0.987, 0.005, 1.092, 0.065}; // optimized cut values for each variable for the ptBin
//double cutvarref[nvar] = {0.07}; //Best fit 0.00 0.09 //Acceptable fit -0.24 0.10
//double nocut[nvar] = {-0.20};

//double ptBins[nBins+1] = {7., 10.};
//double cutvarref[nvar] = {12.714, 0.947, 2.928, 0.900, 0.053};
//double cutvarref[nvar] = {0.08}; //0.00 0.09 //-0.05 0.10
//double nocut[nvar] = {-0.03};

//double ptBins[nBins+1] = {10., 15.};
//double cutvarref[nvar] = {9.086, 0.994, 1.540, 1.262, 0.055};
//double cutvarref[nvar] = {0.09}; //0.00 0.12 //-0.08 0.15
//double nocut[nvar] = {0.00};

//double ptBins[nBins+1] = {15., 20.};
//double cutvarref[nvar] = {7.587, 0.757, 0.000, 1.813, 0.056};
//double cutvarref[nvar] = {0.09}; //0.00 0.12 //-0.20 0.20
//double nocut[nvar] = {0.05};

//double ptBins[nBins+1] = {20., 30.};
//double cutvarref[nvar] = {4.004, 0.996, 0.000, 1.822, 0.050};
//double cutvarref[nvar] = {0.07}; //0.00 0.12 //-0.10 0.20
//double nocut[nvar] = {0.05};

//double ptBins[nBins+1] = {30., 40.};
//double cutvarref[nvar] = {2.000, 0.998, 0.000, 2.046, 0.050};
//double cutvarref[nvar] = {0.12}; //0.00 0.15 //0.00 0.22
//double nocut[nvar] = {0.08};

//double ptBins[nBins+1] = {40., 50.};
//double cutvarref[nvar] = {2.000, 0.998, 0.000, 2.046, 0.050};
//double cutvarref[nvar] = {0.12}; //0.00 0.15 //0.00 0.22
//double nocut[nvar] = {0.08};

double ptBins[nBins+1] = {50., 60.};
//double cutvarref[nvar] = {4.084, -0.112, 0.000, 1.645, 0.050};
double cutvarref[nvar] = {0.24}; //0.14 0.30 //0.14 0.30
double nocut[nvar] = {0.20};

TString cutvarname[nvar]; // dls3D, costheta, dxysig, trkpt, chisq
TString cutvar[nvar]; // (BsvpvDistance/BsvpvDisErr), cos(Bdtheta), TMath::Abs(Btrk1Dxy1/Btrk1DxyError1), Btrk1Pt, Bchi2cl

//double cutvarmin[nvar] = {10.0, 0.799, 0.0, 0.92, 0.050}; // customize
//double cutvarmax[nvar] = {18.0, 0.999, 8.0, 1.1, 0.500}; // customize
double cutvarmin[nvar] = {0.14};
double cutvarmax[nvar] = {0.30};

double cutspacing;

double yieldData_ref;
double yieldErrData_ref;
double yieldMC_ref;
double yieldErrMC_ref;

double Ratio_ref;
double RatioErr_ref;

double yieldData_nocut;
double yieldErrData_nocut;
double yieldMC_nocut;
double yieldErrMC_nocut;

double Ratio_nocut;
double RatioErr_nocut;

//double RatioErrData_ref;
//double RatioErrMC_ref;

double yieldData[ncutvar];
double yieldErrData[ncutvar];
double yieldMC[ncutvar];
double yieldErrMC[ncutvar];

double Ratio_var[ncutvar];
double RatioErr_var[ncutvar];

//double RatioData[ncutvar];
//double RatioErrData[ncutvar];
//double RatioMC[ncutvar];
//double RatioErrMC[ncutvar];

double DoubleRatio[ncutvar];
double DoubleRatioErr[ncutvar];

double DoubleRatio_nocut;
double DoubleRatioErr_nocut;

TF1* fData_ref;
TF1* fMC_ref;
TF1* fData_nocut;
TF1* fMC_nocut;
TF1* fData[ncutvar];
TF1* fMC[ncutvar];
TF1* totalmass;