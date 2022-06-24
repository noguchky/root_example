#include "TH1.h"
#include "TLegend.h"

/**
 * ヒストグラムを2つ作り、凡例と共にそれらを1つのキャンバスに描画する
 */
void draw_two_hists_with_legend() {
  // 1つ目のヒストグラムを作り、値を詰める
  TH1* hist_1 = new TH1D("name_1", "title_1", 10, -1, 9);
  hist_1->Fill(-1);
  hist_1->Fill(1);
  hist_1->Fill(2);
  hist_1->Fill(2);
  hist_1->Fill(5);

  // 2つ目のヒストグラムを作り、値を詰める
  TH1* hist_2 = new TH1D("name_2", "title_2", 10, -1, 9);
  hist_2->Fill(4);
  hist_2->Fill(4);
  hist_2->Fill(6);
  hist_2->Fill(7);
  hist_2->Fill(8);

  // 2つのヒストグラムを見分けられるように色を変更する
  hist_1->SetLineColor(kRed);
  hist_2->SetLineColor(kBlue);

  // 凡例を表示するかわり、統計ボックスは表示しない
  hist_1->SetStats(false);
  hist_2->SetStats(false);

  // 凡例(legend)を作る
  TLegend* legend = new TLegend(0.6, 0.6, 0.93, 0.93);
  //   引数の数字は、キャンバス上の座標(0が左端・下端で、1が右端・上端)

  // 凡例にヒストグラムを登録する
  legend->AddEntry(hist_1, "hist (1)", "L");
  legend->AddEntry(hist_2, "hist (2)", "L");
  // legend->AddEntry([0], [1], [2]) について
  //   [0] ... 登録するオブジェクト(ヒストグラムやグラフ)
  //   [1] ... 凡例に表示する文章
  //   [2] ... 凡例に載せるサンプルの形式 ("L"で線、"F"で塗りつぶし、"P"でマーカー。"LP"のように複数指定も可能)

  // ヒストグラムを描画
  hist_1->Draw();
  hist_2->Draw("same");

  // 凡例を描画
  legend->Draw();
}
