import tensorflow_datasets as tfds
import tensorflow as tf
from tensorflow import keras

# ds = food_train.take(1)
# for example in ds:
#     print(list(example.keys()))
#     image = example["image"]
#     label = example["label"]
#     print(image.shape, label)


def build_model():
    # 512 x 512 because of the image sizes for the input shape
    # output layer has 101 logits to represent the number of food classes
    # the middle layer is something that can be tuned
    model = keras.Sequential([
        keras.layers.Flatten(input_shape=(512, 512)),
        keras.layers.Dense(128, activation='relu'),
        keras.layers.Dense(101)
    ])
    model.compile(optimizer='adam',
                  loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
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


def get_batch(dataset):
    train_batch = dataset.padded_batch(10, padded_shapes={'image': [512, 512, 3], 'label': []})
    # print(train_batch['image'])
    # print(train_batch['label'])
    return train_batch

# def save_model():
#
#
# def load_saved_model():
#
#


def load_data():
    food_data, info = tfds.load("food101", with_info=True)
    training_data, testing_data = food_data["train"], food_data["validation"]
    assert isinstance(training_data, tf.data.Dataset)
    assert isinstance(testing_data, tf.data.Dataset)
    return training_data, testing_data


def train_model(model, training_dataset, testing_dataset):
    model.fit(
        tuple(training_dataset.shuffle(101000).padded_batch(10, padded_shapes={'image': [512, 512, 3], 'label': []})),
        epochs=20,
        validation_data=testing_dataset.padded_batch(10, padded_shapes={'image': [512, 512, 3], 'label': []}),
        verbose=1)


# def classify_image():
#
#


def get_labels_array():
    with open("labels.txt") as f:
        lines = (line.rstrip() for _, line in zip(range(101), f.readlines()))
        for line in lines:
            print(line)


train_data, validation_data, test_data = tfds.load(
    name="imdb_reviews",
    split=('train[:60%]', 'train[60%:]', 'test'),
    as_supervised=True)
print(train_data)
train_data, test_data = load_data()
print(train_data)
batch = get_batch(train_data)
print(batch)
model = build_model()
# train_model(model, train_data, test_data)
# TODO: save model properly after training
# TODO: load model properly after saving to a file
