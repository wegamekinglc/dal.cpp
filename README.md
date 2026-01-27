# DAL - *D*erivatives *A*lgorithms *L*ib

## Build

### linux
```bash
$ mkdir build
$ cd build
$ cmake --preset=Release-linux ..
$ make -j32
$ make install
```

### windows

we prepared a `.bat` file for windows building:
```bash
$ build_windows.bat
```

## Run the examples ...

```bash
$ bin/test_suite

starting DAL with: 32 threads.
use AAD framework: AADET
starting initialization global data ...
stating initialization global tape ...
finished initialization all the global information.
[==========] Running 407 tests from 46 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from ConcurrencyTest
[ RUN      ] ConcurrencyTest.TestConcurrentQueuePushAndPop
[       OK ] ConcurrencyTest.TestConcurrentQueuePushAndPop (0 ms)
[ RUN      ] ConcurrencyTest.TestThreadPoolStart
[       OK ] ConcurrencyTest.TestThreadPoolStart (3 ms)
[----------] 2 tests from ConcurrencyTest (3 ms total)
```

## Excel add-in

## python binding
