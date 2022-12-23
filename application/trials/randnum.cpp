#include<iostream>
#include<array>
#include<stdlib.h>


int main(){
    srand(time(0));
    int x; 
    int y; 
    const std::string& text{"G"};
    std::array<int,2> arr{0,15};
     char tryagain{'y'};
    //do{
    int r = rand() % 2;
    int a= rand()%2;
     
   
     
    if(r==1){
        x=arr[a];
        y=rand()%16;
    }
    else{
        y=arr[a];
        x=rand()%16;
    }
    
 
    
    std::cin >> tryagain;

  
    std::cout<<x<<'\n'<<y;
    //}while(tryagain!='n');

}

