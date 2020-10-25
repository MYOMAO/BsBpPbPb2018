#include "TCut.h"

TString weightmc="1";
TString weightdata="1";
//TString weightdata = "(1/0.144708+TMath::Exp(-1.035696*(BptNew-15.321432))+TMath::Exp(-0.204131*(BptNew-30.289313)))";

const int nBins=4;
double ptBins[nBins+1] = {7,10,15,20,50};


const int nBinsInc=1;
double ptBinsInc[nBinsInc+1] = {10,15};
const int nBins750=3;
double ptBins750[nBins750+1] = {7,15,20,50};
const int nBins750_acc=4;
double ptBins750_acc[nBins750_acc+1] = {7,12,15,20,50};
const int nBins1050=4;
double ptBins1050[nBins1050+1] = {10,15,20,30,50};
const int nBins1250=4;
double ptBins1250[nBins1250+1] = {12,15,20,30,50};


const int nBinsY=4;
double ptBinsY[nBinsY+1] = {0.0,0.5, 1.0, 1.5, 2.4};

const int nBinsFine=45;
double ptBinsFine[nBinsFine+1]={5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};


const int nBinshi=1;
double Binshi[nBinshi+1] = {0.*2,90.*2};
const int nBins_full=1;
double ptBins_full[nBins_full+1] = {15,20};
double hiBins_full[nBins_full+1] = {0*2,90*2};
const int nBins_bp = 8;
double ptBins_bp[nBins_bp+1] = {5,7,10,15,20,30,40,50,60};

float cRightMargin = 0.043;
float cLeftMargin = 0.18;
float cTopMargin = 0.1;
float cBottomMargin = 0.145;
//Color_t BsBoxColor = kAzure+7;
//Color_t BsPointColor = kAzure-1;
Color_t BsBoxColor = kMagenta-3;
Color_t BsPointColor = kMagenta+2;

