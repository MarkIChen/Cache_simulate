#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>

using namespace std;
int main()
{
    bitset<32> block;

    unsigned int x;
    std::cin >> std::hex >> x;
    // std::cout <<std::dec<< x << std::endl;

    block = x;
    cout<< block;
    
    // cin>>x;
    // int a[x];
    //
    // cout<<sizeof(a);

    return 0;
}
