#include "TH1.h"

/**
 * ヒストグラムを2つ作り、それらを1つのキャンバスに描画する
 */
void draw_two_hists() {
  // 1つ目のヒストグラムを作り、値を詰める
  TH1* hist_1 = new TH1D("name_1", "title_1", 10, -4, 6);
  hist_1->Fill(-1);
  hist_1->Fill(1);
  hist_1->Fill(2);
  hist_1->Fill(2);
  hist_1->Fill(5);

  // 2つ目のヒストグラムを作り、値を詰める
  TH1* hist_2 = new TH1D("name_2", "title_2", 10, -4, 6);
  hist_2->Fill(0);
  hist_2->Fill(1);
  hist_2->Fill(1);
  hist_2->Fill(3);
  hist_2->Fill(6);

  // 2つのヒストグラムを見分けられるように色を変更する
  hist_1->SetLineColor(kRed);
  hist_2->SetLineColor(kBlue);
  // hist_1->SetLineColor(数値) について
  //   数値 ... 色を表す数値
  // [[詳細]]
  // TAttLine::SetLineColor https://root.cern.ch/doc/master/classTAttLine.html#a718156d3be0e4b3e0c52b2257a9d4e7a
  //
  // kRed, kBlue について
  //   色を表す数字であり、具体的には kRed=632, kBlue=600
  // [[詳細]]
  // 色の一覧 https://root.cern.ch/doc/master/classTColor.html#C01

  // 1つ目のヒストグラムを描画
  hist_1->Draw();

  // 2つ目のヒストグラムを重ね書き
  hist_2->Draw("same");
  // hist_2->Draw("same") について
  //   1つ目のヒストグラムは、x軸y軸と、ヒストグラムを描画している
  //   "same"を指定した場合、すでに存在するx軸y軸に合わせてヒストグラムを描画する
  // [[参照]]
  // TH1::Draw https://root.cern.ch/doc/master/classTH1.html#a83e36de9b41ceffc540f729d45c0ad0c
  // "same"について https://root.cern.ch/doc/master/classTHistPainter.html
}
