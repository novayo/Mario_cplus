import copy
import os

import cv2
import numpy as np


def calculate_mse(image1, image2):
    """计算两张图像之间的均方差"""
    err = np.sum((image1.astype("float") - image2.astype("float")) ** 2)
    err /= float(image1.shape[0] * image1.shape[1])
    return err


def crop_image(image, x, y, tile_size):
    """从大图中裁剪出指定位置和大小的小图"""
    return image[y : y + tile_size, x : x + tile_size, :]


def find_similar_images(big_image_path, image_folder, tile_size=32):
    """在 image_folder 中找到与从 big_image_path 裁剪出的小图最相似的图像"""
    # 读取大图
    big_image = cv2.imread(big_image_path, cv2.IMREAD_COLOR)
    big_image_height, big_image_width, _ = big_image.shape

    # 初始化最小差异和最相似图片的路径
    min_diff = float("inf")
    most_similar_image = None

    ans = []

    maps = {}
    for filename in os.listdir(image_folder):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            # 读取图片
            image_path = os.path.join(image_folder, filename)
            image = cv2.imread(image_path, cv2.IMREAD_COLOR)
            if image.shape[0] != 32 or image.shape[1] != 32:
                continue
            maps[image_path] = image

    # 遍历大图并裁剪出所有的小图，并与文件夹中的图片比较
    for x in range(0, big_image_width - tile_size + 1, tile_size):
        for y in range(0, big_image_height - tile_size + 1, tile_size):
            # 裁剪出小图
            cropped_image = crop_image(big_image, x, y, tile_size)

            # 初始化最小差异和最相似图片的路径
            min_diff = float("inf")
            most_similar_image = None

            # 遍历文件夹中的所有图片
            for image_path, image in maps.items():
                diff = calculate_mse(cropped_image, image)

                # 更新最小差异和最相似图片路径
                if diff < min_diff:
                    min_diff = diff
                    most_similar_image = image_path

            ans.append((most_similar_image, y, x))
    return ans


# 示例用法
image_folder = "../res/images"
big_image_path = image_folder + "/11.png"  # 替换成你的大图路径


print("Matching photos...")
similar_image_paths = find_similar_images(big_image_path, image_folder)
big_image = cv2.imread(big_image_path, cv2.IMREAD_UNCHANGED)
original_big_image = copy.deepcopy(big_image)
for most_similar_image, x, y in similar_image_paths:
    idx_x, idx_y = x // 32, y // 32
    image = cv2.imread(most_similar_image, cv2.IMREAD_UNCHANGED)
    big_image[x : x + 32, y : y + 32, :] = image


print("Making image 3 times bigger...")
big_image = cv2.resize(big_image, (7168 * 3, 480 * 3))
original_big_image = cv2.resize(original_big_image, (7168 * 3, 480 * 3))
block_size = 32 * 3


print("Drawing lines & pos...")
for most_similar_image, y, x in similar_image_paths:
    x, y = x * 3, y * 3
    cv2.rectangle(
        big_image, (x, y), (x + block_size, y + block_size), (0, 255, 0), 2
    )  # Green rectangle with thickness 2
    cv2.rectangle(
        original_big_image, (x, y), (x + block_size, y + block_size), (0, 255, 0), 2
    )  # Green rectangle with thickness 2

    text = f"({y//block_size}, {x//block_size})"

    # Calculate the position to place the text centered in the rectangle
    text_size, _ = cv2.getTextSize(text, cv2.FONT_HERSHEY_SIMPLEX, 0.1, 1)
    text_x = x + (block_size - text_size[0]) // 2 - 30
    text_y = y + (block_size + text_size[1]) // 2

    # Draw the text centered in the rectangle
    cv2.putText(
        big_image,
        text,
        (text_x, text_y),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.5,
        (255, 255, 255),
        2,
    )
    cv2.putText(
        original_big_image,
        text,
        (text_x, text_y),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.5,
        (255, 255, 255),
        2,
    )


print("Outputing results...")
cv2.imwrite("modified.png", big_image, [cv2.IMWRITE_PNG_COMPRESSION, 0])
cv2.imwrite("original.png", original_big_image, [cv2.IMWRITE_PNG_COMPRESSION, 0])


print("Done.")
