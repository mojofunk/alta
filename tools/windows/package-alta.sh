#! /bin/bash

# This is not a standalone script

$PYTHON ./waf --destdir=$PACKAGE_DIR install || exit 1

echo "Moving $PROGRAM_NAME dll's and executable to $PACKAGE_BIN_DIR ..."

#mv $PACKAGE_LIB_DIR/ardour3/*.dll $PACKAGE_BIN_DIR || exit 1
#mv $PACKAGE_LIB_DIR/ardour3/*.exe $PACKAGE_BIN_DIR || exit 1

echo "Deleting import libs ..."

rm $PACKAGE_LIB_DIR/*dll.a

# delete sh script
#rm $PACKAGE_BIN_DIR/ardour3

if test x$WITH_TESTS != x ; then
	echo "Copying tests and test data to $PACKAGE_DIR ..."
	#cp $BUILD_DIR/libs/pbd/run-tests.exe $PACKAGE_BIN_DIR/pbd-run-tests.exe
	#cp -r $BASE/libs/pbd/test $PACKAGE_DIR/pbd_testdata
fi
