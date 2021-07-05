# echo "cleanup pipipi0Alg pipipi0Alg-00-00 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtpipipi0Algtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtpipipi0Algtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=pipipi0Alg -version=pipipi0Alg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtpipipi0Algtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=pipipi0Alg -version=pipipi0Alg-00-00 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  $* >${cmtpipipi0Algtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtpipipi0Algtempfile}
  unset cmtpipipi0Algtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtpipipi0Algtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtpipipi0Algtempfile}
unset cmtpipipi0Algtempfile
return $cmtcleanupstatus

