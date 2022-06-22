#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"

/**
 * ROOTファイルに保存されているツリーを使って、ヒストグラムを描画する。
 */
void read_tree_and_draw_a_hist() {
  // ファイルを開く
  TFile* input_file = new TFile("../data/tree.root");
  // new TFile(文字列) について
  //   文字列 ... ファイル名
  //   絶対パスか、マクロを実行するディレクトリから見た相対パスを指定する
  // [[参照]]
  // TFile::TFile https://root.cern.ch/doc/master/classTFile.html#ad0377adf2f3d88da1a1f77256a140d60

  // 無事にファイルを開けたか確認する
  if (input_file->IsOpen()) {
    // 判定結果 : 正常にファイルが開けている

    // input_file->IsOpen() について
    //   ファイルが開けていれば true になる
    // [[参照]]
    // TFile::IsOpen https://root.cern.ch/doc/master/classTFile.html#a67dedbe56cfe4792cff78df129718c11

  } else {
    // 判定結果 : ファイルが開けていない
    //   ファイルが存在しない、ファイル名の指定ミス、アクセス権限がなかった、などの理由が考えられる

    // エラーメッセージを表示する
    std::cout << "Error: file was not opened" << std::endl;

    // 処理を終了する
    return; 
  }

  // ファイルからツリーを取得する
  TTree* input_tree = dynamic_cast<TTree*>(input_file->Get("tree"));

  // ツリーが取得できたかどうか確認する
  if (input_tree) {
    // 取得できている
  } else {
    // 取得できていない
    // file->Get部分の指定ミスや、間違ったファイルを使用しているなどの可能性がある

    // エラーメッセージを表示する
    std::cout << "Error: tree was not found" << std::endl;
    
    return;
  }

  // ツリーの変数を使ってヒストグラムを描画する (作られるヒストグラムの名前やビン数や範囲の設定をROOTに任せる)
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value");

  // ツリーの変数を使ってヒストグラムを描画する (ヒストグラムの名前は自分で決める)
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value >> myhist_1");

  // ツリーの変数を使ってヒストグラムを描画する (名前やビン数、範囲を全て自分で決める)
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value >> myhist_2(100,-5,5)");

  // ツリーの変数を使った計算値のヒストグラムを描画する
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value * value + id * value");

  // ツリーの変数を使ってヒストグラムを描画する (idが奇数のもののみ描画する)
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value", "id%2!=0");
  // 第二引数は描画する条件

  // ツリーの変数を使って二次元ヒストグラムを描画する
  TCanvas::MakeDefCanvas();
  input_tree->Draw("value:id", "", "col");
  // 二次元ヒストグラムの場合、「y軸の値:x軸の値」で指定する (y vs x という英語の語順に従う)
  // 第三引数は描画に関するオプション
}
