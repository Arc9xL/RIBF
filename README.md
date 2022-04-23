# RIBF

This code is based on ROOT and ANAROOT. The installation process for both is described here.

# 1. ROOT Installation

### - Ubuntu

1. Download root_v6.10.04.source.tar.gz from https://root.cern/install/all_releases/
2. Unpack the tar file in ROOTcern folder.
3. Create a build folder
```
d@d:~/ROOTcern$ mkdir root-6.10.04Build 
d@d:~/ROOTcern$ cd root-6.10.04Build
```

4. cmake as a super user
```
d@d:~/ROOTcern/root-6.10.04Build$ sudo su
root@d:/home/d/ROOTcern/root-6.10.04Build# cmake ../root-6.10.04
root@d:/home/d/ROOTcern/root-6.10.04Build# cmake -Dall=on .
root@d:/home/d/ROOTcern/root-6.10.04Build# cmake -DCMAKE_INSTALL_PREFIX=/home/d/ROOTcern/root-6.10.04install .
```

5. make
```
root@d:/home/d/ROOTcern/root-6.10.04Build# make -j4
```

6. install
```
root@d:/home/d/ROOTcern/root-6.10.04Build# make install
```
7. .bashrc file

- Open .bashrc file
```
root@d:/home/d/ROOTcern/root-6.10.04Build# cd
root@d:~# gedit .bashrc 
```
- Add following lines to it.
```
# ROOT CERN 
source /home/d/ROOTcern/root-6.10.04install/bin/thisroot.sh 
```
8. To access root as a normal user, I am also adding this lines to .bashrc file in /home/d
```
root@d:~# cd /home/d/
root@d:/home/d# gedit .bashrc 
```

### - Windows
- Follow this tutorial to install `Xming` and `Ubuntu terminal`: https://www.youtube.com/watch?v=pmfM4Zq6OQU
- After the intallation,
  - Start Xming (this will allow the terminal to display root).
  - Open ther ubuntu terminal
  - `export DISPLAY = "localhost:0"` (optional step)
  - `root -l`

# 2. ANAROOT installation

- Following the instructions on webpage: https://ribf.riken.jp/RIBFDAQ/index.php?Tools%2FAnalysis%2FANAROOT%2FInstallation

1. Download anaroot_v4.5.36.tgz
- Extract the file in ANAROOTriken folder.
```
d@d:~/ANAROOTriken$ tar xzfv anaroot_v4.5.36.tgz
```

2. cd anaroot

3. In autogen.sh file, replaced sh by bash.
- because the TARTSYS is in bashrc file.
- form #!/bin/sh to #!/bin/bash in the first line of autogen.sh.

- Note: I tried excluding this step and check if it works. But results were similar.

4. Super user.
```
d@d:~/ANAROOTriken/anaroot$ sudo su
root@d:/home/d/ANAROOTriken/anaroot# 
```

5. `./autogen.sh --prefix=$PWD`

6. `make install`

7. `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/lib`


- Now following the instructions on the second section of webpage: http://be.nucl.ap.titech.ac.jp/~nishi/root.html

8. Add anaroot path to .bashrc file
- Open .bashrc file
```
root@d:/home/d/ANAROOTriken/anaroot# cd
root@d:~# gedit .bashrc 
```
- Add following lines
```
# ANAROOT RIKEN
export TARTSYS=/home/d/ANAROOTriken/anaroot
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TARTSYS/lib
```

8. `cd run`

9. `root -l`
- The command history after this step is following.
```
root@d:~# cd /home/d/ANAROOTriken/anaroot
root@d:/home/d/ANAROOTriken/anaroot/run# root -l
add include path : /home/d/ANAROOTriken/anaroot/include
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

10. To access anaroot as a normal user, I repeated step-7 for bashrc file in /home/d.
```
root@d:~# gedit /home/d/.bashrc
```
- The last lines for both the .bashrc files are
```
# ROOT CERN
source /home/d/ROOTcern/root-6.10.04install/bin/thisroot.sh 

# ANAROOT RIKEN
export TARTSYS=/home/d/ANAROOTriken/anaroot
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$TARTSYS/lib
```
