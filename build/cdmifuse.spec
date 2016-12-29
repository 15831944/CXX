# spec for building cdmifuse
%define topdir	 	$ZQProjsPath
%define name		CdmiFuse 
%define release		0
%define version 	0.1
%define buildroot   /var/tmp/%{name}-buildroot
%define versuffix   %{version}.%{release}
%define sdkpath     /opt/sdk/
%define curlpath    %{sdkpath}/3rdPartyKits/curl
%define boostpath		%{sdkpath}/3rdPartyKits/boost

BuildRoot:	    %{buildroot}
Summary: 		fuse for cdmi
License: 		Commercial
Name:			%{name}
Version:		%{version}
Release:		%{release}
Source: 		%{name}-%{version}.tar.gz
Prefix: 		/opt/cdmifuse
Group: 			System
Requires:       fuse curl openssl python-simplejson

%description
fuse with cdmi interface implementation

%prep
rm -rf $RPM_BUILD_ROOT

%build
make -C %{topdir}/build CdmiFuse dbgfile=0 debug=0 version=%{versuffix}

%pre
# stop cdmifuse service before upgrade
if [ "$1" = "2" ]; then
	[ -x /etc/init.d/cdmifuse ] && /etc/init.d/cdmifuse stop
	exit 0
fi

%install
mkdir -p $RPM_BUILD_ROOT/%{prefix}/bin
mkdir -p $RPM_BUILD_ROOT/%{prefix}/etc
mkdir -p $RPM_BUILD_ROOT/%{prefix}/logs
mkdir -p $RPM_BUILD_ROOT/%{prefix}/SDK/java
mkdir -p $RPM_BUILD_ROOT/%{prefix}/SDK/python
mkdir -p $RPM_BUILD_ROOT/%{prefix}/SDK/doc
mkdir -p $RPM_BUILD_ROOT/%{prefix}/mountpoint

install %{boostpath}/lib64/libboost_system-mt.so.1.56.0 $RPM_BUILD_ROOT/%{prefix}/bin
install %{boostpath}/lib64/libboost_system-mt-d.so.1.56.0 $RPM_BUILD_ROOT/%{prefix}/bin
install %{boostpath}/lib64/libboost_thread-mt.so.1.56.0 $RPM_BUILD_ROOT/%{prefix}/bin

install %{topdir}/Common/libZQCommon.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin
ln -sf  libZQCommon.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin/libZQCommon.so 
install %{curlpath}/lib/libcurl.so.4.3.0 $RPM_BUILD_ROOT/%{prefix}/bin
ln -sf  libcurl.so.4.3.0 $RPM_BUILD_ROOT/%{prefix}/bin/libcurl.so.4
install %{topdir}/Generic/CdmiFuse/sdk/libAquaClient.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin
ln -sf libAquaClient.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin/libAquaClient.so

install %{topdir}/Generic/CdmiFuse/linux/cdmifuse.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin
ln -sf  cdmifuse.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/bin/cdmifuse
install %{topdir}/Generic/CdmiFuse/linux/daemon.py $RPM_BUILD_ROOT/%{prefix}/bin
install %{topdir}/Generic/CdmiFuse/linux/fuseshell.py $RPM_BUILD_ROOT/%{prefix}/bin
install %{topdir}/Generic/CdmiFuse/linux/pidlockfile.py $RPM_BUILD_ROOT/%{prefix}/bin
install %{topdir}/Generic/CdmiFuse/linux/runner.py $RPM_BUILD_ROOT/%{prefix}/bin
install %{topdir}/Generic/CdmiFuse/linux/lockfile.py $RPM_BUILD_ROOT/%{prefix}/bin
install %{topdir}/Generic/CdmiFuse/linux/cdmifuse.conf $RPM_BUILD_ROOT/%{prefix}/etc/cdmifuse_sample.conf
install %{topdir}/Generic/CdmiFuse/linux/cdmifuse.sh $RPM_BUILD_ROOT/%{prefix}/etc
install %{topdir}/Generic/CdmiFuse/linux/initd_funcs $RPM_BUILD_ROOT/%{prefix}/etc

install %{topdir}/Generic/CdmiFuse/sdk/libAquaClient.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/SDK
ln -sf libAquaClient.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/SDK/libAquaClient.so
install %{topdir}/Generic/CdmiFuse/sdk/java/bin/AquaClient.jar $RPM_BUILD_ROOT/%{prefix}/SDK/java
install %{topdir}/Generic/CdmiFuse/sdk/java/lib/*.jar $RPM_BUILD_ROOT/%{prefix}/SDK/java
install %{topdir}/Generic/CdmiFuse/sdk/java/com/xormedia/aqua/sdk/AquaClientTest.java $RPM_BUILD_ROOT/%{prefix}/SDK/java
install %{topdir}/Generic/CdmiFuse/sdk/python/*.py $RPM_BUILD_ROOT/%{prefix}/SDK/python
install %{topdir}/Generic/CdmiFuse/sdk/python/client.config.json $RPM_BUILD_ROOT/%{prefix}/SDK/python
ln -sf	../libAquaClient.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/SDK/python/AquaClient.so
ln -sf	../../bin/libZQCommon.so.%{versuffix} $RPM_BUILD_ROOT/%{prefix}/SDK/python/libZQCommon.so
install %{topdir}/Generic/CdmiFuse/doc/"CDMI FUSE Extension thru ioctl".doc $RPM_BUILD_ROOT/%{prefix}/SDK/doc
install %{topdir}/Generic/CdmiFuse/doc/AquaClientSDK.doc $RPM_BUILD_ROOT/%{prefix}/SDK/doc

%post
ln -sf %{prefix}/etc/cdmifuse.sh /etc/init.d/cdmifuse
chmod +x /etc/init.d/cdmifuse
chmod +x /opt/cdmifuse/bin/fuseshell.py

# stop all running service before upgrade
if [ "$1" = "2" ]; then 
    [ -x %{prefix}/etc/cdmifuse.sh ] && %{prefix}/etc/cdmifuse.sh stop
    exit 0
fi

%preun
# stop cdmifuse service before uninstall
if [ "$1" = "0" ]; then
	[ -x /etc/init.d/cdmifuse ] && /etc/init.d/cdmifuse stop
	exit 0
fi

%files
%defattr(-,root,root)
/%{prefix}/*
