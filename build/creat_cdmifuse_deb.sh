debugfile=0
version=1.0.1.0
#DEB_DEST_FOLDER=$ZQProjsPath/../
DEB_DEST_FOLDER=~/aptpkg

if [ -z "$ZQProjsPath" ]; then 
	echo "Please export ZQProjsPath, $ZQProjsPath is empty"
	echo "Failed to create deb file..... abort"
	exit 1 #if ZQProjsPath is not be set, compile would failed, so abort
fi

if [ -n "$1" ]; then
	debugfile=$1
fi

if [ -n "$2" ]; then
	version=$2
fi

export CDMIFUSE_DEBUG_FILE=$debugfile
export CDMIFUSE_VERSION=$version

cd debcreate && rm -f cdmifuse_1.orig.tar.gz && tar zcvf cdmifuse_1.orig.tar.gz cdmifuse-1 && cd -
cd debcreate && rm -f *.deb && cd -
cd debcreate/cdmifuse-1 && dpkg-buildpackage --source-option=--no-copy && cd -
cp debcreate/*.deb $DEB_DEST_FOLDER
cd $DEB_DEST_FOLDER
PWD=$(pwd)
DEB_FILE_NAME=$(ls | grep *$version*.deb)

echo ==========================================================================
echo "Input argument list = $1, $2"
if [ -n "$DEB_FILE_NAME" ]; then
	echo "debugfile=$debugfile"
	echo "version=$version"
	echo "Succeed to create deb file="$PWD"/"$DEB_FILE_NAME
else
	echo "Failed to create deb file..... abort"
fi

