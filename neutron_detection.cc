#include "G4RunManager.hh"
#include "G4UImanager.hh"

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
#include "QBBC.hh"

int main(int argc, char **argv)
{
	// controls program, we pass it our derived detector
	// object (NeutronDetectorConstruction),
	// the physics processes (physics_list),
	// and the "action initialization" which describes the
	// initial particles that we will create
	G4RunManager* runManager = new G4RunManager;
	
	// physics list
	G4VModularPhysicsList *physics_list =
		new QBBC;
	physics_list->SetVerboseLevel(1);

	// adding the physics list to the run manager
	runManager->SetUserInitialization(physics_list);

	// detector
	runManager->SetUserInitialization(new _3HeWorldConstruction);

	// how we are handling "run" and "event" actions
	runManager->SetUserInitialization(new NeutronActionInitialization);

	// initializes the run manager with everything we have passed to it
	runManager->Initialize();
  
	// visualization manager. we are only using OpenGL, but the
	// G4VisExecutive derived class can handle many more
	G4VisManager *vis_manager = new G4VisExecutive;
	vis_manager->Initialize();

	// UI pointer which allows us to interface with the interactive
	// session that Geant4 sets up for us
	G4UImanager* UI_manager = G4UImanager::GetUIpointer();
	UI_manager->ApplyCommand("/control/execute init_vis.mac");

	// keeps our GUI session running, prevents it from immediately
	// opening and closing
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	ui->SessionStart();

	runManager->BeamOn(100);
	delete ui;

	// actually runs the simulation. the number passed to
	// beamOn is the amount of runs we want to do.
	

	delete vis_manager;
	delete runManager;
	return 0;
}