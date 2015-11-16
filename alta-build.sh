#!/bin/bash

# script assumes it is placed in the top level of the source directory

ALTA_BRANCH=`git rev-parse --abbrev-ref HEAD`

STATIC="--enable-static"
TESTS="--with-tests"
SINGLE_TESTS="--with-single-tests"
RUN_TESTS="--run-tests"
GUI="--with-gtkmm-ui"
OPTIMIZE="--optimize"
DISABLE_DEBUG_LOGGING="--disable-debug-logging"
MSVC_TOOLSET="--toolset=msvc"
CLANG_TOOLSET="--toolset=clang"
BACKTRACE=""
PROFILE=""

DEBUG="$TESTS $SINGLE_TESTS"
RELEASE="$OPTIMIZE $DISABLE_DEBUG_LOGGING"

declare -A gcc_config
gcc_config["gcc-debug"]="$DEBUG"
gcc_config["gcc-debug-static"]="$DEBUG $STATIC"
gcc_config["gcc-release"]="$RELEASE"
gcc_config["gcc-release-static"]="$RELEASE $STATIC"

declare -A clang_config
clang_config["clang-debug"]="$CLANG_TOOLSET $DEBUG"
clang_config["clang-debug-static"]="$CLANG_TOOLSET $DEBUG $STATIC"
clang_config["clang-release"]="$CLANG_TOOLSET $RELEASE"
clang_config["clang-release-static"]="$CLANG_TOOLSET $RELEASE $STATIC"

declare -A msvc_config
msvc_config["msvc-debug"]="$MSVC_TOOLKIT $DEBUG"
msvc_config["msvc-debug-static"]="$MSVC_TOOLKIT $DEBUG $STATIC"
msvc_config["msvc-release"]="$MSVC_TOOLKIT $RELEASE"
msvc_config["msvc-release-static"]="$MSVC_TOOLKIT $RELEASE $STATIC"

declare -A config

for key in "${!gcc_config[@]}"
	do
  config["$key"]="${gcc_config["$key"]}"
  # or: config+=( ["$key"]="${OTHERARRAY["$key"]}" )
done

UNAME=`uname`

if [ "$UNAME" == 'Linux' ]; then
	for key in "${!clang_config[@]}"
		do
		config["$key"]="${clang_config["$key"]}"
		# or: config+=( ["$key"]="${OTHERARRAY["$key"]}" )
	done
else # Windows
	for key in "${!msvc_config[@]}"
		do
		config["$key"]="${msvc_config["$key"]}"
		# or: config+=( ["$key"]="${OTHERARRAY["$key"]}" )
	done
fi

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
CONFIG_WAF_BUILD_DIR="$CONFIG_BUILD_DIR/waf-build"

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
	rsync -av --delete --exclude /waf-build --exclude /.lock* --exclude /.waf-* $ALTA_SRC_DIR/ $CONFIG_BUILD_DIR || exit 1
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
			CONFIG_WAF_BUILD_DIR="$CONFIG_BUILD_DIR/waf-build"
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
