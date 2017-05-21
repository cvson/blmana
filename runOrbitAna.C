{
    gROOT->ProcessLine(".x /export/jnulsv01/home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /export/jnulsv01/home/cvson/basicPlotUtil.C");
    
    gROOT->ProcessLine(".L hOrbitAna.C");
    
    hOrbitAna *pAnalysis = new hOrbitAna();
    pAnalysis->MakeBasicPlot("/export/jnulsv01/home/cvson/atwork/myana/run/rootfiles/run0710268_orbit.root","/export/jnulsv01/home/cvson/atwork/myana/run/basichisto/histo_run0710268_orbit.root");
    
}
