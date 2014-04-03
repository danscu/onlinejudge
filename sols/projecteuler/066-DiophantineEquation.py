from __future__ import division
from math import sqrt

xlim = 10000000

def sol_slow():
	global xlim
	maxX = 0
	for D in range(2,1000):
	  if sqrt(D)*sqrt(D) == D:
	    continue
	  x = 1
	  done = False
	  while not done and x <= xlim:
	    y = sqrt((x*x - 1) / D)
	    if y == int(y) and y > 0:
	      print "D =",D,"x =",x,"y =",y
	      done = True
	    else:
	      x = x + 1
	  if done:
	    maxX = max(maxX, x)
	  else:
	    print "D =", D, "solution not found"
	print "Ans",maxX

result = 0
maxX = 0

def sol():
  global result
  global maxX
  for D in range(2,1001):
    lim = long(sqrt(D))
    if lim * lim == D:
      continue
    m = long(0) # 
    d = long(1) # denom integer
    a = lim

    num_m1 = long(1)
    num = long(a)

    den_m1 = long(0)
    den = long(1)

    while num * num - D * den * den != 1:
      m = d * a - m
      d = long((D - m * m) / d)
      a = long((lim + m) / d)
      
      num_m2 = num_m1
      num_m1 = num

      den_m2 = den_m1
      den_m1 = den

      num = a * num_m1 + num_m2
      den = a * den_m1 + den_m2

    if num > maxX:
      maxX = num
      result = D
  
    print "D =", D, "X =", num, "maxX =", maxX

sol()
print "Result D =", result, "maxX =", maxX

