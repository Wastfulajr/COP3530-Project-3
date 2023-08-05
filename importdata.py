"""Created by Austin Rhee 8/3/2023"""
import time

from src import steamimport as stim
from src import CSVHandler as csvh

def GetAppLists():
    """Provided a list of appIDs, query Steam API for detailed information,
       Sanitize the gathered data, then write this data to a .csv file.
       User defined number of games to process"""
    appIDs = csvh.grabAppIDs('steamofficial.csv')
    index = csvh.grabIndex('indexer.csv')
    stIndex = index
    end = len(appIDs)

    while True:
        try:
           # groupSize = int(input('Number of games to process: '))
           # Used if user Defined sizes are required
           groupSize = 500
        except ValueError:
            print('Please input an integer.')
        else:
            break
    
    print('Beginning at index', index)
    st = time.time()
    while (index < end - 1) and (index - stIndex < groupSize):
        appInfo = stim.getAppInfo(appIDs[index])
        if appInfo == False:
            print('JSON failure at', index)
            print('Stopping requests...')
            break
        stim.saveData(appInfo, 'data/', 'compAppInfo.csv', stim.fieldsBaseSteam())
        index += 1
        csvh.updateIndex(index, 'indexer.csv')
        if index % 10 == 0 and index != 0:
            en = time.time()
            print('Jobs', index - 10, 'to', index, 'completed.')
            print('Took', round(en - st, 2), 'seconds')
            st = time.time()
    print(index - stIndex, 'completed. Stopping...')
    csvh.updateIndex(index, 'indexer.csv')

if __name__ == '__main__':
    GetAppLists()