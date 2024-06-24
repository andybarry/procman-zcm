from distutils.core import setup

setup(name="zcm", version="0.1.0",
      package_dir = { '' : 'src' },
      packages=["procman", "procman/sheriff_gtk"],
      scripts=["scripts/procman-sheriff"])
