# 我还以为要用回溯，还是python语法不熟
for x in range(1,5):
    for y in range(1,5):
        for z in range(1,5):
                if (x!=y) and (y!=z) and (z!=x):
                        print("%d%d%d" % (x, y, z)) 
