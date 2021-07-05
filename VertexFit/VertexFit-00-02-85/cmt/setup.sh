# echo "setup VertexFit VertexFit-00-02-85 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtVertexFittempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtVertexFittempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=VertexFit -version=VertexFit-00-02-85 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtVertexFittempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=VertexFit -version=VertexFit-00-02-85 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtVertexFittempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtVertexFittempfile}
  unset cmtVertexFittempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtVertexFittempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtVertexFittempfile}
unset cmtVertexFittempfile
return $cmtsetupstatus

