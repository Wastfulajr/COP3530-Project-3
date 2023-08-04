""" Created by Austin Rhee 8/2/2023 """
import csv
import json
import time
import os

import requests as rq  # Used to interface with Steam API HTTP/S requests

def urlbaseSpy():
    """Base API url for SteamSpy"""
    return "https://steamspy.com/api.php"

def urlbaseSteam():
    """Base API url for Steam Store"""
    return "https://store.steampowered.com/api/appdetails"

def def_params():
    """Params for SteamSpy API call"""
    return {"request": "all", "page": "0"}

def fieldsBaseSpy():
    """Headers for SteamSpy data"""
    data_fields = ['appid', 'name', 'developer', 'publisher', 
                    'score_rank', 'positive', 'negative', 'userscore',
                    'owners', 'average_forever', 'average_2weeks',
                    'median_forever', 'median_2weeks', 'price',
                    'initialprice', 'discount', 'ccu']
    return data_fields

def fieldsBaseSteam():
    """Headers for Steam App Data"""
    data_fields = ['steam_appid', 'type', 'name', 'genres', 'metacritic', 'price', 'recommendations', 'developers']
    return data_fields

def json_req(url=None, params=None):
    """Given a url, return the JSON response."""
    if url is None:
        print("Error: no URL.")
        return
    try:
        jsonReq = rq.get(url=url, params=params)  # Send a GET request to the Steam APi
    except Exception as e:
        print("Excpetion during GET Request:", e)  # Prints err if rq.get() fails
        print("Re-trying request in 5 seconds.")
        time.sleep(5)
        return json_req(url, params)  # Recurse, and attempt to re-make request
    if jsonReq:  # If the request is successful, get the response json
        return jsonReq.json()

def dataRequest(url=urlbaseSpy(), params=def_params()):
    """Given a url and params, call json_req to return that url's data.
       Default url defined by urlbaseSpy().
       Default parameters defined by def_params()."""
    data = json_req(url, params)
    if not data:
       print("Failed to process json request for", url)
       print("Retrying in 15 seconds")
       time.sleep(15)
       return dataRequest(params)  # Recurse, and attempt to re-make request
    return data

def printData(data):
    """Given a dict, read out data"""
    """Primarily a test function"""
    for key in data:
        print(key, ": ", data[key], sep="")

def cleanSteamData(data):
    """Given a data dict of Steam data, reformat for .csv writing"""
    data_clean = {}
    for applist in data:  # Only executes ONCE
        for app in data[applist]:  # Only executes ONCE
            for game in data[applist][app]:  # Iterates over every game entry
                data_clean[game['appid']] = game
    print("Cleaned Steam Data.")
    return data_clean

def cleanAppDetails(data):
    """Given a data dict of an app, reformat for .csv writing"""
    req_keys = ['type', 'name', 'steam_appid', 'metacritic', 'genres', 'recommendations', 'developers']
    data_clean = {}
    for appID in data:  # Executes only ONCE
        if data[appID]['success'] == False:
            return data
        info = data[appID]['data']
        for key in info:
            if key not in req_keys:
                continue
            if key == req_keys[3]:  # Metacritic
                data_clean[key] = info[key]['score']
                continue
            if key == req_keys[4]:  # Genres
                data_clean[key] = info[key][0]['description']
                continue
            if key == req_keys[5]:  # Recommendations
                data_clean[key] = info[key]['total']
                continue
            if key == req_keys[6]:  # Developers (Take only top)
                data_clean[key] = info[key][0]
                continue
            else:
                data_clean[key] = info[key]
    return data_clean

def cleanAppPrice(data):
    """Given a data dict of app pricing, reformat for .csv writing"""
    data_clean = {}
    for appID in data:  # Executes ONCE
        if data[appID]['success'] == False:
            data_clean[appID] = '0' 
            return data_clean
        if data[appID]['data']:
            data_clean['price'] = data[appID]['data']['price_overview']['initial']
        else:
            data_clean['price'] = '0'
    return data_clean

def saveData(data, path='data/', file='steamspy.csv', data_fields=fieldsBaseSpy()):
    """Given a dict of data, save to a csv file.
       Takes path, file, datafields as args.
       path: data/
       file: steamspy.csv
       data_fields: fieldsBaseSpy()"""
    dataExists = os.path.isfile(path + file)
    try:
        if not dataExists:  # Case where CSV does not exist, write header & enter 'write' mode
            print("Creating new file", file)
            with open(path + file, 'w', encoding="utf-8", newline='') as f:
                wr = csv.DictWriter(f, fieldnames=data_fields)  # Pass dict() to writehead
                wr.writeheader()  # Pass all data_fields as header
                for key in data:
                    wr.writerow(data[key])
                print("Write complete!")
        else:  # Case where CSV does exist, do not write header & enter 'append' mode
            print("Appending to file", file)
            with open(path + file, 'a', encoding="utf-8", newline='') as f:
                wr = csv.DictWriter(f, fieldnames=data_fields)  # Pass dict() to writehead
                for key in data:
                    wr.writerow(data[key])
                print("Write complete!")
    except Exception as e:
        print("Writing failed! Exception:", e)

def getAppDetails(appID):
    """Query Steam API for App Details (not incl price)
       Accepts appID its arg.
    """
    data = dataRequest(urlbaseSteam(), {'appids': appID, 'l': 'english'})
    if not data:  # If dev has hidden information, return only appid and name
        return {'appid': appID}
    return data

def getAppPrice(appID):
    """Query Steam Storefront API for detailed App Pricing.
       Accepts appID as its only arg.
       Returns both a data stream."""
    data = dataRequest(urlbaseSteam(), {'filters': 'price_overview', 'appids': appID, 'l': 'english'})
    if not data:  # If error, raise.
        print('Error getting', appID)
    return data

def getAppInfo(appID):
    """Calls getAppPrice and getAppDetails for data streams,
       then calls cleanAppPrice and cleanAppDetails to format
       for proper writing to .csv files
       Returns a data dict object"""
    appDetails = cleanAppDetails(getAppDetails(appID))
    appPrice = cleanAppPrice(getAppPrice(appID))
    merge_data ={'': appDetails | appPrice }
    return merge_data