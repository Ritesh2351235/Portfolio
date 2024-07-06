---
layout: post
title:  "Red Riding Hood"
author: sal
categories: [ Jekyll, tutorial ]
image: assets/images/3.jpg
---
Zillow wants to enhance its platform by improving the efficiency of property search operations. By using skip lists, a data structure that allows for fast insertion, deletion, and lookup of properties based on various attributes (e.g., price, location, size), Zillow aims to provide a more responsive and user-friendly experience. This approach helps users quickly find properties that match their criteria, making the platform more engaging and effective.

## Design Technique
Skip lists are a probabilistic data structure that allows for fast search, insertion, and deletion operations. They achieve this by maintaining multiple levels of linked lists, where each higher level skips over a larger number of elements. This design provides a balance between simplicity and efficiency, making it well-suited for dynamic data sets with frequent updates.

![Skip List]({{ site.baseurl }}/assets/images/Skiplist.gif)

### Learn more about Skip List here - [Article](https://medium.com/@danielorihuelarodriguez/skip-list-in-rust-explained-eb506693e4fd#:~:text=A%20Skip%20List%20is%20a%20probabilistic%20data%20structure%20that%20serves,than%20%E2%80%9Cn%E2%80%9D%20linked%20lists.)

## Implementation

   - Represent properties with attributes such as price, location, and size.
   - Define the skip list structure with levels and pointers for forward traversal.
   - Set up probability and max level parameters for balancing.
   - Insert properties into the skip list based on their attributes.
   - Adjust the levels of the skip list nodes according to the defined probability.
   - Implement deletion to remove properties from the skip list.
   - Update pointers and levels to maintain the structure.
   - Implement efficient search to find properties based on specific attributes.
   - Utilize the skip list's layered structure to perform fast lookups.
   - Ensure that the skip list remains balanced with frequent updates.
   - Adjust the probability and maximum levels as necessary.
   - Provide search results to users based on their queries.
   - Ensure quick response times and relevant property listings.

## Algorithm
Algorithm to insert a node in the skip list
```cpp
Insert(list, searchKey, newValue)
local update[1..MaxLevel]
x := list→header
for i := list→level downto 1 do
while x→forward[i]→key < searchKey do
x := x→forward[i]
-- x→key < searchKey ≤ x→forward[i]→key
update[i] := x
x := x→forward[1]
if x→key = searchKey then x→value := newValue
else
lvl := randomLevel()
if lvl > list→level then
for i := list→level + 1 to lvl do
update[i] := list→header
list→level := lvl
x := makeNode(lvl, searchKey, value)
for i := 1 to level do
x→forward[i] := update[i]→forward[i]
update[i]→forward[i] := x
```
Algorithm to delete a node in the skip List 
```cpp
Delete(list, searchKey)
local update[1..MaxLevel]
x := list→header
for i := list→level downto 1 do
while x→forward[i]→key < searchKey do
x := x→forward[i]
update[i] := x
x := x→forward[1]
if x→key = searchKey then
for i := 1 to list→level do
if update[i]→forward[i] ≠ x then break
update[i]→forward[i] := x→forward[i]
free(x)
while list→level > 1 and
list→header→forward[list→level] = NIL do
list→level := list→level – 1
```
## Here is the full code implementation [Code](https://gist.github.com/hjy0102/d83518e77b0d01864b8a427b78053bed)
