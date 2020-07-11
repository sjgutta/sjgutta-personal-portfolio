import numpy as np
import tensorflow_datasets as tfds
import tensorflow as tf
from tensorflow import keras


LABELS = ["cat", "dog"]


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


def build_better_model():
    model = keras.Sequential([
        keras.layers.Conv2D(16, 3, padding='same', activation='relu',
                            input_shape=(224, 224, 3)),
        keras.layers.MaxPooling2D(),
        keras.layers.Dropout(0.2),
        keras.layers.Conv2D(32, 3, padding='same', activation='relu'),
        keras.layers.MaxPooling2D(),
        keras.layers.Conv2D(64, 3, padding='same', activation='relu'),
        keras.layers.MaxPooling2D(),
        keras.layers.Dropout(0.2),
        keras.layers.Flatten(),
        keras.layers.Dense(512, activation='relu'),
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
    predictions_single = model.predict(img)
    if predictions_single >= 0:
        return 1
    else:
        return 0


def check_test_data_predictions(model, ds):
    correct = 0
    wrong = 0
    for example in ds:
        row = example[0]
        labels = example[1]
        for item, label in zip(row, labels):
            # print(item)
            img = np.expand_dims(item, 0)
            print(model.predict(img))
            prediction = model.predict(img)
            if prediction > 0 and label == 1:
                correct += 1
            elif prediction < 0 and label == 0:
                correct += 1
            else:
                wrong += 1
    print(f"Correct: {correct}")
    print(f"Wrong: {wrong}")


# Code to load data and batch properly using functions above
# training_data, test_data = load_data()
# batched_training_data = batch_and_map_ds(training_data)
# batched_test_data = batch_and_map_ds(test_data)

# Code to build, train, and save model
# model = build_better_model()
# train_model(model, batched_training_data, batched_test_data, epochs=10)
# save_model(model, "sigmoid_try")

# Code to load and evaluate model
# model = load_saved_model([INSERT FILENAME HERE])
# check_test_data_predictions(model, ds)
# print(model.summary())
# model.evaluate(batched_test_data, verbose=2)
# model.evaluate(ds, verbose=2)
