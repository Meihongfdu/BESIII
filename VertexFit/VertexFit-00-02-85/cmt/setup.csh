# echo "setup VertexFit VertexFit-00-02-85 in /besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtVertexFittempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtVertexFittempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=VertexFit -version=VertexFit-00-02-85 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtVertexFittempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=VertexFit -version=VertexFit-00-02-85 -path=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/Analysis  -no_cleanup $* >${cmtVertexFittempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtVertexFittempfile}
  unset cmtVertexFittempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtVertexFittempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtVertexFittempfile}
unset cmtVertexFittempfile
exit $cmtsetupstatus

