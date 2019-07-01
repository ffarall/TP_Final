
#ifndef PARSECMD_H
#define PARSECMD_H
#include <iostream>
#include<string>
#include<cstdlib>


typedef int(*pCallback) (char *, char*, void *);
int parseCmdLine(int argc, char *argv[], pCallback p, void *userData);

#endif 
