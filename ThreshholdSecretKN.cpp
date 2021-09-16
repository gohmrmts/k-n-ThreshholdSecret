#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MOD = 257;

class Galois {
  public:
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
};

class Person :public Galois{
  private:
    int k, n, no, S, table, c;
    int *share, *a, *table_share;
    
  public:
    Person(int inputK = 0, int inputN = 0, int inputNo = 0) {
      k = inputK;
      n = inputN;
      no = inputNo;
      share = new int[n + 1];
      table_share = new int[n + 1];
      for (int i = 0; i < n + 1; i++){
        share[i] = 0;
        table_share[i] = 0;
      }
      S = rand() % 2;

      // generate c
      c = 1;
      for (int j = 1; j <= n; j++) {
        if (j != no) {
          c = mul(c, division(sub(0, j), sub(no, j)));
        }
      }
      if (n != 0) {
        // cout << "n = " << n << " No = " << no << " c = " << c << endl;
      }
    }
    void generate_share(){
      // generationg share
      a = new int[k];
      for (int i = 0; i < k; i++) {
        a[i] = rand() % MOD;
      }

      share = new int[n + 1];
      for(int i = 1; i <= n; i++) {
        share[i] = S;
        for (int j = 1; j < k; j++) {
          share[i] = add(share[i], mul(a[j], i));
        }
        table_share[i] = share[i];
      }
    }

    void updateShare() {
      for(int i = 1; i <= n; i++) {
          share[i] = table_share[i];
      }
    }

    void sumTableShare() {
      table = 0;
      for (int i = 1; i < n + 1; i++) { 
        table = add(table, table_share[i]);
      }
    }

    void updateTableShareNeedAll(int first, int second) {
      int tmp = c * first * second;
      for(int i = 1; i <= n; i++) {
        table_share[i] = tmp;
        for (int j = 1; j < k; j++) {
          table_share[i] = add(table_share[i], mul(a[j], i));
        }
      }
    }

    void setTableShare(int i, int s) {
      table_share[i] = s;
    }

    int getS() {
      return S;
    }

    int getC() {
      return c;
    }

    int getNo() {
      return no;
    }

    int getTable() {
      return table;
    }

    int getShare(int i) {
      return share[i];
    }

    int getTableShare(int i) {
      return table_share[i];
    }

};


// Using lagrange
int fix(int k, int n, int *v) {
  Galois g;
  int s = 0;
  for (int j = 1; j <= n; j++) {
    int numerator = 1;
    int demoninator = 1;
    for(int l = 1; l <= n; l++) {
      if (j != l) {
        numerator = g.mul(numerator, g.sub(0, l));
        demoninator = g.mul(demoninator, g.sub(j, l));
      }
    }
    s = g.add(s, g.mul(v[j], g.division(numerator, demoninator)));
  }
  return s;
}

void tradeShare(int n, Person *p) {
  cout << "----- Trade start -----" << endl;
  int tmp[n + 1][n + 1];
  for (int i = 1; i < n + 1; i++) { // person
    for (int j = 1; j < n + 1; j++) { // share sequence
      tmp[i][j] = p[i].getTableShare(j);
      cout << tmp[i][j] << ", ";
    }
    cout << endl;
  }
  cout << "-----    -----" << endl;
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      p[i].setTableShare(j, tmp[j][i]);
      cout << p[i].getTableShare(j) << ", ";
    }
    cout << endl;
  }
  cout << "----- Trade finished -----" << endl;
}

void all(int n, Person *p) {
  Galois g;
  int ans = 0;
  cout << "---- multparty start(needAll) ----" << endl;
  tradeShare(n, p);
  for (int i = 1; i < n + 1; i++) {
    p[i].updateShare();
    p[i].updateTableShareNeedAll(p[i].getTableShare(1), p[i].getTableShare(2));
  }
  for (int loop = 0; loop < n - 2; loop++) {
    tradeShare(n, p);
    for (int i = 1; i < n + 1; i++) {
      p[i].sumTableShare();
      p[i].updateTableShareNeedAll(p[i].getTable(), p[i].getShare(loop + 3));
    }
  }
  tradeShare(n, p);
  for (int i = 1; i < n + 1; i++) {
    p[i].sumTableShare();
    ans = g.add(ans, g.mul(p[i].getTable(), p[i].getC()));
    cout << p[i].getTable() << ": C = " << p[i].getC() << endl;
  }
  int correct = 1;
  for (int i = 1; i < n + 1; i++) {
    correct *= p[i].getS();
    cout << p[i].getS() << " ";
  }
  cout << endl << ans;
  if (correct == ans) {
    cout << " ---> complate!!" << endl;
  } else {
    cout << " ---> faild ..." << endl;
  }
  return;
}

void majority(int n, Person *p) {
  int ans = 0;
  Galois g;
  cout << "---- multparty start(majority) ----" << endl;
  tradeShare(n, p);
  for (int i = 1; i < n + 1; i++) {
    p[i].updateShare();
    p[i].sumTableShare();
  }
  for (int i = 1; i < n + 1; i++) {
    ans = g.add(ans, g.mul(p[i].getTable(), p[i].getC()));
  }
  int correct = 0;
  for (int i = 1; i < n + 1; i++) {
    correct += p[i].getS();
    cout << p[i].getS() << " ";
  }
  cout << endl << ans;
  if (correct == ans) {
    cout << " ---> complate!!" << endl;
  } else {
    cout << " ---> faild ..." << endl;
  }
  return;
}

int main(int argc, char *argv[]) {
  int k, n;
  if (argc == 4) {
    k = stoi(argv[2]);
    n = stoi(argv[3]);
    printf("%d, %d", k, n);
  } else {
    k = 2;
    n = 3;
  }
  cout << "----- Program start(" << k << ", " << n << ") -----" << endl;
  Galois g;
  srand((unsigned int)time((NULL)));
  cout << "----- Person generate -----" << endl;
  Person *p = new Person[n + 1];
  int tmp[n + 1];
  for (int i = 1; i <= n; i++) {
    p[i] = Person(k, n, i); // regenerate instance "Person(k, n, no)";
    p[i].generate_share();
    tmp[i] = 0;
    cout << "S : " << p[i].getS() << endl;
    for (int j = 1; j < n + 1; j++) {
      cout << "share " << i << " : " << p[i].getShare(j) << endl;
      tmp[j] = p[i].getShare(j);
    }
    cout << "fix : " << fix(k, n, tmp);
    if (p[i].getS() == fix(k, n, tmp)) {
      cout << " ---> complate! " << endl;
    } else {
      cout << " ---> faild! " << endl;
    }
  }
  if (argc != 1) {
    if (stoi(argv[1]) == 1) all(n, p);
    else if (stoi(argv[1]) == 2) majority(n, p);
  }
}
