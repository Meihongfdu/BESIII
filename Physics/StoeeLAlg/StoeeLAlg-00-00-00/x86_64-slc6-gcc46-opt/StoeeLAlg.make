#-- start of make_header -----------------

#====================================
#  Library StoeeLAlg
#
#   Generated Mon Jan 11 19:36:34 2021  by liumeihong
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_StoeeLAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_StoeeLAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_StoeeLAlg

StoeeLAlg_tag = $(tag)

#cmt_local_tagfile_StoeeLAlg = $(StoeeLAlg_tag)_StoeeLAlg.make
cmt_local_tagfile_StoeeLAlg = $(bin)$(StoeeLAlg_tag)_StoeeLAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

StoeeLAlg_tag = $(tag)

#cmt_local_tagfile_StoeeLAlg = $(StoeeLAlg_tag).make
cmt_local_tagfile_StoeeLAlg = $(bin)$(StoeeLAlg_tag).make

endif

include $(cmt_local_tagfile_StoeeLAlg)
#-include $(cmt_local_tagfile_StoeeLAlg)

ifdef cmt_StoeeLAlg_has_target_tag

cmt_final_setup_StoeeLAlg = $(bin)setup_StoeeLAlg.make
cmt_dependencies_in_StoeeLAlg = $(bin)dependencies_StoeeLAlg.in
#cmt_final_setup_StoeeLAlg = $(bin)StoeeLAlg_StoeeLAlgsetup.make
cmt_local_StoeeLAlg_makefile = $(bin)StoeeLAlg.make

else

cmt_final_setup_StoeeLAlg = $(bin)setup.make
cmt_dependencies_in_StoeeLAlg = $(bin)dependencies.in
#cmt_final_setup_StoeeLAlg = $(bin)StoeeLAlgsetup.make
cmt_local_StoeeLAlg_makefile = $(bin)StoeeLAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)StoeeLAlgsetup.make

#StoeeLAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'StoeeLAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = StoeeLAlg/
#StoeeLAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

StoeeLAlglibname   = $(bin)$(library_prefix)StoeeLAlg$(library_suffix)
StoeeLAlglib       = $(StoeeLAlglibname).a
StoeeLAlgstamp     = $(bin)StoeeLAlg.stamp
StoeeLAlgshstamp   = $(bin)StoeeLAlg.shstamp

StoeeLAlg :: dirs  StoeeLAlgLIB
	$(echo) "StoeeLAlg ok"

#-- end of libary_header ----------------

StoeeLAlgLIB :: $(StoeeLAlglib) $(StoeeLAlgshstamp)
	@/bin/echo "------> StoeeLAlg : library ok"

$(StoeeLAlglib) :: $(bin)initial.o $(bin)FillInf.o $(bin)KinematicFit.o $(bin)StoeeLAlg.o $(bin)GetParList.o $(bin)entries.o $(bin)load.o $(bin)Print.o $(bin)ReadBeamInfFromDb.o $(bin)current.o $(bin)StoeeLAlgProtonSelector.o $(bin)StoeeLAlgSigma0Selector.o $(bin)StoeeLAlgEptoPiPiEtaSelector.o $(bin)StoeeLAlgElectronSelector.o $(bin)StoeeLAlgPhotonSelector.o $(bin)StoeeLAlgKaonSelector.o $(bin)StoeeLAlgPionSelector.o $(bin)StoeeLAlgGoodChrTrkSelector.o $(bin)StoeeLAlgEtatoGGSelector.o $(bin)StoeeLAlgLambdaSelector.o $(bin)StoeeLAlgSignalSelector.o $(bin)StoeeLAlgPi0Selector.o $(bin)StoeeLAlgKsSelector.o $(bin)StoeeLAlgEtatoPiPiPi0Selector.o $(bin)StoeeLAlgDsSelector.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(StoeeLAlglib) $?
	$(lib_silent) $(ranlib) $(StoeeLAlglib)
	$(lib_silent) cat /dev/null >$(StoeeLAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(StoeeLAlglibname).$(shlibsuffix) :: $(StoeeLAlglib) $(StoeeLAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" StoeeLAlg $(StoeeLAlg_shlibflags)

$(StoeeLAlgshstamp) :: $(StoeeLAlglibname).$(shlibsuffix)
	@if test -f $(StoeeLAlglibname).$(shlibsuffix) ; then cat /dev/null >$(StoeeLAlgshstamp) ; fi

StoeeLAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)initial.o $(bin)FillInf.o $(bin)KinematicFit.o $(bin)StoeeLAlg.o $(bin)GetParList.o $(bin)entries.o $(bin)load.o $(bin)Print.o $(bin)ReadBeamInfFromDb.o $(bin)current.o $(bin)StoeeLAlgProtonSelector.o $(bin)StoeeLAlgSigma0Selector.o $(bin)StoeeLAlgEptoPiPiEtaSelector.o $(bin)StoeeLAlgElectronSelector.o $(bin)StoeeLAlgPhotonSelector.o $(bin)StoeeLAlgKaonSelector.o $(bin)StoeeLAlgPionSelector.o $(bin)StoeeLAlgGoodChrTrkSelector.o $(bin)StoeeLAlgEtatoGGSelector.o $(bin)StoeeLAlgLambdaSelector.o $(bin)StoeeLAlgSignalSelector.o $(bin)StoeeLAlgPi0Selector.o $(bin)StoeeLAlgKsSelector.o $(bin)StoeeLAlgEtatoPiPiPi0Selector.o $(bin)StoeeLAlgDsSelector.o

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
StoeeLAlginstallname = $(library_prefix)StoeeLAlg$(library_suffix).$(shlibsuffix)

StoeeLAlg :: StoeeLAlginstall

install :: StoeeLAlginstall

StoeeLAlginstall :: $(install_dir)/$(StoeeLAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(StoeeLAlginstallname) :: $(bin)$(StoeeLAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(StoeeLAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(StoeeLAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(StoeeLAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(StoeeLAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(StoeeLAlginstallname) $(install_dir)/$(StoeeLAlginstallname); \
	      echo `pwd`/$(StoeeLAlginstallname) >$(install_dir)/$(StoeeLAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(StoeeLAlginstallname), no installation directory specified"; \
	  fi; \
	fi

StoeeLAlgclean :: StoeeLAlguninstall

uninstall :: StoeeLAlguninstall

StoeeLAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(StoeeLAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(StoeeLAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(StoeeLAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(StoeeLAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)initial.d

$(bin)$(binobj)initial.d :

$(bin)$(binobj)initial.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)initial.o : $(src)initial.cxx
	$(cpp_echo) $(src)initial.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(initial_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(initial_cppflags) $(initial_cxx_cppflags)  $(src)initial.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(initial_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)initial.cxx

$(bin)$(binobj)initial.o : $(initial_cxx_dependencies)
	$(cpp_echo) $(src)initial.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(initial_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(initial_cppflags) $(initial_cxx_cppflags)  $(src)initial.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FillInf.d

$(bin)$(binobj)FillInf.d :

$(bin)$(binobj)FillInf.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)FillInf.o : $(src)FillInf.cxx
	$(cpp_echo) $(src)FillInf.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(FillInf_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(FillInf_cppflags) $(FillInf_cxx_cppflags)  $(src)FillInf.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(FillInf_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)FillInf.cxx

$(bin)$(binobj)FillInf.o : $(FillInf_cxx_dependencies)
	$(cpp_echo) $(src)FillInf.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(FillInf_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(FillInf_cppflags) $(FillInf_cxx_cppflags)  $(src)FillInf.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)KinematicFit.d

$(bin)$(binobj)KinematicFit.d :

$(bin)$(binobj)KinematicFit.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)KinematicFit.o : $(src)KinematicFit.cxx
	$(cpp_echo) $(src)KinematicFit.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(KinematicFit_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(KinematicFit_cppflags) $(KinematicFit_cxx_cppflags)  $(src)KinematicFit.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(KinematicFit_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)KinematicFit.cxx

$(bin)$(binobj)KinematicFit.o : $(KinematicFit_cxx_dependencies)
	$(cpp_echo) $(src)KinematicFit.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(KinematicFit_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(KinematicFit_cppflags) $(KinematicFit_cxx_cppflags)  $(src)KinematicFit.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlg.d

$(bin)$(binobj)StoeeLAlg.d :

$(bin)$(binobj)StoeeLAlg.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlg.o : $(src)StoeeLAlg.cxx
	$(cpp_echo) $(src)StoeeLAlg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlg_cppflags) $(StoeeLAlg_cxx_cppflags)  $(src)StoeeLAlg.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlg_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)StoeeLAlg.cxx

$(bin)$(binobj)StoeeLAlg.o : $(StoeeLAlg_cxx_dependencies)
	$(cpp_echo) $(src)StoeeLAlg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlg_cppflags) $(StoeeLAlg_cxx_cppflags)  $(src)StoeeLAlg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)GetParList.d

$(bin)$(binobj)GetParList.d :

$(bin)$(binobj)GetParList.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)GetParList.o : $(src)GetParList.cxx
	$(cpp_echo) $(src)GetParList.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(GetParList_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(GetParList_cppflags) $(GetParList_cxx_cppflags)  $(src)GetParList.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(GetParList_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)GetParList.cxx

$(bin)$(binobj)GetParList.o : $(GetParList_cxx_dependencies)
	$(cpp_echo) $(src)GetParList.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(GetParList_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(GetParList_cppflags) $(GetParList_cxx_cppflags)  $(src)GetParList.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)entries.d

$(bin)$(binobj)entries.d :

$(bin)$(binobj)entries.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)entries.o : $(src)components/entries.cxx
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(entries_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)components/entries.cxx

$(bin)$(binobj)entries.o : $(entries_cxx_dependencies)
	$(cpp_echo) $(src)components/entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(entries_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(entries_cppflags) $(entries_cxx_cppflags) -I../src/components $(src)components/entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)load.d

$(bin)$(binobj)load.d :

$(bin)$(binobj)load.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)load.o : $(src)components/load.cxx
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(load_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)components/load.cxx

$(bin)$(binobj)load.o : $(load_cxx_dependencies)
	$(cpp_echo) $(src)components/load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(load_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(load_cppflags) $(load_cxx_cppflags) -I../src/components $(src)components/load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Print.d

$(bin)$(binobj)Print.d :

$(bin)$(binobj)Print.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)Print.o : $(src)util/Print.cxx
	$(cpp_echo) $(src)util/Print.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(Print_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(Print_cppflags) $(Print_cxx_cppflags) -I../src/util $(src)util/Print.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(Print_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)util/Print.cxx

$(bin)$(binobj)Print.o : $(Print_cxx_dependencies)
	$(cpp_echo) $(src)util/Print.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(Print_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(Print_cppflags) $(Print_cxx_cppflags) -I../src/util $(src)util/Print.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ReadBeamInfFromDb.d

$(bin)$(binobj)ReadBeamInfFromDb.d :

$(bin)$(binobj)ReadBeamInfFromDb.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)ReadBeamInfFromDb.o : $(src)util/ReadBeamInfFromDb.cxx
	$(cpp_echo) $(src)util/ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags) -I../src/util $(src)util/ReadBeamInfFromDb.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(ReadBeamInfFromDb_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)util/ReadBeamInfFromDb.cxx

$(bin)$(binobj)ReadBeamInfFromDb.o : $(ReadBeamInfFromDb_cxx_dependencies)
	$(cpp_echo) $(src)util/ReadBeamInfFromDb.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(ReadBeamInfFromDb_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(ReadBeamInfFromDb_cppflags) $(ReadBeamInfFromDb_cxx_cppflags) -I../src/util $(src)util/ReadBeamInfFromDb.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)current.d

$(bin)$(binobj)current.d :

$(bin)$(binobj)current.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)current.o : $(src)util/current.cxx
	$(cpp_echo) $(src)util/current.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(current_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(current_cppflags) $(current_cxx_cppflags) -I../src/util $(src)util/current.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(current_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)util/current.cxx

$(bin)$(binobj)current.o : $(current_cxx_dependencies)
	$(cpp_echo) $(src)util/current.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(current_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(current_cppflags) $(current_cxx_cppflags) -I../src/util $(src)util/current.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgProtonSelector.d

$(bin)$(binobj)StoeeLAlgProtonSelector.d :

$(bin)$(binobj)StoeeLAlgProtonSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgProtonSelector.o : $(src)Selector/StoeeLAlgProtonSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgProtonSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgProtonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgProtonSelector_cppflags) $(StoeeLAlgProtonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgProtonSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgProtonSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgProtonSelector.cxx

$(bin)$(binobj)StoeeLAlgProtonSelector.o : $(StoeeLAlgProtonSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgProtonSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgProtonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgProtonSelector_cppflags) $(StoeeLAlgProtonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgProtonSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgSigma0Selector.d

$(bin)$(binobj)StoeeLAlgSigma0Selector.d :

$(bin)$(binobj)StoeeLAlgSigma0Selector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgSigma0Selector.o : $(src)Selector/StoeeLAlgSigma0Selector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgSigma0Selector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgSigma0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgSigma0Selector_cppflags) $(StoeeLAlgSigma0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgSigma0Selector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgSigma0Selector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgSigma0Selector.cxx

$(bin)$(binobj)StoeeLAlgSigma0Selector.o : $(StoeeLAlgSigma0Selector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgSigma0Selector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgSigma0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgSigma0Selector_cppflags) $(StoeeLAlgSigma0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgSigma0Selector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgEptoPiPiEtaSelector.d

$(bin)$(binobj)StoeeLAlgEptoPiPiEtaSelector.d :

$(bin)$(binobj)StoeeLAlgEptoPiPiEtaSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgEptoPiPiEtaSelector.o : $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgEptoPiPiEtaSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx

$(bin)$(binobj)StoeeLAlgEptoPiPiEtaSelector.o : $(StoeeLAlgEptoPiPiEtaSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_cppflags) $(StoeeLAlgEptoPiPiEtaSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEptoPiPiEtaSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgElectronSelector.d

$(bin)$(binobj)StoeeLAlgElectronSelector.d :

$(bin)$(binobj)StoeeLAlgElectronSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgElectronSelector.o : $(src)Selector/StoeeLAlgElectronSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgElectronSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgElectronSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgElectronSelector_cppflags) $(StoeeLAlgElectronSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgElectronSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgElectronSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgElectronSelector.cxx

$(bin)$(binobj)StoeeLAlgElectronSelector.o : $(StoeeLAlgElectronSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgElectronSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgElectronSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgElectronSelector_cppflags) $(StoeeLAlgElectronSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgElectronSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgPhotonSelector.d

$(bin)$(binobj)StoeeLAlgPhotonSelector.d :

$(bin)$(binobj)StoeeLAlgPhotonSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgPhotonSelector.o : $(src)Selector/StoeeLAlgPhotonSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgPhotonSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPhotonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPhotonSelector_cppflags) $(StoeeLAlgPhotonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPhotonSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgPhotonSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgPhotonSelector.cxx

$(bin)$(binobj)StoeeLAlgPhotonSelector.o : $(StoeeLAlgPhotonSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgPhotonSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPhotonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPhotonSelector_cppflags) $(StoeeLAlgPhotonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPhotonSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgKaonSelector.d

$(bin)$(binobj)StoeeLAlgKaonSelector.d :

$(bin)$(binobj)StoeeLAlgKaonSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgKaonSelector.o : $(src)Selector/StoeeLAlgKaonSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgKaonSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgKaonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgKaonSelector_cppflags) $(StoeeLAlgKaonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgKaonSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgKaonSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgKaonSelector.cxx

$(bin)$(binobj)StoeeLAlgKaonSelector.o : $(StoeeLAlgKaonSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgKaonSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgKaonSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgKaonSelector_cppflags) $(StoeeLAlgKaonSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgKaonSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgPionSelector.d

$(bin)$(binobj)StoeeLAlgPionSelector.d :

$(bin)$(binobj)StoeeLAlgPionSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgPionSelector.o : $(src)Selector/StoeeLAlgPionSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgPionSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPionSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPionSelector_cppflags) $(StoeeLAlgPionSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPionSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgPionSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgPionSelector.cxx

$(bin)$(binobj)StoeeLAlgPionSelector.o : $(StoeeLAlgPionSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgPionSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPionSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPionSelector_cppflags) $(StoeeLAlgPionSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPionSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgGoodChrTrkSelector.d

$(bin)$(binobj)StoeeLAlgGoodChrTrkSelector.d :

$(bin)$(binobj)StoeeLAlgGoodChrTrkSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgGoodChrTrkSelector.o : $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgGoodChrTrkSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgGoodChrTrkSelector_cppflags) $(StoeeLAlgGoodChrTrkSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgGoodChrTrkSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx

$(bin)$(binobj)StoeeLAlgGoodChrTrkSelector.o : $(StoeeLAlgGoodChrTrkSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgGoodChrTrkSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgGoodChrTrkSelector_cppflags) $(StoeeLAlgGoodChrTrkSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgGoodChrTrkSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgEtatoGGSelector.d

$(bin)$(binobj)StoeeLAlgEtatoGGSelector.d :

$(bin)$(binobj)StoeeLAlgEtatoGGSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgEtatoGGSelector.o : $(src)Selector/StoeeLAlgEtatoGGSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgEtatoGGSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEtatoGGSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEtatoGGSelector_cppflags) $(StoeeLAlgEtatoGGSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEtatoGGSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgEtatoGGSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgEtatoGGSelector.cxx

$(bin)$(binobj)StoeeLAlgEtatoGGSelector.o : $(StoeeLAlgEtatoGGSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgEtatoGGSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEtatoGGSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEtatoGGSelector_cppflags) $(StoeeLAlgEtatoGGSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEtatoGGSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgLambdaSelector.d

$(bin)$(binobj)StoeeLAlgLambdaSelector.d :

$(bin)$(binobj)StoeeLAlgLambdaSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgLambdaSelector.o : $(src)Selector/StoeeLAlgLambdaSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgLambdaSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgLambdaSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgLambdaSelector_cppflags) $(StoeeLAlgLambdaSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgLambdaSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgLambdaSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgLambdaSelector.cxx

$(bin)$(binobj)StoeeLAlgLambdaSelector.o : $(StoeeLAlgLambdaSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgLambdaSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgLambdaSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgLambdaSelector_cppflags) $(StoeeLAlgLambdaSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgLambdaSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgSignalSelector.d

$(bin)$(binobj)StoeeLAlgSignalSelector.d :

$(bin)$(binobj)StoeeLAlgSignalSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgSignalSelector.o : $(src)Selector/StoeeLAlgSignalSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgSignalSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgSignalSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgSignalSelector_cppflags) $(StoeeLAlgSignalSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgSignalSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgSignalSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgSignalSelector.cxx

$(bin)$(binobj)StoeeLAlgSignalSelector.o : $(StoeeLAlgSignalSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgSignalSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgSignalSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgSignalSelector_cppflags) $(StoeeLAlgSignalSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgSignalSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgPi0Selector.d

$(bin)$(binobj)StoeeLAlgPi0Selector.d :

$(bin)$(binobj)StoeeLAlgPi0Selector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgPi0Selector.o : $(src)Selector/StoeeLAlgPi0Selector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgPi0Selector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPi0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPi0Selector_cppflags) $(StoeeLAlgPi0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPi0Selector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgPi0Selector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgPi0Selector.cxx

$(bin)$(binobj)StoeeLAlgPi0Selector.o : $(StoeeLAlgPi0Selector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgPi0Selector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgPi0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgPi0Selector_cppflags) $(StoeeLAlgPi0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgPi0Selector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgKsSelector.d

$(bin)$(binobj)StoeeLAlgKsSelector.d :

$(bin)$(binobj)StoeeLAlgKsSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgKsSelector.o : $(src)Selector/StoeeLAlgKsSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgKsSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgKsSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgKsSelector_cppflags) $(StoeeLAlgKsSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgKsSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgKsSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgKsSelector.cxx

$(bin)$(binobj)StoeeLAlgKsSelector.o : $(StoeeLAlgKsSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgKsSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgKsSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgKsSelector_cppflags) $(StoeeLAlgKsSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgKsSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgEtatoPiPiPi0Selector.d

$(bin)$(binobj)StoeeLAlgEtatoPiPiPi0Selector.d :

$(bin)$(binobj)StoeeLAlgEtatoPiPiPi0Selector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgEtatoPiPiPi0Selector.o : $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgEtatoPiPiPi0Selector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx

$(bin)$(binobj)StoeeLAlgEtatoPiPiPi0Selector.o : $(StoeeLAlgEtatoPiPiPi0Selector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_cppflags) $(StoeeLAlgEtatoPiPiPi0Selector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgEtatoPiPiPi0Selector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),StoeeLAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)StoeeLAlgDsSelector.d

$(bin)$(binobj)StoeeLAlgDsSelector.d :

$(bin)$(binobj)StoeeLAlgDsSelector.o : $(cmt_final_setup_StoeeLAlg)

$(bin)$(binobj)StoeeLAlgDsSelector.o : $(src)Selector/StoeeLAlgDsSelector.cxx
	$(cpp_echo) $(src)Selector/StoeeLAlgDsSelector.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgDsSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgDsSelector_cppflags) $(StoeeLAlgDsSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgDsSelector.cxx
endif
endif

else
$(bin)StoeeLAlg_dependencies.make : $(StoeeLAlgDsSelector_cxx_dependencies)

$(bin)StoeeLAlg_dependencies.make : $(src)Selector/StoeeLAlgDsSelector.cxx

$(bin)$(binobj)StoeeLAlgDsSelector.o : $(StoeeLAlgDsSelector_cxx_dependencies)
	$(cpp_echo) $(src)Selector/StoeeLAlgDsSelector.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(StoeeLAlg_pp_cppflags) $(lib_StoeeLAlg_pp_cppflags) $(StoeeLAlgDsSelector_pp_cppflags) $(use_cppflags) $(StoeeLAlg_cppflags) $(lib_StoeeLAlg_cppflags) $(StoeeLAlgDsSelector_cppflags) $(StoeeLAlgDsSelector_cxx_cppflags) -I../src/Selector $(src)Selector/StoeeLAlgDsSelector.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: StoeeLAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(StoeeLAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

StoeeLAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library StoeeLAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)StoeeLAlg$(library_suffix).a $(library_prefix)StoeeLAlg$(library_suffix).s? StoeeLAlg.stamp StoeeLAlg.shstamp
#-- end of cleanup_library ---------------
