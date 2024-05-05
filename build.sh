#!/bin/sh
ROOTDIR=$PWD

cd $ROOTDIR/raylib/src
make 
rm *.o

cd $ROOTDIR/src
make 
rm *.o

cd $ROOTDIR

if [ ! -d $ROOTDIR/bin ];then
mkdir $ROOTDIR/bin
fi;

if [ ! -d $ROOTDIR/bin/resources ];then
cp -r $ROOTDIR/src/resources $ROOTDIR/bin/resources
fi;
cp $ROOTDIR/src/PartyGameLauncher $ROOTDIR/bin