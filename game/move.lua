class.Move { extends('Drawable'),
  
  initialize = function(self, game, textureName)
    self.Drawable.initialize(self, game)
    -- initialize class members here --
    self.sprite = new.Sprite(Textures[textureName])
    self.sprite:setCenter(32, 32)
    -----------------------------------
  end,
  
  setPosition = function(self, x, y)
    self.sprite:setDestination(x, y)
  end,
  
  clone = function(self)
    local clone = self.Drawable.clone(self)
    clone.sprite = new.Sprite(self.sprite:texture())
    clone.sprite:setDestination(self.sprite:position())
    clone.sprite:setCenter(32, 32)
    return clone
   end,
  
  draw = function(self)
    -- draw calls here ----------------
    self.sprite:draw()
    -----------------------------------
  end
  
}
