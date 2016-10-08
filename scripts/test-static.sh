#!/bin/bash
# @Author: Marius Messerschmidt <marius>
# @Date:   08-10-2016 10:10:41
# @Email:  marius.messerschmidt@googlemail.com
# @Last modified by:   marius
# @Last modified time: 08-10-2016 11:10:93
# @License: MIT

find . -name "*.[c,h]" -exec cppcheck --force --error-exitcode=1 --inline-suppr {} +
