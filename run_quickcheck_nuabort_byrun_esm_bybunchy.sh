#!/bin/sh
#root -b -q runmaketemplate_ver3.C\($1\)
for i in {0..20}; do
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710253,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710250,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710235,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710234,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710233,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710228,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_esm_bybunchy.C\(710215,$i\)
done

