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
