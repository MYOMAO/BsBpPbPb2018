//List of the optimal cuts for each pt bin
const int nBins = 1;
const int nvar = 1; // number of variables
const int ncutvar = 10; // number of varied cuts (in equal spacing)
const int nleft = 6;
const int nright = 3;
double cutspacing = 0.03;

double ptBins[nBins+1] = {5., 10.};
double cutvarref1[nvar] = {0.07};
double cutvarref2[nvar] = {0.08};
//double cutvarref3[nvar] = {0.09};
//double cutvarref4[nvar] = {0.09};
//double cutvarref5[nvar] = {0.07};
//double cutvarref6[nvar] = {0.12};

//double cutvarref7[nvar] = {0.24};

TString cutvarname; // dls3D, costheta, dxysig, trkpt, chisq
TString cutvar[2]; // (BsvpvDistance/BsvpvDisErr), cos(Bdtheta), TMath::Abs(Btrk1Dxy1/Btrk1DxyError1), Btrk1Pt, Bchi2cl

//double cutvarmin[nvar] = {2.0, -1.0, 0.0, 0.9, 0.050}; // customize
//double cutvarmax[nvar] = {18.0, 0.999, 8.0, 2.4, 0.500}; // customize

double yieldData_ref;
double yieldErrData_ref;
double yieldMC_ref;
double yieldErrMC_ref;

double Ratio_ref;
double RatioErr_ref;

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

TF1* fData_ref;
TF1* fMC_ref;
TF1* fData[ncutvar];
TF1* fMC[ncutvar];
TF1* totalmass;
