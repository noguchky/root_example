#include <iostream>
#include <cmath>

/**
 * 任意の関数の積分値を計算する
 *   シンプソン法で積分を実行する
 *   積分対象の関数は、引数がdouble型1つで、返り値がdouble型ならなんでもOK
 */
template <typename F>
double simpson_integration(const F& func, double from, double to, int nx) {
  const double dx = (to - from) / nx;

  // 積分を実行
  double sum = 0.0;
  double x = from;
  sum -= func(x) * 0.5;
  if (from < to) {
    while (x < to) {
      sum += func(x);
      x += dx;
      sum += func(x) * 2.0;
      x += dx;
    }
  } else {
    while (x > to) {
      sum += func(x);
      x += dx;
      sum += func(x) * 2.0; 
      x += dx;
    }
  }
  sum += func(x) * 0.5;

  return sum * dx * 2.0 / 3.0;
}

/**
 * 何かの関数
 */
double sine_function(double x) {
  return std::sin(x);
}

/**
 * 関数の積分値を計算する
 */
void calc_integration() {
  // 関数に対して積分を実行 (分割の細かさが異なる)
  const double result_100 = simpson_integration(sine_function, 0, M_PI, 100);
  const double result_200 = simpson_integration(sine_function, 0, M_PI, 200);
  const double result_400 = simpson_integration(sine_function, 0, M_PI, 400);
  const double result_800 = simpson_integration(sine_function, 0, M_PI, 800);

  // 計算結果を出力
  std::cout << "int_0^pi sin(x) dx (100 div) = " << result_100 << std::endl;
  std::cout << "int_0^pi sin(x) dx (200 div) = " << result_200 << std::endl;
  std::cout << "int_0^pi sin(x) dx (400 div) = " << result_400 << std::endl;
  std::cout << "int_0^pi sin(x) dx (800 div) = " << result_800 << std::endl;
}
