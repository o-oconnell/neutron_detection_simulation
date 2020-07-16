#include "CounterSD.hh"

CounterSD::CounterSD(G4String id) :
	G4VSensitiveDetector(id)
{}

void CounterSD::Initialize(G4HCofThisEvent *HCE) {}

G4bool CounterSD::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
	auto track = step->GetTrack();
	
	G4double kinetic_energy = track->GetKineticEnergy();
	G4AnalysisManager *analysis_mgr = G4AnalysisManager::Instance();

	G4ParticleDefinition *particle_definition
		= track->GetDefinition();
	if (particle_definition == G4Neutron::Neutron())
		analysis_mgr->FillH1(1, kinetic_energy);

	return true;
}
