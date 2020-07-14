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
