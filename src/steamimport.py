""" Created by Austin Rhee 8/2/2023 """
import csv
import json
import time
import os

import requests as rq  # Used to interface with Steam API HTTP/S requests

def urlbase():
    """Base API url for Steamspy"""
    return "https://steamspy.com/api.php"

def def_params():
    """Params for SteamSpy API call"""
    return {"request": "all", "page": "0"}

def fieldsBase():
    """Headers for SteamSpy data"""
    data_fields = ['appid', 'name', 'developer', 'publisher', 
                    'score_rank', 'positive', 'negative', 'userscore',
                    'owners', 'average_forever', 'average_2weeks',
                    'median_forever', 'median_2weeks', 'price',
                    'initialprice', 'discount', 'ccu']

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

def dataRequest(url=urlbase(), params=def_params()):
    """Given a page, call json_req to return that page.
       Default url defined by urlbase().
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
        for info in data[key]:
            print(info, ": ", data[key][info])
        print("\n")

def saveData(data, path='data/', file='steamspy.csv', data_fields=fieldsBase()):
    """Given a dict of data, save to a csv file.
       Takes path, file, datafields as args.
       path: data/
       file: steamspy.csv
       data_fields: fieldsBase()"""
    dataExists = os.path.isfile(path)
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

def cleanSteamData(data):
    data_clean = {}
    for applist in data:  # Only iterates ONCE
        for app in data[applist]:  # Only iterates ONCE
            for game in data[applist][app]:
                data_clean[game['appid']] = game
    print("Cleaned Steam Data.")
    return data_clean