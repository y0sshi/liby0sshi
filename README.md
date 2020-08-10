# y0sshi ライブラリ
## 概要
y0sshiが制作しているライブラリです。  
C++とPython3を対象としています。  

## インストール
```
make
sudo make install
```
## アンインストール
```
sudo make uninstall
```

## 使い方
### C++
#### psplクラス(zynq向け)
- ヘッダをインクルードする
```
#include <y0sshi/pspl.hpp>
```
- y0sshi::psplクラスの変数を宣言する
  - コンストラクタが/dev/uio0へアクセスするため、実行時にsudoをつけていないとパーミッションエラーになる
```
y0sshi::pspl fpga;
```
- 指定したアドレスのレジスタ値を取得する
```
fpga.read(int addr)
```
- レジスタの指定したアドレスに、指定した値を書き込む
```
fpga.write(int addr, int value)
```
#### コンパイルと実行
```
g++ source.cpp -o exe `pkg-config --libs y0sshi` 
sudo ./exe
```

### python3
#### psplクラス(zynq向け)
- y0sshi モジュールをインポートする
```
import y0sshi
```
- zynq の PL をオープンする
  - コンストラクタが/dev/uio0へアクセスするため、実行時にsudoをつけていないとパーミッションエラーになる
```
fpga = y0sshi.pspl()
```
- 指定したアドレスのレジスタ値を取得する
```
fpga.read(int addr)
```
- レジスタの指定したアドレスに、指定した値を書き込む
```
fpga.write(int addr, int value)
```
#### 実行
```
sudo python3 source.py
```

## サンプルコード
[python3 サンプルコード](./sample/pspl.py)  
[C++ サンプルコード](./sample/main.cpp)
