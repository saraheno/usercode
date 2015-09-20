# PYTHIA configuration file.
# Generated on Fri Sep 4 16:09:47 EDT 2015 with the user supplied options:
# --with-root=/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/root/5.32.00/

# Install directory prefixes.
PREFIX_BIN=/home/eno/data/pythia8210/bin
PREFIX_INCLUDE=/home/eno/data/pythia8210/include
PREFIX_LIB=/home/eno/data/pythia8210/lib
PREFIX_SHARE=/home/eno/data/pythia8210/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=false
CXX=g++
CXX_COMMON=-O2 -ansi -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname
LIB_SUFFIX=.so

# EVTGEN configuration.
EVTGEN_USE=false
EVTGEN_BIN=
EVTGEN_INCLUDE=
EVTGEN_LIB=

# FASTJET3 configuration.
FASTJET3_USE=false
FASTJET3_BIN=
FASTJET3_INCLUDE=
FASTJET3_LIB=

# HEPMC2 configuration.
HEPMC2_USE=false
HEPMC2_BIN=
HEPMC2_INCLUDE=
HEPMC2_LIB=

# HEPMC3 configuration.
HEPMC3_USE=false
HEPMC3_BIN=
HEPMC3_INCLUDE=
HEPMC3_LIB=

# LHAPDF5 configuration.
LHAPDF5_USE=false
LHAPDF5_BIN=
LHAPDF5_INCLUDE=
LHAPDF5_LIB=
LHAPDF5_PLUGIN=LHAPDF5.h

# LHAPDF6 configuration.
LHAPDF6_USE=false
LHAPDF6_BIN=
LHAPDF6_INCLUDE=
LHAPDF6_LIB=
LHAPDF6_PLUGIN=LHAPDF5.h

# POWHEG configuration.
POWHEG_USE=false
POWHEG_BIN=
POWHEG_INCLUDE=
POWHEG_LIB=

# PROMC configuration.
PROMC_USE=false
PROMC_BIN=
PROMC_INCLUDE=
PROMC_LIB=

# ROOT configuration.
ROOT_USE=true
ROOT_BIN=/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/root/5.32.00//bin/
ROOT_INCLUDE=/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/root/5.32.00//include
ROOT_LIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/root/5.32.00//lib

# GZIP configuration.
GZIP_USE=false
GZIP_BIN=
GZIP_INCLUDE=
GZIP_LIB=

# BOOST configuration.
BOOST_USE=false
BOOST_BIN=
BOOST_INCLUDE=
BOOST_LIB=
