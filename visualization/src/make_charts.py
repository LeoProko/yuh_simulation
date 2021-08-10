import json
import matplotlib.pyplot as plt
from matplotlib.colors import BoundaryNorm
from matplotlib.ticker import MaxNLocator
import numpy as np
import os

class MakeCharsFromJson:
    def __init__(self):
        os.system('rm -rf charts')
        os.system('mkdir charts')
        os.system('mkdir charts/map')

    def map(self, json_name):
        json_path = 'json/' + json_name + '.json'
        print('Starting to convert map charts to .jpg for video creation')
        data = open(json_path, 'r')
        for day_number, bot_map in enumerate(data):
            if day_number % 10 == 0:
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
            fig.set_size_inches(14, 12)
            ax.set_title('day number ' + str(day_number + 1))
            plt.savefig('charts/map/day_number_' + str(day_number).zfill(6) + '.jpg')
            plt.close()
        print('Converting was successful')

    def parameters(self, json_name):
        json_path = 'json/' + json_name + '.json'
        print('Starting to convert parameters charts to .jpg for video creation')
        data = open(json_path, 'r')
        average_parameters = dict()
        genes_list = data.readline().split()
        for gene in genes_list:
            average_parameters[gene] = []
        for day_number, parameters in enumerate(data):
            parameters = json.loads(parameters)
            for parameter in parameters:
                average_parameters[parameter].append(parameters[parameter])
        days_amount = len(average_parameters[genes_list[0]])
        plt.figure(figsize=(20, 10))
        for gene in genes_list:
            plt.plot(range(days_amount), average_parameters[gene], label=gene)
        plt.legend()
        plt.title('Average parameters')
        plt.xlabel('Day')
        plt.ylabel('Absolute parameter value')
        plt.ylim([0, 100])
        plt.savefig('charts/parameters.jpg')
        print('Converting was successful')

def main():
    charts = MakeCharsFromJson()
    charts.map('bots_amount')
    charts.parameters('parameters')
    print('Please, run make_video.sh')

if __name__ == '__main__':
    main()
