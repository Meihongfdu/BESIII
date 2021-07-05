# echo "setup neeAlg neeAlg-00-00-01 in /workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtneeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtneeAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtneeAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtneeAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtneeAlgtempfile}
  unset cmtneeAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtneeAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtneeAlgtempfile}
unset cmtneeAlgtempfile
exit $cmtsetupstatus

