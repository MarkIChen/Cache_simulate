
#include <math.h> 
#include<iostream>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>
#include "Cache_class.cpp"
using namespace std;

class Controler{
    int asso, policy;
    unsigned index_len, tag_size;
    Cache *ca;
    std::bitset<32> addr;

    public:
   
        Controler(int asso, int policy, int index_len, int tag_size){
            this->asso = asso;
            this->policy = policy;
            this->index_len = index_len;
            this->tag_size = tag_size;

            setCache();
        }

        int read(string line){
            const char *cstr = line.c_str();
            unsigned int num = (unsigned int)strtol(cstr , NULL, 16);
            addr = num;

            string tag;
            string index;
            for(int i = 0; i < tag_size; i++){
                tag.append(string((addr[31 - i]) ? "1" : "0"));
                // tag.append(addr[i]);
            }
            for(int i = 0; i < index_len; i++){
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
            int block_size = pow(2, index_len);

            if(asso ==0){
                ca = new Direct_map(block_size);
            }
            else if(asso == 1){ //four way
                ca = new Four_way(block_size, policy);

            }
        }

};



