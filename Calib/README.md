# How to run calib.cc?

1. Clear files
```
$ make clean
```
2. Make
```
$ make
```
3. Execute the program
- I edited the calib.cc. Now it requires 3 inputs
  1) full name of input file with path.
  2) full name of output file with path.
  3) run number 
```
$ ./calib Inputfile.root Outputfile.root runnumber
```

## Output file name

- The conventional name for output calib file is: calRUNNUMBER.root.
- For exampler file name `cal0125.root` indicates calibrated outputfile for 125 runnumber.
