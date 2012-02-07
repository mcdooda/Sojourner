class.%s { extends('Updatable', 'Drawable'),
  
  initialize = function(self, game)
    self.Updatable.initialize(self, game)
    self.Drawable.initialize(self, game)
    -- initialize class members here --
    --local texture = Textures['picture.png']
    --self.sprite = new.Sprite(texture)
    -----------------------------------
  end,
  
  update = function(self, input, key, time)
    -- update logic here --------------
    
    -----------------------------------
  end,
  
  draw = function(self)
    -- draw calls here ----------------
    --self.sprite:draw()
    -----------------------------------
  end
  
}
