#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <Windows.h> // TODO get rid of OS specific headers
#include <cstdio>

// Prints a message in console and stores response in variable
void get_input(std::string* var, const char* msg);

// Reads parameters from file
int get_options(std::string path,
                std::string* path_from, std::string* path_to,
                std::string* prefix,
                std::string* file_extension_from, std::string* file_extension_to,
                int* sleep_time);

// Puts all file paths in a certain directory with a specific prefix and extension in a vector
void get_file_paths(std::vector<std::experimental::filesystem::path>* paths, std::string path, std::string prefix, std::string extension);

// Moves all files into another directory and changes their extensions
void move_files(std::vector<std::experimental::filesystem::path>* paths_from, std::string path_to, std::string extension);

// Uncomment to start as cli application
//#define cli

#define option_file "filemover.conf"

int main() {
    std::string path_from = "";
    std::string path_to = "";
    std::string prefix = "";
    std::string file_extension_from = "";
    std::string file_extension_to = "";
    int sleep_time = 0;

#ifdef cli

    if (get_input(&prefix, "Enter some file prefix to look for") != 0) {
        std::cout << "Illegal file path entered\n";
        return -1;
    }
    get_input(&path_from, "Enter path to get files from");
    get_input(&file_extension_from, "Enter file extension to convert from");
    get_input(&path_to, "Enter path to move files into");
    get_input(&file_extension_to, "Enter file extension to convert to");

#else



#endif

    std::vector<std::experimental::filesystem::path> file_paths;

    while (true) {
        get_file_paths(&file_paths, path_from, prefix, file_extension_from);

        if (!file_paths.empty()) 
            move_files(&file_paths, path_to, file_extension_to);

        file_paths.clear();

        Sleep(sleep_time);
    }
}

void get_input(std::string* var, const char* msg) {
    std::cout << msg;

    char tmp = (int) std::cin.get();
    while (tmp != '\n') {
        *var += tmp;
        tmp = (char) std::cin.get();
    }
}

int get_options(std::string path, std::string* path_from, std::string* path_to, std::string* prefix, std::string* file_extension_from, std::string* file_extension_to, int* sleep_time)
{
    return 0;
}

inline bool hasPrefix(std::string path, std::string prefix) {
    return path.length() >= prefix.length() && prefix == path.substr(0, prefix.size());
}

void get_file_paths(std::vector<std::experimental::filesystem::path>* paths,
                   std::string path,
                   std::string prefix,
                   std::string extension) {
    try {
        for (const std::experimental::filesystem::directory_entry entry : std::experimental::filesystem::directory_iterator(path)) {
            if (hasPrefix(entry.path().stem().string(), prefix)
                && entry.path().extension().string() == extension) {
                paths->push_back(entry);
            }
        }
    }
    catch (...) {
        std::cout << "\nError while searching for files in folder " << path << "\n";
    }
}

void move_files(std::vector<std::experimental::filesystem::path>* paths_from,
                std::string path_to, std::string extension) {
    for (std::experimental::filesystem::path path_from : *paths_from) {
        std::experimental::filesystem::path filename = 
            std::experimental::filesystem::path(path_to) / path_from.filename().string();

        try {
            std::experimental::filesystem::rename(path_from, filename.replace_extension(extension));
        }
        catch (...) {
            std::cout << "Failed to move file " << path_from << " to " << filename << "\n";
        }
    }
}
