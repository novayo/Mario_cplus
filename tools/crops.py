import copy
import os

import cv2
import numpy as np

IMAGE_FOLDER = "../res/images/"
level_bg = IMAGE_FOLDER + "11.png"  # 替换成你的大图路径

items = {}
blacklists = set()
blacklists.add("water_2.png")

ending_flag = (3, 197.5, "end0_flag.png")
manual_fix = {
    (12, 0): "bush_left.png",
    (11, 1): "bush_left.png",
    (10, 2): "bush_top.png",

    (3, 8): "cloud_left_top.png",
    (4, 8): "cloud_left_bot.png",
    (4, 9): "cloud_center_bot.png",
    (4, 10): "cloud_right_bot.png",
    (3, 10): "cloud_right_top.png",

    (12, 11): "grass_left.png",
    (12, 15): "grass_right.png",

    (12, 16): "bush_left.png",
    (11, 17): "bush_top.png",
    (12, 18): "bush_right.png",

    (2, 19): "cloud_left_top.png",
    (3, 19): "cloud_left_bot.png",
    (3, 20): "cloud_center_bot.png",
    (3, 21): "cloud_right_bot.png",
    (2, 21): "cloud_right_top.png",

    (12, 22): "water_2.png",

    (12, 23): "grass_left.png",
    (12, 25): "grass_right.png",

    (3, 27): "cloud_left_top.png",
    (4, 27): "cloud_left_bot.png",
    (4, 28): "cloud_center_bot.png",
    (4, 29): "cloud_center_bot.png",
    (4, 30): "cloud_center_bot.png",
    (4, 31): "cloud_right_bot.png",
    (3, 31): "cloud_right_top.png",

    (12, 40): "water_2.png",

    (2, 36): "cloud_left_top.png",
    (3, 36): "cloud_left_bot.png",
    (3, 37): "cloud_center_bot.png",
    (3, 38): "cloud_center_bot.png",
    (3, 39): "cloud_right_bot.png",
    (2, 39): "cloud_right_top.png",

    (12, 41): "grass_left.png",
    (12, 44): "grass_right.png",

    (12, 48): "bush_left.png",
    (11, 49): "bush_left.png",
    (10, 50): "bush_top.png",
    (12, 51): "bush_center_0.png",
    (12, 52): "bush_right.png",

    (12, 53): "water_2.png",

    (3, 56): "cloud_left_top.png",
    (4, 56): "cloud_left_bot.png",
    (4, 57): "cloud_center_bot.png",
    (4, 58): "cloud_right_bot.png",
    (3, 58): "cloud_right_top.png",

    (12, 59): "grass_left.png",
    (12, 63): "grass_right.png",

    (12, 64): "bush_left.png",
    (11, 65): "bush_top.png",
    (8, 64): "water_2.png",

    (2, 67): "cloud_left_top.png",
    (3, 67): "cloud_left_bot.png",
    (3, 68): "cloud_center_bot.png",
    (3, 69): "cloud_right_bot.png",
    (2, 69): "cloud_right_top.png",

    (12, 71): "grass_left.png",
    (12, 73): "grass_right.png",

    (3, 75): "cloud_left_top.png",
    (4, 75): "cloud_left_bot.png",
    (4, 76): "cloud_center_bot.png",
    (4, 77): "cloud_center_bot.png",
    (4, 78): "cloud_center_bot.png",
    (4, 79): "cloud_right_bot.png",
    (3, 79): "cloud_right_top.png",

    (4, 80): "water_2.png",
    (4, 82): "water_2.png",

    (2, 84): "cloud_left_top.png",
    (3, 84): "cloud_left_bot.png",
    (3, 85): "cloud_center_bot.png",
    (3, 86): "cloud_center_bot.png",
    (3, 87): "cloud_right_bot.png",
    (2, 87): "cloud_right_top.png",

    (12, 89): "grass_left.png",
    (12, 92): "grass_right.png",

    (12, 96): "bush_left.png",
    (11, 97): "bush_left.png",
    (10, 98): "bush_top.png",
    (12, 97): "bush_center_0.png",
    (12, 98): "bush_center_1.png",

    (3, 104): "cloud_left_top.png",
    (4, 104): "cloud_left_bot.png",
    (4, 105): "cloud_center_bot.png",
    (4, 106): "cloud_right_bot.png",
    (3, 106): "cloud_right_top.png",

    (9, 101): "brickred.png",

    (12, 107): "grass_left.png",
    (12, 111): "grass_right.png",

    (2, 115): "cloud_left_top.png",
    (3, 115): "cloud_left_bot.png",
    (3, 116): "cloud_center_bot.png",
    (3, 117): "cloud_right_bot.png",
    (2, 117): "cloud_right_top.png",

    (12, 112): "bush_left.png",
    (11, 113): "bush_top.png",
    (12, 114): "bush_right.png",

    (12, 115): "water_2.png",
    (12, 116): "water_2.png",

    (12, 119): "grass_left.png",
    (12, 121): "grass_right.png",

    (12, 124): "water_2.png",
    (12, 125): "water_2.png",
    (12, 126): "water_2.png",
    (12, 128): "water_2.png",
    (12, 129): "water_2.png",
    (12, 130): "water_2.png",

    (3, 123): "cloud_left_top.png",
    (4, 123): "cloud_left_bot.png",
    (4, 124): "cloud_center_bot.png",
    (4, 125): "cloud_center_bot.png",
    (4, 126): "cloud_center_bot.png",
    (4, 127): "cloud_right_bot.png",
    (3, 127): "cloud_right_top.png",

    (2, 132): "cloud_left_top.png",
    (3, 132): "cloud_left_bot.png",
    (3, 133): "cloud_center_bot.png",
    (3, 134): "cloud_center_bot.png",
    (3, 135): "cloud_right_bot.png",
    (2, 135): "cloud_right_top.png",

    (12, 144): "bush_left.png",
    (11, 145): "bush_left.png",
    (10, 146): "bush_top.png",

    (3, 152): "cloud_left_top.png",
    (4, 152): "cloud_left_bot.png",
    (4, 153): "cloud_center_bot.png",
    (4, 154): "cloud_right_bot.png",
    (3, 154): "cloud_right_top.png",

    (12, 160): "bush_left.png",
    (11, 161): "bush_top.png",
    
    (12, 159): "grass_right.png",

    (12, 167): "grass_left.png",
    (12, 169): "grass_right.png",

    (12, 174): "water_2.png",
    (12, 175): "water_2.png",
    (12, 176): "water_2.png",

    (2, 163): "cloud_left_top.png",
    (3, 163): "cloud_left_bot.png",
    (3, 164): "cloud_center_bot.png",
    (3, 165): "cloud_right_bot.png",
    (2, 165): "cloud_right_top.png",

    (3, 171): "cloud_left_top.png",
    (4, 171): "cloud_left_bot.png",
    (4, 172): "cloud_center_bot.png",
    (4, 173): "cloud_center_bot.png",
    (4, 174): "cloud_center_bot.png",
    (4, 175): "cloud_right_bot.png",
    (3, 175): "cloud_right_top.png",

    (2, 180): "cloud_left_top.png",
    (3, 180): "cloud_left_bot.png",
    (3, 181): "cloud_center_bot.png",
    (3, 182): "cloud_center_bot.png",
    (3, 183): "cloud_right_bot.png",
    (2, 183): "cloud_right_top.png",

    (12, 192): "bush_left.png",
    (11, 193): "bush_left.png",
    (10, 194): "bush_top.png",

    (3, 200): "cloud_left_top.png",
    (4, 200): "cloud_left_bot.png",
    (4, 201): "cloud_center_bot.png",
    (4, 202): "cloud_right_bot.png",
    (3, 202): "cloud_right_top.png",

    (2, 211): "cloud_left_top.png",
    (3, 211): "cloud_left_bot.png",
    (3, 212): "cloud_center_bot.png",
    (3, 213): "cloud_right_bot.png",
    (2, 213): "cloud_right_top.png",

    (3, 219): "cloud_left_top.png",
    (4, 219): "cloud_left_bot.png",
    (4, 220): "cloud_center_bot.png",
    (4, 221): "cloud_center_bot.png",
    (4, 222): "cloud_center_bot.png",
    (4, 223): "cloud_right_bot.png",
    (3, 223): "cloud_right_top.png",

    (12, 215): "grass_left.png",
    (12, 217): "grass_right.png",

    (12, 207): "grass_right.png",

    (12, 208): "bush_left.png",
    (11, 209): "bush_top.png",

    (2, 198): "end0_dot.png",
    (3, 198): "end0_l.png",
    (4, 198): "end0_l.png",
    (5, 198): "end0_l.png",
    (6, 198): "end0_l.png",
    (7, 198): "end0_l.png",
    (8, 198): "end0_l.png",
    (9, 198): "end0_l.png",
    (10, 198): "end0_l.png",
    (11, 198): "end0_l.png",
}


def calculate_mse(image1, image2):
    """计算两张图像之间的均方差"""
    err = np.sum((image1.astype("float") - image2.astype("float")) ** 2)
    err /= float(image1.shape[0] * image1.shape[1])
    return err


def crop_image(image, x, y, tile_size):
    """从大图中裁剪出指定位置和大小的小图"""
    return image[y : y + tile_size, x : x + tile_size, :]


def find_similar_images(level_bg, IMAGE_FOLDER, tile_size=32):
    """在 IMAGE_FOLDER 中找到与从 level_bg 裁剪出的小图最相似的图像"""
    # 读取大图
    big_image = cv2.imread(level_bg, cv2.IMREAD_COLOR)
    big_image_height, big_image_width, _ = big_image.shape

    # 初始化最小差异和最相似图片的路径
    min_diff = float("inf")
    most_similar_image = None

    ans = []

    maps = {}
    for filename in os.listdir(IMAGE_FOLDER):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            # 读取图片
            image_path = os.path.join(IMAGE_FOLDER, filename)
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

def main():
    print("Matching photos...")
    similar_image_paths = find_similar_images(level_bg, IMAGE_FOLDER)
    big_image = cv2.imread(level_bg, cv2.IMREAD_UNCHANGED)
    original_big_image = copy.deepcopy(big_image)
    for most_similar_image, x, y in similar_image_paths:
        idx_x, idx_y = x // 32, y // 32

        if (idx_x, idx_y) in manual_fix:
            most_similar_image = IMAGE_FOLDER + manual_fix[idx_x, idx_y]
        
        filename = most_similar_image.split("/")[-1]
        if filename not in blacklists:
            items[idx_x, idx_y] = filename

        image = cv2.imread(most_similar_image, cv2.IMREAD_UNCHANGED)
        big_image[x : x + 32, y : y + 32, :] = image

    # Draw ending flag
    image = cv2.imread(IMAGE_FOLDER + ending_flag[2], cv2.IMREAD_UNCHANGED)
    x = ending_flag[0] * 32
    y = int(ending_flag[1] * 32)
    items[ending_flag[0], ending_flag[1]] = ending_flag[2]
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
    cv2.imwrite("modified.jpg", big_image, [cv2.IMWRITE_PNG_COMPRESSION, 0])
    cv2.imwrite("original.jpg", original_big_image, [cv2.IMWRITE_PNG_COMPRESSION, 0])

    print("Done.")
    print()

    for i, j in sorted(items.keys()):
        # {POS(1, 1), std::string("123")},
        print('{POS(%d, %d), std::string("%s")},' % (i, j, items[i, j]))

main()
