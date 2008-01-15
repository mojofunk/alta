#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

for file in `find $BUILD_DIR -name 'test_*' -type f -perm /u+x`;
do
	echo "Running test....$file"
	$file "$@";
done;
