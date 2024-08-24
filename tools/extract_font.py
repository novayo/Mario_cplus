"""Tool to extract font.png.

The original crop size is 8*8 px. In the tool, the image is showed 5 times bigger.
Also shows the index of each text.
Press ESC to stop the process.
"""

import cv2

IMAGE_FOLDER = "../res/images/"
font = cv2.imread(IMAGE_FOLDER + "font.png")
block_size = 8*5
font = cv2.resize(font, (512 * 5, 8 * 5))

for x in range(54):
    x = x*block_size
    y = 0
    cv2.rectangle(
        font, (x, y), (x + block_size, y + block_size), (0, 255, 0), 2
    )
    text = f"{x//block_size}"

    # Calculate the position to place the text centered in the rectangle
    text_size, _ = cv2.getTextSize(text, cv2.FONT_HERSHEY_SIMPLEX, 0.1, 1)
    text_x = x + (block_size - text_size[0]) // 2
    text_y = y + (block_size + text_size[1]) // 2 + 13

    # Draw the text centered in the rectangle
    cv2.putText(
        font,
        text,
        (text_x, text_y),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.5,
        (0, 0, 0),
        2,
    )

cv2.imshow("123", font)
cv2.waitKey(0)
