# echo "cleanup StoeeLAlg StoeeLAlg-00-00-00 in /besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtStoeeLAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtStoeeLAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  $* >${cmtStoeeLAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  $* >${cmtStoeeLAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtStoeeLAlgtempfile}
  unset cmtStoeeLAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtStoeeLAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtStoeeLAlgtempfile}
unset cmtStoeeLAlgtempfile
exit $cmtcleanupstatus

