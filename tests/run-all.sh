#!/bin/sh

set -eu

echo 'FuelLang Tests'
echo

echo 'Building CLI...'
cd ../build/cli
make
cd ../../tests
cp ../build/cli/fuelc .
echo

echo 'Running bootstrap tests...'
echo "(Interpreter)";
for tc in syntax/*.fuel; do
    echo "$tc";
    ./fuelc --disable-jit $tc > out;
    diff $tc.out out;
done
echo "(JIT)";
for tc in syntax/*.fuel; do
    echo "$tc";
    ./fuelc $tc > out;
    diff $tc.out out;
done
echo 'Bootstrapped.'
echo
exit

echo 'Running self-hosted tests...'
echo
echo 'Multi-architecture JIT tests...'
./fuelc multiarch.fuel

echo
echo 'All tests passed.'
