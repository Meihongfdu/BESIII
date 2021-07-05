#-- start of make_header -----------------

#====================================
#  Document DstoetamvAlg_check_install_runtime
#
#   Generated Thu Jan 14 22:17:26 2021  by panx
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DstoetamvAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DstoetamvAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DstoetamvAlg_check_install_runtime

DstoetamvAlg_tag = $(tag)

#cmt_local_tagfile_DstoetamvAlg_check_install_runtime = $(DstoetamvAlg_tag)_DstoetamvAlg_check_install_runtime.make
cmt_local_tagfile_DstoetamvAlg_check_install_runtime = $(bin)$(DstoetamvAlg_tag)_DstoetamvAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DstoetamvAlg_tag = $(tag)

#cmt_local_tagfile_DstoetamvAlg_check_install_runtime = $(DstoetamvAlg_tag).make
cmt_local_tagfile_DstoetamvAlg_check_install_runtime = $(bin)$(DstoetamvAlg_tag).make

endif

include $(cmt_local_tagfile_DstoetamvAlg_check_install_runtime)
#-include $(cmt_local_tagfile_DstoetamvAlg_check_install_runtime)

ifdef cmt_DstoetamvAlg_check_install_runtime_has_target_tag

cmt_final_setup_DstoetamvAlg_check_install_runtime = $(bin)setup_DstoetamvAlg_check_install_runtime.make
cmt_dependencies_in_DstoetamvAlg_check_install_runtime = $(bin)dependencies_DstoetamvAlg_check_install_runtime.in
#cmt_final_setup_DstoetamvAlg_check_install_runtime = $(bin)DstoetamvAlg_DstoetamvAlg_check_install_runtimesetup.make
cmt_local_DstoetamvAlg_check_install_runtime_makefile = $(bin)DstoetamvAlg_check_install_runtime.make

else

cmt_final_setup_DstoetamvAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_DstoetamvAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_DstoetamvAlg_check_install_runtime = $(bin)DstoetamvAlgsetup.make
cmt_local_DstoetamvAlg_check_install_runtime_makefile = $(bin)DstoetamvAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DstoetamvAlgsetup.make

#DstoetamvAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DstoetamvAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DstoetamvAlg_check_install_runtime/
#DstoetamvAlg_check_install_runtime::
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
DstoetamvAlg_check_install_runtime_once = 1
endif

ifdef DstoetamvAlg_check_install_runtime_once

DstoetamvAlg_check_install_runtimeactionstamp = $(bin)DstoetamvAlg_check_install_runtime.actionstamp
#DstoetamvAlg_check_install_runtimeactionstamp = DstoetamvAlg_check_install_runtime.actionstamp

DstoetamvAlg_check_install_runtime :: $(DstoetamvAlg_check_install_runtimeactionstamp)
	$(echo) "DstoetamvAlg_check_install_runtime ok"
#	@echo DstoetamvAlg_check_install_runtime ok

#$(DstoetamvAlg_check_install_runtimeactionstamp) :: $(DstoetamvAlg_check_install_runtime_dependencies)
$(DstoetamvAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.3/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/users/panx/workarea/workarea-7.0.3/InstallArea/share
	$(silent) cat /dev/null > $(DstoetamvAlg_check_install_runtimeactionstamp)
#	@echo ok > $(DstoetamvAlg_check_install_runtimeactionstamp)

DstoetamvAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(DstoetamvAlg_check_install_runtimeactionstamp)

else

#DstoetamvAlg_check_install_runtime :: $(DstoetamvAlg_check_install_runtime_dependencies)
DstoetamvAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.3/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/users/panx/workarea/workarea-7.0.3/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: DstoetamvAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DstoetamvAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DstoetamvAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
