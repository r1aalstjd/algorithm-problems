import random

#------------------------------------------------------------------------------------

#테스트케이스 번호
#입력 파일은 Python 현재 경로에 {번호}.in, 출력 파일은 {번호}.out의 형태로 만들어짐
tc_num = 16

f = open('./' + str(tc_num) + '.in', 'w')
f2 = open('./' + str(tc_num) + '.out', 'w')

#debug == 1이면 입력 파일에 디버그 정보 추가
debug = 0

#s는 입력 파일 생성에 사용되는 문자열로, 지정하지 않을 경우 조건에 맞추어 랜덤으로 생성
s = ''

#n은 문자열의 길이로, 지정하지 않을 경우 조건에 맞추어 랜덤으로 생성
n = 100000

#q는 쿼리의 개수로, 지정하지 않을 경우 조건에 맞추어 랜덤으로 생성
q = 100000

#------------------------------------------------------------------------------------

ans = []
output = []
output1 = []
output2 = []

"""
1 2 3 4 5 6 7 8
0 1 2 3 4 5 6 7
4 8 2
1 19 20 1
+-->+>-+>>>>++++>-+>
"""

def validate(l, r):
    s1 = s[l-1:r]
    t = [0]
    for i in s1:
        if(i == '+'): t[len(t)-1] += 1
        elif(i == '-'): t[len(t)-1] -= 1
        elif(i == '>'): t.append(0)
    mx = -1987654321
    for i in t:
        mx = max(mx, i)
    return mx

def shift(l, r, k):
    global s
    if(k > 0):
        s1 = s[l-1:r]
        s2 = s1[0:r-l+1-k]
        s3 = s1[r-l-k+1:]
        s4 = s[:l-1]
        s5 = s[r:]
        #if(debug): print(s4, s1, s2, s3, s5)
        s = s4 + s3 + s2 + s5
    else:
        k = -k
        s1 = s[l-1:r]
        s2 = s1[0:k]
        s3 = s1[k:]
        s4 = s[:l-1]
        s5 = s[r:]
        s = s4 + s3 + s2 + s5

ch = ['+', '-', '>']
if(n < 2): n = random.randint(2, 300000)
if(q < 1): q = random.randint(1, 100000)
if(len(s) < 1):
    s = ''
    for i in range(n):
        s += ch[random.randint(0, len(ch)-1)]

if(len(s) != n):
    n = len(s)

f.write(str(n) + '\n')
f.write(str(s) + '\n')
f.write(str(q) + '\n')
for i in range(q):
    a = random.randint(1, 2)
    b = random.randint(1, n-1)
    c = random.randint(b+1, n)
    if(a == 1):
        d = random.randint(1, c-b)
        e = random.randint(0, 1)
        if(e == 1): d = -d
        shift(b, c, d)
        if(debug):
            output.append('{:>7} {:>7} {:>7} {:>7} '.format(a, b, c, d) + s + '\n')
            output1.append('{:>7} {:>7} {:>7} {:>7} '.format(a, b, c, d) + s + '\n')
        f.write('{} {} {} {}\n'.format(a, b, c, d))
    elif(a == 2):
        #b = 1
        #c = n
        f.write('{} {} {}\n'.format(a, b, c))
        t = validate(b, c)
        ans.append(t)
        if(debug):
            output.append('{:>7} {:>7} {:>7} {:>7} '.format(a, b, c, t) + s[b-1:c] + '\n')
            output2.append('{:>7} {:>7} {:>7} {:>7} '.format(a, b, c, t) + s[b-1:c] + '\n')


if(debug):
    f.write('\n\n')
    for i in output:
        f.write(i)
    f.write('\n\n')
    for i in output1:
        f.write(i)
    f.write('\n\n')
    for i in output2:
        f.write(i)
    f.write('\n\n')
    f.write(str(len(output2)))
    f.write('\n')

for i in range(len(ans)):
    if(debug): f.write(str(ans[i]) + '\n')
    f2.write(str(ans[i]) + '\n')


f.close()
f2.close()