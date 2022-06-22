#include "TF1.h"

/**
 * 関数を1つ作り、それを描画する
 */
void draw_a_func() {
  // 関数を作る
  TF1* func = new TF1("name", "[0]*x*x*x + [1]*x*x + [2]*x + [3]", -10, 10);
  // new TF1(文字列1, 文字列2, 数値1, 数値2) について
  //   文字列1 ... 関数の名前(ROOTが管理するため)
  //   文字列2 ... 関数の定義
  //               関数の定義中の[0]~[3]は、関数のパラメータで、プログラム中で与えることができる
  //   数値1   ... 関数の定義域(最小値)
  //   数値2   ... 関数の定義域(最大値)
  // [[参照]]
  // TF1::TF1 https://root.cern/doc/master/classTF1.html#a81624e58e70c2963e4c141b7fa85eff1

  // 関数のパラメータを設定する
  func->SetParameter(0,  0.2);
  func->SetParameter(1, -1.0);
  func->SetParameter(2, -4.0);
  func->SetParameter(3,  1.0);
  // func->SetParameter(数値1, 数値2) について
  //   数値1 ... パラメータの番号。0はパラメータ[0]を表す
  //   数値2 ... パラメータの数値
  // [[参照]]
  // TF1::SetParameter https://root.cern/doc/master/classTF1.html#ade6e54171210c6b1b955c9f813040eb8

  // 関数の描画範囲を設定する
  func->SetMinimum(-20.0);
  func->SetMaximum(+20.0);
  // func->SetMinimum(数値) について
  //   数値 ... y方向の描画範囲の最小値
  // [[参照]]
  // TF1::SetMinimum https://root.cern/doc/master/classTF1.html#a94f28adc867a04e9d3698656b49de869
  // TF1::SetMaximum https://root.cern/doc/master/classTF1.html#a30493478fd00ed7c949f0a845517f5bb

  // 関数の描画
  func->Draw();
}
