# Cat/Dog Image Classifier

This project classifies an image as being either a cat or a dog. Running the file app.py will pull up a GUI in which a user can select an image and classify it. This project utilizes Python, Tensorflow, Keras, TKinter for building a simple GUI, and numpy.


## Project Purpose

I worked on this project as an introduction to Tensorflow. I have worked with Tensorflow in a professional setting, developing an event recommendation system in my role at Discotech. In order to practice working with Tensorflow, I worked on this simple project. There is certainly room for improvement in some of these techniques and the model's performance which I may make in the future, but this was completed for introductory purposes.

## The Dataset

I used the cats_vs_dogs dataset provided in Tensorflow 2.0.0. The dataset consisted of 23,262 images of cats and dogs, labeled 0 if they were a cat and 1 if they were a dog.
* The dataset was split into a train and test set of data, using the first 80% for training and the remaining 20% for testing.
* This split is something that could be tuned in the future for a more accurate model.

## The Model/Results

The model was built in the build_better_model() function and trained using train_model().
* You can find code inside of trainer.py that is commented out, which was used for building and training the model.
* The model was then saved to a file, which in this case is called current_model.h5, using the Tensorflow h5 format for saving a model to later be loaded and used in a program.
* The model was able to achieve 90% accuracy after 10 epochs of training, using BinaryCrossEntropy as the loss function to be optimized. However, the accuracy was around 68% when running the model on the test data.
* This is a case of overfitting and something I would fix in the future by creating an ImageDataGenerator and applying transformations to the images before training the model.
* The future improvements section below includes other steps I might take to improve my current work. If I make any of them, I will report them back within this README.

## Batching the Data and Performance Issues

I initially intended to complete this project as a food image classifier using the food 101 set. However, when I began to train my model, my computer didn't have enough GPU memory to progress, leading me to pivot to the more simple cats_vs_dogs dataset.
* This is not surprising considering I was working on my MacBook Pro. For complex models, it is typical to have systems that have been custom-built for training ML models and have much more robust hardware.
* The image data was also passed into the model in batches in order to use less memory while training the model.
## Export a file

You can export the current file by clicking **Export to disk** in the menu. You can choose to export the file as plain Markdown, as HTML using a Handlebars template or as a PDF.


## Future Improvements

As previously mentioned, this was a project I did to get acquainted with Tensorflow. I have completed much more complex and high-quality work while using Tensorflow at Discotech. This will later be shared in an article I plan to write about the unique model I have developed there for making recommendations. Below is a list of improvements I would make to this project in the future:
* In the future, I would tune the hyperparameters used in this project to achieve better performance on the test data. This includes finding a good split of test and validation data, a better set of layers in the model, a more ideal input shape, and a better activation function for making predictions.
* I would also implement a callback to reach a target level of performance on the test data and then end training. A common problem I encountered was the data being overfitted. The model accuracy would increase on the training data, but at some point it would begin to get worse on the test data.
* To solve the aforementioned overfitting problem, I would pass the images through an ImageDataGenerator and apply a number of transformations (including zooming, rotations, and flips) before using them for training. This increases the number of examples in the training set, ensures that none are the exact same image, and exposes the model to more aspects of the data in order to generalize better.
* I would make the GUI more advanced in the future. However, for current purposes a simple TKinter GUI works just fine.
