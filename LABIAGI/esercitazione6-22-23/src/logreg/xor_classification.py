from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
from .xor_dataset import XORDataset
import numpy as np
import matplotlib.pyplot as plt
import plotly.graph_objects as go


# Create dataset
dataset = XORDataset()

# Plot dataset: the data is created in a way that it is linearly separable, but only in a higher dimension
dataset.plot_data()

# Split dataset into train and test
train_size = int(0.8 * dataset.sample_size)
train_x = dataset.x[:train_size, :]
train_y = dataset.y[:train_size, :]
test_x = dataset.x[train_size:, :]
test_y = dataset.y[train_size:, :]
print('train_x.shape =', train_x.shape)
print('train_y.shape =', train_y.shape)
print('test_x.shape =', test_x.shape)
print('test_y.shape =', test_y.shape)

# Train logistic regression model
model = LogisticRegression()
model.fit(train_x, train_y.ravel())

# Predict on test set
pred_y = model.predict(test_x)

# Evaluate accuracy
accuracy = accuracy_score(test_y, pred_y)
print('accuracy =', accuracy)

# Plot decision boundary:
# 1. Create a grid of points
x1_min, x1_max = dataset.x[:, 0].min() - 0.1, dataset.x[:, 0].max() + 0.1
x2_min, x2_max = dataset.x[:, 1].min() - 0.1, dataset.x[:, 1].max() + 0.1
# Note: the meshgrid has a finer resolution than the original data (exactly 100 times more points per dimension)
x1, x2 = np.meshgrid(np.arange(x1_min, x1_max, 0.01), np.arange(x2_min, x2_max, 0.01))
# 2. Predict on each point of the grid
Z = model.predict(np.c_[x1.ravel(), x2.ravel()])
# 3. Plot decision boundary point by point
Z = Z.reshape(x1.shape)
plt.contourf(x1, x2, Z, alpha=0.4)
plt.scatter(dataset.x[dataset.y[:, 0] == 0, 0], dataset.x[dataset.y[:, 0] == 0, 1], label='0')
plt.scatter(dataset.x[dataset.y[:, 0] == 1, 0], dataset.x[dataset.y[:, 0] == 1, 1], label='1')
plt.legend()
plt.show()

# Add new non-linear feature to improve classification accuracy
train_x = np.c_[train_x, train_x[:, 0] * train_x[:, 1]]
test_x = np.c_[test_x, test_x[:, 0] * test_x[:, 1]]
print('train_x.shape =', train_x.shape)
print('test_x.shape =', test_x.shape)

# Plot the new feature in 3d
fig = go.Figure(data=[go.Scatter3d(x=dataset.x[dataset.y[:, 0] == 0, 0],
                                   y=dataset.x[dataset.y[:, 0] == 0, 1],
                                   z=dataset.x[dataset.y[:, 0] == 0, 0] * dataset.x[dataset.y[:, 0] == 0, 1],
                                   mode='markers',
                                   marker=dict(size=5, color='red', opacity=0.8)),
                      go.Scatter3d(x=dataset.x[dataset.y[:, 0] == 1, 0],
                                   y=dataset.x[dataset.y[:, 0] == 1, 1],
                                   z=dataset.x[dataset.y[:, 0] == 1, 0] * dataset.x[dataset.y[:, 0] == 1, 1],
                                   mode='markers', marker=dict(size=5, color='blue', opacity=0.8)),
                      go.Surface(x=x1, y=x2, z=x1*x2, colorscale='RdBu', opacity=0.5)])
fig.show()

# Train logistic regression model
model.fit(train_x, train_y.ravel())

input("Press Enter to continue...")

# Predict on test set and evaluate accuracy
pred_y = model.predict(test_x)
accuracy = accuracy_score(test_y, pred_y)
print('accuracy =', accuracy)

# Plot decision boundary
x1_min, x1_max = dataset.x[:, 0].min() - 0.2, dataset.x[:, 0].max() + 0.2
x2_min, x2_max = dataset.x[:, 1].min() - 0.2, dataset.x[:, 1].max() + 0.2
x1, x2 = np.meshgrid(np.arange(x1_min, x1_max, 0.01), np.arange(x2_min, x2_max, 0.01))
Z = model.predict(np.c_[x1.ravel(), x2.ravel(), x1.ravel() * x2.ravel()])
Z = Z.reshape(x1.shape)
plt.contourf(x1, x2, Z, alpha=0.4)
plt.scatter(dataset.x[dataset.y[:, 0] == 0, 0], dataset.x[dataset.y[:, 0] == 0, 1], label='0')
plt.scatter(dataset.x[dataset.y[:, 0] == 1, 0], dataset.x[dataset.y[:, 0] == 1, 1], label='1')
plt.legend()
plt.show()

# Interactive 3d plot with decision boundary
fig = go.Figure(data=[go.Scatter3d(x=dataset.x[dataset.y[:, 0] == 0, 0],
                                   y=dataset.x[dataset.y[:, 0] == 0, 1],
                                   z=dataset.x[dataset.y[:, 0] == 0, 0] * dataset.x[dataset.y[:, 0] == 0, 1],
                                   mode='markers',
                                   marker=dict(size=5, color='red', opacity=0.8)),
                      go.Scatter3d(x=dataset.x[dataset.y[:, 0] == 1, 0],
                                   y=dataset.x[dataset.y[:, 0] == 1, 1],
                                   z=dataset.x[dataset.y[:, 0] == 1, 0] * dataset.x[dataset.y[:, 0] == 1, 1],
                                   mode='markers',
                                   marker=dict(size=5, color='blue', opacity=0.8)),
                      go.Surface(x=x1, y=x2, z=Z, colorscale='RdBu', opacity=0.5)])

fig.show()
