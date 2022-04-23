# RIBF

# ROOT Installation

### 1. Ubuntu

1. Download root_v6.10.04.source.tar.gz from https://root.cern/install/all_releases/
2. Unpack the tar file in ROOTcern folder.
3. Create a build folder
'''
d@d:~/ROOTcern$ mkdir root-6.10.04Build
d@d:~/ROOTcern$ cd root-6.10.04Build
'''

4) cmake as a super user
d@d:~/ROOTcern/root-6.10.04Build$ sudo su
root@d:/home/d/ROOTcern/root-6.10.04Build# cmake ../root-6.10.04

--> root@d:/home/d/ROOTcern/root-6.10.04Build# cmake -Dall=on .
--> root@d:/home/d/ROOTcern/root-6.10.04Build# cmake -DCMAKE_INSTALL_PREFIX=/home/d/ROOTcern/root-6.10.04install .

5) make
root@d:/home/d/ROOTcern/root-6.10.04Build# make -j4

6) install
root@d:/home/d/ROOTcern/root-6.10.04Build# make install

7) .bashrc file

--> Open .bashrc file
root@d:/home/d/ROOTcern/root-6.10.04Build# cd
root@d:~# gedit .bashrc 

--> Add following lines to it.
# ROOT CERN
source /home/d/ROOTcern/root-6.10.04install/bin/thisroot.sh 

8) To access root as a normal user, I am also adding this lines to .bashrc file in /home/d
root@d:~# cd /home/d/
root@d:/home/d# gedit .bashrc 
