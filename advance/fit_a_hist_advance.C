#include "TH1.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TStyle.h"

/**
 * ヒストグラムを作成し、フィットする
 */
void fit_a_hist_advance() {
  // フィッティング結果をキャンバスに表示させる
  gStyle->SetOptFit(1);
  
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

  // パラメータに名前をつける
  func->SetParName(0, "amplitude");
  func->SetParName(1, "mean");
  func->SetParName(2, "sigma");
  func->SetParName(3, "background");

  // フィッティングの初期値を、ヒストグラムの情報をもとに設定する
  func->SetParameter(0, hist->GetBinContent(hist->GetMaximumBin())); // ヒストグラムの最大値を設定
  func->SetParameter(1, hist->GetMean()); // ヒストグラムの平均値を設定
  func->SetParameter(2, hist->GetStdDev()); // ヒストグラムの標準偏差を設定
  func->SetParameter(3, hist->GetBinContent(hist->GetMinimumBin())); // ヒストグラムの最小値を設定

  // パラメータのとりうる範囲を制限する
  func->SetParLimits(0, 0, 2.0 * func->GetParameter(0)); // 0以上、最大値の倍以下
  func->SetParLimits(1, -5, 5); // ガウス分布のピーク位置がヒストグラムの範囲内
  func->SetParLimits(2, 0, 10); // ガウス分布の標準偏差がヒストグラムの範囲よりは小さい
  func->SetParLimits(3, -func->GetParameter(0), func->GetParameter(0)); // 背景事象成分は +-最大値の間

  // ガウス分布でフィットする
  hist->Fit(func);
}
