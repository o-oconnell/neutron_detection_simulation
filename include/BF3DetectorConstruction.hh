/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file BF3DetectorConstruction.hh
 * @brief boron trifluoride container in a modifiable world envelope detector
 * construction header file
 */

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
