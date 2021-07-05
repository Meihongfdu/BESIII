if [ -f FileList ]; then
mv -f FileList  FileList.bak
fi
find . -name '*.cxx' >FileList
find . -name '*.h' >>FileList
find . -name 'requirements' >>FileList
find . -name '*.txt' >>FileList
while read MY_LINE
do 
if [ ! -d $MY_LINE ]; then
echo $MY_LINE
mv $MY_LINE $MY_LINE.bak
#sed  "s/SingleAlg/DoubleAlg/g" $MY_LINE.bak >$MY_LINE
#sed  "s/Single/Double/g" $MY_LINE.bak >$MY_LINE
#sed  "s/Double/JpsitoSigmabar-lmde/g" $MY_LINE.bak >$MY_LINE
#sed  "s/TTest/JpsitoSigmabar_lmde/g" $MY_LINE.bak >$MY_LINE
sed  "s/eeppetap/pipipi0/g" $MY_LINE.bak >$MY_LINE
rm -f $MY_LINE.bak
fi
done < FileList
