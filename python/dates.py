from datetime import date, datetime
now = date.today()
print(now.strftime("%y-%m-%d. %d %b %Y is a %A on the %d day of %B."))

birthday = date(1964,7,31)
age=now-birthday
print(age)
print(age.days)

unix_birthday=datetime.strptime("1970-01-01","%Y-%m-%d")
print(unix_birthday)
unix_birthday=datetime.strptime("70-01-01","%y-%m-%d")
print(unix_birthday)