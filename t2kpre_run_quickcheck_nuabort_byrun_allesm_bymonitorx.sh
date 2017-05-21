#!/bin/sh
#root -b -q runmaketemplate_ver3.C\($1\)
for i in {0..7}; do
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710253,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710250,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710235,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710234,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710233,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710228,$i\)
#root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(710215,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(720016,$i\)
root -b -q t2kpre_quickcheck_nuabort_byrun_allesm_bymonitorx.C\(720022,$i\)

done

