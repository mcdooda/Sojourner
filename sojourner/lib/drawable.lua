class.Drawable {
  
  initialize = function(self, game)
    self.game = game
    game.drawables[self] = true
  end,
  
  hide = function(self)
    self.game.drawables[self] = nil
  end,
  
  show = function(self)
    self.game.drawables[self] = true
  end,
  
  hidden = function(self)
    return not self.game.drawables[self]
  end,
  
  draw = function(self)
    
  end
  
}
