#!/bin/sh

# --log_level=test_suite

. gmojo_env.sh

test_dirs=(
	"rtg"
	"cformat"
	"ark"
	"libgleam"
	)

for dir in ${test_dirs[*]};
do
	echo "Running test cases for $dir"

	TEST_DIR="$BUILD_DIR/$dir/tests/"
	for file in `find $TEST_DIR -type f -perm /u+x`;
	do
		$file "$@";
	done;
done
