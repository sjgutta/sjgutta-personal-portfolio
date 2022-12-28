import csv
import random


def write_new_train(train_image, train_label, test_image, test_label, start_index):
    with open("new_datasets/train_image.csv", "w") as file:
        # Write train_image up to start_index
        file.write("".join(train_image[0:start_index]))

        # Write after start_index + 10k
        file.write("".join(train_image[start_index + 10000:]))

        # Write out test image to new training set
        file.write("".join(test_image))

    with open("new_datasets/train_label.csv", "w") as file:
        file.write("".join(train_label[0:start_index]))

        file.write("".join(train_label[start_index + 10000:]))

        file.write("".join(test_label))


def write_new_test(train_image, train_label, start_index):
    with open("new_datasets/test_image.csv", "w") as file:
        # Write train_image up to start_index
        file.write("".join(train_image[start_index:start_index + 10000]))

    with open("new_datasets/test_label.csv", "w") as file:
        # Write train_image up to start_index
        file.write("".join(train_label[start_index:start_index + 10000]))


if __name__ == "__main__":
    start_index = random.randint(0, 40000)

    with open("datasets/train_image.csv") as file:
        input_images = file.readlines()

    with open("datasets/train_label.csv") as file:
        input_labels = file.readlines()

    with open("datasets/test_image.csv") as file:
        test_images = file.readlines()

    with open("datasets/test_label.csv") as file:
        test_labels = file.readlines()

    write_new_train(input_images, input_labels, test_images, test_labels, start_index)
    write_new_test(input_images, input_labels, start_index)
