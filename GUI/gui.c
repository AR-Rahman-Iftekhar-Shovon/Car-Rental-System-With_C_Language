#include "gui.h"
#include <string.h>
#include "owner_login.h"
#include "customer_login.h"
#include "driver_management.h"
#include "customer_support.h"
#include "car_owners.h"
#include "customer_registration.h"
#include "rent_a_car.h"

// CSS styles
const char* css = 
    "window { background-color: #f0f2f5; }"
    ".main-title { font: 22pt 'Segoe UI'; color: #1a237e; font-weight: bold; margin-bottom: 20px; }"
    ".sub-title { font: 16pt 'Segoe UI'; color: #0d47a1; margin-bottom: 15px; }"
    ".menu-button { background-color: #e3f2fd; color: #1565c0; font: 12pt 'Segoe UI'; border-radius: 8px; padding: 10px; border: 2px solid #90caf9; }"
    ".menu-button:hover { background-color: #bbdefb; color: #0d47a1; }"
    ".input-field { font: 11pt 'Segoe UI'; padding: 8px; border-radius: 4px; border: 1px solid #90caf9; background-color: white; }"
    ".car-card { background-color: white; border-radius: 8px; padding: 15px; margin: 10px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }"
    ".car-card:hover { background-color: #e3f2fd; }"
    ".status-label { font: 10pt 'Segoe UI'; color: #546e7a; }"
    ".price-label { font: 14pt 'Segoe UI'; color: #1976d2; font-weight: bold; }"
    ".content-box { background-color: white; border-radius: 8px; padding: 20px; margin: 10px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }";

void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

GtkWidget* create_styled_button(const char* label, const char* css_class) {
    GtkWidget* button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(button, 250, 40);
    gtk_style_context_add_class(gtk_widget_get_style_context(button), css_class);
    return button;
}

GtkWidget* create_styled_entry(const char* placeholder, const char* css_class) {
    GtkWidget* entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
    gtk_widget_set_size_request(entry, 250, 35);
    gtk_style_context_add_class(gtk_widget_get_style_context(entry), css_class);
    return entry;
}

GtkWidget* create_styled_label(const char* text, const char* css_class) {
    GtkWidget* label = gtk_label_new(text);
    gtk_style_context_add_class(gtk_widget_get_style_context(label), css_class);
    return label;
}

GtkWidget* create_styled_box(GtkOrientation orientation, int spacing) {
    GtkWidget* box = gtk_box_new(orientation, spacing);
    gtk_container_set_border_width(GTK_CONTAINER(box), 20);
    return box;
}

GtkWidget* create_main_window() {
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Car Rental System");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Main vertical box
    GtkWidget* main_box = create_styled_box(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Content box for all elements
    GtkWidget* content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_style_context_add_class(gtk_widget_get_style_context(content_box), "content-box");
    gtk_box_pack_start(GTK_BOX(main_box), content_box, TRUE, TRUE, 20);

    // Title
    GtkWidget* title = create_styled_label("🚗 Car Rental System", "main-title");
    gtk_box_pack_start(GTK_BOX(content_box), title, FALSE, FALSE, 20);

    // Menu buttons
    const char* menu_items[] = {
        "Owner Login",
        "New Customer Sign Up",
        "Existing Customer Login",
        "Driver Management",
        "Customer Support",
        "Rent A Car",
        "View Car Owners"
    };

    for (int i = 0; i < 7; i++) {
        GtkWidget* btn = create_styled_button(menu_items[i], "menu-button");
        g_signal_connect(btn, "clicked", G_CALLBACK(on_menu_clicked), (gpointer)menu_items[i]);
        gtk_box_pack_start(GTK_BOX(content_box), btn, FALSE, FALSE, 5);
    }

    return window;
}

GtkWidget* create_login_window() {
    owner_login();  // Call the owner login function directly
    return NULL;  // The owner_login function creates its own window
}

GtkWidget* create_car_list_window() {
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Available Cars");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget* box = create_styled_box(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget* title = create_styled_label("Available Cars", "sub-title");
    gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 20);

    // Create a scrollable area for car cards
    GtkWidget* scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(box), scrolled, TRUE, TRUE, 0);

    GtkWidget* car_list = create_styled_box(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(scrolled), car_list);

    // Add sample car cards
    const char* cars[][3] = {
        {"Lamborghini Countach", "2021", "5000"},
        {"BMW i5", "2020", "2100"},
        {"Audi R8", "2022", "4245"},
        {"Mercedes Benz S", "2021", "11890"},
        {"Ferrari SF", "2021", "5900"}
    };

    for (int i = 0; i < 5; i++) {
        GtkWidget* card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_style_context_add_class(gtk_widget_get_style_context(card), "car-card");

        GtkWidget* name = create_styled_label(cars[i][0], "sub-title");
        gtk_box_pack_start(GTK_BOX(card), name, FALSE, FALSE, 5);

        GtkWidget* year = create_styled_label(cars[i][1], "status-label");
        gtk_box_pack_start(GTK_BOX(card), year, FALSE, FALSE, 5);

        GtkWidget* price = create_styled_label(cars[i][2], "price-label");
        gtk_box_pack_start(GTK_BOX(card), price, FALSE, FALSE, 5);

        GtkWidget* rent_btn = create_styled_button("Rent Now", "menu-button");
        g_signal_connect(rent_btn, "clicked", G_CALLBACK(on_rent_clicked), (gpointer)cars[i][0]);
        gtk_box_pack_start(GTK_BOX(card), rent_btn, FALSE, FALSE, 5);

        gtk_box_pack_start(GTK_BOX(car_list), card, FALSE, FALSE, 10);
    }

    return window;
}

GtkWidget* create_dashboard_window(const char* username) {
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Dashboard");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget* box = create_styled_box(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Welcome message
    char welcome_text[100];
    snprintf(welcome_text, sizeof(welcome_text), "Welcome, %s!", username);
    GtkWidget* title = create_styled_label(welcome_text, "main-title");
    gtk_box_pack_start(GTK_BOX(box), title, FALSE, FALSE, 20);

    // Dashboard options
    const char* menu_items[] = {
        "View My Rentals",
        "Browse Available Cars",
        "Update Profile",
        "View Payment History",
        "Logout"
    };

    for (int i = 0; i < 5; i++) {
        GtkWidget* btn = create_styled_button(menu_items[i], "menu-button");
        g_signal_connect(btn, "clicked", G_CALLBACK(on_menu_clicked), (gpointer)menu_items[i]);
        gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 5);
    }

    return window;
}

// Callback implementations
void on_menu_clicked(GtkWidget* widget, gpointer data) {
    const char* label = (const char*)data;
    g_print("[ACTION] You clicked: %s\n", label);
    GtkWidget* new_window = NULL;

    if (strstr(label, "Owner Login")) {
        owner_login();  // Call the owner login function
    } else if (strstr(label, "Existing Customer Login")) {
        customer_login();  // Call the customer login function
    } else if (strstr(label, "Driver Management")) {
        driver_management();  // Call the driver management function
    } else if (strstr(label, "Customer Support")) {
        customer_support();  // Call the customer support function
    } else if (strstr(label, "View Car Owners")) {
        display_car_owners();  // Call the car owners display function
    } else if (strstr(label, "Rent")) {
        new_window = create_car_list_window();
    } else if (strstr(label, "New Customer Sign Up")) {
        new_customer_registration();  // Call the customer registration function
    }

    if (new_window) {
        gtk_widget_show_all(new_window);
    }
}

void on_rent_clicked(GtkWidget* widget, gpointer data) {
    // Get the current user's email from the window data
    GtkWidget* window = gtk_widget_get_toplevel(widget);
    const char* user_email = g_object_get_data(G_OBJECT(window), "user_email");
    
    if (!user_email) {
        // If no user is logged in, show login dialog
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Please login first to rent a car.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        customer_login();  // Show login window
        return;
    }

    // Call the rent_a_car function with the user's email
    rent_a_car(user_email);
} 