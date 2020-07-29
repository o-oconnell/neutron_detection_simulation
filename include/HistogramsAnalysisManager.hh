/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file HistogramsAnalysisManager.hh
 * @brief Analysis manager header file, optionally allows us to place 
 * commands within our code that add to a histogram based on an event,
 * a step, or something else.
 */

#ifndef HISTOGRAMS_ANALYSIS_MANAGER_H
#define HISTOGRAMS_ANALYSIS_MANAGER_H

// this header has the namespace that we use for our histogram output,
// also can be se to "g4xml" or "g4root" for those formats specifically
#include "g4csv.hh"

class HistogramsAnalysisManager
{
public:
	HistogramsAnalysisManager();
	~HistogramsAnalysisManager();

private:
	void CreateInactiveHistograms();
	
};

#endif
