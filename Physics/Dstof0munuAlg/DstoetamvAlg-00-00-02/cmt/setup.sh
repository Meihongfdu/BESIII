# echo "setup DstoetamvAlg DstoetamvAlg-00-00-02 in /besfs5/users/panx/workarea/workarea-7.0.3/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDstoetamvAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDstoetamvAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=DstoetamvAlg -version=DstoetamvAlg-00-00-02 -path=/besfs5/users/panx/workarea/workarea-7.0.3/Analysis  -no_cleanup $* >${cmtDstoetamvAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=DstoetamvAlg -version=DstoetamvAlg-00-00-02 -path=/besfs5/users/panx/workarea/workarea-7.0.3/Analysis  -no_cleanup $* >${cmtDstoetamvAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtDstoetamvAlgtempfile}
  unset cmtDstoetamvAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtDstoetamvAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtDstoetamvAlgtempfile}
unset cmtDstoetamvAlgtempfile
return $cmtsetupstatus

