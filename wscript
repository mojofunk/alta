#! /usr/bin/env python
# encoding: utf-8
# Tim Mayberry, 2008

import os

VERSION='0.1.0'
APPNAME='gmojo'

# these variables are mandatory ('/' are converted automatically)
srcdir = '.'
blddir = 'build'

def init():
	pass

def set_options(opt):
	# options provided by the modules
	opt.tool_options('compiler_cxx')
	opt.tool_options('compiler_cc')

	for i in "datadir libdir configdir".split():
		opt.add_option('--'+i, type='string', default='', dest=i)

def _check_required_deps(conf, deps):
	for pkg, version in deps.iteritems():
	        conf.check_cfg(package=pkg, atleast_version=version, mandatory=1)
		conf.check_cfg(package=pkg, args='--cflags --libs')


def _define_paths(conf):

	import Options

	prefix = Options.options.prefix
	datadir = Options.options.datadir
	libdir = Options.options.libdir
	configdir = Options.options.configdir

	if not datadir: datadir = os.path.join(prefix,'share')
	if not libdir:  libdir  = os.path.join(prefix,'lib')
	if not configdir:
		if os.path.normpath(prefix) == '/usr':
			configdir = '/etc'
		else:
			configdir  = os.path.join(prefix, 'etc')

	conf.define('DATA_DIR', datadir)
	conf.define('LIB_DIR', libdir)
	conf.define('MODULE_DIR', os.path.join(prefix, libdir))
	conf.define('LOCALE_DIR', os.path.join(datadir, 'locale'))
	conf.define('CONFIG_DIR', configdir)

def configure(conf):

	conf.check_tool('compiler_cxx')
	conf.check_tool('compiler_cc')

	conf.check(header_name='mntent.h')

	deps = \
	{
		'glib-2.0'             : '2.10.1',
		'gthread-2.0'          : '2.10.1',
		'gtk+-2.0'             : '2.8.1',
		'glibmm-2.4'           : '2.8.1',
		'gtkmm-2.4'            : '2.8.1',
		'goocanvasmm-1.0'      : '0.4.0',
#		'libxml-2.0'           : '2.6.0',
#		'samplerate'           : '0.1.0',
#		'raptor'               : '1.4.2',
#		'lrdf'                 : '0.4.0',
#		'jack'                 : '0.109.0',
#		'libgnomecanvas-2.0'   : '2.0',
#		'sndfile'              : '1.0.18'
	}

	_check_required_deps(conf, deps)

	conf.check(lib='boost_unit_test_framework')
	conf.check(lib='boost_filesystem')

	defines=[ 'HAVE_CONFIG_H'
		, '_REENTRANT'
		, '_LARGEFILE_SOURCE'
		, '_LARGEFILE64_SOURCE'
		, 'BOOST_TEST_DYN_LINK'
		]

	conf.env.append_value('CCDEFINES', defines)
	conf.env.append_value('CXXDEFINES', defines)

	_define_paths(conf)

	conf.sub_config('src')

	conf.write_config_header('config.h')

def build(bld):
	# process subfolders from here
	bld.add_subdirs('src')
