#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TMath.h"

/**
 * エラーつきグラフを作り、フィットする
 */
void fit_a_graph_with_errors() {
  // グラフを作る
  TGraphErrors* graph = new TGraphErrors();

  // グラフの点のスタイル(形状)を見やすいものに変更する
  graph->SetMarkerStyle(kFullCircle);

  // グラフの点を設定する
  TRandom3 rand;
  for (Int_t i = 0; i < 20; ++i) {
	const Double_t y = 100.0 * TMath::Exp(- i / 10.0);
	graph->SetPoint(i, i, rand.Gaus(y, TMath::Sqrt(y)));
	graph->SetPointError(i, 0.0, TMath::Sqrt(y));
  }

  // フィッティング関数を作る
  TF1* func = new TF1("func", "[0]*TMath::Exp(-x/[1])", 0, 20);

  // フィッティングの初期値を設定する
  func->SetParameters(100.0, 0.1);

  // フィットする
  graph->Fit(func);

  // フィット結果を描画する
  graph->Draw("AP");
}
