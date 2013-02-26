# setup.py
from setuptools import setup, find_packages, Extension
import sys, os

version = '0.1'

setup(name='sha1',
      version=version,
      description='SHA1 Checksum Package',
      packages=find_packages('sha1', exclude=['tests']),
      ext_modules=[
        Extension('sha1', ['sha1/src/sha1module.cpp'], language='c++',
        	libraries=['sha1_checksum'],
        	library_dirs = ['../../build'],
        	include_dirs = ['..'])
        ],
      include_package_data=True,
      zip_safe=False,
      )
