# echo "setup DstoetamvAlg DstoetamvAlg-00-00-02 in /besfs5/users/panx/workarea/workarea-7.0.3/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtDstoetamvAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtDstoetamvAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DstoetamvAlg -version=DstoetamvAlg-00-00-02 -path=/besfs5/users/panx/workarea/workarea-7.0.3/Analysis  -no_cleanup $* >${cmtDstoetamvAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=DstoetamvAlg -version=DstoetamvAlg-00-00-02 -path=/besfs5/users/panx/workarea/workarea-7.0.3/Analysis  -no_cleanup $* >${cmtDstoetamvAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtDstoetamvAlgtempfile}
  unset cmtDstoetamvAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtDstoetamvAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtDstoetamvAlgtempfile}
unset cmtDstoetamvAlgtempfile
exit $cmtsetupstatus

