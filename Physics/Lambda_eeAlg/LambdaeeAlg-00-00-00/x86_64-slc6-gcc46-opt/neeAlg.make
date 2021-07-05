#-- start of make_header -----------------

#====================================
#  Library neeAlg
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

cmt_neeAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_neeAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_neeAlg

neeAlg_tag = $(tag)

#cmt_local_tagfile_neeAlg = $(neeAlg_tag)_neeAlg.make
cmt_local_tagfile_neeAlg = $(bin)$(neeAlg_tag)_neeAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

neeAlg_tag = $(tag)

#cmt_local_tagfile_neeAlg = $(neeAlg_tag).make
cmt_local_tagfile_neeAlg = $(bin)$(neeAlg_tag).make

endif

include $(cmt_local_tagfile_neeAlg)
#-include $(cmt_local_tagfile_neeAlg)

ifdef cmt_neeAlg_has_target_tag

cmt_final_setup_neeAlg = $(bin)setup_neeAlg.make
cmt_dependencies_in_neeAlg = $(bin)dependencies_neeAlg.in
#cmt_final_setup_neeAlg = $(bin)neeAlg_neeAlgsetup.make
cmt_local_neeAlg_makefile = $(bin)neeAlg.make

else

cmt_final_setup_neeAlg = $(bin)setup.make
cmt_dependencies_in_neeAlg = $(bin)dependencies.in
#cmt_final_setup_neeAlg = $(bin)neeAlgsetup.make
cmt_local_neeAlg_makefile = $(bin)neeAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)neeAlgsetup.make

#neeAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'neeAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = neeAlg/
#neeAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

neeAlglibname   = $(bin)$(library_prefix)neeAlg$(library_suffix)
neeAlglib       = $(neeAlglibname).a
neeAlgstamp     = $(bin)neeAlg.stamp
neeAlgshstamp   = $(bin)neeAlg.shstamp

neeAlg :: dirs  neeAlgLIB
	$(echo) "neeAlg ok"

#-- end of libary_header ----------------

neeAlgLIB :: $(neeAlglib) $(neeAlgshstamp)
	@/bin/echo "------> neeAlg : library ok"

$(neeAlglib) :: $(bin)nee.o $(bin)neeAlg_load.o $(bin)neeAlg_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(neeAlglib) $?
	$(lib_silent) $(ranlib) $(neeAlglib)
	$(lib_silent) cat /dev/null >$(neeAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(neeAlglibname).$(shlibsuffix) :: $(neeAlglib) $(neeAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" neeAlg $(neeAlg_shlibflags)

$(neeAlgshstamp) :: $(neeAlglibname).$(shlibsuffix)
	@if test -f $(neeAlglibname).$(shlibsuffix) ; then cat /dev/null >$(neeAlgshstamp) ; fi

neeAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)nee.o $(bin)neeAlg_load.o $(bin)neeAlg_entries.o

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
neeAlginstallname = $(library_prefix)neeAlg$(library_suffix).$(shlibsuffix)

neeAlg :: neeAlginstall

install :: neeAlginstall

neeAlginstall :: $(install_dir)/$(neeAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(neeAlginstallname) :: $(bin)$(neeAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(neeAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(neeAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(neeAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(neeAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(neeAlginstallname) $(install_dir)/$(neeAlginstallname); \
	      echo `pwd`/$(neeAlginstallname) >$(install_dir)/$(neeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(neeAlginstallname), no installation directory specified"; \
	  fi; \
	fi

neeAlgclean :: neeAlguninstall

uninstall :: neeAlguninstall

neeAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(neeAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(neeAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(neeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(neeAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),neeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)nee.d

$(bin)$(binobj)nee.d :

$(bin)$(binobj)nee.o : $(cmt_final_setup_neeAlg)

$(bin)$(binobj)nee.o : $(src)nee.cxx
	$(cpp_echo) $(src)nee.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(nee_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(nee_cppflags) $(nee_cxx_cppflags)  $(src)nee.cxx
endif
endif

else
$(bin)neeAlg_dependencies.make : $(nee_cxx_dependencies)

$(bin)neeAlg_dependencies.make : $(src)nee.cxx

$(bin)$(binobj)nee.o : $(nee_cxx_dependencies)
	$(cpp_echo) $(src)nee.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(nee_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(nee_cppflags) $(nee_cxx_cppflags)  $(src)nee.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),neeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)neeAlg_load.d

$(bin)$(binobj)neeAlg_load.d :

$(bin)$(binobj)neeAlg_load.o : $(cmt_final_setup_neeAlg)

$(bin)$(binobj)neeAlg_load.o : $(src)components/neeAlg_load.cxx
	$(cpp_echo) $(src)components/neeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(neeAlg_load_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(neeAlg_load_cppflags) $(neeAlg_load_cxx_cppflags) -I../src/components $(src)components/neeAlg_load.cxx
endif
endif

else
$(bin)neeAlg_dependencies.make : $(neeAlg_load_cxx_dependencies)

$(bin)neeAlg_dependencies.make : $(src)components/neeAlg_load.cxx

$(bin)$(binobj)neeAlg_load.o : $(neeAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/neeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(neeAlg_load_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(neeAlg_load_cppflags) $(neeAlg_load_cxx_cppflags) -I../src/components $(src)components/neeAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),neeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)neeAlg_entries.d

$(bin)$(binobj)neeAlg_entries.d :

$(bin)$(binobj)neeAlg_entries.o : $(cmt_final_setup_neeAlg)

$(bin)$(binobj)neeAlg_entries.o : $(src)components/neeAlg_entries.cxx
	$(cpp_echo) $(src)components/neeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(neeAlg_entries_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(neeAlg_entries_cppflags) $(neeAlg_entries_cxx_cppflags) -I../src/components $(src)components/neeAlg_entries.cxx
endif
endif

else
$(bin)neeAlg_dependencies.make : $(neeAlg_entries_cxx_dependencies)

$(bin)neeAlg_dependencies.make : $(src)components/neeAlg_entries.cxx

$(bin)$(binobj)neeAlg_entries.o : $(neeAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/neeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(neeAlg_pp_cppflags) $(lib_neeAlg_pp_cppflags) $(neeAlg_entries_pp_cppflags) $(use_cppflags) $(neeAlg_cppflags) $(lib_neeAlg_cppflags) $(neeAlg_entries_cppflags) $(neeAlg_entries_cxx_cppflags) -I../src/components $(src)components/neeAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: neeAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(neeAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

neeAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library neeAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)neeAlg$(library_suffix).a $(library_prefix)neeAlg$(library_suffix).s? neeAlg.stamp neeAlg.shstamp
#-- end of cleanup_library ---------------
