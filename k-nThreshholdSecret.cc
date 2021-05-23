#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int MOD = 257;
int k;
int n;
int* a;
int* v;

// Galois Field
int gf(int x) {
  x = x % MOD;
  if (x < 0) {
    x = MOD + x;
  }
  return x;
}

// Calculater
int add(int a, int b) {
  return gf(a + b);
}
int mul(int a, int b) {
  return gf(a * b);
}
int sub(int a, int b) {
  return gf(a - b);
}
int division(int x, int y) {
  y = gf(y);
  for (int z = 0; z < MOD; z++) {
    if (mul(y, z) == 1) {
      return mul(x, z);
    }
  }
  return 0;
}

// Using lagrange
int fix() {
  int s = 0;
  for (int j = 1; j <= n; j++) {
    int numerator = 1;
    int demoninator = 1;
    for(int l = 1; l <= n; l++) {
      if (j != l) {
        numerator = mul(numerator, sub(0, l));
        demoninator = mul(demoninator, sub(j, l));
      }
    }
    s = add(s, mul(v[j], division(numerator, demoninator)));
  }
  return s;
}

// main function
int main() {
  cout << "----- Program start -----" << endl;
  srand((unsigned int)time((NULL)));
  int S;
  a = new int[k];
  // cout << "input S : ";
  // cin >> S;
  cout << "input k : ";
  cin >> k;
  cout << "input n : ";
  cin >> n;
  S = rand() % MOD;
  for (int i = 0; i < k; i++) {
    a[i] = rand() % MOD;
  }
  v = new int[n + 1];
  for(int i = 1; i <= n; i++) {
    v[i] = S;
    for (int j = 1; j < k; j++) {
      v[i] = add(v[i], mul(a[j], i));
    }
  }

  cout << "S = " << S << endl;
  cout << "----- a -----------------" << endl;
  for (int i = 1; i < k; i++) {
    cout << "a[" << i << "] = " << a[i] << endl;
  }
  cout << "----- v -----------------" << endl;
  for (int i = 1; i <= n; i++) {
    cout << "v[" << i << "] = " << v[i] << endl;
  }

  cout << "----- finished -----------" << endl;
  if (S == fix()) {
    cout << "S = " << fix() << " ---> complate!!" << endl;
  }
  else {
    cout << "S = " << fix() << " ---> faild......" << endl;
  }
}
