#!/bin/bash
# @Author: Marius Messerschmidt <marius>
# @Date:   08-10-2016 10:10:41
# @Email:  marius.messerschmidt@googlemail.com
# @Last modified by:   marius
# @Last modified time: 08-10-2016 20:10:30
# @License: MIT

CPPCHECK_ARGS="--force --language=c --error-exitcode=1 --verbose --std=c99 --std=c11"
find . -name "*.[c,h]" -exec cppcheck $CPPCHECK_ARGS {} +
