#include <iostream>
#include "functions_types.h"
using namespace std;

bool readField(const string& line, int& i, string& el){
    el.clear();
    if(i >= (int)line.size()) return false;
    while(i < (int)line.size() && line[i] != ',' && line[i] != '\r'){
        el.push_back(line[i]);
        i++;
    }
    if(i < (int)line.size() && line[i] == ',') i++;
    return true;
}