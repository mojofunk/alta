# -*- python -*-
#
# vim: tabstop=4 expandtab shiftwidth=4
#
# SConstruct
# gmojo build script
#
# Process this file with 'scons' to build the project.
# For more information, please visit: http://www.scons.org/ .
#
# Usage: 
#
#	. scons               build all the default targets
#	. scons -h            see available configuration options
#	. scons opt=value     set a configuration option
#	. scons install       install library and include files (as root)
#	. scons dist          build a source package (.tar.bz2) XXX todo
#	. scons doc           build documentation for the project (Doxygen)
#

#import commands
import os
import sys

import tools.pkgconfig as pkgconfig
import tools.substitute as substitute

conf_file = 'gmojo.conf'

# So scons doesn't install .sconsign files
SConsignFile()

#############
#  Options  #
#############

# Command line options
opts = Options(conf_file)

opts.AddOptions(
	PathOption('PREFIX', 'installation path prefix', '/usr/local'),
	('DESTDIR', 'installation root directory (for packaging)', ''),
	('BINDIR', 'path for binary files (default is $PREFIX/bin)', '/bin'),
	('LIBDIR', 'path for library files (default is $PREFIX/lib', '/lib'),
	BoolOption('DEBUG', 'Debug version (useful for developers only)', 1),
)

###############################
#  Configuration Environment  #
###############################

env = Environment(options = opts)

if env['PLATFORM'] == 'win32':
	Tool('mingw')(env)

env.Append(ENV = os.environ)

env.Append(MAJOR='0',MINOR='1',MICRO='0')
env.Append(PACKAGE_NAME = 'gmojo')
env.Append(VERSIONED_NAME = "%s-%s.%s" % (env['PACKAGE_NAME'], env['MAJOR'], env['MINOR']))

#######################
# Dependency Checking #
#######################

#deps = { }

deps = \
{
    'glib-2.0'             : '2.10.1',
    'gthread-2.0'          : '2.10.1',
    'gtk+-2.0'             : '2.8.1',
    'glibmm-2.4'           : '2.8.1',
    'goocanvas'            : '0.6',
    'sndfile'              : '1.0'
}

pkgconfig.CheckDependencies ( env, deps )

pkgconfig.ParseDependencies ( env, deps )

# err actually check for these.

env.Append(LIBS = ['boost_filesystem', 'boost_serialization', 'boost_signals'])

env.Append(CPPPATH = [ '#src' ])
env.Append(CPPPATH = [ '#src/libgleam' ])
env.Append(CPPPATH = [ '#src/cformat' ])
env.Append(CPPPATH = [ '#src/mojo' ])


if env['DEBUG']:
	env.Append(CCFLAGS = ['-g'])
	env.Append(CCFLAGS = ['-Wextra'])
	env.Append(CCFLAGS = ['-Wall'])
	# it is too annoying without this to suppress unused parameters.
	# at the moment. Note, must come after -Wall
	env.Append(CCFLAGS = ['-Wno-unused-parameter'])
	env.Append(CCFLAGS = ['-Wpointer-arith'])
	env.Append(CCFLAGS = ['-Wconversion'])
	env.Append(CCFLAGS = ['-Wcast-align'])
    # Other compiler options to play with.
    #
    #env.Append(CCFLAGS = ['-pedantic'])
    #env.Append(CCFLAGS = ['-ansi'])
    #
    #env.Append(CCFLAGS = ['-Wunreachable-code'])
    #env.Append(CCFLAGS = ['-Wsign-promo'])
    #
    #env.Append(CCFLAGS = ['-fno-nonansi-builtins'])
    #env.Append(CCFLAGS = ['-fvisibility-inlines-hidden'])
	#env.Append(CCFLAGS = ['-fno-default-inline'])
	#
	#It is doubtful that these would ever be used.
	#
	#env.Append(CCFLAGS = ['-Wstack-protector'])
	#env.Append(CCFLAGS = ['-fstack-protector-all'])
	#
	# C++ specific warnings.
	#
	#	env.Append(CXXFLAGS = ['-Wshadow'])
	#	env.Append(CXXFLAGS = ['-Wold-style-cast'])
	#	env.Append(CXXFLAGS = ['-Wabi'])
	#	env.Append(CXXFLAGS = ['-Weffc++'])
	#	env.Append(CXXFLAGS = ['-Wstrict-null-sentinel'])
	#	env.Append(CXXFLAGS = ['-Woverloaded-virtual'])
	
else:
	env.Append(CXXFLAGS = ['-DNDEBUG'])
	env.Append(CXXFLAGS = ['-O2'])

# Generate help text for command line options
Help(opts.GenerateHelpText(env))

# Cache current options
opts.Save(conf_file, env)

##############
#  Builders  #
##############

# Substitute values into files
subst_action = Action (substitute.subst_in_file, substitute.subst_in_file_string)
subst_builder = Builder(action=subst_action, emitter=substitute.subst_emitter)
env.Append (BUILDERS = {'SubstInFile' : subst_builder})

# Documentation generation system
doxygen_builder = Builder(action = 'doxygen $SOURCE')
env.Append(BUILDERS = { 'DoxygenDoc' : doxygen_builder })

########################
#  Installation rules  #
########################

# Set the final installation paths This may be used to configure
# an application with statically configured paths.

# This is unused.
env.Append( FINAL_LIBDIR = env['PREFIX'] + env['LIBDIR'] )

# This is unused in my build, The final installation path of binaries.
env.Append( FINAL_BINDIR = env['PREFIX'] + env['BINDIR'] )

# The location to install the binaries to, useful for chroot style builds.
# ala rpm etc.
env.Append( INSTALL_BINDIR = env['DESTDIR'] + env['FINAL_BINDIR'] )

# This is unused.
env.Append( INSTALL_LIBDIR = env['DESTDIR'] + env['FINAL_LIBDIR'] )

# This is unused.
env.Append( INSTALL_PREFIX = env['DESTDIR'] + env['PREFIX'] )

# This is unused.
env.Append( INCLUDE_DIR = "%s/include/%s/" % (env['INSTALL_PREFIX'], env['VERSIONED_NAME']))

# Only the INSTALL_BINDIR is used at the moment.
# A better build system would take care of this crap.
installpaths = [ env['INSTALL_BINDIR'], env['INSTALL_LIBDIR'], env['INCLUDE_DIR'] ]

###########################
#  Configuration summary  #
###########################

debugging = ""

if env['DEBUG']:
	debugging = "ON"
else:
	debugging = "OFF"

print ""
print "+=================+"
print "|  CONFIGURATION  |"
print "+=================+"
print ""
print "PREFIX                           : " + env['PREFIX']
print "BINDIR                           : " + env['BINDIR']
print "LIBDIR                           : " + env['LIBDIR']
print "DESTDIR                          : " + env['DESTDIR']
print "INSTALL_PREFIX                   : " + env['INSTALL_PREFIX']
print "INCLUDE_DIR                      : " + env['INCLUDE_DIR']
print "INSTALL_BINDIR                   : " + env['INSTALL_BINDIR']
print "INSTALL_LIBDIR                   : " + env['INSTALL_LIBDIR']
print "FINAL_BINDIR                     : " + env['FINAL_BINDIR']
print "FINAL_LIBDIR                     : " + env['FINAL_LIBDIR']
print "PLATFORM                         : " + env['PLATFORM']
print "DEBUG                            : " + debugging
print ""

Export('env')

###########################
# Substitution Dictionary #
###########################

# These are also properties of the scons environment but
# are used for substituting values into foo.in files.

# Substitution dictionary for generating a pkg-config file,
# Documentation, etc.
subst_dict = { }

subst_dict['%PACKAGE_NAME%'] = env['PACKAGE_NAME']
subst_dict['%VERSIONED_NAME%'] = env['VERSIONED_NAME']
subst_dict['%MAJOR%'] = env['MAJOR']
subst_dict['%MINOR%'] = env['MINOR']
subst_dict['%MICRO%'] = env['MICRO']
subst_dict['%PREFIX%'] = env['PREFIX']

# useful for pkg-config, but not used in my build
subst_dict['%LIBDIR%'] = env['LIBDIR']

#################
#  Build rules	#
#################

if env['DEBUG']:
	BuildDir("#build/debug", 'src', duplicate = 0 )
	buildDirectory = 'build/debug/'
else:
	BuildDir("#build/release", 'src', duplicate = 0 )
	buildDirectory = 'build/release/'

SConscript (buildDirectory + '/SConscript')

# Provide "install" target (ie. 'scons install')
env.Alias('install', installpaths)

###################
#  Documentation  #
###################

# I would prefer the name of the directory containing 
# documentation to be docs or doc directory instead of DOCUMENTATION
doxybuild = env.SubstInFile ( 'doc/doxygen/Doxyfile', 'doc/doxygen/Doxyfile.in', SUBST_DICT = subst_dict)

Default(doxybuild)

doxygen_path = '(doxygen-generated-files)'

env.DoxygenDoc(doxygen_path, 'doc/doxygen/Doxyfile')
env.Alias('doc', doxygen_path)
