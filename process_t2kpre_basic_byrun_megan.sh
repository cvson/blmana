#!/bin/sh
source ~/env_root.sh 
 
root -b -q "t2kpre_basic_byrun_megan.C($1, $2)"

echo "
document.write(\"$1\");
" > date.js
cp "date.js" ~/public_html/beamorbit/

