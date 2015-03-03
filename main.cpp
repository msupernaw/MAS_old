/* 
 * File:   main.cpp
 * Author: Matthew
 *
 * Created on February 11, 2015, 12:06 PM
 */

#include <cstdlib>
#include <iostream>
#include "source/Information.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    mas::Information<double> info;
    info.LoadModel("model.json");
    std::cout<<info.ToString();
    return 0;
}

