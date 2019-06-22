#include<iostream>

struct Block {
    bool valid;
    unsigned int tag;
    int feq;
    // unsigned int index;

    Block(): valid(0), tag(0), feq(0){
    }
};
