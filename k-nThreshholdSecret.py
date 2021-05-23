package secret;

import java.util.Random;
import java.util.Scanner;

public class ThreshholdSecret23 {
  static final int MOD = 257;
  static int k, n;
  static int[] a, v;

  public static int gf(int x) {
    x = x % MOD;
    if (x < 0) {
      x = MOD + x;
    }
    return x;
  }

  public static int add (int a, int b) {
    return gf(a + b);
  }

  public static int sub(int a, int b) {
    return gf(a - b);
  }

  public static int mul(int a, int b) {
    return gf(a * b);
  }

  public static int div(int x, int y) {
    y = gf(y);
    for (int z = 0; z < MOD; z++) {
      if (mul(y, z) == 1) {
        return mul(x, z);
      }   
    }
    return 0;
  }

  public static int fix() {
    int s = 0;
    for (int i = 1; i < v.length; i++) {
      int numerator = 1;
      int demoninator = 1;
      for(int j = 1; j < v.length; j++) {
        if (i != j) {
          numerator = mul(numerator, sub(0, j));
          demoninator = mul(demoninator, sub(i, j));
        }
      }
      s = add(s, mul(v[i], div(numerator, demoninator)));
    }
    return s;
  }

  public static void main(String[] args) {
    Random random = new Random();
    Scanner scan = new Scanner(System.in);
    System.out.print("input k : ");
    k = scan.nextInt();
    System.out.print("input n : ");
    n = scan.nextInt();

    int S = random.nextInt(MOD);

    a = new int[k];
    for (int i = 1; i < a.length; i++) {
      a[i] = random.nextInt(MOD);
    }

    v = new int[n + 1];
    for (int i = 1; i < v.length; i++) {
      v[i] = S;
      for (int j = 1; j < a.length; j++) {
        v[i] = add(v[i], mul(a[j], i)); 
      }
    }

    System.out.println("S = " + S);
    for (int i = 1; i < a.length; i++) {
      System.out.println("a[" + i + "]" + a[i]);
    }
    for (int i = 1; i < v.length; i++) {
      System.out.println("v[" + i + "]" + v[i]);
    }
    System.out.println("encrypt : " + fix());
    if (fix() == S) {
      System.out.println("Conplate!!");
    } else {
      System.out.println("Failed......");
    }
  }
}
