#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdio>  // For std::remove
#include <cstring> // For std::strerror
#if defined(_WIN32)
#include <io.h> // For _access, _unlink
#else
#endif
#include <errno.h>
using namespace std;

class Aggregator
{
    // fileName, fileContent
    vector<pair<string, string>> allFiles;
    // aggregate file pointer
    fstream aggregate;

public:
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
        while (getline(aggregate, currentLine))
        {
            if (currentLine.empty())
                continue;
            // cout<<currentLine<<endl;
            if (currentLine.size() > 3 && currentLine[0] == '~' && currentLine[1] == '~')
            {
                for (int i = 2; i < currentLine.size(); i++)
                {
                    fileName += currentLine[i];
                }
            }
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

    bool removeFile(string fileToRemoveName)
    {
        fstream cutFile;
        cutFile.open("cut_File.txt", ios::out);
        string fileContent = "";
        for (int i = 0; i < allFiles.size(); i++)
        {
            if (allFiles[i].first == fileToRemoveName)
            {
                fileContent = allFiles[i].second;
                allFiles.erase(allFiles.begin() + i);
                break;
            }
        }

        cutFile << fileContent;

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

    bool copyFile(string fileToCopyName)
    {
        fstream copyFile;
        copyFile.open("copy_File.txt", ios::out);
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

    bool moveFile(string fileToMoveName, string newLocationOfFile)
    {
        const string sourceFile = fileToMoveName;
        string newLocation = newLocationOfFile;

        // Check if source file exists
        if (access(sourceFile.c_str(), F_OK) == -1)
        {
            cerr << "Source file does not exist.\n";
            return 1;
        }

        // Create the target directory if it does not exist
        string targetDir = newLocation.substr(0, newLocation.find_last_of('/'));
        if (mkdir(targetDir.c_str()) == -1 && errno != EEXIST)
        {
            cerr << "Failed to create directory: " << std::strerror(errno) << '\n';
            return 1;
        }

        // Move the file
        newLocation += fileToMoveName;
        if (rename(sourceFile.c_str(), newLocation.c_str()) == -1)
        {
            cerr << "Failed to move file: " << std::strerror(errno) << '\n';
            return 1;
        }

        cout << "File moved successfully to " << newLocation << "\n";
        return 0;
    }

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
            return 1;
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
            return 1;
        }

        cout << "File deleted successfully.\n";
        return 0;
    }
};
