--luacheck: ignore describe it setup teardown
describe('native', function()
  local native = require('native')
  describe('.decode(.encode())', function()
    it('encode UTF-8 string in to native encoding', function()
      assert.are.equal('这是一个UTF8字符串', native.decode(native.encode('这是一个UTF8字符串')))
    end)
  end)
end)
