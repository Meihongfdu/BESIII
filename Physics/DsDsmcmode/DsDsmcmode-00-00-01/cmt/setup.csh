# echo "setup DsDsmcmode DsDsmcmode-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDsDsmcmodetempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDsDsmcmodetempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DsDsmcmode -version=DsDsmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtDsDsmcmodetempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=DsDsmcmode -version=DsDsmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtDsDsmcmodetempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtDsDsmcmodetempfile}
  unset cmtDsDsmcmodetempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtDsDsmcmodetempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtDsDsmcmodetempfile}
unset cmtDsDsmcmodetempfile
exit $cmtsetupstatus

