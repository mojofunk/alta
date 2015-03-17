#!/bin/bash

. ./msys2-env.sh

DLLS='
jack-0.dll
jackserver-0.dll
libatk-1.0-0.dll
libatkmm-1.6-1.dll
libbz2-1.dll
libcairo-2.dll
libcairo-gobject-2.dll
libcairomm-1.0-1.dll
libcairo-script-interpreter-2.dll
libcppunit-1-13-0.dll
libcurl-4.dll
libeay32.dll
libexpat-1.dll
libfftw3-3.dll
libfftw3f-3.dll
libfontconfig-1.dll
libfreetype-6.dll
libgailutil-18.dll
libgcc_s_dw2-1.dll
libgdkmm-2.4-1.dll
libgdk_pixbuf-2.0-0.dll
libgdk-win32-2.0-0.dll
libgio-2.0-0.dll
libgiomm-2.4-1.dll
libglib-2.0-0.dll
libglibmm-2.4-1.dll
libglibmm_generate_extra_defs-2.4-1.dll
libgmodule-2.0-0.dll
libgobject-2.0-0.dll
libgthread-2.0-0.dll
libgtkmm-2.4-1.dll
libgtk-win32-2.0-0.dll
libharfbuzz-0.dll
libltc-11.dll
libiconv-2.dll
libFLAC-8.dll
libogg-0.dll
libvorbis-0.dll
libvorbisenc-2.dll
libffi-6.dll
libidn-11.dll
libintl-8.dll
liblo-7.dll
libpango-1.0-0.dll
libpangocairo-1.0-0.dll
libpangoft2-1.0-0.dll
libpangomm-1.4-1.dll
libpangowin32-1.0-0.dll
libpixman-1-0.dll
libpng16-16.dll
libpython2.7.dll
rubberband-2.dll
libsamplerate-0.dll
libsigc-2.0-0.dll
libsndfile-1.dll
libssh2-1.dll
libstdc++-6.dll
libtag.dll
libxml2-2.dll
libwinpthread-1.dll
libportaudio-2.dll
vamp-hostsdk-3.dll
vamp-sdk-2.dll
zlib1.dll
lilv-0.dll
sratom-0-0.dll
serd-0-0.dll
sord-0-0.dll
'

WITH_JACK='TRUE'
WITH_LV2='TRUE'

. ./copydll-default.sh
. ./package.sh