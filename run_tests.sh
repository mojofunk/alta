#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

for dir in "rtg" "cformat" "ark" "libgleam";
do
	echo "Running test cases for $dir"

	TEST_DIR="$BUILD_DIR/$dir/tests/"
	for file in `find $TEST_DIR -type f -perm /u+x`;
	do
		$file "$@";
	done;
done
