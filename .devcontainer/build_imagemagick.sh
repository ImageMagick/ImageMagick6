#!/bin/bash -eu

autoreconf -fiv
./configure --prefix="$WORK" --disable-docs CFLAGS="-I$WORK/include" LIBS="-L$WORK/lib" PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
make "-j$(nproc)"
make install
