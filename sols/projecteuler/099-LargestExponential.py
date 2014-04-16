import math

def largestExp(fname):
  line = 0
  mx = 0
  mxline = 0
  with open(fname) as f:
    content = f.readlines()
  for c in content:
    [strBase,strExp] = c.split(',')
    base = int(strBase)
    exp = int(strExp)
    line = line + 1
    if math.log(base) * exp > mx:
      mx = math.log(base) * exp
      mxline = line
      print "mx=",mx,"base=",base,"exp=",exp
  return mxline

if __name__ == '__main__':
  print largestExp('099-LargestExp.txt')

