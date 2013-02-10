#!/bin/sh

TOPDIR=`pwd`
RPMDIR=$TOPDIR/rpm
SRCDIR=$RPMDIR/SOURCES
PKGNAME=`grep Name $RPMDIR/apr-helper.spec | awk -F" " '{ print $2 }'`
PKGVERSION=`grep Version $RPMDIR/apr-helper.spec | awk -F" " '{ print $2 }'`
TGZDIR=$SRCDIR/$PKGNAME-$PKGVERSION

echo "Creating source pakage $PKGNAME-$PKGVERSION.tar.gz..."
rm -rf $RPMDIR/BUILD $RPMDIR/BUILDROOT $RPMDIR/RPMS $RPMDIR/SOURCES $RPMDIR/SRPMS $RPMDIR/SPECS
mkdir -p $TGZDIR/cmake
mkdir -p $TGZDIR/rpm
mkdir -p $TGZDIR/src
mkdir -p $TGZDIR/tsrc
cp -r $TOPDIR/cmake/* $TGZDIR/cmake
cp    $TOPDIR/rpm/apr-helper.spec $TGZDIR/rpm
cp -r $TOPDIR/src/* $TGZDIR/src
cp -r $TOPDIR/tsrc/* $TGZDIR/tsrc
cp $TOPDIR/CMakeLists.txt $TGZDIR
cp $TOPDIR/buildrpm.sh $TGZDIR
mkdir -p $RPMDIR/BUILD $RPMDIR/BUILDROOT $RPMDIR/RPMS $RPMDIR/SOURCES $RPMDIR/SRPMS $RPMDIR/SPECS
cd $SRCDIR
tar -pczf $PKGNAME-$PKGVERSION.tar.gz $PKGNAME-$PKGVERSION
rm -rf $PKGNAME-$PKGVERSION
cd $TOPDIR

echo "Building RPM packages..."
rpmbuild --define "_topdir $RPMDIR" -ba rpm/apr-helper.spec
