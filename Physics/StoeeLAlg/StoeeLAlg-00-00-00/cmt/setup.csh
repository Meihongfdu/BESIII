# echo "setup StoeeLAlg StoeeLAlg-00-00-00 in /besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtStoeeLAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtStoeeLAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtStoeeLAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtStoeeLAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtStoeeLAlgtempfile}
  unset cmtStoeeLAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtStoeeLAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtStoeeLAlgtempfile}
unset cmtStoeeLAlgtempfile
exit $cmtsetupstatus

