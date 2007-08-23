
def CheckVersion(context, version):
     context.Message( 'Checking for pkg-config version >= %s... ' %version )
     ret = context.TryAction('pkg-config --atleast-pkgconfig-version=%s' % version)[0]
     context.Result( ret )
     return ret

def CheckPackage(context, name, version):
     context.Message( 'Checking for %s... ' % name )
     ret = context.TryAction('pkg-config --atleast-version=%s %s' %(version,name) )[0]
     context.Result( ret )
     return ret
