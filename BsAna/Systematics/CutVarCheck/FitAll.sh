i=0
f=50



init=0.08
CentMin=0
CentMax=90


PtMin=5
PtMax=10

while [ $i -lt $f ]

do 
	echo "Now Working on i = " $i 
 
	source doRoofit2.sh $i  ${CentMin} ${CentMax}  ${PtMin} ${PtMax} ${init}

	i=$(($i+1))

done

