/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 4HeDetectorConstruction.cc
 * @brief helium-4 container in an air world envelope detector construction 
 * file
 */

#include "4HeDetectorConstruction.hh"
#include "CounterSD.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

_4HeDetectorConstruction::_4HeDetectorConstruction() :
	G4VUserDetectorConstruction() {}

G4VPhysicalVolume *_4HeDetectorConstruction::Construct()
{
	G4NistManager *nist_mgr = G4NistManager::Instance();
	
        G4Material *world_material = nist_mgr->FindOrBuildMaterial("G4_AIR");
	
	G4double world_hx = 4.0*m;
	G4double world_hy = 4.0*m;
	G4double world_hz = 4.0*m;

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
       	G4double detector_hx = 3*m;
	G4double detector_hy = 1*m;
	G4double detector_hz = 1*m;
	G4Box *_4He_detector = new G4Box("4HeDetector",
					detector_hx,
					detector_hy,
					detector_hz);
	
	G4double atomicMass=4.002603*g/mole;
	G4Isotope* he4 = new G4Isotope("he4", 2, 4, atomicMass);
	G4Element* He4 = new G4Element("He4", "He4", 1);
	He4->AddIsotope(he4,100.*perCent);
	
	G4double pressure = 5*bar,
		temperature = 293*kelvin,
		molar_constant = CLHEP::Avogadro*CLHEP::k_Boltzmann,
		density = (atomicMass*pressure)/(temperature*molar_constant);
	
	G4Material* He4Gas = new G4Material("He4_gas", density,	1, kStateGas, temperature, pressure);
	He4Gas->AddElement(He4, 100.*perCent);

	G4LogicalVolume *logic_4He_detector
		= new G4LogicalVolume(_4He_detector,
				      He4Gas,
				      "4HeDetector");
	
	//add the sensitive detector to the logical volume
	CounterSD* sensitive = new CounterSD("4He");
	G4SDManager* sd_mgr = G4SDManager::GetSDMpointer();
	sd_mgr->AddNewDetector(sensitive);
	logic_4He_detector->SetSensitiveDetector(sensitive);

	G4PVPlacement *detector_placement =
		new G4PVPlacement(0,
				  G4ThreeVector(0, 50*cm, 0*cm),				  logic_4He_detector,
				  "4HeDetector",
				  logical_world, // parent volume
				  false,
				  0,
				  true); // check for overlaps

	return physical_world;
}

