import calendar
from datetime import datetime, timedelta
import csv

maxDate = datetime(1970, 1, 1)
byUserId = {}
byJoinMonth = {}


class Record:
    def __init__(self, date, pay):
        self.date = date
        self.pay = pay


with open('startup_users_visits.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        userId, date, pay = row[0], datetime.strptime(row[1], '%Y-%m-%d'), bool(row[2] == 'True')
        maxDate = max(maxDate, date)
        if userId not in byUserId:
            byUserId[userId] = []
        byUserId[userId].append(Record(date, pay))

for userId, logs in byUserId.items():
    join = min(logs, key=lambda log: log.date).date
    pays = list(filter(lambda log: log.pay is True, logs))
    if not pays:
        continue
    firstPay = min(pays, key=lambda log: log.date).date
    if firstPay - join >= timedelta(days=90):
        continue

    joinMonthBounds = calendar.monthrange(join.year, join.month)
    joinMonthFirstDay = datetime(join.year, join.month, 1)
    joinMonthLastDay = datetime(join.year, join.month, joinMonthBounds[1])
    if maxDate - joinMonthLastDay < timedelta(days=90):
        continue
    if joinMonthFirstDay not in byJoinMonth:
        byJoinMonth[joinMonthFirstDay] = 0
    byJoinMonth[joinMonthFirstDay] += 1

with open('out.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)

    for dt, value in sorted(byJoinMonth.items(), key=lambda x: x[0]):
        writer.writerow([dt.strftime('%Y-%m-%d'), value])
