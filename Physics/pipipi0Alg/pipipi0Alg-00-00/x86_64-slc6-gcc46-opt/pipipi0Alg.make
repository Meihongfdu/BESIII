#-- start of make_header -----------------

#====================================
#  Library pipipi0Alg
#
#   Generated Mon Mar  1 21:21:49 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_pipipi0Alg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_pipipi0Alg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_pipipi0Alg

pipipi0Alg_tag = $(tag)

#cmt_local_tagfile_pipipi0Alg = $(pipipi0Alg_tag)_pipipi0Alg.make
cmt_local_tagfile_pipipi0Alg = $(bin)$(pipipi0Alg_tag)_pipipi0Alg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

pipipi0Alg_tag = $(tag)

#cmt_local_tagfile_pipipi0Alg = $(pipipi0Alg_tag).make
cmt_local_tagfile_pipipi0Alg = $(bin)$(pipipi0Alg_tag).make

endif

include $(cmt_local_tagfile_pipipi0Alg)
#-include $(cmt_local_tagfile_pipipi0Alg)

ifdef cmt_pipipi0Alg_has_target_tag

cmt_final_setup_pipipi0Alg = $(bin)setup_pipipi0Alg.make
cmt_dependencies_in_pipipi0Alg = $(bin)dependencies_pipipi0Alg.in
#cmt_final_setup_pipipi0Alg = $(bin)pipipi0Alg_pipipi0Algsetup.make
cmt_local_pipipi0Alg_makefile = $(bin)pipipi0Alg.make

else

cmt_final_setup_pipipi0Alg = $(bin)setup.make
cmt_dependencies_in_pipipi0Alg = $(bin)dependencies.in
#cmt_final_setup_pipipi0Alg = $(bin)pipipi0Algsetup.make
cmt_local_pipipi0Alg_makefile = $(bin)pipipi0Alg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)pipipi0Algsetup.make

#pipipi0Alg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'pipipi0Alg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = pipipi0Alg/
#pipipi0Alg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

pipipi0Alglibname   = $(bin)$(library_prefix)pipipi0Alg$(library_suffix)
pipipi0Alglib       = $(pipipi0Alglibname).a
pipipi0Algstamp     = $(bin)pipipi0Alg.stamp
pipipi0Algshstamp   = $(bin)pipipi0Alg.shstamp

pipipi0Alg :: dirs  pipipi0AlgLIB
	$(echo) "pipipi0Alg ok"

#-- end of libary_header ----------------

pipipi0AlgLIB :: $(pipipi0Alglib) $(pipipi0Algshstamp)
	@/bin/echo "------> pipipi0Alg : library ok"

$(pipipi0Alglib) :: $(bin)pipipi0Alg.o $(bin)entries.o $(bin)load.o $(bin)MyIsGoodtrack.o $(bin)MyTrk.o $(bin)MyUtil.o $(bin)MyIsPID.o $(bin)MyInitIP.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(pipipi0Alglib) $?
	$(lib_silent) $(ranlib) $(pipipi0Alglib)
	$(lib_silent) cat /dev/null >$(pipipi0Algstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(pipipi0Alglibname).$(shlibsuffix) :: $(pipipi0Alglib) $(pipipi0Algstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" pipipi0Alg $(pipipi0Alg_shlibflags)

$(pipipi0Algshstamp) :: $(pipipi0Alglibname).$(shlibsuffix)
	@if test -f $(pipipi0Alglibname).$(shlibsuffix) ; then cat /dev/null >$(pipipi0Algshstamp) ; fi

pipipi0Algclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)pipipi0Alg.o $(bin)entries.o $(bin)load.o $(bin)MyIsGoodtrack.o $(bin)MyTrk.o $(bin)MyUtil.o $(bin)MyIsPID.o $(bin)MyInitIP.o

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
pipipi0Alginstallname = $(library_prefix)pipipi0Alg$(library_suffix).$(shlibsuffix)

pipipi0Alg :: pipipi0Alginstall

install :: pipipi0Alginstall

pipipi0Alginstall :: $(install_dir)/$(pipipi0Alginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(pipipi0Alginstallname) :: $(bin)$(pipipi0Alginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(pipipi0Alginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(pipipi0Alginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(pipipi0Alginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(pipipi0Alginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(pipipi0Alginstallname) $(install_dir)/$(pipipi0Alginstallname); \
	      echo `pwd`/$(pipipi0Alginstallname) >$(install_dir)/$(pipipi0Alginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(pipipi0Alginstallname), no installation directory specified"; \
	  fi; \
	fi

pipipi0Algclean :: pipipi0Alguninstall

uninstall :: pipipi0Alguninstall

pipipi0Alguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(pipipi0Alginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(pipipi0Alginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(pipipi0Alginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(pipipi0Alginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)pipipi0Alg.d

$(bin)$(binobj)pipipi0Alg.d :

$(bin)$(binobj)pipipi0Alg.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)pipipi0Alg.o : $(src)pipipi0Alg.cxx
	$(cpp_echo) $(src)pipipi0Alg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(pipipi0Alg_cppflags) $(pipipi0Alg_cxx_cppflags)  $(src)pipipi0Alg.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(pipipi0Alg_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)pipipi0Alg.cxx

$(bin)$(binobj)pipipi0Alg.o : $(pipipi0Alg_cxx_dependencies)
	$(cpp_echo) $(src)pipipi0Alg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(pipipi0Alg_cppflags) $(pipipi0Alg_cxx_cppflags)  $(src)pipipi0Alg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)entries.d

$(bin)$(binobj)entries.d :

$(bin)$(binobj)entries.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)entries.o : $(src)components/entries.cxx
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(entries_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)components/entries.cxx

$(bin)$(binobj)entries.o : $(entries_cxx_dependencies)
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)load.d

$(bin)$(binobj)load.d :

$(bin)$(binobj)load.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)load.o : $(src)components/load.cxx
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(load_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)components/load.cxx

$(bin)$(binobj)load.o : $(load_cxx_dependencies)
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsGoodtrack.d

$(bin)$(binobj)MyIsGoodtrack.d :

$(bin)$(binobj)MyIsGoodtrack.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)MyIsGoodtrack.o : $(src)util/MyIsGoodtrack.cxx
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(MyIsGoodtrack_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)util/MyIsGoodtrack.cxx

$(bin)$(binobj)MyIsGoodtrack.o : $(MyIsGoodtrack_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyTrk.d

$(bin)$(binobj)MyTrk.d :

$(bin)$(binobj)MyTrk.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)MyTrk.o : $(src)util/MyTrk.cxx
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(MyTrk_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)util/MyTrk.cxx

$(bin)$(binobj)MyTrk.o : $(MyTrk_cxx_dependencies)
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyUtil.d

$(bin)$(binobj)MyUtil.d :

$(bin)$(binobj)MyUtil.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)MyUtil.o : $(src)util/MyUtil.cxx
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(MyUtil_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)util/MyUtil.cxx

$(bin)$(binobj)MyUtil.o : $(MyUtil_cxx_dependencies)
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsPID.d

$(bin)$(binobj)MyIsPID.d :

$(bin)$(binobj)MyIsPID.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)MyIsPID.o : $(src)util/MyIsPID.cxx
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(MyIsPID_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)util/MyIsPID.cxx

$(bin)$(binobj)MyIsPID.o : $(MyIsPID_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),pipipi0Algclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyInitIP.d

$(bin)$(binobj)MyInitIP.d :

$(bin)$(binobj)MyInitIP.o : $(cmt_final_setup_pipipi0Alg)

$(bin)$(binobj)MyInitIP.o : $(src)util/MyInitIP.cxx
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx
endif
endif

else
$(bin)pipipi0Alg_dependencies.make : $(MyInitIP_cxx_dependencies)

$(bin)pipipi0Alg_dependencies.make : $(src)util/MyInitIP.cxx

$(bin)$(binobj)MyInitIP.o : $(MyInitIP_cxx_dependencies)
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(pipipi0Alg_pp_cppflags) $(lib_pipipi0Alg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(pipipi0Alg_cppflags) $(lib_pipipi0Alg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: pipipi0Algclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(pipipi0Alg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

pipipi0Algclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library pipipi0Alg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)pipipi0Alg$(library_suffix).a $(library_prefix)pipipi0Alg$(library_suffix).s? pipipi0Alg.stamp pipipi0Alg.shstamp
#-- end of cleanup_library ---------------
