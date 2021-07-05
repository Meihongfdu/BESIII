# echo "setup DDmcmode DDmcmode-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDDmcmodetempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDDmcmodetempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DDmcmode -version=DDmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtDDmcmodetempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=DDmcmode -version=DDmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtDDmcmodetempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtDDmcmodetempfile}
  unset cmtDDmcmodetempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtDDmcmodetempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtDDmcmodetempfile}
unset cmtDDmcmodetempfile
exit $cmtsetupstatus

