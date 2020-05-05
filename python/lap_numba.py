import time
import numpy as np
from numba import njit

r=500
c=500

a=np.zeros((r,c))

# for x in range(c):
#     for y in range(r):
#         a[y][x]=1;
    
for x in range(c):
    a[0][x]=x/(c-1)*x/(c-1)
    a[r-1][x]=x/(c-1)*x/(c-1)-1

for y in range(r):
    a[y][0]=-y/(r-1)*y/(r-1);
    a[y][r-1]=1-y/(r-1)*y/(r-1);
    
b=np.zeros((r,c))

for y in range(r):
    for x in range(c):
        b[y][x]=a[y][x];
        
sum1=0
sum2=0
counter=10000
#temp=np.zeros((r,c))

#start=time.perf_counter()

@njit
def runloop(counter,a,b):
    while counter>0:
        #sum1=sum2
        #sum2=0
        temp=a
        a=b
        b=temp
        
        for y in range(1,r-1):
            #print("\n")
            for x in range(1,c-1):
                b[y][x]=0.25*(a[y-1][x] + a[y][x-1] + a[y][x+1] + a[y+1][x])
                #sum2=sum2+(b[y][x] * b[y][x])
                
        counter-=1 



start=time.perf_counter()
runloop(counter,a,b)
stop=time.perf_counter() 


for y in range(1,r-1):
    for x in range(1,c-1):
        sum2=sum2+(b[y][x] * b[y][x])
        sum1=sum1+(a[y][x] * a[y][x])

  
# for y in range(r):
#     print()
#     for x in range(c):
#         print(b[y][x], end=' ')
        
        
print(sum1,sum2,sum1-sum2)
print(stop-start)
