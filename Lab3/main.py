import time

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

mean1, std1 = 2, 3
mean2, std2 = 7, 2
prior1 = 0.6
prior2 = 0.4

sample_size = 10000
np.random.seed(int(time.time()) % 2 ** 32)
sample1 = np.random.normal(mean1, std1, sample_size)
sample2 = np.random.normal(mean2, std2, sample_size)

threshold = (mean1 + mean2) / 2
# Сколько объектов из класса 2 (sample2) ошибочно попали в класс 1
false_positives = np.sum(sample2 < threshold) / sample_size
# Сколько объектов из класса 1 (sample1) ошибочно попали в класс 2
false_negatives = np.sum(sample1 > threshold) / sample_size
total_error = prior1 * false_negatives + prior2 * false_positives

print(f"Эмпирическая вероятность ложной тревоги: {false_positives:.4f}")
print(f"Эмпирическая вероятность пропуска обнаружения: {false_negatives:.4f}")
print(f"Эмпирическая суммарная ошибка: {total_error:.4f}")

# Интегральный расчет ошибок
false_positives_cdf = norm.cdf(threshold, mean2, std2)
false_negatives_cdf = 1 - norm.cdf(threshold, mean1, std1)
total_error_cdf = prior1 * false_negatives_cdf + prior2 * false_positives_cdf

print("")
print(f"Аналитическая вероятность ложной тревоги : {false_positives_cdf:.4f}")
print(f"Аналитическая вероятность пропуска обнаружения : {false_negatives_cdf:.4f}")
print(f"Аналитическая суммарная ошибка : {total_error_cdf:.4f}")

x = np.linspace(min(sample1.min(), sample2.min()), max(sample1.max(), sample2.max()), 100)
plt.plot(x, norm.pdf(x, mean1, std1), label='Класс 1')
plt.plot(x, norm.pdf(x, mean2, std2), label='Класс 2')
plt.axvline(threshold, color='red', linestyle='dashed', linewidth=1, label='Порог')
plt.xlabel('Значение')
plt.ylabel('Плотность вероятности')
plt.title('Распределение и классификация')
plt.legend()
plt.show()
