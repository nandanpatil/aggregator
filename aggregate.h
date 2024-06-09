#include <bits/stdc++.h>
using namespace std;

class Aggregator{
           //fileName, fileContent
vector<pair<string,string>>allFiles;
        //aggregate file pointer
fstream aggregate;
public:
Aggregator(){
    aggregate.open("aggregator.txt",ios::in);
    aggregate.close();
}




//function to read the whole aggregate file into a AllFiles structure
bool readAggregator(){
    aggregate.open("aggregator.txt",ios::in);
    string currentLine="";
     string fileName="";
     string fileContent="";
    while(getline(aggregate,currentLine)){
        //cout<<currentLine<<endl;
        if(currentLine.size()>3 && currentLine[0]=='~' && currentLine[1]=='~'){
            for(int i=2;i<currentLine.size();i++){
                fileName+=currentLine[i];
            }
        }
        else if(currentLine.size()==3 && currentLine=="~~~"){
           allFiles.push_back({fileName,fileContent});
           fileName="";
           fileContent="";
        }
        else{
            fileContent = fileContent + currentLine + "\n";
        }
    }
    aggregate.close();
    return true;
}


void printAllFiles(){
    for(int i=0;i<allFiles.size();i++){
        cout<<allFiles[i].first<<endl;
        cout<<allFiles[i].second<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
    }
}




bool addFile(string fileToWriteName){
fstream fileToWrite;
string fileContent="";
fileToWrite.open(fileToWriteName,ios::in);
if(!fileToWrite.is_open()){
    cout<<"Error opening file to add to aggregator !"<<endl;
    return false;
}
aggregate.open("aggregator.txt",ios::app);
if(!aggregate.is_open()){
    cout<<"Error opening Aggregate file !"<<endl;
    return false;
}
if(aggregate.tellg()!=0 || aggregate.tellp()!=0)
    aggregate<<"\n";
//adding file name ~~ + FileName
aggregate<<("~~"+fileToWriteName+"\n");
string currLine="";
while(getline(fileToWrite,currLine)){
    fileContent = fileContent+currLine+"\n";
    aggregate<<(currLine+"\n");
}
aggregate<<"~~~\n";
aggregate.close();
allFiles.push_back({fileToWriteName,fileContent});
return true;
}

};



