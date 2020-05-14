# Multi-threaded Food Delivery Program

This program was written for a software engineering class assignment to showcase introductory multi-threading and networked programming in Java.
The program simulates a food delivery system (similar to how something like Postmates would work) by utilizing multi-threading to properly time orders and dispatch drivers to deliver them.

## The Server program

Running the file titled HQ.java starts the food service which in this case is synonymous with the server for the program. 
- The user is prompted for a file with a schedule of orders, a latitude for the HQ, a longitude, and the number of drivers in service.
- The schedule contains an order on each line. Each order provides a time at which it is ready (in seconds), the food item being ordered, and the restaurant from which it is ordered.
- A sample schedule of orders provided as input can be seen in the relevant section below.

## The Client program

The client program is inside the Driver.java file. Users who start this are prompted with the server and port they want to bind to, which should match those of the server program.
- Once this connects, the driver is added to the pool of drivers waiting on orders from HQ.
- Once all drivers have connected (based on the number specified when starting the server program), the clients and server get messages that the specificed number of drivers has arrived and the service is starting.

## Execution of the program
- The drivers wait in line for orders to be ready. When an order is ready, the first driver in line takes that order and all other available orders and leaves to deliver them.
- While out on delivery, a driver goes to the closest restaurant first. Once that is done, it recalculates distances and finds the closest restaurant from there, making that the next destination.
- Once all orders it is currently delivering have been completed, the driver returns to HQ and joins the back of the line of drivers waiting for orders.
- If no orders are ready, drivers that are currently waiting will continue to wait until an order becomes available and the first driver in line will take that next order.
- If no drivers are ready but an order (or multiple) is ready, the next driver to return to HQ will take that order (and any others that are available) immediately and leave to deliver it.
- Separate threads exist for each driver to allow them to act independently but on the same set of orders.
- Each order also has a thread that sleeps until its preparation time is complete and it is ready for delivery.

## Determining Location of restaurants
- The location of each restaurant is determined using the Yelp API. The restaurant name is searched on the backend and the longitude/latitude is found.
- This is why providing the longitude and longitude for HQ is necessary as input to the Server program. This location is used to determine distance from the different restaurants and plan the order of delivery.

## Sample input file
A sample input file with scheduled orders would look like the following:  
  
  0, Momota Ramen House, black garlic ramen  
0, Momota Ramen House, spicy miso ramen  
0, Slurpin’ Ramen Bar, veggie ramen  
3, Daikokuya Little Tokyo, daikoku ramen  
3, Daikokuya Little Tokyo, daikoku ramen  
9, Daikokuya Little Tokyo, daikoku ramen  
9, Tengoku Ramen Bar, chicken ramen  
10, Tengoku Ramen Bar, tonkotsu ramen  

# Languages/Libraries/Concepts Used
- Java (written in Eclipse IDE)
- Java Multi-threading
- Yelp Fusion API
- File I/O and Parsing
- Web socket and server (networked programming)
