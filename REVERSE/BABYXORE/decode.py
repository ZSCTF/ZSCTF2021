myinput = 0x89fd639dc9cba711 

    # 获得二进制start-end范围的值
def getPlace(start,end,input):
    all = -1
    result = input >>start

    l = end-start

    all <<= l
        
    result = result & (~all) 

    return result

#d == 0 right
#d == 1 left

def decode(d,sh,input):
    result_num = 0
    result = []
    if d == 0:
        curent = 64
        pre = getPlace(curent-sh,curent,input)
        result.append(pre)
        while  1:
            curent -= sh
            if curent <sh:
                tmp = getPlace(0,curent,input)
                pre =getPlace(sh-curent,sh,pre)

                result.append(tmp ^ pre)
                break
            
            tmp=getPlace(curent-sh,curent,input)
            
        
            pre = pre ^tmp
            result.append(pre)    

        for i in range(len(result)):

            shift = 64-(i+1)*sh
            if shift>0:
                result_num +=result[i] << shift
            else:
                result_num += result[i]
    else:
        curent = 0
        pre = getPlace(curent,curent+sh,input)
        result.append(pre)
        while 1:
            curent +=sh
            if curent >64:
                tmp = getPlace(curent-sh,64,input)
                pre = getPlace(0,64-(curent-sh),pre)
                result.append(tmp^pre)
                break
            
            if curent+sh > 64:
                continue
            tmp = getPlace(curent,curent+sh,input)

            pre = pre^tmp
            result.append(pre)
        for i in range(len(result)):
            shift = (i)*sh
            
            result_num +=result[i]<<shift

        
    return result_num




result = decode(0,13,myinput)
print(hex(result))

result = decode(1,31,result)

print(hex(result))

result = decode(0,11,result)

print(hex(result))

result = decode(1,7,result)



print(hex(result))