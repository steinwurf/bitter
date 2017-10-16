News for bitter
===============

This file lists the major changes between versions. For a more
detailed list of every change, see the Git log.

Latest
------
* Major: Added support for additional byte sized fields. Instead of
  directly using the native types. bitter now uses the types defined in
  ``src/bitter/types.hpp`` such as ``u8``, ``u16``, ``u24``, ``u32``, etc.
* Major: Changed ``bitter::reader`` and ``bitter::writer`` to support
  LSB 0 and MSB 0 bit numbering (see README.rst for introduction). The old
  ``bitter::reader`` and ``bitter::writer`` are functional equivalent to
  ``bitter::lsb0_reader``, ``bitter::lsb0_writer`` old applications should
  be able to upgrade by simply renaming.

2.0.1
-----
* Patch: Fix version name.

2.0.0
-----
* Major: Upgrade to waf-tools 4
* Minor: Upgrade to gtest 4
* Major: Removed endian dependency

1.1.0
-----
* Minor: Made ``field`` and ``read_as`` member functions ``const``.

1.0.0
-----
* Major: Initial release.
