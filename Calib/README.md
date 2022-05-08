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
- I edited the calib.cc. Now it requires 4 inputs
  1) Path to input file
  2) Name of input file
  3) Name of output file. Output file will be created in the same folder as inputfile.
  4) run number 
```
$ ./calib Path Inputfile.root Outputfile.root runnumber
```

## Output file name

- The conventional name for output calib file is: calibRUNNUMBER.root.
- For exampler file name `calib0125.root` indicates calibrated outputfile for 125 runnumber.
