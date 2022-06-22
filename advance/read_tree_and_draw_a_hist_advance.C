#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

/**
 * ROOTファイルに保存されているツリーを使って、ヒストグラムを描画する。
 */
void read_tree_and_draw_a_hist_advance() {
  // ファイルを開く
  TFile* input_file = new TFile("../data/tree.root");

  // 無事にファイルを開けたか確認する
  if (not input_file->IsOpen()) {
    // エラーメッセージを表示する
    std::cout << "Error: file was not opened" << std::endl;

    // 処理を終了する
    return; 
  }

  // ファイルからツリーを取得する
  TTree* input_tree = dynamic_cast<TTree*>(input_file->Get("tree"));

  // ツリーが取得できたかどうか確認する
  if (not input_tree) {
    // エラーメッセージを表示する
    std::cout << "Error: tree was not found" << std::endl;
    
    return;
  }

  // ツリーの全エントリー数を取得する
  const Long64_t entries = input_tree->GetEntries();

  // ツリーから読み込む数値を格納する変数を用意する
  Double_t val_value;

  // ブランチに値を登録する
  input_tree->SetBranchAddress("value", &val_value);

  // ヒストグラムを作る
  TH1* hist = new TH1D("name", "title", 10, -5, 5);

  // ツリーから値を取得してヒストグラムに詰める
  for (Long64_t entry = 0; entry < entries; ++entry) {
    // 登録した変数(val_value)に値を出力する
    input_tree->GetEntry(entry);

    hist->Fill(val_value);
  }

  // ヒストグラムを描画する
  hist->Draw();
}
