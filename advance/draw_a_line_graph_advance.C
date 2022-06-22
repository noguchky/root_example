#include "TGraph.h"
#include "TAxis.h"

/**
 * グラフを1つ作り、それを折れ線グラフとして描画する
 */
void draw_a_line_graph_advance() {
  // グラフ作り、点を設定する
  TGraph* graph = new TGraph();
  graph->SetPoint(0, 1, -1);
  graph->SetPoint(1, 2, 1);
  graph->SetPoint(2, 4, 2);
  graph->SetPoint(3, 6, 2);
  graph->SetPoint(4, 7, 5);

  // 線のスタイル(形状)を設定する
  graph->SetLineStyle(kDashed);

  // 線の太さを設定する
  graph->SetLineWidth(2);

  // 線の色を設定する
  graph->SetLineColor(kRed);

  // 描画するyの範囲を指定する
  graph->SetMinimum(-1);
  graph->SetMaximum(5);

  // 描画するxの範囲を指定する
  graph->GetXaxis()->SetLimits(-1, 5);

  // グラフを折線グラフとして描画
  graph->Draw("AL");
}
