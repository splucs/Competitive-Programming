'''
author: @vinuthegr8
'''

import sys
import math
input = sys.stdin.readline
 
n=int(input())
arr=[]
status=[]
 
for i in range(n):
	arr.append(list(map(int,input().split())))
	if arr[-1][0]>arr[-1][1]:
		status.append(2)
	elif arr[-1][0]==arr[-1][1]:
		status.append(1)
	else:
		status.append(0)
 
w=0
for i in range(n):
	if status[i]==2:
		w+=1
d=n-(w*2-1)
diff=d
 
if diff<=0:
	print(0)
	exit(0)
 
ans=[]
 
flag=True
for i in range(n-1):
	if flag:
		if (status[i]==2 and status[i+1]==0) or (status[i]==0 and status[i+1]==2):
			if arr[i][0]+arr[i+1][0]>arr[i][1]+arr[i+1][1]:
				ans.append([i+1,i+2])
				flag=False
				diff-=1
		elif status[i]+status[i+1]<4:
			ans.append([i+1,i+2])
			flag=False
			diff-=1
	else:
		flag=True
 
	if diff==0:
		break
 
if diff>0:
	print(-1)
else:
	print(d)
	for i in range(len(ans)):
		print(*ans[i])
