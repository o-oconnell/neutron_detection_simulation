
#ifndef GAMMA_DETECTOR_CONSTRUCTION_H
#define GAMMA_DETECTOR_CONSTRUCTION_H



#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class GammaDetectorConstruction : public G4VUserDetectorConstruction {
public:
	GammaDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
