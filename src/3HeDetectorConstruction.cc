/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 3HeDetectorConstruction.cc
 * @brief helium-3 detector construction file. Air envelope with 3He
 * container.
 */

#include "3HeDetectorConstruction.hh"
#include "CounterSD.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

_3HeDetectorConstruction::_3HeDetectorConstruction() :
	G4VUserDetectorConstruction() {}

G4VPhysicalVolume *_3HeDetectorConstruction::Construct()
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
	G4Box *_3He_detector = new G4Box("3HeDetector",
					detector_hx,
					detector_hy,
					detector_hz);
	
	// // 3He and 4He definitions:
	// G4Isotope *helium_3_iso =
	// 	new G4Isotope("Helium-3",
	// 		      2, // protons
	// 		      3, // nucleons (protons + neutrons)
	// 		      3.016*g/mole); // atomic mass
	
	// G4Element *helium_3_element =
	// 	new G4Element("Helium-3",
	// 		      "3He",
	// 		      1); // number  of isotopes
	
	// helium_3_element->AddIsotope(helium_3_iso, 100.*perCent);

	// // density obviously varies with temperature, so here we define
	// // the temperature of our gas-filled chamber
	// // and calculate the density of our material
	
	// // g/mol, m_sub_u molar constant
	// G4double grams_per_mol = CLHEP::Avogadro*CLHEP::k_Boltzmann; 

	// // density calculation, pressure and
	// // temperature taken from geant4 forum samples
	// // as reasonable for a gas-filled
	// // chamber filled with 3he in a water medium
	// G4double helium_3_density =
	// 	(3.016*g/mole * 1.51988*bar)/(293*kelvin*grams_per_mol);

	// G4State helium_gas_state = kStateGas;
	// G4Material *helium_3_material
	// 	= new G4Material("3He",
	// 			 helium_3_density,
	// 			 1, // number of components
	// 			 helium_gas_state, // the state of the material (gas here)
	// 			 293*kelvin, // temperature
	// 			 1.51988*bar); // pressure

	// from the geant4 forum: https://geant4-forum.web.cern.ch/t/helium-3-neutron-capture-cross-section-doesnt-seem-right/2544
	//He3 element
	G4double atomicMass=3.016*g/mole;
	G4Isotope* he3 = new G4Isotope("he3", 2, 3, atomicMass);
	G4Element* He3 = new G4Element("He3", "He3", 1);
	He3->AddIsotope(he3,100.*perCent);
	
	//He3 gas
	G4double    pressure = 5*bar,
		temperature = 293*kelvin,
		molar_constant = CLHEP::Avogadro*CLHEP::k_Boltzmann,
		density = (atomicMass*pressure)/(temperature*molar_constant);
	G4Material* He3Gas = new G4Material("He3_gas", density,	1, kStateGas, temperature, pressure);
	He3Gas->AddElement(He3, 100.*perCent);


	G4LogicalVolume *logic_3He_detector
		= new G4LogicalVolume(_3He_detector,
				      He3Gas,
				      "3HeDetector");

	G4VisAttributes *helium_attrs =
		new G4VisAttributes(G4Colour(255., 0., 0.));
	logic_3He_detector->SetVisAttributes(helium_attrs);
	
	//add the sensitive detector to the logical volume
	CounterSD* sensitive = new CounterSD("3He");
	G4SDManager* sd_mgr = G4SDManager::GetSDMpointer();
	sd_mgr->AddNewDetector(sensitive);
	logic_3He_detector->SetSensitiveDetector(sensitive);

	G4double case_hx = 4*m;
	G4double case_hy = 2*m;
	G4double case_hz = 2*m;
	G4Box *casing_box = new G4Box("Casing",
				      case_hx,
				      case_hy,
				      case_hz);
	
	G4Material *casing_material
		= nist_mgr->FindOrBuildMaterial("G4_STAINLESS-STEEL");
	
	G4LogicalVolume *logic_casing =
		new G4LogicalVolume(casing_box,
				    casing_material,
				    "Casing");
	
	new G4PVPlacement(0,
			  G4ThreeVector(0, 50*cm, 0*cm),
			  logic_casing,
			  "Casing",
			  logical_world, // parent volume
			  false, // multiple volumes
			  0, // amount of multiple volumes if any
			  true); // check for overlaps

	new G4PVPlacement(0,
			  G4ThreeVector(0, 50*cm, 0*cm),
			  logic_3He_detector,
			  "3HeDetector",
			  logic_casing, // parent volume
			  false, // multiple volumes
			  0, // amount of multiple volumes if any
			  true); // check for overlaps
	
	return physical_world;
}

