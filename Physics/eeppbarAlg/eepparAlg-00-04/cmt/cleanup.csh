# echo "cleanup eeppetapAlg eeppetapAlg-00-04 in /workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmteeppetapAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmteeppetapAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=eeppetapAlg -version=eeppetapAlg-00-04 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmteeppetapAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=eeppetapAlg -version=eeppetapAlg-00-04 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmteeppetapAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmteeppetapAlgtempfile}
  unset cmteeppetapAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmteeppetapAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmteeppetapAlgtempfile}
unset cmteeppetapAlgtempfile
exit $cmtcleanupstatus

