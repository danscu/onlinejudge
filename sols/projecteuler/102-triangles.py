import math

def XP(ax,ay,bx,by):
  return ax * by - ay * bx

def triangles(fname):
  inside = 0
  with open(fname) as f:
    for c in f:
      [ax,ay,bx,by,cx,cy] = map(lambda x:int(x), c.split(','))
      xp1 = XP(bx-ax, by-ay, -ax, -ay)
      xp2 = XP(cx-bx, cy-by, -bx, -by)
      xp3 = XP(ax-cx, ay-cy, -cx, -cy)
      if xp1 * xp2 * xp3 == 0 or \
          math.copysign(1,xp1) == math.copysign(1,xp2) == math.copysign(1,xp3):
        inside += 1
  return inside

if __name__ == '__main__':
  print triangles('102-triangles.txt')

