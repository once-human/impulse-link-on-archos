#include "file_model.h"
#include <sys/stat.h>
#include <cstdlib>

std::string getDocumentsPath() {
    const char* home = std::getenv("HOME");
    return std::string(home) + "/Documents";
}

void createDirectory(const std::string& path) {
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else
        mkdir(path.c_str(), 0777);
    #endif
}
