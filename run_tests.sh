#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

for file in `find $BUILD_DIR -name 'test_*' -type f -perm /u+x`;
do
	echo "Running test....$file"
	valgrind -v --track-fds=yes --leak-check=full --log-file=$file $file "$@";
done;
