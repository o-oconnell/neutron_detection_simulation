#include "NeutronActionInitialization.hh"
#include "NeutronPrimaryGeneratorAction.hh"

NeutronActionInitialization::NeutronActionInitialization() :
	G4VUserActionInitialization() {}

void NeutronActionInitialization::BuildForMaster() const
{


}

void NeutronActionInitialization::Build() const
{
	SetUserAction(new NeutronPrimaryGeneratorAction);
}
