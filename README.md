# RIBF

- Raw/MakeTree.C and Calib/calib.cc are the main codes.
- MakeTree.C reads .ridf file and crate .root file which contains the raw data.
- calib.cc reads .root raw data file generated using MakeTree.C, and gives calibrated data in the form of .root file.
- MakeTree.C is based on the ANAROOT.

# ANAROOT installation

- Following the instructions on webpage: https://ribf.riken.jp/RIBFDAQ/index.php?Tools%2FAnalysis%2FANAROOT%2FInstallation

1. Download `anaroot_v4.5.36.tgz`.
- Extract the file in ANAROOTriken folder.
```
usrName@usrName:~/ANAROOTriken$ tar xzfv anaroot_v4.5.36.tgz
```

2. `cd anaroot`

3. In `autogen.sh` file, replaced `sh` by `bash` because the TARTSYS is in bashrc file.
- form `#!/bin/sh` to `#!/bin/bash` in the first line of autogen.sh.

4. Super user.
```
usrName@usrName:~/ANAROOTriken/anaroot$ sudo su
root@usrName:/home/usrName/ANAROOTriken/anaroot# 
```

5. `./autogen.sh --prefix=$PWD`

6. `make install`

7. `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/lib`


- Now following the instructions on the second section of webpage: http://be.nucl.ap.titech.ac.jp/~nishi/root.html

8. Add anaroot path to `.bashrc` file
- Open `.bashrc` file
```
root@usrName:/home/usrName/ANAROOTriken/anaroot# cd
root@usrName:~# gedit .bashrc 
```
- Add following lines
```
# ANAROOT RIKEN
export TARTSYS=/home/usrName/ANAROOTriken/anaroot
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TARTSYS/lib
```

9. `cd run`

10. `root -l`
- The command history after this step is following.
```
root@d:~# cd /home/usrName/ANAROOTriken/anaroot
root@d:/home/usrName/ANAROOTriken/anaroot/run# root -l
add include path : /home/usrName/ANAROOTriken/anaroot/include
reading libXMLParser.so
reading libananadeko.so
reading libanacore.so
reading libanabrips.so
reading libanadali.so
reading libanasamurai.so
reading libanacatana.so
reading libanaespri.so
reading libanawinds.so
reading libanaloop.so
reading libanaloopexample.so
reading libanaloopencexample.so
root [0] 
```

11. To access anaroot as a normal user, I repeated step-7 for bashrc file in `/home/usrName`.
```
root@usrName:~# gedit /home/usrName/.bashrc
```
- The last lines for both the `.bashrc` files are
```
# ROOT CERN
source /home/usrName/ROOTcern/root-6.10.04install/bin/thisroot.sh 

# ANAROOT RIKEN
export TARTSYS=/home/usrName/ANAROOTriken/anaroot
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TARTSYS/lib
```
