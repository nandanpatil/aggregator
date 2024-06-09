#include "aggregate.h"

int main(){
    Aggregator agg;
    agg.readAggregator();
    // agg.printAllFiles();
    cout<<"============================="<<endl;
    // agg.addFile("text0.txt");
    // agg.addFile("text1.txt");
    // agg.addFile("text2.txt");
    // agg.addFile("text3.txt");
    //  agg.addFile("text4.txt");
    // agg.copyFile("text3.txt");
    agg.displayFile("text3.txt");
    // agg.printAllFiles();

}