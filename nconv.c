#include <Windows.h>
#define LUA_BUILD_AS_DLL
#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"

static int convert( lua_State * L, UINT decode, UINT encode ) 
{
	size_t srcsz = 0;
	const char* src = luaL_checklstring(L, 1, &srcsz);
	wchar_t* w = malloc(sizeof(*w) * srcsz*2);
	char* dst = malloc(sizeof(*dst) * srcsz*2);
	int bom = (decode == CP_UTF8) 
		&& src[0] == '\xEF' 
		&& src[1] == '\xBB'
		&& src[2] == '\xBF';
	int bomsz = bom ? 3 : 0;
	int wsz = MultiByteToWideChar(decode, 0, src+bomsz, srcsz-bomsz, w, srcsz*2);
	int dstsz = WideCharToMultiByte(encode, 0, w, wsz, dst, srcsz*2, 0, 0);
	lua_pushlstring(L, dst, dstsz);
	free(w);
	free(dst);
	return 1;
}


static int native(lua_State *L) {
	return convert(L, CP_UTF8, CP_OEMCP);
}


static int utf8(lua_State *L) {
	return convert(L, CP_OEMCP, CP_UTF8);
}

static luaL_Reg driver[] = {
	{"native", native},
	{"utf8", utf8},	
	{NULL, NULL},
};

int LUALIB_API luaopen_nconv(lua_State *L)
{
	luaL_openlib(L, "nconv", driver, 0);
	return 1;
}
