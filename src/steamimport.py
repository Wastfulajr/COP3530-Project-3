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
    """Params for API call"""
    return {"request": "all", "page": "0"}

def json_req(url=None, params=None):
    """Given a url, return the JSON response."""
    if url is None:
        print("Error: no URL.")
        return
    try:
        jsonReq = rq.get(url=url, params=params)  # Send a GET request to the Steam APi
    except Exception as e:
        print("Excpetion on page ", params["page"], " during GET Request:\n", e)  # Prints err if rq.get() fails
        print("\nRe-trying request in 5 seconds.")
        time.sleep(5)
        return json_req(url, params)  # Recurse, and attempt to re-make request
    if jsonReq:  # If the request is successful, get the response json
        return jsonReq.json()

def dataRequest(page="0"):
    """Given a page, call json_req to return that page. Default page = 0"""
    params = def_params()
    params["page"] = str(page)
    data = json_req(urlbase(), params)
    return data

def printData(data):
    """Given a dict, read out data"""
    """Primarily a test function"""
    for key in data:
        for info in data[key]:
            print(info, ": ", data[key][info])
        print("\n")

def saveData(data):
    """Given a dict of data, save to a csv file"""
    dataExists = os.path.isfile('test/steamspy.csv')
    data_fields = ['appid', 'name', 'developer', 'publisher', 
                        'score_rank', 'positive', 'negative', 'userscore',
                        'owners', 'average_forever', 'average_2weeks',
                        'median_forever', 'median_2weeks', 'price',
                        'initialprice', 'discount', 'ccu']
    try:
        if not dataExists:  # Case where CSV does not exist, write header & enter 'write' mode
            print("Creating new file steamspy.csv")
            with open('test/steamspy.csv', 'w', encoding="utf-8", newline='') as f:
                wr = csv.DictWriter(f, fieldnames=data_fields)  # Pass dict() to writehead
                wr.writeheader()  # Pass all data_fields as header
                for key in data:
                    wr.writerow(data[key])
                print("Write complete!")
        else:  # Case where CSV does exist, do not write header & enter 'append' mode
            print("Appending to file steamspy.csv")
            with open('test/steamspy.csv', 'a', encoding="utf-8", newline='') as f:
                wr = csv.DictWriter(f, fieldnames=data_fields)  # Pass dict() to writehead
                for key in data:
                    wr.writerow(data[key])
                print("Write complete!")
    except Exception as e:
        print("Writing failed! Exception: ", e)