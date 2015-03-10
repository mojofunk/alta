#! /bin/bash

# This is not a standalone script

echo "Copying config files to $PACKAGE_DIR ..."
mkdir -p $PACKAGE_DIR/etc
cp -RL $MINGW_ROOT/etc/fonts $PACKAGE_DIR/etc
cp -RL $MINGW_ROOT/etc/gtk-2.0 $PACKAGE_DIR/etc
cp -RL $MINGW_ROOT/etc/pango $PACKAGE_DIR/etc

cp -R $MINGW_ROOT/lib/gtk-2.0 $PACKAGE_DIR/lib

# Copy any gdk-pixbuf2 modules if they exist
if [ -d $MINGW_ROOT/lib/gdk-pixbuf-2.0 ]; then
    echo "Copying gdk-pixbuf2 modules to $PACKAGE_LIB_DIR ..."
    cp -R $MINGW_ROOT/lib/gdk-pixbuf-2.0 $PACKAGE_LIB_DIR
    cp $TOOLS_DIR/loaders.cache $PACKAGE_LIB_DIR/gdk-pixbuf-2.0/2.10.0/loaders.cache
fi

# Copy any pango modules if they exist
if [ -d $MINGW_ROOT/lib/pango/1.8.0/modules ]; then
    echo "Copying pango modules to $PACKAGE_LIB_DIR ..."
    mkdir -p $PACKAGE_LIB_DIR/pango/1.8.0/modules
    cp -r $MINGW_ROOT/lib/pango/1.8.0/modules/*.dll $PACKAGE_LIB_DIR/pango/1.8.0/modules
    cp $TOOLS_DIR/pango.modules $PACKAGE_DIR/etc/pango
fi

if [ x$DEBUG = xT ]; then
	echo "Copying Gtk demo to $PACKAGE_BIN_DIR ..."
	cp $MINGW_ROOT/bin/gtk-demo.exe $PACKAGE_BIN_DIR
fi
