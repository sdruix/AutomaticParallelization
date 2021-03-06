SEARCH_FOLDER="*"
float_scale=4
echo  "Test Name;NameMinT;MinT;NameMinE;MinE;NameMinTO;MinTO;SqT;SqE;OmpT;OmpE;" > "report.csv"
#####################################################################
# Evaluate a floating point number expression.

function float_eval()
{
    local stat=0
    local result=0.0
    if [[ $# -gt 0 ]]; then
        result=$(echo "scale=$float_scale; $*" | bc -q 2>/dev/null)
        stat=$?
        if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    fi
    echo $result
    return $stat
}

ENERGYACTIVATED=0
CHECKACTIVATED=0
for f in $SEARCH_FOLDER
do
    if [ -d "$f" ]
    then
        for ff in $f/*
        do  
 	    if [ -d "$ff" ]
	    then    
        	    
		    for fff in $ff/*
       			 do
			    if [ "$fff" = "$ff/log.csv" ] ; then
				filename="$fff"
				echo "Log file found in "$fff
				OLDIFS=$IFS
				IFS=";"
				MINT=""
				MINE=""
				MINTO=""
				ITERATION=0
				NAMEBESTT=""
				NAMEBESTE=""
				NAMEBESTTO=""
				TIMEORIGSQ=""
				ENERGYSQ=""
				TIMEORIGOMP=""
				ENERGYOMP=""
				energynorm=1.0
				timenorm=1.0
				time=""
				energy=""
				while read name signature time energy
				 do
                                    time=${time//[-._]/}
			            comparision=$(echo $ITERATION">"0 | bc -l)
				    if [ "$comparision" == "1" ]; then
					    if [ "$time" != "" ] ; then
					    	timenorm=$(echo $time | tr ',' '.');
					    fi
					    if [ "$energy" != "" ] ; then
					    	energynorm=$(echo $energy | tr ',' '.');
					    fi
					    if [ "$MINT" != "" ] ; then
					    	MINTnorm=$(echo $MINT | tr ',' '.');
					    fi
					    if [ "$MINE" != "" ] ; then
					    	MINEnorm=$(echo $MINE | tr ',' '.');
					    fi
					    if [ "$MINTO" != "" ] ; then
					    	MINTOnorm=$(echo $MINTO | tr ',' '.');
					    fi
					    if [ "$ITERATION" == "1" ] ; then
					        MINT=$time
						NAMEBESTT=$name
						if [ "$name" == "Original without OpenMp" ] ; then
							echo $name
							CHECKACTIVATED=1
							TIMEORIGSQ=$time
							ENERGYSQ=$energy
						fi
					    else if [ "$ITERATION" == "2" ] ; then
						        MINT=$time
							NAMEBESTT=$name
							if [ "$name" == "Original with OpenMp" ] ; then
								echo $name
								CHECKACTIVATED=1
								TIMEORIGOMP=$time
								ENERGYOMP=$energy
							fi
					    	fi 
					    fi
					    if [ "$MINT" == "" ] ; then
		                                    MINT=$time
						    NAMEBESTT=$name
					    else
						   comparision=$(echo $MINTnorm">"$timenorm | bc -l)
						   if [ "$comparision" == "1" ]; then
		                                    MINT=$time
						    NAMEBESTT=$name
						   fi
					    fi
					    if [ "$ENERGYACTIVATED" == 1 ] ; then
						    if [ "$MINE" == "" ] ; then
				                            MINE=$energy
							    NAMEBESTE=$name
						    else
							   comparision=$(echo $MINEnorm">"$energynorm | bc -l)
							   if [ "$comparision" == "1" ]; then
				                            MINE=$energy
							    NAMEBESTE=$name
							   fi
						    fi
						    if [ "$energynorm" != 1.0 ] ; then
							operation=$(echo $timenorm"/"$energynorm)
							tradeoffnorm=$(float_eval $operation)
							tradeoff=$(echo $tradeoffnorm | tr '.' ',');
							if [ "$MINTO" == "" ] ; then
				                            MINTO=$tradeoff
							    NAMEBESTTO=$name
							else
							   comparision=$(echo $MINTOnorm">"$tradeoffnorm | bc -l)
							   if [ "$comparision" == "1" ]; then
				                            MINTO=$tradeoff
							    NAMEBESTTO=$name
							   fi
							fi
						    fi
					    fi
					    
				    else
					if [ "$energy" == "Energy Consumtion(J.)" ] ; then
						ENERGYACTIVATED=1
					fi
				    fi
				    ITERATION=$(echo $ITERATION"+ 1"| bc -l);
				 done < $filename
				 echo "Mint("$f"): "$MINT
				 if [ "$ENERGYACTIVATED" == 1 ] ; then
					
					 echo "Mine("$f"): "$MINE
					 echo "Minto("$f"): "$MINTO
					if [ "$CHECKACTIVATED" == 1 ] ; then
				 		echo  $f";"$NAMEBESTT";"$MINT";"$MINE";"$NAMEBESTE";"$NAMEBESTTO";"$MINTO";"$TIMEORIGSQ";"$ENERGYSQ";"$TIMEORIGOMP";"$ENERGYOMP";" >> "report.csv"
					else
						echo  $f";"$NAMEBESTT";"$MINT";"$MINE";"$NAMEBESTE";"$NAMEBESTTO";"$MINTO";" >> "report.csv"
					fi
				 else
					if [ "$CHECKACTIVATED" == 1 ] ; then
						echo  $f";"$NAMEBESTT";"$MINT";"$TIMEORIGSQ";"$ENERGYSQ";"$TIMEORIGOMP";"$ENERGYOMP";" >> "report.csv"
					else
						echo  $f";"$NAMEBESTT";"$MINT";" >> "report.csv"
					fi
				 fi
				 IFS=$OLDIFS
			    fi
		        done
            fi
        done

    fi
done



