/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 4HeDetectorConstruction.cc
 * @brief helium-4 container in an air world envelope detector construction 
 * file
 */

#include "4HeDetectorConstruction.hh"

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
	G4Box *_4He_detector = new G4Box("4HeDetector",
					detector_hx,
					detector_hy,
					detector_hz);

	// 4He definition
	G4Isotope *helium_4_iso =
		new G4Isotope("Helium-4",
			      2, // protons
			      4, // nucleons (protons + neutrons)
			      4.002602*g/mole); // atomic mass
	
	G4Element *helium_4_element =
		new G4Element("Helium-4",
			      "4He",
			      1); // number of isotopes
	helium_4_element->AddIsotope(helium_4_iso, 100*perCent);

	// density obviously varies with temperature, so here we define
	// the temperature of our gas-filled chamber
	// and calculate the density of our material
	
	// g/mol, m_sub_u molar constant
	G4double grams_per_mol = CLHEP::Avogadro*CLHEP::k_Boltzmann; 

	G4double helium_4_density =
		(4.002602*g/mole * 1.51988*bar)/(293*kelvin*grams_per_mol);

	G4State helium_gas_state = kStateGas;
	G4Material *helium_4_material
		= new G4Material("4He",
				 helium_4_density,
				 1, // number of components
				 helium_gas_state, // the state of the material (gas here)
				 293*kelvin, // temperature
				 1.51988*bar); // pressure

	G4LogicalVolume *logic_4He_detector
		= new G4LogicalVolume(_4He_detector,
				      helium_4_material,
				      "4HeDetector");
	
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

