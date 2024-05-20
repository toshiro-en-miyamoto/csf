#include <type_traits> 

int main()
{
  // 0 is int
  static_assert(std::is_floating_point_v<decltype(0)> == false);
  // sign(?) digits exponent : 1e1
  static_assert(std::is_floating_point_v<decltype(1e1)>);
  // sign(?) digits . exponent(?) : +1., -2.e0
  static_assert(std::is_floating_point_v<decltype(+1.)>);
  static_assert(std::is_floating_point_v<decltype(-2.e0)>);
  // sign(?) digits(?) . digits exponent(?) : +.2, -0.2, -.2E+3, 0.2e-3
  static_assert(std::is_floating_point_v<decltype(+.2)>);
  static_assert(std::is_floating_point_v<decltype(-0.2)>);
  static_assert(std::is_floating_point_v<decltype(-.2E+3)>);
  static_assert(std::is_floating_point_v<decltype(0.2e-3)>);
  return 0;
}