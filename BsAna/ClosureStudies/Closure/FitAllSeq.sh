i=0
f=100



CentMin=0
CentMax=90


PtMin=10
PtMax=50 

while [ $i -lt $f ]

do 
	echo "Now Working on i = " $i 

	source doRoofit3.sh $i  ${CentMin} ${CentMax}  ${PtMin} ${PtMax}

	i=$(($i+1))

done

