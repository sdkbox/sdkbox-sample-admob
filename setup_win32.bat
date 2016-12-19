@echo off
set CURR_DIR=%~dp0

set BINARY_PATH=%CURR_DIR%\..\sdkbox-cocos2d-x-binary
if not exist %BINARY_PATH% (
	git clone --depth 1 https://github.com/sdkbox/sdkbox-cocos2d-x-binary.git %BINARY_PATH%
)

@echo DONE
