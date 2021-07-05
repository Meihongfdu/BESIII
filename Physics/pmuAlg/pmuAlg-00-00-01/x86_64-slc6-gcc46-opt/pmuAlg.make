#-- start of make_header -----------------

#====================================
#  Library pmuAlg
#
#   Generated Mon Mar  1 21:25:04 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_pmuAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_pmuAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_pmuAlg

pmuAlg_tag = $(tag)

#cmt_local_tagfile_pmuAlg = $(pmuAlg_tag)_pmuAlg.make
cmt_local_tagfile_pmuAlg = $(bin)$(pmuAlg_tag)_pmuAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

pmuAlg_tag = $(tag)

#cmt_local_tagfile_pmuAlg = $(pmuAlg_tag).make
cmt_local_tagfile_pmuAlg = $(bin)$(pmuAlg_tag).make

endif

include $(cmt_local_tagfile_pmuAlg)
#-include $(cmt_local_tagfile_pmuAlg)

ifdef cmt_pmuAlg_has_target_tag

cmt_final_setup_pmuAlg = $(bin)setup_pmuAlg.make
cmt_dependencies_in_pmuAlg = $(bin)dependencies_pmuAlg.in
#cmt_final_setup_pmuAlg = $(bin)pmuAlg_pmuAlgsetup.make
cmt_local_pmuAlg_makefile = $(bin)pmuAlg.make

else

cmt_final_setup_pmuAlg = $(bin)setup.make
cmt_dependencies_in_pmuAlg = $(bin)dependencies.in
#cmt_final_setup_pmuAlg = $(bin)pmuAlgsetup.make
cmt_local_pmuAlg_makefile = $(bin)pmuAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)pmuAlgsetup.make

#pmuAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'pmuAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = pmuAlg/
#pmuAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

pmuAlglibname   = $(bin)$(library_prefix)pmuAlg$(library_suffix)
pmuAlglib       = $(pmuAlglibname).a
pmuAlgstamp     = $(bin)pmuAlg.stamp
pmuAlgshstamp   = $(bin)pmuAlg.shstamp

pmuAlg :: dirs  pmuAlgLIB
	$(echo) "pmuAlg ok"

#-- end of libary_header ----------------

pmuAlgLIB :: $(pmuAlglib) $(pmuAlgshstamp)
	@/bin/echo "------> pmuAlg : library ok"

$(pmuAlglib) :: $(bin)pmu.o $(bin)pmuAlg_load.o $(bin)pmuAlg_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(pmuAlglib) $?
	$(lib_silent) $(ranlib) $(pmuAlglib)
	$(lib_silent) cat /dev/null >$(pmuAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(pmuAlglibname).$(shlibsuffix) :: $(pmuAlglib) $(pmuAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" pmuAlg $(pmuAlg_shlibflags)

$(pmuAlgshstamp) :: $(pmuAlglibname).$(shlibsuffix)
	@if test -f $(pmuAlglibname).$(shlibsuffix) ; then cat /dev/null >$(pmuAlgshstamp) ; fi

pmuAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)pmu.o $(bin)pmuAlg_load.o $(bin)pmuAlg_entries.o

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
pmuAlginstallname = $(library_prefix)pmuAlg$(library_suffix).$(shlibsuffix)

pmuAlg :: pmuAlginstall

install :: pmuAlginstall

pmuAlginstall :: $(install_dir)/$(pmuAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(pmuAlginstallname) :: $(bin)$(pmuAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(pmuAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(pmuAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(pmuAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(pmuAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(pmuAlginstallname) $(install_dir)/$(pmuAlginstallname); \
	      echo `pwd`/$(pmuAlginstallname) >$(install_dir)/$(pmuAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(pmuAlginstallname), no installation directory specified"; \
	  fi; \
	fi

pmuAlgclean :: pmuAlguninstall

uninstall :: pmuAlguninstall

pmuAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(pmuAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(pmuAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(pmuAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(pmuAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pmuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)pmu.d

$(bin)$(binobj)pmu.d :

$(bin)$(binobj)pmu.o : $(cmt_final_setup_pmuAlg)

$(bin)$(binobj)pmu.o : $(src)pmu.cxx
	$(cpp_echo) $(src)pmu.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmu_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmu_cppflags) $(pmu_cxx_cppflags)  $(src)pmu.cxx
endif
endif

else
$(bin)pmuAlg_dependencies.make : $(pmu_cxx_dependencies)

$(bin)pmuAlg_dependencies.make : $(src)pmu.cxx

$(bin)$(binobj)pmu.o : $(pmu_cxx_dependencies)
	$(cpp_echo) $(src)pmu.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmu_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmu_cppflags) $(pmu_cxx_cppflags)  $(src)pmu.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pmuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)pmuAlg_load.d

$(bin)$(binobj)pmuAlg_load.d :

$(bin)$(binobj)pmuAlg_load.o : $(cmt_final_setup_pmuAlg)

$(bin)$(binobj)pmuAlg_load.o : $(src)components/pmuAlg_load.cxx
	$(cpp_echo) $(src)components/pmuAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmuAlg_load_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmuAlg_load_cppflags) $(pmuAlg_load_cxx_cppflags) -I../src/components $(src)components/pmuAlg_load.cxx
endif
endif

else
$(bin)pmuAlg_dependencies.make : $(pmuAlg_load_cxx_dependencies)

$(bin)pmuAlg_dependencies.make : $(src)components/pmuAlg_load.cxx

$(bin)$(binobj)pmuAlg_load.o : $(pmuAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/pmuAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmuAlg_load_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmuAlg_load_cppflags) $(pmuAlg_load_cxx_cppflags) -I../src/components $(src)components/pmuAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pmuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)pmuAlg_entries.d

$(bin)$(binobj)pmuAlg_entries.d :

$(bin)$(binobj)pmuAlg_entries.o : $(cmt_final_setup_pmuAlg)

$(bin)$(binobj)pmuAlg_entries.o : $(src)components/pmuAlg_entries.cxx
	$(cpp_echo) $(src)components/pmuAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmuAlg_entries_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmuAlg_entries_cppflags) $(pmuAlg_entries_cxx_cppflags) -I../src/components $(src)components/pmuAlg_entries.cxx
endif
endif

else
$(bin)pmuAlg_dependencies.make : $(pmuAlg_entries_cxx_dependencies)

$(bin)pmuAlg_dependencies.make : $(src)components/pmuAlg_entries.cxx

$(bin)$(binobj)pmuAlg_entries.o : $(pmuAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/pmuAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pmuAlg_pp_cppflags) $(lib_pmuAlg_pp_cppflags) $(pmuAlg_entries_pp_cppflags) $(use_cppflags) $(pmuAlg_cppflags) $(lib_pmuAlg_cppflags) $(pmuAlg_entries_cppflags) $(pmuAlg_entries_cxx_cppflags) -I../src/components $(src)components/pmuAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: pmuAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(pmuAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

pmuAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library pmuAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)pmuAlg$(library_suffix).a $(library_prefix)pmuAlg$(library_suffix).s? pmuAlg.stamp pmuAlg.shstamp
#-- end of cleanup_library ---------------
