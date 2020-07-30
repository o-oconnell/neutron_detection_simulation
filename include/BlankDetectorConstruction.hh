/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file BlankDetectorConstruction.hh
 * @brief header file for a blank world which solely contains the world
 * material that has been selected in the GTK window.
 */

#ifndef BLANK_DETECTOR_CONSTRUCTION_H
#define BLANK_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class BlankDetectorConstruction : public G4VUserDetectorConstruction {
public:
	BlankDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
