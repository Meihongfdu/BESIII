# echo "cleanup DssDssAlg DssDssAlg-00-00-00 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDssDssAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDssDssAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=DssDssAlg -version=DssDssAlg-00-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtDssDssAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=DssDssAlg -version=DssDssAlg-00-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtDssDssAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtDssDssAlgtempfile}
  unset cmtDssDssAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtDssDssAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtDssDssAlgtempfile}
unset cmtDssDssAlgtempfile
return $cmtcleanupstatus

