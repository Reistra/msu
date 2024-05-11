from sklearn import datasets
from sklearn.linear_model import SGDClassifier
from sklearn.metrics import accuracy_score
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import GridSearchCV,  train_test_split
import matplotlib.pyplot as plt
import numpy as np

# Создаем выборку данных 
x, y = datasets.make_classification(n_samples=1000, n_features=20, n_classes=2, n_redundant=0)
# Делим данные на тренировочный и тестовый набор
# stratify - это параметр, который обеспечивает стратификацию разделения данных. Если этот параметр установлен в y, то разделение будет выполнено таким образом, чтобы распределение классов в обучающем и тестовом наборах было аналогичным распределению классов в исходном наборе данных y. Это полезно, если у вас есть дисбаланс классов в данных.
# random_state - это параметр, который управляет случайностью разделения данных. Установка random_state на определенное целое число гарантирует воспроизводимость разделения. Другими словами, если вы запустите код с одним и тем же random_state, то каждый раз будет получен один и тот же результат разделения данных.
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, stratify=y, random_state=42)


DEVIANCE = 'deviance'
EXPONENTIAL = 'exponential'
LOG_LOSS = 'log_loss'
HINGE = 'hinge'

    

# методы, поддерживающие различные функции потерь

gd1 = GradientBoostingClassifier(loss=LOG_LOSS) # log_loss эквивалентно deviance 
gd1.fit(x_train, y_train)
prediction_gd1 = gd1.predict(x_test)

gd1_accuracity = accuracy_score(y_test, prediction_gd1)
print(f"\033[92mModel: GradientBoostingClassifier, Loss_func: {LOG_LOSS}, Accuracity_score: {gd1_accuracity}\033[0m")


gd2 = GradientBoostingClassifier(loss=EXPONENTIAL)
gd2.fit(x_train, y_train)
prediction_gd2 = gd2.predict(x_test)

gd2_accuracity = accuracy_score(y_test, prediction_gd2)
print(f"\033[92mModel: GradientBoostingClassifier, Loss_func: {EXPONENTIAL}, Accuracity_score: {gd2_accuracity}\033[0m")

""""""

sgd1 = SGDClassifier(loss=HINGE)
sgd1.fit(x_train, y_train)
prediction_sgd1 = sgd1.predict(x_test)

sgd1_accuracity = accuracy_score(y_test, prediction_sgd1)
print(f"\033[92mModel: SGD, Loss_func: {HINGE}, Accuracity_score: {sgd1_accuracity}\033[0m")


sgd2 = SGDClassifier(loss=LOG_LOSS)
sgd2.fit(x_train, y_train)
prediction_sgd2 = sgd2.predict(x_test)

sgd2_accuracity = accuracy_score(y_test, prediction_sgd2)
print(f"\033[92mModel: SGD, Loss_func: {LOG_LOSS}, Accuracity_score: {sgd2_accuracity}\033[0m")


# методы, не поддерживающие различные функции потерь

rf = RandomForestClassifier()
rf_search_space = {
    "n_estimators" : [1, 100, 500], # количество деревьев в лесу
    "criterion" : ['gini', 'entropy'], # функции для измерения качества разделения
    "max_depth" : [None, 10], # макс. глубина дерева
    "min_samples_split" : [2, 8], # минимальное количество выборок, необходимое для разделения внутреннего узла
}

# estimator: используемый метод
# param_grid: сетка параметров метода
# scoring: метод оценки качества
# verbose: количество отладочной информации; verbose = 4 для показа всей дополнительной информации

gs_rf = GridSearchCV(estimator=rf, param_grid=rf_search_space, scoring="neg_log_loss", verbose=0)
gs_rf.fit(x_train, y_train)
prediction_rf = gs_rf.predict(x_test)

rf_accuracity = accuracy_score(y_test, prediction_rf)
print(f"\033[92mModel: RandomForest, Accuracity_score: {rf_accuracity}\033[0m")
print(f"\033[92mBest parametrs: {gs_rf.best_params_}\033[0m")


""""""

kn = KNeighborsClassifier()
kn_search_space = {
    "n_neighbors" : [5, 15, 100], # количество соседей
    "weights" : ['uniform', 'distance'], # весовые функции. uniform - одинаковые веса; distance - вес точек обратно пропорционален их расстоянию
    "algorithm" : ['auto', 'kd_tree'], # алгоритм, используемый для вычисления ближайших соседей
}

gs_kn = GridSearchCV(estimator=kn, param_grid=kn_search_space, scoring="neg_log_loss", verbose=0)
gs_kn.fit(x_train, y_train)
prediction_kn = gs_kn.predict(x_test)

kn_accuracity = accuracy_score(y_test, prediction_kn)
print(f"\033[92mModel: KNN, Accuracity_score: {kn_accuracity}\033[0m")
print(f"\033[92mBest parametrs: {gs_kn.best_params_}\033[0m")


# тестируемые объекты как точки на графике

fig, ax = plt.subplots(figsize=(4,3))
scatter = ax.scatter(x_test[:,0], x_test[:,1], c=y_test, edgecolors = "k")
ax.legend(*scatter.legend_elements(), title="Classes")
plt.show()


# точность каждого из методов на графике
# методы, поддерживающие различные функции потерь

x_axes = ["GDB, l = 'log_loss'", "GDB, l = 'exponential'", "SGD, l = 'hinge'", "SGD, l = 'log_loss'"]
y_axes = [gd1_accuracity, gd2_accuracity, sgd1_accuracity, sgd2_accuracity]

plt.figure(figsize=(10, 4))
plt.bar(x_axes, y_axes, width=0.4)
plt.ylim(0,1)
plt.ylabel("Точность")
for i, value in enumerate(y_axes):
    plt.text(i, value, str(value), ha='center')
plt.legend()
plt.show()

# методы, не поддерживающие различные функции потерь

x_axes = ["RandomForest", "KNN"]
y_axes = [rf_accuracity, kn_accuracity]

plt.bar(x_axes, y_axes, width=0.4)
plt.ylim(0,1)
plt.ylabel("Точность")
for i, value in enumerate(y_axes):
    plt.text(i, value, str(value), ha='center')
plt.legend()
plt.show()
