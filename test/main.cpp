#include <gtest/gtest.h>
#include <string>
#include "calcexp.h"

namespace {

	using namespace std;

	class ExpressionTest : public ::testing::Test {};

	TEST(Expression,isDigits) {
		
		string exp = "737";
		ASSERT_TRUE(calc::isDigits(exp, 0));
	}

	TEST(Expression, isSingedDigits) {
		string exp = "+999";
		ASSERT_TRUE(calc::isSignedDigits(exp, 0));
	}

	TEST(Expression, isSingedDigits_1) {
		string exp = "+ 999";
		ASSERT_TRUE(calc::isSignedDigits(exp, 0));
	}

	TEST(Expression, isSingedDigits_2) {
		string exp = "+    999";
		ASSERT_TRUE(calc::isSignedDigits(exp, 0));
	}

	TEST(Expression, isNotDigits) {
		string exp = "*(10)";
		ASSERT_FALSE(calc::isDigits(exp, 0));
	}

	TEST(Expression, isPlusMinus_1) {
		
		string exp = "-(10)";
		ASSERT_TRUE(calc::isPlusMinus(exp, 0));
	}

	TEST(Expression, isPlusMinus_2) {
		
		string exp = "-(10)";
		ASSERT_TRUE(calc::isPlusMinus(exp, 0));
	}

	TEST(Expression, isNotPlusMinus) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isPlusMinus(exp, 0));
	}
	TEST(Expression, isMulDiv_1) {
		
		string exp = "*(10)";
		ASSERT_TRUE(calc::isMulDiv(exp, 0));
	}

	TEST(Expression, isMulDiv_2) {
		
		string exp = "/(10)";
		ASSERT_TRUE(calc::isMulDiv(exp, 0));
	}

	TEST(Expression, isNotMulDiv) {
		
		string exp = "-(10)";
		ASSERT_FALSE(calc::isMulDiv(exp, 0));
	}

	TEST(Expression, isBracketStart) {
		
		string exp = "(10)";
		ASSERT_TRUE(calc::isBracketStart(exp, 0));
	}

	TEST(Expression, isNotBracketStart_1) {
		
		string exp = "-(10)";
		ASSERT_FALSE(calc::isBracketStart(exp, 0));
	}

	TEST(Expression, isNotBracketStart_2) {
		
		string exp = ")(10)";
		ASSERT_FALSE(calc::isBracketStart(exp, 0));
	}

	TEST(Expression, isBracketEnd) {
		
		string exp = ")*";
		ASSERT_TRUE(calc::isBracketEnd(exp, 0));
	}

	TEST(Expression, isNotBracketEnd_1) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isBracketEnd(exp, 0));
	}

	TEST(Expression, isNotBracketEnd_2) {
		
		string exp = "(10)";
		ASSERT_FALSE(calc::isBracketEnd(exp, 0));
	}

	TEST(Expression, isEnd_1) {
		
		string exp = "";
		ASSERT_TRUE(calc::isEnd(exp, 0));
	}

	TEST(Expression, isEnd_2) {

		string exp = "aaaa";
		ASSERT_TRUE(calc::isEnd(exp, 3));
	}

	TEST(Expression, isNotEnd) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isEnd(exp, 0));
	}

	//**********
	//Digits
	//**********
	TEST(Digits, calc_1) {
		calc::Expression exp("1");

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1, res);
		ASSERT_EQ(0, exp.endPos);
	}

	TEST(Digits, calc_2) {
		calc::Expression exp("1383");

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(Digits, calc_3) {
		calc::Expression exp("(1383");
		exp.startPos = 1;

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(Digits, calc_4) {
		calc::Expression exp("123+1383");
		exp.startPos = 4;

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(7, exp.endPos);
	}

	TEST(Digits, calc_5) {
		calc::Expression exp("12345678");

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(12345678, res);
		ASSERT_EQ(7, exp.endPos);
	}

	TEST(Digits, calc_failed_1) {
		calc::Expression exp("+1383");

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_EQ(101, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(Digits, calc_failed_2) {
		calc::Expression exp("123456789");

		long long res = exp.calcDigits();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_EQ(102, exp.error.code);
		ASSERT_EQ(0, res);
	}

	//**********
	//Signed
	//**********
	TEST(SignedDigits, calc_1) {
		calc::Expression exp("1383");

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(SignedDigits, calc_2) {
		calc::Expression exp("+1383");

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(SignedDigits, calc_3) {
		calc::Expression exp("-1383");

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(-1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(SignedDigits, calc_4) {
		calc::Expression exp("-1383p");

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(-1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(SignedDigits, calc_5) {
		calc::Expression exp("(-1383");
		exp.startPos = 1;

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(-1383, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(SignedDigits, calc_failed_1) {
		calc::Expression exp("*1383");

		long long res = exp.calcSignedDigits();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	//**********
	//PlusMinus
	//**********
	TEST(PlusMinusExp, calc_1) {
		calc::Expression exp("100+23");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(123, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(PlusMinusExp, calc_2) {
		calc::Expression exp("1000-23");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(977, res);
		ASSERT_EQ(6, exp.endPos);
	}

	TEST(PlusMinusExp, calc_3) {
		calc::Expression exp("1000+23*10+4");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1234, res);
		ASSERT_EQ(11, exp.endPos);
	}

	TEST(PlusMinusExp, calc_failed_1) {
		calc::Expression exp("[1234");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(PlusMinusExp, calc_failed_2) {
		calc::Expression exp("1234+");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(4, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(PlusMinusExp, calc_failed_3) {
		calc::Expression exp("1234-");

		long long res = exp.calcPlusMinusExp();

		ASSERT_EQ(4, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	//**********
	//MulDiv
	//**********
	TEST(MulDivExp, calc_1) {
		calc::Expression exp("100*23");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(2300, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(MulDivExp, calc_2) {
		calc::Expression exp("100/2");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(50, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(MulDivExp, calc_3) {
		calc::Expression exp("100*234*2");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(46800, res);
		ASSERT_EQ(8, exp.endPos);
	}

	TEST(MulDivExp, calc_failed_1) {
		calc::Expression exp("1234/0");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(5, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(MulDivExp, calc_failed_2) {
		calc::Expression exp("1234*");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(4, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(MulDivExp, calc_failed_3) {
		calc::Expression exp("1234/");

		long long res = exp.calcMulDivExp();

		ASSERT_EQ(4, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	//**********
	//Bracket
	//**********
	TEST(BracketExp, calc_1) {
		calc::Expression exp("1234");

		long long res = exp.calcBracketExp();

		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1234, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(BracketExp, calc_2) {
		calc::Expression exp("(1234)");

		long long res = exp.calcBracketExp();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(BracketExp, calc_3) {
		calc::Expression exp("1234)");

		long long res = exp.calcBracketExp();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(1234, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(BracketExp, calc_failed_1) {
		calc::Expression exp("(1234");

		long long res = exp.calcBracketExp();

		ASSERT_EQ(4, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	TEST(BracketExp, calc_failed_2) {
		calc::Expression exp("*1234");

		long long res = exp.calcBracketExp();

		ASSERT_EQ(0, exp.error.pos);
		ASSERT_NE(0, exp.error.code);
		ASSERT_EQ(0, res);
	}

	//****************
	// Calculate
	//****************
	TEST(Calculate, calc_1) {
		calc::Expression exp(" ( 1234 ) ");

		long long res = exp.calc();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(9, exp.endPos);
	}

	TEST(Calculate, calc_2) {
		calc::Expression exp(" ( 1234 )");

		long long res = exp.calc();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(8, exp.endPos);
	}

	TEST(Calculate, calc_3) {
		calc::Expression exp(" ( 1234 + 1 ) * 2 + 1 ");

		long long res = exp.calc();

		ASSERT_EQ(2471, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(21, exp.endPos);
	}

	TEST(Calculate, calc_4) {
		calc::Expression exp("(((((((1)))))))");

		long long res = exp.calc();

		ASSERT_EQ(1, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(14, exp.endPos);
	}

	TEST(Calculate, calc_5) {
		calc::Expression exp("((((((1+1)*((2)))))))*(2)");

		long long res = exp.calc();

		ASSERT_EQ(8, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(24, exp.endPos);
	}

	TEST(Calculate, calc_6) {
		calc::Expression exp("12345678*12345678");

		long long res = exp.calc();

		ASSERT_EQ(152415765279684, res);
		ASSERT_EQ(0, exp.error.code);
		ASSERT_EQ(16, exp.endPos);
	}
}