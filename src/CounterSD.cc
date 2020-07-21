#include "CounterSD.hh"

CounterSD::CounterSD(G4String id) :
	G4VSensitiveDetector(id)
{}

void CounterSD::Initialize(G4HCofThisEvent *HCE) {}

G4bool CounterSD::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
	auto track = step->GetTrack();
	
	//	G4double energy_deposit = track->GetKineticEnergy();

	G4double energy_deposit = step->GetPreStepPoint()->GetKineticEnergy()
		- step->GetPostStepPoint()->GetKineticEnergy();
	G4AnalysisManager *analysis_mgr = G4AnalysisManager::Instance();

	G4ParticleDefinition *particle_definition
		= track->GetDefinition();
	
	if (particle_definition->GetParticleName() == "neutron"
	    && energy_deposit > 1) {
		analysis_mgr->FillH1(1, energy_deposit);
		G4cout<< "FOUND THE NEUTRON. DEPOSIT: " << energy_deposit << '\n';
	}
	

	return true;
}
