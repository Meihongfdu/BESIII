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

#sed  "s/JpsitoSigmabar_lmde/JpsitoLmdbar_pe/g" $MY_LINE.bak >$MY_LINE
sed  "s/eeppetap/mmppetap/g" $MY_LINE.bak >$MY_LINE

rm -f $MY_LINE.bak
fi
done < FileList
