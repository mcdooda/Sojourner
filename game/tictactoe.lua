class.Tictactoe { extends('Game'),

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
    graphics.clearColor(255, 255, 255)
    self.cross = new.Cross(self)
    self.cross:hide()
    self.circle = new.Circle(self)
    self.cursor = self.circle
    
    self.board = {
      {false, false, false},
      {false, false, false},
      {false, false, false}
    }
    -----------------------------------
  end,
  
  nextTurn = function(self)
    self.cursor:hide()
    if self.cursor == self.cross then
      self.cursor = self.circle
    else
      self.cursor = self.cross
    end
    self.cursor:show()
    self:testEnd()
  end,
  
  testEnd = function(self)
    local board = self.board
    local winner
    if not winner then
      for i = 1, 3 do
        if board[i][1] and board[i][1] == board[i][2] and board[i][1] == board[i][3] then
          winner = board[i][1]
          break
        end
      end
    end
    if not winner then
      for i = 1, 3 do
        if board[1][i] and board[1][i] == board[2][i] and board[1][i] == board[3][i] then
          winner = board[1][i]
          break
        end
      end
    end
    if not winner then
      if board[1][1] and board[1][1] == board[2][2] and board[1][1] == board[3][3] then
        winner = board[1][1]
      end
    end
    if not winner then
      if board[3][1] and board[3][1] == board[2][2] and board[3][1] == board[1][3] then
        winner = board[3][1]
      end
    end
    if winner then
      print(tostring(winner)..' wins!')
      self:exit()
    else
      local movesCount = 0
      for i = 1, 3 do
        for j = 1, 3 do
          if board[i][j] then
            movesCount = movesCount + 1
          end
        end
      end
      if movesCount == 9 then
        print('Ex aequo!')
        self:exit()
      end
    end
  end,
  
  update = function(self, input, key, time)
    -- game logic here ----------------
    if input.mouseJustPressed(1) then
      local x, y = input.pointer()
      x = math.ceil(x / 64)
      y = math.ceil(y / 64)
      if not self.board[x][y] then
        local move = self.cursor:clone()
        move:setPosition(x * 64 - 32, y * 64 - 32)
        move:show()
        self.board[x][y] = move
        self:nextTurn()
      end
    end
    self.cursor:setPosition(input.pointer())
    -----------------------------------
    self.Game.update(self, input, key, time)
  end,
  
  draw = function(self)
    -- draw calls ---------------------
    
    -----------------------------------
    self.Game.draw(self)
  end
  
}
