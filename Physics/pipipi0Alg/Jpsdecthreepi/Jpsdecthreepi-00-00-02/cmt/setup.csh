# echo "Setting Jpsdecthreepi Jpsdecthreepi-00-00-02 in /besfs/users/vindy/cmt6.6.4/workarea"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118
endif
source ${CMTROOT}/mgr/setup.csh

set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=Jpsdecthreepi -version=Jpsdecthreepi-00-00-02 -path=/besfs/users/vindy/cmt6.6.4/workarea  -no_cleanup $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

