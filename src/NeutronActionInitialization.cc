/**
 * @author Oisin O'Connell
 * @file NeutronActionInitialization.cc
 * @date 7/20/20
 * @brief neutron action initialization header file, where we initialize
 * user actions such as defining the behavior for events and runs. Currently
 * we are only defining user actions for the primary generator action and the
 * run action.
 */

#include "NeutronActionInitialization.hh"
#include "NeutronPrimaryGeneratorAction.hh"
#include "NeutronSteppingAction.hh"

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
	SetUserAction(new NeutronSteppingAction());
}
