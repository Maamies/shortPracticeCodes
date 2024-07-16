import re

file = 'test.txt'
print("new run")

with open(file, 'r', encoding='utf-8') as text:
    data = text.read().rstrip()
print(type(data))

x = re.findall('[0-9]+', data)

def filterNumber(n):
    if(len(n)==4):
        return True
    else:
        return False
        
# Filter the list
finalx = list(filter(filterNumber, x))
print('Final List\n',finalx)
