
int imt001_parBranchProcessing()
{
    int nthreads = 8;
    ROOT::EnableImplicitMT(nthreads);
    auto file = TFile::Open("/home/kuanyu/Documents/root_file/Ztoee/2016BKGMC/DY/ee_DYincli.root");

    // Get the tree
    auto tree = file->Get<TTree>("T_tree");

    const auto nEntries = tree->GetEntries();

    std::cout << "Entries = " << nEntries << std::endl;
    // Read the branches in parallel.
    // Note that the interface does not change, the parallelisation is internal
    for (auto i : ROOT::TSeqUL(nEntries))
    {
        tree->GetEntry(i); // parallel read
        std::cout << "i = " << i << std::endl;
    }
    return 0;
}