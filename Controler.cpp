#include "Controler.h"
#include "Cache.h"
#include <math.h> 
using namespace std;

Controler::Controler(int asso, int policy, int index_len, int tag_size){
    this->asso = asso;
    this->policy = policy;
    this->index_len = index_len;
    this->tag_size = tag_size;

    setCache();
}

void Controler:: setCache(){
    if(asso ==0){
        int map_size = pow(2, index_len);
        // int map_size = pow(2, 3);

        // cout<<"this is direct map  map_size = "<<map_size<<endl;
        ca = new Direct_map[map_size];
        for(int i = 0; i < map_size; i++){
            // cout<<"i = "<<i<<" valid = "<<ca[i].valid<<" tag = "<< ca[i].tag<<endl;
        }
    }
}

int Controler:: read(string line){
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

    cout << addr << " " << "tag = " <<tag << " index = " <<index<< endl;
    cout << "tag_dec = "<<tag_dec<<" index_dec = "<<index_dec<<endl;
    // cout<<"ca[index_dec] = "<<ca[index_dec].tag<<endl<<endl;
    
    // if(ca[index_dec].valid == 0){
    //     cout<<"load new data"<<endl;
    //     ca[index_dec].tag = tag_dec;
    //     ca[index_dec].valid = 1;
    //     return -1;
    // }else if(ca[index_dec].tag == tag_dec){
    //     cout<<"hit"<<endl;
    //     return -1;
    // } else {
    //     cout<<"miss"<<endl;
    //     int victim = ca[index_dec].tag;
    //     ca[index_dec].tag = tag_dec;

    //     return victim;
    // }
    int re = ca[index_dec].read(tag_dec);
    return re;

}