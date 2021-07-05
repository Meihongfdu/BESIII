#-- start of make_header -----------------

#====================================
#  Document Xi_peeAlg_check_install_runtime
#
#   Generated Fri Mar 19 19:36:36 2021  by pengcheng6499
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Xi_peeAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Xi_peeAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Xi_peeAlg_check_install_runtime

Xi_peeAlg_tag = $(tag)

#cmt_local_tagfile_Xi_peeAlg_check_install_runtime = $(Xi_peeAlg_tag)_Xi_peeAlg_check_install_runtime.make
cmt_local_tagfile_Xi_peeAlg_check_install_runtime = $(bin)$(Xi_peeAlg_tag)_Xi_peeAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Xi_peeAlg_tag = $(tag)

#cmt_local_tagfile_Xi_peeAlg_check_install_runtime = $(Xi_peeAlg_tag).make
cmt_local_tagfile_Xi_peeAlg_check_install_runtime = $(bin)$(Xi_peeAlg_tag).make

endif

include $(cmt_local_tagfile_Xi_peeAlg_check_install_runtime)
#-include $(cmt_local_tagfile_Xi_peeAlg_check_install_runtime)

ifdef cmt_Xi_peeAlg_check_install_runtime_has_target_tag

cmt_final_setup_Xi_peeAlg_check_install_runtime = $(bin)setup_Xi_peeAlg_check_install_runtime.make
cmt_dependencies_in_Xi_peeAlg_check_install_runtime = $(bin)dependencies_Xi_peeAlg_check_install_runtime.in
#cmt_final_setup_Xi_peeAlg_check_install_runtime = $(bin)Xi_peeAlg_Xi_peeAlg_check_install_runtimesetup.make
cmt_local_Xi_peeAlg_check_install_runtime_makefile = $(bin)Xi_peeAlg_check_install_runtime.make

else

cmt_final_setup_Xi_peeAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_Xi_peeAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_Xi_peeAlg_check_install_runtime = $(bin)Xi_peeAlgsetup.make
cmt_local_Xi_peeAlg_check_install_runtime_makefile = $(bin)Xi_peeAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Xi_peeAlgsetup.make

#Xi_peeAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Xi_peeAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Xi_peeAlg_check_install_runtime/
#Xi_peeAlg_check_install_runtime::
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
Xi_peeAlg_check_install_runtime_once = 1
endif

ifdef Xi_peeAlg_check_install_runtime_once

Xi_peeAlg_check_install_runtimeactionstamp = $(bin)Xi_peeAlg_check_install_runtime.actionstamp
#Xi_peeAlg_check_install_runtimeactionstamp = Xi_peeAlg_check_install_runtime.actionstamp

Xi_peeAlg_check_install_runtime :: $(Xi_peeAlg_check_install_runtimeactionstamp)
	$(echo) "Xi_peeAlg_check_install_runtime ok"
#	@echo Xi_peeAlg_check_install_runtime ok

#$(Xi_peeAlg_check_install_runtimeactionstamp) :: $(Xi_peeAlg_check_install_runtime_dependencies)
$(Xi_peeAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/pengcheng6499/workarea/boss7.0.5/InstallArea/share
	$(silent) cat /dev/null > $(Xi_peeAlg_check_install_runtimeactionstamp)
#	@echo ok > $(Xi_peeAlg_check_install_runtimeactionstamp)

Xi_peeAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(Xi_peeAlg_check_install_runtimeactionstamp)

else

#Xi_peeAlg_check_install_runtime :: $(Xi_peeAlg_check_install_runtime_dependencies)
Xi_peeAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/pengcheng6499/workarea/boss7.0.5/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: Xi_peeAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Xi_peeAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Xi_peeAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
