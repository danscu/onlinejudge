matrix = []

#fname = "086-test.txt"
fname = "086-PathSumTwoWays.txt"

with open(fname, "r") as f:
    for line in f:
	row = map(int,line.split(","))
        matrix.append(row)

nRow = len(matrix)
nCol = len(matrix[0])

print "nRow=", nRow, "nCol=", nCol

dp = [[0 for x in xrange(nCol+1)] for x in xrange(nRow+1)]

INF = 1000000

for i in range(1,nRow+1):
  dp[i][0] = INF

for j in range(1,nCol+1):
  dp[0][j] = INF

dp[1][0] = 0

for i in range(1,nRow+1):
  for j in range(1,nCol+1):
    dp[i][j] = matrix[i-1][j-1] + min(dp[i-1][j], dp[i][j-1])

print dp[nRow][nCol]

