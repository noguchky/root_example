#include <iostream>
#include <cmath>

/**
 * 100以下の素数を画面出力する
 */
void print_prime_number() {
  // 2から100まで試す
  for (int i = 2; i <= 100; ++i) {
    // 素数であればtrueであるフラグを初期化
    bool isPrimary = true;

    // 割るのを試すのは元の数の平方根までで良い
    const double searchmax = std::sqrt(i);
    for (int jj = 2; jj <= searchmax; ++jj) {
      // 割った余が0であれば素数ではない。
      if (i % jj == 0) {
        isPrimary = false;
        break;
      }
    }

    // 素数については画面に出力する
    if (isPrimary) {
      std::cout << i << std::endl;
    }
  }
}
