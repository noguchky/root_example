#include "TH1.h"
#include "TAxis.h"

/**
 * ヒストグラムを1つ作り、それを描画する
 */
void draw_a_hist_with_customizing() {
  // ヒストグラムを作り、値を詰める
  TH1* hist = new TH1D("name", "title", 10, -4, 6);
  hist->Fill(-1);
  hist->Fill(1);
  hist->Fill(2);
  hist->Fill(2);
  hist->Fill(5);

  // ヒストグラムの線の色を変更する
  hist->SetLineColor(kRed);
  // hist->SetLineColor(数値) について
  //   数値 ... 色を表す数値
  // [[詳細]]
  // TAttLine::SetLineColor https://root.cern.ch/doc/master/classTAttLine.html#a718156d3be0e4b3e0c52b2257a9d4e7a
  //
  // kRed について
  //   色を表す数字であり、具体的には kRed=632
  // [[詳細]]
  // 色の一覧 https://root.cern.ch/doc/master/classTColor.html#C01

  // x軸y軸のタイトルを設定する
  hist->GetXaxis()->SetTitle("sample");
  hist->GetYaxis()->SetTitle("entries");
  // hist->GetXaxis(), hist->GetYaxis() について
  //   ヒストグラムと一緒に描画されるx軸y軸を取得する
  //   軸の見た目をカスタマイズしたい場合などに使用する
  // [[詳細]]
  // TH1::GetXaxis https://root.cern.ch/doc/master/classTH1.html#a5535ca3d71c41416004b158915a234f6
  //
  // ->SetTitle(文字列) について
  //   文字列 ... 軸に設定するタイトル
  // [[詳細]]
  // TNamed::SetTitle https://root.cern.ch/doc/master/classTNamed.html#a72f4d419b48a5fbfef07485b335139ca

  // 描画するyの範囲を指定する
  hist->SetMinimum(-1);
  hist->SetMaximum(5);
  // hist->SetMinimum(数値) について
  //   数値 ... 描画する際のy方向の最小値
  // [[詳細]]
  // TH1::SetMinimum https://root.cern.ch/doc/master/classTH1.html#a89a5d8fc84154b504566f367ba8d0238
  // TH1::SetMaximum https://root.cern.ch/doc/master/classTH1.html#a68e78664002d109dd4747964d66778a3

  // 描画するxの範囲を指定する
  hist->GetXaxis()->SetRangeUser(-1, 5);
  // ->SetRangeUser([0], [1]) について
  //   [0] ... 描画する際のx方向の最小値
  //   [1] ... 描画する際のx方向の最大値
  // [[詳細]]
  // TAxis::SetRangeUser https://root.cern.ch/doc/master/classTAxis.html#ac85f8261dedc23bbe68f90afd196cdb8

  // ヒストグラムを描画する
  hist->Draw();
}
