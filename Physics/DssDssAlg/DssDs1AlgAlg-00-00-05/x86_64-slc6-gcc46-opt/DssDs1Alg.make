#-- start of make_header -----------------

#====================================
#  Library DssDs1Alg
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

cmt_DssDs1Alg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DssDs1Alg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DssDs1Alg

DssDs1Alg_tag = $(tag)

#cmt_local_tagfile_DssDs1Alg = $(DssDs1Alg_tag)_DssDs1Alg.make
cmt_local_tagfile_DssDs1Alg = $(bin)$(DssDs1Alg_tag)_DssDs1Alg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DssDs1Alg_tag = $(tag)

#cmt_local_tagfile_DssDs1Alg = $(DssDs1Alg_tag).make
cmt_local_tagfile_DssDs1Alg = $(bin)$(DssDs1Alg_tag).make

endif

include $(cmt_local_tagfile_DssDs1Alg)
#-include $(cmt_local_tagfile_DssDs1Alg)

ifdef cmt_DssDs1Alg_has_target_tag

cmt_final_setup_DssDs1Alg = $(bin)setup_DssDs1Alg.make
cmt_dependencies_in_DssDs1Alg = $(bin)dependencies_DssDs1Alg.in
#cmt_final_setup_DssDs1Alg = $(bin)DssDs1Alg_DssDs1Algsetup.make
cmt_local_DssDs1Alg_makefile = $(bin)DssDs1Alg.make

else

cmt_final_setup_DssDs1Alg = $(bin)setup.make
cmt_dependencies_in_DssDs1Alg = $(bin)dependencies.in
#cmt_final_setup_DssDs1Alg = $(bin)DssDs1Algsetup.make
cmt_local_DssDs1Alg_makefile = $(bin)DssDs1Alg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DssDs1Algsetup.make

#DssDs1Alg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DssDs1Alg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DssDs1Alg/
#DssDs1Alg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DssDs1Alglibname   = $(bin)$(library_prefix)DssDs1Alg$(library_suffix)
DssDs1Alglib       = $(DssDs1Alglibname).a
DssDs1Algstamp     = $(bin)DssDs1Alg.stamp
DssDs1Algshstamp   = $(bin)DssDs1Alg.shstamp

DssDs1Alg :: dirs  DssDs1AlgLIB
	$(echo) "DssDs1Alg ok"

#-- end of libary_header ----------------

DssDs1AlgLIB :: $(DssDs1Alglib) $(DssDs1Algshstamp)
	@/bin/echo "------> DssDs1Alg : library ok"

$(DssDs1Alglib) :: $(bin)RscanDQ.o $(bin)DssInc.o $(bin)DssInc_entries.o $(bin)DssInc_load.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DssDs1Alglib) $?
	$(lib_silent) $(ranlib) $(DssDs1Alglib)
	$(lib_silent) cat /dev/null >$(DssDs1Algstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DssDs1Alglibname).$(shlibsuffix) :: $(DssDs1Alglib) $(DssDs1Algstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DssDs1Alg $(DssDs1Alg_shlibflags)

$(DssDs1Algshstamp) :: $(DssDs1Alglibname).$(shlibsuffix)
	@if test -f $(DssDs1Alglibname).$(shlibsuffix) ; then cat /dev/null >$(DssDs1Algshstamp) ; fi

DssDs1Algclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)RscanDQ.o $(bin)DssInc.o $(bin)DssInc_entries.o $(bin)DssInc_load.o

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
DssDs1Alginstallname = $(library_prefix)DssDs1Alg$(library_suffix).$(shlibsuffix)

DssDs1Alg :: DssDs1Alginstall

install :: DssDs1Alginstall

DssDs1Alginstall :: $(install_dir)/$(DssDs1Alginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DssDs1Alginstallname) :: $(bin)$(DssDs1Alginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DssDs1Alginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DssDs1Alginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DssDs1Alginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DssDs1Alginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DssDs1Alginstallname) $(install_dir)/$(DssDs1Alginstallname); \
	      echo `pwd`/$(DssDs1Alginstallname) >$(install_dir)/$(DssDs1Alginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DssDs1Alginstallname), no installation directory specified"; \
	  fi; \
	fi

DssDs1Algclean :: DssDs1Alguninstall

uninstall :: DssDs1Alguninstall

DssDs1Alguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DssDs1Alginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DssDs1Alginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DssDs1Alginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DssDs1Alginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDs1Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RscanDQ.d

$(bin)$(binobj)RscanDQ.d :

$(bin)$(binobj)RscanDQ.o : $(cmt_final_setup_DssDs1Alg)

$(bin)$(binobj)RscanDQ.o : $(src)RscanDQ.cxx
	$(cpp_echo) $(src)RscanDQ.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(RscanDQ_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(RscanDQ_cppflags) $(RscanDQ_cxx_cppflags)  $(src)RscanDQ.cxx
endif
endif

else
$(bin)DssDs1Alg_dependencies.make : $(RscanDQ_cxx_dependencies)

$(bin)DssDs1Alg_dependencies.make : $(src)RscanDQ.cxx

$(bin)$(binobj)RscanDQ.o : $(RscanDQ_cxx_dependencies)
	$(cpp_echo) $(src)RscanDQ.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(RscanDQ_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(RscanDQ_cppflags) $(RscanDQ_cxx_cppflags)  $(src)RscanDQ.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDs1Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssInc.d

$(bin)$(binobj)DssInc.d :

$(bin)$(binobj)DssInc.o : $(cmt_final_setup_DssDs1Alg)

$(bin)$(binobj)DssInc.o : $(src)DssInc.cxx
	$(cpp_echo) $(src)DssInc.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_cppflags) $(DssInc_cxx_cppflags)  $(src)DssInc.cxx
endif
endif

else
$(bin)DssDs1Alg_dependencies.make : $(DssInc_cxx_dependencies)

$(bin)DssDs1Alg_dependencies.make : $(src)DssInc.cxx

$(bin)$(binobj)DssInc.o : $(DssInc_cxx_dependencies)
	$(cpp_echo) $(src)DssInc.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_cppflags) $(DssInc_cxx_cppflags)  $(src)DssInc.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDs1Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssInc_entries.d

$(bin)$(binobj)DssInc_entries.d :

$(bin)$(binobj)DssInc_entries.o : $(cmt_final_setup_DssDs1Alg)

$(bin)$(binobj)DssInc_entries.o : $(src)components/DssInc_entries.cxx
	$(cpp_echo) $(src)components/DssInc_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_entries_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_entries_cppflags) $(DssInc_entries_cxx_cppflags) -I../src/components $(src)components/DssInc_entries.cxx
endif
endif

else
$(bin)DssDs1Alg_dependencies.make : $(DssInc_entries_cxx_dependencies)

$(bin)DssDs1Alg_dependencies.make : $(src)components/DssInc_entries.cxx

$(bin)$(binobj)DssInc_entries.o : $(DssInc_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/DssInc_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_entries_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_entries_cppflags) $(DssInc_entries_cxx_cppflags) -I../src/components $(src)components/DssInc_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DssDs1Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DssInc_load.d

$(bin)$(binobj)DssInc_load.d :

$(bin)$(binobj)DssInc_load.o : $(cmt_final_setup_DssDs1Alg)

$(bin)$(binobj)DssInc_load.o : $(src)components/DssInc_load.cxx
	$(cpp_echo) $(src)components/DssInc_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_load_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_load_cppflags) $(DssInc_load_cxx_cppflags) -I../src/components $(src)components/DssInc_load.cxx
endif
endif

else
$(bin)DssDs1Alg_dependencies.make : $(DssInc_load_cxx_dependencies)

$(bin)DssDs1Alg_dependencies.make : $(src)components/DssInc_load.cxx

$(bin)$(binobj)DssInc_load.o : $(DssInc_load_cxx_dependencies)
	$(cpp_echo) $(src)components/DssInc_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DssDs1Alg_pp_cppflags) $(lib_DssDs1Alg_pp_cppflags) $(DssInc_load_pp_cppflags) $(use_cppflags) $(DssDs1Alg_cppflags) $(lib_DssDs1Alg_cppflags) $(DssInc_load_cppflags) $(DssInc_load_cxx_cppflags) -I../src/components $(src)components/DssInc_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DssDs1Algclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DssDs1Alg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DssDs1Algclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DssDs1Alg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DssDs1Alg$(library_suffix).a $(library_prefix)DssDs1Alg$(library_suffix).s? DssDs1Alg.stamp DssDs1Alg.shstamp
#-- end of cleanup_library ---------------
