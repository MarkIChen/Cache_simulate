
#include <math.h> 
#include<iostream>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>
#include "Cache_class.cpp"
using namespace std;

class Controler{
    int asso, policy;
    unsigned index_bit, tag_size, offset;
    unsigned cache_size, block_size, block_len;
    Cache *ca;
    std::bitset<32> addr;

    public:
   
        Controler(int asso, int policy, int cache_size, int block_size){
            this->asso = asso;
            this->policy = policy;
            this->cache_size = cache_size;
            this->block_size = block_size;
            
            offset = log2(block_size);

            unsigned int block_num = (log2(cache_size) + 10) - (log2(block_size));
            if (asso == 0) {
                index_bit = block_num;
            } else if (asso ==1){
                index_bit = block_num - 2;
            } else if(asso == 2) {
                index_bit = 0;
            }

            block_len = pow(2, block_num);
            tag_size = 32 - (index_bit + offset);
            cout << "totoal size of blocks = " << block_len <<endl;
            cout << "offset = " << offset << endl;
            cout << "tag_size = " << tag_size << endl;
            setCache();
        }

        int read(string line){
            const char *cstr = line.c_str();
            unsigned int num = (unsigned int)strtol(cstr , NULL, 16);
            addr = num;

            string tag;
            string index;
            if(asso == 2) index = "0";

            for(int i = 0; i < tag_size; i++){
                tag.append(string((addr[31 - i]) ? "1" : "0"));
                // tag.append(addr[i]);
            }
            for(int i = 0; i < index_bit; i++){
                index.append(string(addr[31 - tag_size - i] ? "1" : "0"));
            }
            const char *cstr2 = tag.c_str();
            int tag_dec = strtol(cstr2 , NULL, 2);

            const char *cstr3 = index.c_str();
            int index_dec = strtol(cstr3 , NULL, 2);

            // cout << addr << " " << "tag = " <<tag << " index = " <<index<< endl;
            cout << "tag_dec = "<<tag_dec<<" index_dec = "<<index_dec<<endl;

            int re = ca -> read(tag_dec, index_dec);
            return re;

            }
    
    private:
        void setCache(){
            
            if(asso ==0){
                ca = new Direct_map(block_len);
            }
            else if(asso == 1){ //four way
                ca = new Four_way(block_len, policy, 4);
            } else if(asso == 2){
                ca = new Four_way(block_len, policy, block_len);
            }
        }

};



