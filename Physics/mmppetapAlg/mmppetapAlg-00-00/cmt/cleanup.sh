# echo "cleanup mmppetapAlg mmppetapAlg-00-00 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtmmppetapAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtmmppetapAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=mmppetapAlg -version=mmppetapAlg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtmmppetapAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=mmppetapAlg -version=mmppetapAlg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtmmppetapAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtmmppetapAlgtempfile}
  unset cmtmmppetapAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtmmppetapAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtmmppetapAlgtempfile}
unset cmtmmppetapAlgtempfile
return $cmtcleanupstatus

