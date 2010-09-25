#!/bin/sh

# --log_level=test_suite, all, message, warning, nothing

. build/default/gmojo_env.sh

TESTS='test_*'

if [ -n "$1" ] && [ "$1" != "all" ]
then
	TESTS="test_*$1*"
fi

for file in `find $BUILD_DIR -name "$TESTS" -type f -perm /u+x`;
do
	echo "Running test....$file"
	G_DEBUG=gc-friendly G_SLICE=always-malloc valgrind -v --track-fds=yes --leak-check=full --log-file=$file.%p $file "$@";
done;
