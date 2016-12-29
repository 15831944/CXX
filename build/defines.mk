MAKEFLAGS += --no-print-directory --no-builtin-rules

#ifneq ("$(origin ZQProjsPath)", "environment")
mkfilepath:=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))../
ZQProjsPath:=$(abspath $(mkfilepath))
#endif


version ?= 1.0.1.0
verbose ?= 0
debug   ?= 1
dbgfile ?= 0

ifeq ($(verbose),1)
	Q :=
else
	Q := @ 
endif

# base directories
#
_prefix  := $(ZQProjsPath)

ifeq ("$(origin ZQSdkPath)", "environment")
_sdk_dir := $(ZQSdkPath)
else
_sdk_dir := /opt/sdk
endif

_schange_sdk := $(_sdk_dir)/SeaChangeKits
_3rdparty_sdk:= $(_sdk_dir)/3rdPartyKits

_arch := $(shell uname -m)

_centos_ver := $(shell cat /etc/redhat-release |grep -o "[[:digit:]]\.[[:digit:]]"|cut -b 1)

_postfix :=
ifeq ($(_arch),x86_64)
    _postfix := 64
endif

_tsdir := $(_prefix)/TianShan
_csdir := $(_tsdir)/ContentStore

_sys_libdir := /usr/lib$(_postfix)/

_bindir := $(_tsdir)/bin$(_postfix)
_libdir := $(_tsdir)/lib$(_postfix)

_sym_dir := $(_prefix)/symbols

# third party SDK
_java_dir      := $(_3rdparty_sdk)/java
_java_hdr_dir  := $(_java_dir)/include $(_java_dir)/include/linux

_ice_dir       := $(_3rdparty_sdk)/ice
_ice_lib_dir   := $(_ice_dir)/lib
_ice_slice_dir := $(_ice_dir)/slice

_jsoncpp_dir  := $(_3rdparty_sdk)/jsoncpp
_curl_dir      := $(_3rdparty_sdk)/curl
_net-snmp_dir  := /usr
_snmp++_dir    := $(_3rdparty_sdk)/snmp++
_expat_dir     := $(_3rdparty_sdk)/expat
_libnl_dir     := $(_3rdparty_sdk)/libnl
_pcap_dir      := $(_3rdparty_sdk)/libpcap
_libaio_dir    := $(_3rdparty_sdk)/libaio
_boost_dir  := /usr
_e2fsprogs_dir := $(_3rdparty_sdk)/e2fsprogs
_readline_dir  := $(_3rdparty_sdk)/readline
_openssl_dir  := /usr
_krb5_dir      := $(_3rdparty_sdk)/krb5
_termcap_dir   := $(_3rdparty_sdk)/libtermcap
_ncurses_dir   := $(_3rdparty_sdk)/ncurses
_odbc_dir      := $(_3rdparty_sdk)/odbc

_vstrm_dir     := $(_schange_sdk)/vstrmkit
_ctf_dir       := $(_schange_sdk)/ctflib

_ctf_inc_dir   := $(_ctf_dir)/Include
_vstrm_inc_dir := $(_vstrm_dir)/Sdk/inc

ifeq ($(_arch),x86_64)
_ctf_lib_dir   := $(_ctf_dir)/LINUX64_REL
else
_ctf_lib_dir   := $(_ctf_dir)/LINUX32_REL
endif

ifeq ($(_arch),x86_64)
_sys_interp := /lib64/ld-linux-x86-64.so.2
else
_sys_interp := /lib/ld-linux.so.2
endif

_sym_ext := dbg

INCDIR += . \
		  $(_prefix)/Common $(_prefix)/build $(_tsdir)/common \
          $(_tsdir)/Ice $(_tsdir)/Shell/ZQSNMPManPkg $(_csdir) \
          $(_ice_dir)/include   $(_net-snmp_dir)/include $(_snmp++_dir)/include \
		  $(_expat_dir)/include $(_pcap_dir)/include $(_libaio_dir)/include \
		  $(_libnl_dir)/include $(_boost_dir)/include $(_e2fsprogs_dir)/include \
		  $(_java_hdr_dir) $(_readline_dir)/include \
	  	  $(_openssl_dir)/include $(_krb5_dir)/include $(_termcap_dir)/include $(_ncurses_dir)/include $(_odbc_dir)/include

LINKDIR += $(_bindir) $(_libdir) \
		   $(_ice_dir)/lib $(_net-snmp_dir)/lib64 $(_net-snmp_dir)/lib $(_snmp++_dir)/lib \
		   $(_expat_dir)/lib $(_pcap_dir)/lib $(_libaio_dir)/lib \
		   $(_libnl_dir)/lib $(_boost_dir)/lib64 $(_e2fsprogs_dir)/lib \
		   $(_readline_dir)/lib $(_openssl_dir)/lib64 $(_krb5_dir)/lib $(_termcap_dir)/lib $(_ncurses_dir)/lib $(_odbc_dir)/lib64
		   
commonlink:= $(addprefix -l, TianShanCommon TianShanIce ZQCommon) 
icelink   := $(addprefix -l, IceStorm Freeze Ice IceUtil db)
snmplink  := $(addprefix -l, SnmpManPkg snmp crypto ZQSnmp)


# host utlities
#
STRIP := strip -d --strip-unneeded

_exec_ice_bin := $(_sys_interp) --library-path $(_ice_lib_dir) 
SLICE2CPP    := $(_exec_ice_bin) $(_ice_dir)/bin/slice2cpp
SLICE2FREEZE := $(_exec_ice_bin) $(_ice_dir)/bin/slice2freeze
SLICEFLAGS   := $(addprefix -I, . $(_ice_slice_dir) $(_tsdir)/Ice $(_tsdir)/common)

JAVAC        := $(_java_dir)/bin/javac
JAVAH        := $(_java_dir)/bin/javah
JAR          := $(_java_dir)/bin/jar

VPATH += $(_prefix)/Common:$(_tsdir)/Ice:$(_csdir):$(_csdir)/ICE:$(_tsdir)/Shell/ZQSNMPManPkg/

# modules
#

# vim: ts=4 sw=4 
