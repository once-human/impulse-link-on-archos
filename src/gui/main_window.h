#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtk/gtk.h>

class MainWindow {
public:
    MainWindow();
    static GtkApplication* createApp(int argc, char *argv[]);
    static void activate(GtkApplication *app);
    void startHttpServer();

private:
    GtkWidget *window;
};

#endif // MAIN_WINDOW_H
