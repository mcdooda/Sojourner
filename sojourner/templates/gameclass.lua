class.%s { extends('Game'),

  initialize = function(self, arg)
    self.Game.initialize(self)
    -- initialize class members here --
    
    -----------------------------------
  end,

  load = function(self)
    -- load files here ----------------
    
    -----------------------------------
  end,
  
  setup = function(self, time, graphics)
    -- set up the game's environment --
    
    -----------------------------------
  end,
  
  update = function(self, input, key, time)
    -- game logic here ----------------
    
    -----------------------------------
    self.Game.update(self, input, key, time)
  end,
  
  draw = function(self)
    -- draw calls ---------------------
    
    -----------------------------------
    self.Game.draw(self)
  end
  
}
