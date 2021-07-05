#-- start of make_header -----------------

#====================================
#  Document Sigmap_eeAlg_check_install_runtime
#
#   Generated Mon Mar  1 21:24:26 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Sigmap_eeAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Sigmap_eeAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Sigmap_eeAlg_check_install_runtime

Sigmap_eeAlg_tag = $(tag)

#cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime = $(Sigmap_eeAlg_tag)_Sigmap_eeAlg_check_install_runtime.make
cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime = $(bin)$(Sigmap_eeAlg_tag)_Sigmap_eeAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Sigmap_eeAlg_tag = $(tag)

#cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime = $(Sigmap_eeAlg_tag).make
cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime = $(bin)$(Sigmap_eeAlg_tag).make

endif

include $(cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime)
#-include $(cmt_local_tagfile_Sigmap_eeAlg_check_install_runtime)

ifdef cmt_Sigmap_eeAlg_check_install_runtime_has_target_tag

cmt_final_setup_Sigmap_eeAlg_check_install_runtime = $(bin)setup_Sigmap_eeAlg_check_install_runtime.make
cmt_dependencies_in_Sigmap_eeAlg_check_install_runtime = $(bin)dependencies_Sigmap_eeAlg_check_install_runtime.in
#cmt_final_setup_Sigmap_eeAlg_check_install_runtime = $(bin)Sigmap_eeAlg_Sigmap_eeAlg_check_install_runtimesetup.make
cmt_local_Sigmap_eeAlg_check_install_runtime_makefile = $(bin)Sigmap_eeAlg_check_install_runtime.make

else

cmt_final_setup_Sigmap_eeAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_Sigmap_eeAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_Sigmap_eeAlg_check_install_runtime = $(bin)Sigmap_eeAlgsetup.make
cmt_local_Sigmap_eeAlg_check_install_runtime_makefile = $(bin)Sigmap_eeAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Sigmap_eeAlgsetup.make

#Sigmap_eeAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Sigmap_eeAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Sigmap_eeAlg_check_install_runtime/
#Sigmap_eeAlg_check_install_runtime::
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
Sigmap_eeAlg_check_install_runtime_once = 1
endif

ifdef Sigmap_eeAlg_check_install_runtime_once

Sigmap_eeAlg_check_install_runtimeactionstamp = $(bin)Sigmap_eeAlg_check_install_runtime.actionstamp
#Sigmap_eeAlg_check_install_runtimeactionstamp = Sigmap_eeAlg_check_install_runtime.actionstamp

Sigmap_eeAlg_check_install_runtime :: $(Sigmap_eeAlg_check_install_runtimeactionstamp)
	$(echo) "Sigmap_eeAlg_check_install_runtime ok"
#	@echo Sigmap_eeAlg_check_install_runtime ok

#$(Sigmap_eeAlg_check_install_runtimeactionstamp) :: $(Sigmap_eeAlg_check_install_runtime_dependencies)
$(Sigmap_eeAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/InstallArea/share
	$(silent) cat /dev/null > $(Sigmap_eeAlg_check_install_runtimeactionstamp)
#	@echo ok > $(Sigmap_eeAlg_check_install_runtimeactionstamp)

Sigmap_eeAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(Sigmap_eeAlg_check_install_runtimeactionstamp)

else

#Sigmap_eeAlg_check_install_runtime :: $(Sigmap_eeAlg_check_install_runtime_dependencies)
Sigmap_eeAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.5/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs5/groups/jpsi/jpsigroup/user/liumeihong/workarea/boss7.0.5/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: Sigmap_eeAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Sigmap_eeAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Sigmap_eeAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
