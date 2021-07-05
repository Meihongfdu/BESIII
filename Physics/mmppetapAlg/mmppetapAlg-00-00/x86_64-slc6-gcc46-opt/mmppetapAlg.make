#-- start of make_header -----------------

#====================================
#  Library mmppetapAlg
#
#   Generated Mon Mar  1 21:22:12 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_mmppetapAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_mmppetapAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_mmppetapAlg

mmppetapAlg_tag = $(tag)

#cmt_local_tagfile_mmppetapAlg = $(mmppetapAlg_tag)_mmppetapAlg.make
cmt_local_tagfile_mmppetapAlg = $(bin)$(mmppetapAlg_tag)_mmppetapAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

mmppetapAlg_tag = $(tag)

#cmt_local_tagfile_mmppetapAlg = $(mmppetapAlg_tag).make
cmt_local_tagfile_mmppetapAlg = $(bin)$(mmppetapAlg_tag).make

endif

include $(cmt_local_tagfile_mmppetapAlg)
#-include $(cmt_local_tagfile_mmppetapAlg)

ifdef cmt_mmppetapAlg_has_target_tag

cmt_final_setup_mmppetapAlg = $(bin)setup_mmppetapAlg.make
cmt_dependencies_in_mmppetapAlg = $(bin)dependencies_mmppetapAlg.in
#cmt_final_setup_mmppetapAlg = $(bin)mmppetapAlg_mmppetapAlgsetup.make
cmt_local_mmppetapAlg_makefile = $(bin)mmppetapAlg.make

else

cmt_final_setup_mmppetapAlg = $(bin)setup.make
cmt_dependencies_in_mmppetapAlg = $(bin)dependencies.in
#cmt_final_setup_mmppetapAlg = $(bin)mmppetapAlgsetup.make
cmt_local_mmppetapAlg_makefile = $(bin)mmppetapAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)mmppetapAlgsetup.make

#mmppetapAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'mmppetapAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = mmppetapAlg/
#mmppetapAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

mmppetapAlglibname   = $(bin)$(library_prefix)mmppetapAlg$(library_suffix)
mmppetapAlglib       = $(mmppetapAlglibname).a
mmppetapAlgstamp     = $(bin)mmppetapAlg.stamp
mmppetapAlgshstamp   = $(bin)mmppetapAlg.shstamp

mmppetapAlg :: dirs  mmppetapAlgLIB
	$(echo) "mmppetapAlg ok"

#-- end of libary_header ----------------

mmppetapAlgLIB :: $(mmppetapAlglib) $(mmppetapAlgshstamp)
	@/bin/echo "------> mmppetapAlg : library ok"

$(mmppetapAlglib) :: $(bin)mmppetapAlg.o $(bin)entries.o $(bin)load.o $(bin)MyIsGoodtrack.o $(bin)MyTrk.o $(bin)MyUtil.o $(bin)MyIsPID.o $(bin)MyInitIP.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(mmppetapAlglib) $?
	$(lib_silent) $(ranlib) $(mmppetapAlglib)
	$(lib_silent) cat /dev/null >$(mmppetapAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(mmppetapAlglibname).$(shlibsuffix) :: $(mmppetapAlglib) $(mmppetapAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" mmppetapAlg $(mmppetapAlg_shlibflags)

$(mmppetapAlgshstamp) :: $(mmppetapAlglibname).$(shlibsuffix)
	@if test -f $(mmppetapAlglibname).$(shlibsuffix) ; then cat /dev/null >$(mmppetapAlgshstamp) ; fi

mmppetapAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)mmppetapAlg.o $(bin)entries.o $(bin)load.o $(bin)MyIsGoodtrack.o $(bin)MyTrk.o $(bin)MyUtil.o $(bin)MyIsPID.o $(bin)MyInitIP.o

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
mmppetapAlginstallname = $(library_prefix)mmppetapAlg$(library_suffix).$(shlibsuffix)

mmppetapAlg :: mmppetapAlginstall

install :: mmppetapAlginstall

mmppetapAlginstall :: $(install_dir)/$(mmppetapAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(mmppetapAlginstallname) :: $(bin)$(mmppetapAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(mmppetapAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(mmppetapAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(mmppetapAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(mmppetapAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(mmppetapAlginstallname) $(install_dir)/$(mmppetapAlginstallname); \
	      echo `pwd`/$(mmppetapAlginstallname) >$(install_dir)/$(mmppetapAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(mmppetapAlginstallname), no installation directory specified"; \
	  fi; \
	fi

mmppetapAlgclean :: mmppetapAlguninstall

uninstall :: mmppetapAlguninstall

mmppetapAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(mmppetapAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(mmppetapAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(mmppetapAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(mmppetapAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)mmppetapAlg.d

$(bin)$(binobj)mmppetapAlg.d :

$(bin)$(binobj)mmppetapAlg.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)mmppetapAlg.o : $(src)mmppetapAlg.cxx
	$(cpp_echo) $(src)mmppetapAlg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(mmppetapAlg_cppflags) $(mmppetapAlg_cxx_cppflags)  $(src)mmppetapAlg.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(mmppetapAlg_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)mmppetapAlg.cxx

$(bin)$(binobj)mmppetapAlg.o : $(mmppetapAlg_cxx_dependencies)
	$(cpp_echo) $(src)mmppetapAlg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(mmppetapAlg_cppflags) $(mmppetapAlg_cxx_cppflags)  $(src)mmppetapAlg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)entries.d

$(bin)$(binobj)entries.d :

$(bin)$(binobj)entries.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)entries.o : $(src)components/entries.cxx
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(entries_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)components/entries.cxx

$(bin)$(binobj)entries.o : $(entries_cxx_dependencies)
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)load.d

$(bin)$(binobj)load.d :

$(bin)$(binobj)load.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)load.o : $(src)components/load.cxx
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(load_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)components/load.cxx

$(bin)$(binobj)load.o : $(load_cxx_dependencies)
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsGoodtrack.d

$(bin)$(binobj)MyIsGoodtrack.d :

$(bin)$(binobj)MyIsGoodtrack.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)MyIsGoodtrack.o : $(src)util/MyIsGoodtrack.cxx
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(MyIsGoodtrack_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)util/MyIsGoodtrack.cxx

$(bin)$(binobj)MyIsGoodtrack.o : $(MyIsGoodtrack_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyTrk.d

$(bin)$(binobj)MyTrk.d :

$(bin)$(binobj)MyTrk.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)MyTrk.o : $(src)util/MyTrk.cxx
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(MyTrk_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)util/MyTrk.cxx

$(bin)$(binobj)MyTrk.o : $(MyTrk_cxx_dependencies)
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyUtil.d

$(bin)$(binobj)MyUtil.d :

$(bin)$(binobj)MyUtil.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)MyUtil.o : $(src)util/MyUtil.cxx
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(MyUtil_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)util/MyUtil.cxx

$(bin)$(binobj)MyUtil.o : $(MyUtil_cxx_dependencies)
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsPID.d

$(bin)$(binobj)MyIsPID.d :

$(bin)$(binobj)MyIsPID.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)MyIsPID.o : $(src)util/MyIsPID.cxx
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(MyIsPID_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)util/MyIsPID.cxx

$(bin)$(binobj)MyIsPID.o : $(MyIsPID_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),mmppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyInitIP.d

$(bin)$(binobj)MyInitIP.d :

$(bin)$(binobj)MyInitIP.o : $(cmt_final_setup_mmppetapAlg)

$(bin)$(binobj)MyInitIP.o : $(src)util/MyInitIP.cxx
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx
endif
endif

else
$(bin)mmppetapAlg_dependencies.make : $(MyInitIP_cxx_dependencies)

$(bin)mmppetapAlg_dependencies.make : $(src)util/MyInitIP.cxx

$(bin)$(binobj)MyInitIP.o : $(MyInitIP_cxx_dependencies)
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(mmppetapAlg_pp_cppflags) $(lib_mmppetapAlg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(mmppetapAlg_cppflags) $(lib_mmppetapAlg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: mmppetapAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(mmppetapAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

mmppetapAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library mmppetapAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)mmppetapAlg$(library_suffix).a $(library_prefix)mmppetapAlg$(library_suffix).s? mmppetapAlg.stamp mmppetapAlg.shstamp
#-- end of cleanup_library ---------------
