# echo "setup Lambda_eeAlg Lambda_eeAlg-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtLambda_eeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtLambda_eeAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=Lambda_eeAlg -version=Lambda_eeAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtLambda_eeAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=Lambda_eeAlg -version=Lambda_eeAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtLambda_eeAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtLambda_eeAlgtempfile}
  unset cmtLambda_eeAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtLambda_eeAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtLambda_eeAlgtempfile}
unset cmtLambda_eeAlgtempfile
exit $cmtsetupstatus

