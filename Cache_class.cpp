
#include<iostream>
#include "block.cpp"
using namespace std;
class Cache {
    public:
        bool valid;
        int tag;

    // Cache():valid(0), tag(-1){
        
    // }

    virtual int read(int tag_dec, int index_dec){
        cout<<"this is parent read func";
        return -2;
    }
};

class Direct_map : public Cache{
    public:
    struct Block *block_ptr;

    Direct_map(int block_size){
        block_ptr = new Block[block_size];
    }

    int read(int tag_dec, int index_dec){

        if(block_ptr[index_dec].valid == 0){
            cout<<"load new data"<<endl;
            block_ptr[index_dec].tag = tag_dec;
            block_ptr[index_dec].valid = 1;
            return -1;
        }else if(block_ptr[index_dec].tag == tag_dec){
            cout<<"hit"<<endl;
            return -1;
        } else {
            cout<<"miss"<<endl;
            int victim = block_ptr[index_dec].tag;
            block_ptr[index_dec].tag = tag_dec;
            return victim;
        }
    }
};

