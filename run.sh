#!/bin/bash
CUR_DIR=$(cd "$(dirname $0)" && pwd)

cd "$CUR_DIR"

if [ ! -d ../sdkbox-cocos2d-x-binary ]; then
	echo "[ERROR] not found sdkbox-cocos2d-x-binary"
	echo ""
	cat README.md
	exit
fi

if [ "$2" == "" ]; then
	echo "[ERROR] not specified language and platform"
	echo ""

	echo "syntax:"
	echo "  run.sh LANGUAGE PLATFORM"
	echo ""
	echo "examples:"
	echo "  run.sh cpp android"
	echo "  run.sh js ios"
	echo ""
	exit
fi

../sdkbox-cocos2d-x-binary/run_sample.sh apteligent $*
