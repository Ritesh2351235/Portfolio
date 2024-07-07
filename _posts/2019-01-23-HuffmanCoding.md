---
layout: post
title:  "Property Image Compression using Huffman Coding for efficient Storage and retrival"
categories: [ Huffman Coding , Algorithm ]
image: assets/images/6.jpg
---

Zillow hosts a vast number of property images, which can consume significant storage space and bandwidth. To address this, Huffman Coding can be used to compress these images efficiently. Huffman Coding is a lossless data compression algorithm that can significantly reduce the size of image files without compromising their quality.

By analyzing the frequency of pixel values in property images, Huffman Coding creates a variable-length code for each pixel value. More frequent pixel values are assigned shorter codes, while less frequent ones are given longer codes. This method optimizes the overall size of the image files.

### Perks of image compression in zillow platform:
- Reduced storage costs due to smaller image file sizes.
- Faster image loading times, leading to an improved user experience.
- Efficient use of bandwidth, especially for users with slower internet connections.

## Implementation

**Compressing the image:**
- Extract pixel value frequencies from a sample set of property images.
- Build a frequency table for the pixel values.

- Create leaf nodes for each pixel value and its frequency.
- Construct the Huffman Tree by repeatedly merging the two nodes with the lowest frequencies until only one node remains.

- Traverse the Huffman Tree to assign binary codes to each pixel value.
- Ensure that more frequent pixel values receive shorter codes.

- Replace each pixel value in the image with its corresponding Huffman code.
- Store the compressed binary data and the Huffman Tree for later decompression.

**Extracting the Original image:**
- Use the stored Huffman Tree to decode the compressed binary data back into the original pixel values.
- Reconstruct the image from the decoded pixel values.

## Algorithm  for Huffman coding(text based compression)

![Algorithm ]({{ site.baseurl }}/assets/images/Huffmann.png)

## Here is the Full code for image compression using huffman Coding for efficient image storage [Code](https://github.com/sudhamshu091/Huffman-Encoding-Decoding-For-Image-Compression/blob/main/huffman.py)

## For the full information on image compression using Huffman Coding refer the following paper [Paper](https://www.academia.edu/35330074/Compression_Using_Huffman_Coding_on_Digital_Image_for_LSB_Steganography)