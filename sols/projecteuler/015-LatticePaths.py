def mul(x,y):
    return x * y

n = 20

top = reduce(mul, range(n+1,2*n+1))
bottom = reduce(mul, range(1,n+1))

print top / bottom
