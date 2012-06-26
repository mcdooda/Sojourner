class.Game {

  initialize = function(self, arg)
    self.updatables = {}
    self.drawables = {}
    self.running = true
  end,

  load = function(self)
    
  end,
  
  setup = function(self, time, graphics)
    
  end,
  
  update = function(self, input, key, time)
    for updatable, _ in pairs(self.updatables) do
      updatable:update(input, key, time)
    end
  end,
  
  draw = function(self)
    for drawable, _ in pairs(self.drawables) do
      drawable:draw()
    end
  end,
  
  exit = function(self)
    self.running = false
  end
  
}
