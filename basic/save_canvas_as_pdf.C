#include "TCanvas.h"
#include "TF1.h"

/**
 * 関数を描画したキャンバスをPDFファイルに保存する
 */
void save_canvas_as_pdf() {
  // 関数を作る
  TF1* func = new TF1("func", "gaus(0)", -10, 10);

  // キャンバスを作る
  TCanvas* c1 = new TCanvas("canvas");

  // 複数ページのPDFの出力開始
  c1->Print("../out/save_canvas.pdf[");

  for (Int_t i = 0; i < 3; ++i) {
    // 変数を変えて関数を描画
    const Double_t mu    = 3.0 * (i - 2);
    const Double_t sigma = i + 1;
    func->SetParameters(10.0, mu, sigma);
    func->Draw();

    // 複数ページのPDFの1ページを出力
    c1->Print("../out/save_canvas.pdf");
  }

  // 複数ページのPDFの出力終了
  c1->Print("../out/save_canvas.pdf]");
}
