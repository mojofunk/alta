#! /usr/bin/env python
# encoding: utf-8
# Tim Mayberry, 2008

import os
import subprocess
import sys
import re

from waflib import Logs

# TODO use version from git tag/describe
MAJOR_VERSION = '0'
MINOR_VERSION = '1'
MICRO_VERSION = '0'
# these are required by waf for waf dist
VERSION = MAJOR_VERSION + '.' + MINOR_VERSION + '.' + MICRO_VERSION
APPNAME = 'Alta'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'waf-build'


def options(opt):
    # options provided by the modules

    opt.load('gnu_dirs')

    opt.add_option(
        '--toolset',
        type='string',
        dest='toolset',
        default='auto',
        help='Compiler and Toolset options: auto, gcc, clang, mingw, msvc')
    opt.add_option(
        '--target-system',
        type='string',
        dest='target_system',
        default='auto',
        help='Target system options for cross compiling: auto, linux, windows')
    opt.add_option(
        '--enable-system-libs',
        action='store_true',
        default=False,
        help='Use system versions of library dependencies')
    opt.add_option(
        '--with-tests',
        action='store_true',
        default=False,
        help='Enable Testsuite')
    opt.add_option(
        '--with-single-tests',
        action='store_true',
        default=False,
        help='Build each test as single executable')
    opt.add_option(
        '--enable-shared',
        action='store_true',
        default=False,
        help='Build shared libraries')
    opt.add_option(
        '--enable-static',
        action='store_true',
        default=False,
        help='Build static libraries')
    opt.add_option(
        '--optimize',
        action='store_true',
        default=False,
        help='Enable Optimization')
    opt.add_option(
        '--disable-debug-logging',
        action='store_false',
        default=False,
        help='Disable logging of debug messages')
    opt.add_option(
        '--with-gtkmm-ui',
        action='store_true',
        default=False,
        help='Build Gtkmm based GUI')
    opt.add_option(
        '--run-tests',
        action='store_true',
        default=False,
        help='Run testsuite after build')


def set_config_env_from_options(conf):
    # Use same order as above and use all capitals to indicate they are const
    conf.env.TOOLSET = conf.options.toolset
    conf.env.TARGET_SYSTEM = conf.options.target_system
    conf.env.ENABLE_SYSTEM_LIBS = conf.options.enable_system_libs
    conf.env.BUILD_TESTS = conf.options.with_tests
    conf.env.BUILD_SINGLE_TESTS = conf.options.with_single_tests
    conf.env.ENABLE_SHARED = conf.options.enable_shared
    conf.env.ENABLE_STATIC = conf.options.enable_static
    conf.env.DEBUG_LOGGING = not conf.options.disable_debug_logging
    conf.env.WITH_GTKMM_UI = conf.options.with_gtkmm_ui
    conf.env.RUN_TESTS = conf.options.run_tests


def check_required_deps(conf, deps):
    for pkg, version in deps.items():
        conf.check_cfg(package=pkg, atleast_version=version, mandatory=1)
        conf.check_cfg(package=pkg, args='--cflags --libs')


def set_gcc_compiler_flags(conf):
    cxx_flags = []
    conf.check_cxx(cxxflags=["-std=c++11"])
    cxx_flags.append('-std=c++11')

    conf.env.append_value('CXXFLAGS', cxx_flags)

    if conf.options.optimize:
        conf.env.append_value('CFLAGS', '-DNDEBUG')
        conf.env.append_value('CXXFLAGS', '-DNDEBUG')
    else:
        conf.env.append_value('CFLAGS', '-g')
        conf.env.append_value('CXXFLAGS', '-g')

    if not conf.options.disable_debug_logging:
        conf.env.append_value('CFLAGS', '-DMOJO_ENABLE_DEBUG_LOGGING')
        conf.env.append_value('CXXFLAGS', '-DMOJO_ENABLE_DEBUG_LOGGING')


def set_msvc_compiler_flags(conf):
    # much more to do here
    cxx_flags = []
    # enable exceptions
    cxx_flags.append('/EHsc')
    conf.env.append_value('CXXFLAGS', cxx_flags)


def display_config(conf):
    Logs.info('C compiler flags         : %s' % conf.env.CFLAGS)
    Logs.info('C++ compiler flags       : %s' % conf.env.CXXFLAGS)
    Logs.info('Enable shared            : %s' % conf.env.ENABLE_SHARED)
    Logs.info('Enable static            : %s' % conf.env.ENABLE_STATIC)
    Logs.info('Build tests              : %s' % conf.env.BUILD_TESTS)
    Logs.info('Build single tests       : %s' % conf.env.BUILD_SINGLE_TESTS)
    Logs.info('Enable debug logging     : %s' % conf.env.DEBUG_LOGGING)
    Logs.info('Enable System libraries  : %s' % conf.env.ENABLE_SYSTEM_LIBS)

def set_toolset_from_env(conf):
    conf.load('gcc')
    conf.load('g++')
    conf.env.TOOLSET_GCC = True
    conf.env.TOOLSET_CLANG = False
    conf.env.TOOLSET_MSVC = False


def set_toolset(conf):
    if conf.env.TOOLSET == 'gcc':
        conf.load('gcc')
        conf.load('g++')
        conf.env.TOOLSET_GCC = True
        conf.env.TOOLSET_CLANG = False
        conf.env.TOOLSET_MSVC = False
    elif conf.env.TOOLSET == 'clang':
        conf.load('clang')
        conf.load('clang++')
        conf.env.TOOLSET_GCC = False
        conf.env.TOOLSET_CLANG = True
        conf.env.TOOLSET_MSVC = False
    elif conf.env.TOOLSET == 'msvc':
        conf.load('msvc')
        conf.env.TOOLSET_GCC = False
        conf.env.TOOLSET_CLANG = False
        conf.env.TOOLSET_MSVC = True
    elif conf.env.TOOLSET == 'auto':
        set_toolset_from_env(conf)
    else:
        print ("Unsupported Toolset option")
        sys.exit(1)


def set_target_system_from_build_system(conf):
    if re.search('linux', sys.platform) != None:
        conf.env.TARGET_LINUX = True
        conf.env.TARGET_WINDOWS = False
    else:
        conf.env.TARGET_WINDOWS = True
        conf.env.TARGET_LINUX = False


def set_target_system(conf):
    if conf.env.TARGET_SYSTEM == 'auto':
        set_target_system_from_build_system(conf)
        return
    if conf.env.TARGET_SYSTEM == 'windows':
        conf.env.TARGET_WINDOWS = True
        conf.env.TARGET_LINUX = False
    elif conf.env.TARGET_SYSTEM == 'linux':
        conf.env.TARGET_LINUX = True
        conf.env.TARGET_WINDOWS = False
    else:
        print ("Unsupported Target System option")
        sys.exit(1)


def check_system_libs(conf):

    common_deps = \
        {
            'glib-2.0': '2.10.1',
            'gmodule-2.0': '2.10.1',
            'gthread-2.0': '2.10.1',
            'glibmm-2.4': '2.8.1',
            'sndfile': '1.0.20'
        }

    check_required_deps(conf, common_deps)

    if not conf.check(
            lib='boost_filesystem-mt', uselib_store='BOOST_FILESYSTEM', mandatory=False):
        conf.check(lib='boost_filesystem', uselib_store='BOOST_FILESYSTEM')

    if not conf.check(
            lib='boost_system-mt', uselib_store='BOOST_SYSTEM', mandatory=False):
        conf.check(lib='boost_system', uselib_store='BOOST_SYSTEM')


def configure(conf):

    set_config_env_from_options(conf)

    set_toolset(conf)

    conf.load('gnu_dirs')

    set_target_system(conf)

    if conf.env.TOOLSET_GCC:
        set_gcc_compiler_flags(conf)
    if conf.env.TOOLSET_CLANG:
        set_gcc_compiler_flags(conf)
    elif conf.env.TOOLSET_MSVC:
        print('Using MSVC Compile flags')
        set_msvc_compiler_flags(conf)

    if conf.env.ENABLE_SYSTEM_LIBS:
        check_system_libs(conf)

    if conf.env.BUILD_SINGLE_TESTS:
        conf.env.BUILD_TESTS = True

    if conf.env.BUILD_TESTS:
        if not conf.check(lib='boost_unit_test_framework-mt',
                          uselib_store='BOOST_UNIT_TEST_FRAMEWORK', mandatory=False):
            conf.check(
                lib='boost_unit_test_framework',
                uselib_store='BOOST_UNIT_TEST_FRAMEWORK')

    if not conf.env.ENABLE_SHARED and not conf.env.ENABLE_STATIC:
        # needed because of the weird waf options design
        conf.env.ENABLE_SHARED = True

    defines = ['HAVE_CONFIG_H', '_REENTRANT',
               '_LARGEFILE_SOURCE', '_LARGEFILE64_SOURCE']

    if conf.env.BUILD_TESTS:
        defines += ['BOOST_TEST_DYN_LINK']

    conf.env.append_value('CCDEFINES', defines)
    conf.env.append_value('CXXDEFINES', defines)

    conf.recurse('src')

    display_config(conf)


def build(bld):
    # process subfolders from here

    bld.env.PROGRAM_NAME = APPNAME
    bld.env.PROGRAM_EXE_NAME = 'alta' + MAJOR_VERSION
    bld.env.PROGRAM_DIR_NAME = bld.env.PROGRAM_EXE_NAME
    # redefine LIBDIR so all libs get installed automatically
    bld.env.LIBDIR = "%s/%s" % (bld.env.LIBDIR, bld.env.PROGRAM_DIR_NAME)

    bld.recurse('src')

    if bld.env['RUN_TESTS']:
        bld.add_post_fun(test)


def test(bld):
    subprocess.call("tools/linux/run-tests.sh")
