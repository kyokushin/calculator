# �v�Z�@�v���O����
## �������j
���͂��ꂽ�������\����͂��A���̌��ʂ��琔�����v�Z���邱�Ƃɂ��܂����B

�\����͂ɂ�BNF�L�@��p���܂����B�܂�BNF�L�@�͈ȉ��̃y�[�W���Q�l�ɂ��܂����B
http://dai1741.github.io/maximum-algo-2012/docs/parsing/

�������ɂ�BNF�L�@�ňȉ����`���Ă��܂��B
```
<digits> := <digit>+
<signed digits> := <digits> | {+|-}<digits> 
<exp> := <term>[{+|-}<term>]
<term> := <factor>[{*|/}<factor>]
<factor> := <digits>|(<exp>)
```
�������ċA�ŌĂяo���悤�Ɏ������܂����B  
�܂������ɂ�C++�𗘗p���Ă��܂��B

## �r���h�ɗ��p���郉�C�u�����A�r���h�c�[��
### Windows
* cmake �o�[�W����3.0.0�ȏ� https://cmake.org/download/  
URL����Windows�p�C���X�g�[�����_�E�����[�h���A�C���X�g�[������B
* Visual Studio 2017 https://www.visualstudio.com/ja/downloads/?rr=https%3A%2F%2Fwww.microsoft.com%2Fja-jp%2Fdev  
URL����Y������G�f�B�V������I�����AC/C++�����̃C���X�g�[�����s���B
* googletest (�I�v�V����) https://github.com/google/googletest/archive/release-1.8.0.zip  
  1. URL����ZIP�t�@�C�����_�E�����[�h��A�𓀂��A�𓀂��Đ������ꂽgoogletest�f�B���N�g���Ɉړ�
  1. cmake�����s
  1. Where is source code:��googletest�̃��[�g�f�B���N�g�����w�肵�܂��B
  1. Where to build the binaries:�Ƀr���h�ɗ��p����f�B���N�g���i�ȉ��r���h�f�B���N�g���j���w�肵�܂��B
  1. CMAKE_INSTALL_PREFIX��C:\ProgramData\googletest��ݒ肷��
  1. Configure�{�^���������B�r���h�Ɏg���v���O�����̑I����ʂ��\�������̂ŁAVisual Studio2017���w�肷��B
  1. build�f�B���N�g�����ɐ������ꂽVisualStudio�̃\�����[�V�����t�@�C�����J��
  1. VisualStudio�̃��j���[����r���h���o�b�`�r���h��I��
  1. �_�C�A���O����ALL_BUILD Release�AALL_BUILD Debug�A
  INSTALL Release�AINSTALL Debug��4�Ƀ`�F�b�N�����ăr���h�����s
  1. ���ϐ���CMAKE_PREFIX_PATH���쐬���A�l�Ƃ���C:\ProgramData\googletest��
  �ݒ肷��
### Linux
Ubuntu�ł̑����z�肵�������ɂȂ��Ă��܂�
* cmake �o�[�W����3.0.0�ȏ� https://cmake.org/download/
* gcc �o�[�W����5.0�ȏ� 
* g++ �o�[�W����5.0�ȏ� 
* nkf(�����R�[�h�̕ϊ��ŗ��p)  
��L4�̃c�[���͈ȉ��̃R�}���h�ŃC���X�g�[�����܂��B  
  ```
  $ sudo apt install cmake gcc g++ nkf
  ```
* googletest (�I�v�V����) https://github.com/google/googletest/archive/release-1.8.0.zip
URL����ZIP�t�@�C�����_�E�����[�h��A�𓀂��A�𓀂��Đ������ꂽgoogletest�f�B���N�g���Ɉړ���
�ȉ��̃R�}���h�����s���C���X�g�[�����܂�
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## �r���h���@
### Windows

Windows�ł̃r���h�ɂ�Visual Studio 2017���g�p���܂��B
�܂��r���h�c�[���ɂ�CMake�𗘗p���܂��B
1. CMake�����s
2. Where is source code:�ɖ{�v���O�����̃��[�g�f�B���N�g�����w�肵�܂��B
3. Where to build the binaries:�Ƀr���h�ɗ��p����f�B���N�g���i�ȉ��r���h�f�B���N�g���j���w�肵�܂��B
4. Configure�{�^���������B�r���h�Ɏg���v���O�����̑I����ʂ��\�������̂ŁAVisual Studio2017���w�肷��B
5. �e�X�g���r���h���Ȃ��ꍇ��build_test�̃`�F�b�N���O���B
5. Generate�{�^���������AVisualStudio�̃\�����[�V�����t�@�C���𐶐�����B
7. �r���h�f�B���N�g���ɐ������ꂽ�\�����[�V�����t�@�C�����J���B
8. VisualStudio�Ńr���h����ƃr���h�f�B���N�g��/bin�ȉ��̃v���O���������������B
   1. Debug���[�h�ł́Acalcd�v���O���������������
   2. Release���[�h�ł́Acalc�v���O���������������

### Linux
�{�v���O�����̃��[�g�f�B���N�g�������Ƃ��J�n���܂��B
```
$ ls
CMakeLists.txt  src  test 
# �t�@�C���̕����R�[�h��SJIS����UTF8�ɕϊ�����
$ nkf -w --overwrite src/main.cpp
# �r���h�p�f�B���N�g���i�ȉ��r���h�f�B���N�g���j���쐬����
$ mkdir build
$ cd build
# cmake�����s���A�r���h�X�N���v�g�𐶐�����
$ cmake ..
## �e�X�g���r���h���Ȃ��ꍇ�͈ȉ������s����
# $ cmake .. -Dbuild_tests=false
# �v���O�������r���h����
$ make
# �r���h�f�B���N�g��/bin��calc����������Ă���
$ ls bin
calc
```

## ���s���@
Windows�̓R�}���h�v�����v�g���ALinux�ł̓V�F�����g�p����B
### �v���O�����N��
#### Windows
```
> calc
++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
```
#### Linux
```
$ ./calc
++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+d����͂��Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
```
### �v�Z�̎��s
��������͌�AEnter���������ƂŌv�Z���ʂ��\������܂��B
���͉\�Ȑ����͐����l�̎l�����Z�A�܂�����"()"���g�����v�Z���\�ł��B
```
++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
1 + 2 #��������͌�AEnter

== �v�Z���� == # �\�����ꂽ�v�Z����
3

++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
( 11 + 2 * ( 34 + 3 ) / 2 ) * 10 #()���g�����v�Z

== �v�Z���� ==
480
```
### �v�Z���̃G���[�ɂ���
���͂��ꂽ�����ɊԈႢ������ƃG���[��\�����܂��B
�܂��G���[�\�����ɂ͊ԈႢ���������Ǝv����ꏊ��\�����܂��B
```
++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
( 23 + 10 ) 10 # )�̌�ɐ��������邱�Ƃ��ԈႢ�̂��߃G���[�ƂȂ��Ă���

!! �v�Z�ł��܂���ł��� !!
( 23 + 10 ) 10
             ^�������Ԉ���Ă��܂�

++++++++++++++++++++++++++++++++++++++
��������͌�AEnter�������Ă�������
�I������ꍇ��Ctrl+z����͌�AEnter�������Ă�������
�ڂ����g������h����͌�AEnter�������Ă�������
( 23 + 10 ) * 10 # *��ǉ�����ƌv�Z�ł���B

== �v�Z���� ==
330
```

## ����m�F
����m�F�ɂ̓e�X�g��L���ɂ��Ď��s����K�v������܂��B
�f�t�H���g�ł͗L���ɂȂ��Ă��܂��B
�e�X�g�p�v���O�����̓r���h�f�B���N�g��/bin�ȉ��ɂ���calcTest�ł��B
���s���AFailed���������Ă��Ȃ���Ζ�肠��܂���B

### Windows
```
> calcTest
```
### Linux
```
$ ./calcTest
```