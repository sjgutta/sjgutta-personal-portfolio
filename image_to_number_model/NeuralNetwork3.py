import sys
import pandas
import numpy


LEARNING_RATE = 0.01
NUM_EPOCHS = 75
BATCH_SIZE = 50


DEBUG = True


def debug_print(contents):
    if DEBUG:
        print(contents)


def activation_function(input_values):
    """
    This is a sigmoid activation function (as suggested in assignment description).
    """
    # Have to clip to avoid overflow errors
    input_values = numpy.clip(input_values, -500, 500)
    return 1/(1 + numpy.exp(-input_values))


def activation_backwards(input_values):
    """
    This is the activation function but backwards for back prop.
    """
    act_function = activation_function(input_values)
    return act_function * (1 - act_function)


def softmax(input_values):
    """
    Implementing softmax function on numpy array.
    """
    e_x = numpy.exp(input_values - input_values.max())
    return e_x / numpy.sum(e_x, axis=0)


def softmax_backwards(input_values):
    """
    Implementing derivative of softmax for back propagation.
    """
    e_x = numpy.exp(input_values - input_values.max())
    return e_x / numpy.sum(e_x, axis=0) * (1 - e_x / numpy.sum(e_x, axis=0))


class Network:
    """
    This class is my custom Neural Network class
    """
    def __init__(self):
        # Initialize layers of the network
        # There is an input layer with 784 nodes (28 x 28 pixels)
        # Hidden layers with 256 and 128 nodes
        # And an output layer with 10 nodes for classifying digits
        self.input_layer = Layer(784, 150)
        self.hidden_layer_1 = Layer(150, 80)
        self.hidden_layer_2 = Layer(80, 10)
        self.output_layer = Layer(10, 1)

    def train_network(self, training_data, training_labels):
        """
        This method is used to train the network on some test data using epochs and batches.
        """
        for i in range(0, NUM_EPOCHS):
            debug_print(f"Training Epoch Number {i + 1}")
            # Shuffle training data and labels in unison
            p = numpy.random.permutation(training_data.shape[1])
            shuffled_training_data = training_data[p].T
            shuffled_training_labels = training_labels[p]

            # Calculating number of batches to use
            num_batches = (training_data.shape[1] // BATCH_SIZE) + 1

            for j in range(0, num_batches):
                # Generate batch data and labels
                if (j + 1) * BATCH_SIZE > training_data.shape[1]:
                    end_index = training_data.shape[1]
                else:
                    end_index = (j + 1) * BATCH_SIZE
                batch_data = shuffled_training_data[j * BATCH_SIZE:end_index]
                batch_labels = shuffled_training_labels[j * BATCH_SIZE:end_index]

                if batch_data.shape[0] == 0:
                    # Skip empty array at end
                    continue

                forward_pass_results = self.forward_pass(batch_data.T)

                self.back_propagation(batch_data.T, batch_labels.T, forward_pass_results)

    def forward_pass(self, batch):
        # TODO: Add biases if needed for better accuracy

        # Calculate input to hidden layer 1
        INPUT_1 = numpy.dot(self.input_layer.weights, batch)

        # Calculate activation values out of hidden layer 1
        ACTIVATION_1 = activation_function(INPUT_1)

        # Calculating input to hidden layer 2
        INPUT_2 = numpy.dot(self.hidden_layer_1.weights, ACTIVATION_1)

        # Calculate activation values out of hidden layer 2
        ACTIVATION_2 = activation_function(INPUT_2)

        # Calculate Input values of output layer
        INPUT_3 = numpy.dot(self.hidden_layer_2.weights, ACTIVATION_2)

        # Calculate activation values from output layer
        ACTIVATION_3 = softmax(INPUT_3)

        return {
            "INPUT_1": INPUT_1,
            "ACTIVATION_1": ACTIVATION_1,
            "INPUT_2": INPUT_2,
            "ACTIVATION_2": ACTIVATION_2,
            "INPUT_3": INPUT_3,
            "ACTIVATION_3": ACTIVATION_3
        }

    def back_propagation(self, input_data, expected_outputs, forward_pass_results):
        output_values = forward_pass_results['ACTIVATION_3']

        batch_size = expected_outputs.shape[1]

        """
        Layer 1 Calculations
        """
        # Based on derivative of MSE (I dropped the constant 2 in front of it)
        d_error_to_outputs = (output_values - expected_outputs) / batch_size

        # Calculate gradients using error gradients above and activation values
        # I tried doing softmax backwards at first for middle derivative per derivations I read online
        # For some reason it works much better without that (not really sure why)
        output_layer_gradients = numpy.dot(d_error_to_outputs, forward_pass_results['ACTIVATION_2'].T)

        """
        Layer 2 Calculations
        """
        # New derivative of error to outputs (but now from layer 2)
        d_error_to_outputs = numpy.dot(self.hidden_layer_2.weights.T, d_error_to_outputs)

        # Using derivative of activation function for "backwards" version
        # Call on INPUT values per derivation for back prop (dA/dI)
        d_outputs_to_inputs = activation_backwards(forward_pass_results['INPUT_2'])

        hidden_layer_2_gradients = d_error_to_outputs * d_outputs_to_inputs
        # Applied chain rule above and then did dot product with activation values from input layer
        hidden_layer_2_gradients = numpy.dot(hidden_layer_2_gradients, forward_pass_results['ACTIVATION_1'].T)

        """
        Layer 3 Calculations
        """
        # Same as layer 2 back prop
        d_error_to_outputs = numpy.dot(self.hidden_layer_1.weights.T, d_error_to_outputs * d_outputs_to_inputs)
        d_outputs_to_inputs = activation_backwards(forward_pass_results['INPUT_1'])

        hidden_layer_1_gradients = d_error_to_outputs * d_outputs_to_inputs
        # Used input data since that's technically the activation values going into input layer
        hidden_layer_1_gradients = numpy.dot(hidden_layer_1_gradients, input_data.T)

        """
        Updating Weights
        """
        # TODO: Update biases?
        self.input_layer.weights -= LEARNING_RATE * hidden_layer_1_gradients
        self.hidden_layer_1.weights -= LEARNING_RATE * hidden_layer_2_gradients
        self.hidden_layer_2.weights -= LEARNING_RATE * output_layer_gradients


class Layer:
    def __init__(self, n_nodes, next_n_nodes):
        # Weights, irrelevant for output layer
        self.weights = numpy.random.randn(next_n_nodes, n_nodes) * numpy.sqrt(1. / n_nodes)

        # # One bias value for each node in this layer (irrelevant for input layer)
        # self.biases = numpy.random.rand(n_nodes, 1)


def make_predictions(network: Network, test_data, output_file):
    forward_pass_results = network.forward_pass(test_data)

    # Find predicted digits
    predictions = numpy.argmax(forward_pass_results['ACTIVATION_3'], axis=0)
    pandas.DataFrame(predictions).to_csv(output_file, header=None, index=None)


def convert_labels_to_one_hot(labels):
    result = numpy.zeros((labels.size, 10))
    result[numpy.arange(labels.size), labels] = 1
    return result.T

"""
Command to copy for running locally:
python3 NeuralNetwork3.py datasets/train_image.csv datasets/train_label.csv datasets/test_image.csv
"""


"""
Command for accuracy check after run
python3 NeuralNetwork3.py datasets/train_image.csv datasets/train_label.csv datasets/test_image.csv datasets/test_label.csv
python3 NeuralNetwork3.py new_datasets/train_image.csv new_datasets/train_label.csv new_datasets/test_image.csv new_datasets/test_label.csv
"""


def check_accuracy(network, data, labels):
    predictions_array = []

    results = network.forward_pass(data)
    results = results['ACTIVATION_3']

    predictions = numpy.argmax(results, axis=0)

    predictions_array.append(predictions == labels)
    accuracy = numpy.mean(predictions_array)

    print(f"Accuracy Achieved: {accuracy}")


if __name__ == "__main__":
    # Reading in data from files
    training_data = pandas.read_csv(sys.argv[1], header=None)
    training_labels = pandas.read_csv(sys.argv[2], header=None)
    testing_data = pandas.read_csv(sys.argv[3], header=None)

    testing_labels = None
    if len(sys.argv) > 4:
        testing_labels = pandas.read_csv(sys.argv[4], header=None)

    network = Network()

    # Convert labels to one hot encoding for calculating loss later
    one_hot_labels = convert_labels_to_one_hot(training_labels.T.values)

    # Train the network
    network.train_network(training_data.T, one_hot_labels.T)

    # Make the predictions
    make_predictions(network, testing_data.T.values, "test_predictions.csv")

    if testing_labels is not None:
        check_accuracy(network, testing_data.T.values, testing_labels.T.values)
