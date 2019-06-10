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

    ifstream t1_file("trace1_four.txt");
    ofstream t1_out_file("trace1_test.txt");

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


        

        Controler *controler = new Controler(associate, policy, cache_size, block_size);
        
        bool f_line = 0;
        while(getline(t1_file, line)){
            if(f_line == 0){
                f_line = 1;
                t1_out_file<<controler->read(line);
            } else {
                t1_out_file<<endl<<controler->read(line);
            }
        }
        
     
   

    } else{
        cout<<"unable to open"<<endl; 
    }


    t1_file.close();
    t1_out_file.close();
    return 0;
}
