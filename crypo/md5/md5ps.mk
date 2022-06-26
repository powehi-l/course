
md5ps.dll: dlldata.obj md5_p.obj md5_i.obj
	link /dll /out:md5ps.dll /def:md5ps.def /entry:DllMain dlldata.obj md5_p.obj md5_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del md5ps.dll
	@del md5ps.lib
	@del md5ps.exp
	@del dlldata.obj
	@del md5_p.obj
	@del md5_i.obj
