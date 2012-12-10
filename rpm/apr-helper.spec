Summary:            A simple library for helping use of Apache Portable Runtime in C++
Name:               apr-helper
Version:            0.1.0
Release:            21%{?dist}
License:            LGPLv2+
Group:              Development
Source:             %{name}-%{version}.tar.gz
URL:                https://github.com/aevalo/apr-helper 
BuildRequires:      apr-devel, apr-util-devel, pcre-devel
Requires:           apr, apr-util, pcre

%description
Simplify the usage of Apache Portable Runtime with C++.

%prep
%setup -q

%build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%{buildroot} -DAPR_HELPER_BUILD_HAS_CXX11=1 -DAPR_HELPER_BUILD_SHARED=1 ..
make %{?_smp_mflags}

%install
cd build
make install

%files
/include/*
/lib/*
/bin/*
/test_data/*

%changelog
* Mon Dec 10 2012 Arttu Valo <arttu.valo@gmail.com> 0.1.0-20
- Added RPM build files to project.

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

