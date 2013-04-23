# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.26
# 

Name:       kcalcore

# >> macros
# << macros

Summary:    Extended KDE kcal calendar library port for Maemo
Version:    4.10.2
Release:    1
Group:      System/Libraries
License:    LGPLv2
Source0:    %{name}-%{version}.tar.gz
Source100:  kcalcore.yaml
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(QtCore)
BuildRequires:  pkgconfig(QtDBus)
BuildRequires:  pkgconfig(libical)
BuildRequires:  pkgconfig(sqlite3)
BuildRequires:  pkgconfig(uuid)
BuildRequires:  doxygen
BuildRequires:  fdupes

%description
%{summary}.

%package devel
Summary:    Development files for %{name}
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
%{summary}.

%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qmake 

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
%{_libdir}/libkcalcoren.so.*
# >> files
# << files

%files devel
%defattr(-,root,root,-)
%{_includedir}/kcalcoren/*
%{_libdir}/libkcalcoren.so
%{_libdir}/pkgconfig/*.pc
# >> files devel
# << files devel
