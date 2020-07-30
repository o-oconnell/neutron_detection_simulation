#ifndef NEUTRON_STEPPING_ACTION_H
#define NEUTRON_STEPPING_ACTION_H

#include "G4Event.hh"
#include "G4UserSteppingAction.hh"

class NeutronSteppingAction : public G4UserSteppingAction
{
  public:
	NeutronSteppingAction();
	
	virtual void UserSteppingAction(const G4Step* step);
};

#endif
