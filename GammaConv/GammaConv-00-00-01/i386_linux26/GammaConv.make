#-- start of make_header -----------------

#====================================
#  Library GammaConv
#
#   Generated Thu Jan 31 00:13:52 2013  by chuxk
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

ifdef READONLY
cmt_local_tagfile_GammaConv = /tmp/CMT_$(GammaConv_tag)_GammaConv.make$(cmt_lock_pid)
else
cmt_local_tagfile_GammaConv = $(GammaConv_tag)_GammaConv.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

GammaConv_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_GammaConv = /tmp/CMT_$(GammaConv_tag).make$(cmt_lock_pid)
else
cmt_local_tagfile_GammaConv = $(GammaConv_tag).make
endif

endif

-include $(cmt_local_tagfile_GammaConv)

ifdef cmt_GammaConv_has_target_tag

ifdef READONLY
cmt_final_setup_GammaConv = /tmp/CMT_GammaConv_GammaConvsetup.make
cmt_local_GammaConv_makefile = /tmp/CMT_GammaConv$(cmt_lock_pid).make
else
cmt_final_setup_GammaConv = $(bin)GammaConv_GammaConvsetup.make
cmt_local_GammaConv_makefile = $(bin)GammaConv.make
endif

else

ifdef READONLY
cmt_final_setup_GammaConv = /tmp/CMT_GammaConvsetup.make
cmt_local_GammaConv_makefile = /tmp/CMT_GammaConv$(cmt_lock_pid).make
else
cmt_final_setup_GammaConv = $(bin)GammaConvsetup.make
cmt_local_GammaConv_makefile = $(bin)GammaConv.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_GammaConvsetup.make
else
cmt_final_setup = $(bin)GammaConvsetup.make
endif

GammaConv ::


ifdef READONLY
GammaConv ::
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
	@echo 'GammaConv'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = GammaConv/
GammaConv::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	@echo "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

GammaConvlibname   = $(bin)$(library_prefix)GammaConv$(library_suffix)
GammaConvlib       = $(GammaConvlibname).a
GammaConvstamp     = $(bin)GammaConv.stamp
GammaConvshstamp   = $(bin)GammaConv.shstamp

GammaConv :: dirs  GammaConvLIB
	@/bin/echo "------> GammaConv ok"

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




#-- start of dependency ------------------

$(bin)GammaConv_dependencies.make :: dirs

ifndef QUICK
$(bin)GammaConv_dependencies.make :: $(src)*.cxx  requirements $(use_requirements) $(cmt_final_setup_GammaConv)
	@echo "------> (GammaConv.make) Rebuilding $@"; \
	  args=`echo $? | sed -e "s#requirements.*##"`; \
	  $(build_dependencies) GammaConv -all_sources $${args}
endif

#$(GammaConv_dependencies)

-include $(bin)GammaConv_dependencies.make

#-- end of dependency -------------------
#-- start of cpp_library -----------------
#
$(bin)$(binobj)GammaConv.o : $(GammaConv_cxx_dependencies)
	$(cpp_echo) $@
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)GammaConv.o $(use_pp_cppflags) $(GammaConv_pp_cppflags) $(lib_GammaConv_pp_cppflags) $(GammaConv_pp_cppflags) $(use_cppflags) $(GammaConv_cppflags) $(lib_GammaConv_cppflags) $(GammaConv_cppflags) $(GammaConv_cxx_cppflags)  $(src)GammaConv.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: GammaConvclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	@echo "WARNING >> You should provide a target for $@"
else
.DEFAULT::
	@echo "PEDANTIC MODE >> You should provide a target for $@"
	@if test `expr index $@ '.'` != 0 ; \
	then  echo "PEDANTIC MODE >> This target seems to be a missing file, please check"; exit -1 ;\
	else echo "PEDANTIC MODE >> Just ignore it ; as it seems to be just a fake target due to some pattern" ; exit 0; fi; 		
endif

GammaConvclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)GammaConv$(library_suffix).a $(binobj)$(library_prefix)GammaConv$(library_suffix).s? $(binobj)GammaConv.stamp $(binobj)GammaConv.shstamp
#-- end of cleanup_library ---------------

