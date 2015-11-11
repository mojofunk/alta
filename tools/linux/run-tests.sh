#!/bin/sh

# --log_level=test_suite, all, message, warning, nothing, error

# be able to source the env script no matter the pwd
RUN_TESTS_SCRIPT_PATH=$( cd $(dirname $0) ; pwd -P )
. "$RUN_TESTS_SCRIPT_PATH/env.sh"

LOG_LEVEL='all' # error is the default


OPTION=""
if [ "$1" == "--debug" -o "$1" == "--valgrind" -o "$1" == "--massif" ]; then
	OPTION=$1
	echo "Using option $OPTION"
	shift 1
fi


if [ -n "$1" ] && [ "$1" != "all" ]
then
	TESTS="test_*$1*"
else
	# run all tests
	TESTS="test_*"
fi

echo "Matching tests $TESTS"

for file in `find $BUILD_DIR -name "$TESTS" -type f -perm /u+x`;
do
	FILE_NAME=`basename $file`
	if [ "$OPTION" == "--debug" ]; then
		if [ $TESTS == "test_*" ]; then
			echo "--debug option not supported for all tests, run individually"
			exit 0
		fi
		gdb --args $file # --log_level="$LOG_LEVEL" "$@";
	elif [ "$OPTION" == "--valgrind" ]; then
		MEMCHECK_OPTIONS="--leak-check=full --show-leak-kinds=all"
		valgrind $MEMCHECK_OPTIONS $file
	elif [ "$OPTION" == "--massif" ]; then
		MASSIF_OPTIONS="--time-unit=ms --massif-out-file=massif.out.$FILE_NAME"
		valgrind --tool=massif $MASSIF_OPTIONS $file
	else
		echo "Running test....$file"
		$file --log_level="$LOG_LEVEL" "$@";
	fi
done;
