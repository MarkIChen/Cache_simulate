
#include<iostream>
#include "block.cpp"
#include <vector>
using namespace std;
class Cache {

    public :

    virtual int read(int tag_dec, int index_dec){
        cout<<"this is parent read func"<<endl;
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

class Four_way : public Cache {

    public :
        unsigned int set_num, policy;
        // Block **all_set_ptr;
        vector< vector<struct Block> > all_set;
        

        // vector<vector<struct Block> > all_set;
        
    Four_way(int block_size, int policy){
        this->policy = policy;
        set_num = block_size / 4;
        // row.assign(4, 0);
        // all_set = all_set
        // all_set_ptr = new Block*[set_num];
        for(int i=0; i< set_num; i++) {
            vector<struct Block> row(0);
            all_set.push_back(row);
        }

        
    }

    int read(int tag_dec, int index_dec){

        unsigned int set = index_dec / 4;
        cout<<"set = "<<set<<endl;

        for(int  i = 0; i < all_set.at(set).size() ; i ++ ){

            unsigned int tag = all_set.at(set).at(i).tag;
            unsigned int index = all_set.at(set).at(i).index;
            bool valid = all_set.at(set).at(i).valid;

            if(valid == 1 && tag_dec == tag && index_dec == index) { 
                cout<<"hit"<<endl;
                return -1;
            }
        }
        //cannot find
        if(all_set.at(set).size() < 4){
            cout<<"now size in set = "<< all_set.at(set).size()<<endl;
            cout<<"adding new element"<<endl<<"--------"<<endl;

            struct Block element;
            element.valid = 1;
            element.index = index_dec;
            element.tag = tag_dec;

            all_set.at(set).push_back(element);
        }


        return 0 ;
    }
};

