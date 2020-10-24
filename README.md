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

Please note that the file formats are different. The file located at NewEff2DMaps is for nominal, data bootstrapping for statistical uncertainties, MC stat systematics, TnP systematics purpose. The files located at other systematics such as data-MC comparison and Pt shape systematics. They are basically identical but with different naming and histogram filling strategies: ManualTest.C fills the Bs with all the pthat, event and TnP weights for B muons candidates candidates by looping through the tree. New2DMaps.sh runs the MCefficiency codes instead and apply pthat, event, and TnP weight using TCut in the multiplication. The yield to identical nominal results and statistical errors for the acceptance and selection efficiency. 

