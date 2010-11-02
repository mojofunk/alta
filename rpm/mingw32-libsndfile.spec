%define __strip %{_mingw32_strip}
%define __objdump %{_mingw32_objdump}
%define _use_internal_dependency_generator 0
%define __find_requires %{_mingw32_findrequires}
%define __find_provides %{_mingw32_findprovides}

Name:		mingw32-libsndfile
Version:	1.0.23
Release:	1%{?dist}
Summary:	Library for reading and writing sound files
License:	LGPLv2+
Group:		System Environment/Libraries
URL:		http://www.mega-nerd.com/libsndfile/
Source0:	http://www.mega-nerd.com/libsndfile/libsndfile-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-buildroot-%(%{__id_u} -n)

BuildArch:      noarch

BuildRequires: mingw32-filesystem
BuildRequires: mingw32-gcc
BuildRequires: mingw32-gcc-c++
BuildRequires: mingw32-binutils
BuildRequires: pkgconfig 

Requires: pkgconfig


%description
libsndfile is a C library for reading and writing sound files such as
AIFF, AU, WAV, and others through one standard interface. It can
currently read/write 8, 16, 24 and 32-bit PCM files as well as 32 and
64-bit floating point WAV files and a number of compressed formats. It
compiles and runs on *nix, MacOS, and Win32.


%package devel
Summary:	Development files for libsndfile
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release} pkgconfig


%description devel
libsndfile is a C library for reading and writing sound files such as
AIFF, AU, WAV, and others through one standard interface.
This package contains files needed to develop with libsndfile.


%prep
%setup -q -n libsndfile-%{version}

%build
%{_mingw32_configure}  \
	--disable-dependency-tracking \
	--disable-static \
	--disable-alsa \
	--disable-sqlite \
	--disable-external-libs \
	--disable-shave
	#--enable-largefile

make %{?_smp_mflags}


%install
rm -rf %{buildroot} __docs
make install DESTDIR=%{buildroot}
cp -pR %{buildroot}%{_mingw32_docdir}/libsndfile1-dev/html __docs
rm -rf %{buildroot}%{_mingw32_docdir}/libsndfile1-dev

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc COPYING AUTHORS README NEWS ChangeLog
%{_mingw32_bindir}/*sndfile*.exe
%{_mingw32_mandir}/man1/*.1
%{_mingw32_bindir}/libsndfile-1.dll


%files devel
%defattr(-,root,root,-)
%doc __docs/*
%exclude %{_mingw32_libdir}/libsndfile.la
%{_mingw32_includedir}/sndfile.h
%{_mingw32_includedir}/sndfile.hh
%{_mingw32_libdir}/libsndfile.dll.a
%{_mingw32_libdir}/pkgconfig/sndfile.pc


%changelog
* Wed Nov 3 2010 Tim Mayberry <mojofunk@gmail.com> - 1.0.23-1
- update to latest release
- added --disable-shave to configure options to allow build to succeed
* Sun Nov 30 2008 Tim Mayberry <mojofunk@gmail.com> - 1.0.18pre24h-1
- Initial MinGW build of pre-release version
