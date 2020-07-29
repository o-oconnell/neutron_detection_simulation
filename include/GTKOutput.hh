#ifndef GTK_OUTPUT_H
#define GTK_OUTPUT_H

#include <gtk/gtk.h>
#include <iostream>

struct WinContainer {
	GtkWidget *window;
};

void create_output_window();
	
#endif
