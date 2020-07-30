#include "NeutronSteppingAction.hh"
#include "GTKInput.hh"


#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

NeutronSteppingAction::NeutronSteppingAction()
: G4UserSteppingAction()
{}

void NeutronSteppingAction::UserSteppingAction(const G4Step* step)
{      
	G4double energy_deposit = step->GetTotalEnergyDeposit();
	results->output->edep_world += energy_deposit;
}


