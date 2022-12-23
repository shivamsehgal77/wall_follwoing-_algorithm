#include <iostream>
#include <string>
#include "cps.h"
#include "simulator/simulator.h"

int main(int argc, char *argv[])
{
    // instance to class algorithm using unique pointer  
   auto a=std::make_unique<rwa2group2::Algorithm>(Simulator::mazeHeight(),Simulator::mazeWidth());
   
    // pointer to follow_wall_left
    a->follow_wall_left();
   
}
