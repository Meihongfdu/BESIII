# echo "cleanup DDmcmode DDmcmode-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDDmcmodetempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDDmcmodetempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=DDmcmode -version=DDmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  $* >${cmtDDmcmodetempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=DDmcmode -version=DDmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  $* >${cmtDDmcmodetempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtDDmcmodetempfile}
  unset cmtDDmcmodetempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtDDmcmodetempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtDDmcmodetempfile}
unset cmtDDmcmodetempfile
return $cmtcleanupstatus

