require 'lib/cache'

--[[local factorielle
factorielle = cache(function(n)
  if n <= 1 then
    return 1
  else
    return n * factorielle(n - 1)
  end
end)]]

--[[function factorielle(n)
  if n <= 1 then
    return 1
  else
    return n * factorielle(n - 1)
  end
end]]

--[[function factorielle(n)
  local f = 1
  for i = 1, n do
    f = f * i
  end
  return f
end]]

local factorielle
factorielle = cache(function(n)
  local f = 1
  for i = 1, n do
    f = f * i
  end
  return f
end)

for i = 1, 10000 do
  for j = 1, 170 do
    factorielle(j)
  end
end

