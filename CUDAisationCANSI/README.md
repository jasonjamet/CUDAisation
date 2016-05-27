# CUDAisation
Transforms "C" functions to "CUDA" functions.


###Usage :
```
Usage: cudaparse [OPTION] [FILE]
```
-x \t\t Print an XML representation of the tree (build from ANSI-C).

-c \t\t Print the C code with cuda kernel(s).

-o OUTPUT_FILE \t\t Save the result on a file, depend to the prints options (if none, store the c result).

-h \t	 Print help informations.

####Compilation:
```
make
```

###Exemple :
Parallelize a function on our test file "test.c", result will be on testcuda.c
```
./cudaparse -c -o test/testcuda.c test/test.c
```
