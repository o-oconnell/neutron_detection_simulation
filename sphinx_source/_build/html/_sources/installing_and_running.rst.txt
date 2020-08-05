==============================================
Installing the program and running simulations
==============================================
Running this program requires that you already have Geant4 installed. Like all Geant4 programs, building this project requires you to make a separate ``build`` directory to contain the build products and executable. You can choose to use ``cmake`` or ``ccmake`` to build the project. 


Using cmake to build the program
================================
CMake has a variety of advanced variables that can be set for each build, which you can list using ``cmake -LA`` (this is also helpful for debugging). If you choose not to specify a value for the ``CMAKE_INSTALL_PREFIX``, CMake will automatically look in the ``/usr/local`` directory. If you have installed Geant4 under your home directory, you will need to specify where it is installed. A full build can be done using:

.. code-block:: shell
		
   mkdir neutron_detection_simulation-build
   cd neutron_detection_simulation-build
   cmake -DCMAKE_INSTALL_PREFIX=/home/myusername/geant4-version-install /home/myusername/neutron_detection_simulation
   make
		
This is assuming both Geant4 and the Neutron detection simulation exist under your home directory.

Using ccmake to build the program
=================================
CCMake provides a GUI for the CMake process, and can make it clearer when CMake variables are set incorrectly. Running a full build using CCMake requires entering the directory you want to build in, running CCMake on the directory where the program is installed, and then generating the build files. The GUI window looks like this:

.. code-block:: shell
		
   CMAKE_BUILD_TYPE                 Debug                                                                                   
   CMAKE_INSTALL_PREFIX             /home/myusername/geant4-version-install                                                      
   Geant4_DIR                       /home/myusername/geant4-version-install/lib/Geant4-10.6.2

You can press enter to modify any of the variables, and the GUI will display the options. When finished, press 'c' twice to configure and 'g' once to generate the build files and the Makefile. A full build can be done using:

.. code-block:: shell
		
   mkdir neutron_detection_simulation-build
   cd neutron_detection_simulation-build
   ccmake /home/myusername/neutron_detection_simulation
   make

This is assuming you set your CMake variables properly inside of the CCMake GUI, and that this project is cloned in your home directory.
