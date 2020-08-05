=========================
Structure of this project
=========================

Folders and files
=================
The organization of this project is similar to the majority of Geant4 projects. The root directory contains the main program in ``neutron_detection.cc``. Header files are in ``include`` and source files are in ``src``. All of the derived classes for user actions and user initializations are in these folders. The non-standard piece of this project is the GTK files. In ``src``, ``GTKInput.cc`` and ``GTKOutput.cc`` each display the user data input window and the summary window after a simulation has been run respectively. Note that displaying the output window requires the user to exit the Geant4 shell using the ``exit`` command instead of using ``Control-C``.

CMake files, macros, and other extra files
==========================================
Modifying compiler parameters and linking properties can be done easily by modifying the ``CMakeLists.txt`` file in the root directory of this project. Adding macros can be done by inserting them into the ``NEUTRON_SCRIPTS`` CMake variable in ``CMakeLists.txt``. Alternatively, you can copy them into the build directory yourself or modify existing macro files that have been added to the build directory, but those modifications will not remain if you rebuild the project.
