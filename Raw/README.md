## Aim of MakeTree.C

- MakeTree.C reads `.ridf` input file and generates `.root` output file.
- `.ridf` file (RIBF Data Format) is generated by the DAQ (Data AcQuisition) system of RIBF, which is not readable.
- MakeTree.C creates a tree that contains event-by-event information of all the variables of interest.

## Inside the code

- Majority of the code is just defination of variables and appending the values from `.ridf` file.
- One can devide the code in two main parts: 1) Before while loop, and 2) After while loop.

1) Before while loop
- This part begins with the hardcore ANAROOT. This means BigRIPS + ZDS geometry is defined here. This section is more like a standard format. Do not change anything here, unless you know what it means. Offcourse one can change some parameters according to the experiment.
- The second section in this part creates branches for variables of interest. Later, in the while loop we will append the data in these branches.

2) After while loop
- Store the information event-by-event in the branches.


## How to run MakeTree.C?

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
- For example, a file name `raw0125.root` indicates raw data output file for 125 run number.
- One can take the run number from the input `.ridf` file's name.
- For example, a file name `27F_27F_F8in_F11out0125.ridf` indicates the run number 125.
