#include <Eigen/Dense>
#include <iostream>

using namespace std;

int main() {
  Eigen::MatrixXf m(4, 4);
  m = Eigen::MatrixXf::Random(4, 4);
  cout << "m: " << endl << m << endl;
  cout << "Block in the middle" << endl;
  cout << endl;
  cout << m.block<2, 2>(1, 1) << endl
       << endl;  // m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图i行,j列
  // 也可以作为左值
  m.block<2, 2>(1, 1) *= 2;
  cout << "After 'm.block<2,2>(1,1) *= 2;':" << endl << m << endl;
  cout << "Block in the middle" << endl;
  cout << m.block(1, 1, 2, 2) << endl; // m.block(a,b,i,j) 表示从第(a+1)行(b+1)列开始,截图i行,j列
}
