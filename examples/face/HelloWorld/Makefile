# -*-Makefile-*-
#----------------------------------------------------------------------------
#       Make Workspace
#
# $Id$
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/tariq/tariq/opensplice/bin/mwc.pl -features ospl_os_host_linux=1 -features ospl_os_linux=1 -features ospl_64_bit=1 -value_template lib_modifier= -include /bin/MakeProjectCreator/config -include /bin/MakeProjectCreator/config/TAO -features x86_64_linux=1 -features ospl_arch_x86_64=1 -type make -features no_c99=0 -features isocpp2_cxx11=1 HDE/x86_64.linux/examples/examples_simple.mwc
#
#----------------------------------------------------------------------------


all: Face_HelloWorld_Types Face_HelloWorld_Publisher Face_HelloWorld_Subscriber

clean depend generated realclean check-syntax $(CUSTOM_TARGETS):
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Types $(@)
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Publisher $(@)
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Subscriber $(@)

.PHONY: Face_HelloWorld_Types
Face_HelloWorld_Types:
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Types all

.PHONY: Face_HelloWorld_Publisher
Face_HelloWorld_Publisher: Face_HelloWorld_Types
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Publisher all

.PHONY: Face_HelloWorld_Subscriber
Face_HelloWorld_Subscriber: Face_HelloWorld_Types
	@cd cpp && $(MAKE) -f Makefile.Face_HelloWorld_Subscriber all

project_name_list:
	@echo Face_HelloWorld_Publisher
	@echo Face_HelloWorld_Subscriber
	@echo Face_HelloWorld_Types
