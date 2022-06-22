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
void draw_a_func_advance() {
  // 関数を作る
  TF1* func = new TF1("name", difficult_function, -10, 10, 4);

  // 関数のパラメータに名前をつける
  func->SetParName(0, "amplitude");
  func->SetParName(1, "period"   );
  func->SetParName(2, "threshold");
  func->SetParName(3, "decaytime");

  // 関数のパラメータを設定する
  func->SetParameter(0,  1.0); // amplitude
  func->SetParameter(1,  3.0); // period
  func->SetParameter(2, -5.0); // threshold
  func->SetParameter(3,  4.0); // decaytime

  // 関数の描画範囲を設定する
  func->SetMinimum(-2.0);
  func->SetMaximum(+2.0);

  // 関数の描画
  func->Draw();
}
