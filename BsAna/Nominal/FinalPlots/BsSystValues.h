const int GlobalSystNBin = 1;
double GlobalX[GlobalSystNBin] = {3};
double GlobalY[GlobalSystNBin] = {0};

double GlobalXLow[GlobalSystNBin] = {1.5};
double GlobalXHigh[GlobalSystNBin] = {1.5};
double GlobalSystLow[GlobalSystNBin] = {0.0793};
double GlobalSystHigh[GlobalSystNBin] = {0.0798};




const int NPtBins = 4;
double PtBin[NPtBins] ={8.5,12.5,17.5,35};
double PtBinY[NPtBins] ={0,0,0,0};
double PtBinWidthHigh[NPtBins] ={1.5,2.5,2.5,15};
double PtBinWidthLow[NPtBins] ={1.5,2.5,2.5,15};


double TotalSystHigh[NPtBins] = {0.5108,0.1622,0.1320,0.1634};
double TotalSystLow[NPtBins] = {0.4910,0.1553,0.1305,0.1622};

double SignalSystHigh[NPtBins] = {0.0862,0.03777,0.01848,0.03734};
double SignalSystLow[NPtBins] = {0.0862,0.03777,0.01848,0.03734};

double EffSystHigh[NPtBins] ={0.4602,0.1271,0.1160,0.1482};
double EffSystLow[NPtBins] = {0.4602,0.1271,0.1160,0.1482};


double TnPSystHigh[NPtBins] = {0.200,0.0934,0.0601,0.0605};
double TnPSystLow[NPtBins] = {0.142,0.0808,0.0568,0.0573};



const int NCentBins = 2;
double CentBin[NCentBins] ={15,60};
double CentBinY[NCentBins] ={0,0};
double CentBinWidthHigh[NCentBins] ={15,30};
double CentBinWidthLow[NCentBins] ={15,30};


double GlobalXCent[GlobalSystNBin] = {-5};
double GlobalXCentLow[GlobalSystNBin] = {2.5};
double GlobalXCentHigh[GlobalSystNBin] = {2.5};

double GlobalSystLowCent[GlobalSystNBin] = {0.0760};
double GlobalSystHighCent[GlobalSystNBin] = {0.0760};


double TotalSystHighCent[NCentBins] = {0.167,0.135};
double TotalSystLowCent[NCentBins] = {0.159,0.132};

double SignalSystHighCent[NCentBins] = {0.0619,0.0139};
double SignalSystLowCent[NCentBins] = {0.0619,0.0139};

double EffSystHighCent[NCentBins] ={0.1228,0.1072};
double EffSystLowCent[NCentBins] = {0.1225,0.1072};


double TnPSystHighCent[NCentBins] = {0.0913,0.0723};
double TnPSystLowCent[NCentBins] = {0.0777,0.0664};














const int NInclusive = 1;
double InclusiveBin[NInclusive] ={45};
double InclusiveBinY[NInclusive] ={0};
double InclusiveBinWidthLow[NInclusive] ={45};
double InclusiveBinWidthHigh[NInclusive] ={45};


double GlobalSystLowInc[GlobalSystNBin] = {0.0760};
double GlobalSystHighInc[GlobalSystNBin] = {0.0760};

double TotalSystHighInc[NInclusive] = {0.143};
double TotalSystLowInc[NInclusive] = {0.137};

double SignalSystHighInc[NInclusive] = {0.0228};
double SignalSystLowInc[NInclusive] = {0.0228};

double EffSystHighInc[NInclusive] ={0.1110};
double EffSystLowInc[NInclusive] = {0.1110};


double TnPSystHighInc[NInclusive] = {0.0836};
double TnPSystLowInc[NInclusive] = {0.0737};





TH2D * HisEmptyPt = new TH2D("HisEmptyPt","",100,0,100,100,-1,1);
TH2D * HisEmptyCent = new TH2D("HisEmptyCent","",105,-10,120,100,-1,1);
TH2D * HisEmptyInc = new TH2D("HisEmptyInc","",105,-10,120,100,-1,1);

