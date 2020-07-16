#ifndef COUNTER_SD_H
#define COUNTER_SD_H

#include "G4VSensitiveDetector.hh"
#include "G4ParticleTypes.hh"
#include "g4csv.hh"

class G4TouchableHistory;
class G4Step;
class G4HCofThisEvent;

class CounterSD : public G4VSensitiveDetector
{
public:
	CounterSD(G4String id);
	virtual void Initialize(G4HCofThisEvent *HCE);
	virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *hist);

	
};
	
#endif
