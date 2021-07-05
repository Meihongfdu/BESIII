#-- start of make_header -----------------

#====================================
#  Library Jpsdecthreepi
#
#   Generated Fri Jun 29 16:12:09 2018  by vindy
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Jpsdecthreepi_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Jpsdecthreepi_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Jpsdecthreepi

Jpsdecthreepi_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_Jpsdecthreepi = /tmp/CMT_$(Jpsdecthreepi_tag)_Jpsdecthreepi.make$(cmt_lock_pid)
else
#cmt_local_tagfile_Jpsdecthreepi = $(Jpsdecthreepi_tag)_Jpsdecthreepi.make
cmt_local_tagfile_Jpsdecthreepi = $(bin)$(Jpsdecthreepi_tag)_Jpsdecthreepi.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

Jpsdecthreepi_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_Jpsdecthreepi = /tmp/CMT_$(Jpsdecthreepi_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_Jpsdecthreepi = $(Jpsdecthreepi_tag).make
cmt_local_tagfile_Jpsdecthreepi = $(bin)$(Jpsdecthreepi_tag).make
endif

endif

-include $(cmt_local_tagfile_Jpsdecthreepi)

ifdef cmt_Jpsdecthreepi_has_target_tag

ifdef READONLY
cmt_final_setup_Jpsdecthreepi = /tmp/CMT_Jpsdecthreepi_Jpsdecthreepisetup.make
cmt_local_Jpsdecthreepi_makefile = /tmp/CMT_Jpsdecthreepi$(cmt_lock_pid).make
else
cmt_final_setup_Jpsdecthreepi = $(bin)Jpsdecthreepi_Jpsdecthreepisetup.make
cmt_local_Jpsdecthreepi_makefile = $(bin)Jpsdecthreepi.make
endif

else

ifdef READONLY
cmt_final_setup_Jpsdecthreepi = /tmp/CMT_Jpsdecthreepisetup.make
cmt_local_Jpsdecthreepi_makefile = /tmp/CMT_Jpsdecthreepi$(cmt_lock_pid).make
else
cmt_final_setup_Jpsdecthreepi = $(bin)Jpsdecthreepisetup.make
cmt_local_Jpsdecthreepi_makefile = $(bin)Jpsdecthreepi.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_Jpsdecthreepisetup.make
else
cmt_final_setup = $(bin)Jpsdecthreepisetup.make
endif

Jpsdecthreepi ::


ifdef READONLY
Jpsdecthreepi ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Jpsdecthreepi'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Jpsdecthreepi/
Jpsdecthreepi::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

Jpsdecthreepilibname   = $(bin)$(library_prefix)Jpsdecthreepi$(library_suffix)
Jpsdecthreepilib       = $(Jpsdecthreepilibname).a
Jpsdecthreepistamp     = $(bin)Jpsdecthreepi.stamp
Jpsdecthreepishstamp   = $(bin)Jpsdecthreepi.shstamp

Jpsdecthreepi :: dirs  JpsdecthreepiLIB
	$(echo) "Jpsdecthreepi ok"

#-- end of libary_header ----------------

JpsdecthreepiLIB :: $(Jpsdecthreepilib) $(Jpsdecthreepishstamp)
	@/bin/echo "------> Jpsdecthreepi : library ok"

$(Jpsdecthreepilib) :: $(bin)Jpsdecthreepi.o $(bin)Jpsdecthreepi_load.o $(bin)Jpsdecthreepi_entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Jpsdecthreepilib) $?
	$(lib_silent) $(ranlib) $(Jpsdecthreepilib)
	$(lib_silent) cat /dev/null >$(Jpsdecthreepistamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Jpsdecthreepilibname).$(shlibsuffix) :: $(Jpsdecthreepilib) $(Jpsdecthreepistamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Jpsdecthreepi $(Jpsdecthreepi_shlibflags)

$(Jpsdecthreepishstamp) :: $(Jpsdecthreepilibname).$(shlibsuffix)
	@if test -f $(Jpsdecthreepilibname).$(shlibsuffix) ; then cat /dev/null >$(Jpsdecthreepishstamp) ; fi

Jpsdecthreepiclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Jpsdecthreepi.o $(bin)Jpsdecthreepi_load.o $(bin)Jpsdecthreepi_entries.o

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
Jpsdecthreepiinstallname = $(library_prefix)Jpsdecthreepi$(library_suffix).$(shlibsuffix)

Jpsdecthreepi :: Jpsdecthreepiinstall

install :: Jpsdecthreepiinstall

Jpsdecthreepiinstall :: $(install_dir)/$(Jpsdecthreepiinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Jpsdecthreepiinstallname) :: $(bin)$(Jpsdecthreepiinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Jpsdecthreepiinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Jpsdecthreepiinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Jpsdecthreepiinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Jpsdecthreepiinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Jpsdecthreepiinstallname) $(install_dir)/$(Jpsdecthreepiinstallname); \
	      echo `pwd`/$(Jpsdecthreepiinstallname) >$(install_dir)/$(Jpsdecthreepiinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Jpsdecthreepiinstallname), no installation directory specified"; \
	  fi; \
	fi

Jpsdecthreepiclean :: Jpsdecthreepiuninstall

uninstall :: Jpsdecthreepiuninstall

Jpsdecthreepiuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Jpsdecthreepiinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Jpsdecthreepiinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Jpsdecthreepiinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Jpsdecthreepiinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),Jpsdecthreepiclean)

#$(bin)Jpsdecthreepi_dependencies.make :: dirs

ifndef QUICK
$(bin)Jpsdecthreepi_dependencies.make : ../src/Jpsdecthreepi.cxx ../src/components/Jpsdecthreepi_load.cxx ../src/components/Jpsdecthreepi_entries.cxx $(use_requirements) $(cmt_final_setup_Jpsdecthreepi)
	$(echo) "(Jpsdecthreepi.make) Rebuilding $@"; \
	  $(build_dependencies) Jpsdecthreepi -all_sources -out=$@ ../src/Jpsdecthreepi.cxx ../src/components/Jpsdecthreepi_load.cxx ../src/components/Jpsdecthreepi_entries.cxx
endif

#$(Jpsdecthreepi_dependencies)

-include $(bin)Jpsdecthreepi_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)Jpsdecthreepi_dependencies.make : $(Jpsdecthreepi_cxx_dependencies)

$(bin)$(binobj)Jpsdecthreepi.o : $(Jpsdecthreepi_cxx_dependencies)
	$(cpp_echo) $(src)Jpsdecthreepi.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(Jpsdecthreepi_pp_cppflags) $(lib_Jpsdecthreepi_pp_cppflags) $(Jpsdecthreepi_pp_cppflags) $(use_cppflags) $(Jpsdecthreepi_cppflags) $(lib_Jpsdecthreepi_cppflags) $(Jpsdecthreepi_cppflags) $(Jpsdecthreepi_cxx_cppflags)  $(src)Jpsdecthreepi.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)Jpsdecthreepi_dependencies.make : $(Jpsdecthreepi_load_cxx_dependencies)

$(bin)$(binobj)Jpsdecthreepi_load.o : $(Jpsdecthreepi_load_cxx_dependencies)
	$(cpp_echo) $(src)components/Jpsdecthreepi_load.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(Jpsdecthreepi_pp_cppflags) $(lib_Jpsdecthreepi_pp_cppflags) $(Jpsdecthreepi_load_pp_cppflags) $(use_cppflags) $(Jpsdecthreepi_cppflags) $(lib_Jpsdecthreepi_cppflags) $(Jpsdecthreepi_load_cppflags) $(Jpsdecthreepi_load_cxx_cppflags) -I../src/components $(src)components/Jpsdecthreepi_load.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)Jpsdecthreepi_dependencies.make : $(Jpsdecthreepi_entries_cxx_dependencies)

$(bin)$(binobj)Jpsdecthreepi_entries.o : $(Jpsdecthreepi_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/Jpsdecthreepi_entries.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(Jpsdecthreepi_pp_cppflags) $(lib_Jpsdecthreepi_pp_cppflags) $(Jpsdecthreepi_entries_pp_cppflags) $(use_cppflags) $(Jpsdecthreepi_cppflags) $(lib_Jpsdecthreepi_cppflags) $(Jpsdecthreepi_entries_cppflags) $(Jpsdecthreepi_entries_cxx_cppflags) -I../src/components $(src)components/Jpsdecthreepi_entries.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Jpsdecthreepiclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Jpsdecthreepi.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(Jpsdecthreepi.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_Jpsdecthreepi)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsdecthreepi.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsdecthreepi.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(Jpsdecthreepi.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

Jpsdecthreepiclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)Jpsdecthreepi$(library_suffix).a $(binobj)$(library_prefix)Jpsdecthreepi$(library_suffix).s? $(binobj)Jpsdecthreepi.stamp $(binobj)Jpsdecthreepi.shstamp
#-- end of cleanup_library ---------------

