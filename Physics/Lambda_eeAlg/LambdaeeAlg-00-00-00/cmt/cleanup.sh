# echo "cleanup neeAlg neeAlg-00-00-01 in /workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtneeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtneeAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  $* >${cmtneeAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=neeAlg -version=neeAlg-00-00-01 -path=/workfs/bes/wangs/workarea/boss7.0.5/Analysis/Physics  $* >${cmtneeAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtneeAlgtempfile}
  unset cmtneeAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtneeAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtneeAlgtempfile}
unset cmtneeAlgtempfile
return $cmtcleanupstatus

