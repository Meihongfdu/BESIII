# echo "setup DssDs1Alg DssDs1Alg-00-00-05 in /workfs/bes/qity/boss705/workarea/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDssDs1Algtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDssDs1Algtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DssDs1Alg -version=DssDs1Alg-00-00-05 -path=/workfs/bes/qity/boss705/workarea/Analysis  -no_cleanup $* >${cmtDssDs1Algtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=DssDs1Alg -version=DssDs1Alg-00-00-05 -path=/workfs/bes/qity/boss705/workarea/Analysis  -no_cleanup $* >${cmtDssDs1Algtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtDssDs1Algtempfile}
  unset cmtDssDs1Algtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtDssDs1Algtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtDssDs1Algtempfile}
unset cmtDssDs1Algtempfile
exit $cmtsetupstatus

