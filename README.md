# 計算機プログラム
## 実装方針
入力された数式を構文解析し、その結果から数式を計算することにしました。

構文解析にはBNF記法を用いました。またBNF記法は以下のページを参考にしました。
http://dai1741.github.io/maximum-algo-2012/docs/parsing/

実装時にはBNF記法で以下を定義しています。
```
<digits> := <digit>+
<signed digits> := <digits> | {+|-}<digits> 
<exp> := <term>[{+|-}<term>]
<term> := <factor>[{*|/}<factor>]
<factor> := <digits>|(<exp>)
```
これらを再帰で呼び出すように実装しました。  
また実装にはC++を利用しています。

## ビルドに利用するライブラリ、ビルドツール
### Windows
* cmake バージョン3.0.0以上 https://cmake.org/download/  
URLからWindows用インストーラをダウンロードし、インストールする。
* Visual Studio 2017 https://www.visualstudio.com/ja/downloads/?rr=https%3A%2F%2Fwww.microsoft.com%2Fja-jp%2Fdev  
URLから該当するエディションを選択し、C/C++向けのインストールを行う。
* googletest (オプション) https://github.com/google/googletest/archive/release-1.8.0.zip  
  1. URLからZIPファイルをダウンロード後、解凍し、解凍して生成されたgoogletestディレクトリに移動
  1. cmakeを実行
  1. Where is source code:にgoogletestのルートディレクトリを指定します。
  1. Where to build the binaries:にビルドに利用するディレクトリ（以下ビルドディレクトリ）を指定します。
  1. CMAKE_INSTALL_PREFIXにC:\ProgramData\googletestを設定する
  1. Configureボタンを押す。ビルドに使うプログラムの選択画面が表示されるので、Visual Studio2017を指定する。
  1. buildディレクトリ内に生成されたVisualStudioのソリューションファイルを開く
  1. VisualStudioのメニューからビルド＞バッチビルドを選択
  1. ダイアログ内のALL_BUILD Release、ALL_BUILD Debug、
  INSTALL Release、INSTALL Debugの4つにチェックを入れてビルドを実行
  1. 環境変数にCMAKE_PREFIX_PATHを作成し、値としてC:\ProgramData\googletestを
  設定する
### Linux
Ubuntuでの操作を想定した説明になっています
* cmake バージョン3.0.0以上 https://cmake.org/download/
* gcc バージョン5.0以上 
* g++ バージョン5.0以上 
* nkf(文字コードの変換で利用)  
上記4つのツールは以下のコマンドでインストールします。  
  ```
  $ sudo apt install cmake gcc g++ nkf
  ```
* googletest (オプション) https://github.com/google/googletest/archive/release-1.8.0.zip
URLからZIPファイルをダウンロード後、解凍し、解凍して生成されたgoogletestディレクトリに移動し
以下のコマンドを実行しインストールします
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

## ビルド方法
### Windows

WindowsでのビルドにはVisual Studio 2017を使用します。
またビルドツールにはCMakeを利用します。
1. CMakeを実行
2. Where is source code:に本プログラムのルートディレクトリを指定します。
3. Where to build the binaries:にビルドに利用するディレクトリ（以下ビルドディレクトリ）を指定します。
4. Configureボタンを押す。ビルドに使うプログラムの選択画面が表示されるので、Visual Studio2017を指定する。
5. テストをビルドしない場合はbuild_testのチェックを外す。
5. Generateボタンを押し、VisualStudioのソリューションファイルを生成する。
7. ビルドディレクトリに生成されたソリューションファイルを開く。
8. VisualStudioでビルドするとビルドディレクトリ/bin以下のプログラムが生成される。
   1. Debugモードでは、calcdプログラムが生成される
   2. Releaseモードでは、calcプログラムが生成される

### Linux
本プログラムのルートディレクトリから作業を開始します。
```
$ ls
CMakeLists.txt  src  test 
# ファイルの文字コードをSJISからUTF8に変換する
$ nkf -w --overwrite src/main.cpp
# ビルド用ディレクトリ（以下ビルドディレクトリ）を作成する
$ mkdir build
$ cd build
# cmakeを実行し、ビルドスクリプトを生成する
$ cmake ..
## テストをビルドしない場合は以下を実行する
# $ cmake .. -Dbuild_tests=false
# プログラムをビルドする
$ make
# ビルドディレクトリ/binにcalcが生成されている
$ ls bin
calc
```

## 実行方法
Windowsはコマンドプロンプトを、Linuxではシェルを使用する。
### プログラム起動
#### Windows
```
> calc
++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+zを入力後、Enterを押してください
詳しい使い方はhを入力後、Enterを押してください
```
#### Linux
```
$ ./calc
++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+dを入力してください
詳しい使い方はhを入力後、Enterを押してください
```
### 計算の実行
数式を入力後、Enterを押すことで計算結果が表示されます。
入力可能な数式は整数値の四則演算、また括弧"()"を使った計算も可能です。
```
++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+zを入力後、Enterを押してください
詳しい使い方はhを入力後、Enterを押してください
1 + 2 #数式を入力後、Enter

== 計算結果 == # 表示された計算結果
3

++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+zを入力後、Enterを押してください
詳しい使い方はhを入力後、Enterを押してください
( 11 + 2 * ( 34 + 3 ) / 2 ) * 10 #()を使った計算

== 計算結果 ==
480
```
### 計算時のエラーについて
入力された数式に間違いがあるとエラーを表示します。
またエラー表示時には間違いがあったと思われる場所を表示します。
```
++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+zを入力後、Enterを押してください
詳しい使い方はhを入力後、Enterを押してください
( 23 + 10 ) 10 # )の後に数字があることが間違いのためエラーとなっている

!! 計算できませんでした !!
( 23 + 10 ) 10
             ^ここが間違っています

++++++++++++++++++++++++++++++++++++++
数式を入力後、Enterを押してください
終了する場合はCtrl+zを入力後、Enterを押してください
詳しい使い方はhを入力後、Enterを押してください
( 23 + 10 ) * 10 # *を追加すると計算できる。

== 計算結果 ==
330
```

## 動作確認
動作確認にはテストを有効にして実行する必要があります。
デフォルトでは有効になっています。
テスト用プログラムはビルドディレクトリ/bin以下にあるcalcTestです。
実行し、Failedが発生していなければ問題ありません。

### Windows
```
> calcTest
```
### Linux
```
$ ./calcTest
```