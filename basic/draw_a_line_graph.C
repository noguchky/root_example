#include "TGraph.h"

/**
 * グラフを1つ作り、それを折れ線グラフとして描画する
 */
void draw_a_line_graph() {
  // グラフ作る
  TGraph* graph = new TGraph();
  // [[参照]]
  // TGraph::TGraph https://root.cern.ch/doc/master/classTGraph.html#af67c25bf5dbcc17ef0bab90904b06da6

  // グラフに点を設定する
  graph->SetPoint(0, 1, -1);
  graph->SetPoint(1, 2, 1);
  graph->SetPoint(2, 4, 2);
  graph->SetPoint(3, 6, 2);
  graph->SetPoint(4, 7, 5);
  // graph->SetPoint([0], [1], [2]) について
  //   [0] ... 何番目の点か指定する(0始まり)
  //   [1] ... [0]番目の点のxの値
  //   [2] ... [0]番目の点のyの値
  // [[参照]]
  // TGraph::SetPoint https://root.cern.ch/doc/master/classTGraph.html#a0cd3af5cb1b7cdc249002e45a0b32318

  // グラフを折線グラフとして描画
  graph->Draw("AL");
  // graph->Draw(文字列) について
  //   "A" ... 軸(x軸y軸)を描画する
  //   "L" ... グラフの点を結ぶ線を描画する
  // [[参照]]
  // TGraph::Draw https://root.cern.ch/doc/master/classTGraph.html#aac911e69487b57f1c4ba5d62d7b60af9
  // "A"や"L"について https://root.cern.ch/doc/master/classTGraphPainter.html
}
