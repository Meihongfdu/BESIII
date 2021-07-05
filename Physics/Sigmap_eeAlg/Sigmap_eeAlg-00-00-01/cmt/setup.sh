# echo "setup Sigmap_eeAlg Sigmap_eeAlg-00-00-01 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtSigmap_eeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtSigmap_eeAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=Sigmap_eeAlg -version=Sigmap_eeAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtSigmap_eeAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=Sigmap_eeAlg -version=Sigmap_eeAlg-00-00-01 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtSigmap_eeAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtSigmap_eeAlgtempfile}
  unset cmtSigmap_eeAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtSigmap_eeAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtSigmap_eeAlgtempfile}
unset cmtSigmap_eeAlgtempfile
return $cmtsetupstatus

