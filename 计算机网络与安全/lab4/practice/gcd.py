a = int(input("输入第一个数: "))
b = int(input("输入第二个数: "))
c = max(a,b)
d = min(a,b)
while (d != 0):
    temp = d
    d = c % d
    c = temp
print(c)
