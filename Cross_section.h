#ifndef CROSS_SECTION
#define CROSS_SECTION
// ====
// Cross_Srction: pb
// ====
class GlobalConstants
{
public:
    // Unit pb^-1
    static constexpr float Lumi2016 = 35.9;
    // For DY Background
    static constexpr float HT0CS = 4274.424946;
    static constexpr float HT70CS = 149.9710714;
    static constexpr float HT100CS = 147.4;
    static constexpr float HT200CS = 41.04;
    static constexpr float HT400CS = 5.674;
    static constexpr float HT600CS = 1.358;
    static constexpr float HT800CS = 0.6229;
    static constexpr float HT1200CS = 0.1512;
    static constexpr float HT2500CS = 0.003659;
    static constexpr float PT50CS = 344.3;
    static constexpr float PT100CS = 80.64;
    static constexpr float PT250CS = 2.955;
    static constexpr float PT400CS = 0.3807;
    static constexpr float PT650CS = 0.03711;
    // For Top Background
    static constexpr float ST_tW_top_5fCS = 35.6;
    static constexpr float ST_tW_antitop_5fCS = 35.6;
    static constexpr float TTTo2L2Nu = 88.29;
    static constexpr float TTWJetsToLNu = 0.2043;
    static constexpr float TTWJetsToQQ = 0.4062;
    static constexpr float TTZToLLNuNu = 0.2529;
    static constexpr float TTZToQQ = 0.5297;
    // For Diboson Background
    static constexpr float gg_WW_2L2Nu = 0.5905;
    static constexpr float gg_ZZ_2e2mu = 0.003194 * 2.3;
    static constexpr float gg_ZZ_2e2nu = 0.001720 * 2.3;
    static constexpr float gg_ZZ_2e2tau = 0.003194 * 2.3;
    static constexpr float gg_ZZ_2mu2nu = 0.001720 * 2.3;
    static constexpr float gg_ZZ_2mu2tau = 0.003194 * 2.3;
    static constexpr float gg_ZZ_4e = 0.001586 * 2.3;
    static constexpr float gg_ZZ_4mu = 0.001586 * 2.3;
    static constexpr float gg_ZZ_4tau = 0.001586 * 2.3;
    static constexpr float qq_WW_2L2Nu = 12.18;
    static constexpr float qq_WZ_2L2Q = 5.595 * 1.109;
    static constexpr float qq_WZ_3LNu = 4.42965 * 1.109;
    static constexpr float qq_ZZ_2L2Nu = 0.564;
    static constexpr float qq_ZZ_2L2Q = 3.220;
    static constexpr float qq_ZZ_4L = 1.256;

    // For Triboson Background
    static constexpr float WWZ_TuneCUETP8M1 = 0.16510;
    static constexpr float WZZ_TuneCUETP8M1 = 0.05565;
    static constexpr float ZZZ_TuneCUETP8M1 = 0.01398;
};
#endif
