#include <iostream> // エラーメッセージを表示するために使用する
#include <fstream>  // テキストファイルを読むために使用する
#include "TGraph.h"

/**
 * テキストファイルに書かれている数値を読み込み、散布図を描画する。
 */
void read_text_and_draw_a_scatter_plot() {
  // グラフを作る
  TGraph* graph = new TGraph();

  // グラフの点を見やすいマーカーに変更する
  graph->SetMarkerStyle(kCircle);

  // ファイルを開く
  std::ifstream input_file;
  input_file.open("../data/data_double_columns.txt");
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
  Double_t x, y;

  // ファイルから数値を読み込む (成功する限り繰り返す)
  while (input_file >> x >> y) {
    // input_file >> x >> y について
    //   テキストファイルから、スペースや改行で区切られている部分を読み込み、x, yに順に代入している
    //   ファイルを最後まで読み終えると、ループが終わる
    // [[参照]]
    // std::basic_istream::operator>> https://cpprefjp.github.io/reference/istream/basic_istream/op_istream.html

    // グラフに点を追加する
    graph->AddPoint(x, y);
    // graph->AddPoint(x, y) について
    //   新たな点を追加する
    //   graph->SetPoint(graph->GetN(), x, y) も同等に作用する
    // [[参照]]
    // TGraph::AddPoint https://root.cern.ch/doc/master/classTGraph.html#a056c11b01569445bfcaf33079cf01f27
  }

  // グラフを描画する
  graph->Draw("AP");
}
