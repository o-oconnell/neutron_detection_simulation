/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file NeutronRunAction.cc
 * @brief Run user action file, allows us to define what should
 * occur before and after a run. Currently being used to open and close
 * the histogram if the user turns it on.
 */

#include "NeutronRunAction.hh"
#include "HistogramsAnalysisManager.hh"

// initialize our primary generator action with the existing
// pga, which will allow us to get the primary particle of the sim
NeutronRunAction::NeutronRunAction(NeutronPrimaryGeneratorAction* pga) :
	G4UserRunAction(),
	fPrimaryGeneratorAction(pga),
	fRun(NULL),
	fHAM(NULL)
{
	fHAM = new HistogramsAnalysisManager;
}

NeutronRunAction::~NeutronRunAction()
{
	delete fHAM;
}

// create and return a heap-allocated run,
// which is simply a container of events that occur in the simulation
G4Run* NeutronRunAction::GenerateRun()
{
	fRun = new G4Run();
	return fRun;
}

// called at the beginning of a run (when we call
// beamOn from the run manager directly or when
// it is called via macro)
// essentially the "begin" and "end"
// functions set the primary particle and open/close the file
void NeutronRunAction::BeginOfRunAction(const G4Run* run)
{
	// G4ParticleDefinition* particle = fPrimaryGeneratorAction
	// 	->GetParticleGun()
	// 	->GetParticleDefinition();
	
	// G4double energy = fPrimaryGeneratorAction
	// 	->GetParticleGun()
	// 	->GetParticleEnergy();
	
	// // open the file for our analysis manager,
	// // this file is written to with the neutron energy spectrum
	// // when we call the macro
	// // /analysis/h1/set bins min_energy max_energy
	// // but otherwise we do not write anything
	// G4AnalysisManager *analysis_mgr = G4AnalysisManager::Instance();
	// if (analysis_mgr->IsActive())
	// 	analysis_mgr->OpenFile();
}

void NeutronRunAction::EndOfRunAction(const G4Run* run)
{
	// G4AnalysisManager* analysis_mgr = G4AnalysisManager::Instance();

	// // scale the histogram by the number of events,
	// // since it will be proportional to the number of particles
	// analysis_mgr->ScaleH1(1, fRun->GetNumberOfEvent());

	// analysis_mgr->Write();
	// analysis_mgr->CloseFile();
}
