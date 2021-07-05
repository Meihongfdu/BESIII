# echo "setup Xi_peeAlg Xi_peeAlg-00-00-02 in /workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtXi_peeAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtXi_peeAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=Xi_peeAlg -version=Xi_peeAlg-00-00-02 -path=/workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtXi_peeAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=Xi_peeAlg -version=Xi_peeAlg-00-00-02 -path=/workfs/bes/pengcheng6499/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmtXi_peeAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtXi_peeAlgtempfile}
  unset cmtXi_peeAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtXi_peeAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtXi_peeAlgtempfile}
unset cmtXi_peeAlgtempfile
return $cmtsetupstatus

