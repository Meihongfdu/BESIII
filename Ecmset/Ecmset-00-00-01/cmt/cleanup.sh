# echo "cleanup Ecmset Ecmset-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtEcmsettempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtEcmsettempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=Ecmset -version=Ecmset-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  $* >${cmtEcmsettempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=Ecmset -version=Ecmset-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  $* >${cmtEcmsettempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtEcmsettempfile}
  unset cmtEcmsettempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtEcmsettempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtEcmsettempfile}
unset cmtEcmsettempfile
return $cmtcleanupstatus

