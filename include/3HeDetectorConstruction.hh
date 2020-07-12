
#ifndef _3HE_DETECTOR_CONSTRUCTION_H
#define _3HE_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class _3HeDetectorConstruction : public G4VUserDetectorConstruction {
public:
	_3HeDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
