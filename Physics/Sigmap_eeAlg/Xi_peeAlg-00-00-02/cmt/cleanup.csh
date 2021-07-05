# echo "cleanup Xi_peeAlg Xi_peeAlg-00-00-02 in /workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtXi_peeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtXi_peeAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=Xi_peeAlg -version=Xi_peeAlg-00-00-02 -path=/workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics  $* >${cmtXi_peeAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=Xi_peeAlg -version=Xi_peeAlg-00-00-02 -path=/workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics  $* >${cmtXi_peeAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtXi_peeAlgtempfile}
  unset cmtXi_peeAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtXi_peeAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtXi_peeAlgtempfile}
unset cmtXi_peeAlgtempfile
exit $cmtcleanupstatus

