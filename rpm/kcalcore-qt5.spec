# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.26
# 

Name:       kcalcore-qt5

# >> macros
# << macros

Summary:    Port of KDE kcalcore calendar library
Version:    4.10.2
Release:    1
Group:      System/Libraries
License:    LGPL 2
URL:        https://github.com/mer-packages/kcalcore
Source0:    %{name}-%{version}.tar.bz2
Source100:  kcalcore-qt5.yaml
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(dbus-1)
BuildRequires:  pkgconfig(libical)
BuildRequires:  pkgconfig(uuid)

%description
Port of KDE kcalcore calendar library


%package devel
Summary:    Development files for kcalcore
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
This package contains the files necessary to develop
applications using kcalcore


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qmake5 

make %{?jobs:-j%jobs}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake_install

# >> install post
# << install post

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libkcalcoren-qt5.so.*
# >> files
# << files

%files devel
%defattr(-,root,root,-)
%{_includedir}/kcalcoren-qt5/*
%{_libdir}/libkcalcoren-qt5.so
%{_libdir}/pkgconfig/*.pc
# >> files devel
# << files devel
