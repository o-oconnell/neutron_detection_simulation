#ifndef GAMMA_ACTION_INITIALIZATION_H
#define GAMMA_ACTION_INITIALIZATION_H

#include "G4VUserActionInitialization.hh"

class GammaActionInitialization : public G4VUserActionInitialization
{
public:
	GammaActionInitialization();

	// must be overriden, first defined in class G4VUserActionInitialization
	virtual void BuildForMaster const;
	virtual void Build() const;
}



#endif
