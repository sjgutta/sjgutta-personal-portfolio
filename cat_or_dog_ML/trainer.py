import numpy as np
import tensorflow_datasets as tfds
import tensorflow as tf
from tensorflow import keras
from PIL import Image


LABELS = ["cat", "dog"]


# ds = food_train.take(1)
# for example in ds:
#     print(list(example.keys()))
#     image = example["image"]
#     label = example["label"]
#     print(image.shape, label)


def build_model():
    # 224 x 224 because of the image sizes for the input shape
    # output layer has 101 logits to represent the number of food classes
    # the middle layer is something that can be tuned
    model = keras.Sequential([
        keras.layers.Flatten(input_shape=(224, 224, 3)),
        keras.layers.Dense(128, activation='relu'),
        keras.layers.Dense(1)
    ])
    model.compile(optimizer='adam',
                  loss=tf.keras.losses.BinaryCrossentropy(from_logits=True),
                  metrics=['accuracy'])
    return model


def test_batching(dataset):
    # this is a function being used to make sure the padded batching works properly
    # it will later be edited to improve the model's quality
    train_batch = next(iter(dataset.padded_batch(10, padded_shapes={'image': [512, 512, 3], 'label': []})))
    print(train_batch)
    # print(train_batch['image'])
    # print(train_batch['label'])
    return train_batch


def save_model(trained_model, filename):
    trained_model.save(f"{filename}.h5")
    print(f"Saved model to {filename}.h5")


def load_saved_model(filename):
    loaded_model = tf.keras.models.load_model(filename)
    return loaded_model


def load_data():
    training_data, info = tfds.load("cats_vs_dogs", split="train[80%:]", with_info=True, as_supervised=True)
    print(info)
    testing_data = tfds.load("cats_vs_dogs", split="train[:80%]", as_supervised=True)
    assert isinstance(training_data, tf.data.Dataset)
    assert isinstance(testing_data, tf.data.Dataset)
    return training_data, testing_data


def train_model(model, training_dataset, testing_dataset, epochs=20):
    model.fit(training_dataset, epochs=epochs, validation_data=testing_dataset, verbose=1)


def image_formatter(image, label):
    image = tf.cast(image, tf.float32)
    image = image / 255.0
    image = tf.image.resize(image, (224, 224))
    return image, label


def batch_and_map_ds(dataset):
    return dataset.map(image_formatter).batch(25)


def show_examples():
    dataset, ds_info = tfds.load("cats_vs_dogs", with_info=True)
    tfds.show_examples(dataset, ds_info)


def classify_image(model_filename, img_filename):
    img = tf.io.read_file(img_filename)
    img = tf.image.decode_jpeg(img, channels=3)
    img = tf.image.convert_image_dtype(img, tf.float32)
    img = tf.image.resize(img, [224, 224])
    img = np.expand_dims(img, 0)
    model = load_saved_model(model_filename)
    probability_model = tf.keras.Sequential([model, tf.keras.layers.Softmax()])
    predictions_single = probability_model.predict(img)
    return int(predictions_single)


# training_data, test_data = load_data()
# batched_training_data = batch_and_map_ds(training_data)
# batched_test_data = batch_and_map_ds(test_data)
# model = build_model()
# print("training model")
# train_model(model, batched_training_data, batched_test_data, epochs=15)
# print("model trained")
# save_model(model, "first_try")
# TODO: load model properly after saving to a file
# model = load_saved_model("first_try.h5")
# print(model.summary())
# model.evaluate(batched_test_data, verbose=2)

classify_image("first_try.h5", "simba.jpg")
