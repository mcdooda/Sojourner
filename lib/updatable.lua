class.Updatable {
  
  initialize = function(self, game)
    self.game = game
    game.updatables[self] = true
  end,
  
  sleep = function(self)
    self.game.updatables[self] = nil
  end,
  
  wakeup = function(self)
    self.game.updatables[self] = true
  end,
  
  sleeping = function(self)
    return not self.game.updatables[self]
  end,
  
  update = function(self, input, key, time)
    
  end
  
}
