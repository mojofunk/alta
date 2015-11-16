#! /usr/bin/env python
# encoding: utf-8
# Tim Mayberry, 2008

import os
import subprocess
import sys
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
        default='gcc',
        help='Compiler and Toolset options: gcc(default), clang, msvc')
    opt.add_option(
        '--target-platform',
        type='string',
        dest='target_platform',
        default='auto',
        help='Target platform options: auto, windows')
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
        '--run-tests',
        action='store_true',
        default=False,
        help='Run testsuite after build')
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
        '--enable-shared',
        action='store_true',
        default=True,
        help='Build shared libraries')
    opt.add_option(
        '--enable-static',
        action='store_true',
        default=False,
        help='Build static libraries')
    opt.add_option(
        '--enable-amalgamation',
        action='store_true',
        default=False,
        help='Amalgamate files when building libraries')
    opt.add_option(
        '--with-gtkmm-ui',
        action='store_true',
        default=False,
        help='Build Gtkmm based GUI')


def _check_required_deps(conf, deps):
    for pkg, version in deps.items():
        conf.check_cfg(package=pkg, atleast_version=version, mandatory=1)
        conf.check_cfg(package=pkg, args='--cflags --libs')


def set_compiler_flags(conf):
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


def display_config(conf):
    Logs.info('C++ compiler flags: %s' % conf.env.CXXFLAGS)
    Logs.info('Enable shared: %s' % conf.env.ENABLE_SHARED)
    Logs.info('Enable static: %s' % conf.env.ENABLE_STATIC)
    Logs.info('Enable amalgamation: %s' % conf.env.ENABLE_AMALGAMATION)
    Logs.info('Build tests: %s' % conf.env.BUILD_TESTS)
    Logs.info('Build single tests: %s' % conf.env.BUILD_SINGLE_TESTS)
    Logs.info('Enable debug logging: %s' % conf.env.DEBUG_LOGGING)


def configure(conf):

    conf.env.TOOLSET = conf.options.toolset

    if conf.env.TOOLSET == 'gcc':
        conf.load('gcc')
        conf.load('g++')
    elif conf.env.TOOLSET == 'clang':
        conf.load('clang')
        conf.load('clang++')
    elif conf.env.TOOLSET == 'msvc':
        conf.load('msvc')
    else:
        print ("Unsupported Toolset option")
        sys.exit(1)

    conf.load('gnu_dirs')

    conf.env.TARGET_PLATFORM = conf.options.target_platform

    set_compiler_flags(conf)

    deps = \
        {
            'glib-2.0': '2.10.1',
            'gmodule-2.0': '2.10.1',
            'gthread-2.0': '2.10.1',
            'glibmm-2.4': '2.8.1',
            'sndfile': '1.0.20'
        }

    _check_required_deps(conf, deps)

    conf.env.BUILD_TESTS = conf.options.with_tests
    conf.env.BUILD_SINGLE_TESTS = conf.options.with_single_tests
    conf.env.RUN_TESTS = conf.options.run_tests

    if conf.env.BUILD_SINGLE_TESTS:
        conf.env.BUILD_TESTS = True

    if conf.env.BUILD_TESTS:
        if not conf.check(lib='boost_unit_test_framework-mt',
                          uselib_store='BOOST_UNIT_TEST_FRAMEWORK', mandatory=False):
            conf.check(
                lib='boost_unit_test_framework',
                uselib_store='BOOST_UNIT_TEST_FRAMEWORK')

    conf.env.ENABLE_SHARED = conf.options.enable_shared
    conf.env.ENABLE_STATIC = conf.options.enable_static

    conf.env.ENABLE_AMALGAMATION = conf.options.enable_amalgamation

    conf.env.DEBUG_LOGGING = not conf.options.disable_debug_logging

    conf.env.WITH_GTKMM_UI = conf.options.with_gtkmm_ui

    if not conf.check(
            lib='boost_filesystem-mt', uselib_store='BOOST_FILESYSTEM', mandatory=False):
        conf.check(lib='boost_filesystem', uselib_store='BOOST_FILESYSTEM')

    if not conf.check(
            lib='boost_system-mt', uselib_store='BOOST_SYSTEM', mandatory=False):
        conf.check(lib='boost_system', uselib_store='BOOST_SYSTEM')

    if conf.env.TARGET_PLATFORM == 'windows':
        conf.check(lib='winmm', uselib_store='WINMM')

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
