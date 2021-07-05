#!/bin/bash
#code by Hao Xiqing, method from Zhang Lei
#mail haoxq@ihep.ac.cn
###################
#Chang Log
#creat in 2009-09-08 by Hao Xiqing
#test-version
####################
#

#variable only for script itself
MY_LINE_NO=0
MY_FILEE=1000

###variable user difine####################
#The number of data files you want to sub in one job.My_NUM cant't be 1.
MY_NUM=50
#The name of table of path of data file
DST_TABLE=datalist
#The end line of the path table you want to stop. Zero means for all
END=0

#all.sh > $DST_TABLE
TOTAL=`cat $DST_TABLE|wc -l`
if [ $TOTAL -le $END ];then
    END=$TOTAL
fi
if [ $END == 0 ];then
    END=$TOTAL
fi

while read MY_LINE
  do
#    MY_FILE=$((MY_FILE+1))
  MY_LINE_NO=$((MY_LINE_NO+1)) 
  
#for where to begin and end
  if [ $MY_LINE_NO -le $END ]; then
      
      if expr $MY_LINE_NO % $MY_NUM == 1 >/dev/null;then  
	  MY_FILEE=$((MY_FILEE+1))
	  MY_FILE=`echo $MY_FILEE |cut -c 2-6`
	  cat upper.txt>job_$MY_FILE.txt
      fi
      echo \"$MY_LINE\">>job_$MY_FILE.txt
      if expr $MY_LINE_NO % $MY_NUM == 0 >/dev/null;then
	    echo $MY_LINE_NO
      elif [ $MY_LINE_NO -ne $END ];then
	  echo ",">>job_$MY_FILE.txt;
      fi
	if expr $MY_LINE_NO % $MY_NUM == 0 >/dev/null || expr $MY_LINE_NO == $END >/dev/null;then  
	    cat lower.txt>>job_$MY_FILE.txt
	    echo "/besfs/groups/jpsi/jpsigroup/user/vindy/syst/Jpsi_data_$MY_FILE.root' OPT='NEW' TYP='ROOT'\"};">>job_$MY_FILE.txt
	    echo "boss -q job_$MY_FILE.txt">>pbs_jobs
	   
	    sleep 1
	fi
  fi
done < $DST_TABLE
