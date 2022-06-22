#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"

/**
 * 関数を描画したキャンバスをROOTファイルに保存する
 */
void save_canvas_as_root() {
  // 関数を作る
  TF1* func = new TF1("func", "gaus(0)", -10, 10);

  // キャンバスを作る
  TCanvas* c1 = new TCanvas("canvas");

  // ROOTファイルを作る
  TFile* ofile = new TFile("../out/save_canvas.root", "RECREATE");

  // ファイルが開けたかどうか確認する
  if (ofile->IsOpen()) {
    // 正常にファイルが開けている
  } else {
    // ファイルが開けていない
    //   ファイル名の間違い、存在しないディレクトリ以下にファイルを作ろうとしている、アクセス権限がないなどの理由が考えられる

    // エラーメッセージを出力する
    std::cout << "Error: root file was not opened" << std::endl;

    // 処理を終了する
    return;
  }

  for (Int_t i = 0; i < 3; ++i) {
    // 変数を変えて関数を描画
    const Double_t mu    = 3.0 * (i - 2);
    const Double_t sigma = i + 1;
    func->SetParameters(10.0, mu, sigma);
    func->Draw();

    // 現在のキャンバスをROOTファイルに書き込む (名前が重複しないように個別の名前で保存する)
    c1->Write(Form("c1_%d", i));
  }

  // ROOTファイルを閉じる
  ofile->Close();
}
