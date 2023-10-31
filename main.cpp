#include <iostream>
#include <cstring>
#include <dirent.h>

bool isDirectoryValid(const char* directory_path) {
    DIR* dir = opendir(directory_path);
    if (!dir) {
        return false;
    }
    closedir(dir);
    return true;
}

void listDirectory(const char* directory_path) {
    DIR* dir;
    struct dirent* entry;

    // Open the directory
    dir = opendir(directory_path);

    if (!dir) {
        std::cerr << "Error opening directory." << std::endl;
        return;
    }

    
    std::cout << "DIRECTORY FILES:" << std::endl;

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        i++;
        std::cout << i << ".) " << entry->d_name << std::endl;
    }

    closedir(dir);
}

int main() {
    std::string directory_path; 
    int choice;

    do {
        std::cout << "Options:" << std::endl;
        std::cout << "1. Open directory" << std::endl;
        std::cout << "2. Read directory" << std::endl;
        std::cout << "3. Close directory" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter directory path: ";
                std::cin >> directory_path;
                if (!isDirectoryValid(directory_path.c_str())) {
                    std::cerr << "Invalid directory path. The directory does not exist." << std::endl;
                    directory_path.clear();
                }
                break;
            case 2:
                if (!directory_path.empty()) {
                    listDirectory(directory_path.c_str());
                } else {
                    std::cerr << "Directory is not open. Please open a directory first." << std::endl;
                }
                break;
            case 3:
                directory_path.clear();
                std::cout << "Directory closed." << std::endl;
                break;
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

