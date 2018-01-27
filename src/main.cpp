#include <iostream>
#include <string>
#include "calcexp.h"

using namespace std;

void printUsage() {
	cout
		<< "***********************************************" << endl
		<< "* 使い方" << endl
		<< "数式を入力したあとEnterを押すと計算結果を表示します" << endl
		<< "整数の四則演算を使った計算ができます" << endl
		<< "また()を使った計算も可能です" << endl
		<< "空白文字は無視されます" << endl
		<< "** 入力例" << endl
		<< "-10*2" << endl
		<< "(10+2)*2" << endl
		<< "10/(2*4)+2" << endl
		<< "** 注意" << endl
		<< "* 終了方法" << endl
		<< "Ctrl + z を入力後、Enterを押す" << endl
		<< "* 使い方の表示"
		<< "h を入力後、Enterを押す" << endl
		<< "***********************************************" << endl
		<< endl;
}

int main(int argc, char** argv) {

	while (true) {
		cout
			<< "++++++++++++++++++++++++++++++++++++++" << endl
			<< "数式を入力後、Enterを押してください" << endl
			<< "終了する場合はCtrl+zを入力後、Enterを押してください" << endl
			<< "詳しい使い方はhを入力後、Enterを押してください" << endl;

		string e;
		getline(cin, e);
		if (e[0] == 0) {
			break;
		}
		if (e[0] == 'h') {
			printUsage();
		}
		calc::Expression exp(e);
		long long res = exp.calc();
		if (exp.hasError()) {
			cout
				<< "!! 計算できませんでした !!" <<  endl
				<< e << endl;
			for (int i = 0; i < exp.error.pos; i++) {
				cout << " ";
			}
			cout << "^ここが間違っています" << endl;
		}
		else if (exp.endPos + 1 != e.size()) {
			cout
				<< "!! 計算できませんでした !!" << endl
				<< e << endl;
			for (int i = 0; i < exp.endPos + 1; i++) {
				cout << " ";
			}
			cout << "^ここが間違っています" << endl;
		}
		else {
			cout << endl
				<< "== 計算結果 ==" << endl
				<< res << endl;
		}
		cout << endl;
	}

	cout << "プログラムを終了します" << endl;

	return 0;
}
