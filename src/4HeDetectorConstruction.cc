/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file 4HeDetectorConstruction.cc
 * @brief helium-4 container in an air world envelope detector construction 
 * file
 */

#include "4HeDetectorConstruction.hh"
#include "CounterSD.hh"

#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
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
		G4Tubs *casing
		= new G4Tubs("Stainless steel casing",
			     200*cm, 201*cm, 3.9*m, 0, 360*deg);
	
	G4LogicalVolume *logic_casing
		= new G4LogicalVolume(casing,
				      nist_mgr->FindOrBuildMaterial("G4_STAINLESS-STEEL"),
				      "Stainless steel casing");

	G4VisAttributes *casing_attrs =
		new G4VisAttributes(G4Colour(255., 255., 0.));
	casing_attrs->SetForceSolid(true);
	casing_attrs->SetForceWireframe(true);
	logic_casing->SetVisAttributes(casing_attrs);

	
	G4RotationMatrix *casing_rot = new G4RotationMatrix();
	casing_rot->rotateY(90.*deg);
	new G4PVPlacement(casing_rot,
			  G4ThreeVector(0, -30*cm, 0*cm),
			  logic_casing,
			  "Stainless steel casing",
			  logical_world, // parent volume
			  false,
			  0,
			  false ); // check for overlaps


	G4Tubs *endcap_right
		= new G4Tubs("Right endcap",
			     0*cm, 201*cm, 0.1*m, 0, 360*deg);
	
	G4LogicalVolume *logic_endcap_right
		= new G4LogicalVolume(endcap_right,
				      nist_mgr->FindOrBuildMaterial("G4_STAINLESS-STEEL"),
				      "Stainless steel endcap_right");

	G4VisAttributes *endcap_right_attrs =
		new G4VisAttributes(G4Colour(100., 233., 255.));
	endcap_right_attrs->SetForceSolid(true);
	logic_endcap_right->SetVisAttributes(endcap_right_attrs);

	G4RotationMatrix *endcap_right_rot = new G4RotationMatrix();
	endcap_right_rot->rotateY(90.*deg);
	new G4PVPlacement(endcap_right_rot,
			  G4ThreeVector(-4*m, -30*cm, 0*cm),
			  logic_endcap_right,
			  "Stainless steel endcap right",
			  logical_world, // parent volume
			  false,
			  0,
			  false); // check for overlaps

	G4Tubs *endcap_left
		= new G4Tubs("Right endcap",
			     0*cm, 201*cm, 0.1*m, 0, 360*deg);
	
	G4LogicalVolume *logic_endcap_left
		= new G4LogicalVolume(endcap_left,
				      nist_mgr->FindOrBuildMaterial("G4_STAINLESS-STEEL"),
				      "Stainless steel endcap_left");

	G4VisAttributes *endcap_left_attrs =
		new G4VisAttributes(G4Colour(100., 233., 255.));
	endcap_left_attrs->SetForceSolid(true);
	logic_endcap_left->SetVisAttributes(endcap_left_attrs);

	G4RotationMatrix *endcap_left_rot = new G4RotationMatrix();
	endcap_left_rot->rotateY(90.*deg);
	new G4PVPlacement(endcap_left_rot,
			  G4ThreeVector(4*m, -30*cm, 0*cm),
			  logic_endcap_left,
			  "Stainless steel endcap right",
			  logical_world, // parent volume
			  false,
			  0,
			  false); // check for overlaps


	
       	// G4double detector_hx = 3*m;
	// G4double detector_hy = 1*m;
	// G4double detector_hz = 1*m;
	// G4Box *_4He_detector = new G4Box("4HeDetector",
	// 				detector_hx,
	// 				detector_hy,
	// 				detector_hz);

	G4Tubs* _4He_detector =
		new G4Tubs("3Hetube", 0*cm, 200*cm, 4*m, 0, 360*deg);
	
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

	G4RotationMatrix *parallel = new G4RotationMatrix();
	parallel->rotateY(90.*deg);
	G4PVPlacement *detector_placement =
		new G4PVPlacement(parallel,
				  G4ThreeVector(0, -30*cm, 0*cm),
				  logic_4He_detector,
				  "4HeDetector",
				  logical_world, // parent volume
				  false,
				  0,
				  true); // check for overlaps

	return physical_world;
}

