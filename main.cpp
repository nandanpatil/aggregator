#include "aggregate.h"

void codeDriver(vector<string> &params)
{
    Aggregator agg;
    string operation = params[0];
    bool executed = false;
    if (operation == "-addFile")
    {
        executed = agg.addFile(params[1]);
        if (executed)
            cout << "File added successfully" << endl;
    }
    else if (operation == "-removeFile")
    {
        executed = agg.removeFile(params[1]);
        if (executed)
            cout << "File removed successfully from aggregator.txt and new file has been created" << endl;
    }
    else if (operation == "-listAllFiles")
    {
        executed = agg.listAllFiles();
    }
    else if (operation == "-copyFile")
    {
        executed = agg.copyFile(params[1]);
        if (executed)
            cout << "File has been copied successfully" << endl;
    }
    else if (operation == "-renameFile")
    {
        executed = agg.renameFile(params[1], params[2]);
        if (executed)
            cout << "File renamed successfully" << endl;
    }
    else if (operation == "-moveFile")
    {
        executed = agg.moveFile(params[1], params[2]);
        if (executed)
            cout << "File moved successfully to specified location" << endl;
    }
    else if (operation == "-displayFile")
    {
        executed = agg.displayFile(params[1]);
        if (!executed)
            cout << "Please check the required file again" << endl;
    }
    else
    {
        cout << "Command does not exist.\n";
        cout << "Help -> ./aggregator -{functionName} {fileName} {fileName(only required for moving file)}\n";
        cout << "Functions available :\n";
        /*#*/ cout << "addFile {fileName} :Adds file.txt to aggregator.txt and deletes the original_file.txt\n"
                   << endl;
        /*#*/ cout << "removeFile {fileName} :Removes file.txt from aggregator.txt and creates a separate file cut_file.txt with the same content as the original file.txt\n"
                   << endl;
        /*#*/ cout << "copyFile {fileName} :Keeps file.txt in aggregator.txt and creates a copy of the original file.txt as copy_file.txt\n"
                   << endl;
        /*#*/ cout << "renameFile {old_name} {new_name} :Renames old_file.txt to new_file.txt within aggregator.txt.\n"
                   << endl;
        /*#*/ cout << "moveFile {fileName} :Moves file.txt to a new location (new_location), keeping a reference in aggregator.txt.\n"
                   << endl;
        /*#*/ cout << "displayFile {fileName} :Displays the content of file.txt from aggregator.txt.\n"
                   << endl;
         /*#*/ cout << "listAllFiles :Displays the content of file.txt from aggregator.txt.\n"
                   << endl;           
        return;
    }
    if (!executed)
        cout << "Please check the file and try again" << endl;
}

int main(int argc, char *argv[])
{
    vector<string> params;
    for (int i = 1; i <= argc; i++)
    {
        if (argv[i])
            params.push_back(argv[i]);
    }

    codeDriver(params);
}