
#ifndef NEUTRON_DETECTOR_CONSTRUCTION_H
#define NEUTRON_DETECTOR_CONSTRUCTION_H



#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class NeutronDetectorConstruction : public G4VUserDetectorConstruction {
public:
	NeutronDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
