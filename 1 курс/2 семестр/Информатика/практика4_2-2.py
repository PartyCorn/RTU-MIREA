import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv('sales_15.csv')

fig, axes = plt.subplots(1, 2, figsize=(12, 5))  # 2 графика

# Гистограмма цен
df['Цена'].hist(ax=axes[0], bins=10, color='skyblue', edgecolor='black')
axes[0].set_title('Распределение цен')
axes[0].set_xlabel('Цена')
axes[0].set_ylabel('Частота')
axes[0].grid(False)

# Гистограмма объёмов продаж
df['Количество'].hist(ax=axes[1], bins=10, color='salmon', edgecolor='black')
axes[1].set_title('Распределение объёмов продаж')
axes[1].set_xlabel('Количество')
axes[1].set_ylabel('Частота')
axes[1].grid(False)

plt.tight_layout()
plt.show()
