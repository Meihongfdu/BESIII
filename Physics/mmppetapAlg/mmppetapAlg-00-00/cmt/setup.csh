# echo "setup mmppetapAlg mmppetapAlg-00-00 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtmmppetapAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtmmppetapAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=mmppetapAlg -version=mmppetapAlg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtmmppetapAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=mmppetapAlg -version=mmppetapAlg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtmmppetapAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtmmppetapAlgtempfile}
  unset cmtmmppetapAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtmmppetapAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtmmppetapAlgtempfile}
unset cmtmmppetapAlgtempfile
exit $cmtsetupstatus

