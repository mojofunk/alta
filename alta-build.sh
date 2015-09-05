#!/bin/bash

# script assumes it is placed in the top level of the source directory

ALTA_BRANCH=`git rev-parse --abbrev-ref HEAD`

STATIC="--enable-static"
TESTS="--with-tests"
SINGLE_TESTS="--with-single-tests"
GUI="--with-gtkmm-ui"
AMALGAMATE="--enable-amalgamation"
OPTIMIZE="--optimize"

declare -A config
config["debug"]=""
config["debug-tests"]="$TESTS"
config["debug-tests-amalgamated"]="$SINGLE_TESTS $AMALGAMATE"
config["debug-tests-static"]="$TESTS $STATIC"
config["debug-tests-static-amalgamated"]="$TESTS $STATIC $AMALGAMATE"
config["debug-tests-single"]="$SINGLE_TESTS"
config["debug-tests-single-static"]="$SINGLE_TESTS $STATIC"
config["debug-tests-single-amalgamated"]="$SINGLE_TESTS $AMALGAMATE"
config["debug-amalgamated"]="$AMALGAMATE"
config["debug-amalgamated-static"]="$TESTS $AMALGAMATE $STATIC"
config["debug-gtkmm-ui"]="$GUI"
config["debug-gtkmm-ui-static"]="$GUI $STATIC"
config["debug-gtkmm-ui-amalgamated"]="$AMALGAMATE $GUI"
config["release"]="$STATIC $AMALGAMATE $OPTIMIZE"

function print_usage ()
{
	echo "usage: alta-build.sh [-l] [-v] <command> <config>"
	echo " -l list configs"
	echo " -v verbose"
	echo "The commands are:"
	echo "    configure"
	echo "    build"
	echo "    install"
	echo "    clean"
}

function print_configs ()
{
	echo "Possible build configurations: "
	for conf in "${!config[@]}"
	do
		echo "$conf"
	done
}

OPTIND=1
while getopts "h?vl" opt; do
	case "$opt" in
		h)
			print_usage
			exit 0
			;;
		v)
			ALTA_BUILD_VERBOSE=1
			set -x
			;;
		l)
			print_configs
			exit 0
			;;
	esac
done
shift "$((OPTIND-1))"

if [ -z "$1" ] || [ -z "$2" ]; then
	print_usage
	echo "You must specify command and build config"
	print_configs
	exit 1
fi

ALTA_BUILD_COMMAND="$1"
ALTA_BUILD_CONFIG="$2"
ALTA_BUILD_SCRIPT_PATH=$( cd $(dirname $0) ; pwd -P )
ALTA_SRC_DIR=$ALTA_BUILD_SCRIPT_PATH
HOME_DIR_PATH=$( cd ~/ ; pwd -P )

ALTA_BUILD_ROOT=${ALTA_BUILD_ROOT:=$HOME_DIR_PATH/"alta-build"}

CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
CONFIG_WAF_BUILD_DIR="$CONFIG_BUILD_DIR/build"

mkdir -p $ALTA_BUILD_ROOT || exit 1

function sync ()
{
	rsync -av $ALTA_SRC_DIR/ $CONFIG_BUILD_DIR || exit 1
}

function configure ()
{
	sync
	cd $CONFIG_BUILD_DIR || exit 1
	./waf configure ${config["$ALTA_BUILD_CONFIG"]} "$@"
}

function build ()
{
	sync
	cd $CONFIG_BUILD_DIR || exit 1
	./waf "$@"
}

function install ()
{
	sync
	cd $CONFIG_BUILD_DIR || exit 1
	./waf install "$@"
}

function clean ()
{
	echo "Removing directory $CONFIG_BUILD_DIR"
	cd $CONFIG_BUILD_DIR || exit 1
	rm -rf $CONFIG_WAF_BUILD_DIR
}

if [ "${config["$ALTA_BUILD_CONFIG"]+isset}" ]; then
	echo "Using configuration: $ALTA_BUILD_CONFIG"
else
	echo "No such configuration: $ALTA_BUILD_CONFIG"
	print_configs
	exit 1
fi;

# remove the command and config parameters
shift 2

case $ALTA_BUILD_COMMAND in
	configure)
		configure $@ || exit 1
		;;
	build)
		build $@ || exit 1
		;;
	install)
		install  $@ || exit 1
		;;
	clean)
		clean || exit 1
		;;
	*)
		print_usage
		exit 1
		;;
esac
