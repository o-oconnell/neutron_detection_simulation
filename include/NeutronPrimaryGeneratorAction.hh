#ifndef NEUTRON_PRIMARY_GENERATOR_ACTION_H
#define NEUTRON_PRIMARY_GENERATOR_ACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


class G4ParticleGun;
class G4Event;
class G4Box;

class NeutronPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
private:
	G4ParticleGun *particle_gun;
public:
	NeutronPrimaryGeneratorAction();
	virtual ~NeutronPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

	G4ParticleGun* GetParticleGun();
};

#endif
