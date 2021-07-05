#-- start of make_header -----------------

#====================================
#  Library Sigmap_eeAlg
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

cmt_Sigmap_eeAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Sigmap_eeAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Sigmap_eeAlg

Sigmap_eeAlg_tag = $(tag)

#cmt_local_tagfile_Sigmap_eeAlg = $(Sigmap_eeAlg_tag)_Sigmap_eeAlg.make
cmt_local_tagfile_Sigmap_eeAlg = $(bin)$(Sigmap_eeAlg_tag)_Sigmap_eeAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Sigmap_eeAlg_tag = $(tag)

#cmt_local_tagfile_Sigmap_eeAlg = $(Sigmap_eeAlg_tag).make
cmt_local_tagfile_Sigmap_eeAlg = $(bin)$(Sigmap_eeAlg_tag).make

endif

include $(cmt_local_tagfile_Sigmap_eeAlg)
#-include $(cmt_local_tagfile_Sigmap_eeAlg)

ifdef cmt_Sigmap_eeAlg_has_target_tag

cmt_final_setup_Sigmap_eeAlg = $(bin)setup_Sigmap_eeAlg.make
cmt_dependencies_in_Sigmap_eeAlg = $(bin)dependencies_Sigmap_eeAlg.in
#cmt_final_setup_Sigmap_eeAlg = $(bin)Sigmap_eeAlg_Sigmap_eeAlgsetup.make
cmt_local_Sigmap_eeAlg_makefile = $(bin)Sigmap_eeAlg.make

else

cmt_final_setup_Sigmap_eeAlg = $(bin)setup.make
cmt_dependencies_in_Sigmap_eeAlg = $(bin)dependencies.in
#cmt_final_setup_Sigmap_eeAlg = $(bin)Sigmap_eeAlgsetup.make
cmt_local_Sigmap_eeAlg_makefile = $(bin)Sigmap_eeAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Sigmap_eeAlgsetup.make

#Sigmap_eeAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Sigmap_eeAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Sigmap_eeAlg/
#Sigmap_eeAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

Sigmap_eeAlglibname   = $(bin)$(library_prefix)Sigmap_eeAlg$(library_suffix)
Sigmap_eeAlglib       = $(Sigmap_eeAlglibname).a
Sigmap_eeAlgstamp     = $(bin)Sigmap_eeAlg.stamp
Sigmap_eeAlgshstamp   = $(bin)Sigmap_eeAlg.shstamp

Sigmap_eeAlg :: dirs  Sigmap_eeAlgLIB
	$(echo) "Sigmap_eeAlg ok"

#-- end of libary_header ----------------

Sigmap_eeAlgLIB :: $(Sigmap_eeAlglib) $(Sigmap_eeAlgshstamp)
	@/bin/echo "------> Sigmap_eeAlg : library ok"

$(Sigmap_eeAlglib) :: $(bin)Sigmap_ee.o $(bin)Sigmap_eeAlg_load.o $(bin)Sigmap_eeAlg_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Sigmap_eeAlglib) $?
	$(lib_silent) $(ranlib) $(Sigmap_eeAlglib)
	$(lib_silent) cat /dev/null >$(Sigmap_eeAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Sigmap_eeAlglibname).$(shlibsuffix) :: $(Sigmap_eeAlglib) $(Sigmap_eeAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Sigmap_eeAlg $(Sigmap_eeAlg_shlibflags)

$(Sigmap_eeAlgshstamp) :: $(Sigmap_eeAlglibname).$(shlibsuffix)
	@if test -f $(Sigmap_eeAlglibname).$(shlibsuffix) ; then cat /dev/null >$(Sigmap_eeAlgshstamp) ; fi

Sigmap_eeAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Sigmap_ee.o $(bin)Sigmap_eeAlg_load.o $(bin)Sigmap_eeAlg_entries.o

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
Sigmap_eeAlginstallname = $(library_prefix)Sigmap_eeAlg$(library_suffix).$(shlibsuffix)

Sigmap_eeAlg :: Sigmap_eeAlginstall

install :: Sigmap_eeAlginstall

Sigmap_eeAlginstall :: $(install_dir)/$(Sigmap_eeAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Sigmap_eeAlginstallname) :: $(bin)$(Sigmap_eeAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Sigmap_eeAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Sigmap_eeAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Sigmap_eeAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Sigmap_eeAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Sigmap_eeAlginstallname) $(install_dir)/$(Sigmap_eeAlginstallname); \
	      echo `pwd`/$(Sigmap_eeAlginstallname) >$(install_dir)/$(Sigmap_eeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Sigmap_eeAlginstallname), no installation directory specified"; \
	  fi; \
	fi

Sigmap_eeAlgclean :: Sigmap_eeAlguninstall

uninstall :: Sigmap_eeAlguninstall

Sigmap_eeAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Sigmap_eeAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Sigmap_eeAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Sigmap_eeAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Sigmap_eeAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Sigmap_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Sigmap_ee.d

$(bin)$(binobj)Sigmap_ee.d :

$(bin)$(binobj)Sigmap_ee.o : $(cmt_final_setup_Sigmap_eeAlg)

$(bin)$(binobj)Sigmap_ee.o : $(src)Sigmap_ee.cxx
	$(cpp_echo) $(src)Sigmap_ee.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_ee_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_ee_cppflags) $(Sigmap_ee_cxx_cppflags)  $(src)Sigmap_ee.cxx
endif
endif

else
$(bin)Sigmap_eeAlg_dependencies.make : $(Sigmap_ee_cxx_dependencies)

$(bin)Sigmap_eeAlg_dependencies.make : $(src)Sigmap_ee.cxx

$(bin)$(binobj)Sigmap_ee.o : $(Sigmap_ee_cxx_dependencies)
	$(cpp_echo) $(src)Sigmap_ee.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_ee_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_ee_cppflags) $(Sigmap_ee_cxx_cppflags)  $(src)Sigmap_ee.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Sigmap_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Sigmap_eeAlg_load.d

$(bin)$(binobj)Sigmap_eeAlg_load.d :

$(bin)$(binobj)Sigmap_eeAlg_load.o : $(cmt_final_setup_Sigmap_eeAlg)

$(bin)$(binobj)Sigmap_eeAlg_load.o : $(src)components/Sigmap_eeAlg_load.cxx
	$(cpp_echo) $(src)components/Sigmap_eeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_eeAlg_load_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_eeAlg_load_cppflags) $(Sigmap_eeAlg_load_cxx_cppflags) -I../src/components $(src)components/Sigmap_eeAlg_load.cxx
endif
endif

else
$(bin)Sigmap_eeAlg_dependencies.make : $(Sigmap_eeAlg_load_cxx_dependencies)

$(bin)Sigmap_eeAlg_dependencies.make : $(src)components/Sigmap_eeAlg_load.cxx

$(bin)$(binobj)Sigmap_eeAlg_load.o : $(Sigmap_eeAlg_load_cxx_dependencies)
	$(cpp_echo) $(src)components/Sigmap_eeAlg_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_eeAlg_load_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_eeAlg_load_cppflags) $(Sigmap_eeAlg_load_cxx_cppflags) -I../src/components $(src)components/Sigmap_eeAlg_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Sigmap_eeAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Sigmap_eeAlg_entries.d

$(bin)$(binobj)Sigmap_eeAlg_entries.d :

$(bin)$(binobj)Sigmap_eeAlg_entries.o : $(cmt_final_setup_Sigmap_eeAlg)

$(bin)$(binobj)Sigmap_eeAlg_entries.o : $(src)components/Sigmap_eeAlg_entries.cxx
	$(cpp_echo) $(src)components/Sigmap_eeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_eeAlg_entries_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_eeAlg_entries_cppflags) $(Sigmap_eeAlg_entries_cxx_cppflags) -I../src/components $(src)components/Sigmap_eeAlg_entries.cxx
endif
endif

else
$(bin)Sigmap_eeAlg_dependencies.make : $(Sigmap_eeAlg_entries_cxx_dependencies)

$(bin)Sigmap_eeAlg_dependencies.make : $(src)components/Sigmap_eeAlg_entries.cxx

$(bin)$(binobj)Sigmap_eeAlg_entries.o : $(Sigmap_eeAlg_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/Sigmap_eeAlg_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Sigmap_eeAlg_pp_cppflags) $(lib_Sigmap_eeAlg_pp_cppflags) $(Sigmap_eeAlg_entries_pp_cppflags) $(use_cppflags) $(Sigmap_eeAlg_cppflags) $(lib_Sigmap_eeAlg_cppflags) $(Sigmap_eeAlg_entries_cppflags) $(Sigmap_eeAlg_entries_cxx_cppflags) -I../src/components $(src)components/Sigmap_eeAlg_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Sigmap_eeAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Sigmap_eeAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Sigmap_eeAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library Sigmap_eeAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)Sigmap_eeAlg$(library_suffix).a $(library_prefix)Sigmap_eeAlg$(library_suffix).s? Sigmap_eeAlg.stamp Sigmap_eeAlg.shstamp
#-- end of cleanup_library ---------------
