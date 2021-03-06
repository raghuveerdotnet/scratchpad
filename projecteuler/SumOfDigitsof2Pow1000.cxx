/* This program computes 2^1000 and sum of digits of the result
 * author@Raghu
 */
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

void multiply(std::vector<unsigned long int>& prod, std::vector<unsigned long int> twoPow25)
{
  std::vector<std::vector<unsigned long int>> resVec;
  std::vector<unsigned long int> resVec1;
  int zeroAppCnt = 0;
  int zeroPrepCnt = 0;
  unsigned long int carry = 0;
  int prodPlusCarry = 1;
  for (auto digIn2Pow25 : twoPow25) {
    for (auto digInProd : prod) {
      prodPlusCarry = (digIn2Pow25 * digInProd) + carry;
      resVec1.push_back(prodPlusCarry % 10);
      carry = prodPlusCarry / 10; 
    }
    if (carry) {
      resVec1.push_back(carry);
    }
    resVec1.insert(resVec1.begin(), zeroAppCnt, 0);
    zeroAppCnt = zeroAppCnt + 1;
    if (resVec1.size() > zeroPrepCnt) {
      zeroPrepCnt = resVec1.size();
    }
    resVec.push_back(resVec1);
    resVec1.clear();
    carry = 0;
    prodPlusCarry = 1;
  }
  for (auto& rv : resVec) {
    rv.insert(rv.end(), zeroPrepCnt - rv.size(), 0);
  }

  prod.clear();
  carry = 0;
  unsigned long int size = resVec[0].size();
  unsigned long int sum = 0;
  for (unsigned long int i = 0; i < size; i++) {
    for (auto rv : resVec) {
      sum += rv[i];
    }
    sum += carry;
    prod.push_back(sum % 10);
    carry = sum / 10;
    sum = 0;
  }
  if (carry) { 
    prod.push_back(carry);
  }
}

int main()
{
  std::vector<unsigned long int> twoPowerTwentyFive = { 2, 3, 4, 4, 5, 5, 3, 3 };
  std::vector<unsigned long int> product = twoPowerTwentyFive;
  for (int i = 0; i < 39; i++) {
    multiply(product, twoPowerTwentyFive);
  }
  std::cout << std::accumulate(product.begin(), product.end(), 0) << std::endl;
  return 0;
}
