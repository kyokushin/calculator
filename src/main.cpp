#include <iostream>
#include <string>
#include "calcexp.h"

using namespace std;

void printUsage() {
	cout
		<< "***********************************************" << endl
		<< "* �g����" << endl
		<< "��������͂�������Enter�������ƌv�Z���ʂ�\�����܂�" << endl
		<< "�ő�8���̐����̎l�����Z���g�����v�Z���ł��܂�" << endl
		<< "�܂�()���g�����v�Z���\�ł�" << endl
		<< "�󔒕����͖�������܂�" << endl
		<< "** ���͗�" << endl
		<< "-10*2" << endl
		<< "(10+2)*2" << endl
		<< "10/(2*4)+2" << endl
		<< "** ����" << endl
		<< "* �I�����@" << endl
#if defined(_WIN32)
		<< "Ctrl + z ����͌�AEnter������" << endl
#elif defined(linux)
		<< "Ctrl + d �����" << endl
#endif
		<< "* �g�����̕\��"
		<< "h ����͌�AEnter������" << endl
		<< "***********************************************" << endl
		<< endl;
}

int main(int argc, char** argv) {

	while (true) {
		cout
			<< "++++++++++++++++++++++++++++++++++++++" << endl
			<< "��������͌�AEnter�������Ă�������" << endl
#if defined(_WIN32)
			<< "�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������" << endl
#elif defined(linux)
			<< "�I������ꍇ��Ctrl+d����͂��Ă�������" << endl
#endif
			<< "�ڂ����g������h����͌�AEnter�������Ă�������" << endl;

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
		cout << endl;
		if (exp.hasError()) {
			string message;
			if (exp.error.code == 102) {
				message = "���͂ł��鐔�l��8���܂łł�";
			}
			else {
				message = "";
			}
			cout
				<< "!! �v�Z�ł��܂���ł��� !!" << endl
				<< e << endl;
			for (int i = 0; i < exp.error.pos; i++) cout << " ";
			cout << "^�������Ԉ���Ă��܂�" << endl;
			if (message.size() > 0) {
				for (int i = 0; i < exp.error.pos; i++) cout << " ";
				cout << message << endl;
			}
		}
		else if (exp.endPos + 1 != e.size()) {
			cout
				<< "!! �v�Z�ł��܂���ł��� !!" << endl
				<< e << endl;
			for (int i = 0; i < exp.endPos + 1; i++) {
				cout << " ";
			}
			cout << "^�������Ԉ���Ă��܂�" << endl;
		}
		else {
			cout
				<< "== �v�Z���� ==" << endl
				<< res << endl;
		}
		cout << endl;
	}

	cout << "�v���O�������I�����܂�" << endl;

	return 0;
}
