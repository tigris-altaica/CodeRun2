import pandas as pd
import xml.etree.ElementTree as ET

def read_xml(filename):
    root = ET.fromstring(open(filename).read())

    # Список для хранения строк DataFrame
    data = []

    # Извлечение данных
    for row in root.findall('Row'):
        row_data = {}
        for column in row.findall('Column'):
            # Получаем имя колонки и ее значение
            col_name = column.get('name')
            col_value = column.text
            row_data[col_name] = col_value
        data.append(row_data)

    return pd.DataFrame(data)

# Создание DataFrame
df = read_xml('test_data.xml')

df['1_4'] = None
df['score'] = df['score'].astype('Int32')
df = df[['username'] + sorted([col for col in df.columns if col != 'score' and col != 'username']) + ['score']]

df.sort_values(by=['score', 'username'], ascending=[False, True], inplace=True)

df.to_csv('result.csv', index=False)