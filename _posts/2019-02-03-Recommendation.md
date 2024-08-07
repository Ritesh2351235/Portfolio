---
layout: post
title:  "Property Recommendation System by Zillow"
categories: [ Hash-Maps,DataStructure ]
image: assets/images/Recommendation.jpg
tags: []
---

Zillow's property recommendation is a popular feature. It suggests properties to users based on their previous data and interactions. To make this work efficiently, we need to access the data quickly. By using a strong data structure and smart algorithms, we can offer personalized property suggestions that match user preferences. This approach improves user experience, making the platform more engaging and helpful for finding the perfect home.

### Data Storage Strategy
To make property recommendations quickly, let's use in-memory storage. This means all property data will be stored in the computer's memory, avoiding the delays that come with accessing data from a hard disk.

We'll use two hash tables for fast data access. One hash table will be indexed by user_id (uid), making it easy to look up properties that a specific user has rated. The other hash table will be indexed by property_id (pid), allowing quick access to ratings for a specific property.

![Database Schema]({{ site.baseurl }}/assets/images/portfoliodatabase.png)

### Memory Optimization
To save memory space, we'll store both user_id and property_id using only 24 bits. By shifting the user_id or property_id to the upper 24 bits of an integer and storing the rating in the lower 8 bits, we can store and retrieve ratings efficiently using bitwise operations. Additionally, we'll maintain hash tables that keep track of the number of properties each user has rated and the sum of those ratings. Similarly, we'll have hash tables for the number of ratings each property has received and the sum of those ratings. This setup will help us quickly calculate average ratings and add new ratings efficiently.

### Implementation
First, we'll define the data structure by creating hash tables that map users to properties and properties to users. Then, we'll implement functions to add ratings to these hash tables, ensuring that the data is stored compactly. Finally, we'll implement functions to retrieve ratings, calculate averages, and perform specific queries efficiently.

### Algorithm
```cpp
function recommendProperties(uid, minRating) is
    propertyScores := empty hash table
    propertyCounts := empty hash table

    for each data in userToProperties[uid] do
        pid := data >> 8
        rating := data & 0xFF

        for each relatedData in propertyToUsers[pid] do
            relatedUid := relatedData >> 8
            relatedRating := relatedData & 0xFF

            if relatedUid != uid and relatedRating >= minRating then
                propertyScores[pid] += relatedRating
                propertyCounts[pid]++

    recommendations := empty list

    for each entry in propertyScores do
        if propertyCounts[entry.first] > 1 then
            recommendations.push_back(entry.first)

    return recommendations
```
### Time and Space Complexity
#### Best Case
  - **Time Complexity:** `O(1)`
  - **Space Complexity:** `O(1)` per call, growing with the number of ratings

#### Worst Case
 - **Time Complexity:** `O(N * M)` N:properties M: Users
  - **Space Complexity:** `O(P)` P:unique properties

The similar type of datastructure is used for netflix recommendation system.
## Here is the full code implementation [Code](https://github.com/Ritesh2351235/Portfolio/blob/master/assets/Codes/Recommendation.cpp)