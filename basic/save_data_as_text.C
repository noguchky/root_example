#include <fstream>
#include "TF1.h"

/**
 * 乱数でデータを作成し、それをテキストファイルに出力する。
 */
void save_data_as_text() {
  // 関数を作る
  TF1* func = new TF1("func", "[0] * TMath::Gaus(x, [1], [2]) + [3]", -5, 5);

  // 関数のパラメータを設定する
  func->SetParameter(0, 100);
  func->SetParameter(1,   0);
  func->SetParameter(2,   1);
  func->SetParameter(3,  10);

  // 出力ファイルを作る
  std::ofstream output_file;
  output_file.open("../out/save_data.txt");

  // データを出力する
  for (Int_t i = 0; i < 100; ++i) {
    output_file << i << " " << func->GetRandom() << std::endl;
  }

  // ファイルを閉じる
  output_file.close();
}
