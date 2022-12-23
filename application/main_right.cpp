#include <iostream>
#include <string>
#include "cps.h"
#include "simulator/simulator.h"

int main(int argc, char *argv[])
{
    // instance of class algorithm using unique pointers
   auto a=std::make_unique<rwa2group2::Algorithm>(Simulator::mazeHeight(),Simulator::mazeWidth());
   
    // pointer to follow_wall_right function
    a->follow_wall_right();
      
}
