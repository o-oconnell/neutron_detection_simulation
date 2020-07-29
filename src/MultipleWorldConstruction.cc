/**
 * @author Oisin O'Connell
 * @file MultipleWorldConstruction.cc
 * @date 7/20/20
 * @brief multiple world construction header file, when used allows us to
 * choose the world based on the input that we receive from the getInput
 * function in main, but by default we use a GTK window instead.
 */

#include "MultipleWorldConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

extern int AIR_SELECTED;
extern int SPACE_SELECTED;
extern int WATER_SELECTED;
extern int ARGON_SELECTED;
extern int HELIUM_SELECTED;

MultipleWorldConstruction::MultipleWorldConstruction() :
	G4VUserDetectorConstruction() {}

/** 
 * @brief constructs the world, empty world with logical volume based on
 * user-selected material
 */
G4VPhysicalVolume *MultipleWorldConstruction::Construct()
{
	G4NistManager *nist_mgr = G4NistManager::Instance();
	G4Material *world_material;

	if (AIR_SELECTED)
		world_material = nist_mgr->FindOrBuildMaterial("G4_AIR");
	else if (SPACE_SELECTED)
		world_material = nist_mgr->FindOrBuildMaterial("G4_Galactic");
	else if (WATER_SELECTED)
		world_material = nist_mgr->FindOrBuildMaterial("G4_WATER");
	else if (ARGON_SELECTED)
		world_material = nist_mgr->FindOrBuildMaterial("G4_Ar");
	else if (HELIUM_SELECTED)
		world_material = nist_mgr->FindOrBuildMaterial("G4_He");
	
	G4Box *world = new G4Box("World", 4.0*m, 1.0*m, 2.0*m);

	G4LogicalVolume *logical_world = new G4LogicalVolume(world,
							     world_material,
							     "world");
	G4VPhysicalVolume *physical_world = new G4PVPlacement(0, G4ThreeVector(),
							     logical_world,
							     "world",
							     0,
							     false,
							     0,
							     true);
	return physical_world;
}

