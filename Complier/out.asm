.486 
    .model flat, stdcall 
    option casemap :none

include msvcrt.inc
includelib msvcrt.lib
 
.data
       szFmtOut       db    '%f',0
       szFmtIn         db    '%f',0
       szText            dd    1.2
.code
start:
    invoke     crt_scanf, addr szFmtIn,addr szText   
    invoke     crt_printf, addr szFmtOut,szText
    ret
end start