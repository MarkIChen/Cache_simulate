#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle (int,int);
    int area () {return (width*height);}
};

Rectangle::Rectangle (int a, int b) {
  width = a;
  height = b;
}
class Cache{
    int asso, policy;
    public:
        Cache(int asso, int policy);
        int read(std::string);
    
    private:
        void setCache();
};
Cache::Cache(int asso, int policy){
    this->asso = asso;
    this->policy = policy;

    setCache();
}

void Cache:: setCache(){
    cout<<"setting cache";
}

int Cache:: read(string s){
    return 0;
}
int main () {
  Cache c (3,4);

  return 0;
}