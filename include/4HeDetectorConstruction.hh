
#ifndef _4HE_DETECTOR_CONSTRUCTION_H
#define _4HE_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class _4HeDetectorConstruction : public G4VUserDetectorConstruction {
public:
	_4HeDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
