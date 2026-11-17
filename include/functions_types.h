#include <iostream>

enum type {foit, kath, math, none};
enum oper {Epej, del, noOp};

bool readField(const std::string& line, int& i, std::string& el);