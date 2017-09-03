# tfCPPExample
This is an example to create a tf graph in python and use it in c++.

# TensorFlow C++ and Python load and return a value

This example shows how you can load a pre-trained TensorFlow graph and use it
in c++ to compute and return an output.
## Description

Download and place the folder TFprocEx in C drive.

## To build/install/run

Download and place the folder TFprocEx in C drive.

Open cmd prompt,  cd c:\TFprocEx
run cppCreatProcEx.exe. This will show the time taken for 'loadcppEx' process creation/execution (~0.015seconds) and time taken until process in terminated/return the output (~0.8 seconds).

Within cppCreatProcEx.cpp (line 30) change the process name to dummyEx.ex which takes much lesser time (<0.1 seconds) to create, execute, and also to get the return value. 
