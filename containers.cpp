#include <iostream>
#include <vector>

template<class Os,class Co>
Os& operator<<(Os& os,const Co& co){
  for(auto it=co.begin();it!=co.end();++it){
    std::cout<<*it<<",";
  }
  return os;
}
int main (int argc, char *argv[]) {
  std::vector<int> v1{0,1,2,3,4,40},v2{10,11,12,13,14};
  v1.swap(v2);
  std::cout<<v1<<"\n";
  std::cout<<v2<<"\n";
  return 0;
}
