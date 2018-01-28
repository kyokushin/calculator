#include <iostream>
#include <string>

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

	long long res = calcPlusMinusExp();
	if (endPos + 1 < e.size()) {
		endPos = skip(e, endPos + 1);
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

long long calc::Expression::calcDigits() {
	chomp();
	if (e[startPos] < '0' || '9' < e[startPos]) {
		setError(101, startPos);
		return 0;
	}
	size_t end = e.find_first_not_of("0123456789", startPos);
	if (end == string::npos) {
		endPos = e.size() - 1;
	}
	else {
		endPos = end - 1;
	}
	size_t len = endPos - startPos + 1;
	if (len > 8) {
		setError(102, startPos);
		return 0;
	}

	const string valStr = e.substr(startPos, len);
	return stoll(valStr);
}

long long calc::Expression::calcSignedDigits() {

	chomp();
	if (isDigits(e, startPos)) {
		auto res = calcDigits();
		if (hasError()) {
			return 0;
		}
		return res;
	}

	const char c = e[skip(e, startPos)];
	if (isSignedDigits(e, startPos)) {
		if (c == '+') {
			startPos++;
			auto res = calcDigits();
			if (hasError()) {
				return 0;
			}
			return res;
		}
		else if (c == '-') {
			startPos++;
			auto res = calcDigits();
			if (hasError()) {
				return 0;
			}
			return -1 * res;
		}
		else {
			setError(1);
			return 0;
		}
	}

	setError(202, startPos);
	return 0;
}

long long calc::Expression::calcPlusMinusExp() {

	chomp();
	startPos = skip(e, startPos);
	auto val0 = calcMulDivExp();
	if (hasError()) {
		return 0;
	}

	if (endPos + 1 == e.size()) {
		return val0;
	}

	if (e.size() < endPos + 1) {
		setError(301, endPos);
		return 0;
	}

	auto expPos = skip(e, endPos + 1);
	endPos = skip(e, endPos);
	auto c = e[expPos];
	auto res = val0;
	for (; ('+' == c || '-' == c) && expPos < e.size();
		expPos = skip(e, endPos + 1), c = e[expPos]) {

		if ('+' == c) {
			startPos = expPos + 1;
			auto val1 = calcMulDivExp();
			if (hasError()) {
				return 0;
			}

			res += val1;
		}

		if ('-' == c) {
			startPos = expPos + 1;
			auto val1 = calcMulDivExp();
			if (hasError()) {
				return 0;
			}

			res -= val1;
		}
	}
	return res;

}
long long calc::Expression::calcMulDivExp() {

	chomp();
	auto val0 = calcBracketExp();
	if (hasError()) {
		return 0;
	}

	if (e.size() <= endPos + 1) {
		return val0;
	}

	auto expPos = skip(e, endPos + 1);
	auto c = e[expPos];
	auto res = val0;
	for (; ('*' == c || '/' == c) && expPos < e.size();
		expPos = skip(e, endPos + 1), c = e[expPos]) {
		if ('*' == c) {
			startPos = expPos + 1;
			auto val1 = calcBracketExp();
			if (hasError()) {
				return 0;
			}

			res *= val1;
		}

		if ('/' == c) {
			startPos = expPos + 1;
			auto val1 = calcBracketExp();
			if (hasError()) {
				return 0;
			}
			if (val1 == 0) {
				setError(401, startPos);
				return 0;
			}

			res /= val1;
		}
	}

	return res;
}

long long calc::Expression::calcBracketExp() {

	chomp();
	if (isSignedDigits(e, startPos)) {
		auto res = calcSignedDigits();
		return res;
	}

	if ('(' == e[skip(e, startPos)]) {
		startPos++;
		auto val = calcPlusMinusExp();
		if (hasError()) {
			return 0;
		}

		if (endPos + 1 < e.size() && ')' == e[skip(e, endPos + 1)]) {
			endPos = skip(e, endPos + 1);
			return val;
		}

		setError(501, endPos);
		return 0;
	}

	setError(2, startPos);
	return 0;
}

void calc::Expression::chomp() {
	startPos = skip(e, startPos);
}
