#include "TH1.h"

/**
 * ヒストグラムを1つ作り、それを描画する
 */
void draw_a_hist() {
  // ヒストグラムを作る
  TH1* hist = new TH1D("name", "title", 10, -4, 6);
  // new TH1D([0], [1], [2], [3], [4]) について
  //   [0] ... ヒストグラムの名前(ROOTが管理するための名前)
  //   [1] ... ヒストグラムのタイトル
  //   [2] ... ビンの数
  //   [3] ... ビンの左端の値
  //   [4] ... ビンの右端の値
  // [[参照]]
  // TH1D::TH1D https://root.cern.ch/doc/master/classTH1D.html#a4e0536d7ab2c883c26b2e4ea5b540334

  // ヒストグラムに値を詰める
  hist->Fill(-1);
  hist->Fill(1);
  hist->Fill(2);
  hist->Fill(2);
  hist->Fill(5);
  // hist->Fill(数値) について
  //   数値 ... ヒストグラムに詰める値
  // [[参照]]
  // TH1::Fill https://root.cern.ch/doc/master/classTH1.html#a77e71290a82517d317ea8d05e96b6c4a

  // ヒストグラムを描画する
  hist->Draw();
  // [[参照]]
  // TH1::Draw https://root.cern.ch/doc/master/classTH1.html#a83e36de9b41ceffc540f729d45c0ad0c
}
