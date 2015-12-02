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


def compiler_is_clang(conf):
    clang_check_source='''
#ifndef __clang__
#error
#endif
int main() { return 0; }'''

    return conf.check_cxx(fragment = clang_check_source,
            features = 'cxx',
            mandatory = False,
            execute = False,
            msg = 'Checking for clang compiler')


def compiler_is_msvc(conf):
    msvc_check_source='''
#ifndef _MSC_VER
#error
#endif
int main() { return 0; }'''

    return conf.check_cxx(fragment = msvc_check_source,
            features = 'cxx',
            mandatory = False,
            execute = False,
            msg = 'Checking for msvc compiler')

def compiler_is_mingw(conf):
    mingw_check_source='''
#ifndef __MINGW32__
#error
#endif
int main() { return 0; }'''

    return conf.check_cxx(fragment = mingw_check_source,
            features = 'cxx',
            mandatory = False,
            execute = False,
            msg = 'Checking for mingw compiler')


def options(opt):
    # options provided by the modules
    opt.load('compiler_c')
    opt.load('compiler_cxx')

    opt.load('gnu_dirs')

    opt.add_option(
        '--toolset',
        type='string',
        dest='toolset',
        default='auto',
        help='Compiler and Toolset options: auto, gcc, clang, mingw, msvc')
    opt.add_option(
        '--with-tests',
        action='store_true',
        default=False,
        help='Enable Testsuite')
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
        '--with-juce',
        action='store_true',
        default=False,
        help='Build JUCE library')
    opt.add_option(
        '--run-tests',
        action='store_true',
        default=False,
        help='Run testsuite after build')


def set_config_env_from_options(conf):
    # Use same order as above and use all capitals to indicate they are const
    conf.env.TOOLSET = conf.options.toolset
    conf.env.WITH_TESTS = conf.options.with_tests
    conf.env.ENABLE_SHARED = conf.options.enable_shared
    conf.env.ENABLE_STATIC = conf.options.enable_static
    conf.env.DEBUG_LOGGING = not conf.options.disable_debug_logging
    conf.env.WITH_GTKMM_UI = conf.options.with_gtkmm_ui
    conf.env.WITH_JUCE = conf.options.with_juce
    conf.env.RUN_TESTS = conf.options.run_tests


def display_config(conf):
    Logs.info('Target System            : %s' % conf.env.TARGET_SYSTEM)
    Logs.info('Toolset                  : %s' % conf.env.TOOLSET)
    Logs.info('C compiler flags         : %s' % conf.env.CFLAGS)
    Logs.info('C++ compiler flags       : %s' % conf.env.CXXFLAGS)
    Logs.info('Linker flags             : %s' % conf.env.LINKFLAGS)
    Logs.info('Enable shared            : %s' % conf.env.ENABLE_SHARED)
    Logs.info('Enable static            : %s' % conf.env.ENABLE_STATIC)
    Logs.info('Build tests              : %s' % conf.env.WITH_TESTS)
    Logs.info('Enable debug logging     : %s' % conf.env.DEBUG_LOGGING)
    Logs.info('Enable System libraries  : %s' % conf.env.ENABLE_SYSTEM_LIBS)
    Logs.info('Enable Gtkmm UI          : %s' % conf.env.WITH_GTKMM_UI)
    Logs.info('Enable JUCE library      : %s' % conf.env.WITH_JUCE)


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
    cxx_debug_flags = ['/DEBUG', '/Od', '/MD', '/Zi', '/EHsc']
    link_flags = ['/DEBUG']
    # enable exceptions
    conf.env.append_value('CXXFLAGS', cxx_debug_flags)
    conf.env.append_value('LINKFLAGS', link_flags)


def set_toolset_from_compiler_check(conf):
    print('Setting Toolset from compiler check')
    if compiler_is_clang(conf):
        set_toolset_clang(conf)
    elif compiler_is_msvc(conf):
        set_toolset_msvc(conf)
    else:
        set_toolset_gcc(conf)


def set_toolset_gcc(conf):
    conf.env.TOOLSET = 'gcc'
    conf.env.TOOLSET_GCC = True
    conf.env.TOOLSET_CLANG = False
    conf.env.TOOLSET_MSVC = False


def set_toolset_clang(conf):
    conf.env.TOOLSET = 'clang'
    conf.env.TOOLSET_GCC = False
    conf.env.TOOLSET_CLANG = True
    conf.env.TOOLSET_MSVC = False


def set_toolset_msvc(conf):
    conf.env.TOOLSET = 'msvc'
    conf.env.TOOLSET_GCC = False
    conf.env.TOOLSET_CLANG = False
    conf.env.TOOLSET_MSVC = True


def check_toolset_clang(conf):
    if not compiler_is_clang(conf):
        print ("Clang compiler not detected")
        sys.exit(1)


def check_toolset_msvc(conf):
    if not compiler_is_msvc(conf):
        print ("MSVC compiler not detected")
        sys.exit(1)


def check_toolset_mingw(conf):
    if not compiler_is_mingw(conf):
        print ("MingW compiler/toolset not detected")
        sys.exit(1)


def load_toolset(conf):
    if conf.env.TOOLSET == 'gcc':
        conf.load('gcc')
        conf.load('g++')
        set_toolset_gcc(conf)
    elif conf.env.TOOLSET == 'clang':
        conf.load('clang')
        conf.load('clang++')
        set_toolset_clang(conf)
        check_toolset_clang(conf)
    elif conf.env.TOOLSET == 'msvc':
        conf.load('msvc')
        set_toolset_msvc(conf)
        check_toolset_msvc(conf)
    elif conf.env.TOOLSET == 'auto':
        conf.load('compiler_c')
        conf.load('compiler_cxx')
        set_toolset_from_compiler_check(conf)
    else:
        print ("Unsupported Toolset option")
        sys.exit(1)


def set_target_system(conf):
    print('Setting Target system from compiler check')
    if compiler_is_mingw(conf) or compiler_is_msvc(conf):
        conf.env.TARGET_SYSTEM = 'Windows'
        conf.env.TARGET_WINDOWS = True
        conf.env.TARGET_LINUX = False
    else:
        conf.env.TARGET_SYSTEM = 'Linux'
        conf.env.TARGET_LINUX = True
        conf.env.TARGET_WINDOWS = False


def check_library_dependencies(conf):

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

    if conf.env.WITH_TESTS:
        if not conf.check(lib='boost_unit_test_framework-mt',
                          uselib_store='BOOST_UNIT_TEST_FRAMEWORK', mandatory=False):
            conf.check(
                lib='boost_unit_test_framework',
                uselib_store='BOOST_UNIT_TEST_FRAMEWORK')


def configure(conf):

    set_config_env_from_options(conf)

    load_toolset(conf)

    conf.load('gnu_dirs')

    set_target_system(conf)

    if conf.env.TOOLSET_GCC:
        set_gcc_compiler_flags(conf)
    if conf.env.TOOLSET_CLANG:
        set_gcc_compiler_flags(conf)
    elif conf.env.TOOLSET_MSVC:
        set_msvc_compiler_flags(conf)

    check_library_dependencies(conf)

    if not conf.env.ENABLE_SHARED and not conf.env.ENABLE_STATIC:
        # needed because of the weird waf options design
        conf.env.ENABLE_SHARED = True

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
