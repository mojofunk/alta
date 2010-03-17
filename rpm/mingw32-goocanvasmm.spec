%global __strip %{_mingw32_strip}
%global __objdump %{_mingw32_objdump}
%global _use_internal_dependency_generator 0
%global __find_requires %{_mingw32_findrequires}
%global __find_provides %{_mingw32_findprovides}
%define __debug_install_post %{_mingw32_debug_install_post}

Name:           mingw32-goocanvasmm
Version:        0.15.1
Release:        1%{?dist}

Summary:        MinGW Windows C++ interface for goocanvas

License:        LGPLv2+
Group:          System Environment/Libraries
URL:            http://gtkmm.sourceforge.net/
Source0:        http://ftp.gnome.org/pub/GNOME/sources/goocanvasmm/0.15/goocanvasmm-%{version}.tar.bz2
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildArch:      noarch

BuildRequires:  mingw32-filesystem >= 52
BuildRequires:  mingw32-gcc
BuildRequires:  mingw32-gcc-c++
BuildRequires:  mingw32-binutils
BuildRequires:  mingw32-libsigc++20 >= 2.0.0
BuildRequires:  mingw32-glibmm24 >= 2.14.2
BuildRequires:  mingw32-gtkmm24 >= 2.10.9
BuildRequires:  mingw32-goocanvas >= 0.14
BuildRequires:  pkgconfig
#BuildRequires:  doxygen graphviz

Requires:       pkgconfig


%description
This package provides a C++ interface for goocanvas. It is a
subpackage of the gtkmm project. The interface provides a convenient
interface for C++ programmers to create Gnome GUIs with GTK+'s
flexible object-oriented framework.

#%{_mingw32_debug_package}

#%package        devel
#Summary:        Headers for developing programs that will use %{name}
#Group:          Development/Libraries
#Requires:       %{name} = %{version}-%{release}
#Requires:       gtkmm24-devel
#Requires:       goocanvas-devel
#Requires:       pkgconfig

%prep
%setup -q -n goocanvasmm-%{version}


%build
%{_mingw32_configure} --disable-static --enable-documentation=no
make %{?_smp_mflags}

# Build documentation
#(cd docs/reference; doxygen -u 2> /dev/null)
#make -C docs/reference/

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -type f -name "*.la" -exec rm -f {} ';'
#mkdir docs-to-include
#mv docs/reference/html docs-to-include/
#rm -r $RPM_BUILD_ROOT%{_libdir}/goocanvasmm-0.1


%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root, -)
%doc AUTHORS ChangeLog COPYING NEWS README
#%{_libdir}/*..*
%{_mingw32_bindir}/libgoocanvasmm-1.0-5.dll
%{_mingw32_libdir}/libgoocanvasmm-1.0.dll.a
%{_mingw32_libdir}/pkgconfig/goocanvasmm-1.0.pc
%{_mingw32_includedir}/goocanvasmm-1.0
%{_mingw32_libdir}/goocanvasmm-1.0/include/goocanvasmmconfig.h

#%{_libdir}/*.so
#%{_libdir}/pkgconfig/*.pc


%changelog
* Wed Mar 17 2010 Tim Mayberry <mojofunk@gmail.com> - 0.15.1-1
- First build for MinGW based on native spec file
