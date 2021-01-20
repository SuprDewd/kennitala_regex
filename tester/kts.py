import re
import os
import string
import sys
from kennitala import *
from urllib.request import urlretrieve

def is_valid(kt):
    if int(kt[6:8]) < 20:
        # The two-digit random number is issued starting from 20. The kennitala
        # package assumes it can start from 0.
        return False
    return Kennitala.is_valid(kt) and Kennitala.is_personal(kt)

with open('../regex.txt', 'r') as f:
    print('Les regex...')
    rx = f.read().strip()

print('Þýði regex...')
rx = re.compile('^(%s)$' % rx)

def check(kt):
    val = is_valid(kt)
    a = rx.match(kt) is not None
    print(kt, val, a)
    assert val == a

for i in range(100):
    check(Kennitala.random())

for i in range(100):
    kt = Kennitala.random()

    # Apply some mutations
    ch = random.randint(0, 5)
    for j in range(ch):
        k = random.randint(0, len(kt)-1)
        kt = kt[:k] + str(random.randint(0,9)) + kt[k+1:]

    check(kt)

for i in range(100):
    check(''.join( random.choice(string.digits) for _ in range(10) ))

while True:
    sys.stdout.write('Kennitala: ')
    sys.stdout.flush()
    check(sys.stdin.readline().strip())

