#include <iostream>

/**
 * 重みつき平均
 */
double average(double x1, double x2, double r1, double r2) {
  return (x1 * r1 + x2 * r2) / (r1 + r2);
}

/**
 * 探索した最小値の座標(x,y)
 */
struct Result_t {
  double x;
  double y;
};

/**
 * 任意の関数について、黄金分割探索で最小値を探す
 */
template <typename F>
Result_t golden_section_search_minimum(const F& func, double from, double to, double dx, double dy) {
  const double goldenRatio = 1.6180339887498948482045868343656;
  double x1 = from;
  double x4 = to;
  double x2 = average(x1, x4, goldenRatio, 1.0);
  double x3 = average(x1, x4, 1.0, goldenRatio);

  double y1 = func(x1);
  double y2 = func(x2);
  double y3 = func(x3);
  double y4 = func(x4);

  do {
    if (y2 < y3) {
      x4 = x3, x3 = x2, x2 = average(x1, x4, goldenRatio, 1.0);
      y4 = y3, y3 = y2, y2 = func(x2);
    } else {
      x1 = x2, x2 = x3, x3 = average(x1, x4, 1.0, goldenRatio);
      y1 = y2, y2 = y3, y3 = func(x3);
    }
  } while (std::abs(x1 - x4) > dx || std::abs(y1 - y4) > dy);

  return y2 < y2 ? Result_t { x2, y2 } : Result_t { x3, y3 };
}

/**
 * 三次関数
 */
double pol3_function(double x) {
  return 0.2 * x*x*x - 1.0 * x*x - 4.0 * x + 1.0;
}

/**
 * 関数の最小値を探す
 */
void search_minimum() {

  // 三次関数の最小値を探す
  Result_t result = golden_section_search_minimum(pol3_function, 0, 8, 0.1, 0.1);
  std::cout << "minimum point, x = " << result.x << std::endl;
  std::cout << "minimum value, y = " << result.y << std::endl;
}
