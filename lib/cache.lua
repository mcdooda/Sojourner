function cache(f)
  local c = setmetatable({}, {
    __index = function(t, k)
      local v = f(k)
      t[k] = v
      return v
    end
  })
  return function(k)
    return c[k]
  end
end
