#include "NeutronActionInitialization.hh"
#include "NeutronPrimaryGeneratorAction.hh"
#include "NeutronRunAction.hh"

NeutronActionInitialization::NeutronActionInitialization() :
	G4VUserActionInitialization() {}

void NeutronActionInitialization::BuildForMaster() const
{


}

void NeutronActionInitialization::Build() const
{
	NeutronPrimaryGeneratorAction* npga = new NeutronPrimaryGeneratorAction;
	SetUserAction(npga);
	SetUserAction(new NeutronRunAction(npga));
}
