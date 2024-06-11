#include <bits/stdc++.h> // Includes most standard C++ library headers
#include <cstdio>        // Standard C library for input/output operations
#include <cstring>       // Standard C library for string manipulation
#include <dirent.h>      // POSIX library for directory operations
#include <unistd.h>      // POSIX library for standard symbolic constants and types
#include <sys/stat.h>    // POSIX library for file status
#include <iostream>      // Standard C++ library for input/output stream
#include <cstdio>        // For std::remove, included again (duplicate include)
#include <cstring>       // For std::strerror, included again (duplicate include)
#if defined(_WIN32)
#include <io.h> // Windows library for low-level I/O operations
#else
#include <errno.h> // POSIX library for error numbers
#endif
using namespace std;

class Aggregator
{
    // Stores pairs of file names and their content
    vector<pair<string, string>> allFiles;
    // File stream for the aggregate file
    fstream aggregate;

public:
    // Constructor: initializes the aggregator and reads existing data from "aggregator.txt"
    Aggregator()
    {
        aggregate.open("aggregator.txt", ios::in);
        aggregate.close();
        readAggregator();
    }

    // function to read the whole aggregate file into a AllFiles structure
    bool readAggregator()
    {
        aggregate.open("aggregator.txt", ios::in);
        string currentLine = "";
        string fileName = "";
        string fileContent = "";
        // Read each line of the aggregate file
        while (getline(aggregate, currentLine))
        {
            if (currentLine.empty())
                continue;
            // Detect the start of a new file entry
            if (currentLine.size() > 3 && currentLine[0] == '~' && currentLine[1] == '~')
            {
                for (int i = 2; i < currentLine.size(); i++)
                {
                    fileName += currentLine[i];
                }
            }
            // Detect the end of a file entry
            else if (currentLine.size() == 3 && currentLine == "~~~")
            {
                allFiles.push_back({fileName, fileContent});
                fileName = "";
                fileContent = "";
            }
            else
            {
                fileContent = fileContent + currentLine + "\n";
            }
        }
        aggregate.close();
        return true;
    }
    // Prints all files stored in allFiles
    void printAllFiles()
    {
        for (int i = 0; i < allFiles.size(); i++)
        {
            cout << allFiles[i].first << endl;
            cout << allFiles[i].second << endl;
            cout << "-------------------------------------------------------------------" << endl;
        }
    }

    bool addFile(string fileToWriteName)
    {
        fstream fileToWrite;
        string fileContent = "";
        fileToWrite.open(fileToWriteName, ios::in);
        if (!fileToWrite.is_open())
        {
            cout << "Error opening file to add to aggregator !" << endl;
            return false;
        }
        aggregate.open("aggregator.txt", ios::app);
        if (!aggregate.is_open())
        {
            cout << "Error opening Aggregate file !" << endl;
            return false;
        }
        aggregate << "\n";
        // adding file name ~~ + FileName
        aggregate << ("~~" + fileToWriteName + "\n");
        string currLine = "";
        while (getline(fileToWrite, currLine))
        {
            fileContent = fileContent + currLine + "\n";
            aggregate << (currLine + "\n");
        }
        aggregate << "~~~";
        aggregate.close();
        allFiles.push_back({fileToWriteName, fileContent});
        deleteFile(fileToWriteName);
        return true;
    }

    // removes file from aggregator.txt and creates new file with same content
    bool removeFile(string fileToRemoveName)
    {
        fstream cutFile;
        cutFile.open(fileToRemoveName.substr(0,fileToRemoveName.size()-4) + "_cutFile.txt", ios::out);
        string fileContent = "";
        for (int i = 0; i < allFiles.size(); i++)
        {
            // finding the required file
            if (allFiles[i].first == fileToRemoveName)
            {
                fileContent = allFiles[i].second;
                allFiles.erase(allFiles.begin() + i);
                break;
            }
        }

        // writing the text into new file
        cutFile << fileContent;

        // rewriting aggregator.txt without the specified file
        aggregate.open("aggregator.txt", ios::out);
        for (auto it : allFiles)
        {
            aggregate << "~~" << it.first << "\n";
            aggregate << it.second;
            aggregate << "\n~~~\n";
        }

        aggregate.close();
        return true;
    }

    bool listAllFiles()
    {
        for (int i = 0; i < allFiles.size(); i++)
        {
            cout << (i + 1) << ". " << allFiles[i].first << endl;
        }
        return true;
    }

    // copy the content of specific file into copy_file.txt using content in aggregator.txt
    bool copyFile(string fileToCopyName)
    {
        fstream copyFile;
        copyFile.open(fileToCopyName.substr(0,fileToCopyName.size()-4) + "_copyFile.txt", ios::out);
        string fileContent = "";
        for (int i = 0; i < allFiles.size(); i++)
        {
            if (allFiles[i].first == fileToCopyName)
            {
                fileContent = allFiles[i].second;
                break;
            }
        }
        copyFile << fileContent;
        return true;
    }

    // renames the file within aggregator.txt
    bool renameFile(string oldName, string newName)
    {
        for (int i = 0; i < allFiles.size(); i++)
        {
            // replacing old name with new name
            if (allFiles[i].first == oldName)
            {
                allFiles[i].first = newName;
            }
        }

        // rewriting new aggregator.txt
        aggregate.open("aggregator.txt", ios::out);
        for (auto it : allFiles)
        {
            aggregate << "~~" << it.first << "\n";
            aggregate << it.second;
            aggregate << "\n~~~\n";
        }

        aggregate.close();
        return true;
    }

    // Retrieves the content of a specific file
    bool displayFile(string fileToDisplay)
    {
        for (auto it : allFiles)
        {
            if (it.first == fileToDisplay)
            {
                cout << "FileName :" << it.first << endl;
                cout << it.second << endl;
                return true;
            }
        }
        return false;
    }

    // Moves a file to a new location
    bool moveFile(string fileToMoveName, string newLocationOfFile)
    {
        const string sourceFile = fileToMoveName;
        string newLocation = newLocationOfFile;

        // Check if source file exists
        if (access(sourceFile.c_str(), F_OK) == -1)
        {
            cerr << "Source file does not exist.\n";
            return 0;
        }

        // Create the target directory if it does not exist
        string targetDir = newLocation.substr(0, newLocation.find_last_of('/'));
        if (mkdir(targetDir.c_str()) == -1 && errno != EEXIST)
        {
            cerr << "Failed to create directory: " << std::strerror(errno) << '\n';
            return 0;
        }

        newLocation += fileToMoveName;
        // Move the file
        if (rename(sourceFile.c_str(), newLocation.c_str()) == -1)
        {
            cerr << "Failed to move file: " << std::strerror(errno) << '\n';
            return 0;
        }
        return 1;
    }

    // Deletes a file
    bool deleteFile(string fileToDeleteName)
    {
        const char *fileToDelete = fileToDeleteName.c_str();

        // Check if the file exists
#if defined(_WIN32)
        if (_access(fileToDelete, 0) != 0)
        {
#else
        if (access(fileToDelete, F_OK) != 0)
        {
#endif
            cerr << "File does not exist.\n";
            return 0;
        }

        // Delete the file
#if defined(_WIN32)
        if (_unlink(fileToDelete) != 0)
        {
#else
        if (remove(fileToDelete) != 0)
        {
#endif
            cerr << "Failed to delete file: " << strerror(errno) << '\n';
            return 0;
        }

        return 1;
    }
};
