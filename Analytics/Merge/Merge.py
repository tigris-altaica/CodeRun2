import pandas as pd

mode, num_tours, num_tasks_in_tour, num_regions = 'test', 2, 4, 8 #'train', 2, 2, 3

df = pd.DataFrame()

for region in range(1, num_regions + 1):
    region_df = pd.DataFrame({'username': [], 'score': []})
    for tour in range(1, num_tours + 1):
        region_tour_df = pd.read_csv('{}/{}_{:02d}_{:02d}.csv'.format(mode, mode, region, tour))
        if region_tour_df.empty:
            continue
        region_df = region_df.merge(region_tour_df, how='outer', on='username', suffixes=('_prev', None))
        region_df['score'] += region_df['score_prev'].fillna(0)
        region_df.drop(columns=['score_prev'], inplace=True)
    df = pd.concat([df, region_df])

numeric_cols = df.select_dtypes(include='number').columns
df[numeric_cols] = df[numeric_cols].astype('Int32')

df.sort_values(by=['score', 'username'], ascending=[False, True]).to_csv('{}_results.csv'.format(mode), index=False)
