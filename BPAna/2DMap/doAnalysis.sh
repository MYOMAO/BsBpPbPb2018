#!/bin/bash
#source clean.sh
CENTPbPbMIN=0
CENTPbPbMAX=90
#Central point of the analysis

DOANALYSISPP_FONLL=0
DOANALYSISPP_FITNP=0
DOANALYSISPP_FIT=0
DOANALYSISPP_FITONSAVED=0
DOANALYSISPP_MCSTUDY=0
DOANALYSISPP_CROSS=0

DOANALYSISPbPb_FONLL=0
DOANALYSISPbPb_FITNP=0
DOANALYSISPbPb_FIT=0
DOANALYSISPbPb_FITONSAVED=0
DOANALYSISPbPb_MCSTUDY=0
DOANALYSISPbPb_MCSTUDYSYST=0
DOANALYSISPbPb_MCSTUDYEFF=1
DOANALYSISPbPb_AVERAGEEFF=0
DOANALYSISPbPb_AVERAGEEFF_TRACK=0
DOANALYSISPbPb_AVERAGEEFF_TOY=0
DOANALYSISPbPb_CROSS=0
DORAA=0
DORAA_POSTPRL=0

#Rapidity RAA
DOANALYSISPP_FIT_Y=0
DOANALYSISPP_MCSTUDY_Y=0
DOANALYSISPbPb_FIT_Y=0
DOANALYSISPbPb_MCSTUDY_Y=0
DORAA_Y=0

#CENTRALITY RAA
DOANALYSISPP_FIT_INC=0
DOANALYSISPP_MCSTUDY_INC=0
DOANALYSISPbPb_FIT_CENT=0
DOANALYSISPbPb_MCSTUDY_CENT=0
DOANALYSISPbPb_CROSS_CENT=0
DORAA_CENT=0

DOANALYSISPP_MCSTUDY_FINE=0
DOANALYSISPP_EFFFIT=0
DOANALYSISPP_FIT_INC_EFFCOR=0
DOANALYSISPbPb_MCSTUDY_FINE_HIBIN=0
DOANALYSISPbPb_EFFFIT=0
DOANALYSISPbPb_FIT_CENT_EFFCOR=0
DORAA_CENT_EFFCOR=0
DOANALYSISPP_FIT_EFFCOR=0
DOANALYSISPP_CROSS_EFFCOR=0

#systematic section
DOCOMPARE=0
DOSAVEHISTPP=0
DOSAVEHISTPbPb=0
DOVARIATION=0
DOClosure=0
SAVEMVAPP=0
SAVEMVAPbPb=0
PLOTMVA=0


# 2015 PP
INPUTMCPP="/raid5/data/BntupleRun2018/MC/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderMC_pp_Pythia8_BuToJpsiK_TuneCUEP8M1_20160816_bPt0jpsiPt0tkPt0p5_Bp_pthatweight_JingBDT.root"
INPUTDATAPP="/raid5/data/BntupleRun2018/Data/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderData_pp_20160816_bPt0jpsiPt0tkPt0p5_Bp_JingBDT.root"

# 2018 PbPb
INPUTMCPbPb="/export/d00/scratch/zzshi/CMSSW_7_5_8_patch3/Merge/BsBP2018PbPb/FilePrep/InputFiles/BPMC.root"
INPUTDATAPbPb="/export/d00/scratch/zzshi/CMSSW_7_5_8_patch3/Merge/BsBP2018PbPb/FilePrep/InputFiles/BsData.root"

#INPUTMCPbPb="/raid5/data/gwangjun/crab_Bfinder_20190624_Hydjet_Pythia8_Official_BuToJpsiK_1033p1_pt3tkpt0p7dls2_allpthat_pthatweight_BDT.root"
#INPUTDATAPbPb="/raid5/data/gwangjun/crab_Bfinder_20190513_HIDoubleMuon__PsiPeri__HIRun2018A_04Apr2019_v1_1033p1_GoldenJSON_skimhltBsize_ntKp_BDT.root"

#INPUTMCPbPb="/raid5/data/gwangjun/crab_Bfinder_20190624_Hydjet_Pythia8_Official_BuToJpsiK_1033p1_pt3tkpt0p7dls2_allpthat_pthatweight.root"
#INPUTDATAPbPb="/raid5/data/gwangjun/crab_Bfinder_20190513_HIDoubleMuon__PsiPeri__HIRun2018A_04Apr2019_v1_1033p1_GoldenJSON_skimhltBsize_ntKp.root"

# 2015 PbPb
# INPUTMCPbPb="/mnt/hadoop/cms/store/user/gwangjun/Bp2018/MC/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderMC_PbPb_Pythia8_BuToJpsiK_TuneCUEP8M1_20160816_bPt5jpsiPt0tkPt0p8_Bp_pthatweight_JingBDT.root"


## ANALYSIS PP TRIGGERED
FONLLDATINPUT="fonll_0to120.txt"
FONLLOUTPUTFILE="fonll_Bplus_dsigmadpt.root"
#FONLLOUTPUTFILE="ROOTfiles/fonllOutput_pp_Bplus_5p03TeV_y2p4.root"
OUTPUTFILERAA="ROOTfiles/outputRAA.root"

LABELPP="pp"
#LUMIPP=25.57 # PAS
#25.8*0.991
#LUMIPP=27.45 # paper
#27.7*0.991
LUMIPP=27.748 # paper 20170224
#28.0*0.991

ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1"
SELGENPPACCPP="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && Gtk1pt>0.5 && TMath::Abs(Gtk1eta)<2.4 && ((TMath::Abs(Gmu1eta)<1.2 && Gmu1pt>3.5) || (TMath::Abs(Gmu1eta)>=1.2 && TMath::Abs(Gmu1eta)<2.1 && Gmu1pt>(5.77-1.8*TMath::Abs(Gmu1eta))) || (TMath::Abs(Gmu1eta)>=2.1 && Gmu1pt>1.8)) && ((TMath::Abs(Gmu2eta)<1.2 && Gmu2pt>3.5) || (TMath::Abs(Gmu2eta)>=1.2 && TMath::Abs(Gmu2eta)<2.1 && Gmu2pt>(5.77-1.8*TMath::Abs(Gmu2eta))) || (TMath::Abs(Gmu2eta)>=2.1 && Gmu2pt>1.8))"
RECOONLYPP="Btrk1Pt>0.5 && Bchi2cl>0.005 && Bpt>7.0"
#pp GA
BASECUTPP="TMath::Abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&Bmass>5&&Bmass<6&& ((TMath::Abs(Bmu1eta)<1.2 && Bmu1pt>3.5) || (TMath::Abs(Bmu1eta)>1.2 && TMath::Abs(Bmu1eta)<2.1 && Bmu1pt>(5.77-1.8*TMath::Abs(Bmu1eta))) || (TMath::Abs(Bmu1eta)>2.1 && TMath::Abs(Bmu1eta)<2.4 && Bmu1pt>1.8)) && ((TMath::Abs(Bmu2eta)<1.2 && Bmu2pt>3.5) || (TMath::Abs(Bmu2eta)>1.2 && TMath::Abs(Bmu2eta)<2.1 && Bmu2pt>(5.77-1.8*TMath::Abs(Bmu2eta))) || (TMath::Abs(Bmu2eta)>2.1 && TMath::Abs(Bmu2eta)<2.4 && Bmu2pt>1.8)) && Bmu1TMOneStationTight && Bmu2TMOneStationTight && Bmu1InPixelLayer > 0 && (Bmu1InPixelLayer+Bmu1InStripLayer) > 5 && Bmu2InPixelLayer > 0 && (Bmu2InPixelLayer+Bmu2InStripLayer) > 5 && Bmu1dxyPV< 0.3 && Bmu2dxyPV< 0.3 && Bmu1dzPV<20 && Bmu2dzPV<20 && Bmu1isGlobalMuon && Bmu2isGlobalMuon && Bmu1TrgMatchFilterE>0 && Bmu2TrgMatchFilterE>0 && Btrk1highPurity && TMath::Abs(Btrk1Eta)<2.4 && Btrk1Pt>0.5 && Bchi2cl>0.005"
CUTPP="$BASECUTPP && ((Bpt>5 && Bpt<10 && Btrk1Pt>0.75 && Bchi2cl>0.032 && (BsvpvDistance/BsvpvDisErr)>5.50 && cos(Bdtheta)>0.99 && TMath::Abs(Btrk1Eta)<2.40)|| (Bpt>10 && Bpt<15 && Btrk1Pt>0.88 && Bchi2cl>0.005 && (BsvpvDistance/BsvpvDisErr)>3.50 && cos(Bdtheta)>0.97 && TMath::Abs(Btrk1Eta)<2.39) || (Bpt>15 && Bpt<20 && Btrk1Pt>0.82 && Bchi2cl>0.008 && (BsvpvDistance/BsvpvDisErr)>3.50 && cos(Bdtheta)>0.96 && TMath::Abs(Btrk1Eta)<2.40) || (Bpt>20 && Bpt<30 && Btrk1Pt>0.84 && Bchi2cl>0.014 && (BsvpvDistance/BsvpvDisErr)>3.50 && cos(Bdtheta)>0.60 && TMath::Abs(Btrk1Eta)<2.38) || (Bpt>30 && Bpt<100 && Btrk1Pt>1.06 && Bchi2cl>0.015 && (BsvpvDistance/BsvpvDisErr)>3.52 && cos(Bdtheta)>0.99 && TMath::Abs(Btrk1Eta)<2.37))"

#RECOONLYPP=$CUTPP
TRGPP="(HLT_HIL1DoubleMu0_v1)"
TRGPPMC="(HLT_HIL1DoubleMu0ForPPRef_v1)"
#TRGPPMC="(1)"
OUTPUTFILEPPSAVEHIST="ROOTfiles/hPtSpectrumSaveHistBplusPP.root"
OUTPUTFILEPP="ROOTfiles/hPtSpectrumBplusPP.root"
PREFIXPP="ROOTfiles/hPtSpectrumBplusPP" #IF YOU CHANGE OUTPUTFILEPP, CHANGE PREFIX PP ACCORDINGLY
OUTPUTFILEMCSTUDYPP="ROOTfiles/MCstudiesPP.root"
OUTPUTFILEPlotPP="ROOTfiles/CrossSectionPP.root"
OUTPUTFILEPPDATA="ROOTfiles/data_pp.root"
OUTPUTFILEPPMC="ROOTfiles/mc_pp.root"

#SETTING for NP fit
INPUTMCPP_NP="/data/HeavyFlavourRun2/MC2015/Bntuple/pp/Bntuple20160618_BJpsiMM_5p02TeV_TuneCUETP8M1.root"
CUTPP_NP="$BASECUTPP && Bgen!=23333"
OUTPUTFILEPP_NP="ROOTfiles/NPFitPP.root"
NPFIT_PP="3.12764e1*TMath::Gaus(x,5.33166,3.64663e-2)*(x<5.33166)+(x>=5.33166)*3.12764e1*TMath::Gaus(x,5.33166,1.5204e-1)+2.11124e2*TMath::Erf(-(x-5.14397)/6.43194e-2) + 2.11124e2"

if [ $DOANALYSISPP_FONLL -eq 1 ]; then      
g++ Bplusdsigmadpt.cc $(root-config --cflags --libs) -g -o Bplusdsigmadpt.exe 
./Bplusdsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
rm Bplusdsigmadpt.exe
fi 

if [ $DOANALYSISPP_FITNP -eq 1 ]; then      
g++ fitNP.C $(root-config --cflags --libs) -g -o fitNP.exe 
./fitNP.exe 0 "$INPUTMCPP_NP"  "$INPUTMCPP_NP"  "1" "$CUTPP_NP"   "$SELGENPP"   1   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP_NP"
rm fitNP.exe
fi 

if [ $DOANALYSISPP_FIT -eq 1 ]; then      
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP" "$NPFIT_PP" 0
rm fitB.exe
fi 

if [ $DOANALYSISPP_FITONSAVED -eq 1 ]; then      
g++ fitOnSavedB.C $(root-config --cflags --libs) -g -o fitOnSavedB.exe 
./fitOnSavedB.exe 0 "$OUTPUTFILEPPSAVEHIST"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP" "$NPFIT_PP" 0
rm fitOnSavedB.exe
fi 

if [ $DOANALYSISPP_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP&&$TRGPPMC"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi

if [ $DOANALYSISPP_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEPlotPP" 0 "$LABELPP" 0 "$LUMIPP"
rm CrossSectionRatio.exe
fi

LABELPbPb="PbPb"

#LUMIPbPb=15.5665
#LUMIPbPb=15.17
#350.68(ub-1)*208*208/1000000=15.17

#N_MB = 148356846 lumi_MB_BrilCalc = 7.213*3 lumi_dimuon_BrilCalc = 345.1 TAA = 392.4/(70.*1e9)
#148356846*345.1/(7.213*3) = 2.366003e+09, 2.366003e+09*392.4/(70.*1e9) = 1.326314e+01

#LUMIPbPb=13.14 #PAS
#3.153359e+09*345.1/467.112 = 2329685794.627413, 2329685794.627413*392.4/(70.*1e9) = 13.06
#13.06/0.99*0.996 = 13.14

#NEW TAA = 5.607 20170224
#2329685794.627413*5.607/1e9 = 13.06 same results

#LUMIPbPb=56.564165324 #2018 PbPb 0-100% (SUBJECT TO CHANGE!)
LUMIPbPb=62.546428573 #2018 PbPb 0-90% (SUBJECT TO CHANGE!)
#paper 20170227
#NEW NMB from https://twiki.cern.ch/twiki/pub/CMS/HINUpsilonRaa2016/Jason_MinBiasCounting_2017-02-02.pdf
#2339717742. 2339717742*5.607/1e9 = 13.1187973794
#13.1187973794/0.99*0.996 = 13.1983052423

NMBEVT=9984367691.260341 #Number of MB events (SUBJECT TO CHANGE!)
#NMBEVT=2329685794.627413
ISMCPbPb=0
ISDOWEIGHTPbPb=1

#SELGENPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0"
SELGENPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && ((Gpt>5 && Gpt<10 && TMath::Abs(Gy)>1.5) || (Gpt>10))"
#SELGENPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && TMath::Abs(Gmu1eta)<2.5 && TMath::Abs(Gmu2eta)<2.5 && TMath::Abs(Gtk1eta)<2.5"
#SELGENPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && TMath::Abs(Gmu1eta)<2.5 && TMath::Abs(Gmu2eta)<2.5 && TMath::Abs(Gtk1eta)<2.5 && ((Gpt>5 && Gpt<10 && TMath::Abs(Gy)>1.5) || (Gpt>10))"

#SELGENPbPbACCPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && TMath::Abs(Gtk1eta)<2.4 && ((TMath::Abs(Gmu1eta)<1.2 && Gmu1pt>3.5) || (TMath::Abs(Gmu1eta)>1.2 && TMath::Abs(Gmu1eta)<2.1 && Gmu1pt>5.47-1.89*TMath::Abs(Gmu1eta)) || (TMath::Abs(Gmu1eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu1pt>1.5)) && ((TMath::Abs(Gmu2eta)<1.2 && Gmu2pt>3.5) || (TMath::Abs(Gmu2eta)>1.2 && TMath::Abs(Gmu2eta)<2.1 && Gmu2pt>5.47-1.89*TMath::Abs(Gmu2eta)) || (TMath::Abs(Gmu2eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu2pt>1.5))"
SELGENPbPbACCPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && TMath::Abs(Gtk1eta)<2.4 && ((TMath::Abs(Gmu1eta)<1.2 && Gmu1pt>3.5) || (TMath::Abs(Gmu1eta)>1.2 && TMath::Abs(Gmu1eta)<2.1 && Gmu1pt>5.47-1.89*TMath::Abs(Gmu1eta)) || (TMath::Abs(Gmu1eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu1pt>1.5)) && ((TMath::Abs(Gmu2eta)<1.2 && Gmu2pt>3.5) || (TMath::Abs(Gmu2eta)>1.2 && TMath::Abs(Gmu2eta)<2.1 && Gmu2pt>5.47-1.89*TMath::Abs(Gmu2eta)) || (TMath::Abs(Gmu2eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu2pt>1.5)) && ((Gpt>5 && Gpt<10 && TMath::Abs(Gy)>1.5) || (Gpt>10))"
#SELGENPbPbACCPbPb="TMath::Abs(Gy)<2.4 && TMath::Abs(GpdgId)==521 && GisSignal==1 && GcollisionId==0 && TMath::Abs(Gmu1eta)<2.5 && TMath::Abs(Gmu2eta)<2.5 && TMath::Abs(Gtk1eta)<2.4 && ((TMath::Abs(Gmu1eta)<1.2 && Gmu1pt>3.5) || (TMath::Abs(Gmu1eta)>1.2 && TMath::Abs(Gmu1eta)<2.1 && Gmu1pt>5.47-1.89*TMath::Abs(Gmu1eta)) || (TMath::Abs(Gmu1eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu1pt>1.5)) && ((TMath::Abs(Gmu2eta)<1.2 && Gmu2pt>3.5) || (TMath::Abs(Gmu2eta)>1.2 && TMath::Abs(Gmu2eta)<2.1 && Gmu2pt>5.47-1.89*TMath::Abs(Gmu2eta)) || (TMath::Abs(Gmu2eta)>2.1 && TMath::Abs(Gmu2eta)<2.4 && Gmu2pt>1.5)) && ((Gpt>5 && Gpt<10 && TMath::Abs(Gy)>1.5) || (Gpt>10))"

RECOONLYPbPb="pprimaryVertexFilter && phfCoincFilter2Th4 && pclusterCompatibilityFilter && Btrk1Pt>0.9 && Bpt>3.0 && (BsvpvDistance/BsvpvDisErr)>2.0 && Bchi2cl>0.05 && TMath::Abs(Btrk1Eta)<2.4 && TMath::Abs(By)<2.4 && TMath::Abs(PVz)<15 && Bmass>5 && Bmass<6 && TMath::Abs(Bmumumass-3.096900)<0.15 && Bmu1SoftMuID && Bmu2SoftMuID && Bmu1isAcc && Bmu2isAcc && Bmu1isTriggered && Bmu2isTriggered && (Btrk1PixelHit+Btrk1StripHit)>=11 && (Btrk1Chi2ndf/(Btrk1nStripLayer+Btrk1nPixelLayer))<0.18 && TMath::Abs(Btrk1PtErr/Btrk1Pt)<0.1 && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>12 && cos(Bdtheta)>0.95) || (Bpt>7 && Bpt<10 && (BsvpvDistance/BsvpvDisErr)>9.0 && cos(Bdtheta)>0.92) || (Bpt>10 && Bpt<60)) && ((Bpt>5 && Bpt<7 && BDT_5_7>0.02) || (Bpt>7 && Bpt<10 && BDT_7_10>0.03) || (Bpt>10 && Bpt<15 && BDT_10_15>0.09) || (Bpt>15 && Bpt<20 && BDT_15_20>0.07) || (Bpt>20 && Bpt<30 && BDT_20_30>0.10) || (Bpt>30 && Bpt<40 && BDT_30_40>0.16) || (Bpt>40 && Bpt<50 && BDT_40_50>0.20) || (Bpt>50 && Bpt<60 && BDT_50_60>0.27))"

#GA
BASECUTPbPb="pprimaryVertexFilter && phfCoincFilter2Th4 && pclusterCompatibilityFilter && Btrk1Pt>0.9 && Bpt>5.0 && (BsvpvDistance/BsvpvDisErr)>2.0 && Bchi2cl>0.05 && TMath::Abs(Btrk1Eta)<2.4 && TMath::Abs(By)<2.4 && TMath::Abs(PVz)<15 && Bmass>5 && Bmass<6 && TMath::Abs(Bmumumass-3.096900)<0.15 && Bmu1SoftMuID && Bmu2SoftMuID && Bmu1isAcc && Bmu2isAcc && Bmu1isTriggered && Bmu2isTriggered && (Btrk1PixelHit+Btrk1StripHit)>=11 && (Btrk1Chi2ndf/(Btrk1nStripLayer+Btrk1nPixelLayer))<0.18 && TMath::Abs(Btrk1PtErr/Btrk1Pt)<0.1 && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>12 && cos(Bdtheta)>0.95) || (Bpt>7 && Bpt<10 && (BsvpvDistance/BsvpvDisErr)>9.0 && cos(Bdtheta)>0.92) || (Bpt>10 && Bpt<60))" ## pre-filter (MuonJSON)
#BASECUTPbPb="pprimaryVertexFilter && phfCoincFilter2Th4 && pclusterCompatibilityFilter && Btrk1Pt>0.9 && Bpt>5.0 && (BsvpvDistance/BsvpvDisErr)>2.0 && Bchi2cl>0.05 && TMath::Abs(Btrk1Eta)<2.4 && TMath::Abs(By)<2.4 && TMath::Abs(PVz)<15 && Bmass>5 && Bmass<6 && TMath::Abs(Bmumumass-3.096900)<0.15 && Bmu1SoftMuID && Bmu2SoftMuID && ((TMath::Abs(Bmu1eta)<1.2 && Bmu1pt>3.5) || (TMath::Abs(Bmu1eta)>1.2 && TMath::Abs(Bmu1eta)<2.1 && Bmu1pt>5.47-1.89*TMath::Abs(Bmu1eta)) || (TMath::Abs(Bmu1eta)>2.1 && TMath::Abs(Bmu1eta)<2.4 && Bmu1pt>1.5)) && ((TMath::Abs(Bmu2eta)<1.2 && Bmu2pt>3.5) || (TMath::Abs(Bmu2eta)>1.2 && TMath::Abs(Bmu2eta)<2.1 && Bmu2pt>5.47-1.89*TMath::Abs(Bmu2eta)) || (TMath::Abs(Bmu2eta)>2.1 && TMath::Abs(Bmu2eta)<2.4 && Bmu2pt>1.5)) && Bmu1isTriggered && Bmu2isTriggered && (Btrk1PixelHit+Btrk1StripHit)>=11 && (Btrk1Chi2ndf/(Btrk1nStripLayer+Btrk1nPixelLayer))<0.18 && TMath::Abs(Btrk1PtErr/Btrk1Pt)<0.1 && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>12 && cos(Bdtheta)>0.95) || (Bpt>7 && Bpt<60))" ## pre-filter
#CUTPbPb="$BASECUTPbPb"
CUTPbPb="$BASECUTPbPb && ((Bpt>5 && Bpt<7 && BDT_5_7>0.02) || (Bpt>7 && Bpt<10 && BDT_7_10>0.03) || (Bpt>10 && Bpt<15 && BDT_10_15>0.09) || (Bpt>15 && Bpt<20 && BDT_15_20>0.07) || (Bpt>20 && Bpt<30 && BDT_20_30>0.10) || (Bpt>30 && Bpt<40 && BDT_30_40>0.16) || (Bpt>40 && Bpt<50 && BDT_40_50>0.20) || (Bpt>50 && Bpt<60 && BDT_50_60>0.27))" ## (MuonJSON)
#CUTPbPb="$BASECUTPbPb && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>12 && cos(Bdtheta)>0.95 && BDT_5_7>0.07) || (Bpt>7 && Bpt<10 && BDT_7_10>0.08) || (Bpt>10 && Bpt<15 && BDT_10_15>0.09) || (Bpt>15 && Bpt<20 && BDT_15_20>0.09) || (Bpt>20 && Bpt<30 && BDT_20_30>0.07) || (Bpt>30 && Bpt<50 && BDT_30_50>0.12) || (Bpt>50 && Bpt<100 && BDT_50_100>0.24))"
#CUTPbPb="$BASECUTPbPb && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>16.457 && cos(Bdtheta)>0.987 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.005 && Btrk1Pt>1.092 && Bchi2cl>0.065) || (Bpt>7 && Bpt<10 && (BsvpvDistance/BsvpvDisErr)>12.714 && cos(Bdtheta)>0.947 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>2.928 && Btrk1Pt>0.838 && Bchi2cl>0.053) || (Bpt>10 && Bpt<15 && (BsvpvDistance/BsvpvDisErr)>9.086 && cos(Bdtheta)>0.994 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>1.540 && Btrk1Pt>1.262 && Bchi2cl>0.055) || (Bpt>15 && Bpt<20 && (BsvpvDistance/BsvpvDisErr)>7.587 && cos(Bdtheta)>0.757 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.000 && Btrk1Pt>1.813 && Bchi2cl>0.056) || (Bpt>20 && Bpt<30 && (BsvpvDistance/BsvpvDisErr)>4.004 && cos(Bdtheta)>0.996 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.000 && Btrk1Pt>1.822 && Bchi2cl>0.050) || (Bpt>30 && Bpt<50 && (BsvpvDistance/BsvpvDisErr)>2.000 && cos(Bdtheta)>0.998 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.000 && Btrk1Pt>2.046 && Bchi2cl>0.050) || (Bpt>50 && Bpt<100 && (BsvpvDistance/BsvpvDisErr)>4.084 && cos(Bdtheta)>-0.112 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.000 && Btrk1Pt>1.645 && Bchi2cl>0.050))"
#CUTPbPb="$BASECUTPbPb && ((Bpt>5 && Bpt<7 && (BsvpvDistance/BsvpvDisErr)>13.028 && cos(Bdtheta)>-0.785 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>3.664 && Btrk1Pt>1.104 && Bchi2cl>0.224) || (Bpt>7 && Bpt<10 && (BsvpvDistance/BsvpvDisErr)>6.151 && cos(Bdtheta)>-0.279 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>3.379 && TMath::Abs(Btrk1Dz1/Btrk1DzError1)>0.628 && Btrk1Pt>1.185) || (Bpt>10 && Bpt<15 && (BsvpvDistance/BsvpvDisErr)>9.641 && cos(Bdtheta)>-0.510 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>3.464 && Btrk1Pt>1.287 && Bchi2cl>0.185) || (Bpt>15 && Bpt<20 && (BsvpvDistance/BsvpvDisErr)>6.520 && cos(Bdtheta)>0.971 && Btrk1Pt>1.837 && Bchi2cl>0.089) || (Bpt>20 && Bpt<30 && (BsvpvDistance/BsvpvDisErr)>4.171 && cos(Bdtheta)>0.998 && Btrk1Pt>1.692) || (Bpt>30 && Bpt<50 && (BsvpvDistance/BsvpvDisErr)>3.850 && cos(Bdtheta)>0.571 && Btrk1Pt>1.723) || (Bpt>50 && Bpt<100 && cos(Bdtheta)>0.743 && TMath::Abs(Btrk1Dxy1/Btrk1DxyError1)>0.203 && Btrk1Pt>2.973 && Bchi2cl>0.062))" ## private MC

#TRGPbPbMC="(HLT_HIL1DoubleMu0_v1)"
#TRGPbPbMC="(HLT_HIL1DoubleMu0_v1 || HLT_HIL1DoubleMu0_part1_v1 || HLT_HIL1DoubleMu0_part2_v1 || HLT_HIL1DoubleMu0_part3_v1)"
TRGPbPb="(HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1)"
TRGPbPbMC="(HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1)"
OUTPUTFILEPbPbSAVEHIST="ROOTfiles/hPtSpectrumSaveHistBplusPbPb.root"
OUTPUTFILEPbPb="ROOTfiles/hPtSpectrumBplusPbPb.root"
PREFIXPbPb="ROOTfiles/hPtSpectrumBplusPbPb" #IF YOU CHANGE OUTPUTFILEPbPb, CHANGE PREFIXPbPb ACCORDINGLY
OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb.root"
OUTPUTFILEPlotPbPb="ROOTfiles/CrossSectionPbPb.root"
OUTPUTFILEPbPbDATA="ROOTfiles/data_PbPb.root"
OUTPUTFILEPbPbMC="ROOTfiles/mc_PbPb.root"

#SETTING for NP fit
INPUTMCPbPb_NP="/raid5/data/gwangjun/crab_Bfinder_20190624_Hydjet_Pythia8_Official_Nonprompt_Bplus_1033p1_pt3tkpt0p7dls2_allpthat_pthatweight.root"
CUTPbPb_NP="$CUTPbPb && Bgen!=23333"
OUTPUTFILEPbPb_NP="ROOTfiles/NPFitPbPb.root"
#NPFIT_PbPb="3.39711e1*TMath::Gaus(x,5.35002e0,3.87952e-2)*(x<5.35002e0)+(x>=5.35002e0)*3.39711e1*TMath::Gaus(x,5.35002e0,1.14232e-1)+2.16376e2*TMath::Erf(-(x-5.14189)/8.66243e-2) + 2.16376e2"
#NPFIT_PbPb="148.603007*TMath::Erf(-(x-5.141892)/0.044578)+148.603007+14.048675*(0.729485*TMath::Gaus(x,5.337440,0.239260)/(sqrt(2*3.14159)*0.239260)+(1-0.729485)*TMath::Gaus(x,5.337440,0.040560)/(sqrt(2*3.14159)*0.040560))"
#NPFIT_PbPb="787.503468*TMath::Erf(-(x-5.105477)/0.080109)+787.503468+61.466850*(0.365515*TMath::Gaus(x,5.340806,0.056890)/(sqrt(2*3.14159)*0.056890)+(1-0.365515)*TMath::Gaus(x,5.340806,0.279220)/(sqrt(2*3.14159)*0.279220))+43.437777*TMath::Gaus(x,5.105719,0.025197)/(sqrt(2*3.14159)*0.025197)"
NPFIT_PbPb="701.019629*TMath::Erf((x-5.140349)/-0.035471)+701.019629+16.946432*TMath::Gaus(x,5.343914,0.040000)/(sqrt(2*3.14159)*0.040000)"

if [ $DOANALYSISPbPb_FITNP -eq 1 ]; then      
g++ fitNP.C $(root-config --cflags --libs) -g -o fitNP.exe 
./fitNP.exe 1 "$INPUTMCPbPb_NP"  "$INPUTMCPbPb_NP"  "$TRGPbPb" "$CUTPbPb_NP"   "$SELGENPbPb"   1   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb_NP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitNP.exe
fi 

if [ $DOANALYSISPbPb_FIT -eq 1 ]; then      
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitB.exe
fi 

if [ $DOANALYSISPbPb_FITONSAVED -eq 1 ]; then      
g++ fitOnSavedB.C $(root-config --cflags --libs) -g -o fitOnSavedB.exe 
./fitOnSavedB.exe 1 "$OUTPUTFILEPbPbSAVEHIST"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitOnSavedB.exe
fi 

if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi






if [ $DOANALYSISPbPb_MCSTUDYSYST -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 

echo "Now Working on 0 - 90"

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 1 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 2 0 90

echo "Now Working on 30 - 90"


./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 1 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 2 30 90

echo "Now Working on 0 - 30"


./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 1 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 2 0 30


rm MCefficiency.exe
fi







if [ $DOANALYSISPbPb_MCSTUDYEFF -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 

echo "Now Working on sPLOT"

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 3 0 90

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 3 0 30

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 3 30 90


echo "Now Working on 0 - 90"

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 4 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 5 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 6 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 7 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 8 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 9 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 10 0 90


echo "Now Working on 0 - 30"

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 4 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 5 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 6 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 7 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 8 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 9 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 10 0 30



echo "Now Working on 30 - 90"

./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 4 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 5 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 6 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 7 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 8 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 9 30 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 10 30 90



rm MCefficiency.exe
fi











if [ $DOANALYSISPbPb_AVERAGEEFF -eq 1 ]; then
g++ AverageEff.C $(root-config --cflags --libs) -g -o AverageEff.exe
./AverageEff.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm AverageEff.exe
fi

if [ $DOANALYSISPbPb_AVERAGEEFF_TRACK -eq 1 ]; then
g++ AverageEff_trk.C $(root-config --cflags --libs) -g -o AverageEff_trk.exe
./AverageEff_trk.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm AverageEff_trk.exe
fi

if [ $DOANALYSISPbPb_AVERAGEEFF_TOY -eq 1 ]; then
g++ AverageEff_toy.C $(root-config --cflags --libs) -g -o AverageEff_toy.exe
./AverageEff_toy.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm AverageEff_toy.exe
fi

if [ $DOANALYSISPbPb_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEPlotPbPb" 1 "$LABELPbPb" 0 "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe
fi

if [ $DORAA -eq 1 ]; then
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor.exe
fi

if [ $DORAA_POSTPRL -eq 1 ]; then
g++ NuclearModificationFactor_postPRL.C $(root-config --cflags --libs) -g -o NuclearModificationFactor_postPRL.exe
./NuclearModificationFactor_postPRL.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor_postPRL.exe
fi


#######
#CENTRALITY RAPIDITY
#######
OUTPUTFILEPP_Y="ROOTfiles/hPtSpectrumBplusPP_Y.root"
if [ $DOANALYSISPP_FIT_Y -eq 1 ]; then
g++ fitBY.C $(root-config --cflags --libs) -g -o fitBY.exe
./fitBY.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP&&Bpt>7"  "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP_Y" "$NPFIT_PP" 0
rm fitBY.exe
fi

OUTPUTFILEPbPb_Y="ROOTfiles/hPtSpectrumBplusPbPb_Y.root"
if [ $DOANALYSISPbPb_FIT_Y -eq 1 ]; then      
g++ fitBY.C $(root-config --cflags --libs) -g -o fitBY.exe 
./fitBY.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"  "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb_Y" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitBY.exe
fi 

OUTPUTFILEMCSTUDYPP_Y="ROOTfiles/MCstudiesPP_Y.root"
if [ $DOANALYSISPP_MCSTUDY_Y -eq 1 ]; then
g++ MCefficiencyY.C $(root-config --cflags --libs) -g -o MCefficiencyY.exe
./MCefficiencyY.exe  0 "$INPUTMCPP"  "$SELGENPP&&Gpt>7&&Gpt<50" "$SELGENPPACCPP&&Gpt>7&&Gpt<50"  "$RECOONLYPP" "$CUTPP&&$TRGPPMC"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP_Y" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiencyY.exe
fi

OUTPUTFILEMCSTUDYPbPb_Y="ROOTfiles/MCstudiesPbPb_Y.root"
if [ $DOANALYSISPbPb_MCSTUDY_Y -eq 1 ]; then
g++ MCefficiencyY.C $(root-config --cflags --libs) -g -o MCefficiencyY.exe
./MCefficiencyY.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb_Y" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiencyY.exe
fi

OUTPUTFILERAA_Y="ROOTfiles/outputRAA_Y.root"
if [ $DORAA_Y -eq 1 ]; then
g++ NuclearModificationFactorY.C $(root-config --cflags --libs) -g -o NuclearModificationFactorY.exe
./NuclearModificationFactorY.exe "$OUTPUTFILEPP_Y" "$OUTPUTFILEPbPb_Y" "$OUTPUTFILEMCSTUDYPP_Y" "$OUTPUTFILEMCSTUDYPbPb_Y" "$LABELPbPb" "$OUTPUTFILERAA_Y" 0 "$LUMIPP" "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactorY.exe
fi

#######
#CENTRALITY RAA
#######

OUTPUTFILEPP_INC="ROOTfiles/hPtSpectrumBplusPP_INC.root"
if [ $DOANALYSISPP_FIT_INC -eq 1 ]; then      
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "ppInc"  "$OUTPUTFILEPP_INC" "$NPFIT_PP" 0
rm fitB.exe
fi 

OUTPUTFILEMCSTUDYPP_INC="ROOTfiles/MCstudiesPP_INC.root"
if [ $DOANALYSISPP_MCSTUDY_INC -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP&&$TRGPPMC"  "ppInc" "$OUTPUTFILEMCSTUDYPP_INC" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi

OUTPUTFILEPbPb_CENT="ROOTfiles/hPtSpectrumBplusPbPb_CENT.root"
if [ $DOANALYSISPbPb_FIT_CENT -eq 1 ]; then
g++ fitBCent.C $(root-config --cflags --libs) -g -o fitBCent.exe
./fitBCent.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb_CENT" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitBCent.exe
fi

OUTPUTFILEMCSTUDYPbPb_CENT="ROOTfiles/MCstudiesPbPb_CENT.root"
if [ $DOANALYSISPbPb_MCSTUDY_CENT -eq 1 ]; then      
g++ MCefficiencyCent.C $(root-config --cflags --libs) -g -o MCefficiencyCent.exe 
./MCefficiencyCent.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb_CENT" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiencyCent.exe
fi

OUTPUTFILEPlotPbPb_CENT="ROOTfiles/CrossSectionPbPb_CENT.root"
if [ $DOANALYSISPbPb_CROSS_CENT -eq 1 ]; then
g++ CrossSectionRatioCent.C $(root-config --cflags --libs) -g -o CrossSectionRatioCent.exe
./CrossSectionRatioCent.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPb_CENT" "$OUTPUTFILEMCSTUDYPbPb_CENT" "$OUTPUTFILEPlotPbPb_CENT" 1 "$LABELPbPb" 0 "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatioCent.exe
fi

OUTPUTFILERAA_CENT="ROOTfiles/outputRAA_CENT.root"
if [ $DORAA_CENT -eq 1 ]; then
g++ NuclearModificationFactorCent.C $(root-config --cflags --libs) -g -o NuclearModificationFactorCent.exe
./NuclearModificationFactorCent.exe "$OUTPUTFILEPP_INC" "$OUTPUTFILEPbPb_CENT" "$OUTPUTFILEMCSTUDYPP_INC" "$OUTPUTFILEMCSTUDYPbPb_CENT" "$LABELPbPb" "$OUTPUTFILERAA_CENT" 0 "$LUMIPP" "$NMBEVT" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactorCent.exe
fi

OUTPUTFILEMCSTUDYPP_FINE="ROOTfiles/MCstudiesPP_Fine.root"
if [ $DOANALYSISPP_MCSTUDY_FINE -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe
./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP&&$TRGPPMC"  "ppFine" "$OUTPUTFILEMCSTUDYPP_FINE" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi

if [ $DOANALYSISPP_EFFFIT -eq 1 ]; then
g++ EfficiencyFit.C $(root-config --cflags --libs) -g -o EfficiencyFit.exe
./EfficiencyFit.exe  "$OUTPUTFILEMCSTUDYPP_FINE" "PP_Fine"
rm EfficiencyFit.exe
fi

OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN0to20="ROOTfiles/MCstudiesPbPb_Fine_hiBin0to20.root"
OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN20to60="ROOTfiles/MCstudiesPbPb_Fine_hiBin20to60.root"
OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN60to100="ROOTfiles/MCstudiesPbPb_Fine_hiBin60to100.root"
OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN100to200="ROOTfiles/MCstudiesPbPb_Fine_hiBin100to200.root"
if [ $DOANALYSISPbPb_MCSTUDY_FINE_HIBIN -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe
CentSel="hiBin>=0&&hiBin<20"
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb&&$CentSel" "$SELGENPbPbACCPbPb&&$CentSel"  "$RECOONLYPbPb&&$CentSel" "$CUTPbPb&&$TRGPbPbMC&&$CentSel"  "PbPbFine_hiBin0to20" "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN0to20" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
CentSel="hiBin>=20&&hiBin<60"
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb&&$CentSel" "$SELGENPbPbACCPbPb&&$CentSel"  "$RECOONLYPbPb&&$CentSel" "$CUTPbPb&&$TRGPbPbMC&&$CentSel"  "PbPbFine_hiBin20to60" "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN20to60" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
CentSel="hiBin>=60&&hiBin<100"
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb&&$CentSel" "$SELGENPbPbACCPbPb&&$CentSel"  "$RECOONLYPbPb&&$CentSel" "$CUTPbPb&&$TRGPbPbMC&&$CentSel"  "PbPbFine_hiBin60to100" "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN60to100" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
CentSel="hiBin>=100&&hiBin<=200"
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb&&$CentSel" "$SELGENPbPbACCPbPb&&$CentSel"  "$RECOONLYPbPb&&$CentSel" "$CUTPbPb&&$TRGPbPbMC&&$CentSel"  "PbPbFine_hiBin100to200" "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN100to200" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi

if [ $DOANALYSISPbPb_EFFFIT -eq 1 ]; then
g++ EfficiencyFit.C $(root-config --cflags --libs) -g -o EfficiencyFit.exe
./EfficiencyFit.exe  "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN0to20" "PbPb_Fine_HIBIN0to20"
./EfficiencyFit.exe  "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN20to60" "PbPb_Fine_HIBIN20to60"
./EfficiencyFit.exe  "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN60to100" "PbPb_Fine_HIBIN60to100"
./EfficiencyFit.exe  "$OUTPUTFILEMCSTUDYPbPb_FINE_HIBIN100to200" "PbPb_Fine_HIBIN100to200"
rm EfficiencyFit.exe
fi

OUTPUTFILEPP_INC_EFFCOR="ROOTfiles/hPtSpectrumBplusPP_INC_EFFCOR.root"
if [ $DOANALYSISPP_FIT_INC_EFFCOR -eq 1 ]; then      
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "ppInc"  "$OUTPUTFILEPP_INC_EFFCOR" "$NPFIT_PP" 1
rm fitB.exe
fi 

OUTPUTFILEPbPb_CENT_EFFCOR="ROOTfiles/hPtSpectrumBplusPbPb_CENT_EFFCOR.root"
if [ $DOANALYSISPbPb_FIT_CENT_EFFCOR -eq 1 ]; then
g++ fitBCent.C $(root-config --cflags --libs) -g -o fitBCent.exe
./fitBCent.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb&&Bpt>7"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPb_CENT_EFFCOR" "$NPFIT_PbPb" 1
rm fitBCent.exe
fi

OUTPUTFILERAA_CENT_EFFCOR="ROOTfiles/outputRAA_CENT_EFFCOR.root"
if [ $DORAA_CENT_EFFCOR -eq 1 ]; then
g++ NuclearModificationFactorCent.C $(root-config --cflags --libs) -g -o NuclearModificationFactorCent.exe
./NuclearModificationFactorCent.exe "$OUTPUTFILEPP_INC_EFFCOR" "$OUTPUTFILEPbPb_CENT_EFFCOR" "$OUTPUTFILEMCSTUDYPP_INC" "$OUTPUTFILEMCSTUDYPbPb_CENT" "$LABELPbPb" "$OUTPUTFILERAA_CENT_EFFCOR" 1 "$LUMIPP" "$NMBEVT" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactorCent.exe
fi

###pp fit EFFCOR test
OUTPUTFILEPP_EFFCOR="ROOTfiles/hPtSpectrumBplusPP_EFFCOR.root"
if [ $DOANALYSISPP_FIT_EFFCOR -eq 1 ]; then      
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP_EFFCOR" "$NPFIT_PP" 1
rm fitB.exe
fi 

OUTPUTFILEPlotPP_EFFCOR="ROOTfiles/CrossSectionPP_EFFCOR.root"
if [ $DOANALYSISPP_CROSS_EFFCOR -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP_EFFCOR" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEPlotPP_EFFCOR" 0 "$LABELPP" 1 "$LUMIPP"
rm CrossSectionRatio.exe
fi

#MEAN COMPARISON

if [ $DOCOMPARE -eq 1 ]; then
g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 1 "$INPUTDATAPbPb"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   0   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPbDATA" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitB.exe

g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 1 "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMC" "$CUTPbPb"   "$SELGENPbPb"   1   1   "$ISDOWEIGHTPbPb"   "$LABELPbPb"  "$OUTPUTFILEPbPbMC" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitB.exe

g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   0   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPPDATA" "$NPFIT_PP" 0
rm fitB.exe

g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
./fitB.exe 0 "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMC" "$CUTPP"   "$SELGENPP"   1   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPPMC" "$NPFIT_PP" 0
rm fitB.exe

g++ comparison.C $(root-config --cflags --libs) -g -o comparison.exe 
./comparison.exe 
rm comparison.exe
fi


#FIT VARIATION

if [ $DOSAVEHISTPP -eq 1 ]; then
g++ savehisto.C $(root-config --cflags --libs) -g -o savehisto.exe 
./savehisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "$CUTPP" "$ISMCPP" "$ISDOWEIGHTPP" "$LABELPP"
rm savehisto.exe
fi

if [ $DOSAVEHISTPbPb -eq 1 ]; then
g++ savehisto.C $(root-config --cflags --libs) -g -o savehisto.exe 
./savehisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "$CUTPbPb" "$ISMCPbPb" "$ISDOWEIGHTPbPb" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm savehisto.exe
fi

if [ $DOVARIATION -eq 1 ]; then
#g++ fitBvar.C $(root-config --cflags --libs) -g -o fitBvar.exe 
#./fitBvar.exe "$LABELPP" "$PREFIXPP" "$OUTPUTFILEPP_NP"
#rm fitBvar.exe

g++ fitBvar.C $(root-config --cflags --libs) -g -o fitBvar.exe 
./fitBvar.exe "$LABELPbPb" "$PREFIXPbPb" "$OUTPUTFILEPbPb_NP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitBvar.exe
fi

# MVA COMPARISON

if [ $SAVEMVAPP -eq 1 ]; then
g++ mvahisto.C $(root-config --cflags --libs) -g -o mvahisto.exe 
./mvahisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "$CUTPP" "$ISMCPP" "$ISDOWEIGHTPP" "$LABELPP"
rm mvahisto.exe
fi

if [ $SAVEMVAPbPb -eq 1 ]; then
g++ mvahisto.C $(root-config --cflags --libs) -g -o mvahisto.exe 
./mvahisto.exe "$INPUTDATAPbPb" "$INPUTMCPbPb" "$TRGPbPb" "$CUTPbPb" "$ISMCPbPb" "$ISDOWEIGHTPbPb" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm mvahisto.exe
fi

if [ $PLOTMVA -eq 1 ]; then
g++ fitBmva.C $(root-config --cflags --libs) -g -o fitBmva.exe 
./fitBmva.exe "$LABELPP" "$PREFIXPP" "$OUTPUTFILEPP_NP"
rm fitBmva.exe

g++ fitBmva.C $(root-config --cflags --libs) -g -o fitBmva.exe 
./fitBmva.exe "$LABELPbPb" "$PREFIXPbPb" "$OUTPUTFILEPbPb_NP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitBmva.exe
fi

if [ $DOClosure -eq 1 ]; then      

OUTPUTFILEPPMCClosure="ROOTfiles/hPtSpectrumBplusPPMCClosure.root"
LUMIPPMCClosure=1
ISMCPPMCClosure=1
ISDOWEIGHTPPMCClosure=0
TRGPPMCClosure="1"
LABELPPMCClosure="PPMCClosure"

#g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
#./fitB.exe 0 "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMCClosure" "$CUTPP"   "$SELGENPP"   "$ISMCPPMCClosure"   "$LUMIPPMCClosure"   "$ISDOWEIGHTPPMCClosure"   "$LABELPPMCClosure"  "$OUTPUTFILEPPMCClosure" "$NPFIT_PP" 0
#rm fitB.exe

#g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
#./ClosureTest.exe "$OUTPUTFILEPPMCClosure" "$LABELPP"
#rm ClosureTest.exe

#OUTPUTFILEPbPbMCClosure="ROOTfiles/hPtSpectrumBplusPbPb.root"
OUTPUTFILEPbPbMCClosure="ROOTfiles/hPtSpectrumBplusPbPbMCClosure.root"
LUMIPbPbMCClosure=1
ISMCPbPbMCClosure=1
ISDOWEIGHTPbPbMCClosure=0
TRGPbPbMCClosure="(HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1)"
LABELPbPbMCClosure="PbPbMCClosure"

#g++ fitB.C $(root-config --cflags --libs) -g -o fitB.exe 
#./fitB.exe 1 "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMCClosure" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPbMCClosure"   "$LUMIPbPbMCClosure"   "$ISDOWEIGHTPbPbMCClosure"   "$LABELPbPbMCClosure"  "$OUTPUTFILEPbPbMCClosure" "$NPFIT_PbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
#rm fitB.exe

g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMCClosure" "$LABELPbPb"
rm ClosureTest.exe
fi
