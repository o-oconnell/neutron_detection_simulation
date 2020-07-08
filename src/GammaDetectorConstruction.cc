#include "GammaDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

GammaDetectorConstruction::GammaDetectorConstruction() :
	G4VUserDetectorConstruction() {}
	
G4VPhysicalVolume *GammaDetectorConstruction::Construct()
{
	
	G4NistManager *nist_mgr = G4NistManager::Instance();
	
        G4Material *world_material = nist_mgr->FindOrBuildMaterial("G4_AIR");
	
	G4double world_hx = 4.0*m;
	G4double world_hy = 1.0*m;
	G4double world_hz = 2.0*m;

	G4Box *world = new G4Box("World", world_hx, world_hy, world_hz);
	
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

