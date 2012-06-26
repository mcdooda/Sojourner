#!/usr/bin/env lua5.1

require 'scripts/util'

local commands = {
  
  new = function(projectName)
    checkArg('Project name', projectName, function(v) return type(v) == 'string' end)
    createFileFromTemplate('templates/gameclass.lua', string.lower(projectName)..'.lua', toClassName(projectName))
    createFileFromTemplate('templates/config.lua', 'config.lua', projectName, toClassName(projectName))
  end,
  
  class = function(className)
    checkArg('Class name', className, isIdentifier)
    createFileFromTemplate('templates/class.lua', string.lower(className)..'.lua', toClassName(className))
  end,
  
  updatable = function(updatableName)
    checkArg('Updatable name', updatableName, isIdentifier)
    createFileFromTemplate('templates/updatable.lua', string.lower(updatableName)..'.lua', toClassName(updatableName))
  end,
  
  drawable = function(drawableName)
    checkArg('Drawable name', drawableName, isIdentifier)
    createFileFromTemplate('templates/drawable.lua', string.lower(drawableName)..'.lua', toClassName(drawableName))
  end,
  
  gameobject = function(gameObjectName)
    checkArg('Game object name', gameObjectName, isIdentifier)
    createFileFromTemplate('templates/gameobject.lua', string.lower(gameObjectName)..'.lua', toClassName(gameObjectName))
  end
  
}

local function help()
  print 'Available commands:'
  for command, _ in pairs(commands) do
    print('  '..command)
  end
end

local command = arg[1]
try(function()
  if not command then
    help()
  elseif commands[command] then
    commands[command](select(2, unpack(arg)))
  else
    print('Unknown command '..command)
    help()
  end
end, function(err)
  print(err)
end, function()
  if command then
    info(command..' ok')
  end
end)
