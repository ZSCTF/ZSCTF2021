
BALANCE = 0
CURRENT_BETS = dict([])

import random
import numpy as np

def menu(first):
    global BALANCE


    if BALANCE < 0:
        print('这位ctfer，因为你欠我们钱，跟我们走一趟吧！')
        exit(0)

    if first:
        print('Welcome to the ZSCTFFFFFF CASINO.\n开始你将获得100CTF币\n 听说有钱就可以买到flag了 ~~\n')
        BALANCE += 100

    print('\n1 : 下注')
    print('2 : 查看余额')
    print('3 : 查看当前投注')
    print('4 : 开始转盘 (BOOSTED x72 !) [事先声明我们非常非常公平，完全没有操纵]')
    print('5 : 商店')
    print('6 : 充钱')
    print('7 : 退出')

    while True:
        try:
            choice = int(input('>>> '))
            if choice < 0 or choice > 7:
                raise ValueError
        except ValueError:
            taunts = ['不你不能!', '啊这!', 'emmmmmmmm', 'WTF ?', '就这 ?']
            print(random.choice(taunts))
            menu(False)
        else:
            if choice == 1:
                bet()
            elif choice == 2:
                balance()
            elif choice == 3:
                see_bets()
            elif choice == 4:
                roulette()
            elif choice == 5:
                shop()
            elif choice == 6:
                print('啊这 !')
                print(' ')
            elif choice == 7:
                print('bye~')
                exit(0)
            #### DBG !!!!
            #elif choice == 8:
            #    for i in range(37):
            #        CURRENT_BETS[i] = 200
            menu(False)


def balance():
    global BALANCE
    print('\n你当前的余额： {} !'.format(BALANCE))

def shop():
    global BALANCE

    print('\n Welcome to the shop ! ')
    print('1 : 变成海豹 (100CTF币)\n')
    print('2 : really flag (3CTF币)')
    print('3 : fake flag (3600CTF币)')

    while True:
        try:
            choice = int(input('>>> '))
            if choice < 0 or choice > 3:
                raise ValueError
        except ValueError:
            taunts = ['不你不能!', '啊这!', 'emmmmmmmm', 'WTF ?', '就这 ?']
            print(random.choice(taunts))
            menu(False)
        else:
            if choice == 1:
                if BALANCE < 100:
                    print('ctfer你的余额不足！.')
                    return
                BALANCE -= 100
                print('你已经成功变成海豹了！')

            elif choice == 2:
                if BALANCE < 3:
                    print('ctfer你的余额不足！')
                    return
                BALANCE -= 3
                print('你被骗了~')
            elif choice == 3:
                if BALANCE < 3600:
                    print('ctfer你的余额不足！')
                    return
                BALANCE -= 3600
                print('收好你的flag ~ zsctf{xx-xxxx-xx}')
        return

def see_bets():
    global CURRENT_BETS

    if not CURRENT_BETS:
        print('你还没有下注！')
        return

    print('\n#### 当前投注 ####\n')
    for keys, values in CURRENT_BETS.items():
        print('你有一个 {}CTF币 的投注在 #{}, 你可以赢得 {}CTF币'.format(values, keys, values*72))

    print('\n######################')

def bet():
    
    global CURRENT_BETS
    global BALANCE

    message = '\nctfer你想投注哪个号码(0-36)\n>>> '
    while True:
        try:
            bet = int(input(message))
            if bet < 0 or bet > 36:
                raise ValueError
        except ValueError:
            taunts = ['不你不能!', '啊这!', 'emmmmmmmm', 'WTF ?', '就这 ?']
            print(random.choice(taunts))
            continue
        else:
            break

    message = '你想要投注多少钱 (max : {}CTF币)\n>>> '.format(BALANCE)
    while True:
        try:
            amount = int(input(message))
            if amount < 0 or amount > BALANCE:
                raise ValueError
        except ValueError:
            taunts = ['不你不能!', '啊这!', 'emmmmmmmm', 'WTF ?', '就这 ?']
            print(random.choice(taunts))
            continue
        else:
            break
    
    CURRENT_BETS[bet] = amount
    print('emmm, 你成功投注了 {}CTF币 到 #{} . 你将可能赢得 {}CTF币'.format(amount, bet, amount*72))

def roulette():
    global BALANCE
    global CURRENT_BETS

    results = range(37)


    bets_list = CURRENT_BETS.keys()

    if not bets_list:
        print('你还没有下注，请先下注！')
        return

    if list(sorted(bets_list)) != list(results):
        possibilities = np.setdiff1d(results, bets_list)
        result = random.choice(possibilities)
        for keys, values in CURRENT_BETS.items():
            print('真是可惜, 你投注的号码是 {}  但是开出的号码是{}. 你输了 {}CTF币 . '.format(keys, result, values))
            BALANCE -= values
    else:
        result = random.choice(results)
        for keys, values in CURRENT_BETS.items():
            print("k,v :", keys, values)
            if keys == result:
                print('你竟然赢了\n恭喜这个ctfer')
                print('你赢得了{}CTF币. 请好好使用 !'.format(values * 72))
                BALANCE += values * 72
            else:
                print('真是可惜, 你投注的号码是 {}  但是开出的号码是{}. 你输了 {}CTF币'.format(keys, result, values))
                BALANCE -= values

    print('当前余额 : {}CTF币'.format(BALANCE))
        
menu(True)
