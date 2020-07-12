
#ifndef BF3_DETECTOR_CONSTRUCTION_H
#define BF3_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class BF3DetectorConstruction : public G4VUserDetectorConstruction {
public:
	BF3DetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
