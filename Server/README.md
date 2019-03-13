# multithreadedipserver
# Steps to build the code:

A) Build Client Side Image Processing Application:
cd cIPA
cmake .
make

B) Build Server Side Image Processing Application:
cd sIPA
cmake .
make

C) Build Client and Server
make all
