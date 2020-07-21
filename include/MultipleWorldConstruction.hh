/**
 * @author Oisin O'Connell
 * @file MultipleWorldConstruction.hh
 * @date 7/20/20
 * @brief multiple world construction header file, construction
 * for worlds that are menu-based
 */

#ifndef MULTIPLE_WORLD_CONSTRUCTION_H
#define MULTIPLE_WORLD_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class MultipleWorldConstruction : public G4VUserDetectorConstruction {
public:
	MultipleWorldConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
