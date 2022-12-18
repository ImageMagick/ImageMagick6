#!/bin/bash -eu

# build zlib
pushd "$SRC/zlib"
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build xz
pushd "$SRC/xz"
./autogen.sh --no-po4a
./configure --disable-xz --disable-xzdec --disable-lzmadec --disable-lzmainfo --disable-lzma-links --disable-scripts --disable-doc --disable-shared --with-pic=yes --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build png
pushd "$SRC/libpng"
cmake . -DCMAKE_INSTALL_PREFIX=$WORK
make -j$(nproc)
make install
popd

# Build libjpeg-turbo
pushd "$SRC/libjpeg-turbo"
cmake . -DCMAKE_INSTALL_PREFIX=$WORK
make -j$(nproc)
make install
popd

# Build libtiff
pushd "$SRC/libtiff"
autoreconf -fiv
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build liblcms2
pushd "$SRC/Little-CMS"
autoreconf -fiv
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# build libraw
pushd "$SRC/libraw"
autoreconf -fiv
./configure --prefix="$WORK" --with-pic=yes --disable-examples PKG_CONFIG_PATH="$WORK/lib/pkgconfig" CXXFLAGS="-DLIBRAW_USE_CALLOC_INSTEAD_OF_MALLOC=on"
make -j$(nproc)
make install
popd

# Build freetype2
pushd "$SRC/freetype"
./autogen.sh
./configure --prefix="$WORK" PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
make -j$(nproc)
make install
popd

# Build libde265
pushd "$SRC/libde265"
./autogen.sh
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build libheif
pushd "$SRC/libheif"
./autogen.sh
./configure --disable-go --disable-examples --disable-tests --prefix="$WORK" PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
make -j$(nproc)
make install
popd

# Build webp
pushd "$SRC/libwebp"
./autogen.sh
./configure --disable-png --disable-jpeg --disable-tiff --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build openjpg
pushd "$SRC/openjpeg"
cmake . -DCMAKE_INSTALL_PREFIX=$WORK -DBUILD_CODEC=off -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
make install
popd
