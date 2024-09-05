import pandas as pd

df = pd.read_csv('data_fix.csv')

df['plan/fact_km_ratio'] = df['fact_km'].dropna() / df['plan_km']
df['speed'] = df['plan_km'] / df['plan_time']

df = df.groupby(by=['driver'])
res = pd.DataFrame({
    'Num distinct companions': df['user'].nunique(),
    'Num companions': df['user'].count(),
    'Km ratio avg': df['plan/fact_km_ratio'].mean(),
    'Km ratio std dev': df['plan/fact_km_ratio'].std(),
    'Plan speed avg': df['speed'].mean(),
    'Plan speed std dev': df['speed'].std(),
    'Plan speed max-min': df['speed'].max() - df['speed'].min(),
})

res.to_csv('data_fix_result.csv')

