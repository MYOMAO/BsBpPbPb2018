i=0
f=10



CentMin=0
CentMax=90


PtMin=15
PtMax=20

while [ $i -lt $f ]

do 
	echo "Now Working on i = " $i 

	source doRoofit2.sh $i  ${CentMin} ${CentMax}  ${PtMin} ${PtMax}
	
	mv plotFits/final_roofit/data_PbPb_1_BptNew_710_doubly0_EffInfoTreeFit.png plotFits/final_roofit/All7-10/Fits_$i.png
	
	i=$(($i+1))

done
