#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'bitter'
VERSION = '1.0.0'

import waflib.extras.wurf_options


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    # Internal dependencies
    if ctx.is_toplevel():

        ctx.add_dependency(resolve.ResolveVersion(
            name='gtest',
            git_repository='github.com/steinwurf/gtest.git',
            major=3))

        ctx.add_dependency(resolve.ResolveVersion(
            name='endian',
            git_repository='github.com/steinwurf/endian.git',
            major=3))


def configure(conf):

    conf.load("wurf_common_tools")


def build(bld):

    bld.load("wurf_common_tools")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_CONDIAN_VERSION="{}"'.format(
            VERSION))

    bld(name='bitter_includes',
        includes='./src',
        export_includes='./src',
        use=['endian_includes'])

    if bld.is_toplevel():

        # Only build tests when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse('test')
        bld.recurse('examples/simple_writer')
        bld.recurse('examples/simple_reader')
    #    bld.recurse('examples/tcp_header_read_write')
