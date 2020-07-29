/**
 * @author Oisin O'Connell
 * @file NeutronPrimaryGeneratorAction.cc
 * @date 7/20/20
 * @brief constructs the particle gun and initializes the particle generation
 * when used as a user action in the NeutronActionInitialization class
 */

#include "NeutronPrimaryGeneratorAction.hh"
#include "GTKInput.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

/**
 * @brief computes the desired primary particle properties, initializes the
 * neutron gun so that the Event class can access it.
 */
NeutronPrimaryGeneratorAction::NeutronPrimaryGeneratorAction() :
	G4VUserPrimaryGeneratorAction(),
	particle_gun(0)
{
	particle_gun = new G4ParticleGun(1);
	
	G4ParticleTable *particle_table = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particle_table->FindParticle("neutron");

	particle_gun->SetParticleDefinition(particle);
	particle_gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

	// approximate standard thermal neutron energy
	std::cout << "PARTICLE GUN ENERGY:\n";
	std::cout << results->input->neutron_energy << '\n';
	particle_gun->SetParticleEnergy(results->input->neutron_energy*eV);
}

NeutronPrimaryGeneratorAction::~NeutronPrimaryGeneratorAction()
{
	delete particle_gun;
}

/**
 * @brief used by the NeutronRunAction class to get the particle gun
 */
G4ParticleGun* NeutronPrimaryGeneratorAction::GetParticleGun()
{
	return particle_gun;
}

/**
 * @brief called for the number of times we specify using /run/BeamOn
 */
void NeutronPrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
	// currently all of our particles are generated in somewhat random
	// locations near the back corner of the world (which provides us
	// with our coordinate system)
	// since our locations are random some will be outside of the world
	G4double environment_size_xy_axis = 2*m;


	G4double x0 = environment_size_xy_axis * (G4UniformRand()-0.5) ;
	G4double y0 = environment_size_xy_axis * (G4UniformRand()-0.5) ;
	G4double z0 = environment_size_xy_axis * -1 ;

	std::cout << "INITIAL PARTICLE POSITION: " << x0 << " " << y0 << " " << z0 << '\n';
	particle_gun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
	
	particle_gun->GeneratePrimaryVertex(event);
}
