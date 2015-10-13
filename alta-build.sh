#!/bin/bash

# script assumes it is placed in the top level of the source directory

ALTA_BRANCH=`git rev-parse --abbrev-ref HEAD`

STATIC="--enable-static"
TESTS="--with-tests"
SINGLE_TESTS="--with-single-tests"
RUN_TESTS="--run-tests"
GUI="--with-gtkmm-ui"
AMALGAMATE="--enable-amalgamation"
OPTIMIZE="--optimize"
DISABLE_DEBUG_LOGGING="--disable-debug-logging"

declare -A config
config["debug"]=""
config["debug-tests"]="$TESTS"
config["debug-tests-run-tests"]="$TESTS $RUN_TESTS"
config["debug-tests-amalgamated"]="$SINGLE_TESTS $AMALGAMATE"
config["debug-tests-static"]="$TESTS $STATIC"
config["debug-tests-static-amalgamated"]="$TESTS $STATIC $AMALGAMATE"
config["debug-tests-single"]="$SINGLE_TESTS"
config["debug-tests-single-static"]="$SINGLE_TESTS $STATIC"
config["debug-tests-single-amalgamated"]="$SINGLE_TESTS $AMALGAMATE"
config["debug-amalgamated"]="$AMALGAMATE"
config["debug-amalgamated-static"]="$TESTS $AMALGAMATE $STATIC"
#config["debug-gtkmm-ui"]="$GUI"
#config["debug-gtkmm-ui-static"]="$GUI $STATIC"
#config["debug-gtkmm-ui-amalgamated"]="$AMALGAMATE $GUI"
config["release"]="$STATIC $AMALGAMATE $OPTIMIZE $DISABLE_DEBUG_LOGGING"
config["release-tests"]="$AMALGAMATE $OPTIMIZE $TESTS"
config["release-tests-single"]="$AMALGAMATE $OPTIMIZE $SINGLE_TESTS"

function print_usage ()
{
	echo "Usage for single configuration:"
	echo ""
	echo "alta-build.sh [-l] [-v] <command> <config>"
	echo ""
	echo "Usage for all configurations:"
	echo ""
	echo "alta-build.sh [-l] [-v] -a <command>"
	echo ""
	echo "The commands are: configure, build, install, clean"
	echo " -l list configs"
	echo " -v verbose"
	echo " -h help"
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
while getopts "h?vla" opt; do
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
		a)
			BUILD_ALL_CONFIGS=1
			;;
	esac
done
shift "$((OPTIND-1))"

HOME_DIR_PATH=$( cd ~/ ; pwd -P )
ALTA_BUILD_COMMAND="$1"
ALTA_BUILD_SCRIPT_PATH=$( cd $(dirname $0) ; pwd -P )
ALTA_BUILD_ROOT=${ALTA_BUILD_ROOT:=$HOME_DIR_PATH/"alta-build"}
ALTA_SRC_DIR=$ALTA_BUILD_SCRIPT_PATH

ALTA_BUILD_CONFIG="$2"
CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
CONFIG_WAF_BUILD_DIR="$CONFIG_BUILD_DIR/build"

if [ -z ${BUILD_ALL_CONFIGS+x} ]; then
	if [ -z "$1" ] || [ -z "$2" ]; then
		print_usage
		echo "You must specify command and build config"
		print_configs
		exit 1
	fi
	if [ "${config["$ALTA_BUILD_CONFIG"]+isset}" ]; then
		echo "Using configuration: $ALTA_BUILD_CONFIG"
	else
		echo "No such configuration: $ALTA_BUILD_CONFIG"
		print_configs
		exit 1
	fi;

	# remove the command and config parameters
	shift 2

else
	if [ -z "$1" ]; then
		print_usage
		echo "You must specify command and build config"
		print_configs
		exit 1
	fi

	echo "Using $1 command for all build configurations"

	# remove the command parameter
	shift 1
fi

mkdir -p $ALTA_BUILD_ROOT || exit 1

function sync ()
{
	rsync -av --delete --exclude /build --exclude /.lock* --exclude /.waf-* $ALTA_SRC_DIR/ $CONFIG_BUILD_DIR || exit 1
}

function configure ()
{
	if [ -z ${BUILD_ALL_CONFIGS+x} ]; then
		sync
		cd $CONFIG_BUILD_DIR || exit 1
		./waf configure ${config["$ALTA_BUILD_CONFIG"]} "$@" || exit 1
	else
		for conf in "${!config[@]}"
		do
			ALTA_BUILD_CONFIG="$conf"
			CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
			sync
			cd $CONFIG_BUILD_DIR || exit 1
			./waf configure ${config["$ALTA_BUILD_CONFIG"]} "$@" || exit 1
		done
	fi
}

function build ()
{
	if [ -z ${BUILD_ALL_CONFIGS+x} ]; then
		sync
		cd $CONFIG_BUILD_DIR || exit 1
		./waf "$@" || exit 1
	else
		for conf in "${!config[@]}"
		do
			ALTA_BUILD_CONFIG="$conf"
			CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
			sync
			cd $CONFIG_BUILD_DIR || exit 1
			./waf "$@" || exit 1
		done
	fi
}

function install ()
{
	cd $CONFIG_BUILD_DIR || exit 1
	./waf install "$@"
}

function test ()
{
	if [ -z ${BUILD_ALL_CONFIGS+x} ]; then
		echo "Testing in build directory $CONFIG_BUILD_DIR"
		cd $CONFIG_BUILD_DIR || exit 1
		./waf test "$@"
	else
		for conf in "${!config[@]}"
		do
			ALTA_BUILD_CONFIG="$conf"
			CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
			echo "Testing in build directory $CONFIG_BUILD_DIR"
			cd $CONFIG_BUILD_DIR || exit 1
			./tools/linux/run-tests.sh all "$@"
		done
	fi
	cd $CONFIG_BUILD_DIR || exit 1
}

function clean ()
{
	if [ -z ${BUILD_ALL_CONFIGS+x} ]; then
		echo "Removing directory $CONFIG_BUILD_DIR"
		cd $CONFIG_BUILD_DIR || exit 1
		rm -rf $CONFIG_WAF_BUILD_DIR
	else
		for conf in "${!config[@]}"
		do
			ALTA_BUILD_CONFIG="$conf"
			CONFIG_BUILD_DIR="$ALTA_BUILD_ROOT/$ALTA_BRANCH-$ALTA_BUILD_CONFIG"
			CONFIG_WAF_BUILD_DIR="$CONFIG_BUILD_DIR/build"
			echo "Removing directory $CONFIG_WAF_BUILD_DIR"
			cd $CONFIG_BUILD_DIR || exit 1
			rm -rf $CONFIG_WAF_BUILD_DIR
		done
	fi
}

case $ALTA_BUILD_COMMAND in
	configure)
		configure $@ || exit 1
		;;
	build)
		build $@ || exit 1
		;;
	install)
		install $@ || exit 1
		;;
	test)
		test $@ || exit 1
		;;
	clean)
		clean || exit 1
		;;
	*)
		print_usage
		exit 1
		;;
esac
