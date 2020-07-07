#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserActionInitialization.hh"
#include "QBBC.hh"

int main()
{
  G4RunManager* runManager = new G4RunManager;

  // detector
  runManager->SetUserInitialization(new GammaDetectorConstruction);

  // physics list
  G4VModularPhysicsList physics_list =
	  new QBBC;
  physics_list->SetVerboseLevel(1);
  runManager->SetUserInitialization(physics_list);

  // how we are handling "run" and "event" actions
  runManager->SetUserInitialization(new GammaActionInitialization);

  runManager->Initialize();

  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  runManager->BeamOn(1);

  delete runManager;
  return 0;
}
