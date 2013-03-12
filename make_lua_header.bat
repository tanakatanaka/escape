@echo off
for /f %%r in ('dir /b /OD lua_header.h lua_header.pkg') do (
	if %%r equ lua_header.h (
		echo running tolua..
		tolua -o lua_header.h lua_header.pkg
	) else if %%r equ lua_header.pkg (
		echo lua_header.h already updated
	) else (
		echo "unexpected"
	)
	exit /b %errorlevel%
)