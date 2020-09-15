const int GlobalSystNBin = 1;
double GlobalX[GlobalSystNBin] = {3};
double GlobalY[GlobalSystNBin] = {0};

double GlobalXLow[GlobalSystNBin] = {1.5};
double GlobalXHigh[GlobalSystNBin] = {1.5};
double GlobalSystLow[GlobalSystNBin] = {0.0375};
double GlobalSystHigh[GlobalSystNBin] = {0.0375};




const int NPtBins = 4;
double PtBin[NPtBins] ={8.5,12.5,17.5,35};
double PtBinY[NPtBins] ={0,0,0,0};
double PtBinWidthHigh[NPtBins] ={1.5,2.5,2.5,15};
double PtBinWidthLow[NPtBins] ={1.5,2.5,2.5,15};


double TotalSystHigh[NPtBins] = {0.1980,0.1814,0.0923,0.0844};
double TotalSystLow[NPtBins] = {0.1914,0.1796,0.0901,0.0828};

double SignalSystHigh[NPtBins] = {0.0446,0.0273,0.0280,0.0257};
double SignalSystLow[NPtBins] = {0.0446,0.0273,0.0280,0.0257};

double EffSystHigh[NPtBins] ={0.1667,0.1653,0.06548,0.05505};
double EffSystLow[NPtBins] = {0.1667,0.1653,0.06548,0.05505};


double TnPSystHigh[NPtBins] = {0.0972,0.0696,0.0588,0.0585};
double TnPSystLow[NPtBins] = {0.0828,0.0648,0.0552,0.0560};



const int NCentBins = 2;
double CentBin[NCentBins] ={15,60};
double CentBinY[NCentBins] ={0,0};
double CentBinWidthHigh[NCentBins] ={15,30};
double CentBinWidthLow[NCentBins] ={15,30};


double GlobalXCent[GlobalSystNBin] = {-5};
double GlobalXCentLow[GlobalSystNBin] = {2.5};
double GlobalXCentHigh[GlobalSystNBin] = {2.5};

double GlobalSystLowCent[GlobalSystNBin] = {0.0280};
double GlobalSystHighCent[GlobalSystNBin] = {0.0280};


double TotalSystHighCent[NCentBins] = {0.1604,0.1259};
double TotalSystLowCent[NCentBins] = {0.1589,0.1238};

double SignalSystHighCent[NCentBins] = {0.0253,0.0281};
double SignalSystLowCent[NCentBins] = {0.0253,0.0281};

double EffSystHighCent[NCentBins] ={0.1415,0.09632};
double EffSystLowCent[NCentBins] = {0.1415,0.09632};


double TnPSystHighCent[NCentBins] = {0.066841,0.0659131};
double TnPSystLowCent[NCentBins] = {0.0631,0.0618082};














const int NInclusive = 1;
double InclusiveBin[NInclusive] ={45};
double InclusiveBinY[NInclusive] ={0};
double InclusiveBinWidthLow[NInclusive] ={45};
double InclusiveBinWidthHigh[NInclusive] ={45};


double GlobalSystLowInc[GlobalSystNBin] = {0.0280};
double GlobalSystHighInc[GlobalSystNBin] = {0.0280};

double TotalSystHighInc[NInclusive] = {0.1407};
double TotalSystLowInc[NInclusive] = {0.1387};

double SignalSystHighInc[NInclusive] = {0.0264};
double SignalSystLowInc[NInclusive] = {0.0264};

double EffSystHighInc[NInclusive] ={0.1185};
double EffSystLowInc[NInclusive] = {0.1185};


double TnPSystHighInc[NInclusive] = {0.0665};
double TnPSystLowInc[NInclusive] = {0.0622};





TH2D * HisEmptyPt = new TH2D("HisEmptyPt","",100,0,100,100,-1,1);
TH2D * HisEmptyCent = new TH2D("HisEmptyCent","",105,-10,120,100,-1,1);
TH2D * HisEmptyInc = new TH2D("HisEmptyInc","",105,-10,120,100,-1,1);

