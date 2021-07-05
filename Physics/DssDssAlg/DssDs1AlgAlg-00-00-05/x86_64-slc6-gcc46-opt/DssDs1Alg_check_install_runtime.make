#-- start of make_header -----------------

#====================================
#  Document DssDs1Alg_check_install_runtime
#
#   Generated Fri Apr 17 10:32:14 2020  by qity
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DssDs1Alg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DssDs1Alg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DssDs1Alg_check_install_runtime

DssDs1Alg_tag = $(tag)

#cmt_local_tagfile_DssDs1Alg_check_install_runtime = $(DssDs1Alg_tag)_DssDs1Alg_check_install_runtime.make
cmt_local_tagfile_DssDs1Alg_check_install_runtime = $(bin)$(DssDs1Alg_tag)_DssDs1Alg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DssDs1Alg_tag = $(tag)

#cmt_local_tagfile_DssDs1Alg_check_install_runtime = $(DssDs1Alg_tag).make
cmt_local_tagfile_DssDs1Alg_check_install_runtime = $(bin)$(DssDs1Alg_tag).make

endif

include $(cmt_local_tagfile_DssDs1Alg_check_install_runtime)
#-include $(cmt_local_tagfile_DssDs1Alg_check_install_runtime)

ifdef cmt_DssDs1Alg_check_install_runtime_has_target_tag

cmt_final_setup_DssDs1Alg_check_install_runtime = $(bin)setup_DssDs1Alg_check_install_runtime.make
cmt_dependencies_in_DssDs1Alg_check_install_runtime = $(bin)dependencies_DssDs1Alg_check_install_runtime.in
#cmt_final_setup_DssDs1Alg_check_install_runtime = $(bin)DssDs1Alg_DssDs1Alg_check_install_runtimesetup.make
cmt_local_DssDs1Alg_check_install_runtime_makefile = $(bin)DssDs1Alg_check_install_runtime.make

else

cmt_final_setup_DssDs1Alg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_DssDs1Alg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_DssDs1Alg_check_install_runtime = $(bin)DssDs1Algsetup.make
cmt_local_DssDs1Alg_check_install_runtime_makefile = $(bin)DssDs1Alg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DssDs1Algsetup.make

#DssDs1Alg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DssDs1Alg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DssDs1Alg_check_install_runtime/
#DssDs1Alg_check_install_runtime::
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
DssDs1Alg_check_install_runtime_once = 1
endif

ifdef DssDs1Alg_check_install_runtime_once

DssDs1Alg_check_install_runtimeactionstamp = $(bin)DssDs1Alg_check_install_runtime.actionstamp
#DssDs1Alg_check_install_runtimeactionstamp = DssDs1Alg_check_install_runtime.actionstamp

DssDs1Alg_check_install_runtime :: $(DssDs1Alg_check_install_runtimeactionstamp)
	$(echo) "DssDs1Alg_check_install_runtime ok"
#	@echo DssDs1Alg_check_install_runtime ok

#$(DssDs1Alg_check_install_runtimeactionstamp) :: $(DssDs1Alg_check_install_runtime_dependencies)
$(DssDs1Alg_check_install_runtimeactionstamp) ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/qity/boss705/workarea/InstallArea/share
	$(silent) cat /dev/null > $(DssDs1Alg_check_install_runtimeactionstamp)
#	@echo ok > $(DssDs1Alg_check_install_runtimeactionstamp)

DssDs1Alg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(DssDs1Alg_check_install_runtimeactionstamp)

else

#DssDs1Alg_check_install_runtime :: $(DssDs1Alg_check_install_runtime_dependencies)
DssDs1Alg_check_install_runtime ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/qity/boss705/workarea/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: DssDs1Alg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DssDs1Alg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DssDs1Alg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
