import sys
import math
input = sys.stdin.readline
 
n,k=map(int,input().split())
arr=list(map(int,input().split()))
 
cur=sum(arr[:k])
lo=min(arr)
total=0
for i in range(n-k+1):
	if i>0:
		cur=cur-arr[i-1]+arr[i+k-1]
	#print(cur)
	if cur>=0:
		for j in range(i+k-1,i-1,-1):
			d=arr[j]-lo
			total+=min(d,cur+1)
			arr[j]-=min(d,cur+1)
			cur-=min(d,cur+1)
			
			if cur<0:
				break
print(total)
print(*arr)
