# echo "cleanup DssDs1Alg DssDs1Alg-00-00-05 in /workfs/bes/qity/boss705/workarea/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDssDs1Algtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDssDs1Algtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=DssDs1Alg -version=DssDs1Alg-00-00-05 -path=/workfs/bes/qity/boss705/workarea/Analysis  $* >${cmtDssDs1Algtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=DssDs1Alg -version=DssDs1Alg-00-00-05 -path=/workfs/bes/qity/boss705/workarea/Analysis  $* >${cmtDssDs1Algtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtDssDs1Algtempfile}
  unset cmtDssDs1Algtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtDssDs1Algtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtDssDs1Algtempfile}
unset cmtDssDs1Algtempfile
return $cmtcleanupstatus

