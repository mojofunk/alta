# vim: tabstop=4 expandtab shiftwidth=4

def CheckVersion(context, version):
     context.Message( 'Checking for pkg-config version >= %s... ' %version )
     ret = context.TryAction( 'pkg-config --atleast-pkgconfig-version=%s' % version)[0]
     context.Result( ret )
     return ret

def CheckPackage(context, name, version):
     context.Message( 'Checking for %s... ' % name )
     ret = context.TryAction( 'pkg-config --atleast-version=%s %s' %(version,name) )[0]
     context.Result( ret )
     return ret

def CheckDependencies(env, deps):
    conf = env.Configure( custom_tests = { 'CheckVersion' : CheckVersion,
        'CheckPackage' : CheckPackage })

    for pkg, version in deps.iteritems():
        if not conf.CheckPackage( pkg, version ):
            context.Message( '%s >= %s not found.' %(pkg, version) )
            Exit(1)

    env = conf.Finish()

def ParseDependencies(env, deps):
    for pkg,version in deps.iteritems():
        env.ParseConfig ( 'pkg-config --cflags --libs %s' % pkg )
