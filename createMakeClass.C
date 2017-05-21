void createMakeClass(char* filename="",char* treename="", char* classname=""){
    TFile *pfile = new TFile(filename);
    TTree *ptree = (TTree*)pfile->Get(treename);
    ptree->MakeClass(classname);
    
}

/*{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L basicPlotUtil.C");
    
    gROOT->ProcessLine(".L initAnalysis.C");
    
    initAnalysis *pAnalysis = new initAnalysis();
    //pAnalysis->Loop(true,"/home/cvson/cc1picoh/frkikawa/data/merged_ccqe.root","dt_basic.root");
    //    pAnalysis->Loop(false,"/home/cvson/cc1picoh/frkikawa/MC/pm/merged_ccqe.root","pm_merged_ccqe_basic.root");
    //        cout<<"Processing sucessfully"<<endl;
    }*/
