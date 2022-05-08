# How to run MakeTree.C?

1. Start the ROOT
```
$ root -l
```

2. Compile MakeTree.C file
```
[0] .L MakeTree.C+
```

3. Execute the program
```
[1] MakeTree("Input .ridf file", "Output .root file", run number)
```

## Output file name

- Convetional name for MakeTree output file is rawRUNNUMBER.root
- For example a file name `raw0125.root` indicates raw data output file for 125 runnumber.
