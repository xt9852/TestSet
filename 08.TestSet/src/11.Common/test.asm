

PUBLIC GetArgument2			; 相当于c的extern

.486						; create 32 bit code

.model flat,stdcall			; 32 bit memory model

;option casemap :none		; case sensitive

GetArgument PROTO :DWORD	; 函数声明

_TEXT SEGMENT PUBLIC 'CODE'

GetArgument2 PROC dwArg:DWORD

    INVOKE GetArgument, dwArg	; 调用C++的GetArgument(DWORD)

    MOV EAX, dwArg			; return x

    POP EBP					; 平衡堆栈

    RETN 4

GetArgument2 ENDP

_TEXT ENDS

END
