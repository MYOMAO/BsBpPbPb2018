### Please Read the Following Instruction to Get Started ###

This repository is made to run the Bs/B+ analysis using CMS 2018 PbPb 5.02 TeV datasets. If you successfully run the codes, you should be able to get Bs/B+ as a function pT and event centrality

Some rename of the codes may need to be done since some of the codes' names are a little weird. Nonetheless, for the moment, let's stick to the names now and see if we can get the analysis done on the B mesons done.  

## To START ##

To start, first find a fresh folder on your local machine

Then get this repository first download it from github by doing:

git clone https://github.com/MYOMAO/BsBpPbPb2018.git

You will see the following two folders:

BsAna BpAna BsAndBp

Basically, they stands for the Bs part and the B+ part of the analysis codes. The BsAndBp are the codes to create common results for Bs and B+. They will get you the cross sections. 


## To Run the Codes ##

The following will be for Bs. B+ analysis is basically identical. Before running the codes, make sure you have the file inside the folder named ``BsBPInputSamples". You can find it on MIT grendel: szhaozho@grendel01.mit.edu:/data/szhaozho/BsBPInputSamples. Inside the folder BsBPInputSamples, you should see the following files:

BPData.root  BPMCOld.root  BPMC.root  BsData.root

## Generating Prerequisite Files for the Bs Nominal Results ##

To generate the prerequisite files for the Bs nominal analysis, assuming we start from the file inside the folder BsBPInputSamples, we first get in the folder BPAna/2DMap/. 

cd BPAna/2DMap

There are two ways to get the 2D map. The first way is to run the code ManualTest.C

root -b -l -q ManualTest.C'(0,90)'

root -b -l -q ManualTest.C'(0,30)'

root -b -l -q ManualTest.C'(30,90)'

Basically for each centrality bin. The output file is saved at NewEff2DMaps/

EffFine_0_30.root  EffFine_0_90.root EffFine_30_90.root

Alternatively, you can simply run 

source New2DMaps.sh


Making sure that the option


DOANALYSISPbPb_MCSTUDY=1 

is on.

You can find the files on CheckSystNuno/NoWeight/

Please note that the file formats are different. The file located at NewEff2DMaps is for nominal, data bootstrapping for statistical uncertainties, MC stat systematics, TnP systematics purpose. The files located at other systematics such as data-MC comparison and Pt shape systematics. They are basically identical but with different naming and histogram filling strategies: ManualTest.C fills the Bs with all the pthat, event and TnP weights for B muons candidates candidates by looping through the tree. New2DMaps.sh runs the MCefficiency codes instead and apply pthat, event, and TnP weight using TCut in the multiplication. They yield to identical nominal results and statistical errors for the acceptance and selection efficiency. 


So basically now we have the 2D maps with the TnP weights. The next is to generate the data file with the efficiency for each candidate according to their B candidate pt and |y| in the 2D map. To do so, we can simply run the codes:

root -b -l -q ManualCutEMBs.C'(0,90,1)'

root -b -l -q ManualCutEMBs.C'(0,30,1)'

root -b -l -q ManualCutEMBs.C'(30,90,1)'

The output file will be located at the Nominal folder:

BsAna/Nominal/Efficiency/NewTnPScheme


Keep in mind that we are using two different MC files for efficiency correction in the Bs due to the pre-existing ``cut" in track pT the MC sample. The sample name ``BPMC.root" named inside the folder BsBPInputSamples/ is used to correct the selection efficiency "eff" and the AccNew.root inside 2DMap folder is the corrected acceptance. Therefore, the 2D 1/(acc $\times$ eff) needs 2 separate input: BPMC.root and AccNew.root. The flag 1 turns on to have this two separate file. 0 is having one file ONLY.   


## To Run the Nominal Results ##



# Raw Yield Extraction #

Now we have the input file for calculate the Bs nominal results. To get the nominal results, we first run the raw yield. Simply go to the folder: 

cd BsAna/Nominal/RawYield

Then run the script to perform unbinned fit on the Bs data with the MC template: 

source doRoofit2.sh

Make sure that you have change the pt range in the line of parameters.h 

In line 33:

double ptBins_full[nBins_full+1] = {15,20}; 

to your desired pT bin. 

Basically, for yield vs pT, we need to change 

doRoofit2.sh 

Line 1: DOANALYSISPbPb_ROOFIT_BINNED_PT_BS = 1
Line 4: DOANALYSISPbPb_ROOFIT_FULL_BS = 0


And make sure the centrality is 0 - 90\%

Line 21: CENTPbPbMIN=0
Line 22: CENTPbPbMAX=90

For yield vs centrality, we need to make sure that 

double ptBins_full[nBins_full+1] = {10,50}; 

Then change the centrality bin in the shell script

doRoofit2.sh 


Line 1: DOANALYSISPbPb_ROOFIT_BINNED_PT_BS = 0
Line 4: DOANALYSISPbPb_ROOFIT_FULL_BS = 1

Line 21: CENTPbPbMIN=0
Line 22: CENTPbPbMAX=90

To your desired centrality range.



# Efficiency Correction #


First, go to the efficiency correction folder:

cd BsAna/Nominal/Efficiency

Then transfer the Raw yield file to the efficiency folder if you have updated the raw yield:

cp BsAna/Nominal/RawYield/ROOTfiles/*root BsAna/Nominal/Efficiency/RawYields

simply need to run the codes with the argument as follows:

root -b -l -q ReAnaEffNew.C'(0,90,4,1,0,0)'


Here, the first argument stands for the minimum centrality, the second argument stands for maximum centrality, the third argument stands for number of bins, the fourth argument stands for doing 1D, 2D, and fit function map 0,1,2 respectfully, the fifth argument stands for whether or not dropping the lowest pT bin (7 - 10 GeV/c), the sixth argument stands for the pT weight: 0 = no pT weight, 11 = linear function , 12 = quadratic, 13 = linear + inverse, 14 = linear + square root, 15 =  linear + log. 

You will see the efficiency correction factor <1/acc $\times$ eff> and corrected yield in the print out.

The output files for the efficiency is in the folder Efficiency/ 

The output for the corrected yield is in the folder FinalFiles/

All the plots are saved in the folder Plots/NoTnP/


Note that, here we have ONLY calculate the mean value. The statistical uncertainties cannot be trusted in the printout. To estimate the correct (asymmetric) statistical uncertainties, we need to perform data-boostraping, which we will describe in the later sections. 

# Corrected Yield Calculation #

The final step is to calculate the corrected yield and make the final results plots.

## Contact ##

If you have any question regarding to the instructions or the codes, please feel free to contact me by email: zzshi@mit.edu

