#!/bin/csh
setenv MYLOCATION  `pwd`
echo $MYLOCATION


setenv CMSSCE /home/eno/CMSSW_5_3_29/

cd $CMSSCE
cmsenv
cd $MYLOCATION
setenv PYTHIA8DATA /data/users/eno/pythia8210/share/Pythia8/xmldoc

echo "done"
