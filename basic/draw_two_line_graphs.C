#include "TGraph.h"

/**
 * グラフを2つ作り、それらを折れ線グラフとして1つのキャンバスに描画する
 */
void draw_two_line_graphs() {
  // 1つ目のグラフ作り、点を設定する
  TGraph* graph_1 = new TGraph();
  graph_1->SetPoint(0, 1, -1);
  graph_1->SetPoint(1, 2, 1);
  graph_1->SetPoint(2, 4, 2);
  graph_1->SetPoint(3, 6, 2);
  graph_1->SetPoint(4, 7, 5);

  // 2つ目のグラフ作り、点を設定する
  TGraph* graph_2 = new TGraph();
  graph_2->SetPoint(0, 0, 5);
  graph_2->SetPoint(1, 1, 2);
  graph_2->SetPoint(2, 3, 2);
  graph_2->SetPoint(3, 5, 1);
  graph_2->SetPoint(4, 7, -1);

  // 2つのグラフを見分けられるように色を変更する
  graph_1->SetLineColor(kRed);
  graph_2->SetLineColor(kBlue);
  // graph_1->SetLineColor([0]) について
  //   数値 ... 色を表す数値
  // [[詳細]]
  // TAttLine::SetLineColor https://root.cern.ch/doc/master/classTAttLine.html#a718156d3be0e4b3e0c52b2257a9d4e7a
  //
  // kRed, kBlue について
  //   色を表す数字であり、具体的には kRed=632, kBlue=600
  // [[詳細]]
  // 色の一覧 https://root.cern.ch/doc/master/classTColor.html#C01

  // 1つ目のグラフを折線グラフとして描画
  graph_1->Draw("AL");
  // graph->Draw(文字列) について
  //   "A" ... 軸(x軸y軸)を描画する
  //   "L" ... グラフの点を結ぶ線を描画する

  // 2つ目のグラフを折線グラフとして重ね書き
  graph_2->Draw("L");
  // graph_2->Draw("L") について
  //   2つ目のヒストグラムは、x軸y軸を描画する"A"を指定しない
  //   すでに存在するx軸y軸に合わせて折線グラフを描画する
}
