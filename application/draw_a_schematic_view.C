#include <iostream>
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include "TRandom.h"
#include "TAxis.h"
#include "TPaveText.h"

/**
 * キャンバスのマージン
 */
const struct { Double_t Left, Right, Bottom, Top; } Margin { 0.060, 0.040, 0.145, 0.035 };

namespace UnexpectedKick {
  // 定数パラメータ
  const Double_t Emittance   = 0.25;
  const Double_t KickTiming  = -0.2795;
  const Double_t InjError    = 0.14;
  const Double_t CompTiming  = 2.0;
  const Double_t CompPower   = - InjError;
  const Double_t Tune        = (CompTiming - KickTiming) / 2.0;

  /**
   * 個々の粒子の飛跡
   */
  Double_t ParticleTrajectory(Double_t* px, Double_t* pp) {
    const Double_t x = px[0];

    const Double_t phaseOffset = pp[0];
    const Double_t tuneShift   = pp[1];

    const Double_t phase1 = x - phaseOffset;
    const Double_t tune   = Tune * (1.0 + tuneShift);
    const Double_t phase2 = x - KickTiming;
    const Double_t phase3 = x - CompTiming;

    Double_t y = Emittance * TMath::Sin(TMath::TwoPi() * phase1 / tune);
    if (x > KickTiming) {
      y += InjError  * TMath::Sin(TMath::TwoPi() * phase2 / tune);
    }
    if (x > CompTiming) {
      y += CompPower * TMath::Sin(TMath::TwoPi() * phase3 / tune);
    }
    return y;
  }

  /**
   * 粒子集団(バンチ)の飛跡
   */
  Double_t BunchTrajectory(Double_t* px, Double_t* pp) {
    const Double_t x = px[0];

    const Double_t tune   = Tune;
    const Double_t phase2 = x - KickTiming;
    const Double_t phase3 = x - CompTiming;

    Double_t y = 0.0;
    if (x > KickTiming) {
      y += InjError  * TMath::Sin(TMath::TwoPi() * phase2 / tune);
    }
    if (x > CompTiming) {
      y += CompPower * TMath::Sin(TMath::TwoPi() * phase3 / tune);
    }
    return y;
  }

  /**
   * 包括線の上側
   */
  Double_t EnvelopeTop(Double_t* px, Double_t* pp) {
    const Double_t x = px[0];

    const Double_t tune   = Tune;
    const Double_t phase2 = x - KickTiming;
    const Double_t phase3 = x - CompTiming;

    Double_t y = Emittance;
    if (x > KickTiming) {
      y += InjError  * TMath::Sin(TMath::TwoPi() * phase2 / tune);
    }
    if (x > CompTiming) {
      y += CompPower * TMath::Sin(TMath::TwoPi() * phase3 / tune);
    }
    return y;
  }

  /**
   * 包括線の下側
   */
  Double_t EnvelopeBottom(Double_t* px, Double_t* pp) {
    const Double_t x = px[0];

    const Double_t tune   = Tune;
    const Double_t phase2 = x - KickTiming;
    const Double_t phase3 = x - CompTiming;

    Double_t y = -Emittance;
    if (x > KickTiming) {
      y += InjError  * TMath::Sin(TMath::TwoPi() * phase2 / tune);
    }
    if (x > CompTiming) {
      y += CompPower * TMath::Sin(TMath::TwoPi() * phase3 / tune);
    }
    return y;
  }

}

/**
 * 論文向けの模式図を描画する
 */
void draw_a_schematic_view() {
  const Double_t xmin = -1.5;
  const Double_t xmax = +3.5;

  // キャンバスを作成 (幅800px、高さ370px)
  TCanvas* c1 = new TCanvas("c1", "c1", 800, 370);

  // 余白部分のサイズを設定
  c1->SetMargin(Margin.Left, Margin.Right, Margin.Bottom, Margin.Top);

  // x軸(縦方向)のグリット線のみ有効化
  c1->SetGrid(true, false);

  // x軸y軸の反対側(右側と上側)にも目盛り線をつける
  c1->SetTickx(true);
  c1->SetTicky(true);

  // y=0 の軸を表示するグラフ
  TGraph* gXaxis = new TGraph();

  // タイトルを設定
  gXaxis->SetTitle(";Turn Number;Transverse Position");
  //   ";"で区切ることで、グラフ上部のタイトル、x軸のタイトル、y軸のタイトルの順で設定できる
  //   論文中のグラフの場合、上部のタイトルは不要 (キャプションで説明する)

  // gridと同じ見た目になるように線を設定する
  gXaxis->SetLineWidth(1);
  gXaxis->SetLineStyle(kDotted);
  gXaxis->SetLineColor(kBlack);

  // y=0 となる2点を設定
  gXaxis->SetPoint(0, xmin, 0.0);
  gXaxis->SetPoint(1, xmax, 0.0);

  // 軸を描画
  gXaxis->Draw("AL");

  // x軸のラベルサイズを大きめに設定
  gXaxis->GetXaxis()->SetLabelSize(0.06);

  // y軸のラベルは不要なので非表示
  gXaxis->GetYaxis()->SetLabelSize(0.0);

  // x軸y軸のタイトルサイズを大きめに設定
  gXaxis->GetXaxis()->SetTitleSize(0.065);
  gXaxis->GetYaxis()->SetTitleSize(0.065);

  // タイトルと軸の間の間隔を微調整
  gXaxis->GetXaxis()->SetTitleOffset(0.98);
  gXaxis->GetYaxis()->SetTitleOffset(0.3);

  // 軸の目盛り線のサイズを調整
  gXaxis->GetXaxis()->SetTickLength(0.02);
  gXaxis->GetYaxis()->SetTickLength(0.02);

  // 軸の目盛りの間隔を調整
  gXaxis->GetXaxis()->SetNdivisions(505);
  gXaxis->GetYaxis()->SetNdivisions(101);

  // 軸の描画範囲を設定
  gXaxis->SetMinimum(-1.0);
  gXaxis->SetMaximum(+1.0);
  gXaxis->GetXaxis()->SetLimits(xmin, xmax);

  // 内容物を作る
  const std::size_t N = 8;
  TF1* fParticleTrajectory[N];
  for (std::size_t i = 0; i < N; ++i) {
    fParticleTrajectory[i] = new TF1(Form("fParticleTrajectory_%lu", i), UnexpectedKick::ParticleTrajectory, xmin, xmax, 2);
    fParticleTrajectory[i]->SetNpx(300);
    fParticleTrajectory[i]->SetLineColor(kBlack);
    fParticleTrajectory[i]->SetLineWidth(1);

    const Double_t phaseOffset = gRandom->Uniform(0, 1);
    const Double_t tuneShift   = 0.0;
    fParticleTrajectory[i]->SetParameters(phaseOffset, tuneShift);
    fParticleTrajectory[i]->SetNpx(200); // 滑らかになるよう設定 (200点で関数を描画する)
  }

  TF1* fBunchTrajectory = new TF1("fBunchTrajectory", UnexpectedKick::BunchTrajectory, xmin, xmax, 2);
  TF1* fEnvelopeTop     = new TF1("fEnvelopeTop"    , UnexpectedKick::EnvelopeTop    , xmin, xmax, 2);
  TF1* fEnvelopeBottom  = new TF1("fEnvelopeBottom" , UnexpectedKick::EnvelopeBottom , xmin, xmax, 2);
  fBunchTrajectory->SetNpx(200);
  fEnvelopeTop    ->SetNpx(200);
  fEnvelopeBottom ->SetNpx(200);

  TGraph* gUnexpectedKickTiming = new TGraph();
  gUnexpectedKickTiming->SetPoint(0, UnexpectedKick::KickTiming, -1.0);  
  gUnexpectedKickTiming->SetPoint(1, UnexpectedKick::KickTiming, +1.0);  
  gUnexpectedKickTiming->SetLineWidth(1);
  gUnexpectedKickTiming->SetLineStyle(kDotted);
  gUnexpectedKickTiming->SetLineColor(kBlack);

  // 内容物を描画していく
  gUnexpectedKickTiming->Draw("L");
  fEnvelopeTop   ->Draw("same");
  fEnvelopeBottom->Draw("same");
  for (std::size_t i = 0; i < N; ++i) {
    fParticleTrajectory[i]->Draw("same");
  }
  fBunchTrajectory->Draw("same");

  // 文字を書き込む
  TPaveText* tTimingA = new TPaveText();
  tTimingA->SetFillColor(kWhite); // 白く塗りつぶし (他の線を塗りつぶして文字を見やすくする)
  tTimingA->SetShadowColor(0); // 影なし
  tTimingA->SetBorderSize(0); // 罫線なし
  tTimingA->SetTextSize (0.06); // 文字サイズ設定
  tTimingA->SetTextAlign(22); // 垂直・水平方向に中央揃え
  tTimingA->AddText("(a)"); // 文字内容を設定
  tTimingA->SetX1NDC(Margin.Left + (1.0 - Margin.Left - Margin.Right) / (xmax - xmin) * (UnexpectedKick::KickTiming - xmin - 0.1));
  tTimingA->SetX2NDC(Margin.Left + (1.0 - Margin.Left - Margin.Right) / (xmax - xmin) * (UnexpectedKick::KickTiming - xmin + 0.1));
  tTimingA->SetY1NDC(0.8 - 0.04);
  tTimingA->SetY2NDC(0.8 + 0.04);
  tTimingA->Draw();

  // 同じ書式で文字を書き込む
  TPaveText* tTimingB = new TPaveText();
  tTimingB->SetFillColor(kWhite);
  tTimingB->SetShadowColor(0);
  tTimingB->SetBorderSize(0);
  tTimingB->SetTextSize (0.06);
  tTimingB->SetTextAlign(22);
  tTimingB->AddText("(b)");
  tTimingB->SetX1NDC(Margin.Left + (1.0 - Margin.Left - Margin.Right) / (xmax - xmin) * (UnexpectedKick::CompTiming - xmin - 0.1));
  tTimingB->SetX2NDC(Margin.Left + (1.0 - Margin.Left - Margin.Right) / (xmax - xmin) * (UnexpectedKick::CompTiming - xmin + 0.1));
  tTimingB->SetY1NDC(0.8 - 0.04);
  tTimingB->SetY2NDC(0.8 + 0.04);
  tTimingB->Draw();
}
