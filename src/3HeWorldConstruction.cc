/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 3HeWorldConstruction.cc
 * @brief helium-3 world envelope construction file. 
 */

#include "3HeWorldConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

_3HeWorldConstruction::_3HeWorldConstruction() :
	G4VUserDetectorConstruction() {}

G4VPhysicalVolume *_3HeWorldConstruction::Construct()
{
	// 3He definition:
	G4Isotope *helium_3_iso =
		new G4Isotope("Helium-3",
			      2, // protons
			      3, // nucleons (protons + neutrons)
			      3.016*g/mole); // atomic mass
	
	G4Element *helium_3_element =
		new G4Element("Helium-3",
			      "3He",
			      1); // number of isotopes
	helium_3_element->AddIsotope(helium_3_iso, 100*perCent);

	// density obviously varies with temperature, so here we define
	// the temperature of our gas-filled chamber
	// and calculate the density of our material
	
	// g/mol, m_sub_u molar constant
	G4double grams_per_mol = CLHEP::Avogadro*CLHEP::k_Boltzmann; 

	// density calculation, pressure and
	G4double helium_3_density =
		(3.016*g/mole * 1.51988*bar)/(293*kelvin*grams_per_mol);

	G4State helium_gas_state = kStateGas;

	G4NistManager *nist_mgr = G4NistManager::Instance();
	
	G4Material *helium_3_material = //nist_mgr->FindOrBuildMaterial("G4_AIR");
		 new G4Material("3He",
				 helium_3_density,
				 1, // number of components
				 helium_gas_state, // the state of the material (gas here)
				 293*kelvin, // temperature
				 1.51988*bar); // pressure
	
	G4double world_hx = 4.0*m;
	G4double world_hy = 1.0*m;
	G4double world_hz = 2.0*m;

	G4Box *world = new G4Box("World", world_hx, world_hy, world_hz);

	G4LogicalVolume *logical_world = new G4LogicalVolume(world,
							     helium_3_material,
							     "world");
	
	G4VPhysicalVolume *physical_world = new G4PVPlacement(0, G4ThreeVector(),
							      logical_world,
							      "world",
							      0, // parent vol
							      false,
							      0,
							      true); // check for overlaps
	
	return physical_world;
}

