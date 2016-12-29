Name:      TAO
Version:   1.7.7
Release:   0
Summary:   TAO Naming Service
Group:     Application/System
License:   commercial
BuildArch: x86_64
BuildRoot: %{_tmppath}/%{name}-root

%define __os_install_post  %{nil}
%define __prelink_undo_cmd %{nil}

%define prefix        /usr/local

%define src_dir       %{prefix}
%define src_bin_dir   %{src_dir}/bin
%define src_lib_dir   %{src_dir}/lib

%define dest_dir      %{buildroot}/%{prefix}
%define dest_bin_dir  %{dest_dir}/bin
%define dest_lib_dir  %{dest_dir}/lib

%define dep_tao ImR_Client CosNaming_Serv IORTable Svc_Utils Messaging CosNaming_Skel Valuetype PI CodecFactory PortableServer CosNaming AnyTypeCode Strategies SmartProxies CosEvent CosEvent_Skel CosEvent_Serv CosNotification CosNotification_Skel CosNotification_Serv DynamicAny DynamicInterface ETCL IFR_Client

%define dep_ace ETCL ETCL_Parser XML XML_Parser

%define tao_ver_maj 1
%define tao_ver     1.7.7
%define ace_ver     5.7.7

%description
TAO Naming Service

%prep

%build

%pre

%install 

mkdir -pv %{buildroot}/{etc/init.d,usr/local/{lib,bin}}

for dep in %{dep_tao}; do
    cp -vP %{src_lib_dir}/{libTAO_${dep}.so.%{tao_ver_maj},libTAO_${dep}.so.%{tao_ver},libTAO_${dep}.so} %{dest_lib_dir}
done
for dep in %{dep_ace}; do
    if [ "${dep:0:3}" = "XML" ]; then
        cp -vP %{src_lib_dir}/{libACE${dep}-%{ace_ver}.so,libACE${dep}.so} %{dest_lib_dir}
    else
        cp -vP %{src_lib_dir}/{libACE_${dep}-%{ace_ver}.so,libACE_${dep}.so} %{dest_lib_dir}
    fi
done
cp -vP %{src_lib_dir}/{libTAO.so.%{tao_ver_maj},libTAO.so.%{tao_ver}} %{dest_lib_dir}
cp -v %{src_lib_dir}/libACE-%{ace_ver}.so %{dest_lib_dir}
cp -v %{src_bin_dir}/Naming_Service %{dest_bin_dir}

# service script
cp -v /etc/init.d/tao %{buildroot}/etc/init.d/

%post
%postun

%clean

rm -rf %{buildroot}

%files 
%defattr(-,root,root)
%{prefix}/bin/
%{prefix}/lib/
/etc/init.d/*
