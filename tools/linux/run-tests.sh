#!/bin/sh

# --log_level=test_suite, all, message, warning, nothing, error

# be able to source the env script no matter the pwd
RUN_TESTS_SCRIPT_PATH=$( cd $(dirname $0) ; pwd -P )
. "$RUN_TESTS_SCRIPT_PATH/env.sh"

LOG_LEVEL='all' # error is the default

if [ -n "$1" ] && [ "$1" != "all" ]
then
	TESTS="test_*$1*"
else
	# run all tests
	TESTS="test_*"
fi

for file in `find $BUILD_DIR -name "$TESTS" -type f -perm /u+x`;
do
	echo "Running test....$file"
	$file --log_level="$LOG_LEVEL" "$@";
done;
