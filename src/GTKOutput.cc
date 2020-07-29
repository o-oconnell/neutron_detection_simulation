/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file GTKOutput.cc
 * @brief GTK output file, collects the results from the 
 * OutputValues struct that is forward declared in the GTKInput header
 * file and displays them as the output.
 */

#include "GTKInput.hh"
#include "GTKOutput.hh"
#include <sstream>
#include <iomanip>

/**
 * @brief creates the output window that contains the energy deposition
 * and other statistics after a simulation has run.
 */
void create_output_window()
{
	GtkWidget *win;
	GtkWidget *outer_box, *inner_box;
	GtkWidget *result_list, *close_button;
	gtk_init(0, NULL);

	// window setup
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (win),
			     basename("Neutron propagation simulation summary"));
	gtk_window_set_default_size(GTK_WINDOW (win), 500, 100);
	gtk_container_set_border_width(GTK_CONTAINER (win), 0);
	g_signal_connect(G_OBJECT (win), "destroy",
			 G_CALLBACK (gtk_main_quit), NULL);
	
	// create the outermost box that we pack everything else into
	outer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	// add the title for the output section
	GtkWidget *output_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(output_title), "<b>Simulation results</b>");	
	gtk_box_pack_start(GTK_BOX(inner_box), output_title, FALSE, FALSE, 5);
	
	// add the result list
	GtkWidget *edep = gtk_text_view_new();	
        edep = gtk_label_new ((std::string("Energy deposition in target material: ") + std::to_string(results->output->edep_target) + " MeV").c_str());
	gtk_label_set_xalign(GTK_LABEL(edep), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), edep, FALSE, FALSE, 0);

	GtkWidget *nparticle_target = gtk_text_view_new();	
	nparticle_target = gtk_label_new ((std::string("Number of particles impacted target material: ") + std::to_string(results->output->nparticle_target)).c_str());
	gtk_label_set_xalign(GTK_LABEL(nparticle_target), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), nparticle_target, FALSE, FALSE, 0);
	 
	GtkWidget *nneutron_target = gtk_text_view_new();	
	nneutron_target = gtk_label_new((std::string("Number of neutrons impacted target material: ") + std::to_string(results->output->nneutron_target)).c_str());
	gtk_label_set_xalign(GTK_LABEL(nneutron_target), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), nneutron_target, FALSE, FALSE, 0);
	 
	GtkWidget *nevent_initial = gtk_text_view_new();	
	nevent_initial = gtk_label_new((std::string("Initial number of events: ") + std::to_string(results->output->nevent_initial)).c_str());
	gtk_label_set_xalign(GTK_LABEL(nevent_initial), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), nevent_initial, FALSE, FALSE, 0);

	GtkWidget *eneutron_initial = gtk_text_view_new();
	std::ostringstream eneutron_str;
	eneutron_str << results->output->eneutron_initial;
	
	eneutron_initial = gtk_label_new((std::string("Initial neutron energies: ") + eneutron_str.str() + " keV").c_str());
	gtk_label_set_xalign(GTK_LABEL(eneutron_initial), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), eneutron_initial, FALSE, FALSE, 0);
	 
	GtkWidget *world_material = gtk_text_view_new();	
	world_material = gtk_label_new((std::string("World material NIST definition: ") + results->input->world_material).c_str());
	gtk_label_set_xalign(GTK_LABEL(world_material), 0.0f);
	gtk_box_pack_start(GTK_BOX(inner_box), world_material, FALSE, FALSE, 0);
	 
	// create the close button
	close_button = gtk_button_new_with_label("Close");
	gtk_box_pack_start(GTK_BOX(inner_box), close_button, TRUE, TRUE, 10);

	// place the window in a pointer to a struct so we can pass it as
	// generic to the callback function
	struct WinContainer *wc =
		(struct WinContainer*)malloc(sizeof(struct WinContainer));
	wc->window = win;
	
	// connect the callback for closing the window
	g_signal_connect(G_OBJECT(close_button), "clicked",
			 G_CALLBACK(close_clicked),
			 wc);
	
	gtk_box_pack_start(GTK_BOX(outer_box), inner_box, TRUE, TRUE, 10);
	
 	gtk_container_add(GTK_CONTAINER (win), outer_box);
	gtk_widget_show_all(win);
	gtk_main();
	free(wc);
}

/**
 * @brief callback that closes the window when the close button is clicked
 * @param button the button widget
 * @param wc a struct containing the window that displays the results
 */
void close_clicked(GtkWidget *button, struct WinContainer* wc)
{
	gtk_window_close(GTK_WINDOW(wc->window));
}
