# echo "setup GammaConv GammaConv-00-00-01 in /workfs/bes/liumeihong/workarea/boss7.0.5/Reconstruction"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtGammaConvtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtGammaConvtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=GammaConv -version=GammaConv-00-00-01 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Reconstruction  -no_cleanup $* >${cmtGammaConvtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=GammaConv -version=GammaConv-00-00-01 -path=/workfs/bes/liumeihong/workarea/boss7.0.5/Reconstruction  -no_cleanup $* >${cmtGammaConvtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtGammaConvtempfile}
  unset cmtGammaConvtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtGammaConvtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtGammaConvtempfile}
unset cmtGammaConvtempfile
exit $cmtsetupstatus

