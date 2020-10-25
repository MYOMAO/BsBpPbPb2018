#!/bin/bash
#source clean.sh
CENTPbPbMIN=0
CENTPbPbMAX=90
#Central point of the analysis
DOANALYSISPbPb_MCSTUDY=1
DOANALYSISPbPb_MCSTUDYPTSYST=0
DOANALYSISPbPb_MCSTUDYEFFSYST=0




# 2018 PbPb
INPUTMCPbPb="../../../../BsBPInputSamples/BPMC.root"




LABELPbPb="PbPb"

LUMIPbPb=62.546428573 #2018 PbPb 0-90% (SUBJECT TO CHANGE!)
NMBEVT=9984367691.260341 #Number of MB events (SUBJECT TO CHANGE!)
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






if [ $DOANALYSISPbPb_MCSTUDYPTSYST -eq 1 ]; then      
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




if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 


./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 0 90
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 0 30
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPbPbACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 30 90


rm MCefficiency.exe

fi










if [ $DOANALYSISPbPb_MCSTUDYEFFSYST -eq 1 ]; then      
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





