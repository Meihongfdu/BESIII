#-- start of make_header -----------------

#====================================
#  Document config
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

cmt_config_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_config_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_config

GammaConv_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_config = /tmp/CMT_$(GammaConv_tag)_config.make$(cmt_lock_pid)
else
cmt_local_tagfile_config = $(GammaConv_tag)_config.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

GammaConv_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_config = /tmp/CMT_$(GammaConv_tag).make$(cmt_lock_pid)
else
cmt_local_tagfile_config = $(GammaConv_tag).make
endif

endif

-include $(cmt_local_tagfile_config)

ifdef cmt_config_has_target_tag

ifdef READONLY
cmt_final_setup_config = /tmp/CMT_GammaConv_configsetup.make
cmt_local_config_makefile = /tmp/CMT_config$(cmt_lock_pid).make
else
cmt_final_setup_config = $(bin)GammaConv_configsetup.make
cmt_local_config_makefile = $(bin)config.make
endif

else

ifdef READONLY
cmt_final_setup_config = /tmp/CMT_GammaConvsetup.make
cmt_local_config_makefile = /tmp/CMT_config$(cmt_lock_pid).make
else
cmt_final_setup_config = $(bin)GammaConvsetup.make
cmt_local_config_makefile = $(bin)config.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_GammaConvsetup.make
else
cmt_final_setup = $(bin)GammaConvsetup.make
endif

config ::


ifdef READONLY
config ::
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
	@echo 'config'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = config/
config::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	@echo "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------


config :: ../GammaConv/config.h
	@/bin/echo "------> config.h ok"

../GammaConv/config.h :: ../GammaConv/config.h.in
	@if test -f ../GammaConv/config.h.in; then \
	  cd ../GammaConv; \
	  $(config_command) config.h.in config.h; \
        fi


#-- start of cleanup_header --------------

clean :: configclean
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

configclean ::
#-- end of cleanup_header ---------------
