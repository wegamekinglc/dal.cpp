#!/bin/bash -e

export NUM_CORES=$(grep -c processor /proc/cpuinfo)

echo NUM_CORES: $NUM_CORES

mkdir -p build
(
  cd build || exit
  cmake --preset %BUILD_TYPE%-windows ..
  make -j${NUM_CORES}
  make install
)

if [ $? -ne 0 ]; then
  exit 1
fi

echo "Finished building of Machinist"
