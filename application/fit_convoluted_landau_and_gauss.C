#include <iostream>
#include "TMath.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"

/**
 * 任意の関数の積分を計算する関数
 */
template <typename F>
double simpson_integration(const F& func, double from, double to, int nx) {
  const double dx = (to - from) / nx;

  // 積分を実行
  double sum = 0.0;
  double x = from;
  sum -= func(x) * 0.5;
  if (from < to) {
    while (x < to) {
      sum += func(x);
      x += dx;
      sum += func(x) * 2.0;
      x += dx;
    }
  } else {
    while (x > to) {
      sum += func(x);
      x += dx;
      sum += func(x) * 2.0; 
      x += dx;
    }
  }
  sum += func(x) * 0.5;

  return sum * dx * 2.0 / 3.0;
}

/**
 * ガウス関数とランダウ関数の畳み込み積分を計算
 */
Double_t convoluted_landau_and_gauss(Double_t x, Double_t height, Double_t location, Double_t sigmaLandau, Double_t sigmaGauss) {
  // 標準偏差が正の値になるよう調整
  const Double_t absSigmaLandau = TMath::Abs(sigmaLandau);
  const Double_t absSigmaGauss  = TMath::Abs(sigmaGauss );

  // 計算後の関数の高さが、最初に指定されたheightに近づける換算係数
  const Double_t factor = 0.3989422804014 * 100 * height / absSigmaLandau / absSigmaGauss;

  // 関数の位置 (sigmaによるピーク位置の変動を補正)
  const Double_t locationLandau = location + 0.22278298 * absSigmaLandau;
  const Double_t locationGauss  = x;

  // 積分範囲を設定
  struct {
    double lower;
    double upper;
  } rangeLandau, rangeGauss, *rangeInner, *rangeOuter;

  rangeLandau.lower = locationLandau - 3.0 * absSigmaLandau;
  rangeLandau.upper = locationLandau + 6.0 * absSigmaLandau;
  rangeGauss .lower = locationGauss  - 3.0 * absSigmaGauss;
  rangeGauss .upper = locationGauss  + 3.0 * absSigmaGauss;

  rangeInner = absSigmaLandau < absSigmaGauss ? &rangeLandau : &rangeGauss;
  rangeOuter = absSigmaLandau < absSigmaGauss ? &rangeGauss  : &rangeLandau;

  // 積分の微小幅
  const Double_t dxInner = 0.02 * TMath::Min(absSigmaLandau, absSigmaGauss);
  const Double_t dxOuter = 0.02 * TMath::Max(absSigmaLandau, absSigmaGauss);

  // 被積分関数を定義
  const auto func = [=](Double_t _xi) {
    return
      TMath::Landau(_xi, locationLandau, absSigmaLandau, kFALSE) *
      TMath::Gaus(_xi, locationGauss, absSigmaGauss, kFALSE);
  };

  // 積分を実行
  Double_t sum = 0.0;
  if (rangeOuter->lower < rangeInner->lower) {
    const Int_t nx = (rangeInner->lower - rangeOuter->lower) / dxOuter + 1;
    sum += simpson_integration(func, rangeOuter->lower, rangeInner->lower, nx);
  }
  {
    const Int_t nx = (rangeInner->upper - rangeInner->lower) / dxInner + 1;
    sum += simpson_integration(func, rangeInner->lower, rangeInner->upper, nx);
  }
  if (rangeInner->upper < rangeOuter->upper) {
    const Int_t nx = (rangeOuter->upper - rangeInner->upper) / dxOuter + 1;
    sum += simpson_integration(func, rangeInner->upper, rangeOuter->upper, nx);
  }

  return factor * sum;
}

/**
 * TF1に渡すための形式に変換
 */
Double_t convoluted_landau_and_gauss_tf1(Double_t* px, Double_t* pp) {
  return convoluted_landau_and_gauss(px[0], pp[0], pp[1], pp[2], pp[3]);
}

/**
 * ガウス関数とランダウ関数の畳み込み積分関数でフィッティングを行う
 */
void fit_convoluted_landau_and_gauss() {
  // フィット範囲
  const Double_t xmin = 1200;
  const Double_t xmax = 3000;

  // ファイルに保存されているヒストグラムを開く
  TFile* input_file = new TFile("../data/data_mppc_hist.root");
  if (not input_file->IsOpen()) {
    std::cout << "Error: file was not opened" << std::endl;
    return;
  }

  TH1* hist = dynamic_cast<TH1*>(input_file->Get("hist"));
  if (not hist) {
    std::cout << "Error: hist was not found" << std::endl;
    return;
  }

  // ビンを粗くする
  hist->Rebin(8);

  // フィット結果を画面表示するように設定
  gStyle->SetOptFit(1);

  // フィット前のヒストグラムを描画
  TCanvas::MakeDefCanvas();
  gPad->SetLogy();

  hist->Draw();

  // キャンバスの更新
  gPad->Update();
  gSystem->ProcessEvents();

  // フィット関数を作る
  TF1* func = new TF1("func", convoluted_landau_and_gauss_tf1, 0.0, 1.0, 4);
  func->SetParNames("height", "#mu", "#sigma_{Landau}", "#sigma_{Gauss}");

  // パラメータの初期値を計算
  hist->GetXaxis()->SetRangeUser(xmin, xmax);

  const Int_t    maxbin = hist->GetMaximumBin();
  const Double_t maxx   = hist->GetBinCenter(maxbin);
  const Double_t maxy   = hist->GetBinContent(maxbin);
  const Double_t sigma  = hist->GetStdDev();

  const Double_t height      = maxy;
  const Double_t location    = maxx;
  const Double_t sigmaLandau = sigma / 2;
  const Double_t sigmaGauss  = sigma / 2;

  // 初期パラメータを設定
  func->SetParameters(height,
                      location,
                      sigmaLandau,
                      sigmaGauss);

  // フィットを実行
  std::cout << "start fitting" << std::endl;
  hist->GetXaxis()->UnZoom();
  hist->Fit(func, "", "", xmin, xmax);
}
