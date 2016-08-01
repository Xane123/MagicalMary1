cd C:/truecolorsw
set PATH=;%PATH%

if [%1]==[--debugger] (
	SHIFT
)

"C:\truecolorsw\Release\wok.exe"  
pause
