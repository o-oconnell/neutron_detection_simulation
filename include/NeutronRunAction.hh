/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file NeutronRunAction.hh
 * @brief Run user action header file, allows us to define what should
 * occur before and after a run. Currently being used to open and close
 * the histogram if the user turns it on.
 */

#ifndef NEUTRON_RUN_ACTION_H
#define NEUTRON_RUN_ACTION_H

#include "G4UserRunAction.hh"
#include "NeutronPrimaryGeneratorAction.hh"
#include "G4Run.hh"

class HistogramsAnalysisManager;
class NeutronPrimaryGeneratorAction;

class NeutronRunAction : public G4UserRunAction
{
private:
	NeutronPrimaryGeneratorAction* fPrimaryGeneratorAction;
	G4Run* fRun;
	HistogramsAnalysisManager* fHAM;
public:
	NeutronRunAction(NeutronPrimaryGeneratorAction* particle_gun_info);
	~NeutronRunAction();

	// from parent, must be overridden
	virtual G4Run* GenerateRun();
	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run* run);
};

#endif
