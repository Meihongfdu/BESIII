#-- start of make_header -----------------

#====================================
#  Library DstoetamvAlg
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

cmt_DstoetamvAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DstoetamvAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DstoetamvAlg

DstoetamvAlg_tag = $(tag)

#cmt_local_tagfile_DstoetamvAlg = $(DstoetamvAlg_tag)_DstoetamvAlg.make
cmt_local_tagfile_DstoetamvAlg = $(bin)$(DstoetamvAlg_tag)_DstoetamvAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DstoetamvAlg_tag = $(tag)

#cmt_local_tagfile_DstoetamvAlg = $(DstoetamvAlg_tag).make
cmt_local_tagfile_DstoetamvAlg = $(bin)$(DstoetamvAlg_tag).make

endif

include $(cmt_local_tagfile_DstoetamvAlg)
#-include $(cmt_local_tagfile_DstoetamvAlg)

ifdef cmt_DstoetamvAlg_has_target_tag

cmt_final_setup_DstoetamvAlg = $(bin)setup_DstoetamvAlg.make
cmt_dependencies_in_DstoetamvAlg = $(bin)dependencies_DstoetamvAlg.in
#cmt_final_setup_DstoetamvAlg = $(bin)DstoetamvAlg_DstoetamvAlgsetup.make
cmt_local_DstoetamvAlg_makefile = $(bin)DstoetamvAlg.make

else

cmt_final_setup_DstoetamvAlg = $(bin)setup.make
cmt_dependencies_in_DstoetamvAlg = $(bin)dependencies.in
#cmt_final_setup_DstoetamvAlg = $(bin)DstoetamvAlgsetup.make
cmt_local_DstoetamvAlg_makefile = $(bin)DstoetamvAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DstoetamvAlgsetup.make

#DstoetamvAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DstoetamvAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DstoetamvAlg/
#DstoetamvAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DstoetamvAlglibname   = $(bin)$(library_prefix)DstoetamvAlg$(library_suffix)
DstoetamvAlglib       = $(DstoetamvAlglibname).a
DstoetamvAlgstamp     = $(bin)DstoetamvAlg.stamp
DstoetamvAlgshstamp   = $(bin)DstoetamvAlg.shstamp

DstoetamvAlg :: dirs  DstoetamvAlgLIB
	$(echo) "DstoetamvAlg ok"

#-- end of libary_header ----------------

DstoetamvAlgLIB :: $(DstoetamvAlglib) $(DstoetamvAlgshstamp)
	@/bin/echo "------> DstoetamvAlg : library ok"

$(DstoetamvAlglib) :: $(bin)ReadBeamInfFromDb.o $(bin)Match.o $(bin)Dstoetamv.o $(bin)DstoetamvAlg_load.o $(bin)DstoetamvAlg_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DstoetamvAlglib) $?
	$(lib_silent) $(ranlib) $(DstoetamvAlglib)
	$(lib_silent) cat /dev/null >$(DstoetamvAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DstoetamvAlglibname).$(shlibsuffix) :: $(DstoetamvAlglib) $(DstoetamvAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DstoetamvAlg $(DstoetamvAlg_shlibflags)

$(DstoetamvAlgshstamp) :: $(DstoetamvAlglibname).$(shlibsuffix)
	@if test -f $(DstoetamvAlglibname).$(shlibsuffix) ; then cat /dev/null >$(DstoetamvAlgshstamp) ; fi

DstoetamvAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)ReadBeamInfFromDb.o $(bin)Match.o $(bin)Dstoetamv.o $(bin)DstoetamvAlg_load.o $(bin)DstoetamvAlg_entries.o

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
DstoetamvAlginstallname = $(library_prefix)DstoetamvAlg$(library_suffix).$(shlibsuffix)

DstoetamvAlg :: DstoetamvAlginstall

install :: DstoetamvAlginstall

DstoetamvAlginstall :: $(install_dir)/$(DstoetamvAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DstoetamvAlginstallname) :: $(bin)$(DstoetamvAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DstoetamvAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DstoetamvAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DstoetamvAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DstoetamvAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DstoetamvAlginstallname) $(install_dir)/$(DstoetamvAlginstallname); \
	      echo `pwd`/$(DstoetamvAlginstallname) >$(install_dir)/$(DstoetamvAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DstoetamvAlginstallname), no installation directory specified"; \
	  fi; \
	fi

DstoetamvAlgclean :: DstoetamvAlguninstall

uninstall :: DstoetamvAlguninstall

DstoetamvAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DstoetamvAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DstoetamvAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DstoetamvAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DstoetamvAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DstoetamvAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ReadBeamInfFromDb.d

$(bin)$(binobj)ReadBeamInfFromDb.d :

$(bin)$(binobj)ReadBeamInfFromDb.o : $(cmt_final_setup_DstoetamvAlg)

$(bin)$(binobj)ReadBeamInfFromDb.o : $(src)ReadBeamInfFromDb.cxx
	$(cpp_echo) $(src)ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags)  $(src)ReadBeamInfFromDb.cxx
endif
endif

else
$(bin)DstoetamvAlg_dependencies.make : $(ReadBeamInfFromDb_cxx_dependencies)

$(bin)DstoetamvAlg_dependencies.make : $(src)ReadBeamInfFromDb.cxx

$(bin)$(binobj)ReadBeamInfFromDb.o : $(ReadBeamInfFromDb_cxx_dependencies)
	$(cpp_echo) $(src)ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags)  $(src)ReadBeamInfFromDb.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DstoetamvAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Match.d

$(bin)$(binobj)Match.d :

$(bin)$(binobj)Match.o : $(cmt_final_setup_DstoetamvAlg)

$(bin)$(binobj)Match.o : $(src)Match.cxx
	$(cpp_echo) $(src)Match.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(Match_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(Match_cppflags) $(Match_cxx_cppflags)  $(src)Match.cxx
endif
endif

else
$(bin)DstoetamvAlg_dependencies.make : $(Match_cxx_dependencies)

$(bin)DstoetamvAlg_dependencies.make : $(src)Match.cxx

$(bin)$(binobj)Match.o : $(Match_cxx_dependencies)
	$(cpp_echo) $(src)Match.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(Match_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(Match_cppflags) $(Match_cxx_cppflags)  $(src)Match.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DstoetamvAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Dstoetamv.d

$(bin)$(binobj)Dstoetamv.d :

$(bin)$(binobj)Dstoetamv.o : $(cmt_final_setup_DstoetamvAlg)

$(bin)$(binobj)Dstoetamv.o : $(src)Dstoetamv.cxx
	$(cpp_echo) $(src)Dstoetamv.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(Dstoetamv_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(Dstoetamv_cppflags) $(Dstoetamv_cxx_cppflags)  $(src)Dstoetamv.cxx
endif
endif

else
$(bin)DstoetamvAlg_dependencies.make : $(Dstoetamv_cxx_dependencies)

$(bin)DstoetamvAlg_dependencies.make : $(src)Dstoetamv.cxx

$(bin)$(binobj)Dstoetamv.o : $(Dstoetamv_cxx_dependencies)
	$(cpp_echo) $(src)Dstoetamv.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(Dstoetamv_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(Dstoetamv_cppflags) $(Dstoetamv_cxx_cppflags)  $(src)Dstoetamv.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DstoetamvAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DstoetamvAlg_load.d

$(bin)$(binobj)DstoetamvAlg_load.d :

$(bin)$(binobj)DstoetamvAlg_load.o : $(cmt_final_setup_DstoetamvAlg)

$(bin)$(binobj)DstoetamvAlg_load.o : $(src)components/DstoetamvAlg_load.cxx
	$(cpp_echo) $(src)components/DstoetamvAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(DstoetamvAlg_load_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(DstoetamvAlg_load_cppflags) $(DstoetamvAlg_load_cxx_cppflags) -I../src/components $(src)components/DstoetamvAlg_load.cxx
endif
endif

else
$(bin)DstoetamvAlg_dependencies.make : $(DstoetamvAlg_load_cxx_dependencies)

$(bin)DstoetamvAlg_dependencies.make : $(src)components/DstoetamvAlg_load.cxx

$(bin)$(binobj)DstoetamvAlg_load.o : $(DstoetamvAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/DstoetamvAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(DstoetamvAlg_load_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(DstoetamvAlg_load_cppflags) $(DstoetamvAlg_load_cxx_cppflags) -I../src/components $(src)components/DstoetamvAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DstoetamvAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DstoetamvAlg_entries.d

$(bin)$(binobj)DstoetamvAlg_entries.d :

$(bin)$(binobj)DstoetamvAlg_entries.o : $(cmt_final_setup_DstoetamvAlg)

$(bin)$(binobj)DstoetamvAlg_entries.o : $(src)components/DstoetamvAlg_entries.cxx
	$(cpp_echo) $(src)components/DstoetamvAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(DstoetamvAlg_entries_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(DstoetamvAlg_entries_cppflags) $(DstoetamvAlg_entries_cxx_cppflags) -I../src/components $(src)components/DstoetamvAlg_entries.cxx
endif
endif

else
$(bin)DstoetamvAlg_dependencies.make : $(DstoetamvAlg_entries_cxx_dependencies)

$(bin)DstoetamvAlg_dependencies.make : $(src)components/DstoetamvAlg_entries.cxx

$(bin)$(binobj)DstoetamvAlg_entries.o : $(DstoetamvAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/DstoetamvAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DstoetamvAlg_pp_cppflags) $(lib_DstoetamvAlg_pp_cppflags) $(DstoetamvAlg_entries_pp_cppflags) $(use_cppflags) $(DstoetamvAlg_cppflags) $(lib_DstoetamvAlg_cppflags) $(DstoetamvAlg_entries_cppflags) $(DstoetamvAlg_entries_cxx_cppflags) -I../src/components $(src)components/DstoetamvAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DstoetamvAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DstoetamvAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DstoetamvAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DstoetamvAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DstoetamvAlg$(library_suffix).a $(library_prefix)DstoetamvAlg$(library_suffix).s? DstoetamvAlg.stamp DstoetamvAlg.shstamp
#-- end of cleanup_library ---------------
