#ifndef calcexp_h
#define calcexp_h

#include <string>

namespace calc {

	size_t skip(const std::string& s, size_t pos);

	bool isDigits(const std::string& s, size_t pos );
	bool isSignedDigits(const std::string& s, size_t pos );
	bool isPlusMinus(const std::string& s, size_t pos );
	bool isMulDiv(const std::string& s, size_t pos );
	bool isBracketStart(const std::string& s, size_t pos );
	bool isBracketEnd(const std::string& s, size_t pos );
	bool isEnd(const std::string& s, size_t pos);

	class Error {
	public:
		Error();
		Error(const Error& e);
		Error& operator=(const Error& e);
		int code;
		size_t pos;
	};

	class Expression {
	protected:
		Expression(const std::string& e, size_t pos, int error);
	public:
		Expression(const std::string& e);
		long long calc();
		long long calcDigits();
		long long calcSignedDigits();
		long long calcPlusMinusExp();
		long long calcMulDivExp();
		long long calcBracketExp();
		void chomp();
		void setError(int code, size_t pos = -1);
		bool hasError();
		const std::string e;
		const int baseError;
		size_t startPos = 0;
		size_t endPos = 0;
		Error error;
	};

}
#endif