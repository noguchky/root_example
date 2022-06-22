#include "TH1.h"
#include "TF1.h"
#include "TRandom3.h"

/**
 * ヒストグラムを作成し、フィットする
 */
void fit_a_hist() {
  // ヒストグラムを作る
  TH1* hist = new TH1D("name", "title", 50, -5, 5);

  // ガウス分布でヒストグラムに詰める
  hist->FillRandom("gaus", 1000);

  // ノイズ成分を詰める
  TRandom3 rand;
  for (Int_t i = 0; i < 1000; ++i) {
    hist->Fill(rand.Uniform(-10, 10));
  }

  // フィッティング関数を作る
  TF1* func = new TF1("func", "[0] * TMath::Gaus(x,[1],[2]) + [3]", -5, 5);

  // フィッティングの初期値を設定する
  func->SetParameter(0, 100);
  func->SetParameter(1,   0);
  func->SetParameter(2,   1);
  func->SetParameter(3,  10);

  // ガウス分布でフィットする
  hist->Fit(func);
}
