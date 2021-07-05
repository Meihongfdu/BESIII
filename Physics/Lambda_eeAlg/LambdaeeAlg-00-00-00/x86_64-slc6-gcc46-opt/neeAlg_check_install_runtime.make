#-- start of make_header -----------------

#====================================
#  Document neeAlg_check_install_runtime
#
#   Generated Sat Sep 19 23:48:35 2020  by wangs
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_neeAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_neeAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_neeAlg_check_install_runtime

neeAlg_tag = $(tag)

#cmt_local_tagfile_neeAlg_check_install_runtime = $(neeAlg_tag)_neeAlg_check_install_runtime.make
cmt_local_tagfile_neeAlg_check_install_runtime = $(bin)$(neeAlg_tag)_neeAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

neeAlg_tag = $(tag)

#cmt_local_tagfile_neeAlg_check_install_runtime = $(neeAlg_tag).make
cmt_local_tagfile_neeAlg_check_install_runtime = $(bin)$(neeAlg_tag).make

endif

include $(cmt_local_tagfile_neeAlg_check_install_runtime)
#-include $(cmt_local_tagfile_neeAlg_check_install_runtime)

ifdef cmt_neeAlg_check_install_runtime_has_target_tag

cmt_final_setup_neeAlg_check_install_runtime = $(bin)setup_neeAlg_check_install_runtime.make
cmt_dependencies_in_neeAlg_check_install_runtime = $(bin)dependencies_neeAlg_check_install_runtime.in
#cmt_final_setup_neeAlg_check_install_runtime = $(bin)neeAlg_neeAlg_check_install_runtimesetup.make
cmt_local_neeAlg_check_install_runtime_makefile = $(bin)neeAlg_check_install_runtime.make

else

cmt_final_setup_neeAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_neeAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_neeAlg_check_install_runtime = $(bin)neeAlgsetup.make
cmt_local_neeAlg_check_install_runtime_makefile = $(bin)neeAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)neeAlgsetup.make

#neeAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'neeAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = neeAlg_check_install_runtime/
#neeAlg_check_install_runtime::
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
neeAlg_check_install_runtime_once = 1
endif

ifdef neeAlg_check_install_runtime_once

neeAlg_check_install_runtimeactionstamp = $(bin)neeAlg_check_install_runtime.actionstamp
#neeAlg_check_install_runtimeactionstamp = neeAlg_check_install_runtime.actionstamp

neeAlg_check_install_runtime :: $(neeAlg_check_install_runtimeactionstamp)
	$(echo) "neeAlg_check_install_runtime ok"
#	@echo neeAlg_check_install_runtime ok

#$(neeAlg_check_install_runtimeactionstamp) :: $(neeAlg_check_install_runtime_dependencies)
$(neeAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/wangs/workarea/boss7.0.5/InstallArea/share
	$(silent) cat /dev/null > $(neeAlg_check_install_runtimeactionstamp)
#	@echo ok > $(neeAlg_check_install_runtimeactionstamp)

neeAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(neeAlg_check_install_runtimeactionstamp)

else

#neeAlg_check_install_runtime :: $(neeAlg_check_install_runtime_dependencies)
neeAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/wangs/workarea/boss7.0.5/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: neeAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(neeAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

neeAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
