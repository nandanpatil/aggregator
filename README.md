# # File-Aggregator
A simple file aggregator. It takes a list of files and clubs them into a single file while keeping track of individual files.


## Usage

To aggregate text files using Aggregator, follow these simple steps:

1. Download the aggregator zip on your system.
2. If it is linux based system change line 226 the IF block from ``` mkdir(targetDir.c_str()) == -1 && errno != EEXIST ``` to ```mkdir(targetDir.c_str(),0777) == -1 && errno != EEXIST ```
3. Open a terminal or command prompt with administrator privileges
4. Compile the main program using :
```sh
     g++ main.cpp -o agg
```
**Help**
```sh
    ./agg -help
```

**Add a new file**
```sh
    ./agg -addFile filename
```

**Remove a file**
```sh
    ./agg -removeFile filename
```
**List all files**
```sh
    ./agg -listAllFiles
```
**Create a copy of a file**
```sh
    ./agg -copyFile filename
```
**Rename a file**
```sh
    ./agg -renameFile oldname newname
```
**Move a file**
```sh
    ./agg -moveFile oldDirectory newDirectory/
```
**Display content of a file**
```sh
    ./agg -displayFile filename
```

