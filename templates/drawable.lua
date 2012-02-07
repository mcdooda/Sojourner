class.%s { extends('Drawable'),
  
  initialize = function(self, game)
    self.Drawable.initialize(self, game)
    -- initialize class members here --
    --local texture = Textures['picture.png']
    --self.sprite = new.Sprite(texture)
    -----------------------------------
  end,
  
  draw = function(self)
    -- draw calls here ----------------
    --self.sprite:draw()
    -----------------------------------
  end
  
}
