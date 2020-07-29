/**
 * @author Oisin O'Connell
 * @date 7/29/2020
 * @file GTKOutput.hh
 * @brief GTK output header file, collects the results from the 
 * OutputValues struct that is forward declared in the GTKInput header
 * file and displays them as the output.
 */

#ifndef GTK_OUTPUT_H
#define GTK_OUTPUT_H

#include <gtk/gtk.h>
#include <iostream>

struct WinContainer {
	GtkWidget *window;
};

void close_clicked(GtkWidget *button, struct WinContainer* wc);
void create_output_window();
	
#endif
