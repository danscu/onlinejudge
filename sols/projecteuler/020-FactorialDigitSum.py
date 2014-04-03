import math

s = str(math.factorial(100))

sum = 0
for ch in s:
  sum = sum + int(ch) - int('0')

print sum

