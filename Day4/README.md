# Day4

## For question 4

You need to compile and run the file `Q4.c`.
```sh
gcc Q4.c   # Compile
./a.out    # Run
```

It will take the contents of the header file `my-header.h` included in the program `my-program.c`, and dump their contents one by one in a new file `program.c`, simulation the effect of `#include <header.h>`.

**It will not run on Windows** because it is a file program, and I have used the `getline` function for manipuation, and that function isn't available in Window's `gcc` compiler.
