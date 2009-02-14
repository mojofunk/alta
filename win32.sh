
export HOST=i686-pc-mingw32

export MINGW_ROOT=/usr/$HOST/sys-root/mingw
export PKG_CONFIG_PREFIX=$MINGW_ROOT
export PKG_CONFIG_LIBDIR=$MINGW_ROOT/lib/pkgconfig
export AR=$HOST-ar
export RANLIB=$HOST-ranlib
export CC=$HOST-gcc
export CPP=$HOST-g++
export CXX=$HOST-g++
export LINK_CC=$HOST-gcc
export LINK_CXX=$HOST-g++
export WINRC=$HOST-windres

./waf configure --with-target-platform=win32
./waf -v -j1 "$@"
