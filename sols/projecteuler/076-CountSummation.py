N = 100

S = [[0 for x in xrange(N+1)] for x in xrange(N+1)]

for i in range(1,N+1):
  S[i][i] = 1

# Can be simplified to two loops
for n in range(2, N+1):
  for m in range(1,n+1):
    for k in range(1,m+1):
      S[n][m] += S[n - k][k] if k < n-k else S[n-k][n-k]
      print "S[", n, ",", m, "] += S[", n-k, ",", k, "] = ", S[n][m]

print S[N][N-1]


