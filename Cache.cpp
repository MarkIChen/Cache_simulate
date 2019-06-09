#include<iostream>
#include<fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Controler.cpp"
#include <stdlib.h>
using namespace std;

int main(){
    string line;
    int cache_size, block_size, associate, policy, index_len, offset, tag_size;
    
    long x;

    ifstream t1_file("trace1.txt");
    ofstream t1_out_file("trace1_out.txt");

    if(t1_file.is_open()){
        getline(t1_file, line);
        cache_size =  atoi(line.c_str());
        getline(t1_file, line);
        block_size = atoi(line.c_str());
        getline(t1_file, line);
        associate = atoi(line.c_str());
        getline(t1_file, line);
        policy = atoi(line.c_str());

        cout << cache_size << endl;
        cout << block_size << endl;
        cout << associate << endl;
        cout << policy <<endl;

        index_len = log2(cache_size/block_size) + 10;
        offset = log2(block_size);
        tag_size = 32 - (index_len + offset);

        cout << "index_len = " << index_len <<endl;
        cout << "offset = " << offset << endl;
        cout << "tag_size = " << tag_size << endl;

        Controler *controler = new Controler(associate, policy, index_len, tag_size);
        
        while(getline(t1_file, line)){
            t1_out_file<<controler->read(line)<<endl;
        }
        
     
   

    } else{
        cout<<"unable to open"<<endl; 
    }


    t1_file.close();
    t1_out_file.close();
    return 0;
}
