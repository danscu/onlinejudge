def findLess(n, frac):
  l = 0
  r = n
  while r - l > 1:
    m = (l + r) / 2
    if 1.0 * m / n < frac:
      l = m
    else:
      r = m
  return l

def gcd(a, b):
  while b != 0:
    t = b
    b = a % b
    a = t
  return a

def closest_numerator(N, frac):
  dist = 2
  ans = 0
  for i in range(1,N+1):
    l = findLess(i, frac)
    if frac - 1.0 * l/i < dist:
      dist = frac - 1.0 * l/i
      x = gcd(l, i)
      ans = l / x
      # print "i=",i,"l=",l,"l/i=",1.0*l/i
  return ans

if __name__ == '__main__':
  print closest_numerator(1000000, 3.0/7)

