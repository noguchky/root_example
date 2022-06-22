#include "TGraph.h"
#include "TAxis.h"

/**
 * グラフを1つ作り、それを折れ線グラフとして描画する
 */
void draw_a_line_graph_with_customizing() {
  // グラフ作り、点を設定する
  TGraph* graph = new TGraph();
  graph->SetPoint(0, 1, -1);
  graph->SetPoint(1, 2, 1);
  graph->SetPoint(2, 4, 2);
  graph->SetPoint(3, 6, 2);
  graph->SetPoint(4, 7, 5);

  // 線のスタイル(形状)を設定する
  graph->SetLineStyle(kDashed);
  // graph->SetLineStyle(数値) について
  //   数値 ... 線のスタイル(形状)を表す数値
  // [[参照]]
  // TAttLine::SetLineStyle https://root.cern.ch/doc/master/classTAttLine.html#a2012d69ad2942b0adcdc3991319b74e1
  //
  // kDashed について
  //   破線を表す数値で、具体的には kDashed=2
  // [[参照]]
  // 線のスタイル(形状)の一覧 https://root.cern.ch/doc/master/classTAttLine.html#ATTLINE3

  // 線の太さを設定する
  graph->SetLineWidth(2);
  // graph->SetLineWidth(数値) について
  //   数値 ... 太さを表す数値、1は細線で、数値が大きいほど太くなる
  // [[参照]]
  // TAttLine::SetLineWidth https://root.cern.ch/doc/master/classTAttLine.html#a5eb21074710a85b6cd1b51e145c562f5
  // 線の太さに一覧 https://root.cern.ch/doc/master/classTAttLine.html#ATTLINE2

  // 線の色を設定する
  graph->SetLineColor(kRed);
  // graph->SetLineColor(数値) について
  //   数値 ... 色を表す数値
  // [[詳細]]
  // TAttLine::SetLineColor https://root.cern.ch/doc/master/classTAttLine.html#a718156d3be0e4b3e0c52b2257a9d4e7a
  //
  // kRed について
  //   色を表す数字であり、具体的には kRed=632
  // [[詳細]]
  // 色の一覧 https://root.cern.ch/doc/master/classTColor.html#C01

  // 描画するyの範囲を指定する
  graph->SetMinimum(-1);
  graph->SetMaximum(5);
  // graph->SetMinimum(数値) について
  //   数値 ... 描画する際のy方向の最小値
  // [[詳細]]
  // TGraph::SetMinimum https://root.cern.ch/doc/master/classTGraph.html#af5ac42e5298d86138346c2768fb6ed6c
  // TGraph::SetMaximum https://root.cern.ch/doc/master/classTGraph.html#a3bf634e91e7e27ab462d8a8e61f7dfe7

  // 描画するxの範囲を指定する
  graph->GetXaxis()->SetLimits(-1, 5);
  // ->SetLimits([0], [1]) について
  //   [0] ... 描画する際のx方向の最小値
  //   [1] ... 描画する際のx方向の最大値
  //   ※ ヒストグラムでxの範囲を指定するために使用する関数(SetRangeUser)とは異なるため注意
  // [[詳細]]
  // TAxis::SetLimits https://root.cern.ch/doc/master/classTAxis.html#aa56ec858687dad0b58ca0cf939e7c79b

  // グラフを折線グラフとして描画
  graph->Draw("AL");
}
