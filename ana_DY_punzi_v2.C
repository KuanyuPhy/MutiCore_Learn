#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TMath.h>
#include <time.h>
#include <TFile.h>
#include <TH3D.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <ROOT/TSeq.hxx>
#include <TLine.h>
#include "/home/kuanyu/Documents/CMS/ZtoLL_Plot/ana/lib/Cross_section.h"
using namespace std;

TFile *DYincli = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_DYincli.root");
TFile *DYHT100 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht100.root");
TFile *DYHT600 = new TFile("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_ht600.root");

//---------------------
// Define the HTWeight
//---------------------
double HT0Weight = 1.13213;
double HT70Weight = 1.22077;
double HT100Weight = 0.358809;
double HT200Weight = 0.156015;
double HT400Weight = 0.164709;
double HT600Weight = 0.00585068;
double HT800Weight = 0.0083243;
double HT1200Weight = 0.00905095;
double HT2500Weight = 0.000328741;

void for_inclusive_sample(float HT, float i_tmp, double Weight, TH1D *h_tmp)
{
    if (HT < 70)
    {
        h_tmp->Fill(i_tmp, HT0Weight);
    }
    else if (HT >= 70 && HT < 100)
    {
        h_tmp->Fill(i_tmp, HT70Weight);
    }
    else if (HT >= 100 && HT < 200)
    {
        h_tmp->Fill(i_tmp, HT100Weight);
    }
    else if (HT >= 200 && HT < 400)
    {
        h_tmp->Fill(i_tmp, HT200Weight);
    }
    else if (HT >= 400 && HT < 600)
    {
        h_tmp->Fill(i_tmp, HT400Weight);
    }
    else if (HT >= 600 && HT < 800)
    {
        h_tmp->Fill(i_tmp, HT600Weight);
    }
    else if (HT >= 800 && HT < 1200)
    {
        h_tmp->Fill(i_tmp, HT800Weight);
    }
    else if (HT >= 1200 && HT < 2500)
    {
        h_tmp->Fill(i_tmp, HT1200Weight);
    }
    else if (HT >= 2500)
    {
        h_tmp->Fill(i_tmp, HT2500Weight);
    }
}

void ana_DY_punzi_v2()
{
    int nthreads = 12;
    ROOT::EnableImplicitMT(nthreads);

    clock_t start, end;

    start = clock();
    TH1D *h_pass_DY = new TH1D("h_pass_DY", "", 50, 0, 50);
    h_pass_DY->Sumw2();

    TH1D *h_pass_DY_nMetcut = new TH1D("h_pass_DY_nMetcut", "", 50, 0, 50);
    h_pass_DY_nMetcut->Sumw2();

    float_t HT;

    float_t f_ht0_Met, f_ht70_Met, f_ht100_Met, f_ht200_Met, f_ht400_Met, f_ht600_Met, f_ht800_Met,
        f_ht1200_Met, f_ht2500_Met;

    Int_t I_ht0_weight, I_ht70_weight, I_ht100_weight, I_ht200_weight, I_ht400_weight, I_ht600_weight,
        I_ht800_weight, I_ht1200_weight, I_ht2500_weight;

    vector<float> *v_ht0_alpha = new vector<float>();
    vector<float> *v_ht70_alpha = new vector<float>();
    vector<float> *v_ht100_alpha = new vector<float>();
    vector<float> *v_ht200_alpha = new vector<float>();
    vector<float> *v_ht400_alpha = new vector<float>();
    vector<float> *v_ht600_alpha = new vector<float>();
    vector<float> *v_ht800_alpha = new vector<float>();
    vector<float> *v_ht1200_alpha = new vector<float>();
    vector<float> *v_ht2500_alpha = new vector<float>();

    v_ht0_alpha->clear();
    v_ht70_alpha->clear();
    v_ht100_alpha->clear();
    v_ht200_alpha->clear();
    v_ht400_alpha->clear();
    v_ht600_alpha->clear();
    v_ht800_alpha->clear();
    v_ht1200_alpha->clear();
    v_ht2500_alpha->clear();

    for (int i = 1; i <= 50; i++)
    {
        cout << "i" << i << endl;
        float metcut = i * 10;

        TTree *T_inclusive;
        DYincli->GetObject("T_tree", T_inclusive);
        T_inclusive->SetBranchAddress("I_weight", &I_ht0_weight);
        T_inclusive->SetBranchAddress("f_HT", &HT);
        T_inclusive->SetBranchAddress("f_Met", &f_ht0_Met);
        T_inclusive->SetBranchAddress("v_fakealpha", &v_ht0_alpha);
        const auto Inclusive_nEntries = T_inclusive->GetEntries();
        for (auto evt : ROOT::TSeqUL(Inclusive_nEntries))
        {
            T_inclusive->GetEntry(evt);
            bool alpha_cut = true;
            for (int i = 0; i < v_ht0_alpha->size(); i++)
            {
                if ((*v_ht0_alpha)[i] > 0.15)
                {
                    alpha_cut = false;
                    break;
                }
            }
            if (!alpha_cut)
            {
                continue;
            }
            //-------------------
            // Scan Met
            //-------------------
            for_inclusive_sample(HT, i, I_ht0_weight, h_pass_DY);
            if (f_ht0_Met > metcut)
            {
                for_inclusive_sample(HT, i, I_ht0_weight, h_pass_DY_nMetcut);
            }
        }
        TTree *T_HT100;
        DYHT100->GetObject("T_tree", T_HT100);
        T_HT100->SetBranchAddress("I_weight", &I_ht100_weight);
        T_HT100->SetBranchAddress("f_Met", &f_ht100_Met);
        T_HT100->SetBranchAddress("v_fakealpha", &v_ht100_alpha);
        const auto HT100_nEntries = T_HT100->GetEntries();
        for (auto evt : ROOT::TSeqUL(HT100_nEntries))
        {
            T_HT100->GetEntry(evt);
            bool alpha_cut = true;
            for (int i = 0; i < v_ht100_alpha->size(); i++)
            {
                if ((*v_ht100_alpha)[i] > 0.15)
                {
                    alpha_cut = false;
                    break;
                }
            }
            if (!alpha_cut)
            {
                continue;
            }
            //-------------------
            // Scan Met
            //-------------------
            h_pass_DY->Fill(i, I_ht100_weight * HT100Weight);
            if (f_ht100_Met > metcut)
            {
                h_pass_DY_nMetcut->Fill(i, I_ht100_weight * HT100Weight);
            }
        }
        TTree *T_HT600;
        DYHT600->GetObject("T_tree", T_HT600);
        T_HT600->SetBranchAddress("I_weight", &I_ht600_weight);
        T_HT600->SetBranchAddress("f_Met", &f_ht600_Met);
        T_HT600->SetBranchAddress("v_fakealpha", &v_ht600_alpha);
        const auto HT600_nEntries = T_HT600->GetEntries();
        for (auto evt : ROOT::TSeqUL(HT600_nEntries))
        {
            T_HT600->GetEntry(evt);
            bool alpha_cut = true;
            for (int i = 0; i < v_ht600_alpha->size(); i++)
            {
                if ((*v_ht600_alpha)[i] > 0.15)
                {
                    alpha_cut = false;
                    break;
                }
            }
            if (!alpha_cut)
            {
                continue;
            }
            //-------------------
            // Scan Met
            //-------------------
            h_pass_DY->Fill(i, I_ht600_weight * HT600Weight);
            if (f_ht600_Met > metcut)
            {
                h_pass_DY_nMetcut->Fill(i, I_ht600_weight * HT600Weight);
            }
        }
    }
    h_pass_DY_nMetcut->Draw();
    TString outputfile1 = "./ee_DY_punzi.root";
    TFile *outfile_HT0 = TFile::Open(outputfile1, "RECREATE");
    h_pass_DY->Write();
    h_pass_DY_nMetcut->Write();
    outfile_HT0->Close();
    end = clock();
    cout << double(end) / CLOCKS_PER_SEC << endl;
}
int main()
{
    ana_DY_punzi_v2();
}