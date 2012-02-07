function info(msg)
  print('SJ: '..msg)
end

function createFileFromTemplate(template, file, ...)
  local f = io.open(file, 'w')
  local tpl = io.open(template, 'r')
  f:write(string.format(tpl:read('*all'), ...))
  tpl:close()
  f:close()
  info('created '..file)
end

function toClassName(name)
  return string.upper(string.sub(name, 1, 1))..string.lower(string.sub(name, 2, #name))
end

function isIdentifier(name)
  return string.match(name, '^[_%a][_%w]*$') ~= nil
end

function checkArg(name, value, cond)
  if not cond(value) then
    error('Wrong parameter "'..name..'"')
  end
end

function try(block, catch, else_)
  local ok, msg = pcall(block)
  if not ok then
    catch(msg)
  else
    else_()
  end
end
