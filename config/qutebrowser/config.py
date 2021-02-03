config.load_autoconfig()

from glob import glob
for a in glob(f'{config.configdir}/config/*'):
    config.source(a)

