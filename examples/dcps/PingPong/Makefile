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


all: sac_pingpong_types sac_pingpong_ping sac_pingpong_pong sacpp_pingpong_types sacpp_pingpong_ping sacpp_pingpong_pong

clean depend generated realclean check-syntax $(CUSTOM_TARGETS):
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_types $(@)
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_ping $(@)
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_pong $(@)
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_types $(@)
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_ping $(@)
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_pong $(@)

.PHONY: sac_pingpong_types
sac_pingpong_types:
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_types all

.PHONY: sac_pingpong_ping
sac_pingpong_ping: sac_pingpong_types
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_ping all

.PHONY: sac_pingpong_pong
sac_pingpong_pong: sac_pingpong_types
	@cd c/standalone && $(MAKE) -f Makefile.sac_pingpong_pong all

.PHONY: sacpp_pingpong_types
sacpp_pingpong_types:
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_types all

.PHONY: sacpp_pingpong_ping
sacpp_pingpong_ping: sacpp_pingpong_types
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_ping all

.PHONY: sacpp_pingpong_pong
sacpp_pingpong_pong: sacpp_pingpong_types
	@cd cpp/standalone && $(MAKE) -f Makefile.sacpp_pingpong_pong all

project_name_list:
	@echo sac_pingpong_ping
	@echo sac_pingpong_pong
	@echo sac_pingpong_types
	@echo sacpp_pingpong_ping
	@echo sacpp_pingpong_pong
	@echo sacpp_pingpong_types
