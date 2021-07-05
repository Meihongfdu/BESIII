# echo "setup eeppetapAlg eeppetapAlg-00-04 in /workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmteeppetapAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmteeppetapAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=eeppetapAlg -version=eeppetapAlg-00-04 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmteeppetapAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=eeppetapAlg -version=eeppetapAlg-00-04 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Analysis/Physics  -no_cleanup $* >${cmteeppetapAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmteeppetapAlgtempfile}
  unset cmteeppetapAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmteeppetapAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmteeppetapAlgtempfile}
unset cmteeppetapAlgtempfile
return $cmtsetupstatus

