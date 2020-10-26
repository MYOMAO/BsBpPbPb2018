rm -rf OutData/Bs/*

echo Now work on pt 0 - 90:

root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,4)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,5)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,6)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,7)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,8)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,9)'
root -b -l -q ReAnaEffMCData.C'(0,90,4,1,0,10)'

echo Now work on cent 0 - 90:

root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,4)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,5)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,6)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,7)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,8)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,9)'
root -b -l -q ReAnaEffMCData.C'(0,90,1,1,1,10)'


echo Now work on cent 0 - 30:

root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,4)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,5)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,6)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,7)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,8)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,9)'
root -b -l -q ReAnaEffMCData.C'(0,30,1,1,1,10)'


echo Now work on cent 30 - 90:

root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,4)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,5)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,6)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,7)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,8)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,9)'
root -b -l -q ReAnaEffMCData.C'(30,90,1,1,1,10)'


