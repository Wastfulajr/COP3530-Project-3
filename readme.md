COP3530 Project 3 README

Team Members:

  Austin Rhee
  
  Serafina Myers
  
  Jonathan Kennel


The aim of this project will be to provide game publishers or developers with information regarding current trends. This allows for informed decision making regarding game planning, and allows one to observe trends in genre popularity, prices, and other sets of information as it relates to average user reviews.


References:

  SteamSpy API (Unofficial)
  
    https://steamspy.com/api.php
  
  Official Steam Web API
  
    https://steamcommunity.com/dev 
  
  Documentation regarding Steam Web API
  
    https://wiki.teamfortress.com/wiki/User:RJackson/StorefrontAPI 
    https://partner.steamgames.com/doc/webapi_overview 
    https://steamapi.xpaw.me/ 
  
  Former project regarding Steam data 
  
    https://nik-davis.github.io/posts/2019/steam-data-collection/


  Useful Data Points:
  
    Genre - Use as a primary delimiter to allow users to compare games in similar genres (FPS vs FPS instead of indie game vs strategy game).
    Score_rank - User reviews aggregated into a game score.
    Owners - Roughly correlated with purchases, can be swayed by price, giveaways & discount frequency.
    Median_forever - Determine playtime of average player (ignores super-users).
    Average_forever - Determine playerbase time including outliers (i.e. games with certain people that have 5-10k+ hours).
    Initialprice - Determines the game pricing upon release date. Influenced by genre, scope, and to a lesser extent release time. (Not inflation adjusted as video game prices are assumed to be relatively stable over the course of our data collection).
