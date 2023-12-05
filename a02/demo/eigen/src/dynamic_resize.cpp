#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

int main() {
  // X: dynamic, d: double
  // 在可能的地方使用固定尺寸来显示非常小的尺寸，在需要的地方使用动态尺寸来显示较大的尺寸
  MatrixXd m(2, 5);
  m.resize(4, 3);
  std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols()
            << std::endl;
  std::cout << "It has " << m.size() << " coefficients" << std::endl;
  VectorXd v(2);
  v.resize(5);
  std::cout << "The vector v is of size " << v.size() << std::endl;
  std::cout << "As a matrix, v is of size " << v.rows() << "x" << v.cols()
            << std::endl;
}
