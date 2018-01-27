#include <gtest/gtest.h>
#include <string>
#include "calcexp.h"

namespace {

	using namespace std;

	class ExpressionTest : public ::testing::Test {};

	TEST(Epression,isDigits) {
		
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

	TEST(Epression, isNotDigits) {
		string exp = "*(10)";
		ASSERT_FALSE(calc::isDigits(exp, 0));
	}

	TEST(Epression, isPlusMinus_1) {
		
		string exp = "-(10)";
		ASSERT_TRUE(calc::isPlusMinus(exp, 0));
	}

	TEST(Epression, isPlusMinus_2) {
		
		string exp = "-(10)";
		ASSERT_TRUE(calc::isPlusMinus(exp, 0));
	}

	TEST(Epression, isNotPlusMinus) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isPlusMinus(exp, 0));
	}
	TEST(Epression, isMulDiv_1) {
		
		string exp = "*(10)";
		ASSERT_TRUE(calc::isMulDiv(exp, 0));
	}

	TEST(Epression, isMulDiv_2) {
		
		string exp = "/(10)";
		ASSERT_TRUE(calc::isMulDiv(exp, 0));
	}

	TEST(Epression, isNotMulDiv) {
		
		string exp = "-(10)";
		ASSERT_FALSE(calc::isMulDiv(exp, 0));
	}

	TEST(Epression, isBracketStart) {
		
		string exp = "(10)";
		ASSERT_TRUE(calc::isBracketStart(exp, 0));
	}

	TEST(Epression, isNotBracketStart_1) {
		
		string exp = "-(10)";
		ASSERT_FALSE(calc::isBracketStart(exp, 0));
	}

	TEST(Epression, isNotBracketStart_2) {
		
		string exp = ")(10)";
		ASSERT_FALSE(calc::isBracketStart(exp, 0));
	}

	TEST(Epression, isBracketEnd) {
		
		string exp = ")*";
		ASSERT_TRUE(calc::isBracketEnd(exp, 0));
	}

	TEST(Epression, isNotBracketEnd_1) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isBracketEnd(exp, 0));
	}

	TEST(Epression, isNotBracketEnd_2) {
		
		string exp = "(10)";
		ASSERT_FALSE(calc::isBracketEnd(exp, 0));
	}

	TEST(Epression, isEnd_1) {
		
		string exp = "";
		ASSERT_TRUE(calc::isEnd(exp, 0));
	}

	TEST(Epression, isEnd_2) {

		string exp = "aaaa";
		ASSERT_TRUE(calc::isEnd(exp, 3));
	}

	TEST(Epression, isNotEnd) {
		
		string exp = "*(10)";
		ASSERT_FALSE(calc::isEnd(exp, 0));
	}

	//**********
	//Digits
	//**********
	TEST(Digits, calc_1) {
		calc::Digits exp("1", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1, res);
		ASSERT_EQ(0, exp.endPos);
	}

	TEST(Digits, calc_2) {
		calc::Digits exp("1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(Digits, calc_3) {
		calc::Digits exp("(1383", 1);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(Digits, calc_4) {
		calc::Digits exp("123+1383", 4);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(7, exp.endPos);
	}

	TEST(Digits, calc_failed_1) {
		calc::Digits exp("+1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	//**********
	//Signed
	//**********
	TEST(SignedDigits, calc_1) {
		calc::SignedDigits exp("1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(SignedDigits, calc_2) {
		calc::SignedDigits exp("+1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(SignedDigits, calc_3) {
		calc::SignedDigits exp("-1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(-1383, res);
		ASSERT_EQ(4, exp.endPos);
	}

	TEST(SignedDigits, calc_4) {
		calc::SignedDigits exp("(-1383", 1);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(-1383, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(SignedDigits, calc_failed_1) {
		calc::SignedDigits exp("*1383", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	//**********
	//PlusMinus
	//**********
	TEST(PlusMinusExp, calc_1) {
		calc::PlusMinusExp exp("100+23", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(123, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(PlusMinusExp, calc_2) {
		calc::PlusMinusExp exp("1000+23*10+4", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1234, res);
		ASSERT_EQ(11, exp.endPos);
	}

	TEST(PlusMinusExp, calc_failed_1) {
		calc::PlusMinusExp exp("(1234", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	//**********
	//MulDiv
	//**********
	TEST(MulDivExp, calc_1) {
		calc::MulDivExp exp("100*23", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(2300, res);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(MulDivExp, calc_2) {
		calc::MulDivExp exp("100*234*2", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(46800, res);
		ASSERT_EQ(8, exp.endPos);
	}

	TEST(MulDivExp, calc_failed_1) {
		calc::MulDivExp exp("1234/0", 0);

		long long res = exp.calc();

		ASSERT_EQ(5, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	//**********
	//Bracket
	//**********
	TEST(BracketExp, calc_1) {
		calc::BracketExp exp("1234", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(1234, res);
		ASSERT_EQ(3, exp.endPos);
	}

	TEST(BracketExp, calc_2) {
		calc::BracketExp exp("(1234)", 0);

		long long res = exp.calc();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(5, exp.endPos);
	}

	TEST(BracketExp, calc_failed_1) {
		calc::BracketExp exp("(1234", 0);

		long long res = exp.calc();

		ASSERT_EQ(4, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	TEST(BracketExp, calc_failed_2) {
		calc::BracketExp exp("*1234", 0);

		long long res = exp.calc();

		ASSERT_EQ(0, exp.errorPos);
		ASSERT_NE(0, exp.error);
		ASSERT_EQ(0, res);
	}

	TEST(Calculate, calc_1) {
		calc::Expression exp(" ( 1234 ) ");

		long long res = exp.calc();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(9, exp.endPos);
	}

	TEST(Calculate, calc_2) {
		calc::Expression exp(" ( 1234 )");

		long long res = exp.calc();

		ASSERT_EQ(1234, res);
		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(8, exp.endPos);
	}

	TEST(Calculate, calc_3) {
		calc::Expression exp(" ( 1234 + 1 ) * 2 + 1 ");

		long long res = exp.calc();

		ASSERT_EQ(2471, res);
		ASSERT_EQ(0, exp.error);
		ASSERT_EQ(21, exp.endPos);
	}

}