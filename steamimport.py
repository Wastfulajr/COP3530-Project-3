import csv
import json
import time
import datetime
import statistics
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
        print("Error: no URL.\n")
        return
    try:
        jsonReq = rq.get(url=url, params=params)  # Send a GET request to the Steam APi
    except Exception as e:
        print("Excpetion during GET Request: ", e)  # Prints err if rq.get() fails
        print("\nRe-trying request in 5 seconds.")
        time.sleep(5)
        return json_req(url, params)  # Recurse, and attempt to re-make request
    if jsonReq:  # If the request is successful, get the response json
        return jsonReq.json()

def dataRequest(page="0"):
    """Given a page, call json_req to return that page. Default page = 0"""
    params = def_params()
    params["pages"] = page
    data = json_req(urlbase(), def_params())
    return data

def printData(data):
    """Given a dict, read out data"""
    for key in data:
        print("Key: ", key)
        for info in data[key]:
            print(info, ": ", data[key][info])
        print("\n")
