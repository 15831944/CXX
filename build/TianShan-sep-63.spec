Name:      TianShan
Version:   2.3.1
Release:   2
Summary:   ZQ Stream Server 
Group:     Applications/System
License:   commercial
BuildArch: x86_64
BuildRoot: %{_tmppath}/%{name}-root

Requires: python >= 2.4
Requires: libicu >= 4.2.1
Requires: boost-regex >= 1.41.0
Requires: libaio
Requires: graphviz
Requires: net-snmp-libs

%define __os_install_post  %{nil}
%define __prelink_undo_cmd %{nil}

%define _topdir       %(echo ${HOME})
%define _rpmdir       %(echo ${OutputPath})
%define _builddir     ${ZQProjsPath}/build

%define prefix        /opt/%{name}
%define postfix       %([ $(uname -m) = "x86_64" ] && echo "64")
%define oid           .1.3.6.1.4.1.22839.4.1
%define snmp_agent    %{prefix}/bin/libSnmpAgent.so
%define snmp_server   127.0.0.1

%define sdk_dir       $([ -z "${ZQSdkPath}" ] && echo "/opt/sdk" || echo ${ZQSdkPath})
%define ctf_dir       %{sdk_dir}/SeaChangeKits/ctflib
%define ctf_inc_dir   %{ctf_dir}/Include
%define ice_dir       %{sdk_dir}/3rdPartyKits/ice
%define boost_dir     %{sdk_dir}/3rdPartyKits/boost
%define snmp_dir      %{sdk_dir}/3rdPartyKits/net-snmp
%define snmpp_dir     %{sdk_dir}/3rdPartyKits/snmp++
%define libnl_dir     %{sdk_dir}/3rdPartyKits/libnl
%define libpcap_dir   %{sdk_dir}/3rdPartyKits/libpcap
%define e2fsprogs_dir %{sdk_dir}/3rdPartyKits/e2fsprogs
%define curl_dir	%{sdk_dir}/3rdPartyKits/curl

%define src_dir       ${ZQProjsPath}/%{name}
%define src_cfg_dir   %{src_dir}/etc
%define src_bin_dir   %{src_dir}/bin%{postfix}
%define src_lib_dir   %{src_dir}/lib%{postfix}
%define src_build_dir %{_builddir}
%define src_util_dir  %{src_build_dir}/utils
%define src_ctf_dir   %{ctf_dir}/LINUX%{postfix}_REL
%define src_mod_dir   %{src_dir}/modules

%define dest_dir      %{buildroot}/%{prefix}
%define dest_cfg_dir  %{dest_dir}/etc
%define dest_bin_dir  %{dest_dir}/bin
%define dest_ctf_dir  %{dest_dir}/CTF
%define dest_util_dir %{dest_dir}/utils
%define dest_mod_dir  %{dest_dir}/modules
%define dest_svc_dir  %{buildroot}/etc/init.d

%define svc_daemons   EventChannel Sentry CDNCS CDNSS GBCS CPESvc HttpCRG RtspProxy EventGateway EventRuleEngine ContentLib Weiwoo SiteAdmin MODApp xmlshd EdgeRM NSS GBMODApp DsmccCRG GBVSS TSPump MediaClusterCS DummySvc C2SS BcastChannel
%define util_scripts  %{src_dir}/CDNLib/CRM_C2Locator/checkRH.sh
# NSS
%define svc_runlevel  345
%define svc_seq_pre   9

%define dep_ice       Ice IceUtil IceStorm IceBox IceStormService IceGrid Glacier2 Freeze
%define dep_misc      snmp snmp++ db_cxx boost_regex icu nl

%define ice_ver       3.2.2
%define ice_ver_maj   32
%define boost_ver     1.33.1
%define boost_ver_maj 2
%define snmp_ver      10.0.3
%define snmp_ver_maj  10
%define snmpp_ver     3.2.24
%define snmpp_ver_maj 3
%define db_cxx_ver    4.5
%define icu_ver       36.0
%define icu_ver_maj   36
%define nl_ver        1.1
%define nl_ver_maj    1
%define curl_ver      4.3.0
%define curl_ver_maj  4
%define pcap_ver      1.3.0
%define pcap_ver_maj  1
%define uuid_ver_maj  1
%define uuid_ver      1.2

%define ctf_ver_file  %{ctf_inc_dir}/TrickLibVersion.h
%define ctf_ver %(sudo sed -i 's/\r$//' %{ctf_ver_file}&&_t=$(grep TrickLIB_PRODUCTVERSION %{ctf_ver_file});echo ${_t##*TrickLIB_PRODUCTVERSION})
 
AutoReqProv: no

%description
ZQ Stream Server

#######################################################################
%package common
Summary: TianShan common components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description common
The TianShan-common package provides common components

%pre common
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

%post common

if [ -e /etc/TianShan.xml ]; then
	mv /etc/{TianShan.xml,TianShan.xml.bak}
fi
ln -sf %{prefix}/etc/TianShan.xml /etc/TianShan.xml

unzip -oq %{prefix}/CTF/libctf.zip -d %{prefix}/CTF

if [ ! -L %{prefix}/bin/libCTF.so ]; then
	ln -sf ../CTF/libCTF.so.%{ctf_ver} %{prefix}/bin/libCTF.so 
fi

# verify daemon scripts
for svc in %{svc_daemons}; do
	script=$(echo ${svc} | sed 's/.*/\L&\E/')
	# clean the startup script first if this is upgrade
	if [ "$1" == 2 ]; then
		/sbin/chkconfig --del ${script}
	fi
	/sbin/chkconfig --add ${script}
done

# verify snmpd service
rpm -q net-snmp >/dev/null

if [ $? -eq 0 ]; then
    snmpcfg=/etc/snmp/snmpd.conf

    # auto generate configuration 
    community=$(egrep "[[:space:]]*rwcommunity[[:space:]]+%{name}" ${snmpcfg})
    if [ -z "${community}" ]; then
        echo "rwcommunity %{name} %{snmp_server} %{oid}" >> ${snmpcfg}
    fi 
    agent=$(egrep "[[:space:]]*dlmod[[:space:]]+SNMPAgent[[:space:]]+.*libSnmpAgent.so" ${snmpcfg})
    if [ -z "${agent}" ]; then  
        echo "dlmod SNMPAgent %{snmp_agent}" >> ${snmpcfg}
    fi

    # make snmpd start with system
    dir=/etc/rc2.d
    file=$(find ${dir}/* -type l -name "[KS]??snmpd")

    # this should always be true if net-snmp installed
    if [ -n "${file}" ]; then
        f=$(basename ${file})
        if [ "${f:0:1}" = "K" ]; then
            mv ${dir}/{K,S}${f:1}
        fi
    else
        # not possible here though, just in case
        ln -s ../init.d/snmpd ${dir}/S50snmpd
    fi  
    
    stat /var/run/snmpd.pid >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        service snmpd start >/dev/null
    fi
fi

%preun common

[ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all

# delete chkconfig settings
for svc in %{svc_daemons}; do
	script=$(echo ${svc} | sed 's/.*/\L&\E/')
	/sbin/chkconfig --del ${script}
done

%postun common

# do nothing for an upgrade
[ "$1" = "1" ] && exit 0

# restore default config for core dumps
echo 'core' > /proc/sys/kernel/core_pattern

rm -f /etc/TianShan.xml
rm -f %{prefix}/bin/libCTF.so

#######################################################################
%package contentstore
Summary: TianShan contentstore components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description contentstore
The TianShan contentstore package provides execution components

Requires: TianShan-common

%pre contentstore
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package cpe
Summary: TianShan content provision components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description cpe
The TianShan cpe package provides execution components

Requires: TianShan-common

%pre cpe
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	 exit 0
fi

#######################################################################
%package rtspcrg
Summary: TianShan rtspcrg components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description rtspcrg
The TianShan rtspcrg package provides execution components

Requires: TianShan-common

%pre rtspcrg
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package ostr
Summary: TianShan ostr components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description ostr
The TianShan ostr package provides execution components

Requires: TianShan-common
Requires: TianShan-contentstore

%pre ostr
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi
#######################################################################
%package httpcrg
Summary: TianShan httpcrg components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description httpcrg
The TianShan httpcrg package provides execution components

Requires: TianShan-common

%pre httpcrg
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi 

#######################################################################
%package dsmcccrg
Summary: TianShan dsmcccrg components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description dsmcccrg
The TianShan dsmcccrg package provides execution components

Requires: TianShan-common

%pre dsmcccrg
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all        
	exit 0
fi

#######################################################################
%package scs
Summary: TianShan scs components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description scs
The TianShan scs package provides execution components

Requires: TianShan-contentstore
Requires: TianShan-httpcrg
Requires: TianShan-watch
Requires: TianShan-common

%pre scs
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package cdn
Summary: TianShan cdn components
Group: Applications/System
License:   commercial
#BuildArch: x86_64 
#BuildRoot: /var/tmp/%{productname}-buildroot
%description cdn
The TianShan cdn package provides execution components

Requires: TianShan-contentstore
Requires: TianShan-httpcrg
Requires: TianShan-watch
Requires: TianShan-common
Requires: TianShan-cpe

%pre cdn
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package watch
Summary: TianShan watch components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description watch
The TianShan watch package provides execution components

Requires: TianShan-common

%pre watch
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

rpm -q net-snmp >/dev/null
if [ $? -ne 0 ]; then
    echo "WARNING: package net-snmp is not installed, some of the components will not function."  
    while true; do
        echo -n "continue? [yes|no]: "
        exec 0</dev/tty
        read answer
        
        if [ "${answer}" != "yes" -a "${answer}" != "no" ]; then
            echo "please enter \"yes\" or \"no\""
            continue
        elif [ "${answer}" = "no" ]; then
            exit 1
        else
            break
        fi
    done
else
    service snmpd stop >/dev/null
fi


#######################################################################
%package srm
Summary: TianShan srm components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description srm
The TianShan srm package provides execution components

Requires: TianShan-common

%pre srm
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package stream
Summary: TianShan stream components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description stream
The TianShan stream package provides execution components

Requires: TianShan-common

%pre stream
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package edgerm
Summary: TianShan edgerm components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description edgerm
The TianShan edgerm package provides execution components

Requires: TianShan-common

%pre edgerm
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package app
Summary: TianShan application components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description app
The TianShan application package provides execution components

Requires: TianShan-common
Requires: TianShan-watch

%pre app
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi

#######################################################################
%package utils
Summary: TianShan utils components
Group: Applications/System
License:   commercial
#BuildArch: x86_64
#BuildRoot: /var/tmp/%{productname}-buildroot
%description utils
The TianShan utils package provides execution components

Requires: TianShan-common

%pre utils
# stop all running service before upgrade
if [ "$1" = "2" ]; then
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
	exit 0
fi
#######################################################################

%prep

# clean object files and target files in sub dirs
make veryclean

# clean temp dir for rpm package
[ -d %{buildroot} ] && rm -rvf %{buildroot}

%build

make debug=${Debug} version=%{version}.%{release}

%pre

# stop all running service before upgrade
if [ "$1" = "2" ]; then 
    [ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all
    exit 0
fi

rpm -q net-snmp >/dev/null
if [ $? -ne 0 ]; then
    echo "WARNING: package net-snmp is not installed, some of the components will not function."  
    while true; do
        echo -n "continue? [yes|no]: "
        exec 0</dev/tty
        read answer
        
        if [ "${answer}" != "yes" -a "${answer}" != "no" ]; then
            echo "please enter \"yes\" or \"no\""
            continue
        elif [ "${answer}" = "no" ]; then
            exit 1
        else
            break
        fi
    done
else
    service snmpd stop >/dev/null
fi

%install 

mkdir -pv %{buildroot}/{etc/init.d,opt/%{name}/{CTF,bin,logs/{crashdump,rtrec},etc,data/runtime,utils,modules}}
mkdir -pv %{src_mod_dir}

# utils
chmod a+x %{src_util_dir}/ver_check 
cp -vp %{src_util_dir}/ver_check %{dest_util_dir}

# service scripts

Sentry="sentry monitors the local components and represents their status\n\
#              and runtime information via web UI. It also collects the events of\n\
#              the local components and forwards them to the event channel"
EventChannel="provides m-to-n messaging, it receives the event posts from the publishers and forwards them\n\
#	       to multiple subscribers" 
EventGateway="eventgateway is designed for thirty party integration, who may take different messaging mechanism \n\
#              other than TianShan event, such as JMS, SOAP and so on. EventGateway subscribes events from \n\
#              eventchannel and then translate into different manner (via plugin framework)\n\
#              and forward to the thirty party"
RtspProxy="RtspProxy runs as a RTSP socket server accepts RTSP requests. It offers users a flexible extension \n\
#              opportunity with modules, a plugin-architecture"
CDNSS="cdnss is an implementation of StreamService on CDN header who transfers contents to the cache-enabled \n\
#              video server as HTTP push stream sessions"
CPESvc="CPESvc stands for Content Provisioning Engine, who host various types of content provisioning \n\
#              (including media processing and propagation) tasks"
HttpCRG="HttpCRG stands for HTTP Client Request Gateway, who runs as HTTP socket server, and process and \n\
#              respond HTTP response by its portable plugins"
CDNCS="CDNCS aggregates multiple cdnss instances as a clustered ContentStore, and also load balancing the \n\
#              ingestion tasks amoung the managed multiple content provisioning engine (cpe) instances"
EventRuleEngine="EventRuleEngine"
ContentLib="ContentLib"
Weiwoo="Weiwoo"
SiteAdmin="SiteAdmin"
MODApp="MODApp"
NSS="NSS"
xmlshd="xmlshd"
EdgeRM="EdgeRM"
GBMODApp="GBMODApp"
DsmccCRG="DsmccCRG"
GBCS="GBCS"
GBVSS="GBVSS"
TSPump="TSPump"
MediaClusterCS="MediaClusterCS"
DummySvc="DummySvc"
C2SS="C2SS"
BcastChannel="BcastChannel"

i=0
for svc in %{svc_daemons}; do
    script=$(echo ${svc} | sed 's/.*/\L&\E/')
    eval desc=\$${svc}
    echo -e "#!/bin/bash\n#\n# chkconfig: %{svc_runlevel} %{svc_seq_pre}${i} 04\n# description: ${desc}\n#\n\nservice=${svc}\n\n. %{prefix}/utils/tianshan\n" > %{src_util_dir}/${script}
    chmod a+x %{src_util_dir}/${script}
    cp -vp %{src_util_dir}/${script} %{dest_svc_dir}
#	i=$((i%10)); i=$((i+1))
	[ $i -lt 9 ] && i=$((i+1))
done
chmod a+x %{src_util_dir}/tianshan
cp -vp %{src_util_dir}/tianshan %{dest_util_dir}

# plugins
if [ "%{_build_arch}" = "x86_64" ]; then
    cp -vp %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libCPH*,libAction*,libMHO*,libPHO*} %{src_mod_dir} 
    #mv -v %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libCPH*,libAction*,libMHO*,libPHO*} %{dest_mod_dir}
    cp -vaf %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libCPH*,libAction*,libMHO*,libPHO*} %{dest_mod_dir}
else
    cp -vp %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libAction*,libMHO*,libPHO*} %{src_mod_dir}
    #mv -v %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libAction*,libMHO*,libPHO*} %{dest_mod_dir}
    cp -vaf %{src_bin_dir}/{libEGH*,libSSM*,libCRM*,libAction*,libMHO*,libPHO*} %{dest_mod_dir}
fi

# add two python script
cp -vP %{src_dir}/CDNLib/CDNSS/C2Streamer/*.py %{dest_bin_dir}
chmod a+x %{dest_bin_dir}/*.py

# all exec and shared libraries
cp -vrP %{src_bin_dir}/* %{dest_bin_dir}

# sdk
if [ "%{_build_arch}" = "x86_64" ]; then
	cp -vP %{src_ctf_dir}/libCTF.so %{_tmppath}/libCTF.so.%{ctf_ver}
	zip -jm %{dest_ctf_dir}/libctf.zip %{_tmppath}/libCTF.so.%{ctf_ver}
fi

# third party libraries

# ice
for ice in %{dep_ice}; do
    cp -vP %{ice_dir}/lib/{lib${ice}.so.%{ice_ver},lib${ice}.so.%{ice_ver_maj}} %{dest_bin_dir}
done

# misc
cp -vP \
%{snmp_dir}/lib/{libsnmp.so.%{snmp_ver},libsnmp.so.%{snmp_ver_maj}} \
%{snmpp_dir}/lib/{libsnmp++.so.%{snmpp_ver},libsnmp++.so.%{snmpp_ver_maj}} \
%{ice_dir}/lib/libdb_cxx-%{db_cxx_ver}.so \
%{libnl_dir}/lib/{libnl.so.%{nl_ver},libnl.so.%{nl_ver_maj}} \
%{libpcap_dir}/lib/{libpcap.so.%{pcap_ver},libpcap.so.%{pcap_ver_maj}} \
%{e2fsprogs_dir}/lib/{libuuid.so,libuuid.so.%{uuid_ver},libuuid.so.%{uuid_ver_maj}} \
%{curl_dir}/lib/{libcurl.so.%{curl_ver},libcurl.so.%{curl_ver_maj}} \
%{dest_bin_dir}

#%{_libdir}/{libicui18n.so.%{icu_ver},libicui18n.so.%{icu_ver_maj}} \
#%{_libdir}/{libicuuc.so.%{icu_ver},libicuuc.so.%{icu_ver_maj}} \
#%{_libdir}/{libicudata.so.%{icu_ver},libicudata.so.%{icu_ver_maj}} \
#%{boost_dir}/lib/{libboost_regex.so.%{boost_ver},libboost_regex.so.%{boost_ver_maj}} \

#about additional script files, copy them to TianShan/utils
for file in %{util_scripts}; do
	chmod +w ${file}
    dos2unix ${file}
    chmod a+x ${file}
    cp -vp ${file} %{dest_util_dir}
done

# resources
cp -rv %{src_dir}/webctrl  %{dest_dir}

# sample configuration files
sed -i '{ 
    s/\(.*TianShanHomeDir.*value.*=\).*\(\/>\)/\1"\/opt\/%{name}"\2/
}' %{src_cfg_dir}/TianShanDef.xml

sed -i '{
    s/\([[:space:]]*<CPH.*file.*=".*\.dll"[[:space:]]*enable=\)"1"/\1"0"/ 
    s/\([[:space:]]*<CPH.*file.*=".*lib\w\+\.so"[[:space:]]*enable.*=\)"0"/\1"1"/ 
    s/\([[:space:]]*homeDir.*=\).*/\1"\/tmp\/c2files"/ 
}' %{src_cfg_dir}/CPE.xml

sed -i '{
    s/\([[:space:]]*<Plugins.*populatePath.*=.*".*\)EGH.*\.dll"/\1libEGH_\*.so"/
}' %{src_cfg_dir}/EventGateway.xml

sed -i '{
    /path/ s/\\/\//g 
    /classpath/ s/;/:/g
}' %{src_cfg_dir}/EGH_JMS.xml

sed -i '{
    s/<module\(.*file=".*ssm_.*.dll.*\)\/>/<!--module\1\/-->/ 
    s/<!--module\(.*file=".*libSSM_.*.so".*\)\/-->/<module\1\/>/ 
    s/\(<RequestHandler.*defaultHandler="\).*\(">\)/\1tianshan_s1\2/ 
}' %{src_cfg_dir}/RtspProxy.xml

sed -i '{
	s/\([[:space:]]*<Module.*image=".*\)\(CRM_.*\)\.dll"[[:space:]].*\/>/\1lib\2.so" \/>/ 
    s/\(.*populatePath.*=.*".*\)CRM_.*\.dll"/\1libCRM_\*.so"/
}' %{src_cfg_dir}/HttpCRG.xml

sed -i '{
	s/\(^[[:space:]]*<C2Client.*cacheDir=\)".*"[[:space:]]\(.*\)/\1"\/tmp" \2/
}' %{src_cfg_dir}/CPH_C2Propagation.xml

sed -i '{
	s/\([[:space:]]*<EventSinkModule.*file.*=.*".*\)eventsender\.dll"/\1libEventSender\.so"/
}' %{src_cfg_dir}/SiteAdminSvc.xml

sed -i '{
	s/\([[:space:]]*<module.*file.*=.*".*\)crm_dsmcc\.dll"/\1libCRM_DSMCC\.so"/
}' %{src_cfg_dir}/DsmccCRG.xml

# remove windows only config
rm -f %{src_cfg_dir}/{Sentry.xml,weblayout.xml,weblayout_NGOD.xml}

for file in %{src_cfg_dir}/*.xml; do
    base=$(basename ${file})
	
    if [ "${base%_linux.xml}" = "${base}" ]; then
        # xxx.xml do not touch files below
        if [ "${base}" = "syntax.xml" ]; then
            dest=${base}
        else
            dest=${base%.xml}_sample.xml
        fi
    else
        # xxx_linux.xml
        dest=${base%_linux.xml}_sample.xml
    fi

	case "${base}" in
	"syntax.xml"|"CRM_C2Locator.xml"|"EGH_JMS.xml"|"MovieOnDemand.xml") ;;
	*) sed -i 's/\\/\//g' ${file} ;;
	esac

    cp -v ${file} %{dest_cfg_dir}/${dest}
done
cp -v %{src_dir}/TianShan.xml %{dest_cfg_dir}/TianShan_sample.xml
cp -v %{src_dir}/TianShan.MIB %{dest_cfg_dir}/


%post

unzip -oq %{prefix}/CTF/libctf.zip -d %{prefix}/CTF

if [ ! -L %{prefix}/bin/libCTF.so ]; then
	ln -sf ../CTF/libCTF.so.%{ctf_ver} %{prefix}/bin/libCTF.so 
fi

# upgrading
if [ "$1" = "2" ]; then

	# ask if a previous link exists #
#	if [ -L %{prefix}/bin/libCTF.so ]; then
#
#		echo "NOTICE: CTF link found."  

#	    while true; do
#			echo -n "replace? [yes|no]: "
#			exec 0</dev/tty
#			read answer
        
#			if [ "${answer}" != "yes" -a "${answer}" != "no" ]; then
#				echo "please enter \"yes\" or \"no\""
#				continue
#			fi
		
#			if [ "${answer}" = "yes" ]; then
#				ln -sf ../CTF/libCTF.so.%{ctf_ver} %{prefix}/bin/libCTF.so 
#			fi
#			break
#		done
#		echo
#	else
#		ln -sf ../CTF/libCTF.so.%{ctf_ver} %{prefix}/bin/libCTF.so 
#	fi	
	exit 0
fi

#ln -sf ../CTF/libCTF.so.%{ctf_ver} %{prefix}/bin/libCTF.so 

if [ -e /etc/TianShan.xml ]; then
	mv /etc/{TianShan.xml,TianShan.xml.bak}
fi
ln -sf %{prefix}/etc/TianShan.xml /etc/TianShan.xml

# verify daemon scripts
for svc in %{svc_daemons}; do
	script=$(echo ${svc} | sed 's/.*/\L&\E/')
	# clean the startup script first if this is upgrade
	if [ "$1" == 2 ]; then
		/sbin/chkconfig --del ${script}
	fi
	/sbin/chkconfig --add ${script}
done

# verify snmpd service
rpm -q net-snmp >/dev/null

if [ $? -eq 0 ]; then
    snmpcfg=/etc/snmp/snmpd.conf

    # auto generate configuration 
    community=$(egrep "[[:space:]]*rwcommunity[[:space:]]+%{name}" ${snmpcfg})
    if [ -z "${community}" ]; then
        echo "rwcommunity %{name} %{snmp_server} %{oid}" >> ${snmpcfg}
    fi 
    agent=$(egrep "[[:space:]]*dlmod[[:space:]]+SNMPAgent[[:space:]]+.*libSnmpAgent.so" ${snmpcfg})
    if [ -z "${agent}" ]; then  
        echo "dlmod SNMPAgent %{snmp_agent}" >> ${snmpcfg}
    fi

    # make snmpd start with system
    dir=/etc/rc2.d
    file=$(find ${dir}/* -type l -name "[KS]??snmpd")

    # this should always be true if net-snmp installed
    if [ -n "${file}" ]; then
        f=$(basename ${file})
        if [ "${f:0:1}" = "K" ]; then
            mv ${dir}/{K,S}${f:1}
        fi
    else
        # not possible here though, just in case
        ln -s ../init.d/snmpd ${dir}/S50snmpd
    fi  
    
    stat /var/run/snmpd.pid >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        service snmpd start >/dev/null
    fi
fi

%preun

[ -x %{prefix}/bin/SystemShell ] && %{prefix}/bin/SystemShell -s all

# delete chkconfig settings
for svc in %{svc_daemons}; do
	script=$(echo ${svc} | sed 's/.*/\L&\E/')
	/sbin/chkconfig --del ${script}
done

%postun

# do nothing for an upgrade
[ "$1" = "1" ] && exit 0

# restore default config for core dumps
echo 'core' > /proc/sys/kernel/core_pattern

rm -f /etc/TianShan.xml
rm -f %{prefix}/bin/libCTF.so

%clean

cd %{buildroot}
name=${Package%.*}
zip -rvy %{_rpmdir}/${name}.zip *
cd -

# make package for debug symbols
cd ${ZQProjsPath}/symbols
zip -rv %{_rpmdir}/${Symbols} *
cd -

rm -rf %{buildroot}

%files common
%defattr(-,root,root)
%{prefix}/bin/SystemShell*
%{prefix}/bin/libFreeze.so*
%{prefix}/bin/libGlacier2.so*
%{prefix}/bin/libIce.so*
%{prefix}/bin/libIceBox.so*
%{prefix}/bin/libIceGrid.so*
%{prefix}/bin/libIceStorm.so*
%{prefix}/bin/libIceStormService.so*
%{prefix}/bin/libIceUtil.so*
%{prefix}/bin/libJndiClient*
%{prefix}/bin/libMsgSender*
%{prefix}/bin/libSnmpAgent*
%{prefix}/bin/libSnmpManPkg*
%{prefix}/bin/libSnmpPlug*
%{prefix}/bin/libSysLogger*
%{prefix}/bin/libTSClient*
%{prefix}/bin/libTianShanIce*
%{prefix}/bin/libasync.so*
%{prefix}/bin/libcurl.so*
%{prefix}/bin/libdb_cxx-4.5.so
%{prefix}/bin/libsnmp++.so*
%{prefix}/bin/libuuid.so*
%{prefix}/bin/libnl.so*
%{prefix}/bin/libpcap.so*
%{prefix}/bin/libZQCommon*
%{prefix}/bin/java/JndiClient.jar
%{prefix}/bin/java/jbossall-client.jar
%{prefix}/CTF/libctf.zip
%{prefix}/utils/tianshan
%config %attr(0555,root,root) %{prefix}/etc/TianShan.MIB
%config %attr(0555,root,root) %{prefix}/etc/TianShan*.xml
%config %attr(0555,root,root) %{prefix}/etc/syntax.xml

%files contentstore
%defattr(-,root,root)
%{prefix}/bin/BaseCS*
%{prefix}/bin/ContentClient*
%{prefix}/bin/ContentLib*
#%{prefix}/bin/ContentLibClient*
%{prefix}/bin/libStorage_web*
/etc/init.d/contentlib

%files cpe
%defattr(-,root,root)
%{prefix}/bin/CPEClient*
%{prefix}/bin/CPESvc*
%{prefix}/modules/libCPH_PCAP*
%{prefix}/modules/libCPH_Raw*
%{prefix}/bin/RTICap*
%{prefix}/bin/TrickGen*
%{prefix}/bin/libCPCMan_web*
%{prefix}/bin/libCPEMan_web*
%{prefix}/bin/libPacing*

/etc/init.d/cpesvc
%config %attr(0555,root,root) %{prefix}/etc/CPE*.xml
%config %attr(0555,root,root) %{prefix}/etc/CPH_PCAP*.xml
%config %attr(0555,root,root) %{prefix}/etc/CPH_Raw*.xml

%files rtspcrg
%defattr(-,root,root)
%{prefix}/bin/RtspProxy*
%{prefix}/modules/libSSM_Richurl.so*
%{prefix}/modules/libSSM_TianShan_S1*
#%{prefix}/modules/libSSM_GBstb*

/etc/init.d/rtspproxy
%config %attr(0555,root,root) %{prefix}/etc/RtspProxy*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_richurl*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_tianshan_s1*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_GBstb*.xml

%files ostr
%defattr(-,root,root)
%{prefix}/modules/libSSM_NGOD2*
#%{prefix}/modules/libSSM_GBss*
%{prefix}/modules/libSSM_OpenVBO*
%{prefix}/bin/MediaClusterCS*
%{prefix}/bin/libOpenVBO_web*
%{prefix}/bin/libngod2view.so*
#%{prefix}/bin/auth5i*
/etc/init.d/mediaclustercs
%config %attr(0555,root,root) %{prefix}/etc/MediaClusterCS*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_NGOD2*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_GBss*.xml
%config %attr(0555,root,root) %{prefix}/etc/ssm_OpenVBO*.xml

%files httpcrg
%defattr(-,root,root)
%{prefix}/bin/HttpCRG*
%{prefix}/modules/libAction_A3Message*
/etc/init.d/httpcrg
%config %attr(0555,root,root) %{prefix}/etc/HttpCRG*.xml
%config %attr(0555,root,root) %{prefix}/etc/CRM_A3Message*.xml

%files dsmcccrg
%defattr(-,root,root)
%{prefix}/bin/DsmccCRG*
%{prefix}/bin/TSPump*
/etc/init.d/dsmcccrg
/etc/init.d/tspump
%config %attr(0555,root,root) %{prefix}/etc/DsmccCRG*.xml
%config %attr(0555,root,root) %{prefix}/etc/TSPump*.xml

%files scs
%defattr(-,root,root)
%{prefix}/bin/CDNCS*
%{prefix}/bin/libc2loc_web*
%{prefix}/modules/libCRM_3dServer*
%{prefix}/modules/libCRM_A3Message*
%{prefix}/modules/libCRM_C2Locator*
%{prefix}/utils/checkRH.sh
/etc/init.d/cdncs
%config %attr(0555,root,root) %{prefix}/etc/CDNCS*.xml
%config %attr(0555,root,root) %{prefix}/etc/CRM_3dServer*.xml
%config %attr(0555,root,root) %{prefix}/etc/CRM_A3Message*.xml
%config %attr(0555,root,root) %{prefix}/etc/CRM_C2Locator*.xml

%files cdn
%defattr(-,root,root)
%{prefix}/bin/CDNSS*
%{prefix}/modules/libCPH_AquaRec*
%{prefix}/modules/libCPH_CDN*
%{prefix}/bin/cleanupc2tunnel.py
%{prefix}/bin/createc2tunnel.py
/etc/init.d/cdnss
%config %attr(0555,root,root) %{prefix}/etc/CdnSS*.xml
%config %attr(0555,root,root) %{prefix}/etc/CPH_AquaRec*.xml
%config %attr(0555,root,root) %{prefix}/etc/CPH_CDN*.xml

%files watch
%defattr(-,root,root)
%{prefix}/bin/Sentry*
%{prefix}/bin/EventChannel*
%{prefix}/bin/EventGateway*
%{prefix}/bin/EventRuleEngine*
%{prefix}/bin/LogPage*
%{prefix}/bin/libNGODHist.so*
%{prefix}/bin/libClibMan_web*
%{prefix}/bin/libEventSender*
%{prefix}/bin/libAdminCtrl_web*
%{prefix}/bin/libWebLayout*
%{prefix}/modules/libCRM_DSMCC*
%{prefix}/modules/libEGH_FileWriter*
%{prefix}/modules/libEGH_JMS*
%{prefix}/modules/libEGH_SOAP_CME.so*
%{prefix}/modules/libEGH_SnmpTrap*
/etc/init.d/sentry
/etc/init.d/eventchannel
/etc/init.d/eventgateway
/etc/init.d/eventruleengine
/etc/init.d/rtspproxy
%config %attr(0555,root,root) %{prefix}/etc/Sentry*.xml
%config %attr(0555,root,root) %{prefix}/etc/weblayout*.xml
%config %attr(0555,root,root) %{prefix}/etc/EventChannel*.xml
%config %attr(0555,root,root) %{prefix}/etc/EventGateway*.xml
%config %attr(0555,root,root) %{prefix}/etc/EventRuleEngine*.xml
%config %attr(0555,root,root) %{prefix}/etc/EventRules*.xml
%config %attr(0555,root,root) %{prefix}/etc/NGODHist*.xml
%config %attr(0555,root,root) %{prefix}/etc/crm_Dsmcc*.xml
%config %attr(0555,root,root) %{prefix}/etc/EGH_FileWriter*.xml
%config %attr(0555,root,root) %{prefix}/etc/EGH_JMS*.xml
%config %attr(0555,root,root) %{prefix}/etc/EGH_SOAP_CME*.xml
%config %attr(0555,root,root) %{prefix}/etc/EGH_SnmpTrap*.xml

%files srm
%defattr(-,root,root)
%{prefix}/bin/PathAdmin*
%{prefix}/bin/SiteAdmin*
%{prefix}/bin/Weiwoo*
%{prefix}/modules/libPHO_ERM*
%{prefix}/modules/libPHO_HttpSS.so*
%{prefix}/modules/libPHO_SeaChange*
%{prefix}/modules/libPHO_VSS*
/etc/init.d/siteadmin
/etc/init.d/weiwoo
%config %attr(0555,root,root) %{prefix}/etc/Weiwoo*.xml
%config %attr(0555,root,root) %{prefix}/etc/SiteAdminSvc*.xml
%config %attr(0555,root,root) %{prefix}/etc/pho_ERM*.xml
%config %attr(0555,root,root) %{prefix}/etc/pho_vss*.xml

%files stream
%defattr(-,root,root)
%{prefix}/bin/C2SS*
%{prefix}/bin/DummySS*
%{prefix}/bin/DummySvc*
%{prefix}/bin/NSS*
%{prefix}/bin/StreamClient*
%{prefix}/bin/GBCS*
%{prefix}/bin/GBVSS*
/etc/init.d/c2ss
/etc/init.d/dummysvc
/etc/init.d/gbvss
/etc/init.d/nss
/etc/init.d/gbcs
%config %attr(0555,root,root) %{prefix}/etc/C2SS*.xml
%config %attr(0555,root,root) %{prefix}/etc/DummySvc*.xml
%config %attr(0555,root,root) %{prefix}/etc/dummyss.conf
%config %attr(0555,root,root) %{prefix}/etc/NSS*.xml
%config %attr(0555,root,root) %{prefix}/etc/GBCS*.xml
%config %attr(0555,root,root) %{prefix}/etc/GBVSS*.xml

%files edgerm
%defattr(-,root,root)
%{prefix}/bin/EdgeRM*
%{prefix}/bin/EdgeRMClient*
%{prefix}/bin/libErmMan_web*
/etc/init.d/edgerm
%config %attr(0555,root,root) %{prefix}/etc/EdgeRMSvc*.xml

%files app
%defattr(-,root,root)
%{prefix}/bin/BcastChannel*
%{prefix}/bin/GBMODApp*
%{prefix}/bin/MODApp*
%{prefix}/bin/libBcastChMan_web.so*
%{prefix}/modules/libMHO_GBMOD*
%{prefix}/modules/libMHO_MOD*
/etc/init.d/bcastchannel
/etc/init.d/gbmodapp
/etc/init.d/modapp
%config %attr(0555,root,root) %{prefix}/etc/BroadcastChannel*.xml
%config %attr(0555,root,root) %{prefix}/etc/MovieOnDemand*.xml
%config %attr(0555,root,root) %{prefix}/etc/GBMovieOnDemand*.xml

%files utils
%defattr(-,root,root)
%{prefix}/bin/tslicapp*
%{prefix}/bin/xmlshd*
%{prefix}/utils/ver_check
/etc/init.d/xmlshd
%config %attr(0555,root,root) %{prefix}/etc/xmlshd*.xml

%files 
%defattr(-,root,root)

%config %attr(0555,root,root) %{prefix}/etc/ 

%{prefix}/logs/
%{prefix}/data/
%{prefix}/utils/
%{prefix}/modules/
%{prefix}/bin/
%{prefix}/CTF/
%{prefix}/webctrl/
/etc/init.d/*

# vim: ts=4 sw=4 bg=dark

