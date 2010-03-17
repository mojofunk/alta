%global __strip %{_mingw32_strip}
%global __objdump %{_mingw32_objdump}
%global _use_internal_dependency_generator 0
%global __find_requires %{_mingw32_findrequires}
%global __find_provides %{_mingw32_findprovides}
%define __debug_install_post %{_mingw32_debug_install_post}

Name:           mingw32-goocanvas
Version:        0.15
Release:        1%{?dist}
Summary:        MinGW Windows GooCanvas library

License:        LGPLv2+
Group:          Developement/Libraries
URL:            http://sourceforge.net/projects/goocanvas
Source0:        ftp://ftp.gnome.org/pub/GNOME/sources/0.15/goocanvas/goocanvas-%{version}.tar.bz2
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildArch:      noarch

BuildRequires:  mingw32-filesystem >= 52
BuildRequires:  mingw32-gcc
BuildRequires:  mingw32-binutils
BuildRequires:  mingw32-gettext
BuildRequires:  mingw32-gtk2
BuildRequires:  pkgconfig

%description
MinGW Windows GooCanvas library.

%{_mingw32_debug_package}

%prep
%setup -q -n goocanvas-%{version}

# demo application does not compile properly
#sed -i -e 's/ demo / /g' Makefile.am
#sed -i -e 's/ demo / /g' Makefile.in

%build
%{_mingw32_configure} --disable-static
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

# remove static libraries and libtool droppings
#rm -f $RPM_BUILD_ROOT/%{_mingw32_libdir}/libgoocanvas.{a, la}
	
%find_lang goocanvas
	
%clean
rm -rf $RPM_BUILD_ROOT

%files -f goocanvas.lang
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING NEWS README TODO
%{_mingw32_bindir}/libgoocanvas-3.dll
%{_mingw32_libdir}/libgoocanvas.dll.a
%{_mingw32_libdir}/libgoocanvas.la
# devel:
%{_mingw32_libdir}/pkgconfig/goocanvas.pc
%{_mingw32_includedir}/goocanvas-1.0
%{_mingw32_datadir}/gtk-doc/html/goocanvas
	
	
%changelog
* Wed Mar 17 2010 Tim Mayberry <mojofunk@gmail.com> - 0.15-1
- initial release for mingw32
