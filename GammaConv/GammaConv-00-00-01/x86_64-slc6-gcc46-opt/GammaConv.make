#-- start of make_header -----------------

#====================================
#  Library GammaConv
#
#   Generated Sat Oct 24 17:45:28 2020  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_GammaConv_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_GammaConv_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_GammaConv

GammaConv_tag = $(tag)

#cmt_local_tagfile_GammaConv = $(GammaConv_tag)_GammaConv.make
cmt_local_tagfile_GammaConv = $(bin)$(GammaConv_tag)_GammaConv.make

else

tags      = $(tag),$(CMTEXTRATAGS)

GammaConv_tag = $(tag)

#cmt_local_tagfile_GammaConv = $(GammaConv_tag).make
cmt_local_tagfile_GammaConv = $(bin)$(GammaConv_tag).make

endif

include $(cmt_local_tagfile_GammaConv)
#-include $(cmt_local_tagfile_GammaConv)

ifdef cmt_GammaConv_has_target_tag

cmt_final_setup_GammaConv = $(bin)setup_GammaConv.make
cmt_dependencies_in_GammaConv = $(bin)dependencies_GammaConv.in
#cmt_final_setup_GammaConv = $(bin)GammaConv_GammaConvsetup.make
cmt_local_GammaConv_makefile = $(bin)GammaConv.make

else

cmt_final_setup_GammaConv = $(bin)setup.make
cmt_dependencies_in_GammaConv = $(bin)dependencies.in
#cmt_final_setup_GammaConv = $(bin)GammaConvsetup.make
cmt_local_GammaConv_makefile = $(bin)GammaConv.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)GammaConvsetup.make

#GammaConv :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'GammaConv'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = GammaConv/
#GammaConv::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

GammaConvlibname   = $(bin)$(library_prefix)GammaConv$(library_suffix)
GammaConvlib       = $(GammaConvlibname).a
GammaConvstamp     = $(bin)GammaConv.stamp
GammaConvshstamp   = $(bin)GammaConv.shstamp

GammaConv :: dirs  GammaConvLIB
	$(echo) "GammaConv ok"

#-- end of libary_header ----------------

GammaConvLIB :: $(GammaConvlib) $(GammaConvshstamp)
	@/bin/echo "------> GammaConv : library ok"

$(GammaConvlib) :: $(bin)GammaConv.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(GammaConvlib) $?
	$(lib_silent) $(ranlib) $(GammaConvlib)
	$(lib_silent) cat /dev/null >$(GammaConvstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(GammaConvlibname).$(shlibsuffix) :: $(GammaConvlib) $(GammaConvstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" GammaConv $(GammaConv_shlibflags)

$(GammaConvshstamp) :: $(GammaConvlibname).$(shlibsuffix)
	@if test -f $(GammaConvlibname).$(shlibsuffix) ; then cat /dev/null >$(GammaConvshstamp) ; fi

GammaConvclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)GammaConv.o

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
GammaConvinstallname = $(library_prefix)GammaConv$(library_suffix).$(shlibsuffix)

GammaConv :: GammaConvinstall

install :: GammaConvinstall

GammaConvinstall :: $(install_dir)/$(GammaConvinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(GammaConvinstallname) :: $(bin)$(GammaConvinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(GammaConvinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(GammaConvinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(GammaConvinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(GammaConvinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(GammaConvinstallname) $(install_dir)/$(GammaConvinstallname); \
	      echo `pwd`/$(GammaConvinstallname) >$(install_dir)/$(GammaConvinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(GammaConvinstallname), no installation directory specified"; \
	  fi; \
	fi

GammaConvclean :: GammaConvuninstall

uninstall :: GammaConvuninstall

GammaConvuninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(GammaConvinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(GammaConvinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(GammaConvinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(GammaConvinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),GammaConvclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)GammaConv.d

$(bin)$(binobj)GammaConv.d :

$(bin)$(binobj)GammaConv.o : $(cmt_final_setup_GammaConv)

$(bin)$(binobj)GammaConv.o : $(src)GammaConv.cxx
	$(cpp_echo) $(src)GammaConv.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(GammaConv_pp_cppflags) $(lib_GammaConv_pp_cppflags) $(GammaConv_pp_cppflags) $(use_cppflags) $(GammaConv_cppflags) $(lib_GammaConv_cppflags) $(GammaConv_cppflags) $(GammaConv_cxx_cppflags)  $(src)GammaConv.cxx
endif
endif

else
$(bin)GammaConv_dependencies.make : $(GammaConv_cxx_dependencies)

$(bin)GammaConv_dependencies.make : $(src)GammaConv.cxx

$(bin)$(binobj)GammaConv.o : $(GammaConv_cxx_dependencies)
	$(cpp_echo) $(src)GammaConv.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(GammaConv_pp_cppflags) $(lib_GammaConv_pp_cppflags) $(GammaConv_pp_cppflags) $(use_cppflags) $(GammaConv_cppflags) $(lib_GammaConv_cppflags) $(GammaConv_cppflags) $(GammaConv_cxx_cppflags)  $(src)GammaConv.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: GammaConvclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(GammaConv.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

GammaConvclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library GammaConv
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)GammaConv$(library_suffix).a $(library_prefix)GammaConv$(library_suffix).s? GammaConv.stamp GammaConv.shstamp
#-- end of cleanup_library ---------------
