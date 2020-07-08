#include "NeutronPrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

NeutronPrimaryGeneratorAction::NeutronPrimaryGeneratorAction() :
	G4VUserPrimaryGeneratorAction(),
	particle_gun(0)
{
	particle_gun = new G4ParticleGun(1);
	
	G4ParticleTable *particle_table = G4ParticleTable::GetParticleTable();
	G4String particle_name;
	G4ParticleDefinition *particle = particle_table->FindParticle(particle_name="neutron");

	particle_gun->SetParticleDefinition(particle);
	particle_gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	particle_gun->SetParticleEnergy(3.*MeV);
}

NeutronPrimaryGeneratorAction::~NeutronPrimaryGeneratorAction()
{
	delete particle_gun;
}

void NeutronPrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
	G4double environment_size_xy_axis = 2;
	
	G4double size = 0.3;
	G4double x0 = size * environment_size_xy_axis * (G4UniformRand()-0.5);
	G4double y0 = size * environment_size_xy_axis * (G4UniformRand()-0.5);
	G4double z0 = -0.5 * environment_size_xy_axis;
	
	particle_gun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
	
	particle_gun->GeneratePrimaryVertex(event);
}
