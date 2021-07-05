# echo "setup eeppetapAlg eeppetapAlg-00-02 in /workfs/bes/liumeihong/workarea/boss7.0.3/Analysis/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmteeppetapAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmteeppetapAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=eeppetapAlg -version=eeppetapAlg-00-02 -path=/workfs/bes/liumeihong/workarea/boss7.0.3/Analysis/Physics  -no_cleanup $* >${cmteeppetapAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=eeppetapAlg -version=eeppetapAlg-00-02 -path=/workfs/bes/liumeihong/workarea/boss7.0.3/Analysis/Physics  -no_cleanup $* >${cmteeppetapAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmteeppetapAlgtempfile}
  unset cmteeppetapAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmteeppetapAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmteeppetapAlgtempfile}
unset cmteeppetapAlgtempfile
exit $cmtsetupstatus

