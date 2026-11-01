#include "tmatrix.h"
#include <utility>
#include <clocale>

int main() {
  setlocale(LC_ALL, "Russian");

  cout << "Тестирование класса работы с векторами" << endl;

  TDynamicVector<int> v1(5), v2(5);
  for (int i = 0; i < 5; i++) {
      v1[i] = i + 1;
      v2[i] = 9 - i;
  }
  cout << "Vector v1 = " << v1 << endl;
  cout << "Vector v2 = " << v2 << endl << endl;

  int simpleArray[5] = {7, 8, 6, 4, 3};
  TDynamicVector<int> vOnSimpleArray(simpleArray, 5);
  cout << "Vector vOnSimpleArray = " << vOnSimpleArray << endl;
  TDynamicVector<int> v1Copy(v1);
  cout << "Vector v1Copy = " << v1Copy << endl;
  TDynamicVector<int> v1Movement(std::move(v1Copy));
  cout << "Vector v1Movement = " << v1Movement << endl;

  cout << "Vectors size: " << v1.size() << endl << endl;

  if (v1 == v1Movement) cout << "v1 == v1Movement" << endl;
  if (v1 == v2) cout << "v1 == v2" << endl;
  if (v1 != v2) cout << "v1 != v2" << endl << endl;

  const int scalar = 3;
  cout << "Vector v1 + scalar = " << v1 + scalar << endl;
  cout << "Vector v1 - scalar = " << v1 - scalar << endl;
  cout << "Vector v1 * scalar = " << v1 * scalar << endl;
  cout << "Vector v1 + v2 = " << v1 + v2 << endl;
  cout << "Vector v2 - v1 = " << v2 - v1 << endl;
  cout << "Scalar v1 * v2 = " << v1 * v2 << endl;


  cout << "\nТестирование класса работы с матрицами" << endl;

  TDynamicMatrix<int> a(5), b(5);
  for (int i = 0; i < 5; i++) {
      for (int j = i; j < 5; j++) {
          a(i, j) = i * 10 + j;
          b(i, j) = (i * 10 + j) * 100;
      }
  }
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;

  cout << "Matrix dimension: " << a.getDimension() << endl << endl;
  if (a == b) cout << "a == b" << endl;
  if (a != b) cout << "a != b" << endl << endl;

  cout << "Matrix a * scalar = " << endl << a * scalar << endl;
  cout << "Vector a * v1 = " << a * v1 << endl;
  cout << "Matrix a + b = " << endl << a + b << endl;
  cout << "Matrix a - b = " << endl << a - b << endl;
  cout << "Matrix a * b = " << endl << a * b << endl;

  return 0;
}
