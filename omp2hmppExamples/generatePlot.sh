#/bin/sh

float_scale=4
function float_eval()
{
    local stat=0
    local result=0.0
    if [[ $# -gt 0 ]]; then
        result=$(echo "scale=$float_scale; $*" | bc -q 2>/dev/null)
        stat=$?
        if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    fi
    return $stat
}

filename="./report.csv"
OLDIFS=$IFS
IFS=";"
ITERATION=0
CHECK=0
ENERGY=0
rm *.dat
while read name NameMinT MinT NameMinE MinE NameMinTO MinTO SqT SqE OmpT OmpE
do
    comparision=$(echo $ITERATION">"0 | bc -l)
    if [ "$comparision" == "1" ]; then
	    echo $name $MinT $SqT $OmpT
	    sqTnorm=$(echo $SqT | tr ',' '.')
	    sqEnorm=$(echo $SqE | tr ',' '.')
	    ompTnorm=$(echo $OmpT | tr ',' '.')
	    ompEnorm=$(echo $OmpE | tr ',' '.')
	    Tnorm=$(echo $MinT | tr ',' '.')
	    Enorm=$(echo $MinE | tr ',' '.')
	    TOnorm=$(echo $MinTO | tr ',' '.')
	    operation=$(echo $sqEnorm"/"$sqTnorm)
	    sqTO=$(float_eval $operation)
	    operation=$(echo $ompEnorm"/"$ompTnorm)
	    ompTO=$(float_eval $operation)
	    operation=$(echo $sqTnorm"/"$Tnorm)
	    sphmpp=$(float_eval $operation);
	    operation=$(echo $sqTnorm"/"$ompTnorm)
	    spomp=$(float_eval $operation)
	    operation=$(echo $Enorm"*"$sqEnorm"/100")
	    PEvsSQ=$(float_eval $operation)                 
	    operation=$(echo $Enorm"*"$ompEnorm"/100")
	    PEvsOMP=$(float_eval $operation)   
            
	    if [ "$spVSomp" != "" ] ; then
		    checkSP=$(echo $spVSomp">"0 | bc -l)
		    if [ "$checkSP" == "1" ]; then
		    	echo  $name" "$spVSomp" "$sphmpp >> "speedUP.dat" 
		    fi
	    fi

	    if [ "$PEvsSQ" != "" ] ; then
		    checkVS=$(echo $PEvsSQ">"0 | bc -l)
		    if [ "$checkVS" == "1" ]; then
		    	echo  $name" "$PEvsSQ" "$PEvsOMP >> "energyP.dat" 
		    fi
	    fi
	
	     if [ "$sqTO" != "" ] ; then
		    checkTO=$(echo $sqTO">"0 | bc -l)
		    if [ "$checkTO" == "1" ]; then
		    	echo  $name" "$sqTO" "$ompTO" "$MinTO >> "trade.dat" 
		    fi
	    fi
	   
    fi
    ITERATION=$(echo $ITERATION"+ 1"| bc -l);
done < $filename
IFS=$OLDIFS

FILESP="speedUP.dat"
FILEE="energyP.dat"
FILET="trade.dat"

if [ -f $FILESP ]; then
	cat $FILESP > aux.dat
	echo  "ProblemName/SpeedUP OpenMP HMPP" > $FILESP
	cat aux.dat >> $FILESP
	gnuplot -e "set style data histogram; set style histogram cluster gap 1; set style fill solid border -1; set boxwidth 0.9; plot '"$FILESP"' using 2:xtic(1) t 2,'' u 3 t 3;set out 'speedUP.png';set terminal png; replot;quit"
fi

if [ -f $FILEE ]; then
	cat $FILEE > aux.dat
	echo  "ProblemName/EnergyDecrease OpenMP HMPP" > $FILEE
	cat aux.dat >> $FILEE
	gnuplot -e "set style data histogram; set style histogram cluster gap 1; set style fill solid border -1; set boxwidth 0.9; plot '"$FILEE"' using 2:xtic(1) t 2,'' u 3 t 3;set out 'energy.png';set terminal png; replot;quit"
fi

if [ -f $FILET ]; then
	cat $FILET > aux.dat
	echo  "ProblemName/TradeoffVs Seq OpenMP HMPP" > $FILET
	cat aux.dat >> $FILET
	gnuplot -e "set style data histogram; set style histogram cluster gap 1; set style fill solid border -1; set boxwidth 0.9; plot '"$FILET"' using 2:xtic(1) t 2,'' u 3 t 3,'' u 4 t 4;set out 'tradeoff.png';set terminal png; replot;quit"
fi

				 
