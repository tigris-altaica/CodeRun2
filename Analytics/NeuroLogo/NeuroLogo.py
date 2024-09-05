import pandas as pd
from collections import defaultdict


def by_total_score(df):
    results = defaultdict(int)
    for index, row in df.iterrows():
        results[row['p1']] += row['p1_votes']
        results[row['p2']] += row['p2_votes']
    print(sorted(((k, v) for k, v in results.items()), reverse=True, key=lambda x: x[1]))

def by_win_score_diff(df):
    results = defaultdict(int)
    for index, row in df.iterrows():
        if row['p1_votes'] > row['p2_votes']:
            results[row['p1']] += abs(row['p1_votes'] - row['p2_votes'])
        else:
            results[row['p2']] += abs(row['p1_votes'] - row['p2_votes'])
    print(sorted(((k, v) for k, v in results.items()), reverse=True, key=lambda x: x[1]))

def by_total_score_diff(df):
    results = defaultdict(int)
    for index, row in df.iterrows():
        results[row['p1']] += row['p1_votes'] - row['p2_votes']
        results[row['p2']] += row['p2_votes'] - row['p1_votes']
    print(sorted(((k, v) for k, v in results.items()), reverse=True, key=lambda x: x[1]))

def by_number_of_wins(df):
    results = defaultdict(int)
    for index, row in df.iterrows():
        greater = row['p1_votes'] > row['p2_votes']
        results[row['p1']] += greater
        results[row['p2']] += not greater
    print(sorted(((k, v) for k, v in results.items()), reverse=True, key=lambda x: x[1]))

def by_number_of_wins_and_total_score_diff(df):
    class Result:
        def __init__(self):
            self.num_wins = 0
            self.total_score_diff = 0
        def __repr__(self):
            return "{}, {}".format(self.num_wins, self.total_score_diff)

    results = defaultdict(Result)
    for index, row in df.iterrows():
        greater = row['p1_votes'] > row['p2_votes']
        results[row['p1']].num_wins += greater
        results[row['p2']].num_wins += not greater
        results[row['p1']].total_score_diff += row['p1_votes'] - row['p2_votes']
        results[row['p2']].total_score_diff += row['p2_votes'] - row['p1_votes']
    print(sorted(((k, v) for k, v in results.items()), reverse=True, key=lambda x: (x[1].num_wins, x[1].total_score_diff)))



df = pd.read_csv('dataset.tsv', sep='\t')


by_total_score(df)
by_win_score_diff(df)
by_total_score_diff(df)
by_number_of_wins(df)
by_number_of_wins_and_total_score_diff(df)
