#ifndef CACHE_H
#define CACHE_H
#include<iostream>
using namespace std;
class Cache {
    public:
        bool valid;
        int tag;

    Cache():valid(0), tag(-1){
        
    }

    virtual int read(int tag_dec){
        cout<<"this is parent read func";
        return -2;
    }
};

class Direct_map : public Cache{
    public:
    int read(int tag_dec){

        if(valid == 0){
            cout<<"load new data"<<endl;
            tag = tag_dec;
            valid = 1;
            return -1;
        }else if(tag == tag_dec){
            cout<<"hit"<<endl;
            return -1;
        } else {
            cout<<"miss"<<endl;
            int victim = tag;
            tag = tag_dec;
            return victim;
        }
    }
};

#endif