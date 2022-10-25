#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "programa.h"


int main(int argc, char *argv[])
{
    Programa programa;
    std::ofstream off_file(argv[2]);
    programa.analizar(argv[1]);
    programa.mostrar(off_file);
    programa.mostrar(std::cout);
   
}