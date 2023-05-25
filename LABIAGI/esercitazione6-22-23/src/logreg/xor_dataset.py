import numpy as np
import random
import matplotlib.pyplot as plt


class XORDataset:
    def __init__(self, sample_size=1000, noise_sigma=0.1, seed=0):
        random.seed(seed)
        self.sample_size = sample_size
        self.x = np.zeros((sample_size, 2))
        self.y = np.zeros((sample_size, 1))
        self.noise_sigma = noise_sigma
        self.generate_data()

    def generate_data(self):
        for i in range(self.sample_size):
            x1 = random.randint(0, 1)
            x2 = random.randint(0, 1)
            self.y[i] = x1 ^ x2
            self.x[i, 0] = x1 + random.gauss(0, self.noise_sigma)
            self.x[i, 1] = x2 + random.gauss(0, self.noise_sigma)

    def plot_data(self):
        plt.scatter(self.x[self.y[:, 0] == 0, 0], self.x[self.y[:, 0] == 0, 1], label='0')
        plt.scatter(self.x[self.y[:, 0] == 1, 0], self.x[self.y[:, 0] == 1, 1], label='1')
        plt.legend()
        plt.show()


# test XORDataset class
if __name__ == '__main__':
    dataset = XORDataset()
    print(dataset.x)
    print(dataset.y)
    dataset.plot_data()


