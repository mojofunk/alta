# -*- python -*-
#
# SConstruct
# ardour win32/msys/mingw build script
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

#needed for subst_in_file
import re
import string
#import glob
import SCons.Node.FS

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
	BoolOption('DEBUG_EXTRA', 'Include extra debugging information in debugging output (useful for developers only)', 1),
	BoolOption('DISABLE_ASSERT', 'Disable Assertions (useful for developers only)', 0)
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

deps = \
{
	'glib-2.0'             : '2.10.1',
	'gthread-2.0'          : '2.10.1',
	'gtk+-2.0'             : '2.8.1',
	'glibmm-2.4'           : '2.8.1',
	'gtkmm-2.4'            : '2.8.1',
	'libxml-2.0'           : '2.6.0',
	'sndfile'              : '1.0.15',
	'samplerate'           : '0.1.2',
	'raptor'               : '1.4.8',
	'lrdf'                 : '0.4.0',
	'soundtouch-1.0'       : '1.3.1',
	'libgnomecanvasmm-2.6' : '2.12.0'
}

if env['PLATFORM'] == 'win32':
	deps['jackmp'] = '0.1.0'
else:
	deps['jack'] = '0.101.1'

def CheckPKGConfig(context, version):
     context.Message( 'Checking for pkg-config version >= %s... ' %version )
     ret = context.TryAction('pkg-config --atleast-pkgconfig-version=%s' % version)[0]
     context.Result( ret )
     return ret

def CheckPKG(context, name):
     context.Message( 'Checking for %s... ' % name )
     ret = context.TryAction('pkg-config --exists \'%s\'' % name)[0]
     context.Result( ret )
     return ret

conf = Configure(env, custom_tests = { 'CheckPKGConfig' : CheckPKGConfig,
                                       'CheckPKG' : CheckPKG })

# I think we actually do need a recent version on WIN32, XXX need to check
min_pkg_config_version = '0.18.0'

if not conf.CheckPKGConfig(min_pkg_config_version):
     print 'pkg-config >= %s not found.' % min_pkg_config_version
     Exit(1)

for pkg, version in deps.iteritems():
	if not conf.CheckPKG( '%s >= %s' %(pkg, version) ):
		print '%s >= %s not found.' %(pkg, version)
		Exit(1)
	else:
		env.ParseConfig ('pkg-config --cflags --libs %s' %pkg )

# err actually check for these.

env.Append(LINKFLAGS = '-lboost_filesystem')

env.Append(CCFLAGS = '-DHAVE_INTTYPES')
env.Append(CCFLAGS = '-DHAVE_RINT')
env.Append(CCFLAGS = '-DHAVE_STRING_H')
env.Append(CCFLAGS = '-DNO_POSIX_MEMALIGN')
env.Append(CCFLAGS = '-DHAVE_UNISTD_H')

env = conf.Finish()

env.Append(CPPPATH = [ '#src' ])
env.Append(CPPPATH = [ '#src/libgleam' ])
env.Append(CPPPATH = [ '#src/libcformat' ])
env.Append(CPPPATH = [ '#src/libmojo' ])


if env['DEBUG']:
	
	env.Append(CPPPATH = [ '#src/liblogx' ])

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
#	env.Append(CCFLAGS = ['-pedantic'])
#	env.Append(CCFLAGS = ['-ansi'])
#
#	env.Append(CCFLAGS = ['-Wunreachable-code'])
#	env.Append(CCFLAGS = ['-Wsign-promo'])
#
#	env.Append(CCFLAGS = ['-fno-nonansi-builtins'])
#	env.Append(CCFLAGS = ['-fvisibility-inlines-hidden'])
#	env.Append(CCFLAGS = ['-fno-default-inline'])
#
#	It is doubtful that these would ever be used.
#
#	env.Append(CCFLAGS = ['-Wstack-protector'])
#	env.Append(CCFLAGS = ['-fstack-protector-all'])

# C++ specific warnings.
#
#	env.Append(CXXFLAGS = ['-Wshadow'])
#	env.Append(CXXFLAGS = ['-Wold-style-cast'])
#	env.Append(CXXFLAGS = ['-Wabi'])
#	env.Append(CXXFLAGS = ['-Weffc++'])
#	env.Append(CXXFLAGS = ['-Wstrict-null-sentinel'])
#	env.Append(CXXFLAGS = ['-Woverloaded-virtual'])

	if not env['DEBUG_EXTRA']:
		env.Append(CXXFLAGS = ['-DNDEBUG_EXTRA'])
	
else:
	env.Append(CXXFLAGS = ['-DNDEBUG'])
	env.Append(CXXFLAGS = ['-O3'])

if env['DISABLE_ASSERT']:
	env.Append(CXXFLAGS = ['-DG_DISABLE_ASSERT'])


# Generate help text for command line options
Help(opts.GenerateHelpText(env))

# Cache current options
opts.Save(conf_file, env)

##############
#  Builders  #
##############

# Substitution dictionary for generating a pkg-config file,
# Documentation, etc.
subst_dict = { }

def do_subst_in_file(targetfile, sourcefile, dict):
        """Replace all instances of the keys of dict with their values.
        For example, if dict is {'%VERSION%': '1.2345', '%BASE%': 'MyProg'},
        then all instances of %VERSION% in the file will be replaced with 1.2345 etc.
        """
        try:
            f = open(sourcefile, 'rb')
            contents = f.read()
            f.close()
        except:
            raise SCons.Errors.UserError, "Can't read source file %s"%sourcefile
        for (k,v) in dict.items():
            contents = re.sub(k, v, contents)
        try:
            f = open(targetfile, 'wb')
            f.write(contents)
            f.close()
        except:
            raise SCons.Errors.UserError, "Can't write target file %s"%targetfile
        return 0 # success
 
def subst_in_file(target, source, env):
        if not env.has_key('SUBST_DICT'):
            raise SCons.Errors.UserError, "SubstInFile requires SUBST_DICT to be set."
        d = dict(env['SUBST_DICT']) # copy it
        for (k,v) in d.items():
            if callable(v):
                d[k] = env.subst(v())
            elif SCons.Util.is_String(v):
                d[k]=env.subst(v)
            else:
                raise SCons.Errors.UserError, "SubstInFile: key %s: %s must be a string or callable"%(k, repr(v))
        for (t,s) in zip(target, source):
            return do_subst_in_file(str(t), str(s), d)
 
def subst_in_file_string(target, source, env):
        """This is what gets printed on the console."""
        return '\n'.join(['Substituting vars from %s into %s'%(str(s), str(t))
                          for (t,s) in zip(target, source)])
 
def subst_emitter(target, source, env):
        """Add dependency from substituted SUBST_DICT to target.
        Returns original target, source tuple unchanged.
        """
        d = env['SUBST_DICT'].copy() # copy it
        for (k,v) in d.items():
            if callable(v):
                d[k] = env.subst(v())
            elif SCons.Util.is_String(v):
                d[k]=env.subst(v)
        Depends(target, SCons.Node.Python.Value(d))
        # Depends(target, source) # this doesn't help the install-sapphire-linux.sh problem
        return target, source
 
subst_action = Action (subst_in_file, subst_in_file_string)
subst_builder = Builder(action=subst_action, emitter=subst_emitter)
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

