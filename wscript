#! /usr/bin/env python
# encoding: utf-8
# Tim Mayberry, 2008

import os

VERSION = '0.1.0'
APPNAME = 'Alta'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
	# options provided by the modules
	opt.load('compiler_cxx')
	opt.load('compiler_c')
	opt.load('gnu_dirs')

        opt.add_option('--with-target-platform', type='string', dest='target_platform')
        opt.add_option('--with-tests', action='store_true', default=True, help='Enable Testsuite')

def _check_required_deps(conf, deps):
	for pkg, version in deps.iteritems():
	        conf.check_cfg(package=pkg, atleast_version=version, mandatory=1)
		conf.check_cfg(package=pkg, args='--cflags --libs')

def set_compiler_flags (conf):
	cxx_flags = []
        conf.check_cxx(cxxflags=["-std=c++11"])
        cxx_flags.append('-std=c++11')

	conf.env.append_value('CXXFLAGS', cxx_flags)

def configure(conf):
	conf.load('compiler_cxx')
	conf.load('compiler_c')
	conf.load('gnu_dirs')

        if conf.options.target_platform:
                conf.env['build_target'] = conf.options.target_platform

        #conf.define('TARGET_PLATFORM', conf.env['build_target'])
        conf.env['APPNAME'] = APPNAME

	set_compiler_flags (conf)

	deps = \
	{
		'glib-2.0'             : '2.10.1',
		'gmodule-2.0'          : '2.10.1',
		'gthread-2.0'          : '2.10.1',
		'glibmm-2.4'           : '2.8.1',
		'gtkmm-3.0'            : '2.8.1',
		'sndfile'              : '1.0.20'
#		'libxml-2.0'           : '2.6.0',
#		'samplerate'           : '0.1.0',
#		'raptor'               : '1.4.2',
#		'lrdf'                 : '0.4.0',
#		'jack'                 : '0.109.0',
#		'libgnomecanvas-2.0'   : '2.0',
	}

	_check_required_deps(conf, deps)

        if conf.options.with_tests:
                conf.env['BUILD_TESTS'] = True
                print "Building with testsuite"
		if conf.env['build_target'] == 'mingw':
			if conf.env.CC_NAME == 'gcc':
				libname = 'boost_unit_test_framework-gcc%s%s-mt-1_47' % (conf.env.CC_VERSION[0], conf.env.CC_VERSION[1])
				conf.check(lib=libname, uselib_store='BOOST_UNIT_TEST_FRAMEWORK')
		else:
			conf.check(lib='boost_unit_test_framework')

        #if conf.env['build_target'] == 'mingw':
        #        conf.check(lib='pthreadGC2')
        #        conf.env.append_value('CPPPATH', os.path.join (os.getenv('MINGW_ROOT'), 'include', 'pthread'))

        if conf.env['build_target'] == 'mingw':
		# depend on F14 mingw lib names for now
		boost_filesystem_libname = 'boost_filesystem-gcc%s%s-mt-1_47' % (conf.env.CC_VERSION[0], conf.env.CC_VERSION[1])
		boost_system_libname = 'boost_system-gcc%s%s-mt-1_47' % (conf.env.CC_VERSION[0], conf.env.CC_VERSION[1])
                conf.check(lib=boost_filesystem_libname, uselib_store='BOOST_FILESYSTEM')
                conf.check(lib=boost_system_libname, uselib_store='BOOST_SYSTEM')
	else:
                conf.check(lib='boost_filesystem')
                conf.check(lib='boost_system')
	
	defines=[ 'HAVE_CONFIG_H'
		, '_REENTRANT'
		, '_LARGEFILE_SOURCE'
		, '_LARGEFILE64_SOURCE'
		]

	if conf.env['BUILD_TESTS']:
                defines += [ 'BOOST_TEST_DYN_LINK' ]

	conf.env.append_value('CCDEFINES', defines)
	conf.env.append_value('CXXDEFINES', defines)

	conf.recurse('src')

	conf.write_config_header('gmojo_config.h')

def build(ctx):
	# process subfolders from here
	ctx.recurse('src')
