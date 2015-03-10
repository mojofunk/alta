#!/bin/bash

. ./wine-env.sh

if [ "$1" == "--list" ]; then
	TESTS='test_*'
	for test_program in `find  -name "$TESTS" -type f -perm /u+x`;
	do
		echo "$test_program"
	done
	exit 0
fi

if [ "$1" == "--single" ]; then
    TESTS="test_*$2*"
else
    TESTS='test_*'
fi

for test_program in `find . -name "$TESTS" -type f -perm /u+x`;
do
    echo "Running $test_program..."
    wine "$test_program"
done

