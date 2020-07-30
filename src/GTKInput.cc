/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file GTKInput.cc
 * @brief GTK input file, allows user to input the material for the 
 * neutrons to propagate through and collects the user input in a struct
 * that is used by the detector construction and the primary generator action
 * to create a customized simulation.
 */

#include "GTKInput.hh"

std::vector<std::string> detector_materials;
struct GTKBoxesContainer* results =
	(GTKBoxesContainer*)malloc(sizeof(GTKBoxesContainer));

InputValues *input_values =
	(InputValues*)malloc(sizeof(InputValues));

OutputValues *output_values =
	(OutputValues*)malloc(sizeof(OutputValues));

void neutron_energy_insert_event(GtkEditable *neutron_energy,
				 const gchar *text,
				 gint length,
				 gint *pos);

void num_events_insert_event(GtkEditable *events,
			     const gchar *text,
			     gint length,
			     gint *pos);

void submit_clicked(GtkWidget *button, struct GTKBoxesContainer *multi_arg);

void create_data_entry_window()
{
	GtkWidget *win;
	GtkWidget *outer_box, *data_entry_box;
	GtkWidget *title_description, *submit;
	gtk_init(0, NULL);

	// window setup
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (win),
			     basename("Neutron detection simulator"));
	gtk_window_set_default_size(GTK_WINDOW (win), 500, 100);
	gtk_container_set_border_width(GTK_CONTAINER (win), 10);
	g_signal_connect(G_OBJECT (win), "destroy",
			 G_CALLBACK (gtk_main_quit), NULL);
	
	outer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	// create the outermost box that we pack everything else into
	outer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	data_entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	// add the title for the data entry section
	GtkWidget *data_entry_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(data_entry_title), "<b>Data entry: </b>");	
	gtk_label_set_xalign(GTK_LABEL(data_entry_title), 0.0);
	gtk_box_pack_start(GTK_BOX(data_entry_box), data_entry_title, FALSE, FALSE, 0);
	
	// add the usage description
	title_description = gtk_text_view_new();
	title_description = gtk_label_new ("This program models neutron propagation through various materials and collision with a detector material\nusing Geant4. By default, thermal neutrons are collided with materials that have high nuclear cross-sections\nfor thermal neutrons. Use the first text box to enter a NIST-specified material for the world. Enter the energy\n(eV) of the incident neutrons using the second text box. Enter the number of initial events using the third\ntext box. Press the \"Submit\" button to run the simulation. ");
	gtk_label_set_xalign(GTK_LABEL(title_description), 0.0f);
	gtk_box_pack_start(GTK_BOX(data_entry_box), title_description, FALSE, FALSE, 0);


	// add the data entry box to the outer box
	gtk_box_pack_start(GTK_BOX(outer_box), data_entry_box, FALSE, FALSE, 10);

	// create the text box for world material entry and its label
	GtkWidget *world_material_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	GtkWidget *world_material_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(world_material_entry), "G4_AIR");
	GtkWidget *world_entry_label = gtk_label_new("Enter the NIST-defined world material:");
	gtk_widget_set_halign(world_entry_label, GTK_ALIGN_START);
	
	gtk_box_pack_start(GTK_BOX(world_material_box), world_entry_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(world_material_box), world_material_entry, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(data_entry_box), world_material_box, FALSE, FALSE, 0);

	// create the box for the neutron incident energy
	GtkWidget *neutron_energy_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	GtkWidget *neutron_energy_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(neutron_energy_entry), "0.025");
	GtkWidget *neutron_entry_label = gtk_label_new("Enter the energy of the incident neutrons (default thermal) (eV):");
	gtk_widget_set_halign(neutron_entry_label, GTK_ALIGN_START);
	
	gtk_box_pack_start(GTK_BOX(neutron_energy_box), neutron_entry_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(neutron_energy_box), neutron_energy_entry, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(data_entry_box), neutron_energy_box, FALSE, FALSE, 0);

	// create the box for the number of initial events
	GtkWidget *initial_events_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	GtkWidget *initial_events_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(initial_events_entry), "100");
	GtkWidget *initial_events_label = gtk_label_new("Enter the amount of initial events (int only):");
	gtk_widget_set_halign(initial_events_label, GTK_ALIGN_START);	

	gtk_box_pack_start(GTK_BOX(initial_events_box), initial_events_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(initial_events_box), initial_events_entry, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(data_entry_box), initial_events_box, FALSE, FALSE, 0);
	
	g_signal_connect(G_OBJECT(neutron_energy_entry), "insert-text",
			 G_CALLBACK(neutron_energy_insert_event), NULL);
	
	g_signal_connect(G_OBJECT(initial_events_entry), "insert-text",
			 G_CALLBACK(num_events_insert_event), NULL);
	
	// create the submit button
	submit = gtk_button_new_with_label("Submit");
	gtk_box_pack_start(GTK_BOX(data_entry_box), submit, TRUE, TRUE, 10);
		
	// pack our results struct with all of our widgets so we can pack
	// the output of the struct with the results from running
	// the program
	results->world_material = world_material_entry;
	results->initial_events = initial_events_entry;
	results->neutron_energy = neutron_energy_entry;
	results->window = win;
	results->input = input_values;
	results->output = output_values;
	
	// connect the callback for closing the window
	// and submitting the values
	g_signal_connect(G_OBJECT(submit), "clicked",
			 G_CALLBACK(submit_clicked),
			 results);
	
 	gtk_container_add(GTK_CONTAINER (win), outer_box);
	gtk_widget_show_all(win);
	gtk_main();

}

/**
 * @brief passes the inputted args to our global struct
 * so that the simulation can use them.
 * @param button the input button
 * @param multi_arg the struct containing
 * the entered values
 */
void submit_clicked(GtkWidget *button, struct GTKBoxesContainer *multi_arg)
{
	GtkEntryBuffer *material_buf = gtk_entry_get_buffer
		(GTK_ENTRY(multi_arg->world_material));
	GtkEntryBuffer *initial_events_buf = gtk_entry_get_buffer
		(GTK_ENTRY(multi_arg->initial_events));
	GtkEntryBuffer *neutron_energy_buf = gtk_entry_get_buffer
		(GTK_ENTRY(multi_arg->neutron_energy));
	
	const gchar *material = gtk_entry_buffer_get_text(material_buf);
	const gchar *events = gtk_entry_buffer_get_text(initial_events_buf);
	const gchar *neutron_energy = gtk_entry_buffer_get_text(neutron_energy_buf);
	

	std::string tmp_str(material);
	results->input->world_material = tmp_str;
	
	results->input->num_events = atoi(events);
	results->input->neutron_energy = atof(neutron_energy);

	results->output->edep_world = 0.0;
	results->output->edep_target = 0.0;
	results->output->nparticle_target = 0;
	results->output->nneutron_target = 0;
	results->output->nevent_initial = atoi(events);
	results->output->eneutron_initial = atof(neutron_energy);

	gtk_window_close(GTK_WINDOW(results->window));
}



void create_result_labels(GtkWidget *outer_box,
			  GtkWidget *result_box)
{



}

/**
 * @brief prevents the entry of any non-numeric characters for the neutron 
 * energy
 * @param neutron_energy the text box
 * @param text the text that was added to the text box
 * @param length the length of the added text
 * @param pos the length of the added text
 */
void neutron_energy_insert_event(GtkEditable *neutron_energy,
				 const gchar *text,
				 gint length,
				 gint *pos)
{
	for (int i = 0; i < length; ++i) {
		if(text[i] == '.')
			continue;
		if (!isdigit(text[i])) {
			g_signal_stop_emission_by_name(G_OBJECT(neutron_energy),
						       "insert-text");
			return;
		}
	}
}

/**
 * @brief prevents the entry of any non-numeric characters for the
 * number of events
 * @param events the text box
 * @param text the text that was added to the text box
 * @param length the length of the added text
 * @param pos the length of the added text
 */
void num_events_insert_event(GtkEditable *events,
				 const gchar *text,
				 gint length,
				 gint *pos)
{
	for (int i = 0; i < length; ++i) {
		if (!isdigit(text[i])) {
			g_signal_stop_emission_by_name(G_OBJECT(events),
						       "insert-text");
			return;
		}
	}
}


