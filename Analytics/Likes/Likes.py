import csv
import ast


def slash_sep(art):
    return art[2:].split('/')


def parse_tsv(filename):
    csv.field_size_limit(2 ** 20)

    likes = dict()

    reader = csv.reader(open(filename, 'r', encoding='utf-8'), delimiter='\t')
    header = next(reader)  # Получаем заголовок

    for row in reader:
        record = dict(zip(header, row))

        if record['event'] != 'like':
            continue

        user = record['user']
        arts = ast.literal_eval(record['context'])

        for slash_art in arts:
            art = slash_sep(slash_art)[-1]
            if art not in likes:
                likes[art] = set()
            likes[art].add(user)

    return likes


logs_filename = 'logs.tsv'

nums_likes = [len(users_liked) for users_liked in parse_tsv(logs_filename).values()]

nums_likes.sort(reverse=True)

print(nums_likes[:3])
