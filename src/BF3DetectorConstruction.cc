/**
 * @author Oisin O'Connell
 * @date 7/28/2020
 * @file BF3DetectorConstruction.cc
 * @brief boron trifluoride container in a modifiable world envelope detector
 * construction file
 */
#include "BF3DetectorConstruction.hh"
#include "CounterSD.hh"
#include "GTKInput.hh"

#include "G4RotationMatrix.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

BF3DetectorConstruction::BF3DetectorConstruction() :
	G4VUserDetectorConstruction() {}

BF3DetectorConstruction::~BF3DetectorConstruction()
{ }

G4VPhysicalVolume *BF3DetectorConstruction::Construct()
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
	
	G4bool check_overlaps_root = true;
	G4bool check_overlaps_children = false;
	G4bool has_copies = false;
	G4int num_copies = 0;
	G4VPhysicalVolume *physical_world = new G4PVPlacement(0, // rotation
							      G4ThreeVector(), // translation relative to mother
							      logical_world, // logical volume
							      "world", // name
							      0, // parent logical volume
							      has_copies, // bool if there are multiple
							      num_copies, // number of copies
							      check_overlaps_root); // check overlaps

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
			  has_copies,
			  num_copies,
			  check_overlaps_children); // check for overlaps


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
			  has_copies,
			  num_copies,
			  check_overlaps_children); // check for overlaps

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
			  "Stainless steel endcap left",
			  logical_world, // parent volume
			  has_copies,
			  num_copies,
			  check_overlaps_children); // check for overlaps

	G4Tubs* BF3_detector =
		new G4Tubs("BF3tube", 0*cm, 200*cm, 4*m, 0, 360*deg);

	G4double atomicMass=10.0129370*g/mole;
	G4Isotope* b10 = new G4Isotope("b10", 2, 3, atomicMass);
	G4Element* B10 = new G4Element("B10", "B10", 1);
	B10->AddIsotope(b10,100.*perCent);
	
	G4double    pressure = 5*bar,
		temperature = 293*kelvin,
		molar_constant = CLHEP::Avogadro*CLHEP::k_Boltzmann,
		density = (atomicMass*pressure)/(temperature*molar_constant);

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
		new G4Material("Boron-10 Trifluoride",
			       bf3_density,
			       2,
			       kStateGas, //// the number of elements it contains
			       temperature,
			       pressure); 

	BF3->AddElement(B10, 1); // one boron atom
	BF3->AddElement(elFluorine, 3); // three fluorine atoms

	G4LogicalVolume *logic_BF3_detector
		= new G4LogicalVolume(BF3_detector,
				      BF3,
				      "BF3Detector");

	// add the sensitive detector to the logical volume
	CounterSD* sensitive = new CounterSD("BF3");
	G4SDManager* sd_mgr = G4SDManager::GetSDMpointer();
	sd_mgr->AddNewDetector(sensitive);
	logic_BF3_detector->SetSensitiveDetector(sensitive);

	G4VisAttributes *bf3_attrs =
		new G4VisAttributes(G4Colour(255., 0., 0.));
	bf3_attrs->SetForceSolid(true);
	logic_BF3_detector->SetVisAttributes(bf3_attrs);

	G4RotationMatrix *parallel = new G4RotationMatrix();
	parallel->rotateY(90.*deg);
	new G4PVPlacement(parallel,
			  G4ThreeVector(0, -30*cm, 0*cm),
			  logic_BF3_detector,
			  "BF3Detector",
			  logical_world, // parent volume
			  has_copies,
			  num_copies,
			  check_overlaps_children); // check for overlaps
	
	return physical_world;
}

