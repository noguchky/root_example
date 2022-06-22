#include "TCanvas.h"
#include "TH2D.h"
#include "TRandom3.h"

/**
 * 二次元ヒストグラムの射影(projection)を描画する
 */
void draw_projection() {
  // ヒストグラムを作る
  TH2D* hist = new TH2D("hist", ";x;y", 50, -10, 10, 50, -10, 10);

  // 2次元ガウス分布でヒストグラムに詰める
  TRandom3 rand;
  for (Int_t i = 0; i < 10000; ++i) {
    const Double_t x = rand.Gaus(0.0, 2.0);
    const Double_t y = rand.Gaus(0.0, 5.0);
    hist->Fill(x, y);
  }

  // x軸への射影を描画する
  TCanvas::MakeDefCanvas();
  TH1D* histX = hist->ProjectionX();
  histX->Draw();

  // y軸への射影を描画する
  TCanvas::MakeDefCanvas();
  TH1D* histY = hist->ProjectionY();
  histY->Draw();
}
