#-- start of make_header -----------------

#====================================
#  Library Xi_peeAlg
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

cmt_Xi_peeAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Xi_peeAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Xi_peeAlg

Xi_peeAlg_tag = $(tag)

#cmt_local_tagfile_Xi_peeAlg = $(Xi_peeAlg_tag)_Xi_peeAlg.make
cmt_local_tagfile_Xi_peeAlg = $(bin)$(Xi_peeAlg_tag)_Xi_peeAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Xi_peeAlg_tag = $(tag)

#cmt_local_tagfile_Xi_peeAlg = $(Xi_peeAlg_tag).make
cmt_local_tagfile_Xi_peeAlg = $(bin)$(Xi_peeAlg_tag).make

endif

include $(cmt_local_tagfile_Xi_peeAlg)
#-include $(cmt_local_tagfile_Xi_peeAlg)

ifdef cmt_Xi_peeAlg_has_target_tag

cmt_final_setup_Xi_peeAlg = $(bin)setup_Xi_peeAlg.make
cmt_dependencies_in_Xi_peeAlg = $(bin)dependencies_Xi_peeAlg.in
#cmt_final_setup_Xi_peeAlg = $(bin)Xi_peeAlg_Xi_peeAlgsetup.make
cmt_local_Xi_peeAlg_makefile = $(bin)Xi_peeAlg.make

else

cmt_final_setup_Xi_peeAlg = $(bin)setup.make
cmt_dependencies_in_Xi_peeAlg = $(bin)dependencies.in
#cmt_final_setup_Xi_peeAlg = $(bin)Xi_peeAlgsetup.make
cmt_local_Xi_peeAlg_makefile = $(bin)Xi_peeAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Xi_peeAlgsetup.make

#Xi_peeAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Xi_peeAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Xi_peeAlg/
#Xi_peeAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

Xi_peeAlglibname   = $(bin)$(library_prefix)Xi_peeAlg$(library_suffix)
Xi_peeAlglib       = $(Xi_peeAlglibname).a
Xi_peeAlgstamp     = $(bin)Xi_peeAlg.stamp
Xi_peeAlgshstamp   = $(bin)Xi_peeAlg.shstamp

Xi_peeAlg :: dirs  Xi_peeAlgLIB
	$(echo) "Xi_peeAlg ok"

#-- end of libary_header ----------------

Xi_peeAlgLIB :: $(Xi_peeAlglib) $(Xi_peeAlgshstamp)
	@/bin/echo "------> Xi_peeAlg : library ok"

$(Xi_peeAlglib) :: $(bin)Xi_pee.o $(bin)Lambda_load.o $(bin)Lambda_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Xi_peeAlglib) $?
	$(lib_silent) $(ranlib) $(Xi_peeAlglib)
	$(lib_silent) cat /dev/null >$(Xi_peeAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Xi_peeAlglibname).$(shlibsuffix) :: $(Xi_peeAlglib) $(Xi_peeAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Xi_peeAlg $(Xi_peeAlg_shlibflags)

$(Xi_peeAlgshstamp) :: $(Xi_peeAlglibname).$(shlibsuffix)
	@if test -f $(Xi_peeAlglibname).$(shlibsuffix) ; then cat /dev/null >$(Xi_peeAlgshstamp) ; fi

Xi_peeAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Xi_pee.o $(bin)Lambda_load.o $(bin)Lambda_entries.o

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
Xi_peeAlginstallname = $(library_prefix)Xi_peeAlg$(library_suffix).$(shlibsuffix)

Xi_peeAlg :: Xi_peeAlginstall

install :: Xi_peeAlginstall

Xi_peeAlginstall :: $(install_dir)/$(Xi_peeAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Xi_peeAlginstallname) :: $(bin)$(Xi_peeAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Xi_peeAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Xi_peeAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Xi_peeAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Xi_peeAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Xi_peeAlginstallname) $(install_dir)/$(Xi_peeAlginstallname); \
	      echo `pwd`/$(Xi_peeAlginstallname) >$(install_dir)/$(Xi_peeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Xi_peeAlginstallname), no installation directory specified"; \
	  fi; \
	fi

Xi_peeAlgclean :: Xi_peeAlguninstall

uninstall :: Xi_peeAlguninstall

Xi_peeAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Xi_peeAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Xi_peeAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Xi_peeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Xi_peeAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Xi_peeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Xi_pee.d

$(bin)$(binobj)Xi_pee.d :

$(bin)$(binobj)Xi_pee.o : $(cmt_final_setup_Xi_peeAlg)

$(bin)$(binobj)Xi_pee.o : $(src)Xi_pee.cxx
	$(cpp_echo) $(src)Xi_pee.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Xi_pee_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Xi_pee_cppflags) $(Xi_pee_cxx_cppflags)  $(src)Xi_pee.cxx
endif
endif

else
$(bin)Xi_peeAlg_dependencies.make : $(Xi_pee_cxx_dependencies)

$(bin)Xi_peeAlg_dependencies.make : $(src)Xi_pee.cxx

$(bin)$(binobj)Xi_pee.o : $(Xi_pee_cxx_dependencies)
	$(cpp_echo) $(src)Xi_pee.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Xi_pee_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Xi_pee_cppflags) $(Xi_pee_cxx_cppflags)  $(src)Xi_pee.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Xi_peeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Lambda_load.d

$(bin)$(binobj)Lambda_load.d :

$(bin)$(binobj)Lambda_load.o : $(cmt_final_setup_Xi_peeAlg)

$(bin)$(binobj)Lambda_load.o : $(src)components/Lambda_load.cxx
	$(cpp_echo) $(src)components/Lambda_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Lambda_load_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Lambda_load_cppflags) $(Lambda_load_cxx_cppflags) -I../src/components $(src)components/Lambda_load.cxx
endif
endif

else
$(bin)Xi_peeAlg_dependencies.make : $(Lambda_load_cxx_dependencies)

$(bin)Xi_peeAlg_dependencies.make : $(src)components/Lambda_load.cxx

$(bin)$(binobj)Lambda_load.o : $(Lambda_load_cxx_dependencies)
	$(cpp_echo) $(src)components/Lambda_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Lambda_load_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Lambda_load_cppflags) $(Lambda_load_cxx_cppflags) -I../src/components $(src)components/Lambda_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Xi_peeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Lambda_entries.d

$(bin)$(binobj)Lambda_entries.d :

$(bin)$(binobj)Lambda_entries.o : $(cmt_final_setup_Xi_peeAlg)

$(bin)$(binobj)Lambda_entries.o : $(src)components/Lambda_entries.cxx
	$(cpp_echo) $(src)components/Lambda_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Lambda_entries_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Lambda_entries_cppflags) $(Lambda_entries_cxx_cppflags) -I../src/components $(src)components/Lambda_entries.cxx
endif
endif

else
$(bin)Xi_peeAlg_dependencies.make : $(Lambda_entries_cxx_dependencies)

$(bin)Xi_peeAlg_dependencies.make : $(src)components/Lambda_entries.cxx

$(bin)$(binobj)Lambda_entries.o : $(Lambda_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/Lambda_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Xi_peeAlg_pp_cppflags) $(lib_Xi_peeAlg_pp_cppflags) $(Lambda_entries_pp_cppflags) $(use_cppflags) $(Xi_peeAlg_cppflags) $(lib_Xi_peeAlg_cppflags) $(Lambda_entries_cppflags) $(Lambda_entries_cxx_cppflags) -I../src/components $(src)components/Lambda_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Xi_peeAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Xi_peeAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Xi_peeAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library Xi_peeAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)Xi_peeAlg$(library_suffix).a $(library_prefix)Xi_peeAlg$(library_suffix).s? Xi_peeAlg.stamp Xi_peeAlg.shstamp
#-- end of cleanup_library ---------------
