#-- start of make_header -----------------

#====================================
#  Document pmuAlg_check_install_runtime
#
#   Generated Mon Mar  1 21:25:04 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_pmuAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_pmuAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_pmuAlg_check_install_runtime

pmuAlg_tag = $(tag)

#cmt_local_tagfile_pmuAlg_check_install_runtime = $(pmuAlg_tag)_pmuAlg_check_install_runtime.make
cmt_local_tagfile_pmuAlg_check_install_runtime = $(bin)$(pmuAlg_tag)_pmuAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

pmuAlg_tag = $(tag)

#cmt_local_tagfile_pmuAlg_check_install_runtime = $(pmuAlg_tag).make
cmt_local_tagfile_pmuAlg_check_install_runtime = $(bin)$(pmuAlg_tag).make

endif

include $(cmt_local_tagfile_pmuAlg_check_install_runtime)
#-include $(cmt_local_tagfile_pmuAlg_check_install_runtime)

ifdef cmt_pmuAlg_check_install_runtime_has_target_tag

cmt_final_setup_pmuAlg_check_install_runtime = $(bin)setup_pmuAlg_check_install_runtime.make
cmt_dependencies_in_pmuAlg_check_install_runtime = $(bin)dependencies_pmuAlg_check_install_runtime.in
#cmt_final_setup_pmuAlg_check_install_runtime = $(bin)pmuAlg_pmuAlg_check_install_runtimesetup.make
cmt_local_pmuAlg_check_install_runtime_makefile = $(bin)pmuAlg_check_install_runtime.make

else

cmt_final_setup_pmuAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_pmuAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_pmuAlg_check_install_runtime = $(bin)pmuAlgsetup.make
cmt_local_pmuAlg_check_install_runtime_makefile = $(bin)pmuAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)pmuAlgsetup.make

#pmuAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'pmuAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = pmuAlg_check_install_runtime/
#pmuAlg_check_install_runtime::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of cmt_action_runner_header ---------------

ifdef ONCE
pmuAlg_check_install_runtime_once = 1
endif

ifdef pmuAlg_check_install_runtime_once

pmuAlg_check_install_runtimeactionstamp = $(bin)pmuAlg_check_install_runtime.actionstamp
#pmuAlg_check_install_runtimeactionstamp = pmuAlg_check_install_runtime.actionstamp

pmuAlg_check_install_runtime :: $(pmuAlg_check_install_runtimeactionstamp)
	$(echo) "pmuAlg_check_install_runtime ok"
#	@echo pmuAlg_check_install_runtime ok

#$(pmuAlg_check_install_runtimeactionstamp) :: $(pmuAlg_check_install_runtime_dependencies)
$(pmuAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/InstallArea/share
	$(silent) cat /dev/null > $(pmuAlg_check_install_runtimeactionstamp)
#	@echo ok > $(pmuAlg_check_install_runtimeactionstamp)

pmuAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(pmuAlg_check_install_runtimeactionstamp)

else

#pmuAlg_check_install_runtime :: $(pmuAlg_check_install_runtime_dependencies)
pmuAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: pmuAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(pmuAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

pmuAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
