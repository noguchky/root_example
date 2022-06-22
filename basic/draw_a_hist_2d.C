#include "TH2.h"
#include "TRandom3.h"

/**
 * ヒストグラムを1つ作り、それを描画する
 */
void draw_a_hist_2d() {
  // ヒストグラムを作る
  TH2* hist = new TH2D("name", "title", 50, -5, 5, 50, -5, 5);
  // new TH1D([0], [1], [2], [3], [4], [5], [6], [7]) について
  //   [0] ... ヒストグラムの名前(ROOTが管理するための名前)
  //   [1] ... ヒストグラムのタイトル
  //   [2] ... x軸方向のビンの数
  //   [3] ... x軸方向のビンの左端の値
  //   [4] ... x軸方向のビンの右端の値
  //   [5] ... y軸方向のビンの数
  //   [6] ... y軸方向のビンの左端の値
  //   [7] ... y軸方向のビンの右端の値
  // [[参照]]
  // TH2D::TH2D https://root.cern.ch/doc/master/classTH2D.html#a6c62cabca3d6befd79deef6b0472be5b

  // 乱数生成器を作る
  TRandom3 rand;

  for (Int_t i = 0; i < 10000; ++i) {
    // 詰める値を乱数で取得する
    const Double_t x = rand.Gaus(0.0, 2.0);
    const Double_t y = rand.Gaus(1.0, 1.0);
    // rand.Gaus([0], [1]) について
    //   ガウス分布に従う乱数を生成する
    //   [0] ... ガウス分布の平均値
    //   [1] ... ガウス分布の標準偏差
    // [[参照]]
    // TRandom::Gaus https://root.cern.ch/doc/master/classTRandom.html#a0e445e213eae1343b3d22086ecb87314

    // ヒストグラムに値を詰める
    hist->Fill(x, y);
    // hist->Fill([0], [1]) について
    //   [0] ... ヒストグラムに詰めるxの値
    //   [1] ... ヒストグラムに詰めるyの値
    // [[参照]]
    // TH2D::Fill https://root.cern.ch/doc/master/classTH2.html#a434553d6ee6507ed252f47eba7b43869
  }

  // ヒストグラムを描画する
  hist->Draw("col");
  // hist->Draw("col") について
  //   "col" ... ビンの高さを
  // [[参照]]
  // "col"について https://root.cern/doc/master/classTHistPainter.html#HP01c
}
