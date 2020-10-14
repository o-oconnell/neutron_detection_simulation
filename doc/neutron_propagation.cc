/**
 * @author Oisin O'Connell
 * @file neutron_detection.cc
 * @date 7/20/20
 * @brief main program for neutron detection presentation
 */

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "NeutronActionInitialization.hh"
#include "4HeDetectorConstruction.hh"
#include "3HeDetectorConstruction.hh"
#include "BF3DetectorConstruction.hh"
#include "NeutronPrimaryGeneratorAction.hh"

#include "G4ThermalNeutrons.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT_HP.hh"
#include "FTFP_BERT_HP.hh"
#include "QBBC.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysicsLEND.hh"
#include "G4HadronPhysicsShieldingLEND.hh"
#include "GTKInput.hh"
#include "GTKOutput.hh"

#include <thread>
#include <chrono>

/**
 * @brief creates the user interface (batch), visualization manager (OpenGL,
 * which we specify in the macro files), run manager, and mandatory
 * user initializations.
 */
int main(int argc, char **argv)
{
	create_data_entry_window();

	//	getInput();
	
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
	switch (results->output->detector_material) {
	case (Detector::HE4):
		runManager->SetUserInitialization(new _4HeDetectorConstruction());
		break;
	case(Detector::HE3):
		runManager->SetUserInitialization(new _3HeDetectorConstruction());

		break;
	case(Detector::BF3):
		runManager->SetUserInitialization(new BF3DetectorConstruction());
		break;
	default:
		exit(1);
	}

	// physics list
	G4VModularPhysicsList *physics_list =
		new FTFP_BERT_HP;
	
	// physics_list->RegisterPhysics(new G4EmStandardPhysics(0));
	// physics_list->RegisterPhysics(new G4HadronElasticPhysicsLEND(0));
	// physics_list->RegisterPhysics(new G4HadronPhysicsShieldingLEND(0));
	// physics_list->RegisterPhysics(new G4ThermalNeutrons(0));

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
	UI_manager->ApplyCommand("/control/execute run1_thermal_neutrons.mac");
	runManager->BeamOn(results->input->num_events);
	ui->SessionStart();

	delete ui;
	delete vis_manager;
	delete runManager;
	
	// create the gtk window we use to output our results
	create_output_window();
	return 0;
}
