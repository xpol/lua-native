local native = require('native')

local function readline(filename)
  local f = io.open(filename)
  local ln = f:read('*l')
  f:close()
  return ln
end

describe('native', function()
  describe('.encode() and .decode()', function()
    it('convert between UTF-8 string and native encoding', function()
      local utf8 = readline('spec/data/utf-8')
      assert.are.equal(utf8, native.decode(native.encode(utf8)))
    end)
  end)
end)
