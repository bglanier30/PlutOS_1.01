#!/bin/sh
set -e
. ./headers.sh

for PROJECTin $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="SYSROOT" $MAKE install)
done
