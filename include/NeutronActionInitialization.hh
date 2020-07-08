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
