#include <string>
#include <memory>

#include "calcexp.h"

using namespace std;

size_t calc::skip(const string& s, size_t pos) {
	while ( pos < s.size() && s[pos] == ' ') pos++;
	if (pos >= s.size()) pos = s.size() - 1;
	return pos;
}

bool calc::isDigits(const string& s, size_t pos) {
	const char& c = s[skip(s, pos)];
	return '0' <= c && c <= '9';
}

bool calc::isSignedDigits(const string& s, size_t pos) {
	size_t befPos = pos - 1;
	size_t nexPos = pos + 1;
	return
		//pos‚ª”Žš‚È‚ç
		isDigits(s, pos)
		//pos‚ª0‚Å+|-‚È‚ç
		|| (pos == 0 && ('+' == s[pos] || '-' == s[pos])
			&& isDigits(s, nexPos))
		//pos‚ª1ˆÈã‚Å+|-‚È‚ç
		|| (pos > 0 && !isDigits(s, befPos)
			&& ('+' == s[pos] || '-' == s[pos])
			&& isDigits(s, nexPos));
}

bool calc::isPlusMinus(const string& s, size_t pos) {
	const char& c = s[pos];
	return '+' == c || '-' == c;
}
bool calc::isMulDiv(const string& s, size_t pos) {
	const char& c = s[pos];
	return '*' == c || '/' == c;
}
bool calc::isBracketStart(const string& s, size_t pos) {
	const char& c = s[pos];
	return '(' == c;
}
bool calc::isBracketEnd(const string& s, size_t pos) {
	const char& c = s[pos];
	return ')' == c;
}
bool calc::isEnd(const string& s, size_t pos) {
	return s.size() == 0 || s.size() == pos + 1;
}

calc::Error::Error()
	:code(0),pos(0)
{}

calc::Error::Error(const Error& e)
	: code(e.code), pos(e.pos)
{}

calc::Error& calc::Error::operator=(const Error& e) {
	code = e.code;
	pos = e.pos;
	return *this;
}

calc::Expression::Expression(const string& e)
	:e(e), startPos(skip(e, 0)), endPos(0), baseError(0)
{}

calc::Expression::Expression(const string& e, size_t pos, int error)
	: e(e), startPos(skip(e, pos)), endPos(pos), baseError(error)
{}

long long calc::Expression::calc() {
	//check bracket
	auto count = 0;
	for (auto i = 0; i < e.size(); i++) {
		count += '(' == e[i] ? 1 : ')' == e[i] ? -1 : 0;
		if (count < 0) {
			setError(1, i);
			endPos = i;
			return 0;
		}
	}
	if (count != 0) {
		setError(2, e.size() - 1);
		return 0;
	}

	PlusMinusExp exp(e, 0);
	long long res = exp.calc();
	error = exp.error;
	if (exp.endPos + 1 < e.size()) {
		endPos = skip(e, exp.endPos + 1);
	}
	else {
		endPos = exp.endPos;
	}
	return res;
}

void calc::Expression::setError(int code, size_t pos) {
	error.pos = pos < 0 ? startPos : pos;
	error.code = baseError + code;
}

bool calc::Expression::hasError() {
	return error.code != 0;
}

calc::Digits::Digits(const string& e, size_t pos)
	:Expression(e, pos, 100)
{}

calc::Digits::Digits(const calc::Digits& src)
	: Expression(src.e, src.startPos, 100)
{}

calc::Digits::Digits(const string& e, size_t pos, int error)
	: Expression(e, pos, error)
{}

long long calc::Digits::calc() {
	if (e[startPos] < '0' || '9' < e[startPos]) {
		setError(1, startPos);
		return 0;
	}
	size_t end = e.find_first_not_of("0123456789", startPos);
	if (end == string::npos) {
		endPos = e.size() - 1;
	}
	else {
		endPos = end - 1;
	}
	const string valStr = e.substr(startPos, endPos - startPos + 1);
	return stoll(valStr);
}

calc::SignedDigits::SignedDigits(const string& e, size_t pos)
	:Digits(e, pos, 200)
{}
long long calc::SignedDigits::calc() {

	if (isDigits(e, startPos)) {
		Digits val(e, startPos);
		auto res = val.calc();
		if (val.hasError()) {
			error = val.error;
			return 0;
		}
		endPos = val.endPos;
		return res;
	}

	const char c = e[skip(e, startPos)];
	if (isSignedDigits(e, startPos)) {
		if (c == '+') {
			Digits val(e, startPos + 1);
			auto res = val.calc();
			if (val.hasError()) {
				error = val.error;
				return 0;
			}
			endPos = val.endPos;
			return res;
		}
		else if (c == '-') {
			Digits val(e, startPos + 1);
			auto res = val.calc();
			if (val.hasError()) {
				error = val.error;
				return 0;
			}
			endPos = val.endPos;
			return -1 * res;
		}
		else {
			setError(1);
			return 0;
		}
	}

	setError(2, startPos);
	return 0;
}

calc::PlusMinusExp::PlusMinusExp(const string& e, size_t pos)
	:Expression(e, pos, 300)
{}
long long calc::PlusMinusExp::calc() {


	MulDivExp exp0(e, startPos);
	auto val0 = exp0.calc();
	if (exp0.hasError()) {
		error = exp0.error;
		return 0;
	}

	if (exp0.endPos + 1 == e.size()) {
		endPos = exp0.endPos;
		return val0;
	}

	if (e.size() < exp0.endPos + 1) {
		setError(1, exp0.endPos);
		return 0;
	}

	auto expPos = skip(e, exp0.endPos + 1);
	endPos = skip(e, exp0.endPos);
	auto c = e[expPos];
	auto res = val0;
	for (; ('+' == c || '-' == c) && expPos < e.size();
		expPos = skip(e, endPos + 1), c = e[expPos]) {

		if ('+' == c) {
			MulDivExp exp1(e, expPos + 1);
			auto val1 = exp1.calc();
			if (exp1.hasError()) {
				error = exp1.error;
				return 0;
			}

			res += val1;
			endPos = exp1.endPos;
		}

		if ('-' == exp0.endPos + 1) {
			MulDivExp exp1(e, expPos + 1);
			auto val1 = exp1.calc();
			if (exp1.hasError()) {
				error = exp1.error;
				return 0;
			}

			res -= val1;
			endPos = exp1.endPos;
		}
	}
	return res;

}
calc::MulDivExp::MulDivExp(const string& e, size_t pos)
	: Expression(e, pos, 400)
{}
long long calc::MulDivExp::calc() {

	BracketExp exp0(e, startPos);
	auto val0 = exp0.calc();
	if (exp0.hasError()) {
		error = exp0.error;
		return 0;
	}

	if (e.size() <= exp0.endPos + 1) {
		endPos = exp0.endPos;
		return val0;
	}

	auto expPos = skip(e, exp0.endPos + 1);
	endPos = exp0.endPos;
	auto c = e[expPos];
	auto res = val0;
	for (; ('*' == c || '/' == c) && expPos < e.size();
		expPos = skip(e, endPos + 1), c = e[expPos]) {
		if ('*' == c) {
			BracketExp exp1(e, expPos + 1);
			auto val1 = exp1.calc();
			if (exp1.hasError()) {
				error = exp1.error;
				return 0;
			}

			res *= val1;
			endPos = exp1.endPos;
		}

		if ('/' == c) {
			BracketExp exp1(e, expPos + 1);
			auto val1 = exp1.calc();
			if (exp1.hasError()) {
				error = exp1.error;
				return 0;
			}
			if (val1 == 0) {
				setError(1, exp1.startPos);
				return 0;
			}

			res /= val1;
			endPos = exp1.endPos;
		}
	}

	return res;
}

calc::BracketExp::BracketExp(const string& e, size_t pos)
	: Expression(e, pos, 500)
{}
long long calc::BracketExp::calc() {
	if (isSignedDigits(e, startPos)) {
		SignedDigits digits(e, startPos);
		auto res = digits.calc();
		endPos = digits.endPos;
		return res;
	}

	if ('(' == e[skip(e, startPos)]) {
		PlusMinusExp exp(e, startPos + 1);
		auto val = exp.calc();
		if (exp.hasError()) {
			error = exp.error;
			return 0;
		}

		if (exp.endPos + 1 < e.size() && ')' == e[skip(e, exp.endPos + 1)]) {
			endPos = skip(e, exp.endPos + 1);
			return val;
		}

		setError(1, exp.endPos);
		return 0;
	}

	setError(2, startPos);
	return 0;
}