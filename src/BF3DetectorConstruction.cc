#include "BF3DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

BF3DetectorConstruction::BF3DetectorConstruction() :
	G4VUserDetectorConstruction() {}
	

G4VPhysicalVolume *BF3DetectorConstruction::Construct()
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
       	G4double detector_hx = 50.0*cm;
	G4double detector_hy = 50.0*cm;
	G4double detector_hz = 50.0*cm;
	G4Box *BF3_detector = new G4Box("BF3Detector",
					detector_hx,
					detector_hy,
					detector_hz);


	// material definition for boron trifluoride, which we are
	// using as our detection material
	G4double b_molar_mass = 10.81*g/mole;
	G4Element *elBoron
		= new G4Element("Boron", "B", 5, b_molar_mass);

	G4double f_molar_mass = 19*g/mole;
	G4Element *elFluorine
		= new G4Element("Fluorine", "F", 9, f_molar_mass);

	G4double bf3_density = 0.00276*g/cm3; // anhydrous gas density
	G4Material *BF3 =
		new G4Material("Boron Trifluoride",
			       bf3_density,
			       2); // the number of elements it contains

	BF3->AddElement(elBoron, 1); // one boron atom
	BF3->AddElement(elFluorine, 3); // three fluorine atoms

	G4LogicalVolume *logic_BF3_detector
		= new G4LogicalVolume(BF3_detector,
				      BF3,
				      "BF3Detector");
	
	G4PVPlacement *detector_placement = new G4PVPlacement(0,
							      G4ThreeVector(0, 50*cm, 0*cm),
							      logic_BF3_detector,
							      "BF3Detector",
							      logical_world, // parent volume
							      false,
							      0,
							      true); // check for overlaps
							      


	
	
	return physical_world;
}

