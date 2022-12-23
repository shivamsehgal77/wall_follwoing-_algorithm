#include<iostream>
#include<array>

int main(){
    std::array<char,4> directions;
    directions={'n','e','s','w'};
    // char *ptr{&directions[0]};
    // char *ptr2{&directions[3]};
    // for(int i=0;i<8;i++){
    // if(ptr>=ptr2){
    //     ptr=&directions[0];
    //     ++ptr;
    //     std::cout<<*ptr<<'\n';
    // }
    // else{
    //     ++ptr;
    //     std::cout<<*ptr<<'\n';
    // }
    // }
    char *ptr{&directions[0]};
    char *ptr2{&directions[0]};
    for(int i=0;i<=8;i++){
    if(ptr<=ptr2){
        ptr=&directions[0];
        --ptr;
        std::cout<<*ptr<<'\n';
    }
    else{
        --ptr;
        std::cout<<*ptr<<'\n';
    }
    }

}
    


