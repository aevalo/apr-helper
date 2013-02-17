# setup.py
from setuptools import setup, find_packages, Extension
import sys, os

version = '0.1'

setup(name='spam',
      version=version,
      description='Spam Pakcage',
      packages=find_packages('spam', exclude=['tests']),
      ext_modules=[
        Extension('spam.spam', ['spam/src/spammodule.cpp', 'spam/src/sha1_checksum.cpp'], language='c++', libraries=['apr-1', 'aprutil-1'], library_dirs = ['/usr/lib'], include_dirs = ['/usr/include/apr-1'])
        ],
      include_package_data=True,
      zip_safe=False,
      )
