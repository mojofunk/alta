#!/bin/sh

# --log_level=test_suite, all, message, warning, nothing, error

. ./env.sh

LOG_LEVEL='all' # error is the default

for file in `find $BUILD_DIR -name "mojo-tests" -type f -perm /u+x`;
do
	echo "Running test....$file"
	G_DEBUG=gc-friendly G_SLICE=always-malloc valgrind -v --track-fds=yes \
	--leak-check=full --log-file=$file.%p $file --log_level="$LOG_LEVEL" "$@";
done;
