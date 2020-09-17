//List of the optimal cuts for each pt bin
const int nBins = 1;
const int nvar = 5; // number of variables
const int ncutvar = 10; // number of varied cuts (in equal spacing)

double ptBins[nBins+1] = {5., 50.};

//double ptBins[nBins+1] = {5., 7.};
double cutvarref1[nvar] = {16.457, 0.987, 0.005, 1.092, 0.065}; // optimized cut values for each variable for the ptBin
//double ptBins[nBins+1] = {7., 10.};
double cutvarref2[nvar] = {12.714, 0.947, 2.928, 0.900, 0.053};
//double ptBins[nBins+1] = {10., 15.};
double cutvarref3[nvar] = {9.086, 0.994, 1.540, 1.262, 0.055};
//double ptBins[nBins+1] = {15., 20.};
double cutvarref4[nvar] = {7.587, 0.757, 0.000, 1.813, 0.056};
//double ptBins[nBins+1] = {20., 30.};
double cutvarref5[nvar] = {4.004, 0.996, 0.000, 1.822, 0.050};
//double ptBins[nBins+1] = {30., 50.};
double cutvarref6[nvar] = {2.000, 0.998, 0.000, 2.046, 0.050};
//double ptBins[nBins+1] = {50., 100.};
//double cutvarref[nvar] = {4.084, -0.112, 0.000, 1.645, 0.050};

TString cutvarname[nvar]; // dls3D, costheta, dxysig, trkpt, chisq
TString cutvar[nvar]; // (BsvpvDistance/BsvpvDisErr), cos(Bdtheta), TMath::Abs(Btrk1Dxy1/Btrk1DxyError1), Btrk1Pt, Bchi2cl

double cutvarmin[nvar] = {2.0, -1.0, 0.0, 0.9, 0.050}; // customize
double cutvarmax[nvar] = {18.0, 0.999, 8.0, 2.4, 0.500}; // customize
double cutspacing;

double yieldData_ref;
double yieldErrData_ref;
double yieldMC_ref;
double yieldErrMC_ref;

double yieldData[ncutvar];
double yieldErrData[ncutvar];
double yieldMC[ncutvar];
double yieldErrMC[ncutvar];

double RatioData[ncutvar];
double RatioErrData[ncutvar];
double RatioMC[ncutvar];
double RatioErrMC[ncutvar];

double DoubleRatio[ncutvar];
double DoubleRatioErr[ncutvar];

TF1* fData_ref;
TF1* fMC_ref;
TF1* fData[ncutvar];
TF1* fMC[ncutvar];
TF1* totalmass;
