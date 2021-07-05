# echo "setup DsDsmcmode DsDsmcmode-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtDsDsmcmodetempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtDsDsmcmodetempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=DsDsmcmode -version=DsDsmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtDsDsmcmodetempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=DsDsmcmode -version=DsDsmcmode-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtDsDsmcmodetempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtDsDsmcmodetempfile}
  unset cmtDsDsmcmodetempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtDsDsmcmodetempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtDsDsmcmodetempfile}
unset cmtDsDsmcmodetempfile
return $cmtsetupstatus

