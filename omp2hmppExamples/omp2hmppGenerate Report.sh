#/bin/sh
SEARCH_FOLDER="*"
for f in $SEARCH_FOLDER
do
    if [ -d "$f" ]
    then
	echo "Processing folder $f"
        for ff in $f/*
        do      
            echo "Processing file $ff"
	    filen=$(echo $f"/"$f".c")
            if [ "$ff" == "$filen" ]; then
		rm *.data
		omp2hmpp -f $ff -c $f/codes -l $f/log -r 3 -t 2 -3 -o
	    fi
        done
    fi
done
./bestTimesReport.sh
./generatePlot.sh

