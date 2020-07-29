#ifndef GTK_INPUT_H 
#define GTK_INPUT_H 

#include <gtk/gtk.h>
#include <iostream>
#include <vector>
void create_data_entry_window();

enum Detector {

};

class InputValues {
public:
	std::string world_material;
	int num_events = 100;
	long double neutron_energy = 0.025;
        enum Detector detector_material;
};

class OutputValues {
public:
	long double edep_target;
	long double edep_world = 0.0;
	long long nparticle_target = 0;
	long long nneutron_target = 0;
	std::string world_material;
	std::string target_material;
	long long nevent_initial = 0;
	long double eneutron_initial = 0;
};

struct GTKBoxesContainer {
public:
	GtkWidget *world_material;
	GtkWidget *initial_events;
	GtkWidget *neutron_energy;
	GtkWidget *window; // needs to be here so we can close it within the function
	struct InputValues *input;
	struct OutputValues *output;
};

extern std::vector<std::string> detector_materials;
extern InputValues *input_values;
extern OutputValues *output_values;
extern struct GTKBoxesContainer *results;

#endif
