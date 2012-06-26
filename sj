#!/usr/bin/env lua5.1

local sojourner_path = 'sojourner'

require(sojourner_path..'/scripts/util')

local commands = {
  
  new = {
    description = "\t\tCreates a whole new sojourner project",
    action = function(projectName)
        checkArg('Project name', projectName, function(v) return type(v) == 'string' end)
        createFileFromTemplate(sojourner_path..'/templates/gameclass.lua', string.lower(projectName)..'.lua', toClassName(projectName))
        createFileFromTemplate(sojourner_path..'/templates/config.lua', 'config.lua', projectName, toClassName(projectName))
      end
  },
  
  class = {
    description = "\tCreates a new class file",
    action = function(className)
      checkArg('Class name', className, isIdentifier)
      createFileFromTemplate(sojourner_path..'/templates/class.lua', string.lower(className)..'.lua', toClassName(className))
    end
  },
  
  updatable = {
    description = "\tCreates an updatable object",
    action = function(updatableName)
      checkArg('Updatable name', updatableName, isIdentifier)
      createFileFromTemplate(sojourner_path..'/templates/updatable.lua', string.lower(updatableName)..'.lua', toClassName(updatableName))
    end
  },
  
  drawable = {
    description = "\tCreates a drawable object",
    action = function(drawableName)
      checkArg('Drawable name', drawableName, isIdentifier)
      createFileFromTemplate(sojourner_path..'/templates/drawable.lua', string.lower(drawableName)..'.lua', toClassName(drawableName))
    end
  },
  
  gameobject = {
    description = "\tCreates a game object (both drawable and updatable)",
    action = function(gameObjectName)
      checkArg('Game object name', gameObjectName, isIdentifier)
      createFileFromTemplate(sojourner_path..'/templates/gameobject.lua', string.lower(gameObjectName)..'.lua', toClassName(gameObjectName))
    end
  }
  
}

local function help()
  print 'Available commands:'
  for commandname, command in pairs(commands) do
    print('  '..commandname..' '..command.description)
  end
end

local command = arg[1]
try(function()
  if not command then
    help()
  elseif commands[command] then
    commands[command].action(select(2, unpack(arg)))
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
