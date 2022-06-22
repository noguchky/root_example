#include <iostream> // エラーメッセージを表示するために使用する
#include <fstream>  // テキストファイルを読むために使用する
#include "TH1.h"

/**
 * テキストファイルに書かれている数値を読み込み、ヒストグラムを描画する。
 */
void read_text_and_draw_a_hist() {
  // ヒストグラムを作る
  TH1* hist = new TH1D("name", "title", 10, -5, 5);

  // ファイルを開く
  std::ifstream input_file;
  input_file.open("./data/data_single_column.txt");
  // input_file.open(文字列) について
  //   文字列 ... ファイル名
  //   絶対パスか、マクロを実行するディレクトリから見た相対パスを指定する
  // [[参照]]
  // std::basic_ifstream::open https://cpprefjp.github.io/reference/fstream/basic_ifstream/open.html

  // 無事にファイルを開けたか確認する
  if (input_file) {
    // 判定結果 : 正常にファイルが開けている

    // if (input_file) について
    //   ファイルストリーム(input_fileのこと)が正常であるかを判定する
    //   ファイル入出力オブジェクトをそのまま判定文に指定すれば良い
    //   ※ 正常である = ファイルが開けていて、まだ読み残しがある
    //      正常でない = ファイルが開けていない、あるいは、もう読み終わっている
    // [[参照]]
    // std::basic_ios::operator bool https://cpprefjp.github.io/reference/ios/basic_ios/op_bool.html

  } else {
    // 判定結果 : ファイルが開けていない
    //   ファイルが存在しない、ファイル名の指定ミス、アクセス権限がなかった、などの理由が考えられる

    // エラーメッセージを表示する
    std::cout << "Error: file was not opened" << std::endl;

    // 処理を終了する
    return; 
  }

  // ファイルから読み込む数値を格納する変数を用意する
  Double_t value;

  // ファイルから数値を読み込む (成功する限り繰り返す)
  while (input_file >> value) {
    // input_file >> value について
    //   テキストファイルから、スペースや改行で区切られている部分を読み込み、valueに代入している
    //   ファイルを最後まで読み終えると、ループが終わる

    // ヒストグラムに値を詰める
    hist->Fill(value);

  }

  // ヒストグラムを描画する
  hist->Draw();
}
