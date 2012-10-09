local nconv = require('nconv')

print(nconv.native("这是一个UTF8字符串"))
local f = io.open('bom', 'r')
local text = f:read('*a')
f:close()
local n = nconv.native(text)
print(n)

f = io.open('nobom', 'w')
f:write(nconv.utf8(n))
f:close()
