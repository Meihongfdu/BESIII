# echo "cleanup neeAlg neeAlg-00-00-01 in /workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtneeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtneeAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  $* >${cmtneeAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  $* >${cmtneeAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtneeAlgtempfile}
  unset cmtneeAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtneeAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtneeAlgtempfile}
unset cmtneeAlgtempfile
exit $cmtcleanupstatus

