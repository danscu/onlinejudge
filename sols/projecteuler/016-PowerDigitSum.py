num = long(1)
for r in range(0,1000):
  num = num * 2
snum = str(num)

digsum = 0
for c in snum:
  digsum = digsum + int(c)

print digsum
