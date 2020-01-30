#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <cstdio>



// https://en.cppreference.com/w/cpp/filesystem/directory_iterator

// Prints a message in console and stores response in variable
int get_input(std::string* var, const char* msg);

// Puts all file paths in a certain directory with a specific prefix and extension in a vector
int get_file_paths(std::vector<std::filesystem::path>* paths, std::string path, std::string prefix, std::string extension);

// Moves all files into another directory and changes their extensions
int move_files(std::vector<std::filesystem::path>* paths_from, std::string path_to, std::string extension);


int main() {
    std::string path_from = "";
    std::string path_to = "";
    std::string prefix = "";
    std::string file_extension_from = "";
    std::string file_extension_to = "";


    // TODO input sanitisation
    if (get_input(&prefix, "Enter some file prefix to look for") != 0) {
        std::cout << "Illegal file path entered\n";
        return -1;
    }
    get_input(&path_from, "Enter path to get files from");
    get_input(&file_extension_from, "Enter file extension to convert from");
    get_input(&path_to, "Enter path to move files into");
    get_input(&file_extension_to, "Enter file extension to convert to");

    std::vector<std::filesystem::path> file_paths;

#define SLEEP_TIME 60 * 1000 // sleep 1 minute between runs

    while (true) {
        get_file_paths(&file_paths, path_from, prefix, file_extension_from);

        if (!file_paths.empty()) 
            move_files(&file_paths, path_to, file_extension_to);

        file_paths.clear();

        Sleep(SLEEP_TIME);
    }
}

int get_input(std::string* var, const char* msg) {
    // TODO read/store default values from/to file
    std::string default_option = "";

    std::cout << msg << " (default: " << default_option << "): ";

    std::string temp = std::string();

    char tmp = (int) std::cin.get();
    while (tmp != '\n') {
        temp += tmp;
        tmp = (char) std::cin.get();
    }

    if (temp.empty()) *var = default_option;
    else              *var = temp;

    return 0;
}


inline bool hasPrefix(std::string path, std::string prefix) {
    return path.length() >= prefix.length() && prefix == path.substr(0, prefix.size());
}

int get_file_paths(std::vector<std::filesystem::path>* paths,
                   std::string path,
                   std::string prefix,
                   std::string extension) {
    try {
        for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path)) {
            if (hasPrefix(entry.path().stem().string(), prefix)
                && entry.path().extension().string() == extension) {
                paths->push_back(entry);
            }
        }
    }
    catch (...) {
        std::cout << "\nError while searching for files in folder " << path << "\n";
    }

    return 0;
}

int move_files(std::vector<std::filesystem::path>* paths_from,
               std::string path_to, std::string extension) {
    for (std::filesystem::path path_from : *paths_from) {
        std::filesystem::path filename = std::filesystem::path(path_to) / path_from.filename().string();

        try {
            std::filesystem::rename(path_from, filename.replace_extension(extension));
        }
        catch (...) {
            std::cout << "Failed to move file " << path_from << " to " << filename << "\n";
        }
    }
    return 0;
}
