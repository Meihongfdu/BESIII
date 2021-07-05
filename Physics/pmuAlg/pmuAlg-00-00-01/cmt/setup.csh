# echo "setup pmuAlg pmuAlg-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtpmuAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtpmuAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=pmuAlg -version=pmuAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtpmuAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=pmuAlg -version=pmuAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtpmuAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtpmuAlgtempfile}
  unset cmtpmuAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtpmuAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtpmuAlgtempfile}
unset cmtpmuAlgtempfile
exit $cmtsetupstatus

