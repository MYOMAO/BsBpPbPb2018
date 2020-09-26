i=1990
f=2000



CentMin=0
CentMax=30


PtMin=10
PtMax=50

while [ $i -lt $f ]

do 
	echo "Now Working on i = " $i 

	source doRoofit2.sh $i  ${CentMin} ${CentMax}  ${PtMin} ${PtMax}

	i=$(($i+1))

done

