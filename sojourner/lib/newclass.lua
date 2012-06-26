local classes = {}

-- utility functions

local function tcopy(t)
  local c = {}
  for k, v in pairs(t) do
    c[k] = v
  end
  return c
end

local function tadd(t, u)
  for k, v in pairs(u) do
    t[k] = v -- u erases existing values
  end
end

local function reverse(t)
  return coroutine.wrap(function()
    for i = #t, 1, -1 do
      coroutine.yield(i, t[i])
    end
  end)
end

local function file_exists(filename)
  local f = io.open(filename)
  if f then
    f:close()
    return true
  else
    return false
  end
end

local function load_class(classname)
  if not classes[classname] then -- loads classname.lua
    local filename = string.lower(classname)
    local ok, msg = pcall(function() require(filename) end)
    if not ok then
      error('Undeclared class "'..classname..'"\n'..msg)
    end
  end
end

local function default_allocator(metatable)
  return setmetatable({}, metatable)
end

-- main code below

-- parent of every class
classes.Object = {
  
  initialize = function(self)
    
  end,
  
  destroy = function(self)
    -- only called if self is a userdata (at least in lua 5.1)
  end,
  
  class_name = function(self)
    return getmetatable(self).name
  end,
  
  to_s = function(self)
    return self:class_name()
  end,
  
  clone = function(self)
    local clone = {}
    for k, v in pairs(self) do
      clone[k] = v
    end
    setmetatable(clone, getmetatable(self))
    return clone
  end
  
}

-- class keyword
local class = setmetatable({}, {
  
  __index = function(t, k)
    local newclass = tcopy(classes.Object)
    local classname = k
    
    return function(methods)
      local superclasses = {}
      local allocator
      
      for i = 1, #methods do
        local m = methods[i]
        local r = m[1]
        if r == 'extends' then
          superclasses = {select(2, unpack(m))}
        elseif r == 'allocator' then
          allocator = m[2]
        end
      end
      
      if not allocator then
        allocator = default_allocator
      end
      
      for k, superclass in reverse(superclasses) do
        if type(superclass) == 'string' then
          load_class(superclass)
          tadd(newclass, classes[superclass])
        else
          tadd(newclass, superclass)
        end
        newclass[superclass] = classes[superclass]
      end
      tadd(newclass, methods)
      
      if #superclasses == 0 then
        superclasses[1] = 'Object'
      end
      
      newclass.metatable = {
      
        __index = newclass,
        
        __tostring = function(self)
          return self:to_s()
        end,
        
        __gc = function(self)
          self:destroy()
        end,
        
        __eq = function(self, other)
          if not other.class_name then
            return false
          elseif getmetatable(self) ~= getmetatable(other) then
            return false
          end
          if type(self) == 'table' then
            for k, v in pairs(self) do
              if other[k] ~= v then
                return false
              end
            end
          end
          return true -- userdatas are always the same
        end,
        
        name = classname,
        superclasses = superclasses,
        allocator = allocator
        
      }
      
      classes[classname] = newclass
    end
  end
  
})

-- new keyword
local new = setmetatable({}, {
    
  __index = function(t, classname)
    load_class(classname)
    local metatable = classes[classname].metatable
    local allocator = metatable.allocator
    local constructor = function(...)
      local o = allocator(metatable)
      o:initialize(...)
      return o
    end
    t[classname] = constructor -- new.Class = constructor
    return constructor
  end
  
})

-- extends keyword
local function extends(...)
  return {'extends', ...}
end

-- allocator keyword
local function allocator(func)
  return {'allocator', func}
end

-- abstract function keyword
local function abstract_function()
  error('Trying to call an abstract function')
end

-- public interface
_G['class'], _G['new'] = class, new
_G['extends'], _G['allocator'], _G['abstract_function'] = extends, allocator, abstract_function

