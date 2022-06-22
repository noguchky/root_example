#include "TH1.h"
#include "TAxis.h"

/**
 * ヒストグラムを1つ作り、それを描画する
 */
void draw_a_hist_advance() {
  // ヒストグラムを作り、値を詰める
  TH1* hist = new TH1D("name", "title", 10, -4, 6);
  hist->Fill(-1);
  hist->Fill(1);
  hist->Fill(2);
  hist->Fill(2);
  hist->Fill(5);

  // ヒストグラムの線の色を変更する
  hist->SetLineColor(kRed);

  // x軸y軸のタイトルを設定する
  hist->GetXaxis()->SetTitle("sample");
  hist->GetYaxis()->SetTitle("entries");

  // 描画するyの範囲を指定する
  hist->SetMinimum(-1);
  hist->SetMaximum(5);

  // 描画するxの範囲を指定する
  hist->GetXaxis()->SetRangeUser(-1, 5);

  // ヒストグラムを描画する
  hist->Draw();
}
