# k-n-ThreshholdSecret
(k,n)閾値秘密分散法のコード．
ラグランジュ補間を使っている．



1 環境

実行環境として、wsl２+ubuntu の仮想マシンを使う．
使用するプログラミング言語はC++である．

2 設計方針

k 人の人に関してはクラスのカプセル化を使って直接秘密S にアクセスできないよ
うにする．

3 ガロア体

今回のプログラムを書く上で必要な知識としてガロア体がある．ガロア体とは一つ
の整数を使って表される整数の部分集合である．今回は257 のガロア体を使う．ガロ
ア体の計算をするためには加減乗除の方法を変更する必要がある．Galoisクラスがそれにあたる．

4 クラスPerson

変数k とn は(k, n)閾値法のk とn である．変数no はそれぞれのインスタンスに着
けられた番号である．変数S は秘密である．変数table は満場一致のマルチパーティ計
算をするときに使用する値を一時的に格納しておくために使用する．変数c はマルチ
パーティ計算をするときに使用する係数を格納しておく．
ポインタ型の変数share とtable_share はどちらもシェアを格納しておくための配列
である．配列の⾧さが不明のためポインタ型で宣言し、配列を動的生成している．変数
a に関してはシェアを生成するときに使用する係数を格納しておくための配列である．
これも配列の⾧さが不明であるため、ポインタ型で宣言し、配列を動的生成している．

5 秘密分散法の実装

先に紹介したPerson クラスと関数fix()を使って秘密分散法の復号を行う．fix()はラ
グランジュ補間を使って秘密S を計算している．すべての計算にGalois クラスで定義した計算関数を使っていることに注意する．これ
を使わなければ正しい計算結果は得られない．

6 マルチパーティ計算の実装

マルチパーティ計算は乗法準同型を使った満場一致の多数決と加法準同型を使った
賛成の数を数える多数決の二つを実装した．

7 満場一致の多数決

乗法準同型を活用する過程で(k, n)から(k+1, n)に代わってしま
うのでそれを考慮しながら計算をしなくてはならない．

8 一定数の賛成を数える多数決

今回のプログラムでは0 を反対．1 を賛成としている．そのため、賛成の数を数える
ためにはそれぞれの秘密の合算を求めればいいだけである．この時に加法準同型の性
質を使う．しかし、加法準同型は満場一致の多数決で使った乗法準同型とは異なり、(k,
n)から(k+1, n)に代わってしまうことはない．そのため、シェアの合計を求めるだけで
いい．
