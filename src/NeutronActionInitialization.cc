/**
 * @author Oisin O'Connell
 * @file NeutronActionInitialization.hh
 * @date 7/20/20
 * @brief Action initialization file, where we add our user actions
 */

#include "NeutronActionInitialization.hh"
#include "NeutronPrimaryGeneratorAction.hh"
#include "NeutronRunAction.hh"

NeutronActionInitialization::NeutronActionInitialization() :
	G4VUserActionInitialization() {}

void NeutronActionInitialization::BuildForMaster() const
{


}

/**
 * @brief adds our user actions to a non-multithreaded run manager.
 * */
void NeutronActionInitialization::Build() const
{
	NeutronPrimaryGeneratorAction* npga = new NeutronPrimaryGeneratorAction;
	SetUserAction(npga);
	SetUserAction(new NeutronRunAction(npga));
}
