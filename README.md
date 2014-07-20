CMSIS-DAP Interface Firmware
============================
Interface firmware providing USB CMSIS-DAP for debugging, USB MSD for programming, USB Serial for communication.

Documentation
-------------
* [Porting the FW to new boards](http://mbed.org/handbook/cmsis-dap-interface-firmware)

Community
---------
For discussing the development of the CMSIS-DAP Interface Firmware please join our [mbed-devel mailing list](https://groups.google.com/forum/?fromgroups#!forum/mbed-devel).

Dependencies for tools and exporters
----------------------
* Python 2.7
 * [pyYAML](https://github.com/yaml/pyyaml)
 * [Setuptools](https://pypi.python.org/pypi/distribute)
 * [Jinja2](https://pypi.python.org/pypi/Jinja2)
 
Notes
-----
**All scripts should be run from the projects root directory**
>python exporters/export.py -f exporters/records/projects.yaml

