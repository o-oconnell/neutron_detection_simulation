/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file GTKInput.hh
 * @brief GTK input header file, allows user to input the material for the 
 * neutrons to propagate through and collects the user input in a struct
 * that is used by the detector construction and the primary generator action
 * to create a customized simulation.
 */

#ifndef GTK_INPUT_H 
#define GTK_INPUT_H 

#include <gtk/gtk.h>
#include <iostream>
#include <vector>

enum class Detector {
	       HE3,
	       BF3,
	       HE4,
	       LI6,
};

struct InputValues {
	std::string world_material;
	int num_events = 100;
	long double neutron_energy = 0.025;
        enum Detector detector_material;
};

struct OutputValues {
	std::string world_material;
	enum Detector detector_material;
	long double edep_target;
	long double edep_world = 0.0;
	long long nparticle_target = 0;
	long long nneutron_target = 0;
	long long nevent_initial = 0;
	long double eneutron_initial = 0;
};

struct GTKBoxesContainer {
	GtkWidget *world_material;
	GtkWidget *initial_events;
	GtkWidget *neutron_energy;
	GtkWidget *window; // needs to be here so we can close it within the callback for the close button
	struct InputValues *input;
	struct OutputValues *output;
};

// messy, but we need to have accessible in
// many places without needing to pass
// as a parameter.
extern struct GTKBoxesContainer *results;

void create_data_entry_window();

void neutron_energy_insert_event(GtkEditable *neutron_energy,
				 const gchar *text,
				 gint length,
				 gint *pos);

void num_events_insert_event(GtkEditable *events,
			     const gchar *text,
			     gint length,
			     gint *pos);

void submit_clicked(GtkWidget *button, struct GTKBoxesContainer *multi_arg);
void he3_clicked(GtkWidget *button, GtkWidget *label);
void BF3_clicked(GtkWidget *button, GtkWidget *label);
void he4_clicked(GtkWidget *button, GtkWidget *label);

#endif
