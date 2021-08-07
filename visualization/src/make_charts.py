import json
import matplotlib.pyplot as plt
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator
import numpy as np
import os

def make_charts_from_json(json_name):
    print('Starting to convert charts to .jpg for video creation')
    os.system('mkdir plot_images')
    data = open(json_name, 'r')
    for day_number, bot_map in enumerate(data):
        if day_number % 100 == 0:
            print('Day number', day_number, 'has been processed')
        bot_map = json.loads(bot_map)
        dx, dy = 1, 1
        z = np.array(bot_map)
        y, x = np.mgrid[slice(0, z.shape[0] + dy, dy),
                        slice(0, z.shape[1] + dx, dx)]
        levels = MaxNLocator(nbins=15).tick_values(z.min(), z.max())
        cmap = plt.get_cmap('PiYG')
        norm = BoundaryNorm(levels, ncolors=cmap.N, clip=True)
        fig, ax = plt.subplots()
        cf = ax.contourf(x[:-1, :-1] + dx/2.,
                          y[:-1, :-1] + dy/2., z, levels=levels,
                          cmap=cmap)
        fig.colorbar(cf, ax=ax)
        fig.set_size_inches(7, 6)
        ax.set_title('day number ' + str(day_number + 1))
        plt.savefig('plot_images/day_number_' + str(day_number).zfill(6) + '.jpg')
        plt.close()
    print('Conversion was successful')

def main():
    make_charts_from_json('results.json')

if __name__ == '__main__':
    main()
