# -*- coding: utf-8 -*-
"""
Murmur Hash Library
========

Murmur Hash Library is a simple c level implementation developed for
high speed hashing of in memory strings

As the name implies the hashes are generated via an implementation of 
`MurmurHash 2.0`_. 

A few quick NOTES and WARNINGS:

The implementation of MurMur that is used in this code makes the 
following assumptions about your machine:

	1. A 4-byte value can be read from any address without crashing
	2. sizeof(int) == 4

It will also not produce the same results on little-endian and big-endian 
machines.

I believe it would be easily possible to get around these limitations.
"""
from setuptools import setup, Extension

setup(
    name='Murmur-strings',
    version='0.3.0',
    license='MIT',
    author='Kamo Petrosyan',
    author_email='kamo@haikson.com',
    description='Provides fast murmur hashes for strings.',
    zip_safe=False, # I'm not sure if it is egg safe so I'm erring on the side of caution.
    long_description=__doc__,
	ext_modules = [
		Extension('murmur', 
		[
            "murmur/murmur.cpp",
		],
		language='c++')
	],
    platforms='any',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: C++',
        'Topic :: Software Development',
        'Topic :: Software Development :: Libraries :: Python Modules'
    ],
	packages=[]
)
