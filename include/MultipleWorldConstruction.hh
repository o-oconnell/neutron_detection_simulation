/**
 * @author Oisin O'Connell
 * @file MultipleWorldConstruction.hh
 * @date 7/20/20
 * @brief multiple world construction header file, when used allows us to
 * choose the world based on the input that we receive from the getInput
 * function in main, but by default we use a GTK window instead.
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
