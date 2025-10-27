#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

// Window creation functions
GtkWidget* create_main_window();
GtkWidget* create_login_window();
GtkWidget* create_dashboard_window(const char* username);
GtkWidget* create_car_list_window();
GtkWidget* create_rental_window();

// Widget creation functions
GtkWidget* create_styled_button(const char* label, const char* css_class);
GtkWidget* create_styled_entry(const char* placeholder, const char* css_class);
GtkWidget* create_styled_label(const char* text, const char* css_class);
GtkWidget* create_styled_box(GtkOrientation orientation, int spacing);

// Style functions
void apply_custom_styles();
void load_css();

// Callback functions
void on_menu_clicked(GtkWidget* widget, gpointer data);
void on_register_clicked(GtkWidget* widget, gpointer data);
void on_car_selected(GtkWidget* widget, gpointer data);
void on_rent_clicked(GtkWidget* widget, gpointer data);

#endif // GUI_H
