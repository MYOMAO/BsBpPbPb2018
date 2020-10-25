# Please Read the Following Instruction to Get Started #

This repository is made to run the Bs/B+ analysis using CMS 2018 PbPb 5.02 TeV datasets. If you successfully run the codes, you should be able to get Bs/B+ as a function pT and event centrality

Some rename of the codes may need to be done since some of the codes' names are a little weird. Nonetheless, for the moment, let's stick to the names now and see if we can get the analysis done on the B mesons done.  

## To START ##

To start, first find a fresh folder on your local machine

Then get this repository first download it from github by doing:

``git clone https://github.com/MYOMAO/BsBpPbPb2018.git``

You will see the following two folders:

``BsAna BpAna BsAndBp``

Basically, they stands for the Bs part and the B+ part of the analysis codes. The BsAndBp are the codes to create common results for Bs and B+. They will get you the cross sections. 


## To Run the Codes ##

The following will be for Bs. B+ analysis is basically identical. Before running the codes, make sure you have the file inside the folder named ``BsBPInputSamples``. You can find it on MIT grendel: ``szhaozho@grendel01.mit.edu:/data/szhaozho/BsBPInputSamples``. Inside the folder ``BsBPInputSamples``, you should see the following files:

``BPData.root  BPMCOld.root  BPMC.root  BsData.root``

## Generating Prerequisite Files for the Bs Nominal Results ##

To generate the prerequisite files for the Bs nominal analysis, assuming we start from the file inside the folder ``BsBPInputSamples``, we first get in the folder ``BPAna/2DMap/``. 

cd BPAna/2DMap

There are two ways to get the 2D map. The first way is to run the code ``ManualTest.C``

`` root -b -l -q ManualTest.C'(0,90)' ``

`` root -b -l -q ManualTest.C'(0,30)' ``

`` root -b -l -q ManualTest.C'(30,90)' ``

Basically for each centrality bin. The output file is saved at ``NewEff2DMaps/``

``EffFine_0_30.root  EffFine_0_90.root EffFine_30_90.root``

Alternatively, you can simply run 

``source New2DMaps.sh``


Making sure that the option


``DOANALYSISPbPb_MCSTUDY=1``

is on.

You can find the files on ``CheckSystNuno/NoWeight/``

Please note that the file formats are different. The file located at ``NewEff2DMaps`` is for nominal, data bootstrapping for statistical uncertainties, MC stat systematics, TnP systematics purpose. The files located at other systematics such as data-MC comparison and Pt shape systematics. They are basically identical but with different naming and histogram filling strategies: ManualTest.C fills the Bs with all the pthat, event and TnP weights for B muons candidates candidates by looping through the tree. ``New2DMaps.sh`` runs the ``MCefficiency.C`` codes instead and apply pthat, event, and TnP weight using TCut in the multiplication. They yield to identical nominal results and statistical errors for the acceptance and selection efficiency. 


So basically now we have the 2D maps with the TnP weights. The next is to generate the data file with the efficiency for each candidate according to their B candidate pt and |y| in the 2D map. To do so, we can simply run the codes:

``root -b -l -q ManualCutEMBs.C'(0,90,1)'``

``root -b -l -q ManualCutEMBs.C'(0,30,1)'``

``root -b -l -q ManualCutEMBs.C'(30,90,1)'``

The output file will be located at the Nominal folder:

``BsAna/Nominal/Efficiency/NewTnPScheme``


Keep in mind that we are using two different MC files for efficiency correction in the Bs due to the pre-existing cut in track pT the MC sample. The sample name ``BPMC.root`` named inside the folder ``BsBPInputSamples/`` is used to correct the selection efficiency  "eff" and the ``AccNew.root`` inside ``2DMap`` folder is the corrected acceptance. Therefore, the 2D ``1/(acc * eff)`` needs two separate input: ``BPMC.root`` and ``AccNew.root``. The flag ``1`` turns on to have this two separate file. ``0`` is having one file ONLY.   


## To Run the Nominal Results ##



### Raw Yield Extraction ###

Now we have the input file for calculate the Bs nominal results. To get the nominal results, we first run the raw yield. Simply go to the folder: 

``cd BsAna/Nominal/RawYield``

Then run the script to perform unbinned fit on the Bs data with the MC template: 

``source doRoofit2.sh``

Make sure that you have change the pt range in the line of parameters.h 

In line 33:

``double ptBins_full[nBins_full+1] = {15,20};``

to your desired pT bin. 

Basically, for yield vs pT, we need to change 

``doRoofit2.sh`` 

Line 1: ``DOANALYSISPbPb_ROOFIT_BINNED_PT_BS = 1``
Line 4: ``DOANALYSISPbPb_ROOFIT_FULL_BS = 0``


And make sure the centrality is 0 - 90\%

Line 21: ``CENTPbPbMIN=0``
Line 22: ``CENTPbPbMAX=90``

For yield vs centrality, we need to make sure that 

``double ptBins_full[nBins_full+1] = {10,50};``

Then change the centrality bin in the shell script

``doRoofit2.sh`` 


Line 1: ``DOANALYSISPbPb_ROOFIT_BINNED_PT_BS = 0``
Line 4: ``DOANALYSISPbPb_ROOFIT_FULL_BS = 1``

Line 21: ``CENTPbPbMIN=0``
Line 22: ``CENTPbPbMAX=90``

To your desired centrality range.



### Efficiency Correction ###


First, go to the efficiency correction folder:

``cd BsAna/Nominal/Efficiency``

Then transfer the Raw yield file to the efficiency folder if you have updated the raw yield:

``cp BsAna/Nominal/RawYield/ROOTfiles/*root BsAna/Nominal/Efficiency/RawYields``

simply need to run the codes with the argument as follows:

``root -b -l -q ReAnaEffNew.C'(0,90,4,1,0,0)'``


Here, the first argument stands for the minimum centrality, the second argument stands for maximum centrality, the third argument stands for number of bins, the fourth argument stands for doing 1D, 2D, and fit function map 0,1,2 respectfully, the fifth argument stands for whether or not dropping the lowest pT bin (7 - 10 GeV/c), the sixth argument stands for the pT weight: 0 = no pT weight, 11 = linear function , 12 = quadratic, 13 = linear + inverse, 14 = linear + square root, 15 =  linear + log. 


You will see the efficiency correction factor <1/acc * eff> and corrected yield in the print out.

The output files for the efficiency is in the folder ``Efficiency/``

The output for the corrected yield is in the folder ``FinalFiles/``

All the plots are saved in the folder ``Plots/NoTnP/``


Note that, here we have ONLY calculated the mean value. The statistical uncertainties cannot be trusted in the printout. To estimate the correct (asymmetric) statistical uncertainties, we need to perform data-boostraping, which we will describe in the later sections. 

### Nominal Corrected Yield Calculation ###

The final step is to calculate the corrected yield and make the final results plots. First, we still go to the efficiency folder, 

``cd BsAna/Nominal/Efficiency``

We run the Merging codes to merge 0 - 30\% and 30 - 90\% centrality bins by doing:

``root -b -l -q MergeBin.C``

Then we will copy the files inside the following folder ``FinalFiles`` to  ``BsAndBP/FinalPlots``

``cp FinalFiles/NewCorr_0_90.root  BsAndBP/FinalPlots/BsBP1Bin/CrossSectionPbPbBs.root``
``cp FinalFiles/NewCorr_0_30_90.root  BsAndBP/FinalPlots/BsBP2Bins/CrossSectionPbPbBs.root``
``cp FinalFiles/PtDiffFile_0_90.root  BsAndBP/FinalPlots/BsBP4Bins/CrossSectionPbPbBs.root``

Then simply run the codes:

``root -b -l -q Bs1Bin.C``

``root -b -l -q Bs2Bins.C``

``root -b -l -q Bs4Bins.C``

You will be able to get the printout, plots, and saved text files for the nominal, statistical uncertainties and systematic uncertainties for the Bs final corrected yield results.

The output text is stored at 

``OutText/corryield*txt``

Again, note that the statistical and systematic uncertainties here is not automatically updated. To update the statistical uncertainties, simply go to the files:
 
``StatReCal1Bin.h  StatReCal2Bins.h StatReCal4Bins.h``

And update the numerical value for each bin

For the systematic uncertainties, you will have to go inside the 

``Bs1Bin.C Bs2Bins.C  Bs4Bins.C``

And update the systematic uncertainties:

``double SystErrBs[_nBins];``

``double TrackingErrBs[_nBins] ={0.10,0.10};``

``double SelErrBs[_nBins] ={0.0304,0.0226};``

``double PTErrBs[_nBins] ={0.00011,0.00029};``

``double AccErrBs[_nBins] ={0.0,0.0};``

``double PDFBErrBs[_nBins] ={0.0114,0.0592};``

``double PDFSErrBs[_nBins] ={0.0079,0.0182};``

``double  MCStatBs[_nBins] ={0.0236, 0.0676}``

But these will be further discussed once we have finished the estimation of the statistical uncertainties and systematic uncertainties. This conclude the nominal final results section.


## Statistical Uncertainties Calculation: Data Bootstrapping ##

Due to the nature of the data-average <1/acc * eff>, it will have unknown correlation between the data and the MC. To correctly estimate the statistical uncertainties of the corrected yield, we need to perform bootstrapping. The idea is to resample 1000 data-like sample smear by the Poisson process, compute the corrected yield distribution of the 1000 samples, and quote +/- of the mean with 68.27 as the statistical uncertainties. 

The codes are located: ``BsAna/ClosureStudies/DataBoostrap/``. We first go to the folder:

``cd BsAna/ClosureStudies/DataBoostrap/`` 

Then, we first run the data splitting for our desired bin, for instance, 10 - 15 GeV/c and 0 - 90\%:

``root -b -l -q SpiltDataBoot.C'(0,90,1)'``

The first argument is the minimum centrality range. The second argument is the maximum centrality range. The third argument is the pt bin range: 

``0 = 7 - 10``  

``1 = 10 - 15``

``2 = 15 - 20``

``3 = 20 - 50 ``

``-1 = 10 - 50``

After this, we have constructed 1000 samples whose statistics are varied by the Poisson distribution. To change the number of samples, just go to the code ``SpiltDataBoot.C`` and change

Line 171: ``NSet = 1000``

Next, the we will perform the unbinned fits to all the samples to obtain the raw yield for the 1000 data-like samples. To do so, first view the ``parametersNew.h`` file and change:

Line 44: ``double ptBins_full[nBins_full+1] = {15,20};``

To our example 

``double ptBins_full[nBins_full+1] = {10,15};``

Also, go to the file ``FitAll.sh`` and change the pT and centrality bin:

Line 1: ``i=0``
Line 2: ``f=10``
 

Line 6: ``CentMin=0``
Line 7: ``CentMax=90``


Line 10: ``PtMin=15``
Line 11: ``PtMax=20``


Here basically ``i`` and ``f`` basically stand for the begin and end file IDs. ``CentMin`` and ``CentMax`` mean the minimum and maximum centrality. ``PtMin`` and ``PtMax`` mean the minimum and maximum pT. Here simply change the PtMin and PtMax 

Line 10: ``PtMin=10``
Line 11: ``PtMax=15``

Then after these changes, simply run:

source FitAll.sh


After a long time, all the fits for the 1000 files finished. Then we will now estimate the statistical uncertainties on the efficiency and corrected yield: 

root -b -l -q SampleClosure.C'(0,90,1)'

Then you can see the results in the print out:

``Method 1 Eff:  Percentile = 0.130025``
``Method 2 Eff:  PercentileUp = 0.131425  PercentileDown = 0.121172``

For the symmetric and asymmetric statistical uncertainties on the efficiency. 

``Method 1:  Percentile = 0.248623``
``Method 2:  PercentileUp = 0.223399  PercentileDown = 0.24879``

For the symmetric and asymmetric statistical uncertainties on the corrected yield. 

The plots for the raw yield distribution, efficiency distribution, sample size and corrected yield distribution are save at ``PlotsRaw``, ``PlotsEff``, and ``Plots`` respectfully. 


Finally, again, remember to change the numerical value in

``BsAna/Nominal/Efficiency/StatReCal4Bins.h``

 of the second component of the array
 
 ``double StatUpBs[nBins] = {0.429,0.230,0.211,0.210};``
``double StatDownBs[nBins] = {0.414,0.214,0.204,0.195};``

Repeat the steps for all other pT and centrality bins and change the numerical value manually for the StatReCal*Bin*.h header files. This ends the estimation for the statistical uncertainties studies via data bootstrapping of the corrected yield. 

## Systematic Uncertainties Calculation ##

### PDF Variation ###

We know there is systematic uncertainties on the fits, both the background and signal components. This is called the PDF Variation. Therefore, we create the codes to estimate the systematic uncertainties.

Before running the codes, you need to check the pT and centrality range for PDF variation. The pT range is set at ``parametersNew.h`` and the centrality range is set at the doRoofit2.sh. The change is the same as above 

For pt it is 

Line 44 ``double ptBins_full[nBins_full+1] = {10,50};``

For centrality it is

Line 6: ``CentMin=0``
Line 7: ``CentMax=90``


To run the codes, simply do:

source doRooFit2.sh

The plots are saved at ``plotFits/final_roofit`` and the text files for all different variation fit function are store at ``OutText/``. An example of the file ``OutTexts/PDF0_90_10_50.dat`` is shown here:

``PDFVAR:    VarFunc:      Yield: 80.2495``

``PDFVAR: signal   VarFunc: 3gauss     Yield: 79``

``PDFVAR: signal   VarFunc: fixed     Yield: 80.09``

``PDFVAR: signal   VarFunc: scal+     Yield: 81.3192``

``PDFVAR: signal   VarFunc: scal-     Yield: 78.9276``

``PDFVAR: background   VarFunc: 1st     Yield: 78.9841``

``PDFVAR: background   VarFunc: 2nd     Yield: 80.8699``

``PDFVAR: background   VarFunc: 3rd     Yield: 80.7243``

``PDFVAR: background   VarFunc: 3rd     Yield: 80.7243``

Basically, you can simply calculate and quote the largest percentage deviation from the nominal raw yield as the signal and background PDF systematics. Then add these two into quadrature and quote that number as the total PDF systematic uncertainty. Repeat the steps for each pT and centrality bin and keep in mind to update the numerical values at the codes: ``BsAndBP/FinalPlots/B*Bin*.C`` in the corresponding PDF background and signal arrays.


### TnP Systematics ###

Again, we also have the TnP systematic uncertainties. We have built our codes following the workflow for TnP correction and systematic estimation on the MC 2D map here:

Nominal: ``https://github.com/MYOMAO/BsBpPbPb2018/blob/master/TnPFlowChart/TnP\%20Nominal.png``

Systematics: ``https://github.com/MYOMAO/BsBpPbPb2018/blob/master/TnPFlowChart/TnP\%20Systematics.png``

Calculation Scheme: ``https://github.com/MYOMAO/BsBpPbPb2018/blob/master/TnPFlowChart/TnP\%20Systematics\%20Scheme.png``


To estimate the uncertainties, we will simply run the script:

``source TnPSyst.sh``

The printout of the numerical values can be found at, for instance, for the pT differential studies

``i = 0   Upper TnP Syst = 0.00824708``
``i = 0   Lower TnP Syst = 0.00811191``
``i = 1   Upper TnP Syst = 0.0142312``
``i = 1   Lower TnP Syst = 0.0138036``
``i = 2   Upper TnP Syst = 0.0172237``
``i = 2   Lower TnP Syst = 0.0166216``
``i = 3   Upper TnP Syst = 0.0172501``
``i = 3   Lower TnP Syst = 0.01664``

Note that the script runs the code ``ReAnaEffTnPSyst.C``. The last option is for the TnP systematic on a specific TnP component:

``0 = muid``

``1 = trk``

``2 = trg``

``3 = total = muid * trk * trg``

The muid, trk, trk, and total results are saved at the folders ``TnPPlots/muid/``, ``TnPPlots/trk/``, ``TnPPlots/trg/``, and ``TnPPlots/total/`` respectfully. 

Again, keep in mind to update the numerical values of the TnP systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.


### pT Shape Systematics ###

We know that there is systematic uncertainties due to the unknown of the Bs pT shape. It will affect the corrected yield but we should expect them to be small. To quantify this uncertainties, we basically apply the Bpt weights functions to the RECO and GEN and generate new 2D maps. To run the codes and get the pT Shape Systematics, we simply run the scripy:

``source PtShapSyst.sh``

Then for the pT differential studies, look at the print out:

``i = 0  CorrYieldDiff =  865604``
``i = 1  CorrYieldDiff =  705950``
``i = 2  CorrYieldDiff =  231447``
``i = 3  CorrYieldDiff =  121349``

For the centrality and inclusive bin studies, look at the print out:

``FinalCorrYieldComp = 1.18381e+06     FinalCorrYieldErr = 22178.2``

Note that the file ``PtShapSyst.sh`` runs the code ``ReAnaEffPtShape.C``. The pt shape function variation option is the same as the ones listed above:


``0 = no pT weight``
``11 = linear function``
``12 = quadratic``
``13 = linear + inverse``
``14 = linear + square root``
``15 =  linear + log``

There are other option such as 

``1 = FONLL``

These are not considered in our variation. But even if you include them, the systematic uncertainties will still be VERY SMALL and will not change the total systematic uncertainties. 

Again, like the PDF variation, we collect all these corrected yield numerical values, take the percent deviation from the nominal, and quote the largest one as the pT shape systematics. 

Again, keep in mind to update the numerical values of the pt shape systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.



### MC-Data Disagreement ###

Next is the imperfect agreement between the data and the MC. To estimate this systematic uncertainties, essentially, we use the sPLOT technique to extract the weight for the disagreement between the MC-











## Contact ##

If you have any question regarding to the instructions or the codes, please feel free to contact me by email: zzshi@mit.edu

