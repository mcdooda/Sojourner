Textures = setmetatable({}, {
  __index = function(t, texture_name)
    local texture = new.Texture('game/'..texture_name)
    t[texture_name] = texture
    return texture
  end
})
