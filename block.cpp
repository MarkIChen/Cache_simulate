#include<iostream>

struct Block {
    bool valid;
    unsigned int tag;
    unsigned int index;

    Block(): valid(0), tag(0), index(0){
    }
};