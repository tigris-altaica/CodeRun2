import pandas as pd

num_tours = 3
num_tasks_in_tour = 4

df = pd.read_csv('test_00_00.csv')
df.fillna(0, inplace=True)
df.drop('score', axis=1, inplace=True)

numeric_cols = df.select_dtypes(include='number').columns
df[numeric_cols] = df[numeric_cols].astype('Int32')

for tour in range(1, num_tours + 1):
    tasks = [str(tour) + '_' + str(task) for task in range(1, num_tasks_in_tour + 1)]
    df['score_' + str(tour)] = df[tasks].max(axis=1)

df['score'] = sum([df['score_' + str(tour)] for tour in range(1, num_tours + 1)])
df.sort_values(by=['score', 'username'], ascending=[False, True], inplace=True)

df.to_csv('result.csv', index=False)