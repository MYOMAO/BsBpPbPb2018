i=0
f=10



CentMin=0
CentMax=90


PtMin=20
PtMax=50

while [ $i -lt $f ]

do 
	echo "Now Working on i = " $i 

	source doRoofit2.sh $i  ${CentMin} ${CentMax}  ${PtMin} ${PtMax}

	i=$(($i+1))

done

