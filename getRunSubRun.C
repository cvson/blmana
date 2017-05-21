void getRunSubRun(){
ifstream cfile("database_nuabort.txt");
//ifstream cfile("database_nuabort_r72.txt");
         string line;
        getline(cfile,line);
        std::vector<int> run;
        std::vector<int> spill;

         while (getline(cfile, line))
     {
       stringstream ss(line);
       double p1, p2;
       if(!(ss>>p1>>p2))
         {
           cerr<<"Bad line format: "<<endl
               <<"     "<<line<<endl;
           continue;
         }
       run.push_back(p1);
       spill.push_back(p2);
     }
   cfile.close();
cout<<"Total NU Abort "<<run.size()<<endl;

ofstream ofs("search4subrun.sh");
ofs <<"#!/bin/sh"<<endl;
for (int i=0; i<run.size();i++){
ofs <<"grep "<<spill.at(i)<<" /export/jnulsv01/home/cvson/atwork/blm/ofl9/runblm/integ2/r"<<run.at(i)<<"*.integ2 | cut -c66-70"<<endl;
}
ofs.close();
}
