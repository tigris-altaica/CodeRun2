import pandas as pd

def Q1(df):
    df['time'] = pd.to_datetime(df['time'])
    current_queue_length = 0.0
    for idx in range(len(df)):
        current_queue_length += df.at[idx, 'average_people']
        current_queue_length = max(0.0, current_queue_length - 8)
        df.at[idx, 'queue_length'] = current_queue_length
    return df.loc[df['queue_length'].idxmax()]['time']

def Q2(df):
    df['diff_in_15_mins'] = None
    for idx in range(len(df)):
        target_time = df['time'][idx] - pd.Timedelta(minutes=15)
        idx_15_mins_back = df['time'].sub(target_time).abs().idxmin()
        df.loc[idx_15_mins_back, 'diff_in_15_mins'] = df['queue_length'][idx] - df.loc[idx_15_mins_back, 'queue_length']
    return df.loc[df['diff_in_15_mins'].idxmax()]['time']



df = pd.read_csv('people_by_minute.csv')

print('Q1:', Q1(df))
print('Q2:', Q2(df))

df.to_csv('people_by_minute_result.csv', index=False)