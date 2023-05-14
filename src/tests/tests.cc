#include <gtest/gtest.h>

#include "../source/calculation.h"

TEST(Calc, 1) {
  // Arrange
  std::string input_str = "1+1";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 2.0;
  std::string output_str = "1+1";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 2) {
  // Arrange
  std::string input_str = "1+";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 3) {
  // Arrange
  std::string input_str = "sin(x)+cos(x)-tan(x)*atan(x)";
  double x = 1.;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "sin(x)+cos(x)-tan(x)*atan(x)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 4) {
  // Arrange
  std::string input_str = "2mod2+(-1)";
  double x = 1.;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "2mod2+(-1)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 5) {
  // Arrange
  std::string input_str = "";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 6) {
  // Arrange
  std::string input_str = "2mok7";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 7) {
  // Arrange
  std::string input_str = "sim(x)";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 8) {
  // Arrange
  std::string input_str = "asin(0.5)";
  double x = 0.0;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "asin(0.5)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 9) {
  // Arrange
  std::string input_str = "acos(0.5)";
  double x = 0.0;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "acos(0.5)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 10) {
  // Arrange
  std::string input_str = "atan(0.5)";
  double x = 0.0;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "atan(0.5)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 11) {
  // Arrange
  std::string input_str = "sqrt(16)";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 4.0;
  std::string output_str = "sqrt(16)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 12) {
  // Arrange
  std::string input_str = "ln(2)";
  double x = 0.0;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "ln(2)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 13) {
  // Arrange
  std::string input_str = "log(2)";
  double x = 0.0;
  // Act
  sc2::Calculation::Calc(input_str, x);
  // Assert
  // double origin = 0.0;
  std::string output_str = "log(2)";
  ASSERT_TRUE(input_str == output_str);
  // ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 14) {
  // Arrange
  std::string input_str = "x^2/2";
  double x = 2.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 2.0;
  std::string output_str = "x^2/2";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 15) {
  // Arrange
  std::string input_str = "0.1mod0.1";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "0.1mod0.1";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 16) {
  // Arrange
  std::string input_str = "+cos(x)";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 1.0;
  std::string output_str = "+cos(x)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 17) {
  // Arrange
  std::string input_str = "(1.mod1)";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "(1.mod1)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 18) {
  // Arrange
  std::string input_str = "09.1+2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 19) {
  // Arrange
  std::string input_str = "xmod3";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "xmod3";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 20) {
  // Arrange
  std::string input_str = "(-0.3)mod0.3";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "(-0.3)mod0.3";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 21) {
  // Arrange
  std::string input_str = "-(-x+0.2+x)";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = -0.2;
  std::string output_str = "-(-x+0.2+x)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 22) {
  // Arrange
  std::string input_str = "(2.mod2+7)";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 7.0;
  std::string output_str = "(2.mod2+7)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 23) {
  // Arrange
  std::string input_str = "((cos(0)))";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 1.0;
  std::string output_str = "((cos(0)))";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 24) {
  // Arrange
  std::string input_str = "con(0)";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 25) {
  // Arrange
  std::string input_str = "(3.mod2.)";
  double x = 3.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 1.0;
  std::string output_str = "(3.mod2.)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 26) {
  // Arrange
  std::string input_str = "1modx+1mod(x)";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "1modx+1mod(x)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 27) {
  // Arrange
  std::string input_str = "cos0";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  // std::string output_str = "Error";
  // ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 28) {
  // Arrange
  std::string input_str = "cos(0)modcos(0)";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "cos(0)modcos(0)";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 29) {
  // Arrange
  std::string input_str = "(cos(x)))+1)";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 30) {
  // Arrange
  std::string input_str = "2.*3";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 6.0;
  std::string output_str = "2.*3";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 31) {
  // Arrange
  std::string input_str = "(2.*3)+(-1";
  double x = 1.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 32) {
  // Arrange
  std::string input_str = "3-x";
  double x = 2.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 1.0;
  std::string output_str = "3-x";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 33) {
  // Arrange
  std::string input_str = "x-3.";
  double x = 2.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = -1.0;
  std::string output_str = "x-3.";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 34) {
  // Arrange
  std::string input_str = "x-3.+";
  double x = 2.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.0;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 35) {
  // Arrange
  std::string input_str = "3+12e2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 1203.;
  std::string output_str = "3+12e2";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 36) {
  // Arrange
  std::string input_str = "3+e2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 37) {
  // Arrange
  std::string input_str = "3+e2e5";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 38) {
  // Arrange
  std::string input_str = "3+E2.2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 39) {
  // Arrange
  std::string input_str = "3E+7e";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 40) {
  // Arrange
  std::string input_str = "3E+3*2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 6000.;
  std::string output_str = "3E+3*2";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 41) {
  // Arrange
  std::string input_str = "3E+x";
  double x = 2.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 42) {
  // Arrange
  std::string input_str = "3E+(24)";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 43) {
  // Arrange
  std::string input_str = "3E5*2.3.4";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 44) {
  // Arrange
  std::string input_str = "3.E5";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 300000.;
  std::string output_str = "3.E5";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 45) {
  // Arrange
  std::string input_str = "3.E/2";
  double x = 0.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

TEST(Calc, 46) {
  // Arrange
  std::string input_str = "3.E+x";
  double x = 7.0;
  // Act
  double result = sc2::Calculation::Calc(input_str, x);
  // Assert
  double origin = 0.;
  std::string output_str = "Error";
  ASSERT_TRUE(input_str == output_str);
  ASSERT_NEAR(result, origin, 1e-7);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
