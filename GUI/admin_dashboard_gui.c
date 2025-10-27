#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "admin_dashboard.h"
#include "car_management.h"
#include "view_rental_history.h"

static void on_add_car_clicked(GtkWidget *widget, gpointer data);
static void on_remove_car_clicked(GtkWidget *widget, gpointer data);
static void on_update_car_clicked(GtkWidget *widget, gpointer data);

static void on_menu_clicked(GtkWidget *widget, gpointer data) {
    const char *action = gtk_button_get_label(GTK_BUTTON(widget));
    const char *ownerID = (const char *)data;

    if (strcmp(action, "View My Cars") == 0) {
        view_my_cars(ownerID);
    } else if (strcmp(action, "Add New Car") == 0) {
        add_new_car(ownerID);
    } else if (strcmp(action, "Remove Car") == 0) {
        remove_car(ownerID);
    } else if (strcmp(action, "Edit Car Details") == 0) {
        edit_car_details(ownerID);
    } else if (strcmp(action, "View Rental History") == 0) {
        view_owner_rental_history(ownerID);
    } else if (strcmp(action, "Logout") == 0) {
        gtk_main_quit();
    }
}

void admin_dashboard(char *ownerID) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Admin Dashboard");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    // Welcome message
    char welcome[100];
    snprintf(welcome, sizeof(welcome), "Welcome, Owner %s!", ownerID);
    label = gtk_label_new(welcome);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Menu buttons
    const char *menu_items[] = {
        "View My Cars",
        "Add New Car",
        "Remove Car",
        "Edit Car Details",
        "View Rental History",
        "Logout"
    };

    for (int i = 0; i < 6; i++) {
        button = gtk_button_new_with_label(menu_items[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_menu_clicked), ownerID);
        gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
    }

    gtk_widget_show_all(window);
    gtk_main();
}

void view_my_cars(const char *ownerID) {
    GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkTextBuffer *buffer;
    GtkWidget *text_view;
    FILE *file;
    char line[256];
    char car_info[1024] = "";

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "My Cars");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    label = gtk_label_new("My Cars List:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    file = fopen("car_details.txt", "r");
    if (file) {
        char car_name[100] = "";
        char car_owner_email[100] = "";
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            if (strncmp(line, "Car Name: ", 10) == 0) {
                strncpy(car_name, line + 10, sizeof(car_name) - 1);
            } else if (strncmp(line, "Owner Email: ", 13) == 0) {
                strncpy(car_owner_email, line + 13, sizeof(car_owner_email) - 1);
                if (g_strcmp0(g_strstrip(car_owner_email), g_strstrip((char*)ownerID)) == 0) {
                    strcat(car_info, car_name);
                    strcat(car_info, "\n");
                }
                car_name[0] = 0;
                car_owner_email[0] = 0;
            }
        }
        fclose(file);
    }

    if (strlen(car_info) == 0) {
        strcpy(car_info, "No cars found for this owner.");
    }

    gtk_text_buffer_set_text(buffer, car_info, -1);

    gtk_widget_show_all(window);
}

void add_new_car(const char *ownerID) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *combo;
    GtkWidget *spin;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Add New Car");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Car ID
    label = gtk_label_new("Car ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    // Car Name
    label = gtk_label_new("Car Name:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);

    // Car Model
    label = gtk_label_new("Car Model:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 1, 1);

    // Car Type
    label = gtk_label_new("Car Type:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Sedan");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "SUV");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Sports");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Luxury");
    gtk_grid_attach(GTK_GRID(grid), combo, 1, 3, 1, 1);

    // Price per Day
    label = gtk_label_new("Price per Day:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    spin = gtk_spin_button_new_with_range(0, 10000, 100);
    gtk_grid_attach(GTK_GRID(grid), spin, 1, 4, 1, 1);

    button = gtk_button_new_with_label("Add Car");
    g_signal_connect(button, "clicked", G_CALLBACK(on_add_car_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(window), "owner_id", (gpointer)ownerID);

    gtk_widget_show_all(window);
}

static void on_add_car_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window))));
    GtkWidget *car_id_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
    GtkWidget *car_name_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 1);
    GtkWidget *car_model_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 2);
    GtkWidget *car_type_combo = gtk_grid_get_child_at(GTK_GRID(grid), 1, 3);
    GtkWidget *price_spin = gtk_grid_get_child_at(GTK_GRID(grid), 1, 4);

    const char *car_id = gtk_entry_get_text(GTK_ENTRY(car_id_entry));
    const char *car_name = gtk_entry_get_text(GTK_ENTRY(car_name_entry));
    const char *car_model = gtk_entry_get_text(GTK_ENTRY(car_model_entry));
    const char *car_type = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(car_type_combo));
    double price = gtk_spin_button_get_value(GTK_SPIN_BUTTON(price_spin));

    if (strlen(car_id) == 0 || strlen(car_name) == 0 || strlen(car_model) == 0 || car_type == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_ERROR,
                                                 GTK_BUTTONS_OK,
                                                 "Please fill in all fields");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen("car_details.txt", "a");
    if (file) {
        fprintf(file, "Car ID: %s\n", car_id);
        fprintf(file, "Car Name: %s\n", car_name);
        fprintf(file, "Car Model: %s\n", car_model);
        fprintf(file, "Car Type: %s\n", car_type);
        fprintf(file, "Price per Day: %.2f\n", price);
        fprintf(file, "Owner Email: %s\n", (const char *)g_object_get_data(G_OBJECT(window), "owner_id"));
        fprintf(file, "Status: Available\n\n");
        fclose(file);

        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_INFO,
                                                 GTK_BUTTONS_OK,
                                                 "Car added successfully!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
    }
}

void remove_car(const char *ownerID) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Remove Car");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    label = gtk_label_new("Enter Car ID to remove:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Remove");
    g_signal_connect(button, "clicked", G_CALLBACK(on_remove_car_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(window), "owner_id", (gpointer)ownerID);

    gtk_widget_show_all(window);
}

static void on_remove_car_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    GtkWidget *entry = gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window))));
    const char *car_id = gtk_entry_get_text(GTK_ENTRY(entry));
    const char *owner_id = (const char *)g_object_get_data(G_OBJECT(window), "owner_id");

    if (strlen(car_id) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_ERROR,
                                                 GTK_BUTTONS_OK,
                                                 "Please enter a Car ID");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen("car_details.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[256];
    int found = 0;
    int skip = 0;

    if (file && temp) {
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Car ID:") && strstr(line, car_id)) {
                found = 1;
                skip = 7; // Skip next 7 lines
            }

            if (!skip) {
                fputs(line, temp);
            } else {
                skip--;
            }
        }
        fclose(file);
        fclose(temp);

        remove("car_details.txt");
        rename("temp.txt", "car_details.txt");

        GtkWidget *dialog;
        if (found) {
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_INFO,
                                          GTK_BUTTONS_OK,
                                          "Car removed successfully!");
        } else {
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_OK,
                                          "Car not found!");
        }
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
    }
}

void edit_car_details(const char *ownerID) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *combo;
    GtkWidget *spin;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Car Details");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Car ID (read-only)
    label = gtk_label_new("Car ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    // Car Name
    label = gtk_label_new("Car Name:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);

    // Car Model
    label = gtk_label_new("Car Model:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 1, 1);

    // Car Type
    label = gtk_label_new("Car Type:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Sedan");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "SUV");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Sports");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Luxury");
    gtk_grid_attach(GTK_GRID(grid), combo, 1, 3, 1, 1);

    // Price per Day
    label = gtk_label_new("Price per Day:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 1, 1);
    spin = gtk_spin_button_new_with_range(0, 10000, 100);
    gtk_grid_attach(GTK_GRID(grid), spin, 1, 4, 1, 1);

    button = gtk_button_new_with_label("Update Car");
    g_signal_connect(button, "clicked", G_CALLBACK(on_update_car_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(window), "owner_id", (gpointer)ownerID);

    gtk_widget_show_all(window);
}

static void on_update_car_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window))));
    GtkWidget *car_id_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 0);
    GtkWidget *car_name_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 1);
    GtkWidget *car_model_entry = gtk_grid_get_child_at(GTK_GRID(grid), 1, 2);
    GtkWidget *car_type_combo = gtk_grid_get_child_at(GTK_GRID(grid), 1, 3);
    GtkWidget *price_spin = gtk_grid_get_child_at(GTK_GRID(grid), 1, 4);

    const char *car_id = gtk_entry_get_text(GTK_ENTRY(car_id_entry));
    const char *car_name = gtk_entry_get_text(GTK_ENTRY(car_name_entry));
    const char *car_model = gtk_entry_get_text(GTK_ENTRY(car_model_entry));
    const char *car_type = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(car_type_combo));
    double price = gtk_spin_button_get_value(GTK_SPIN_BUTTON(price_spin));

    if (strlen(car_id) == 0 || strlen(car_name) == 0 || strlen(car_model) == 0 || car_type == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_ERROR,
                                                 GTK_BUTTONS_OK,
                                                 "Please fill in all fields");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen("car_details.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[256];
    int found = 0;
    int skip = 0;

    if (file && temp) {
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Car ID:") && strstr(line, car_id)) {
                found = 1;
                fprintf(temp, "Car ID: %s\n", car_id);
                fprintf(temp, "Car Name: %s\n", car_name);
                fprintf(temp, "Car Model: %s\n", car_model);
                fprintf(temp, "Car Type: %s\n", car_type);
                fprintf(temp, "Price per Day: %.2f\n", price);
                fprintf(temp, "Owner Email: %s\n", (const char *)g_object_get_data(G_OBJECT(window), "owner_id"));
                fprintf(temp, "Status: Available\n\n");
                skip = 7; // Skip next 7 lines
            }

            if (!skip) {
                fputs(line, temp);
            } else {
                skip--;
            }
        }
        fclose(file);
        fclose(temp);

        remove("car_details.txt");
        rename("temp.txt", "car_details.txt");

        GtkWidget *dialog;
        if (found) {
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_INFO,
                                          GTK_BUTTONS_OK,
                                          "Car updated successfully!");
        } else {
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_OK,
                                          "Car not found!");
        }
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
    }
}

void view_owner_rental_history(const char *ownerID) {
    GtkWidget *window;
    GtkWidget *scrolled_window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkTextBuffer *buffer;
    GtkWidget *text_view;
    FILE *file;
    char line[256];
    char history[1024] = "";

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rental History");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    label = gtk_label_new("Rental History:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    file = fopen("rental_history.txt", "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "Owner Email:") && strstr(line, ownerID)) {
                strcat(history, line);
                // Read next 5 lines (rental details)
                for (int i = 0; i < 5; i++) {
                    if (fgets(line, sizeof(line), file)) {
                        strcat(history, line);
                    }
                }
                strcat(history, "\n");
            }
        }
        fclose(file);
    }

    if (strlen(history) == 0) {
        strcpy(history, "No rental history found for this owner.");
    }

    gtk_text_buffer_set_text(buffer, history, -1);

    gtk_widget_show_all(window);
}
