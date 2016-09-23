
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define NCONV_WINDOWS
#endif

#ifdef NCONV_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define LUA_BUILD_AS_DLL
#endif

#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>

#ifdef NCONV_WINDOWS
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
  free(dst);
	free(w);
	return 1;
}
#endif

static int encode(lua_State *L) {
#ifdef NCONV_WINDOWS
	return convert(L, CP_UTF8, CP_OEMCP);
#else
	lua_pushvalue(L, 1); // On non Windows platforms, just return a copy of the arg string.
	return 1;
#endif
}


static int decode(lua_State *L) {
#ifdef NCONV_WINDOWS
	return convert(L, CP_OEMCP, CP_UTF8);
#else
	lua_pushvalue(L, 1); // On non Windows platforms, just return a copy of the arg string.
	return 1;
#endif
}

static luaL_Reg functions[] = {
	{"decode", decode},
	{"encode", encode},
	{NULL, NULL},
};

static void setfuncs(lua_State* L, const luaL_Reg *funcs)
{
#if LUA_VERSION_NUM >= 502 // LUA 5.2 or above
	luaL_setfuncs(L, funcs, 0);
#else
	luaL_register(L, NULL, funcs);
#endif
}

int luaopen_native(lua_State *L)
{
	lua_newtable(L);
	setfuncs(L, functions);
	return 1;
}
