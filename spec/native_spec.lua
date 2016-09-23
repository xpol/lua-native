-- TO RUN THIS TEST, YOU NEED TO CHANGE YOU WIDNOWS CMD TO CODE PAGE 936. (RUN `CHCP 936` IN CMD WINDOW)
local native = require('native')

local function readline(filename)
  local f = io.open(filename)
  local ln = f:read('*l')
  f:close()
  return ln
end

local utf8 = readline('spec/data/utf8')
local cp936 = readline('spec/data/cp936')

describe('native', function()
  describe('.encode()', function()
    it('convert from UTF-8 string to native encoding', function()
      assert.are.equal(cp936, native.encode(utf8))
    end)
  end)

  describe('.decode()', function()
    it('convert to UTF-8 string from native encoding', function()
      assert.are.equal(utf8, native.decode(cp936))
    end)
  end)
end)
