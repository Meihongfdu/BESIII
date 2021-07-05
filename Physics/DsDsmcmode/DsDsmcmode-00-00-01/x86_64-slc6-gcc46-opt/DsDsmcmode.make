#-- start of make_header -----------------

#====================================
#  Library DsDsmcmode
#
#   Generated Mon Mar  1 21:21:03 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DsDsmcmode_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DsDsmcmode_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DsDsmcmode

DsDsmcmode_tag = $(tag)

#cmt_local_tagfile_DsDsmcmode = $(DsDsmcmode_tag)_DsDsmcmode.make
cmt_local_tagfile_DsDsmcmode = $(bin)$(DsDsmcmode_tag)_DsDsmcmode.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DsDsmcmode_tag = $(tag)

#cmt_local_tagfile_DsDsmcmode = $(DsDsmcmode_tag).make
cmt_local_tagfile_DsDsmcmode = $(bin)$(DsDsmcmode_tag).make

endif

include $(cmt_local_tagfile_DsDsmcmode)
#-include $(cmt_local_tagfile_DsDsmcmode)

ifdef cmt_DsDsmcmode_has_target_tag

cmt_final_setup_DsDsmcmode = $(bin)setup_DsDsmcmode.make
cmt_dependencies_in_DsDsmcmode = $(bin)dependencies_DsDsmcmode.in
#cmt_final_setup_DsDsmcmode = $(bin)DsDsmcmode_DsDsmcmodesetup.make
cmt_local_DsDsmcmode_makefile = $(bin)DsDsmcmode.make

else

cmt_final_setup_DsDsmcmode = $(bin)setup.make
cmt_dependencies_in_DsDsmcmode = $(bin)dependencies.in
#cmt_final_setup_DsDsmcmode = $(bin)DsDsmcmodesetup.make
cmt_local_DsDsmcmode_makefile = $(bin)DsDsmcmode.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DsDsmcmodesetup.make

#DsDsmcmode :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DsDsmcmode'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DsDsmcmode/
#DsDsmcmode::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DsDsmcmodelibname   = $(bin)$(library_prefix)DsDsmcmode$(library_suffix)
DsDsmcmodelib       = $(DsDsmcmodelibname).a
DsDsmcmodestamp     = $(bin)DsDsmcmode.stamp
DsDsmcmodeshstamp   = $(bin)DsDsmcmode.shstamp

DsDsmcmode :: dirs  DsDsmcmodeLIB
	$(echo) "DsDsmcmode ok"

#-- end of libary_header ----------------

DsDsmcmodeLIB :: $(DsDsmcmodelib) $(DsDsmcmodeshstamp)
	@/bin/echo "------> DsDsmcmode : library ok"

$(DsDsmcmodelib) :: $(bin)DsDsmcmode.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DsDsmcmodelib) $?
	$(lib_silent) $(ranlib) $(DsDsmcmodelib)
	$(lib_silent) cat /dev/null >$(DsDsmcmodestamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DsDsmcmodelibname).$(shlibsuffix) :: $(DsDsmcmodelib) $(DsDsmcmodestamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DsDsmcmode $(DsDsmcmode_shlibflags)

$(DsDsmcmodeshstamp) :: $(DsDsmcmodelibname).$(shlibsuffix)
	@if test -f $(DsDsmcmodelibname).$(shlibsuffix) ; then cat /dev/null >$(DsDsmcmodeshstamp) ; fi

DsDsmcmodeclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)DsDsmcmode.o

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
DsDsmcmodeinstallname = $(library_prefix)DsDsmcmode$(library_suffix).$(shlibsuffix)

DsDsmcmode :: DsDsmcmodeinstall

install :: DsDsmcmodeinstall

DsDsmcmodeinstall :: $(install_dir)/$(DsDsmcmodeinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DsDsmcmodeinstallname) :: $(bin)$(DsDsmcmodeinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DsDsmcmodeinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DsDsmcmodeinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DsDsmcmodeinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DsDsmcmodeinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DsDsmcmodeinstallname) $(install_dir)/$(DsDsmcmodeinstallname); \
	      echo `pwd`/$(DsDsmcmodeinstallname) >$(install_dir)/$(DsDsmcmodeinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DsDsmcmodeinstallname), no installation directory specified"; \
	  fi; \
	fi

DsDsmcmodeclean :: DsDsmcmodeuninstall

uninstall :: DsDsmcmodeuninstall

DsDsmcmodeuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DsDsmcmodeinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DsDsmcmodeinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DsDsmcmodeinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DsDsmcmodeinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DsDsmcmodeclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DsDsmcmode.d

$(bin)$(binobj)DsDsmcmode.d :

$(bin)$(binobj)DsDsmcmode.o : $(cmt_final_setup_DsDsmcmode)

$(bin)$(binobj)DsDsmcmode.o : $(src)DsDsmcmode.cxx
	$(cpp_echo) $(src)DsDsmcmode.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DsDsmcmode_pp_cppflags) $(lib_DsDsmcmode_pp_cppflags) $(DsDsmcmode_pp_cppflags) $(use_cppflags) $(DsDsmcmode_cppflags) $(lib_DsDsmcmode_cppflags) $(DsDsmcmode_cppflags) $(DsDsmcmode_cxx_cppflags)  $(src)DsDsmcmode.cxx
endif
endif

else
$(bin)DsDsmcmode_dependencies.make : $(DsDsmcmode_cxx_dependencies)

$(bin)DsDsmcmode_dependencies.make : $(src)DsDsmcmode.cxx

$(bin)$(binobj)DsDsmcmode.o : $(DsDsmcmode_cxx_dependencies)
	$(cpp_echo) $(src)DsDsmcmode.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DsDsmcmode_pp_cppflags) $(lib_DsDsmcmode_pp_cppflags) $(DsDsmcmode_pp_cppflags) $(use_cppflags) $(DsDsmcmode_cppflags) $(lib_DsDsmcmode_cppflags) $(DsDsmcmode_cppflags) $(DsDsmcmode_cxx_cppflags)  $(src)DsDsmcmode.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DsDsmcmodeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DsDsmcmode.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DsDsmcmodeclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DsDsmcmode
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DsDsmcmode$(library_suffix).a $(library_prefix)DsDsmcmode$(library_suffix).s? DsDsmcmode.stamp DsDsmcmode.shstamp
#-- end of cleanup_library ---------------
