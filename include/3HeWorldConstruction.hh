/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 3HeWorldConstruction.hh
 * @brief helium-3 world envelope construction file. 
 */

#ifndef _3HE_WORLD_CONSTRUCTION_H
#define _3HE_WORLD_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class _3HeWorldConstruction : public G4VUserDetectorConstruction {
public:
	_3HeWorldConstruction();
	
	virtual G4VPhysicalVolume *Construct();
};

#endif
