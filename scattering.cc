#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "NeutronActionInitialization.hh"
#include "NeutronDetectorConstruction.hh"
#include "NeutronPrimaryGeneratorAction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QBBC.hh"

int main(int argc, char **argv)
{
  G4RunManager* runManager = new G4RunManager;

  // detector
  runManager->SetUserInitialization(new NeutronDetectorConstruction);

  // physics list
  G4VModularPhysicsList *physics_list =
	  new QBBC;
  physics_list->SetVerboseLevel(1);
  runManager->SetUserInitialization(physics_list);


  // how we are handling "run" and "event" actions
  runManager->SetUserInitialization(new NeutronActionInitialization);

  runManager->Initialize();

  G4VisManager *vis_manager = new G4VisExecutive;
  vis_manager->Initialize();
  
  G4UImanager* UI = G4UImanager::GetUIpointer();
  // UI->ApplyCommand("/run/verbose 1");
  // UI->ApplyCommand("/event/verbose 1");
  // UI->ApplyCommand("/tracking/verbose 1");
  UI->ApplyCommand("/control/execute init_vis.mac");

  G4UIExecutive *ui = new G4UIExecutive(argc, argv);
  ui->SessionStart();
  
  runManager->BeamOn(1);

  delete runManager;
  return 0;
}
