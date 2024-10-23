#include "main_window.h"
#include <gtk/gtk.h>
#include <iostream>

MainWindow::MainWindow() {
    // Create GTK window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Impulse Link");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

GtkApplication* MainWindow::createApp(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.matviran.impulselink", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return app;
}

void MainWindow::activate(GtkApplication *app) {
    MainWindow *mainWindow = new MainWindow();
    gtk_widget_show_all(mainWindow->window);
    // Start the HTTP server
    mainWindow->startHttpServer();
}

void MainWindow::startHttpServer() {
    // Call the HTTP server code (defined in the server.cpp)
    startServer();
}
