DOANALYSISPbPb_MCSTUDY=1
DOANALYSISPbPb_MCSTUDY_PTSHAPE=0
DOANALYSISPbPb_MCSTUDY_NOTRG=0
DOANALYSISPbPb_MCSTUDY_NOTNP=0


INPUTMCPbPbCANDWISE="../../../../BsBPInputSamples/BsMC.root"

LABELPbPb="PbPb"
LUMIPbPb=56.564165324
NMBEVT=2329685794.627413
ISMCPbPb=0
ISDOWEIGHTPbPb=1
#SELGENPbPb="TMath::Abs(Gy)<2.4&&TMath::Abs(GpdgId)==531&&GisSignal>0"
SELGENPbPb="TMath::Abs(Gy)<2.4&&TMath::Abs(GpdgId)==531&&GisSignal>0 &&((Gpt > 5 && Gpt < 10 && TMath::Abs(Gy)>1.5)||(Gpt > 10 && Gpt < 50 && TMath::Abs(Gy)>0))" 

SELGENPbPbACCPbPb="TMath::Abs(Gy)<2.4&&abs(GpdgId)==531&&GisSignal>0&&((Gpt > 5 && Gpt < 10 && TMath::Abs(Gy)>1.5)||(Gpt > 10 && Gpt < 50 && TMath::Abs(Gy)>0))&&((TMath::Abs(Gmu1eta)<1.2&&Gmu1pt>3.5)||(TMath::Abs(Gmu1eta)>1.2&&TMath::Abs(Gmu1eta)<2.1&&Gmu1pt>(5.47-1.89*TMath::Abs(Gmu1eta)))||(TMath::Abs(Gmu1eta)>2.1&&TMath::Abs(Gmu1eta)<2.4&&Gmu1pt>1.5))&&((TMath::Abs(Gmu2eta)<1.2&&Gmu2pt>3.5)||(TMath::Abs(Gmu2eta)>1.2&&TMath::Abs(Gmu2eta)<2.1&&Gmu2pt>(5.47-1.89*TMath::Abs(Gmu2eta)))||(TMath::Abs(Gmu2eta)>2.1&&TMath::Abs(Gmu2eta)<2.4&&Gmu2pt>1.5))&&Gtk1pt>0.9&&Gtk2pt>0.9&&TMath::Abs(Gtk1eta)<2.4&&TMath::Abs(Gtk2eta)<2.4"



BASECUTPbPb="(hiBin < 181) && Btrk1Pt > 0.9 && Btrk2Pt > 0.9 && Bchi2cl > 0.05 && BsvpvDistance/BsvpvDisErr > 2.0 && Bpt > 5 && abs(Btrk1Eta-0.0) < 2.4  && abs(Btrk2Eta-0.0) < 2.4 && (TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&((abs(Bmu1eta)<1.2&&Bmu1pt>3.5)||(abs(Bmu1eta)>1.2&&abs(Bmu1eta)<2.1&&Bmu1pt>(5.47-1.89*abs(Bmu1eta)))||(abs(Bmu1eta)>2.1&&abs(Bmu1eta)<2.4&&Bmu1pt>1.5))&&((abs(Bmu2eta)<1.2&&Bmu2pt>3.5)||(abs(Bmu2eta)>1.2&&abs(Bmu2eta)<2.1&&Bmu2pt>(5.47-1.89*abs(Bmu2eta)))||(abs(Bmu2eta)>2.1&&abs(Bmu2eta)<2.4&&Bmu2pt>1.5))&&Bmu1TMOneStationTight&&Bmu2TMOneStationTight&&Bmu1InPixelLayer>0&&(Bmu1InPixelLayer+Bmu1InStripLayer)>5&&Bmu2InPixelLayer>0&&(Bmu2InPixelLayer+Bmu2InStripLayer)>5&&Bmu1dxyPV<0.3&&Bmu2dxyPV<0.3&&Bmu1dzPV<20&&Bmu2dzPV<20&&Bmu1isTrackerMuon&&Bmu2isTrackerMuon&&Bmu1isGlobalMuon&&Bmu2isGlobalMuon&&Btrk1highPurity&&Btrk2highPurity&&abs(Btrk1Eta)<2.4&&abs(Btrk2Eta)<2.4&&Btrk1Pt>1.&&Btrk2Pt>1.&&abs(Btktkmass-1.019455)<0.015) && (abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter) && (Btrk1PixelHit + Btrk1StripHit > 10) && (Btrk2PixelHit + Btrk2StripHit > 10) && (Btrk1PtErr/Btrk1Pt < 0.1)&& (Btrk2PtErr/Btrk2Pt < 0.1) && Btrk1Chi2ndf/(Btrk1nStripLayer+Btrk1nPixelLayer) < 0.18 && Btrk2Chi2ndf/(Btrk2nStripLayer+Btrk2nPixelLayer) < 0.18"

CUTPbPb=${BASECUTPbPb}"&&((Bpt>5&&Bpt<10&&BDT_pt_5_10>0.32)||(Bpt>10&&Bpt<15&&BDT_pt_10_15> 0.29)||(Bpt>15&&Bpt<20&&BDT_pt_15_20>0.35)||(Bpt>20&&Bpt<50&&BDT_pt_20_50>0.33))"
CUTPbPbVAR=${BASECUTPbPb}"&&((Bpt>5&&Bpt<10&&BDT_pt_5_10>0.0)||(Bpt>10&&Bpt<15&&BDT_pt_10_15> 0.0)||(Bpt>15&&Bpt<20&&BDT_pt_15_20>0.0)||(Bpt>20&&Bpt<50&&BDT_pt_20_50>0.0))"
CUTPbPbVAR=${CUTPbPbVAR}"&&abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter && phfCoincFilter2Th4"


CUTPbPb=${CUTPbPb}"&&abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter && phfCoincFilter2Th4  && (Bmu1isTriggered == 1 && Bmu2isTriggered == 1)"

CUTPbPbNP=${CUTPbPb}"&&abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter && Bgen != 23333"

RECOONLYPbPb=${CUTPbPb}


TRGPbPb="(HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1)"
TRGPbPbMC="(HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1)"

OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb.root"


if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then  
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 16 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 16 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 16 30 90

rm MCefficiency.exe
fi




if [ $DOANALYSISPbPb_MCSTUDY_PTSHAPE -eq 1 ]; then  

g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 11 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 11 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 11 30 90

./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 12 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 12 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 12 30 90

./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 13 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 13 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 13 30 90

./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 14 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 14 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 14 30 90

./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 15 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 15 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 15 30 90

rm MCefficiency.exe

fi





if [ $DOANALYSISPbPb_MCSTUDY_NOTNP -eq 1 ]; then  
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 21 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 21 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPb" "$CUTPbPb&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 21 30 90

rm MCefficiency.exe
fi





CUTPbPbNOCUT="(hiBin < 181) && Btrk1Pt > 0.9 && Btrk2Pt > 0.9 && Bchi2cl > 0.05 && BsvpvDistance/BsvpvDisErr > 2.0 && Bpt > 5 && abs(Btrk1Eta-0.0) < 2.4  && abs(Btrk2Eta-0.0) < 2.4 && (TMath::Abs(By)<2.4&&TMath::Abs(Bmumumass-3.096916)<0.15&&((abs(Bmu1eta)<1.2&&Bmu1pt>3.5)||(abs(Bmu1eta)>1.2&&abs(Bmu1eta)<2.1&&Bmu1pt>(5.47-1.89*abs(Bmu1eta)))||(abs(Bmu1eta)>2.1&&abs(Bmu1eta)<2.4&&Bmu1pt>1.5))&&((abs(Bmu2eta)<1.2&&Bmu2pt>3.5)||(abs(Bmu2eta)>1.2&&abs(Bmu2eta)<2.1&&Bmu2pt>(5.47-1.89*abs(Bmu2eta)))||(abs(Bmu2eta)>2.1&&abs(Bmu2eta)<2.4&&Bmu2pt>1.5))&&Bmu1TMOneStationTight&&Bmu2TMOneStationTight&&Bmu1InPixelLayer>0&&(Bmu1InPixelLayer+Bmu1InStripLayer)>5&&Bmu2InPixelLayer>0&&(Bmu2InPixelLayer+Bmu2InStripLayer)>5&&Bmu1dxyPV<0.3&&Bmu2dxyPV<0.3&&Bmu1dzPV<20&&Bmu2dzPV<20&&Bmu1isTrackerMuon&&Bmu2isTrackerMuon&&Bmu1isGlobalMuon&&Bmu2isGlobalMuon&&Btrk1highPurity&&Btrk2highPurity&&abs(Btrk1Eta)<2.4&&abs(Btrk2Eta)<2.4&&Btrk1Pt>1.&&Btrk2Pt>1.&&abs(Btktkmass-1.019455)<0.015) && (abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter) && (Btrk1PixelHit + Btrk1StripHit > 10) && (Btrk2PixelHit + Btrk2StripHit > 10) && (Btrk1PtErr/Btrk1Pt < 0.1)&& (Btrk2PtErr/Btrk2Pt < 0.1) && Btrk1Chi2ndf/(Btrk1nStripLayer+Btrk1nPixelLayer) < 0.18 && Btrk2Chi2ndf/(Btrk2nStripLayer+Btrk2nPixelLayer) < 0.18&&((Bpt>5&&Bpt<10&&BDT_pt_5_10>0.32)||(Bpt>10&&Bpt<15&&BDT_pt_10_15> 0.29)||(Bpt>15&&Bpt<20&&BDT_pt_15_20>0.35)||(Bpt>20&&Bpt<50&&BDT_pt_20_50>0.33))&&abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter && phfCoincFilter2Th4"

RECOONLYPbPbNOCUT=${CUTPbPbNOCUT}


if [ $DOANALYSISPbPb_MCSTUDY_NOTRG -eq 1 ]; then


g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPbNOCUT" "$CUTPbPbNOCUT&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 20 0 90
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPbNOCUT" "$CUTPbPbNOCUT&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 20 0 30
./MCefficiency.exe 1 "$INPUTMCPbPbCANDWISE" "$SELGENPbPb" "$SELGENPbPbACCPbPb" "$RECOONLYPbPbNOCUT" "$CUTPbPbNOCUT&&$TRGPbPbMC" "Bpt" "Gpt" "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "plotEff/plotEff" 20 30 90

rm MCefficiency.exe



fi



