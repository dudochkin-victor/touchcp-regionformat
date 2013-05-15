
Some guide about tests
~~~~~~~~~~~~~~~~~~~~~~

Foreword
~~~~~~~~

Note: All the test related codes are compiled in debug mode with
RUNTIME_BACKTRACE enabled for easier debugging when non reproducible error
happens on CITA.

Code coverage
~~~~~~~~~~~~~

One can use "make check" to have statistics about tests. This statistic will
provide a summary table about successful and failed test cases and an other
table about the line coverage of the source files.

Functional Unit tests
~~~~~~~~~~~~~~~~~~~~~

The name may be not the best. These tests are compiled with some of their
dependencies replaced by mock ones found under test/mock directory.

These tests should be run without problem both on sbox and device.

Mocks
~~~~~

In mocks directory external dependencies are emulated. Each class has some
static public variables to represent underlying system values. By setting
these variables before testing some feature, various use time environment can
be emulated.

Tools
~~~~~

Contains a few basic tool function used during testing. Most important ones
are those which are in use to find some named object/widget in the
runtime object/widget tree to be able to directly set and check some values
on them.

Method / function level unit tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Method and function level unit tests are not in use. The functional tests
with mock dependencies should be able to detect possible problems.

Stubs
~~~~~

Stubs are used for example in libdui to emulate some class provided by the
package itself. Stubs are not in use, instead the real classes are in use.

Original author:
Peter, Csaszar
peter.csaszar@blumsoft.eu

