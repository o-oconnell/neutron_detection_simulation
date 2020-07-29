/**
 * @author Oisin O'Connell
 * @file NeutronActionInitialization.hh
 * @date 7/20/20
 * @brief neutron action initialization header file, where we initialize
 * user actions such as defining the behavior for events and runs. Currently
 * we are only defining user actions for the primary generator action and the
 * run action.
 */

#ifndef NEUTRON_ACTION_INITIALIZATION_H
#define NEUTRON_ACTION_INITIALIZATION_H

#include "G4VUserActionInitialization.hh"

class NeutronActionInitialization : public G4VUserActionInitialization
{
public:
	NeutronActionInitialization();

	// must be overriden, first defined in class G4VUserActionInitialization
	virtual void BuildForMaster() const;
	virtual void Build() const;
};



#endif
