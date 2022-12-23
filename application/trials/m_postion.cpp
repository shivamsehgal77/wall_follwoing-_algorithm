#include<iostream>

int main(){
    std::pair<int,int> m_position{15,0};
    std::cout<< m_position.first<<'\n';
    std::cout<< m_position.second<<'\n';
    --(m_position.first);
    std::cout<<m_position.first;
    m_position.first--;
    
    std::cout<<m_position.first;

}