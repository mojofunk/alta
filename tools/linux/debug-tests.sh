#!/bin/sh

# --log_level=test_suite, all, message, warning, nothing

. ./env.sh

TESTS='test_*'

if [ -n "$1" ] && [ "$1" != "all" ]
then
	TESTS="test_*$1*"
fi

for file in `find $BUILD_DIR -name "$TESTS" -type f -perm /u+x`;
do
	echo "Running test....$file"
	gdb $file "$@";
done;
