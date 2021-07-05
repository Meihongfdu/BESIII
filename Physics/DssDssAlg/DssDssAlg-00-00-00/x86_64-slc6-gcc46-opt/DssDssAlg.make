#-- start of make_header -----------------

#====================================
#  Library DssDssAlg
#
#   Generated Mon Mar  1 21:23:07 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DssDssAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DssDssAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DssDssAlg

DssDssAlg_tag = $(tag)

#cmt_local_tagfile_DssDssAlg = $(DssDssAlg_tag)_DssDssAlg.make
cmt_local_tagfile_DssDssAlg = $(bin)$(DssDssAlg_tag)_DssDssAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DssDssAlg_tag = $(tag)

#cmt_local_tagfile_DssDssAlg = $(DssDssAlg_tag).make
cmt_local_tagfile_DssDssAlg = $(bin)$(DssDssAlg_tag).make

endif

include $(cmt_local_tagfile_DssDssAlg)
#-include $(cmt_local_tagfile_DssDssAlg)

ifdef cmt_DssDssAlg_has_target_tag

cmt_final_setup_DssDssAlg = $(bin)setup_DssDssAlg.make
cmt_dependencies_in_DssDssAlg = $(bin)dependencies_DssDssAlg.in
#cmt_final_setup_DssDssAlg = $(bin)DssDssAlg_DssDssAlgsetup.make
cmt_local_DssDssAlg_makefile = $(bin)DssDssAlg.make

else

cmt_final_setup_DssDssAlg = $(bin)setup.make
cmt_dependencies_in_DssDssAlg = $(bin)dependencies.in
#cmt_final_setup_DssDssAlg = $(bin)DssDssAlgsetup.make
cmt_local_DssDssAlg_makefile = $(bin)DssDssAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DssDssAlgsetup.make

#DssDssAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DssDssAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DssDssAlg/
#DssDssAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DssDssAlglibname   = $(bin)$(library_prefix)DssDssAlg$(library_suffix)
DssDssAlglib       = $(DssDssAlglibname).a
DssDssAlgstamp     = $(bin)DssDssAlg.stamp
DssDssAlgshstamp   = $(bin)DssDssAlg.shstamp

DssDssAlg :: dirs  DssDssAlgLIB
	$(echo) "DssDssAlg ok"

#-- end of libary_header ----------------

DssDssAlgLIB :: $(DssDssAlglib) $(DssDssAlgshstamp)
	@/bin/echo "------> DssDssAlg : library ok"

$(DssDssAlglib) :: $(bin)ReadBeamInfFromDb.o $(bin)Match.o $(bin)DssDss.o $(bin)DssDssAlg_entries.o $(bin)DssDssAlg_load.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DssDssAlglib) $?
	$(lib_silent) $(ranlib) $(DssDssAlglib)
	$(lib_silent) cat /dev/null >$(DssDssAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DssDssAlglibname).$(shlibsuffix) :: $(DssDssAlglib) $(DssDssAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DssDssAlg $(DssDssAlg_shlibflags)

$(DssDssAlgshstamp) :: $(DssDssAlglibname).$(shlibsuffix)
	@if test -f $(DssDssAlglibname).$(shlibsuffix) ; then cat /dev/null >$(DssDssAlgshstamp) ; fi

DssDssAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)ReadBeamInfFromDb.o $(bin)Match.o $(bin)DssDss.o $(bin)DssDssAlg_entries.o $(bin)DssDssAlg_load.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
DssDssAlginstallname = $(library_prefix)DssDssAlg$(library_suffix).$(shlibsuffix)

DssDssAlg :: DssDssAlginstall

install :: DssDssAlginstall

DssDssAlginstall :: $(install_dir)/$(DssDssAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DssDssAlginstallname) :: $(bin)$(DssDssAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DssDssAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DssDssAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DssDssAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DssDssAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DssDssAlginstallname) $(install_dir)/$(DssDssAlginstallname); \
	      echo `pwd`/$(DssDssAlginstallname) >$(install_dir)/$(DssDssAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DssDssAlginstallname), no installation directory specified"; \
	  fi; \
	fi

DssDssAlgclean :: DssDssAlguninstall

uninstall :: DssDssAlguninstall

DssDssAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DssDssAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DssDssAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DssDssAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DssDssAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDssAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ReadBeamInfFromDb.d

$(bin)$(binobj)ReadBeamInfFromDb.d :

$(bin)$(binobj)ReadBeamInfFromDb.o : $(cmt_final_setup_DssDssAlg)

$(bin)$(binobj)ReadBeamInfFromDb.o : $(src)ReadBeamInfFromDb.cxx
	$(cpp_echo) $(src)ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags)  $(src)ReadBeamInfFromDb.cxx
endif
endif

else
$(bin)DssDssAlg_dependencies.make : $(ReadBeamInfFromDb_cxx_dependencies)

$(bin)DssDssAlg_dependencies.make : $(src)ReadBeamInfFromDb.cxx

$(bin)$(binobj)ReadBeamInfFromDb.o : $(ReadBeamInfFromDb_cxx_dependencies)
	$(cpp_echo) $(src)ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags)  $(src)ReadBeamInfFromDb.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDssAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Match.d

$(bin)$(binobj)Match.d :

$(bin)$(binobj)Match.o : $(cmt_final_setup_DssDssAlg)

$(bin)$(binobj)Match.o : $(src)Match.cxx
	$(cpp_echo) $(src)Match.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(Match_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(Match_cppflags) $(Match_cxx_cppflags)  $(src)Match.cxx
endif
endif

else
$(bin)DssDssAlg_dependencies.make : $(Match_cxx_dependencies)

$(bin)DssDssAlg_dependencies.make : $(src)Match.cxx

$(bin)$(binobj)Match.o : $(Match_cxx_dependencies)
	$(cpp_echo) $(src)Match.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(Match_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(Match_cppflags) $(Match_cxx_cppflags)  $(src)Match.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDssAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssDss.d

$(bin)$(binobj)DssDss.d :

$(bin)$(binobj)DssDss.o : $(cmt_final_setup_DssDssAlg)

$(bin)$(binobj)DssDss.o : $(src)DssDss.cxx
	$(cpp_echo) $(src)DssDss.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDss_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDss_cppflags) $(DssDss_cxx_cppflags)  $(src)DssDss.cxx
endif
endif

else
$(bin)DssDssAlg_dependencies.make : $(DssDss_cxx_dependencies)

$(bin)DssDssAlg_dependencies.make : $(src)DssDss.cxx

$(bin)$(binobj)DssDss.o : $(DssDss_cxx_dependencies)
	$(cpp_echo) $(src)DssDss.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDss_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDss_cppflags) $(DssDss_cxx_cppflags)  $(src)DssDss.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDssAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssDssAlg_entries.d

$(bin)$(binobj)DssDssAlg_entries.d :

$(bin)$(binobj)DssDssAlg_entries.o : $(cmt_final_setup_DssDssAlg)

$(bin)$(binobj)DssDssAlg_entries.o : $(src)components/DssDssAlg_entries.cxx
	$(cpp_echo) $(src)components/DssDssAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDssAlg_entries_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDssAlg_entries_cppflags) $(DssDssAlg_entries_cxx_cppflags) -I../src/components $(src)components/DssDssAlg_entries.cxx
endif
endif

else
$(bin)DssDssAlg_dependencies.make : $(DssDssAlg_entries_cxx_dependencies)

$(bin)DssDssAlg_dependencies.make : $(src)components/DssDssAlg_entries.cxx

$(bin)$(binobj)DssDssAlg_entries.o : $(DssDssAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/DssDssAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDssAlg_entries_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDssAlg_entries_cppflags) $(DssDssAlg_entries_cxx_cppflags) -I../src/components $(src)components/DssDssAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDssAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssDssAlg_load.d

$(bin)$(binobj)DssDssAlg_load.d :

$(bin)$(binobj)DssDssAlg_load.o : $(cmt_final_setup_DssDssAlg)

$(bin)$(binobj)DssDssAlg_load.o : $(src)components/DssDssAlg_load.cxx
	$(cpp_echo) $(src)components/DssDssAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDssAlg_load_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDssAlg_load_cppflags) $(DssDssAlg_load_cxx_cppflags) -I../src/components $(src)components/DssDssAlg_load.cxx
endif
endif

else
$(bin)DssDssAlg_dependencies.make : $(DssDssAlg_load_cxx_dependencies)

$(bin)DssDssAlg_dependencies.make : $(src)components/DssDssAlg_load.cxx

$(bin)$(binobj)DssDssAlg_load.o : $(DssDssAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/DssDssAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDssAlg_pp_cppflags) $(lib_DssDssAlg_pp_cppflags) $(DssDssAlg_load_pp_cppflags) $(use_cppflags) $(DssDssAlg_cppflags) $(lib_DssDssAlg_cppflags) $(DssDssAlg_load_cppflags) $(DssDssAlg_load_cxx_cppflags) -I../src/components $(src)components/DssDssAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DssDssAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DssDssAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DssDssAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DssDssAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DssDssAlg$(library_suffix).a $(library_prefix)DssDssAlg$(library_suffix).s? DssDssAlg.stamp DssDssAlg.shstamp
#-- end of cleanup_library ---------------
