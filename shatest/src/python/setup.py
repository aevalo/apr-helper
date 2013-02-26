# setup.py
from setuptools import setup, find_packages, Extension
import sys, os

version = '0.1'

setup(name='sha1py',
      version=version,
      description='SHA1 Checksum Package',
      #packages=find_packages('.', exclude=['tests']),
      packages=['sha1py', 'tests'],
      ext_modules=[
        Extension('sha1', ['src/sha1module.cpp'], language='c++',
        	libraries=['sha1_checksum'],
        	library_dirs = ['../../../build/shatest'],
        	include_dirs = ['..'])
        ],
      include_package_data=True,
      zip_safe=False,
      )
