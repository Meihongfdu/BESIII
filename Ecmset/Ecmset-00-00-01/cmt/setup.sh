# echo "setup Ecmset Ecmset-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtEcmsettempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtEcmsettempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=Ecmset -version=Ecmset-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtEcmsettempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=Ecmset -version=Ecmset-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtEcmsettempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtEcmsettempfile}
  unset cmtEcmsettempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtEcmsettempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtEcmsettempfile}
unset cmtEcmsettempfile
return $cmtsetupstatus

