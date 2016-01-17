#!/bin/sh
#
# Metashell - Interactive C++ template metaprogramming shell
# Copyright (C) 2013, Abel Sinkovics (abel@sinkovics.hu)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set -e

if [ ! -d cmake ]
then
  echo "Please run this script from the root directory of the Metashell source code"
  exit 1
fi

# Arguments
if [ -z "${BUILD_THREADS}" ]
then
  BUILD_THREADS=1
fi

PLATFORM="$(tools/detect_platform.sh)"

# Config
if [ "${PLATFORM}" = "openbsd" ]
then
  export CC=egcc
  export CXX=eg++
fi

# Show argument & config summary
echo "Number of threads used: ${BUILD_THREADS}"
echo "Platform: ${PLATFORM}"

# Build Templight
if [ "${NO_TEMPLIGHT}" = "" ]
then
  cd 3rd
    cd templight
      mkdir -p build; cd build
        cmake ../llvm \
          -DCMAKE_BUILD_TYPE=Release \
          -DLLVM_ENABLE_TERMINFO=OFF \
          && make templight -j${BUILD_THREADS}
      cd ..
    cd ..
  cd ..
else
  echo "Skipping Templight build, because \$NO_TEMPLIGHT = \"${NO_TEMPLIGHT}\""
fi

mkdir -p bin; cd bin
  cmake ..
  make -j${BUILD_THREADS}
  make test

  if [ "${PLATFORM}" = "osx" ]
  then
    OPTIONAL_LIBCXX="-I$(pwd)/include/metashell/libcxx"
  else
    OPTIONAL_LIBCXX=""
  fi

  for t in core pp mdb; do
    test/system/app/${t}/metashell_${t}_system_test \
      app/metashell -- "-I$(pwd)/../3rd/boost/include" --
  
    test/system/app/${t}/metashell_${t}_system_test \
      app/metashell \
      --engine clang \
      -- \
      "$(pwd)/app/templight_metashell" \
      -std=c++0x \
      -ftemplate-depth=256 \
      -Wfatal-errors \
      "${OPTIONAL_LIBCXX}" \
      "-I$(pwd)/include/metashell/templight" \
      "-I$(pwd)/../3rd/boost/include" \
      --
  done

  cpack
cd ..
