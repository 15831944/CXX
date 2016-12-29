%define targetdir   opt
%define productname   TianShan

Name:      TianShan-watch
Version:   2.0.3
Release:   0
Summary:   ZQ Stream Server 
Group:     Applications/System
License:   commercial
BuildArch: x86_64
BuildRoot: /var/tmp/%{productname}-buildroot

Conflicts: TianShan

%define __os_install_post  %{nil}
%define __prelink_undo_cmd %{nil}

%define _topdir       %(echo ${HOME})
%define _rpmdir       %(echo ${OutputPath})
%define _rpmfilename  %(echo ${MonitorPKG})
%define _builddir     ${ZQProjsPath}/build

%description
TianShan Monitor

%define prefix        /opt/%{productname}
%define postfix       %([ $(uname -m) = "x86_64" ] && echo "64")
%define oid           .1.3.6.1.4.1.22839.4.1
%define snmp_agent    %{prefix}/bin/libSnmpAgent*
%define snmp_server   127.0.0.1
%define	etcfix		/etc


%define dest_dir      %{buildroot}/%{prefix}
%define dest_cfg_dir  %{dest_dir}/etc
%define dest_bin_dir  %{dest_dir}/bin
%define dest_util_dir %{dest_dir}/utils
%define dest_mod_dir  %{dest_dir}/modules
%define dest_svc_dir  %{buildroot}/etc

%define svc_runlevel  2345
%define svc_seq_pre   9

%define sdk_dir		/opt/sdk
%define ctf_dir       %{sdk_dir}/SeaChangeKits/ctflib
%define ctf_inc_dir   %{ctf_dir}/Include
%define ice_dir       %{sdk_dir}/3rdPartyKits/ice
%define boost_dir     %{sdk_dir}/3rdPartyKits/boost
%define snmp_dir      %{sdk_dir}/3rdPartyKits/net-snmp
%define snmpp_dir     %{sdk_dir}/3rdPartyKits/snmp++
%define libnl_dir     %{sdk_dir}/3rdPartyKits/libnl
%define libpcap_dir   %{sdk_dir}/3rdPartyKits/libpcap
%define e2fsprogs_dir %{sdk_dir}/3rdPartyKits/e2fsprogs

%define src_dir       ${ZQProjsPath}/%{productname}
%define src_generic   ${ZQProjsPath}/Generic
%define src_cfg_dir   %{src_dir}/etc
%define src_bin_dir   %{src_dir}/bin64
%define src_lib_dir   %{src_dir}/lib64
%define src_mod_dir   %{src_dir}/modules
%define src_build_dir %{_builddir}
%define src_util_dir  %{src_build_dir}/utils
%define src_ctf_dir   %{ctf_dir}/LINUX%{postfix}_REL

%define svc_daemons   EventChannel Sentry EventGateway xmlshd

# clean object files and target files in sub dirs
#make veryclean

# clean temp dir for rpm package
#[ -d %{buildroot} ] && rm -rvf %{buildroot}

#%build

#make debug=${Debug} version=%{version}.%{release}

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

rm -rf $RPM_BUILD_ROOT

mkdir -pv $RPM_BUILD_ROOT/{etc/init.d/,opt/%{productname}/{bin/java,logs/{crashdump,rtrec},etc,data/runtime,utils,modules,webctrl/{images/toolbar,images/tree,img}}}

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
xmlshd="xmlshd service"

i=0
for svc in %{svc_daemons}; do
    script=$(echo ${svc} | sed 's/.*/\L&\E/')
    eval desc=\$${svc}
    echo -e "#!/bin/bash\n#\n# chkconfig: %{svc_runlevel} %{svc_seq_pre}${i} 04\n# description: ${desc}\n#\n\nservice=${svc}\n\n. %{prefix}/utils/tianshan\n" > %{src_util_dir}/${script}
    chmod a+x %{src_util_dir}/${script}
    install  %{src_util_dir}/${script} %{dest_svc_dir}/init.d/
	[ $i -lt 9 ] && i=$((i+1))
done
chmod a+x %{src_util_dir}/tianshan
cp -vp %{src_util_dir}/tianshan %{dest_util_dir}


install --directory %{targetdir}/TianShan/bin
install --directory %{targetdir}/TianShan/bin/java
install --directory %{targetdir}/TianShan/etc
install --directory %{targetdir}/TianShan/logs
install --directory %{targetdir}/TianShan/logs/crashdump
install --directory %{targetdir}/TianShan/rtrec
install --directory %{targetdir}/TianShan/data
install --directory %{targetdir}/TianShan/data/runtime
install --directory %{targetdir}/TianShan/utils
install --directory %{targetdir}/TianShan/modules
install --directory %{targetdir}/TianShan/webctrl
install --directory %{targetdir}/TianShan/webctrl/images
install --directory %{targetdir}/TianShan/webctrl/img
install --directory %{targetdir}/TianShan/webctrl/images/toolbar
install --directory %{targetdir}/TianShan/webctrl/images/tree

install %{ice_dir}/lib/libIce.so.*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libIceBox.so.*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libIceStorm.so.*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libIceStormService.so.*	$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libIceUtil.so.*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libFreeze.so.*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{ice_dir}/lib/libdb_cxx-4.5.so		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{boost_dir}/lib64/libboost_regex.so.1.56.0	$RPM_BUILD_ROOT/opt/TianShan/bin
install %{boost_dir}/lib64/libboost_regex.so       $RPM_BUILD_ROOT/opt/TianShan/bin
#install %{boost_dir}/lib/libboost_regex.so.2     $RPM_BUILD_ROOT/opt/TianShan/bin
install %{snmpp_dir}/lib/libsnmp++.so		 $RPM_BUILD_ROOT/opt/TianShan/bin
install %{snmpp_dir}/lib/libsnmp++.so.*          $RPM_BUILD_ROOT/opt/TianShan/bin
#install %{_libdir}/libicui18n.so.*          	$RPM_BUILD_ROOT/opt/TianShan/bin
#install %{_libdir}/libicuuc.so.*            	$RPM_BUILD_ROOT/opt/TianShan/bin
#install %{_libdir}/libicudata.so.*          	$RPM_BUILD_ROOT/opt/TianShan/bin

install %{src_bin_dir}/EventChannel*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/EventGateway*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/Sentry*			$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libWebLayout*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libZQCommon*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libSnmpManPkg*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libSnmpAgent*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libTianShanIce*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libJndiClient*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/xmlshd*			$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/SystemShell*		$RPM_BUILD_ROOT/opt/TianShan/bin
install %{src_bin_dir}/libMsgSender*		$RPM_BUILD_ROOT/opt/TianShan/bin

install %{src_generic}/JndiClient/JndiClient.jar	$RPM_BUILD_ROOT/opt/TianShan/bin/java
install %{src_generic}/JndiClient/jbossall-client.jar	$RPM_BUILD_ROOT/opt/TianShan/bin/java

install %{src_dir}/webctrl/*.*			$RPM_BUILD_ROOT/opt/TianShan/webctrl
install %{src_dir}/webctrl/images/toolbar/*	$RPM_BUILD_ROOT/opt/TianShan/webctrl/images/toolbar
install %{src_dir}/webctrl/images/tree/*	$RPM_BUILD_ROOT/opt/TianShan/webctrl/images/tree
install %{src_dir}/webctrl/img/*		$RPM_BUILD_ROOT/opt/TianShan/webctrl/img			

install %{src_mod_dir}/libEGH_JMS*		$RPM_BUILD_ROOT/opt/TianShan/modules
install %{src_cfg_dir}/Sentry_linux.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/Sentry_sample.xml
install %{src_cfg_dir}/weblayout_linux.xml	$RPM_BUILD_ROOT/opt/TianShan/etc/weblayout_sample.xml
install %{src_cfg_dir}/MsgSender.xml			$RPM_BUILD_ROOT/opt/TianShan/etc/MsgSender_sample.xml
install %{src_cfg_dir}/EventChannel.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/EventChannel_sample.xml
install %{src_cfg_dir}/EventGateway.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/EventGateway_sample.xml
install %{src_cfg_dir}/EGH_JMS.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/EGH_JMS_sample.xml
install %{src_cfg_dir}/TianShanDef.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/TianShanDef_sample.xml
install %{src_cfg_dir}/xmlshd.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/xmlshd_sample.xml
install %{src_cfg_dir}/syntax.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/syntax.xml
#install %{src_dir}/TianShan.xml			$RPM_BUILD_ROOT/opt/TianShan/etc/TianShan.xml
install %{src_cfg_dir}/COF_LinuxSystemEvent.xml	$RPM_BUILD_ROOT/opt/TianShan/etc/COF_LinuxSystemEvent_sample.xml
install %{src_cfg_dir}/COF_VstreamEvent.xml	$RPM_BUILD_ROOT/opt/TianShan/etc/COF_VstreamEvent_sample.xml
install %{src_cfg_dir}/COF_SystemEvent.xml	$RPM_BUILD_ROOT/opt/TianShan/etc/COF_SystemEvent_sample.xml
install %{src_cfg_dir}/COF_WinEvent.xml		$RPM_BUILD_ROOT/opt/TianShan/etc/COF_WinEvent_sample.xml
install %{src_cfg_dir}/umlconf.tar.gz		$RPM_BUILD_ROOT/opt/TianShan/etc/

install %{src_util_dir}/tianshan		$RPM_BUILD_ROOT/opt/TianShan/utils

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

%post
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

#cp -vp $RPM_BUILD_ROOT/opt/TianShan/etc/TianShan.xml /etc/TianShan.xml 

tar zxvkf  /opt/TianShan/etc/umlconf.tar.gz -C /opt/TianShan/etc/

cp -vp /opt/TianShan/etc/TianShan.xml /etc/TianShan.xml 


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

%files

%defattr(-,root,root)
%config %attr(0555,root,root) %{prefix}/etc/ 
%{prefix}/logs/
%{prefix}/data/
%{prefix}/utils/
%{prefix}/modules/
%{prefix}/bin/
%{prefix}/bin/java/
%{prefix}/webctrl/
/etc/init.d/*

# vim: ts=4 sw=4 bg=dark
