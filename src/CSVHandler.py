"""Created by Austin Rhee 8/4/2023"""
import csv

def grabAppIDs(file, path='data/'):
    """Given a CSV in which the first column is appIDs, return a
       list of appIDs for use in other functions
       Returns an array of string appIDs"""
    appIDs = []
    with open(path + file, newline='', encoding='utf-8') as f:
        rd = csv.reader(f, delimiter=',')
        for row in rd:
            if row[0] == 'appid':
                continue
            else:
                appIDs.append(row[0])
    return appIDs

def createIndexer(file, path='data/'):
    """Given an indexer file and path, initialize index to 0.
       Used to ensure that downloading of AppData can be interrupted
       and resumed."""
    with open(path + file, 'w', encoding='utf-8', newline='') as f:
        print(0, file=f)

def grabIndex(file, path='data/'):
    """Given an indexer file and path, grab current index."""
    try:
        with open(path + file, encoding='utf-8', newline='') as f:
            return int(f.readline())
    except FileNotFoundError:  # If indexer not found, create it and return index = 0
        createIndexer(file, path)
        return 0
    
def updateIndex(index, file, path='data/'):
    """Given index, and indexer file and path, update index."""
    with open(path + file, 'w', encoding='utf-8', newline='') as f:
        print(index, file=f)