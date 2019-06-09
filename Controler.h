#ifndef CONTROLER_H
#define CONTROLER_H

#include<iostream>
#include <bitset>
#include "Cache_class.cpp"

class Controler{
    int asso, policy;
    unsigned index_len, tag_size;
    Cache *ca;
    std::bitset<32> addr;

    public:
        Controler(int , int , int, int);
        int read(std::string);
    
    private:
        void setCache();
};

#endif