#include "TGraph.h"

/**
 * グラフを1つ作り、それを散布図として描画する
 */
void draw_a_scatter_plot() {
  // グラフ作る
  TGraph* graph = new TGraph();
  // [[参照]]
  // TGraph::TGraph https://root.cern.ch/doc/master/classTGraph.html#af67c25bf5dbcc17ef0bab90904b06da6

  // グラフに点を設定する
  graph->SetPoint(0, 3, 3);
  graph->SetPoint(1, 4, 4);
  graph->SetPoint(2, 2, 2);
  graph->SetPoint(3, 1, 1);
  graph->SetPoint(4, 2, 1);
  graph->SetPoint(5, 5, 6);
  graph->SetPoint(6, 3, 4);
  // graph->SetPoint([0], [1], [2]) について
  //   [0] ... 何番目の点か指定する(0始まり)
  //   [1] ... [0]番目の点のxの値
  //   [2] ... [0]番目の点のyの値
  // [[参照]]
  // TGraph::SetPoint https://root.cern.ch/doc/master/classTGraph.html#a0cd3af5cb1b7cdc249002e45a0b32318

  // グラフの点を見やすいマーカーに変更する
  graph->SetMarkerStyle(kCircle);
  // graph->SetMarkerStyle(数値) について
  //   数値 ... マーカーのスタイル(形状)を表す数字
  // [[参照]]
  // TAttMarker::SetMarkerStyle https://root.cern.ch/doc/master/classTAttMarker.html#a697e1a65975ff344c9dca7618fd44de4
  //
  // kCircle について
  //   マーカーのスタイル(形状)を表す数値であり、具体的には kCircle=4
  // [[参照]]
  // マーカーのスタイル一覧 https://root.cern.ch/doc/master/classTAttMarker.html#ATTMARKER2

  // グラフの点の色を変更する
  graph->SetMarkerColor(kRed);
  // graph->SetMarkerColor(数値) について
  //   数値 ... マーカーの色を表す数字
  // [[参照]]
  // TAttMarker::SetMarkerColor https://root.cern.ch/doc/master/classTAttMarker.html#a27f1eae16a3f990024e8a401ed034fa3
  //
  // kRed について
  //   色を表す数字であり、具体的には kRed=632
  // [[詳細]]
  // 色の一覧 https://root.cern.ch/doc/master/classTColor.html#C01

  // グラフを散布図として描画
  graph->Draw("AP");
  // graph->Draw(文字列) について
  //   "A" ... 軸(x軸y軸)を描画する
  //   "P" ... グラフの点のマーカーを描画する
  // [[参照]]
  // TGraph::Draw https://root.cern.ch/doc/master/classTGraph.html#aac911e69487b57f1c4ba5d62d7b60af9
  // "A"や"L"について https://root.cern.ch/doc/master/classTGraphPainter.html
}
