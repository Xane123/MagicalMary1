cd C:/truecolorsw
set PATH=;%PATH%

if [%1]==[--debugger] (
	SHIFT
)

"C:\truecolorsw\RelWithDebInfo\wok.exe"  
pause
