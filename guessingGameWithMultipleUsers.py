# Online Python - IDE, Editor, Compiler, Interpreter
import random
import re

def compareGuesses(a):
    rv = random.randint(1, 9)
    lowest = []
    diff = []
    for x in a:
        diff.append(abs(int(x[1])-rv))
    for idx, x in enumerate(diff):
        if (x == min(diff)):
            lowest.append(a[idx])
    print(lowest)
    if(len(lowest) > 1):
        names = []
        values = []
        for x in lowest:
            names.append(x[0])
            if (x[1] not in values):
                values.append(x[1])
        print(f'The closest were {", ".join(names)} with value/s {", ".join(values)}. The right value was {rv}')
    else:
        print(f'The closest was {lowest[0][0]} with value {lowest[0][1]}. The righ value was {rv}')

def formatList(a):
    data = []
    for x in a:
        splitArr = x.split(", ")
        if (splitArr):
            for y in splitArr:
                data.append(y.split(": "))
        else:
            data.append(x.split(": "))
    return data
    
r = re.compile('.*: [0-9]')
guesses = []
while (1):
    guess = input("Enter a name/s and a guess/' from 1-9 in a form of 'name: number' or 'name: number, ...'. Press q to stop adding")
    if ("q" == guess.lower()):
        break;
    if (r.match(guess)):
        guesses.append(guess)
    else:
        print("Please give the right format. Example ' josh: 2 '")
if (guesses):
    allData = formatList(guesses)
    compareGuesses(allData)
    #A: 3, B: 3, C: 3

    