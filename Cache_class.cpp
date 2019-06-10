
#include<iostream>
#include "block.cpp"
#include <vector>
#include <deque>
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
        deque< deque<struct Block> > all_set;
   
        
    Four_way(int block_size, int policy){
        this->policy = policy;
        set_num = block_size / 4;
        // row.assign(4, 0);
        // all_set = all_set
        // all_set_ptr = new Block*[set_num];
        for(int i=0; i< set_num; i++) {
            deque<struct Block> row(0);
            all_set.push_back(row);
        }

        
    }

    int read(int tag_dec, int index_dec){
        unsigned int set = index_dec / 4;
        cout<<"set = "<<set<<endl;

        deque<struct Block>::iterator it = all_set.at(set).begin();
        // deque<struct Block>::iterator end = all_set.at(set).end();


        while(it != all_set.at(set).end() ){

            unsigned int tag = it->tag;
            unsigned int index = it->index;
            bool valid = it->valid;

            if(valid == 1 && tag_dec == tag && index_dec == index) { 
                cout<<"hit"<<endl;
                if(policy == 1 ){  //LRU
                    // cout<<"improve privacy"<<endl<<"------"<<endl;
                
                    it = all_set.at(set).erase(it);
                    addElement(set, index, tag);
                }


                return -1;
            }
            *it++;
        }
        
        if(all_set.at(set).size() < 4){  //not four element yet
            // cout<<"now size in set = "<< all_set.at(set).size()<<endl;
            // cout<<"adding new element"<<endl<<"--------"<<endl;
            
            addElement(set, index_dec, tag_dec);
            return -1;

        } else{  //queue is Full
           
            // if(policy == 0){
                // cout<<"this set is full, deleting tag_dec = "<< all_set.at(set).begin()->tag <<" index_dec = "<<all_set.at(set).begin()->index<<endl;
                // cout<<"------"<<endl;
                unsigned victim = all_set.at(set).begin()->tag;
                all_set.at(set).pop_front();
                addElement(set, index_dec, tag_dec);
                cout<<"victim = "<<victim;
                return victim;
            // } else if(policy == 1){ //LRU

            // }

        }


        return 0 ;
    }

    void addElement(int set, int index_dec, int tag_dec){
        struct Block element;
        element.valid = 1;
        element.index = index_dec;
        element.tag = tag_dec;

        all_set.at(set).push_back(element);
    }
};

