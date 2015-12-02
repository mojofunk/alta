#!/bin/sh

. ./env.sh

OPTION=""
if [ "$1" == "--debug" -o "$1" == "--valgrind" -o "$1" == "--massif" ]; then
	OPTION=$1
	echo "Using option $OPTION"
	shift 1
fi

cd $BASE || exit 1

if [ "$OPTION" == "--debug" ]; then
	gdb --args $EXECUTABLE
elif [ "$OPTION" == "--valgrind" ]; then
	MEMCHECK_OPTIONS="--leak-check=full --show-leak-kinds=all"
	valgrind $MEMCHECK_OPTIONS $EXECUTABLE
elif [ "$OPTION" == "--massif" ]; then
	MASSIF_OPTIONS="--time-unit=ms --massif-out-file=massif.out.$EXECUTABLE"
	valgrind --tool=massif $MASSIF_OPTIONS $EXECUTABLE
else
	exec $EXECUTABLE "$@"
fi
