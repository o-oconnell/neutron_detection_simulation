/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file HistogramsAnalysisManager.cc
 * @brief Analysis manager file, optionally allows us to place 
 * commands within our code that add to a histogram based on an event,
 * a step, or something else.
 */

#include "HistogramsAnalysisManager.hh"
#include "G4UnitsTable.hh"

HistogramsAnalysisManager::HistogramsAnalysisManager()
{
	CreateInactiveHistograms();
}

HistogramsAnalysisManager::~HistogramsAnalysisManager()
{
	// delete our analysis manager, which is the built-in
	// class that allows us to create histograms
	delete G4AnalysisManager::Instance();
}

void HistogramsAnalysisManager::CreateInactiveHistograms()
{
	// set up the params that will allow us to print our results to a file
	G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
	analysis_manager->SetFileName("neutron_output");
	analysis_manager->SetActivation(true);

	G4int bins = 100;
	G4double min_energy = 0;
	G4double max_energy = 100; // units are defined by user using the
	// /analysis/h1/set bins min_energy max_energy units command
	// (which is handled by the analysis manager)

	
	G4int histogram_id = analysis_manager->CreateH1(1, // histogram id
							"neutron energy spectrum (%)", // title
							bins,
							min_energy,
							max_energy);

	// leave the histogram deactivated since we want the user
	// to specify the bins, min, and max energy using macros
	analysis_manager->SetH1Activation(histogram_id, true);
}
