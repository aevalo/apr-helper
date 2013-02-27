# setup.py
from setuptools import setup, find_packages, Extension
import sys, os

version = '0.1'

setup(name='AprHelperPy',
      version=version,
      description='apr-helper for Python',
      #packages=find_packages('python/', exclude=['tests']),
      packages=['python/AprHelperPy'],
      ext_modules=[
        Extension('apr_helper_py', ['python/src/ahpmodule.cpp'], language='c++',
        	libraries=['apr-helper', 'apr-1'],
        	library_dirs = ['build/src'],
        	include_dirs = ['src', '/usr/include/apr-1'])
        ],
      include_package_data=True,
      zip_safe=False,
      )
