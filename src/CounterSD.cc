/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file CounterSD.cc
 * @brief sensitive detector definition file. We attach a sensitive
 * detector to a logical volume in order to obtain energy deposition and other
 * statistics for the volume.
 */

#include "CounterSD.hh"
#include "GTKInput.hh"

CounterSD::CounterSD(G4String id) :
	G4VSensitiveDetector(id)
{}

void CounterSD::Initialize(G4HCofThisEvent *HCE) {}

G4bool CounterSD::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
	auto track = step->GetTrack();
	
	G4double energy_deposit = step->GetPreStepPoint()->GetKineticEnergy()
		- step->GetPostStepPoint()->GetKineticEnergy();

	if (step->IsFirstStepInVolume()) {
		results->output->edep_target += energy_deposit;
		results->output->nparticle_target++;
	}
	
	G4AnalysisManager *analysis_mgr = G4AnalysisManager::Instance();
	G4ParticleDefinition *particle_definition
		= track->GetDefinition();
	
	if (particle_definition->GetParticleName() == "neutron") {
		if (step->IsFirstStepInVolume()) 
			results->output->nneutron_target++;
	}
	
	return true;
}
