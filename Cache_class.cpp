
#include<iostream>
#include "block.cpp"
#include <vector>
#include <deque>
using namespace std;
class Cache {

    public :
        unsigned block_len, miss, hit;

    virtual int read(int tag_dec, int index_dec){
        // cout<<"this is parent read func"<<endl;
        return -2;
    }
    int getMiss(){
        return miss;
    }
    int getHit(){
        return hit;
    }
        
};

class Direct_map : public Cache{
    public:
    struct Block *block_ptr;

    Direct_map(unsigned int block_len){
        this->block_len = block_len;
        block_ptr = new Block[block_len];
        miss = 0;
        hit = 0;
    }

    int read(int tag_dec, int index_dec){
        
        index_dec = index_dec % block_len;

        if(block_ptr[index_dec].valid == 0){
            // cout<<"load new data"<<endl;
            // cout<<"miss"<<endl;
            miss++;
            block_ptr[index_dec].tag = tag_dec;
            block_ptr[index_dec].valid = 1;
            return -1;
        }else if(block_ptr[index_dec].tag == tag_dec){
            // cout<<"hit"<<endl;
            hit++;
            return -1;
        } else {
            // cout<<"miss"<<endl;
            miss++;
            unsigned int victim = block_ptr[index_dec].tag;
            block_ptr[index_dec].tag = tag_dec;
            return victim;
        }
    }
};

class Four_way : public Cache {

    public :
        unsigned int set_num, policy, block_per_set, set;
        // Block **all_set_ptr;
        deque< deque<struct Block> > all_set;
   
        
    Four_way(int block_len, int policy, int set){
        this->policy = policy;
        this -> block_len = block_len;
        this->set = set;
        block_per_set = block_len / set;
        // cout<<"block in every set = "<<block_per_set<<endl;
        miss = 0;
        hit = 0;

        for(int i=0; i< block_per_set; i++) {
            deque<struct Block> row(0);
            all_set.push_back(row);
        }
    }

    int read(int tag_dec, int index_dec){
        index_dec = index_dec % block_per_set;

        deque<struct Block>::iterator it = all_set.at(index_dec).begin();

        while(it != all_set.at(index_dec).end() ){

            unsigned int tag = it->tag;
            bool valid = it->valid;

            if(valid == 1 && tag_dec == tag ) { 
                hit++;
                if(policy == 1 ){  //LRU 
                    // cout<<"improve priority"<<endl<<"------"<<endl;
                    it = all_set.at(index_dec).erase(it);
                    addElement(index_dec, tag);
                }
                else if(policy == 2){
                    it-> feq ++;
                }
                return -1;
            }
           

            *it++;
        }
        
        if(all_set.at(index_dec).size() < set){  //not four element yet
            // cout<<"Not full in set,  size in set = "<< all_set.at(index_dec).size()<<endl;
            // cout<<"adding new element"<<endl<<"--------"<<endl;
            miss++;
            addElement(index_dec, tag_dec);
            return -1;

        } else{  //queue is Full
           
            if(policy == 0 || policy == 1 ){
                miss++;
                unsigned victim = all_set.at(index_dec).begin()->tag;
                all_set.at(index_dec).pop_front();
                addElement(index_dec,  tag_dec);
                return victim;
            } else if(policy == 2){ 
                miss++;
                deque<struct Block>::iterator it = all_set.at(index_dec).begin();
                deque<struct Block>::iterator min_it = all_set.at(index_dec).begin();
                //find the samallest feq
                while(it != all_set.at(index_dec).end()){

                    it-> feq = it->feq - 3 ;
                    if(it->feq < min_it->feq ){
                        min_it = it;
                    }
                    *it++;
                }
                unsigned victim = min_it->tag;
                all_set.at(index_dec).erase(min_it);
                addElement(index_dec,  tag_dec);
                
                return victim;
            }

        }
        return 0 ;
    }

    void addElement(int index_dec,  int tag_dec){
        struct Block element;
        element.valid = 1;
        element.tag = tag_dec;

        all_set.at(index_dec).push_back(element);
    }
};

