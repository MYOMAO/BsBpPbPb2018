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

In addition for B+ we have 

``1 = Exponential Function * 3rd order poly nominal``

``2 = 4th order poly nominal``

These are not considered in our variation. But even if you include them, the systematic uncertainties will still be VERY SMALL and will not change the total systematic uncertainties. 

Again, like the PDF variation, we collect all these corrected yield numerical values, take the percent deviation from the nominal, and quote the largest one as the pT shape systematics. 

Again, keep in mind to update the numerical values of the pt shape systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.



### MC-Data Disagreement ###

Next is the imperfect agreement between the data and the MC. To estimate this systematic uncertainties, essentially, we use the sPLOT technique to extract the weight for the disagreement between the MC and the data. The sPLOT codes are developed by the LIP. They can be found here: ``https://github.com/powerfuljulia/BsinQGP``. 





Basically, we just directly use the sPLOT weight from the LIP group above. Since the Bs has a very low statistics, We decide to use the B+ tracks variables: trk1Dxy1, Btrk1DxyError1,Btrk1Dz1, Btrk1DzError1, Btrk1Eta, Btrk1Pt, Btrk1Y, and take the largest deviation among them to the nominal <1/acc * eff>. 

Hence, for Bs, we do the following:

To run the codes, first we go to the B+ folder ``BPAna/Systematics/MCData/``:

cd ``BPAna/Systematics/MCData/``

Then we do 

source RunForBs.sh

After the script is done, the percent deviation for each kinematic track variable can be found at ``OutData/Bs``

You should see 4 files

``Syst_1_0_30.dat  Syst_1_0_90.dat  Syst_1_30_90.dat  Syst_4_0_90.dat``

For example, one of the file ``OutData/Bs/Syst_1_0_90.dat``, which is for 0 - 90\% looks like this:



``i = 0   Syst = -0.0123356``

``i = 0   Syst = -0.0115487``

``i = 0   Syst = 0.0272942``

``i = 0   Syst = -0.0017606``

``i = 0   Syst = -0.00658569``

``i = 0   Syst = 0.017343``

``i = 0   Syst = -0.00398941``

Note that the script basically runs the code ``ReAnaEffMCData.C``. The last option of the code is about the different kinematic variables for Data-MC comparison:

``0 = Nominal``

``3 = Splot``

``4 = Btrk1Eta``

``5 = Btrk1Y``

``6 = Btrk1Pt``

``7 = Btrk1Dz1``

``8 = Btrk1DzError1``

``9 = Btrk1Dxy1``

``9 = Btrk1DxyError1``

Just pick the maximum deviation off 0 among them (here is 2.73\%) and remember to update the numerical values of the Data-MC systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.


Hence, for B+, we do the following: 


source RunForBP.sh

You can again file the output text files at  ``OutData/BP/``

Again, you should see 4 files:

``Syst_1_0_30.dat  Syst_1_0_90.dat  Syst_1_30_90.dat  Syst_4_0_90.dat``

One of the file content, for example, ``Syst_4_0_90.dat`` is like this:


``i = 0   Syst = 0.0405886``

``i = 1   Syst = 0.14925``

``i = 2   Syst = 0.029137``

``i = 3   Syst = -0.0165247``


Unlike Bs, here you do not need to pick the maximum inside the file. You basically, just need to quote these numbers and once again remember to update the numerical values of the Data-MC systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.





### MC Stat Systematics ###

Finally, it comes to the MC Stat. Systematics. Basically, we generate 10k 2D maps varied by their statistical uncertainties and then get 10k data sets. Then, we plot the distribution of the <1/acc>, <1/eff>, <1/acc * eff> and quote the RMS/Mean as the MC Stat. Systematics. 

First we go to the folder ``BsAna/Systematics/MCStat/``

To run the codes, first we generate 10k 2D maps according to its nominal values and statistical uncertainties. For instance, for 0 - 90\%

``root -b -l -q GenStatSyst.C'(0,90,0)'``

Now you have generated 10k 2D map, they are stored at ``10kTH2D/GenStatSyst_0_90.root``

Next, we calculate the <1/acc * eff> for each map, Simply run:

``root -b -l -q ReAnaEffSyst.C'(0,90,0)'``

The output for each <1/ac * eff> are stored at ``NunoSyst/0-90/AllTrials.root``

Finally, to calculate the MC Stat Systematic for <1/acc>, <1/eff>, <1/acc * eff>, we just need to run the code:

For pT differential

``root -b -l -q CalculateNunoSyst.C'(0,90,4,0)'``


For inclusive centrality 

``root -b -l -q CalculateNunoSyst.C'(0,90,1,1)'``

For centrality differential, we need to start over with 0 - 30\% and 30 - 90\% and finally run 

``root -b -l -q CalculateNunoSyst.C'(0,30,1,1)'``

``root -b -l -q CalculateNunoSyst.C'(30,90,1,1)'``

After you run the codes, you should be able to see, for example for 0 - 90\% pT differential, the print out as follows: 


``i = 0 Acc  Percentage Syst = 0.0206712``

``i = 0 Sel Percentage Syst = 0.31896``

``i = 0   Percentage Syst = 0.0972091``

``i = 1 Acc  Percentage Syst = 0.0108078``

``i = 1 Sel Percentage Syst = 0.228054``

``i = 1   Percentage Syst = 0.0337798``

``i = 2 Acc  Percentage Syst = 0.0110484``

``i = 2 Sel Percentage Syst = 0.220733``

``i = 2   Percentage Syst = 0.0198043``

``i = 3 Acc  Percentage Syst = 0.00860431``

``i = 3 Sel Percentage Syst = 0.135085``

``i = 3   Percentage Syst = 0.0139482``

Here, basically, the print out is about the MC Stat systematics for acceptance, selection efficiency, and acceptance * efficiency for each bT bin. 

Again, now basically record the acceptance * efficiency for each bin and  once again remember to update the numerical values of the MC Stat systematic uncertainties in the ``BsAndBP/FinalPlots/B*Bin*.C`` files.

Again, repeat everything above for B+, you get all the systematic uncertainties values for B+ as well and update to the B+ header files and codes too.


## Making Final Figures ##

First we go to the folder ``Codes/BsAndBP/FinalPlots``:

``cd Codes/BsAndBP/FinalPlots``

Everything then is based on the ``Codes/BsAndBP/FinalPlots`` folder.

### Total Systematics Summaries ###

Now we are ready to make the final plots. First, we should update all the numbers in the header files: ``BsSystValues.h`` and ``BpSystValues.h`` with the new systematic uncertainties. Keep in mind that ``EffSyst*`` includes: MC Stat, Data-MC,  pT shape, and tracking efficiency (5\% for B+ and 10\% for Bs). You basically need to add all those into quadratures and update the values to the arrays.

After they are updated, you can plot the systematic error by running the codes:

root -b -l -q PlotSystBs.C

The output summary plots for the systematic uncertainties can be found at ``PlotSyst/Bs/``

Same for B+.

### Final Bs, B+, and Bs/B+ vs pT Plots ###

First, make sure you have run the codes ``Bs1Bin.C, Bs2Bins.C, Bs4Bins.C,  BP1Bin.C, BP2Bins.C, BP4Bins.C, BsOverBPlus1Bin.C, BsOverBPlus2Bins.C, BsOverBPlus4Bins.C`` again. Then, they will generate all the text files for Bs and B+ corrected yield at ``OutText``. For instance, you see the file ``OutText/corryield_cent_0_90_Bp_New.txt`` for B+ 0 - 90\% inclusive bin:

``NPart   xsec   statUncertUp   statUncertDown   systUncert Up   systUncert Down   glbUncert Up   glbUncert Down ``
``126   1.94646e+06   0.0885   0.0795   0.14065   0.138668   0.028   0.028``

You see a table of center the x-axis, y-axis, statistical error up and down, systematic error up and down, and global error up and down. 

For the Bs/B+ ratio, they are saved at ``OutText/Ratio/ratio_pt.txt``

It has similar format as the corrected yield. So the next step, you basically just copy all the *_pt (both corrected yield and ratio) files to the folder ``WithCao/Pt/dataSource`` and overwrite the existing files there

``cp OutText/corryield_*pt*txt WithCao/Pt/dataSource/``

``OutText/Ratio/ratio_pt.txt WithCao/Pt/dataSource/``


Then we go to the ``WithCao/Pt/`` folder

``cd `WithCao/Pt/``

And then run to plot the final figures for the corrected yield with the following arguments:

``root -b -l -q plotPt.C++'(1,1,0,1,1)'``

This will generate output files with png and pdf formats. There is some style issue in the png format. You can find the pdf format of the Bs and B+ corrected yield plot (plotted together) at 

``figs/pdf/xsec_vsPt.pdf``

For the Bs/B+ vs pT, simply run:

``root -b -l -q plotPt.C++'(1,1,1,1,1)'``

Again, the output final plot for the Bs/B+ ratio are located at 

``figs/pdf/ratio_vsPt_ref1_1.pdf``


Basically, the first argument is whether to save the plots (should always be 1), the second argument is debug (you can turn it on), the third argument is ``0 for corrected yield`` and ``1 for Bs/B+ ratio``, the fourth argument is whether or not to drop the theory curves (TAMU and Cao), and the fifth is whether to draw the LHCb pp 7 TeV reference. The fourth and fifth options are for Bs/B+ ratio only. 


### Final Bs, B+, and Bs/B+ vs Cent Plots ###

Similarly, we copy everything to the centrality folder ``WithCao/Cent/``. 

``cp OutText/corryield_*cent*txt WithCao/Cent/dataSource/``

``OutText/Ratio/ratio_cent_0_* WithCao/Cent/dataSource/``

Note that we have two seperated centralities: the differential 0 - 30\% + 30 - 90\% in one file and the inclusive 0 - 90\% in another file.

Then similar to the Pt case, we go to the centrality folder ``WithCao/Pt/`` 

``cd `WithCao/Cent/``

And then run to plot the final figures for the corrected yield with the following arguments:

``root -b -l -q plotCentStyle.C++'(1,1,0,1,"dataSource","figs")'``

This will generate output files with png and pdf formats. There is some style issue in the png format. You can find the pdf format of the Bs and B+ corrected yield plot (plotted together) at 

``figs/pdf/xsec_vsCent.pdf``


For the Bs/B+ vs Cent, simply run:

``root -b -l -q plotCentStyle.C++'(1,1,1,1,"dataSource","figs")'``

Again, the output final plot for the Bs/B+ ratio are located at 

``figs/pdf/ratio_vsCent_ref1.pdf``

Here, the arguments are basically the same as the pT. But we do not have a theory curve option for now. In this code, for centrality, the Cao curve is always plotted along with data. The fifth ``dataSource`` argument basically specifies the input texts folder and the sixth ``figs`` argument basically specifies the output plots folder.

## Finish ##

Now, everything is DONE!! Thanks for all the hard work, IT PAYS OFF!!! Just collect all your final plots in pdf version:

``Codes/BsAndBP/FinalPlots/WithCao/Pt/figs/pdf/xsec_vsPt.pdf``

``Codes/BsAndBP/FinalPlots/WithCao/Pt/figs/pdf/ratio_vsPt_ref1_1.pdf``

``Codes/BsAndBP/FinalPlots/WithCao/Cent/figs/pdf/xsec_vsCent.pdf``

``Codes/BsAndBP/FinalPlots/WithCao/Cent/figs/pdf/ratio_vsCent_ref1.pdf``

and post them to your presentations and papers.


## Contact ##

There will be more updates and refinements on the codes in the future. If you have any question regarding to the instructions or the codes, please feel free to contact me by email: zzshi@mit.edu

