KLEE-uClibc
===========

[![Build Status](https://github.com/klee/klee-uclibc/workflows/CI/badge.svg)](https://github.com/klee/klee-uclibc/actions)

This is a modified version version of klee-uclibc.  Please see README for information about uClibc.

To build uClibc for KLEE:

1. Use `--with-llvm-config` to set your llvm-config binary.  The LLVM version used by `llvm-config`
   should match the LLVM version used by the C LLVM Bitcode compiler
   you intend to use in step 2.

2. Use `--with-cc` to set your C LLVM Bitcode compiler.


3. Run the configure script.

   ```$ ./configure --make-llvm-lib --with-cc <PATH_TO_CLANG> --with-llvm-config <PATH_TO_LLVM_CONFIG_BINARY>```

   To see all options run

   ```$ ./configure --help```

4. By default a uClibc pre built `.config` file will be added to the
   uClibc root directory by the configure script. This is done to make
   compilation easier for users.  However the
   --disable-prebuilt-config flag can be used to prevent a `.config`
   file being added. If you wish to create your own `.config` you can
   do so by running `make menuconfig` or `make config` after running
   the configure script.

5. Compile

   ```$ make KLEE_CFLAGS="-fno-discard-value-names -mlong-double-64"```

    We use `KLEE_CFLAGS` here to add additional flags to disable fp80 and preserve variable name in generated IR.
