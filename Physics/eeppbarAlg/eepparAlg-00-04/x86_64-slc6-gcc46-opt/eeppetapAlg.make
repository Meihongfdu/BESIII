#-- start of make_header -----------------

#====================================
#  Library eeppetapAlg
#
#   Generated Tue Sep 22 19:51:46 2020  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_eeppetapAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_eeppetapAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_eeppetapAlg

eeppetapAlg_tag = $(tag)

#cmt_local_tagfile_eeppetapAlg = $(eeppetapAlg_tag)_eeppetapAlg.make
cmt_local_tagfile_eeppetapAlg = $(bin)$(eeppetapAlg_tag)_eeppetapAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

eeppetapAlg_tag = $(tag)

#cmt_local_tagfile_eeppetapAlg = $(eeppetapAlg_tag).make
cmt_local_tagfile_eeppetapAlg = $(bin)$(eeppetapAlg_tag).make

endif

include $(cmt_local_tagfile_eeppetapAlg)
#-include $(cmt_local_tagfile_eeppetapAlg)

ifdef cmt_eeppetapAlg_has_target_tag

cmt_final_setup_eeppetapAlg = $(bin)setup_eeppetapAlg.make
cmt_dependencies_in_eeppetapAlg = $(bin)dependencies_eeppetapAlg.in
#cmt_final_setup_eeppetapAlg = $(bin)eeppetapAlg_eeppetapAlgsetup.make
cmt_local_eeppetapAlg_makefile = $(bin)eeppetapAlg.make

else

cmt_final_setup_eeppetapAlg = $(bin)setup.make
cmt_dependencies_in_eeppetapAlg = $(bin)dependencies.in
#cmt_final_setup_eeppetapAlg = $(bin)eeppetapAlgsetup.make
cmt_local_eeppetapAlg_makefile = $(bin)eeppetapAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)eeppetapAlgsetup.make

#eeppetapAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'eeppetapAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = eeppetapAlg/
#eeppetapAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

eeppetapAlglibname   = $(bin)$(library_prefix)eeppetapAlg$(library_suffix)
eeppetapAlglib       = $(eeppetapAlglibname).a
eeppetapAlgstamp     = $(bin)eeppetapAlg.stamp
eeppetapAlgshstamp   = $(bin)eeppetapAlg.shstamp

eeppetapAlg :: dirs  eeppetapAlgLIB
	$(echo) "eeppetapAlg ok"

#-- end of libary_header ----------------

eeppetapAlgLIB :: $(eeppetapAlglib) $(eeppetapAlgshstamp)
	@/bin/echo "------> eeppetapAlg : library ok"

$(eeppetapAlglib) :: $(bin)eeppetapAlg.o $(bin)entries.o $(bin)load.o $(bin)MyTrk.o $(bin)MyInitIP.o $(bin)MyIsPID.o $(bin)MyUtil.o $(bin)MyIsGoodtrack.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(eeppetapAlglib) $?
	$(lib_silent) $(ranlib) $(eeppetapAlglib)
	$(lib_silent) cat /dev/null >$(eeppetapAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(eeppetapAlglibname).$(shlibsuffix) :: $(eeppetapAlglib) $(eeppetapAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" eeppetapAlg $(eeppetapAlg_shlibflags)

$(eeppetapAlgshstamp) :: $(eeppetapAlglibname).$(shlibsuffix)
	@if test -f $(eeppetapAlglibname).$(shlibsuffix) ; then cat /dev/null >$(eeppetapAlgshstamp) ; fi

eeppetapAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)eeppetapAlg.o $(bin)entries.o $(bin)load.o $(bin)MyTrk.o $(bin)MyInitIP.o $(bin)MyIsPID.o $(bin)MyUtil.o $(bin)MyIsGoodtrack.o

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
eeppetapAlginstallname = $(library_prefix)eeppetapAlg$(library_suffix).$(shlibsuffix)

eeppetapAlg :: eeppetapAlginstall

install :: eeppetapAlginstall

eeppetapAlginstall :: $(install_dir)/$(eeppetapAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(eeppetapAlginstallname) :: $(bin)$(eeppetapAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(eeppetapAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(eeppetapAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(eeppetapAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(eeppetapAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(eeppetapAlginstallname) $(install_dir)/$(eeppetapAlginstallname); \
	      echo `pwd`/$(eeppetapAlginstallname) >$(install_dir)/$(eeppetapAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(eeppetapAlginstallname), no installation directory specified"; \
	  fi; \
	fi

eeppetapAlgclean :: eeppetapAlguninstall

uninstall :: eeppetapAlguninstall

eeppetapAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(eeppetapAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(eeppetapAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(eeppetapAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(eeppetapAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)eeppetapAlg.d

$(bin)$(binobj)eeppetapAlg.d :

$(bin)$(binobj)eeppetapAlg.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)eeppetapAlg.o : $(src)eeppetapAlg.cxx
	$(cpp_echo) $(src)eeppetapAlg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(eeppetapAlg_cppflags) $(eeppetapAlg_cxx_cppflags)  $(src)eeppetapAlg.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(eeppetapAlg_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)eeppetapAlg.cxx

$(bin)$(binobj)eeppetapAlg.o : $(eeppetapAlg_cxx_dependencies)
	$(cpp_echo) $(src)eeppetapAlg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(eeppetapAlg_cppflags) $(eeppetapAlg_cxx_cppflags)  $(src)eeppetapAlg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)entries.d

$(bin)$(binobj)entries.d :

$(bin)$(binobj)entries.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)entries.o : $(src)components/entries.cxx
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(entries_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)components/entries.cxx

$(bin)$(binobj)entries.o : $(entries_cxx_dependencies)
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)load.d

$(bin)$(binobj)load.d :

$(bin)$(binobj)load.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)load.o : $(src)components/load.cxx
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(load_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)components/load.cxx

$(bin)$(binobj)load.o : $(load_cxx_dependencies)
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyTrk.d

$(bin)$(binobj)MyTrk.d :

$(bin)$(binobj)MyTrk.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)MyTrk.o : $(src)util/MyTrk.cxx
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(MyTrk_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)util/MyTrk.cxx

$(bin)$(binobj)MyTrk.o : $(MyTrk_cxx_dependencies)
	$(cpp_echo) $(src)util/MyTrk.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyTrk_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyTrk_cppflags) $(MyTrk_cxx_cppflags) -I../src/util $(src)util/MyTrk.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyInitIP.d

$(bin)$(binobj)MyInitIP.d :

$(bin)$(binobj)MyInitIP.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)MyInitIP.o : $(src)util/MyInitIP.cxx
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(MyInitIP_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)util/MyInitIP.cxx

$(bin)$(binobj)MyInitIP.o : $(MyInitIP_cxx_dependencies)
	$(cpp_echo) $(src)util/MyInitIP.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyInitIP_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyInitIP_cppflags) $(MyInitIP_cxx_cppflags) -I../src/util $(src)util/MyInitIP.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsPID.d

$(bin)$(binobj)MyIsPID.d :

$(bin)$(binobj)MyIsPID.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)MyIsPID.o : $(src)util/MyIsPID.cxx
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(MyIsPID_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)util/MyIsPID.cxx

$(bin)$(binobj)MyIsPID.o : $(MyIsPID_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsPID.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyIsPID_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyIsPID_cppflags) $(MyIsPID_cxx_cppflags) -I../src/util $(src)util/MyIsPID.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyUtil.d

$(bin)$(binobj)MyUtil.d :

$(bin)$(binobj)MyUtil.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)MyUtil.o : $(src)util/MyUtil.cxx
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(MyUtil_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)util/MyUtil.cxx

$(bin)$(binobj)MyUtil.o : $(MyUtil_cxx_dependencies)
	$(cpp_echo) $(src)util/MyUtil.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyUtil_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyUtil_cppflags) $(MyUtil_cxx_cppflags) -I../src/util $(src)util/MyUtil.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),eeppetapAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MyIsGoodtrack.d

$(bin)$(binobj)MyIsGoodtrack.d :

$(bin)$(binobj)MyIsGoodtrack.o : $(cmt_final_setup_eeppetapAlg)

$(bin)$(binobj)MyIsGoodtrack.o : $(src)util/MyIsGoodtrack.cxx
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx
endif
endif

else
$(bin)eeppetapAlg_dependencies.make : $(MyIsGoodtrack_cxx_dependencies)

$(bin)eeppetapAlg_dependencies.make : $(src)util/MyIsGoodtrack.cxx

$(bin)$(binobj)MyIsGoodtrack.o : $(MyIsGoodtrack_cxx_dependencies)
	$(cpp_echo) $(src)util/MyIsGoodtrack.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(eeppetapAlg_pp_cppflags) $(lib_eeppetapAlg_pp_cppflags) $(MyIsGoodtrack_pp_cppflags) $(use_cppflags) $(eeppetapAlg_cppflags) $(lib_eeppetapAlg_cppflags) $(MyIsGoodtrack_cppflags) $(MyIsGoodtrack_cxx_cppflags) -I../src/util $(src)util/MyIsGoodtrack.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: eeppetapAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(eeppetapAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

eeppetapAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library eeppetapAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)eeppetapAlg$(library_suffix).a $(library_prefix)eeppetapAlg$(library_suffix).s? eeppetapAlg.stamp eeppetapAlg.shstamp
#-- end of cleanup_library ---------------
