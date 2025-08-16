year = int(input("输入一个年份: "))
if (((year % 4 == 0) & (year % 100 != 0)) | (year % 400 == 0)):#注意括号
    print("是闰年")
else:
    print("不是闰年")