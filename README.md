## About

lua-iconv is hard to upand running, so roll my own!

nconv is a simpile string convertor, it does:

`nconv.native()` converts from UTF-8 to system default encoding.
	
	local mbcs = nconv.native(utf8string)
	print(mbcs) -- should OK in console...

`nconv.utf8()` converts from system default encoding to UTF-8.
	
	local f = io.open('utf8')
	local utf8string = nconv.native(mbcs)
	f:write(utf8string) -- you'v got utf-8 content
	f:close()

## Build

1. You need [Lua for Windows][1] installed. It will set a `LUA_DEV` environment variable for you.
2. Setup a visual studio dll empty project named `nconv`, add header path `$(LUA_DEV)\include` and lib path
`$(LUA_DEV)\lib` to options, and link with `lua5.1.lib`.
3. Build the nconv.dll, and copy to `$(LUA_DEV)\clibs`.
4. Run the `test.lua` for test.

## Binary

Yes, build is boring, just get a copy of prebuild binary from the [download area][2].

## TODO

1. Add to rock repos?

[1]: http://code.google.com/p/luaforwindows/downloads/list
[2]: https://bitbucket.org/xpol/nconv/downloads
