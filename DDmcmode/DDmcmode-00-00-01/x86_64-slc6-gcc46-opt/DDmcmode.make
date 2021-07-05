#-- start of make_header -----------------

#====================================
#  Library DDmcmode
#
#   Generated Mon Mar  1 21:23:34 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_DDmcmode_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_DDmcmode_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_DDmcmode

DDmcmode_tag = $(tag)

#cmt_local_tagfile_DDmcmode = $(DDmcmode_tag)_DDmcmode.make
cmt_local_tagfile_DDmcmode = $(bin)$(DDmcmode_tag)_DDmcmode.make

else

tags      = $(tag),$(CMTEXTRATAGS)

DDmcmode_tag = $(tag)

#cmt_local_tagfile_DDmcmode = $(DDmcmode_tag).make
cmt_local_tagfile_DDmcmode = $(bin)$(DDmcmode_tag).make

endif

include $(cmt_local_tagfile_DDmcmode)
#-include $(cmt_local_tagfile_DDmcmode)

ifdef cmt_DDmcmode_has_target_tag

cmt_final_setup_DDmcmode = $(bin)setup_DDmcmode.make
cmt_dependencies_in_DDmcmode = $(bin)dependencies_DDmcmode.in
#cmt_final_setup_DDmcmode = $(bin)DDmcmode_DDmcmodesetup.make
cmt_local_DDmcmode_makefile = $(bin)DDmcmode.make

else

cmt_final_setup_DDmcmode = $(bin)setup.make
cmt_dependencies_in_DDmcmode = $(bin)dependencies.in
#cmt_final_setup_DDmcmode = $(bin)DDmcmodesetup.make
cmt_local_DDmcmode_makefile = $(bin)DDmcmode.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)DDmcmodesetup.make

#DDmcmode :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'DDmcmode'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = DDmcmode/
#DDmcmode::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

DDmcmodelibname   = $(bin)$(library_prefix)DDmcmode$(library_suffix)
DDmcmodelib       = $(DDmcmodelibname).a
DDmcmodestamp     = $(bin)DDmcmode.stamp
DDmcmodeshstamp   = $(bin)DDmcmode.shstamp

DDmcmode :: dirs  DDmcmodeLIB
	$(echo) "DDmcmode ok"

#-- end of libary_header ----------------

DDmcmodeLIB :: $(DDmcmodelib) $(DDmcmodeshstamp)
	@/bin/echo "------> DDmcmode : library ok"

$(DDmcmodelib) :: $(bin)DDmcmode.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(DDmcmodelib) $?
	$(lib_silent) $(ranlib) $(DDmcmodelib)
	$(lib_silent) cat /dev/null >$(DDmcmodestamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(DDmcmodelibname).$(shlibsuffix) :: $(DDmcmodelib) $(DDmcmodestamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" DDmcmode $(DDmcmode_shlibflags)

$(DDmcmodeshstamp) :: $(DDmcmodelibname).$(shlibsuffix)
	@if test -f $(DDmcmodelibname).$(shlibsuffix) ; then cat /dev/null >$(DDmcmodeshstamp) ; fi

DDmcmodeclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)DDmcmode.o

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
DDmcmodeinstallname = $(library_prefix)DDmcmode$(library_suffix).$(shlibsuffix)

DDmcmode :: DDmcmodeinstall

install :: DDmcmodeinstall

DDmcmodeinstall :: $(install_dir)/$(DDmcmodeinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(DDmcmodeinstallname) :: $(bin)$(DDmcmodeinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(DDmcmodeinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(DDmcmodeinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DDmcmodeinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(DDmcmodeinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(DDmcmodeinstallname) $(install_dir)/$(DDmcmodeinstallname); \
	      echo `pwd`/$(DDmcmodeinstallname) >$(install_dir)/$(DDmcmodeinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(DDmcmodeinstallname), no installation directory specified"; \
	  fi; \
	fi

DDmcmodeclean :: DDmcmodeuninstall

uninstall :: DDmcmodeuninstall

DDmcmodeuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(DDmcmodeinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DDmcmodeinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(DDmcmodeinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(DDmcmodeinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),DDmcmodeclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DDmcmode.d

$(bin)$(binobj)DDmcmode.d :

$(bin)$(binobj)DDmcmode.o : $(cmt_final_setup_DDmcmode)

$(bin)$(binobj)DDmcmode.o : $(src)DDmcmode.cxx
	$(cpp_echo) $(src)DDmcmode.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(DDmcmode_pp_cppflags) $(lib_DDmcmode_pp_cppflags) $(DDmcmode_pp_cppflags) $(use_cppflags) $(DDmcmode_cppflags) $(lib_DDmcmode_cppflags) $(DDmcmode_cppflags) $(DDmcmode_cxx_cppflags)  $(src)DDmcmode.cxx
endif
endif

else
$(bin)DDmcmode_dependencies.make : $(DDmcmode_cxx_dependencies)

$(bin)DDmcmode_dependencies.make : $(src)DDmcmode.cxx

$(bin)$(binobj)DDmcmode.o : $(DDmcmode_cxx_dependencies)
	$(cpp_echo) $(src)DDmcmode.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(DDmcmode_pp_cppflags) $(lib_DDmcmode_pp_cppflags) $(DDmcmode_pp_cppflags) $(use_cppflags) $(DDmcmode_cppflags) $(lib_DDmcmode_cppflags) $(DDmcmode_cppflags) $(DDmcmode_cxx_cppflags)  $(src)DDmcmode.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: DDmcmodeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(DDmcmode.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

DDmcmodeclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library DDmcmode
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)DDmcmode$(library_suffix).a $(library_prefix)DDmcmode$(library_suffix).s? DDmcmode.stamp DDmcmode.shstamp
#-- end of cleanup_library ---------------
