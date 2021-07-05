#-- start of make_header -----------------

#====================================
#  Library Ecmset
#
#   Generated Mon Mar  1 21:22:57 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_Ecmset_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_Ecmset_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_Ecmset

Ecmset_tag = $(tag)

#cmt_local_tagfile_Ecmset = $(Ecmset_tag)_Ecmset.make
cmt_local_tagfile_Ecmset = $(bin)$(Ecmset_tag)_Ecmset.make

else

tags      = $(tag),$(CMTEXTRATAGS)

Ecmset_tag = $(tag)

#cmt_local_tagfile_Ecmset = $(Ecmset_tag).make
cmt_local_tagfile_Ecmset = $(bin)$(Ecmset_tag).make

endif

include $(cmt_local_tagfile_Ecmset)
#-include $(cmt_local_tagfile_Ecmset)

ifdef cmt_Ecmset_has_target_tag

cmt_final_setup_Ecmset = $(bin)setup_Ecmset.make
cmt_dependencies_in_Ecmset = $(bin)dependencies_Ecmset.in
#cmt_final_setup_Ecmset = $(bin)Ecmset_Ecmsetsetup.make
cmt_local_Ecmset_makefile = $(bin)Ecmset.make

else

cmt_final_setup_Ecmset = $(bin)setup.make
cmt_dependencies_in_Ecmset = $(bin)dependencies.in
#cmt_final_setup_Ecmset = $(bin)Ecmsetsetup.make
cmt_local_Ecmset_makefile = $(bin)Ecmset.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)Ecmsetsetup.make

#Ecmset :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'Ecmset'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = Ecmset/
#Ecmset::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

Ecmsetlibname   = $(bin)$(library_prefix)Ecmset$(library_suffix)
Ecmsetlib       = $(Ecmsetlibname).a
Ecmsetstamp     = $(bin)Ecmset.stamp
Ecmsetshstamp   = $(bin)Ecmset.shstamp

Ecmset :: dirs  EcmsetLIB
	$(echo) "Ecmset ok"

#-- end of libary_header ----------------

EcmsetLIB :: $(Ecmsetlib) $(Ecmsetshstamp)
	@/bin/echo "------> Ecmset : library ok"

$(Ecmsetlib) :: $(bin)Ecmset.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(Ecmsetlib) $?
	$(lib_silent) $(ranlib) $(Ecmsetlib)
	$(lib_silent) cat /dev/null >$(Ecmsetstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(Ecmsetlibname).$(shlibsuffix) :: $(Ecmsetlib) $(Ecmsetstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" Ecmset $(Ecmset_shlibflags)

$(Ecmsetshstamp) :: $(Ecmsetlibname).$(shlibsuffix)
	@if test -f $(Ecmsetlibname).$(shlibsuffix) ; then cat /dev/null >$(Ecmsetshstamp) ; fi

Ecmsetclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Ecmset.o

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
Ecmsetinstallname = $(library_prefix)Ecmset$(library_suffix).$(shlibsuffix)

Ecmset :: Ecmsetinstall

install :: Ecmsetinstall

Ecmsetinstall :: $(install_dir)/$(Ecmsetinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(Ecmsetinstallname) :: $(bin)$(Ecmsetinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(Ecmsetinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(Ecmsetinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Ecmsetinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(Ecmsetinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(Ecmsetinstallname) $(install_dir)/$(Ecmsetinstallname); \
	      echo `pwd`/$(Ecmsetinstallname) >$(install_dir)/$(Ecmsetinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(Ecmsetinstallname), no installation directory specified"; \
	  fi; \
	fi

Ecmsetclean :: Ecmsetuninstall

uninstall :: Ecmsetuninstall

Ecmsetuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(Ecmsetinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Ecmsetinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(Ecmsetinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(Ecmsetinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),Ecmsetclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Ecmset.d

$(bin)$(binobj)Ecmset.d :

$(bin)$(binobj)Ecmset.o : $(cmt_final_setup_Ecmset)

$(bin)$(binobj)Ecmset.o : $(src)Ecmset.cxx
	$(cpp_echo) $(src)Ecmset.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(Ecmset_pp_cppflags) $(lib_Ecmset_pp_cppflags) $(Ecmset_pp_cppflags) $(use_cppflags) $(Ecmset_cppflags) $(lib_Ecmset_cppflags) $(Ecmset_cppflags) $(Ecmset_cxx_cppflags)  $(src)Ecmset.cxx
endif
endif

else
$(bin)Ecmset_dependencies.make : $(Ecmset_cxx_dependencies)

$(bin)Ecmset_dependencies.make : $(src)Ecmset.cxx

$(bin)$(binobj)Ecmset.o : $(Ecmset_cxx_dependencies)
	$(cpp_echo) $(src)Ecmset.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(Ecmset_pp_cppflags) $(lib_Ecmset_pp_cppflags) $(Ecmset_pp_cppflags) $(use_cppflags) $(Ecmset_cppflags) $(lib_Ecmset_cppflags) $(Ecmset_cppflags) $(Ecmset_cxx_cppflags)  $(src)Ecmset.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: Ecmsetclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(Ecmset.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

Ecmsetclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library Ecmset
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)Ecmset$(library_suffix).a $(library_prefix)Ecmset$(library_suffix).s? Ecmset.stamp Ecmset.shstamp
#-- end of cleanup_library ---------------
