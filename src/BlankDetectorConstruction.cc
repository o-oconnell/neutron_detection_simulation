/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file BF3DetectorConstruction.cc
 * @brief boron trifluoride container in a modifiable world envelope detector
 * construction file
 */
#include "BlankDetectorConstruction.hh"
#include "CounterSD.hh"
#include "GTKInput.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

BlankDetectorConstruction::BlankDetectorConstruction() :
	G4VUserDetectorConstruction() {}
	

G4VPhysicalVolume *BlankDetectorConstruction::Construct()
{
	G4NistManager *nist_mgr = G4NistManager::Instance();

	G4Material *world_material =
		nist_mgr->FindOrBuildMaterial(results->input->world_material);
	
	G4double world_hx = 4*m;
	G4double world_hy = 4*m;
	G4double world_hz = 4*m;

	G4Box *world = new G4Box("World", world_hx, world_hy, world_hz);

	G4LogicalVolume *logical_world = new G4LogicalVolume(world, // geometry
							     world_material, // material
							     "world"); // name
	G4VPhysicalVolume *physical_world = new G4PVPlacement(0, // rotation
							      G4ThreeVector(), // translation relative to mother
							      logical_world, // logical volume
							      "world", // name
							      0, // parent logical volume
							      false, // bool if there are multiple
							      0, // number of copies
							      true); // check overlaps
	return physical_world;
}

