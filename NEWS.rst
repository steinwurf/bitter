News for bitter
===============

This file lists the major changes between versions. For a more
detailed list of every change, see the Git log.

Latest
------
* Minor: Added cmake build file.

5.0.0
-----
* Major: Moved files in detail namespace into the detail folder.

4.1.0
-----
* Minor: Added support for native types in the bitter readers and
  writers. Such that using ``uint8_t``, ``uint16_t`` etc. now is the
  default. Using the ``u8``, ``u16``, ``u24`` etc. types is still
  possible and used under-the-hood by bitter.

4.0.0
-----
* Major: Renamed ``read_as`` to ``as``.

3.0.0
-----
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
