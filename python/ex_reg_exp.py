import re
from collections import Counter
from fichiers import Fichiers
cnt = Counter()
for word in ['red', 'blue', 'red', 'green', 'blue', 'blue']:
    cnt[word] += 1

print(cnt)#Counter({'blue':3,'red':2,'green':1})

words=re.findall(r'\w+', Fichiers.lire("mots.txt").lower())
print(Counter(words).most_common(1))
print(Counter(words).most_common(2))
print(Counter(words).most_common(3))
print(Counter(words))
print(Fichiers.lire("mots.txt").split(" "))
print(";".join(Fichiers.lire("mots.txt").split(" ")))

import re
chaine = ""
expression = r"^0[0-9]([ .-]?[0-9]{2}){4}$"
print(re.search(expression, ""))
print(re.search(expression, "01-23-45-67-89"))
print(re.search(expression, "01-23-45-6789"))
print(re.search(expression, "01-23-45-678"))
print(re.search(expression, "01-23-45-67890"))
