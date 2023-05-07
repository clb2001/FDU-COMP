for i in range(1,9):
    for j in range(0,9):
        for k in range(0,9):
            if (100*i+10*j+k == i*i*i + j*j*j + k*k*k):
                print(100*i+10*j+k)