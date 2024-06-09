#include "aggregate.h"

int main(){
    Aggregator agg;
    agg.readAggregator();
    agg.printAllFiles();
    cout<<"=============================";
    bool added=agg.addFile("text3.txt");
    cout<<added<<endl;
    agg.printAllFiles();

}