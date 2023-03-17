#include "TF1.h"
#include "TFile.h"
#include "TTree.h"

/**
 * 乱数でデータを作成し、それをROOTファイルにツリーとして出力する。
 */
void save_data_as_tree() {
  // 関数を作る
  TF1* func = new TF1("func", "[0] * TMath::Gaus(x, [1], [2]) + [3]", -5, 5);

  // 関数のパラメータを設定する
  func->SetParameter(0, 100);
  func->SetParameter(1,   0);
  func->SetParameter(2,   1);
  func->SetParameter(3,  10);

  // 出力ファイルを作る
  TFile* output_file = new TFile("../out/save_data.root", "RECREATE");
  
  // ファイルが正常に開けたかチェック
  if (!output_file->IsOpen()) {
    // 開けなかった場合：エラー内容を表示して処理を終了
    std::cout << "Error: output file was not opened." << std::endl;
    return;
  }

  // ツリーを作る
  TTree* tree = new TTree("tree", "title");

  // ツリーに保存する項目を設定する
  Int_t val_id;
  tree->Branch("id", &val_id);

  Double_t val_value;
  tree->Branch("value", &val_value);

  // データを出力する
  for (Int_t i = 0; i < 100; ++i) {
    val_id = i;
    val_value = func->GetRandom();

    // 対応する変数(val_idとval_value)に入っている値をツリーのブランチ(idとvalue)に登録する
    tree->Fill();
  }

  // ツリーをファイルに書き込む
  tree->Write();
  
  // ファイルを閉じる
  output_file->Close();
}
