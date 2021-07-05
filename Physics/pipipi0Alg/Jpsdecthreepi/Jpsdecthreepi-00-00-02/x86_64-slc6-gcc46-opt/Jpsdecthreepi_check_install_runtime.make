#-- start of make_header -----------------

#====================================
#  Document Jpsdecthreepi_check_install_runtime
#
#   Generated Tue Dec  4 10:56:36 2018  by vindy
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Jpsdecthreepi_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Jpsdecthreepi_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Jpsdecthreepi_check_install_runtime

Jpsdecthreepi_tag = $(tag)

#cmt_local_tagfile_Jpsdecthreepi_check_install_runtime = $(Jpsdecthreepi_tag)_Jpsdecthreepi_check_install_runtime.make
cmt_local_tagfile_Jpsdecthreepi_check_install_runtime = $(bin)$(Jpsdecthreepi_tag)_Jpsdecthreepi_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Jpsdecthreepi_tag = $(tag)

#cmt_local_tagfile_Jpsdecthreepi_check_install_runtime = $(Jpsdecthreepi_tag).make
cmt_local_tagfile_Jpsdecthreepi_check_install_runtime = $(bin)$(Jpsdecthreepi_tag).make

endif

include $(cmt_local_tagfile_Jpsdecthreepi_check_install_runtime)
#-include $(cmt_local_tagfile_Jpsdecthreepi_check_install_runtime)

ifdef cmt_Jpsdecthreepi_check_install_runtime_has_target_tag

cmt_final_setup_Jpsdecthreepi_check_install_runtime = $(bin)setup_Jpsdecthreepi_check_install_runtime.make
cmt_dependencies_in_Jpsdecthreepi_check_install_runtime = $(bin)dependencies_Jpsdecthreepi_check_install_runtime.in
#cmt_final_setup_Jpsdecthreepi_check_install_runtime = $(bin)Jpsdecthreepi_Jpsdecthreepi_check_install_runtimesetup.make
cmt_local_Jpsdecthreepi_check_install_runtime_makefile = $(bin)Jpsdecthreepi_check_install_runtime.make

else

cmt_final_setup_Jpsdecthreepi_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_Jpsdecthreepi_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_Jpsdecthreepi_check_install_runtime = $(bin)Jpsdecthreepisetup.make
cmt_local_Jpsdecthreepi_check_install_runtime_makefile = $(bin)Jpsdecthreepi_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Jpsdecthreepisetup.make

#Jpsdecthreepi_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Jpsdecthreepi_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Jpsdecthreepi_check_install_runtime/
#Jpsdecthreepi_check_install_runtime::
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
Jpsdecthreepi_check_install_runtime_once = 1
endif

ifdef Jpsdecthreepi_check_install_runtime_once

Jpsdecthreepi_check_install_runtimeactionstamp = $(bin)Jpsdecthreepi_check_install_runtime.actionstamp
#Jpsdecthreepi_check_install_runtimeactionstamp = Jpsdecthreepi_check_install_runtime.actionstamp

Jpsdecthreepi_check_install_runtime :: $(Jpsdecthreepi_check_install_runtimeactionstamp)
	$(echo) "Jpsdecthreepi_check_install_runtime ok"
#	@echo Jpsdecthreepi_check_install_runtime ok

#$(Jpsdecthreepi_check_install_runtimeactionstamp) :: $(Jpsdecthreepi_check_install_runtime_dependencies)
$(Jpsdecthreepi_check_install_runtimeactionstamp) ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.3/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs/users/vindy/cmt7.0.3/workarea/InstallArea/share
	$(silent) cat /dev/null > $(Jpsdecthreepi_check_install_runtimeactionstamp)
#	@echo ok > $(Jpsdecthreepi_check_install_runtimeactionstamp)

Jpsdecthreepi_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(Jpsdecthreepi_check_install_runtimeactionstamp)

else

#Jpsdecthreepi_check_install_runtime :: $(Jpsdecthreepi_check_install_runtime_dependencies)
Jpsdecthreepi_check_install_runtime ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.3/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/besfs/users/vindy/cmt7.0.3/workarea/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: Jpsdecthreepi_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Jpsdecthreepi_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Jpsdecthreepi_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
