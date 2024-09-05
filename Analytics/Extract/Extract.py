import pandas as pd


def melt_tours(df, n):
    df1 = df[['username'] + ['1_' + str(i) for i in range(1, n + 1)]].copy()
    df1.columns = ['username'] + ['task' + str(i) for i in range(1, n + 1)]
    df1['tour'] = '1'
    df1['score'] = 0
    for i in range(1, n + 1):
        df1['score'] += df1['task' + str(i)].fillna(0)

    df2 = df[['username'] + ['2_' + str(i) for i in range(1, n + 1)]].copy()
    df2.columns = ['username'] + ['task' + str(i) for i in range(1, n + 1)]
    df2['tour'] = '2'
    df2['score'] = 0
    for i in range(1, n + 1):
        df2['score'] += df2['task' + str(i)].fillna(0)

    result = pd.concat([df1, df2], ignore_index=True)

    return result

def convert_numeric_to_integers(df, n):
    d = {'score': 'Int32'}
    for i in range(1, n + 1):
        d['task' + str(i)] = 'Int32'
    return df.astype(d)

def rename_task_columns(df, n, tour):
    d = {}
    for i in range(1, n + 1):
        d['task' + str(i)] = tour + '_' + str(i)
    return df.rename(columns=d)
    

n = 4
df = pd.read_csv('test_00_00.csv')

melted_df = melt_tours(df, n)
melted_df['region'] = melted_df['username'].str[5:7]

grouped_df = melted_df.groupby(['region', 'tour']).apply(
    lambda x: None if len(x) < 10 else x.sort_values(by=['score', 'username'], ascending=[False, True]).iloc[9]['score']
)

target_region, target_tour = grouped_df.idxmax()

columns = ['username'] + ['task' + str(i) for i in range(1 ,n + 1)] + ['score']
result = melted_df[(melted_df['region'] == target_region) & (melted_df['tour'] == target_tour)] \
    .sort_values(by=['score', 'username'], ascending=[False, True])[columns]

result = convert_numeric_to_integers(result, n)
result = rename_task_columns(result, n, target_tour)

result.to_csv('result.csv', index=False)