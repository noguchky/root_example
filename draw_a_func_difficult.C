#include "TF1.h"

/**
 * xが閾値未満の場合は正弦波で、それ以上では指数関数で減衰していく関数
 */
Double_t difficult_function(Double_t* px, Double_t* pp) {
  // 関数の変数を取得
  const Double_t x = px[0];

  // 関数のパラメータを取得
  const Double_t amplitude = pp[0];
  const Double_t period    = pp[1];
  const Double_t threshold = pp[2];
  const Double_t decaytime = pp[3];

  // パラメータで決められた振幅・波長の正弦波
  Double_t y = amplitude * TMath::Sin(x / period * TMath::TwoPi());

  // xが閾値以上の場合には減衰させる
  if (x > threshold) {
    y *= TMath::Exp(- (x - threshold) / decaytime);
  }

  // xに対するyの値を返す
  return y;
}

/**
 * 定義が複雑な関数を1つ作り、それを描画する
 */
void draw_a_func_difficult() {
  // 関数を作る
  TF1* func = new TF1("name", difficult_function, -10, 10, 4);
  // new TF1(文字列1, 関数, 数値1, 数値2, 数値3) について
  //   文字列1 ... 関数の名前(ROOTが管理するため)
  //   関数    ... 関数の定義
  //               "difficult_function"と同様に、引数が(Double_t*, Duoble_t*)で、戻り値がDouble_tである関数を指定する
  //   数値1   ... 関数の定義域(最小値)
  //   数値2   ... 関数の定義域(最大値)
  //   数値3   ... 指定した関数の
  // [[参照]]
  // TF1::TF1 https://root.cern/doc/master/classTF1.html#aa8905d28455ed7be02019f20b9cc5827

  // 関数のパラメータを設定する
  func->SetParameter(0,  1.0); // amplitude
  func->SetParameter(1,  3.0); // period
  func->SetParameter(2, -5.0); // threshold
  func->SetParameter(3,  4.0); // decaytime
  // func->SetParameter(数値1, 数値2) について
  //   数値1 ... パラメータの番号。0はパラメータ[0]を表す
  //   数値2 ... パラメータの数値
  // [[参照]]
  // TF1::SetParameter https://root.cern/doc/master/classTF1.html#ade6e54171210c6b1b955c9f813040eb8

  // 関数の描画範囲を設定する
  func->SetMinimum(-2.0);
  func->SetMaximum(+2.0);
  // func->SetMinimum(数値) について
  //   数値 ... y方向の描画範囲の最小値
  // [[参照]]
  // TF1::SetMinimum https://root.cern/doc/master/classTF1.html#a94f28adc867a04e9d3698656b49de869
  // TF1::SetMaximum https://root.cern/doc/master/classTF1.html#a30493478fd00ed7c949f0a845517f5bb

  // 関数の描画
  func->Draw();
}
