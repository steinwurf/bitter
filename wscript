#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'bitter'
VERSION = '5.1.0'

def options(opt):

    opt.add_option(
        '--test_filter', default=None, action='store',
        help='Compiles all tests that include the substring specified.'
             'Wildcards allowed. (Used with --run_tests)')

def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_BITTER_VERSION="{}"'.format(
            VERSION))

    bld(name='bitter_includes',
        includes='./src',
        export_includes='./src')

    if bld.is_toplevel():

        # Only build tests when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse('test')

        bld.recurse('examples/simple_writer')
        bld.recurse('examples/simple_reader')
