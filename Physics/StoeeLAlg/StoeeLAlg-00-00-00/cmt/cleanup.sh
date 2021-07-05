# echo "cleanup StoeeLAlg StoeeLAlg-00-00-00 in /besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtStoeeLAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtStoeeLAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  $* >${cmtStoeeLAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=StoeeLAlg -version=StoeeLAlg-00-00-00 -path=/besfs/groups/jpsi/jpsigroup/user/liumeihong/boss/boss7.0.5/Analysis/Physics  $* >${cmtStoeeLAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtStoeeLAlgtempfile}
  unset cmtStoeeLAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtStoeeLAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtStoeeLAlgtempfile}
unset cmtStoeeLAlgtempfile
return $cmtcleanupstatus

