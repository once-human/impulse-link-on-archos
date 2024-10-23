#include "gui/main_window.h"

int main(int argc, char *argv[]) {
    auto app = MainWindow::createApp(argc, argv);
    return app.run();
}
