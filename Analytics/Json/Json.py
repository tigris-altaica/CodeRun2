import pandas as pd

df = pd.read_json('test_data.json')

df['actual_score'] = df.filter(like='_').sum(1)

df = df[df['score'] != df['actual_score']]['username'].sort_values()

df.to_csv('result.csv', index=False, header=False)