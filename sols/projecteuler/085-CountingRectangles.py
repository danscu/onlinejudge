# Answer: 2772

def CountRect(x,y):
  return (x+1)*x*(y+1)*y/4

target = 2000000
best = target

for x in range(1,2000):
  for y in range(1,2000):
    c = CountRect(x,y)
    if abs(c - target) < best:
      best = abs(c - target)
      bestx = x
      besty = y

print bestx * besty

