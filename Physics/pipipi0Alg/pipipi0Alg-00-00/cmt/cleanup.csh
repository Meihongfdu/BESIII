# echo "cleanup pipipi0Alg pipipi0Alg-00-00 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtpipipi0Algtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtpipipi0Algtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=pipipi0Alg -version=pipipi0Alg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtpipipi0Algtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=pipipi0Alg -version=pipipi0Alg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtpipipi0Algtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtpipipi0Algtempfile}
  unset cmtpipipi0Algtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtpipipi0Algtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtpipipi0Algtempfile}
unset cmtpipipi0Algtempfile
exit $cmtcleanupstatus

