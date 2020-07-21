/**
 * @author Oisin O'Connell
 * @file neutron_detection.cc
 * @date 7/20/20
 * @brief main program for neutron detection presentation
 */

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "MultipleWorldConstruction.hh"
#include "global_materials.hh"
#include "NeutronActionInitialization.hh"
#include "4HeDetectorConstruction.hh"
#include "3HeDetectorConstruction.hh"
#include "3HeWorldConstruction.hh"
#include "BF3DetectorConstruction.hh"
#include "NeutronPrimaryGeneratorAction.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT_HP.hh"

#include <thread>
#include <chrono>

/**
 * @brief displays the menu and receives input.
 */
void getInput();

/**
 * @brief creates the user interface (batch), visualization manager (OpenGL,
 * which we specify in the macro files), run manager, and mandatory
 * user initializations.
 */
int main(int argc, char **argv)
{
	getInput();
	
	// initialize the UI executive, which keeps our GUI session running
	// and prevents it from immediately
	// opening and closing
	// (this is for the GUI, not the TUI)
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	// controls program, we pass it our derived detector
	// object (NeutronDetectorConstruction),
	// the physics processes (physics_list),
	// and the "action initialization" which describes the
	// initial particles that we will create
	G4RunManager* runManager = new G4RunManager;
	
	// detector
	runManager->SetUserInitialization(new MultipleWorldConstruction);

	// physics list
	G4VModularPhysicsList *physics_list =
		new QGSP_BERT_HP;
	physics_list->SetVerboseLevel(1);
	
	// adding the physics list to the run manager
	runManager->SetUserInitialization(physics_list);
	
	// add user actions to occur when the simulation is run and
	// at the beginning of an a run
	runManager->SetUserInitialization(new NeutronActionInitialization());
	
	// initializes the run manager with everything we have passed to it
	runManager->Initialize();
  
	// visualization manager. we are only using OpenGL, but the
	// G4VisExecutive derived class can handle many more
	G4VisManager *vis_manager = new G4VisExecutive;
	vis_manager->Initialize();

	// UI pointer which allows us to interface with the interactive
	// session that Geant4 sets up for us
	G4UImanager* UI_manager = G4UImanager::GetUIpointer();
	UI_manager->ApplyCommand("/run/verbose 1");
	UI_manager->ApplyCommand("/event/verbose 1");
	UI_manager->ApplyCommand("/tracking/verbose 1");

	UI_manager->ApplyCommand("/control/execute init_vis.mac");
	//runManager->BeamOn(1000);
	ui->SessionStart();	

	// actually runs the simulation. the number passed to
	// beamOn is the amount of runs we want to do.
	delete ui;
	
	delete vis_manager;
	delete runManager;
	return 0;
}

void getInput()
{
	std::cout << "Enter the propagation material:\n";
	std::cout << "1. Space (G4galactic)\n";
	std::cout << "2. Water\n";
	std::cout << "3. Air\n";
	std::cout << "4. Argon\n";
	std::cout << "5. Helium\n";

	int material = -1;
	G4cin >> material;
	
	switch (material) {
	case(1):
		SPACE_SELECTED = 1;
		break;
	case(2):
		WATER_SELECTED = 1;
		break;
	case(3):
		AIR_SELECTED = 1;
		break;
	case(4):
		ARGON_SELECTED = 1;
		break;
	case(5):
		HELIUM_SELECTED = 1;
		break;
	default:
		std::cout << "Unrecognized option. Exiting.\n";
		exit(1);
		break;
	}
}
