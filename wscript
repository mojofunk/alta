#! /usr/bin/env python
# encoding: utf-8
# Tim Mayberry, 2008

import os
import Params

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

def _check_deps(conf):
	conf.check_pkg('jack', destvar='JACK', vnum='0.105.0', mandatory=True)
	conf.check_pkg('glib-2.0', destvar='GLIB', vnum='2.10.1', mandatory=True)
	conf.check_pkg('gthread-2.0', destvar='GTHREAD', vnum='2.10.1', mandatory=True)
	conf.check_pkg('gtk+-2.0', destvar='GTK2', vnum='2.8.1', mandatory=True)
	conf.check_pkg('libxml-2.0', destvar='LIBXML', vnum='2.6.0', mandatory=True)
	conf.check_pkg('glibmm-2.4', destvar='GLIBMM', vnum='2.8.0', mandatory=True)
	conf.check_pkg('gtkmm-2.4', destvar='GTKMM', vnum='2.8.0', mandatory=True)
	conf.check_pkg('goocanvasmm-1.0', destvar='GOOCANVASMM', vnum='0.4.0', mandatory=True)
	#conf.check_pkg('libSoundTouch', destvar='SOUNDTOUCH', vnum='1.3.1', mandatory=True)
	#conf.check_pkg('samplerate', destvar='SAMPLERATE', vnum='0.1.0', mandatory=True)
	#conf.check_pkg('raptor', destvar='RAPTOR', vnum='1.4.2', mandatory=True)
	#conf.check_pkg('lrdf', destvar='LRDF', vnum='0.4.0', mandatory=True)
	#conf.check_pkg('sndfile', destvar='SNDFILE', vnum='1.0.15', mandatory=True)
	#conf.check_pkg('alsa', destvar='ALSA', vnum='1.0.13', mandatory=True)

	conf.check_library2 ('boost_unit_test_framework', uselib='BOOST_TEST')
	conf.check_library2 ('boost_filesystem', uselib='BOOST_FILESYSTEM')

def _define_paths(conf):

	def getstr(varname):
		return getattr(Params.g_options, varname, '')

	prefix  = getstr('prefix')
	datadir = getstr('datadir')
	libdir  = getstr('libdir')
	configdir  = getstr('configdir')

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
	conf.check_tool('checks')

	#conf.check_header('mntent.h', 'HAVE_GETMNTENT')

	_check_deps(conf)

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
