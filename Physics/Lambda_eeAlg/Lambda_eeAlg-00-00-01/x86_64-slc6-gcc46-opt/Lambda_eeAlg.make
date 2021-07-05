#-- start of make_header -----------------

#====================================
#  Library Lambda_eeAlg
#
#   Generated Mon Mar  1 21:23:47 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Lambda_eeAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Lambda_eeAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Lambda_eeAlg

Lambda_eeAlg_tag = $(tag)

#cmt_local_tagfile_Lambda_eeAlg = $(Lambda_eeAlg_tag)_Lambda_eeAlg.make
cmt_local_tagfile_Lambda_eeAlg = $(bin)$(Lambda_eeAlg_tag)_Lambda_eeAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Lambda_eeAlg_tag = $(tag)

#cmt_local_tagfile_Lambda_eeAlg = $(Lambda_eeAlg_tag).make
cmt_local_tagfile_Lambda_eeAlg = $(bin)$(Lambda_eeAlg_tag).make

endif

include $(cmt_local_tagfile_Lambda_eeAlg)
#-include $(cmt_local_tagfile_Lambda_eeAlg)

ifdef cmt_Lambda_eeAlg_has_target_tag

cmt_final_setup_Lambda_eeAlg = $(bin)setup_Lambda_eeAlg.make
cmt_dependencies_in_Lambda_eeAlg = $(bin)dependencies_Lambda_eeAlg.in
#cmt_final_setup_Lambda_eeAlg = $(bin)Lambda_eeAlg_Lambda_eeAlgsetup.make
cmt_local_Lambda_eeAlg_makefile = $(bin)Lambda_eeAlg.make

else

cmt_final_setup_Lambda_eeAlg = $(bin)setup.make
cmt_dependencies_in_Lambda_eeAlg = $(bin)dependencies.in
#cmt_final_setup_Lambda_eeAlg = $(bin)Lambda_eeAlgsetup.make
cmt_local_Lambda_eeAlg_makefile = $(bin)Lambda_eeAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Lambda_eeAlgsetup.make

#Lambda_eeAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Lambda_eeAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Lambda_eeAlg/
#Lambda_eeAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

Lambda_eeAlglibname   = $(bin)$(library_prefix)Lambda_eeAlg$(library_suffix)
Lambda_eeAlglib       = $(Lambda_eeAlglibname).a
Lambda_eeAlgstamp     = $(bin)Lambda_eeAlg.stamp
Lambda_eeAlgshstamp   = $(bin)Lambda_eeAlg.shstamp

Lambda_eeAlg :: dirs  Lambda_eeAlgLIB
	$(echo) "Lambda_eeAlg ok"

#-- end of libary_header ----------------

Lambda_eeAlgLIB :: $(Lambda_eeAlglib) $(Lambda_eeAlgshstamp)
	@/bin/echo "------> Lambda_eeAlg : library ok"

$(Lambda_eeAlglib) :: $(bin)Lambda_ee.o $(bin)Lambda_eeAlg_load.o $(bin)Lambda_eeAlg_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Lambda_eeAlglib) $?
	$(lib_silent) $(ranlib) $(Lambda_eeAlglib)
	$(lib_silent) cat /dev/null >$(Lambda_eeAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Lambda_eeAlglibname).$(shlibsuffix) :: $(Lambda_eeAlglib) $(Lambda_eeAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Lambda_eeAlg $(Lambda_eeAlg_shlibflags)

$(Lambda_eeAlgshstamp) :: $(Lambda_eeAlglibname).$(shlibsuffix)
	@if test -f $(Lambda_eeAlglibname).$(shlibsuffix) ; then cat /dev/null >$(Lambda_eeAlgshstamp) ; fi

Lambda_eeAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Lambda_ee.o $(bin)Lambda_eeAlg_load.o $(bin)Lambda_eeAlg_entries.o

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
Lambda_eeAlginstallname = $(library_prefix)Lambda_eeAlg$(library_suffix).$(shlibsuffix)

Lambda_eeAlg :: Lambda_eeAlginstall

install :: Lambda_eeAlginstall

Lambda_eeAlginstall :: $(install_dir)/$(Lambda_eeAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Lambda_eeAlginstallname) :: $(bin)$(Lambda_eeAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Lambda_eeAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Lambda_eeAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Lambda_eeAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Lambda_eeAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Lambda_eeAlginstallname) $(install_dir)/$(Lambda_eeAlginstallname); \
	      echo `pwd`/$(Lambda_eeAlginstallname) >$(install_dir)/$(Lambda_eeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Lambda_eeAlginstallname), no installation directory specified"; \
	  fi; \
	fi

Lambda_eeAlgclean :: Lambda_eeAlguninstall

uninstall :: Lambda_eeAlguninstall

Lambda_eeAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Lambda_eeAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Lambda_eeAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Lambda_eeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Lambda_eeAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Lambda_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Lambda_ee.d

$(bin)$(binobj)Lambda_ee.d :

$(bin)$(binobj)Lambda_ee.o : $(cmt_final_setup_Lambda_eeAlg)

$(bin)$(binobj)Lambda_ee.o : $(src)Lambda_ee.cxx
	$(cpp_echo) $(src)Lambda_ee.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_ee_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_ee_cppflags) $(Lambda_ee_cxx_cppflags)  $(src)Lambda_ee.cxx
endif
endif

else
$(bin)Lambda_eeAlg_dependencies.make : $(Lambda_ee_cxx_dependencies)

$(bin)Lambda_eeAlg_dependencies.make : $(src)Lambda_ee.cxx

$(bin)$(binobj)Lambda_ee.o : $(Lambda_ee_cxx_dependencies)
	$(cpp_echo) $(src)Lambda_ee.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_ee_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_ee_cppflags) $(Lambda_ee_cxx_cppflags)  $(src)Lambda_ee.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Lambda_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Lambda_eeAlg_load.d

$(bin)$(binobj)Lambda_eeAlg_load.d :

$(bin)$(binobj)Lambda_eeAlg_load.o : $(cmt_final_setup_Lambda_eeAlg)

$(bin)$(binobj)Lambda_eeAlg_load.o : $(src)components/Lambda_eeAlg_load.cxx
	$(cpp_echo) $(src)components/Lambda_eeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_eeAlg_load_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_eeAlg_load_cppflags) $(Lambda_eeAlg_load_cxx_cppflags) -I../src/components $(src)components/Lambda_eeAlg_load.cxx
endif
endif

else
$(bin)Lambda_eeAlg_dependencies.make : $(Lambda_eeAlg_load_cxx_dependencies)

$(bin)Lambda_eeAlg_dependencies.make : $(src)components/Lambda_eeAlg_load.cxx

$(bin)$(binobj)Lambda_eeAlg_load.o : $(Lambda_eeAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/Lambda_eeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_eeAlg_load_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_eeAlg_load_cppflags) $(Lambda_eeAlg_load_cxx_cppflags) -I../src/components $(src)components/Lambda_eeAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Lambda_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Lambda_eeAlg_entries.d

$(bin)$(binobj)Lambda_eeAlg_entries.d :

$(bin)$(binobj)Lambda_eeAlg_entries.o : $(cmt_final_setup_Lambda_eeAlg)

$(bin)$(binobj)Lambda_eeAlg_entries.o : $(src)components/Lambda_eeAlg_entries.cxx
	$(cpp_echo) $(src)components/Lambda_eeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_eeAlg_entries_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_eeAlg_entries_cppflags) $(Lambda_eeAlg_entries_cxx_cppflags) -I../src/components $(src)components/Lambda_eeAlg_entries.cxx
endif
endif

else
$(bin)Lambda_eeAlg_dependencies.make : $(Lambda_eeAlg_entries_cxx_dependencies)

$(bin)Lambda_eeAlg_dependencies.make : $(src)components/Lambda_eeAlg_entries.cxx

$(bin)$(binobj)Lambda_eeAlg_entries.o : $(Lambda_eeAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/Lambda_eeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Lambda_eeAlg_pp_cppflags) $(lib_Lambda_eeAlg_pp_cppflags) $(Lambda_eeAlg_entries_pp_cppflags) $(use_cppflags) $(Lambda_eeAlg_cppflags) $(lib_Lambda_eeAlg_cppflags) $(Lambda_eeAlg_entries_cppflags) $(Lambda_eeAlg_entries_cxx_cppflags) -I../src/components $(src)components/Lambda_eeAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Lambda_eeAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Lambda_eeAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Lambda_eeAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library Lambda_eeAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)Lambda_eeAlg$(library_suffix).a $(library_prefix)Lambda_eeAlg$(library_suffix).s? Lambda_eeAlg.stamp Lambda_eeAlg.shstamp
#-- end of cleanup_library ---------------
