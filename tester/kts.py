import re
import os
import string
import sys
from kennitala import *
from urllib.request import urlretrieve

path = 'kennitala.txt'
if not os.path.isfile(path):
    print('Næ í regex...')
    urlretrieve('https://x.algo.is/eats', path)
with open(path, 'r') as f:
    print('Les regex...')
    rx = f.read().strip()

print('Þýði regex...')
rx = re.compile('^(%s)$' % rx)

def check(kt):
    a = rx.match(kt) is not None
    b = Kennitala.is_valid(kt) and Kennitala.is_personal(kt)
    print(kt, a, b)
    assert a == b

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

